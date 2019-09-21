#include <iostream>
#include <any>
#include <map>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#define NUM_ST 48
#define NUM_FIN 57

using namespace std;
class Json {
public:
    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string& s): json_string(s){}

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array(const string &str) const{
        //if(str.find('[') != string::npos) return true;
        if(str[0] == '[') return true;
        else return false;
    }
   	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object(const string &str) const{
        //if(str.find('{') != string::npos) return true;
        if(str[0] == '{') return true;
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

private:
    std::string get_key(std::string& str){
        cout << "get key: " << endl;
        if(str.find("\"") != string::npos){
            str.erase(0, str.find("\"")+1);
            //cout << "\t1 str: " << str << endl;
            if(str.find("\"") != string::npos){
                string key = str.substr(0, str.find("\""));
                //cout << "\t2 key: " << key << endl;
                str.erase(0, str.find("\"")+1);
                cout << key;
                return key;
            }
            else throw string("No keys!");
        }
        else throw string("No keys!");
    }
public:
    std::any parse_object_get_value(std::string& s){
        if((!s.length()) || (s.find(":") == string::npos)) throw string("No objects value for the last key!");
        any value;
        string pre_value;
        if(s.find(",") != string::npos){
            if(s.find("{") != string::npos){
                if(s.find("{") < s.find(",")){
                    if(s.find("}") == string::npos) throw string("Bad object!!!");
                    pre_value.assign(s, s.find(":")+2, s.find("}")-2);
                    s.erase(0, s.find("}")+1);
                }
                else{
                pre_value.assign(s, s.find(":")+2, s.find(",")-3);
                s.erase(0, s.find(",")+1);//s.erase(s.find(":"), s.find(",")+1);
            }
            }
            else{
                pre_value.assign(s, s.find(":")+2, s.find(",")-3);
                s.erase(0, s.find(",")+1);//s.erase(s.find(":"), s.find(",")+1);
            }
        }
        else{
            pre_value = s;
            pre_value.erase(0, pre_value.find(":")+2);
            s.erase(s.find(":"), s.length()-1);
        }

        if(is_object(pre_value)){
            pre_value.assign(pre_value, pre_value.find("\""), pre_value.length()-2);
            while(pre_value.length()>5){
                try{
                    string key = get_key(pre_value);
                    //cout << endl << "pre:" << pre_value << ";" << endl;
                    //cout << "{" << any_cast<string>(parse_object_get_value(pre_value)) << "}" << endl; exit(213);
                    string find_here_a_value;
                    //find_here_a_value.assign(pre_value, );
                    map <string, any> MAP = {{key, parse_object_get_value(pre_value)}};
                    //cout << key << " : " << any_cast<string>(MAP[key]) << ";" << endl;
                    value = MAP;
                }
                catch(string Error){
                    cout << endl << "Error occured: " << Error << endl;
                    if(Error == "No keys!") { value = ""; return value;}
                    else if(Error == "No objects value for the last key!") { value = ""; return value;}
                }
            }
        }
        else if(is_array(pre_value)){

        }
        else if(pre_value.find("\"") != string::npos){
            pre_value.assign(pre_value, 1, pre_value.length()-2);
            value = pre_value;
            cout << "\"" << pre_value << "\"" << endl;
        }
        else if((pre_value[0]>=NUM_ST) && (pre_value[pre_value.length()-1]<=NUM_FIN)){
            value = atof(pre_value.c_str());
            cout << "<" << any_cast<double>(value) << ">" << endl;
        }
        else if((pre_value == "true") || (pre_value == "false")){
            if(pre_value == "true") value = true;
            else value = false;
            cout << "{" << any_cast<bool>(value) << "}" << endl;
        }

        return value;
    }
    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string& s){
        string str;
        Json JSON(s);
        str.assign(s, 1, s.length()-2);

        while(str.length()>5){
            //str.erase(0, str.find("\"")+1);
            try{
                string key = JSON.get_key(str);
                JSON._parsed_json[key] = JSON.parse_object_get_value(str);
            }
            catch(string Error){
                if(Error == "No keys!") break;
            }
            //str.erase(0, str.find("\"")+1);
        }
        return JSON;
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
    make_string_from_json_file("json2.txt", JSON);

    Json *F1 = new Json(JSON);
    string s = F1->json_string;
    Json a = Json::parse(s);
    //cout << a.json_string << endl;

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
