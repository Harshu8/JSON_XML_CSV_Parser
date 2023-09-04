#include "InvalidInputException.h"

std::string InvalidInput::what()
{
    return "Invalid input. Try again\n";
}