#include <iostream>
#include <fstream>
#include "CSVParser.h"

template <typename T, typename U>
T CSVParser<T, U>::parseDocument(U fileName)
{
    std::ifstream fileIn(fileName);
    if (!fileIn.is_open())
    {
        throw InvalidFile();
    }
    rapidcsv::Document document(fileName);
    return document;
}