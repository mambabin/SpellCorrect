#include "InvertedIndex.h"
#include "StringUtil.h"
using namespace std;

void InvertedIndex::addItem(WordItem item)
{
    // 加藤凯 20 
    //1.解析字符串
    vector<uint32_t> chars;
    stringutil::parseUTF8String(item.first, chars); 
    //2.依次加入 加 藤 凯
    for(uint32_t t : chars)
    {
        index_[t].insert(std::move(item));
    }
}

InvertedIndex::WordSet InvertedIndex::getWords(const std::string &s) const
{
    WordSet result;

    //1.解析字符串
    vector<uint32_t> chars;
    stringutil::parseUTF8String(s, chars);
    //2.依次取出单词的set 然后合并
    for(uint32_t t : chars)
    {
        Index::const_iterator it = index_.find(t);
        if(it != index_.end())
        {
            //uint32_t -> WordSet
            const WordSet &words = it->second;
            result.insert(words.begin(), words.end());
        }
    }

    return result;
}

