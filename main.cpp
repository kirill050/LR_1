#include <iostream>
#include <any>
#include <map>
#include <cstring>
#include <fstream>

using namespace std;
class Json {
public:
    // ����������� �� ������, ���������� Json-������.
    Json(const std::string& s): json_string(s){}

    // ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
    bool is_array(const string &str) const{
        /*if((str[0] == '[') && (str[str.length()-1] == ']')) return true;
        else return false;*/
        return _is_array;
    }
   	// ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
    bool is_object(const string &str) const{
        if(str.find(':') != string::npos) return true;
        else return false;
    }

    // ����� ���������� �������� �� ����� key, ���� ��������� �������� JSON-��������.
    // �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
    // ���� ��������� �������� JSON-��������, ������������ ����������.
    std::any& operator[](const std::string& key);

    // ����� ���������� �������� �� ������� index, ���� ��������� �������� JSON-��������.
    // �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
    // ���� ��������� �������� JSON-��������, ������������ ����������.
    std::any& operator[](int index);

    // ����� ���������� ������ ������ Json �� ������, ���������� Json-������.
    static Json parse(const std::string& s);

    // ����� ���������� ������� ������ Json �� �����, ����������� Json-������ � ��������� �������.
    static Json parseFile(const std::string& path_to_file);

public:
    std::string json_string;
    bool _is_array;
    any *_array;

    bool _is_object;
    std::map <std::string, std::any> _parsed_json;
};


void make_string_from_json_file(const string file_name, string &json_string_holder){
    ifstream JSON_file(file_name);
    string word;
    char ch;
    if(JSON_file.is_open()){
        while (true)
        {
            JSON_file.get(ch);
            if (JSON_file.eof()) break;
            word.append(1, ch);
        }
        cout << word << endl;
        JSON_file.close();
    }
    json_string_holder = word;
}

int main()
{
    string JSON;
    make_string_from_json_file("JSON.txt", JSON);

    Json *F1 = new Json(JSON);

    //cout << "IS it an array? " << F1->is_array(F1->json_string);
    delete F1;

    //std::map <std::any, std::any> parsed_json;
    map <std::string, std::any> parsed_json;

    parsed_json["Patric"] = 15;
    parsed_json["Patrric"] = 5;
    parsed_json["Patrrrric"] = 5;
    parsed_json["Patrrrrrrrrric"] = 5;

    int b = 65;
    any a = &b;
    cout << a.type().name() << any_cast<int *>(a);

    if(!strcmp(parsed_json["Patric"].type().name(), "i")){
        cout << any_cast<int>(parsed_json["Patric"]) ;//<< "    " << any_cast<int>(a);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "c")){
        cout << any_cast<char>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "d")){
        cout << any_cast<double>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "f")){
        cout << any_cast<float>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "Pc")){
        cout << any_cast<char *>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "Pi")){
        cout << any_cast<int *>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "Pd")){
        cout << any_cast<double *>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "Pf")){
        cout << any_cast<float *>(parsed_json["Patric"]);
    }
    cout << endl;
    //cout << parsed_json["Patrric"] << a.type().name();

    return 0;
}
