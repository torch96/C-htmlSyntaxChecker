


#ifndef HTMLTAGS_H_
#define HTMLTAGS_H_

#include <map>
#include <queue>
#include <cstring>
#include <string>

namespace DSPROJ {

class htmltags {
public:
	static const unsigned short INVALID = 0;
	static const unsigned short OPENING_TAG = 2;
	static const unsigned short SELF_CLOSING = 3;
	static const unsigned short CLOSING_TAG = 4;
	htmltags();
	~htmltags() { }
	bool tokenizeHTMLFile( std::string& );
	bool tokenizeHTMLFile( char * );
	std::string getNextToken();
	bool hasTokens() const;
	unsigned short isTag( std::string& );
	void stringToLower( std::string& );
private:
	static const unsigned short TAG = 1;
	std::queue<std::string> tokens;
	std::map<std::string, unsigned short> htmlmap;
};

} 

#endif 



