#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif /* __STDC_FORMAT_MACROS */
#include <inttypes.h>
#include "WordFrequency.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdexcept>
#include <muduo/base/Logging.h>

using namespace std;

int64_t getUTime();

int main(int argc, char const *argv[])
{

	WordFrequency wf("en.txt", "stopList.txt", "../dict/en.dict");

    LOG_INFO << "begin reading file ";

	int64_t startTime = getUTime();

	wf.readStopList();
	wf.readWordFile();

    wf.saveDict();

	int64_t endTime = getUTime();

    LOG_INFO << "建立英文词典花费:  " << (endTime - startTime) / 1000 << " ms";
}


int64_t getUTime()
{
    struct timeval tv;
    ::memset(&tv, 0, sizeof tv);
    if(::gettimeofday(&tv, NULL) == -1)
    {
        throw runtime_error("gettimeofday");
    }
    int64_t t = tv.tv_usec;
    t += tv.tv_sec * 1000 * 1000;
    return t;
}
