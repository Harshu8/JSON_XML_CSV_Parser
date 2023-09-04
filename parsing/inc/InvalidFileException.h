#pragma once
#include <iostream>

class InvalidFile : public std::exception
{
public:
    std::string what();
};