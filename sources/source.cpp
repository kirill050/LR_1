#include "json.hpp"

int main ()
{
    Json object = Json::parseFile("JSON.txt");
    return 0;
}
