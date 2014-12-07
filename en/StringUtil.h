#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <string>

namespace stringutil
{

void erasePunct(std::string &s);
void stringToLower(std::string &s);
bool isAllDigit(const std::string &s);

}

#endif  /* STRING_UTIL_H_ */