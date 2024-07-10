#pragma once
#include <string>

enum class ErrorCode;
bool is_integer(double &a);
char seperate(std::string input, double &first, double &second);
ErrorCode process(std::string input, double* out);
