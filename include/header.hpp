// Copyright 2019 Kirill Tikhonov <kirilltikhonov050@gmail.com>
#pragma once

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
    Json(const std::string& s);

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array(const string &str) const;
   	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object(const string &str) const;

    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::any& operator[](const std::string& key);

    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::any& operator[](int index);

private:
    std::string make_it_without_tabs(std::string& str);

    std::string get_key(std::string& str);
public:
    std::any parse_object_get_value(std::string& s);

    static Json parse(const std::string& s){
        string str;
        Json JSON(s);
        str.assign(s, 1, s.length()-2);

        while(str.length()>5){
            try{
                string key = JSON.get_key(str);
                JSON._parsed_json[key] = JSON.parse_object_get_value(str);
                //cout << endl;
            }
            catch(string Error){
                //cout << endl << "Error occured: " << Error << endl;
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
