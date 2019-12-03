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
    // ����������� �� ������, ���������� Json-������.
    Json(const std::string& s);

    // ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
    bool is_array(const string &str) const;
   	// ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
    bool is_object(const string &str) const;

    // ����� ���������� �������� �� ����� key, ���� ��������� �������� JSON-��������.
    // �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
    // ���� ��������� �������� JSON-��������, ������������ ����������.
    std::any& operator[](const std::string& key);

    // ����� ���������� �������� �� ������� index, ���� ��������� �������� JSON-��������.
    // �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
    // ���� ��������� �������� JSON-��������, ������������ ����������.
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

    // ����� ���������� ������� ������ Json �� �����, ����������� Json-������ � ��������� �������.
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
