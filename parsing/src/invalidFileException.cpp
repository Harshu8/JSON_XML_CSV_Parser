#include "InvalidFileException.h"
 
std::string InvalidFile::what()
{
    return "Failed to open file! File is not there.\n";
}