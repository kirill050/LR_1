#include <iostream>
#include <any>
#include <map>
#include <cstring>
#include <fstream>

using namespace std;
class Json {
public:
    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string& s): json_string(s){}

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array(const string &str) const{
        if(str.find('[') != string::npos) return true;
        else return false;
    }
   	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object(const string &str) const{
        if(str.find('{') != string::npos) return true;
        else return false;
    }

    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::any& operator[](const std::string& key){
        if(_parsed_json[key].type() == typeid(string)){
            return _parsed_json[key];//any_cast<const std::string&>(_parsed_json[key]);
        }
        else if(_parsed_json[key].type() == typeid(double)){
            return _parsed_json[key];
        }
        else if(_parsed_json[key].type() == typeid(bool)){
            return _parsed_json[key];
        }
        else if(_parsed_json["Patric"].type() == typeid(void)){
            return _parsed_json[key];//return << any_cast<float>(_parsed_json["Patric"]);
        }
        else{
            throw string("This is array!!!");
        }
    }

    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::any& operator[](int index);

    std::any parse_object_get_value(std::string& s){
        string value;
        value.assign(s, s.find(":")+1, s.find(",")-1);

        s.erase(s.find(":"), s.find(",")+1);

        if(is_object(value)){

        }
        else if(is_array(value)){

        }
        return value;
    }
    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string& s){
        string str;
        str.assign(s, 1, s.length()-2);

        str.erase(0, str.find("\"")+1);
        string key = str.substr(0, str.find("\""));
        str.erase(0, str.find("\"")+1);
        //_parsed_json = ;

        return Json(str);
    }

    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string& path_to_file);

public:
    std::string json_string;
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
        //cout << word << endl;
        JSON_file.close();
    }
    json_string_holder = word;
}

int main()
{
    string JSON;
    make_string_from_json_file("JSON.txt", JSON);

    Json *F1 = new Json(JSON);
    string s = F1->json_string;
    Json a = Json::parse(s);
    cout << a.json_string << endl;

    //cout << "IS it an array? " << F1->is_array(F1->json_string);
    delete F1;

    //std::map <std::any, std::any> parsed_json;
    map <std::string, std::any> parsed_json;

    parsed_json["Patric"];
    /*parsed_json["Patrric"] = 5;
    parsed_json["Patrrrric"] = 5;
    parsed_json["Patrrrrrrrrric"] = 5;*/

    //int b = 65;
    //any a = &b;
    //cout << ""<<parsed_json["Patric"].type().name()<<"'"<< endl;// << any_cast<int *>(a);

    /*if(parsed_json["Patric"].type() == typeid(int)){
        cout << any_cast<int>(parsed_json["Patric"]) ;//<< "    " << any_cast<int>(a);
    }
    else if(parsed_json["Patric"].type() == typeid(double)){
        cout << any_cast<double>(parsed_json["Patric"]);
    }
    else if(parsed_json["Patric"].type() == typeid(float)){
        cout << any_cast<float>(parsed_json["Patric"]);
    }
    else if(parsed_json["Patric"].type() == typeid(char)){
        cout << any_cast<char>(parsed_json["Patric"]);
    }
    else if(parsed_json["Patric"].type() == typeid(string)){
        cout << any_cast<const std::string&>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "Pi")){
        cout << any_cast<int *>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "Pd")){
        cout << any_cast<double *>(parsed_json["Patric"]);
    }
    else if(!strcmp(parsed_json["Patric"].type().name(), "Pf")){
        cout << any_cast<float *>(parsed_json["Patric"]);
    }*/
    cout << endl;
    //cout << parsed_json["Patrric"] << a.type().name();
    return 0;
}
