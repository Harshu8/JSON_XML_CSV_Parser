#pragma once
#include <iostream>

class InvalidInput : public std::exception
{
public:
    std::string what();
};