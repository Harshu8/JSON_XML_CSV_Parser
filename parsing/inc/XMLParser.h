#pragma once
#include "rapidxml.hpp"
#include "Parser.h"

template <typename T, typename U>
class XMLParser : public Parser<T, U>
{
public:
    T parseDocument(U);
};