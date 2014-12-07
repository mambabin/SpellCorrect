#include "ChineseFrequency.h"
#include <stdexcept>
#include <muduo/base/Logging.h>
using namespace std;
using namespace CppJieba;

ChineseFrequency::ChineseFrequency(
                     std::string zhFilename,
                     std::string stopListZhFile,
                     std::string zhDictFile,
                     std::string jiebaDictPath,
                     std::string jiebaModelPath)
: zhFilename_(std::move(zhFilename)),
  stopListZhFile_(std::move(stopListZhFile)),
  zhDictFile_(std::move(zhDictFile)),
  jiebaDictPath_(std::move(jiebaDictPath)),
  jiebaModelPath_(std::move(jiebaModelPath)),
  segment_(jiebaDictPath_, jiebaModelPath_)
{
    LOG_INFO << "Jieba分词启动";
}

void ChineseFrequency::readStopList()
{
    ifstream infile(stopListZhFile_);
    if(!infile)
        throw runtime_error("stopList打开失败");

    string word;
    while(infile >> word)
        stopList_.insert(word);

    if(!infile.eof())
        throw runtime_error("error zh stopList file");

    infile.close();
} 
void ChineseFrequency::readWordFile()
{
    ifstream infile(zhFilename_);
    if(!infile)
        throw runtime_error("word文件打开失败");
    words_.clear();

    string line;
    vector<string> result; //存放分词结果
    while(getline(infile, line))
    {
        result.clear();
        segment_.cut(line, result);
        for(const string &s : result) //foreach
        {
            if(stopList_.count(s) == 0) //不是停用词
                words_[s]++;
        }
    }
    if(!infile.eof())
        throw runtime_error("error zh file");

    infile.close();
} 

void ChineseFrequency::saveDict() const
{
    ofstream of(zhDictFile_);
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