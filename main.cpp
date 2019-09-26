#include <iostream>
#include <any>
#include <map>
#include <vector>
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
        if(str[0] == '[') return true;
        else return false;
    }
   	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object(const string &str) const{
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
    std::any& operator[](int index){
        auto it = _parsed_json.begin();
        advance(it, index);
        return it->second;
    }

private:
    std::string make_it_without_tabs(std::string& str){
        while ((str[0] == ' ') ||  (str[0] == '\n') || (str[0] == '\t')){
            str.assign(str, 1, str.length()-1);
        }
        string make_some_more_style_to_be_used_in_parse_obj_func(": ");
        make_some_more_style_to_be_used_in_parse_obj_func += str;
        str = make_some_more_style_to_be_used_in_parse_obj_func;
        return str;
    }
    std::string get_key(std::string& str){
        cout << "get key: ";
        if(str.find("\"") != string::npos){
            str.erase(0, str.find("\"")+1);
            if(str.find("\"") != string::npos){
                string key = str.substr(0, str.find("\""));
                str.erase(0, str.find("\"")+1);
                cout << key << " ";
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
                else if(s.find("[") != string::npos){
                    if(s.find("[") < s.find(",")){
                        if(s.find("]") == string::npos) throw string("Bad array!!!");
                        pre_value.assign(s, s.find(":")+2, s.find("]")-2);
                        s.erase(0, s.find("]")+1);
                    }
                    else{
                    pre_value.assign(s, s.find(":")+2, s.find(",")-3);
                    s.erase(0, s.find(",")+1);
                    }
                }
                else{
                pre_value.assign(s, s.find(":")+2, s.find(",")-3);
                s.erase(0, s.find(",")+1);
                }
            }
            else if(s.find("[") != string::npos){
                if(s.find("[") < s.find(",")){
                    if(s.find("]") == string::npos) throw string("Bad array!!!");
                    pre_value.assign(s, s.find(":")+2, s.find("]")-2);
                    s.erase(0, s.find("]")+1);
                }
                else{
                pre_value.assign(s, s.find(":")+2, s.find(",")-3);
                s.erase(0, s.find(",")+1);
                }
            }
            else{
                pre_value.assign(s, s.find(":")+2, s.find(",")-3);
                s.erase(0, s.find(",")+1);
            }
        }
        else{
            pre_value = s;
            pre_value.erase(0, pre_value.find(":")+2);
            s = "";
        }

        if(is_object(pre_value)){
            pre_value.assign(pre_value, pre_value.find("\""), pre_value.length()-2);
            while(pre_value.length()>5){
                try{
                    string key = get_key(pre_value);
                    string find_here_a_value;

                    map <string, any> MAP = {{key, parse_object_get_value(pre_value)}};
                    value = MAP;
                }
                catch(string Error){
                    cout << endl << "Error occured: " << Error << endl;
                    if(Error == "No keys!") { value = -1; return value;}
                    else if(Error == "No objects value for the last key!") { value = -1; return value;}
                }
                catch(...){
                    cout << endl << "Error occured: "; exit(-12);
                }
            }
        }
        else if(is_array(pre_value)){
            pre_value.assign(pre_value, pre_value.find("[")+1, pre_value.rfind('\n')-1);

            std::vector <std::any> Array;

            cout << "=[";
            while (pre_value.find(",") != string::npos){
                string some_other_string;
                some_other_string.assign(pre_value, 0, pre_value.find(","));
                pre_value.assign(pre_value, pre_value.find(",")+1, pre_value.length()-1);

                some_other_string = make_it_without_tabs(some_other_string);

                Array.push_back(parse_object_get_value(some_other_string));
                cout << ", ";
            }
            pre_value = make_it_without_tabs(pre_value);
            Array.push_back(parse_object_get_value(pre_value));

            cout << "]";
            value = Array;
        }
        else if(pre_value.find("\"") != string::npos){
            pre_value.assign(pre_value, pre_value.find("\"")+1, pre_value.rfind("\"")-1);
            value = pre_value;
            cout << "\"" << pre_value << "\"";
        }
        else if((pre_value[0]>=NUM_ST) && (pre_value[pre_value.length()-1]<=NUM_FIN)){
            value = atof(pre_value.c_str());
            cout << "<" << any_cast<double>(value) << ">";
        }
        else if((pre_value == "true") || (pre_value == "false")){
            if(pre_value == "true") value = true;
            else value = false;
            cout << "{" << any_cast<bool>(value) << "}";
        }

        return value;
    }
    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string& s){
        string str;
        Json JSON(s);
        str.assign(s, 1, s.length()-2);

        while(str.length()>5){
            try{
                string key = JSON.get_key(str);
                JSON._parsed_json[key] = JSON.parse_object_get_value(str);
                cout << endl;
            }
            catch(string Error){
                cout << endl << "Error occured: " << Error << endl;
                break;
            }
        }
        return JSON;
    }

    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string& path_to_file){
        ifstream JSON_file(path_to_file);
        string s;
        Json JSON(s);
        char ch;
        if(JSON_file.is_open()){
            while (true)
            {
                JSON_file.get(ch);
                if (JSON_file.eof()) break;
                JSON.json_string.append(1, ch);
            }
            JSON_file.close();
        }
        JSON = Json::parse(JSON.json_string);
        return JSON;
    }

public:
    std::string json_string;
    std::map <std::string, std::any> _parsed_json;
};


int main()
{
    Json F1 = Json::parseFile("JSON.txt");
    return 0;
}
