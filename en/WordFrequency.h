#ifndef WORD_FREQUENCY_H
#define WORD_FREQUENCY_H

#include <boost/noncopyable.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class WordFrequency : boost::noncopyable
{
public:
	WordFrequency(std::string filename, 
				  std::string stopFile,
				  std::string dictname);

	void readStopList(); //读取停用词
	void readWordFile(); //读取英文语料

	void saveDict() const;

	// void copyWordsToVector();
	// void sortWordsByFrequency();
	// void printWordFrequency() const;

private:

	typedef std::unordered_map<std::string, int>::iterator WordIt;
	typedef std::unordered_map<std::string, int>::const_iterator WordKIt;

	std::string filename_; //语料库名字
	std::string stopFile_; //停用词文件
	std::string dictname_;  //英文词典

	std::unordered_map<std::string, int> words_;
	std::unordered_set<std::string> stopList_;

	//std::vector<std::pair<std::string, int> > sortWords_;
};


#endif /* WORD_FREQUENCY_H */