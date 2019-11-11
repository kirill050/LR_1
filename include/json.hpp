// Copyright 2019 Kirill Tikhonov  <kirilltikhonov050@gmail.com>

#ifndef INCLUDE_JSON_HPP_
#define INCLUDE_JSON_HPP_

#include <iostream>
#include <any>
#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#define NUM_ST 48
#define NUM_FIN 57

class Json {
public:
    // Constructor from a string containing Json data.
    Json(const std::string& s);

    // The method returns true if this instance contains a JSON array. Otherwise false.
    bool is_array(const string &str) const;
   	// The method returns true if this instance contains a JSON object. Otherwise false.
    bool is_object(const string &str) const;

    // The method returns the value by key if the instance is a JSON object.
    // The value can be one of the following types: Json, std::string, double, bool, or empty.
    // If the instance is a JSON array, an exception is thrown.
    std::any& operator[](const std::string& key);

    // The method returns a value by index if the instance is a JSON array.
    // The value can be one of the following types: Json, std::string, double, bool, or empty.
    // If the instance is a JSON object, an exception is thrown.
    std::any& operator[](int index);

private:
    std::string make_it_without_tabs (std::string& str);
    std::string get_key (std::string& str);
public:
    std::any parse_object_get_value (std::string& s);

    // The method returns a Json class object from a string containing Json data.
    static Json parse(const std::string& s);

    // The method returns a Json class object from a file containing JSON data in text format.
    static Json parseFile(const std::string& path_to_file);
public:
    std::string json_string;
    std::map <std::string, any> _parsed_json;
};

#endif // INCLUDE_JSON_HPP_
