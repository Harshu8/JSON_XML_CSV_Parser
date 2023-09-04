#pragma once
#include "InvalidFileException.h"

template <typename T, typename U>
class Parser
{
    virtual T parseDocument(U)=0;
};