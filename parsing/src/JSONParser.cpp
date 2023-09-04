#include <iostream>
#include <fstream>
#include "JSONParser.h"

template <typename T, typename U>
T JSONParser<T, U>::parseDocument(U fileName)
{
    std::ifstream fileIn(fileName);
    if (!fileIn.is_open())
    {
        throw InvalidFile();
    }
    rapidjson::Document document;
    std::string jsonBuffer((std::istreambuf_iterator<char>(fileIn)), std::istreambuf_iterator<char>());
    rapidjson::ParseResult parseResult = document.Parse(jsonBuffer.c_str());
    return document;
}
