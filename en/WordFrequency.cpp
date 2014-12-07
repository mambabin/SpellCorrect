#include "WordFrequency.h"
#include "StringUtil.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>

using namespace std;
using namespace stringutil;

WordFrequency::WordFrequency(std::string filename, 
                             std::string stopFile,
                             std::string dictname)
	:filename_(std::move(filename)),
	 stopFile_(std::move(stopFile)),
     dictname_(std::move(dictname))
{	
}

void WordFrequency::readStopList()
{
	ifstream infile(stopFile_);
	if(!infile)
		throw runtime_error("stopList打开失败");

	string word;
    while(infile >> word)
        stopList_.insert(word);

    infile.close();
}

void WordFrequency::readWordFile()
{
	ifstream infile(filename_.c_str());
	if(!infile)
		throw runtime_error("word文件打开失败");

	words_.clear();
    string word;
    while(infile >> word)
    {
        erasePunct(word);
        if(isAllDigit(word))
        	continue;
        stringToLower(word);
        if(stopList_.count(word) == 0)
        	words_[word]++;
    }

    infile.close();
}

void WordFrequency::saveDict() const
{
    ofstream of(dictname_);
    if(!of)
        throw std::runtime_error("dict file  open failed.");
    for(auto it = words_.begin();
        it != words_.end();
        ++it)
    {
        of << it->first << " " << it->second << endl;
    }

    of.close();
}