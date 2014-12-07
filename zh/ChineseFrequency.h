#ifndef CHINESE_FREQUENCY_H
#define CHINESE_FREQUENCY_H

#include <boost/noncopyable.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "../include/libjieba/MixSegment.hpp"

class ChineseFrequency : boost::noncopyable
{
public:
    ChineseFrequency(std::string zhFilename,
                     std::string stopListZhFile,
                     std::string zhDictFile,
                     std::string jiebaDictPath,
                     std::string jiebaModelPath);

    void readStopList(); //读取停用词
    void readWordFile(); //读取中文语料

    void saveDict() const; //保存数据到磁盘


private:
    std::string zhFilename_;
    std::string stopListZhFile_;
    std::string zhDictFile_; //中文词典

    //结巴分词使用
    std::string jiebaDictPath_;
    std::string jiebaModelPath_;

    CppJieba::MixSegment segment_; //结巴分词

    std::unordered_map<std::string, int> words_;
    std::unordered_set<std::string> stopList_;
};


#endif //CHINESE_FREQUENCY_H