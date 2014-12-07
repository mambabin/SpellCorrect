#include "StringUtil.h"
#include <ctype.h>

using namespace std;

namespace stringutil
{

void erasePunct(string &s)
{
	string::iterator it = s.begin();
    while(it != s.end())
    {
        if(ispunct(*it))
            it = s.erase(it);
        else
            ++it;
    }
}

void stringToLower(string &s)
{
	for(string::iterator it = s.begin();
        it != s.end();
        ++it)
    {
        if(isupper(*it))
            *it = tolower(*it);
    }
}

bool isAllDigit(const std::string &s)
{
	for(string::const_iterator it = s.begin();
		it != s.end();
		++it)
	{
		if(!isdigit(*it))
			return false;
	}

	return true;
}

}

