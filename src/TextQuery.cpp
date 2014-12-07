#include "TextQuery.h"
#include "StringUtil.h"
#include <fstream>
#include <functional>
#include <vector>
#include <queue>
#include <limits>  //ignore illeagl input
#include <muduo/base/Logging.h>

using namespace muduo;
using namespace std;
using namespace std::placeholders;

namespace
{
struct Word
{
public:
    Word(std::string word,
         int editDistance,
         int frequency)
    : word_(std::move(word)),
      editDistance_(editDistance),
      frequency_(frequency)
    {
    }

public:
    std::string word_;
    int editDistance_;
    int frequency_;
};

bool operator< (const Word &a, const Word &b)
{
    if(a.editDistance_ != b.editDistance_)
        return a.editDistance_ > b.editDistance_;
    return a.frequency_ < b.frequency_;
}

}


TextQuery::TextQuery(std::string enDict, 
                     std::string zhDict,
                     const std::string &host,
                     uint16_t port)
: enDictName_(std::move(enDict)),
  zhDictName_(std::move(zhDict)),
  client_(host, port)
{
    readEnDict();
    readZhDict();
}


std::string TextQuery::queryWord(const std::string &word) const
{
    //先查看缓存
    std::pair<std::string, bool> res = client_.getValueByKey(word);
    if(res.second)
        return res.first;
    else
    {
        std::string s = queryWordInDict(word);
        client_.setKeyValue(word, s);
        return s;
    }
}


std::string TextQuery::queryWordInDict(const std::string &word) const
{
    priority_queue<Word, vector<Word>, less<Word> > q;

    LOG_DEBUG << "query Word : " << word;

    InvertedIndex::WordSet words = index_.getWords(word);

    bool isASCII = stringutil::isASCIIString(word);

    for(const auto &pa : words)
    {
        int editDistance;
        if(isASCII)
            editDistance = stringutil::editDistanceChar(word, pa.first);
        else
            editDistance = stringutil::editDistance(word, pa.first);
        if(static_cast<double>(editDistance) / word.size() < 0.5)
            q.push(Word(pa.first, editDistance, pa.second));
    }

    if(q.empty())
        return "";
    else
        return q.top().word_;
}


void TextQuery::readEnDict()
{
    std::ifstream infile(enDictName_);
    if(!infile)
    {
        LOG_FATAL << "open En file error";
    }

    LOG_INFO << "Begin read En Dict : " << enDictName_;

    std::string word;
    int count;
    while(infile >> word >> count)
    {
        //处理错误
        if(infile.fail())
        {
            LOG_WARN << "En File format error in :" << enDictName_;
            infile.clear();  //重置状态
            infile.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');    //忽略错误输入
        }

        index_.addItem(make_pair(word, count));

    }

    LOG_INFO << "read En Dict Finish";

    infile.close();
}

void TextQuery::readZhDict()
{
    std::ifstream infile(zhDictName_);
    if(!infile)
    {
        LOG_FATAL << "open Zh file error";
    }

    LOG_INFO << "Begin read Zh Dict :" << zhDictName_;

    std::string word;
    int count;
    while(infile >> word >> count, !infile.eof())
    {
        //处理格式错误
        if(infile.fail())
        {
            LOG_WARN << "Zh File format error in :" << enDictName_;
            infile.clear();  //重置状态
            infile.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');    //忽略错误输入
        }
        index_.addItem(make_pair(word, count));
    }

    LOG_INFO << "read Zh Dict Finish";

    infile.close();
}

