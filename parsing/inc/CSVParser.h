#pragma once
#include "rapidcsv.h"
#include "Parser.h"

template <typename T, typename U>
class CSVParser : public Parser<T, U>
{
public:
    T parseDocument(U);
};