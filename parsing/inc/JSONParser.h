#pragma once
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "Parser.h"

template <typename T, typename U>
class JSONParser : public Parser<T, U>
{
public:
    T parseDocument(U);
};