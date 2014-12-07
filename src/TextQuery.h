#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <boost/noncopyable.hpp>
#include <unordered_map>
#include <string>
#include "RedisClient.h"
#include "InvertedIndex.h"

class TextQuery : boost::noncopyable
{
public:
    TextQuery(std::string enDict, 
              std::string zhDoct,
              const std::string &host,
              uint16_t port); 
    std::string queryWord(const std::string &word) const;
private:
    void readEnDict(); //读取英文词典
    void readZhDict(); //读取中文词典

    std::string queryWordInDict(const std::string &word) const; //执行真正的查询

    std::string enDictName_;  //英文词典文件
    std::string zhDictName_;  //中文词典文件
    //std::unordered_map<std::string, int> dict_; //英文词典

    InvertedIndex index_;  //倒排索引

    RedisClient client_; //Redis
};

#endif //TEXT_QUERY_H