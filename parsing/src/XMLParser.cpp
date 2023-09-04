#include <iostream>
#include <fstream>
#include <vector>
#include "XMLParser.h"

template <typename T, typename U>
T XMLParser<T, U>::parseDocument(U fileName)
{
    std::ifstream fileIn(fileName);
    if (!fileIn.is_open())
    {
        throw InvalidFile();
    }
    rapidxml::xml_document<> document;
    rapidxml::xml_node<> *rootNode = NULL;
    std::vector<char> buffer((std::istreambuf_iterator<char>(fileIn)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    document.parse<0>(&buffer[0]);
    rootNode = document.first_node("MyStudentsData");
    return rootNode;
}