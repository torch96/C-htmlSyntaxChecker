
#include <map>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include "htmltags.h"

namespace DSPROJ {


htmltags::htmltags() {
	htmlmap["!--"] = SELF_CLOSING;
	htmlmap["a"] = TAG;
	htmlmap["abbr"] = TAG;
	htmlmap["address"] = TAG;
	htmlmap["area"] = TAG;
	htmlmap["article"] = TAG;
	htmlmap["aside"] = TAG;
	htmlmap["audio"] = TAG;
	htmlmap["b"] = TAG;
	htmlmap["base"] = TAG;
	htmlmap["bdi"] = TAG;
	htmlmap["bdo"] = TAG;
	htmlmap["blockquote"] = TAG;
	htmlmap["body"] = TAG;
	htmlmap["br"] = SELF_CLOSING;
	htmlmap["button"] = TAG;
	htmlmap["canvas"] = TAG;
	htmlmap["caption"] = TAG;
	htmlmap["cite"] = TAG;
	htmlmap["code"] = TAG;
	htmlmap["col"] = TAG;
	htmlmap["colgroup"] = TAG;
	htmlmap["datalist"] = TAG;
	htmlmap["dd"] = TAG;
	htmlmap["del"] = TAG;
	htmlmap["details"] = TAG;
	htmlmap["dfn"] = TAG;
	htmlmap["dialog"] = TAG;
	htmlmap["div"] = TAG;
	htmlmap["dl"] = TAG;
	htmlmap["!doctype"] = SELF_CLOSING;
	htmlmap["dt"] = TAG;
	htmlmap["em"] = TAG;
	htmlmap["embed"] = TAG;
	htmlmap["fieldset"] = TAG;
	htmlmap["figcaption"] = TAG;
	htmlmap["figure"] = TAG;
	htmlmap["footer"] = TAG;
	htmlmap["form"] = TAG;
	htmlmap["h1"] = TAG;
	htmlmap["h2"] = TAG;
	htmlmap["h3"] = TAG;
	htmlmap["h4"] = TAG;
	htmlmap["h5"] = TAG;
	htmlmap["h6"] = TAG;
	htmlmap["head"] = TAG;
	htmlmap["header"] = TAG;
	htmlmap["hr"] = SELF_CLOSING;
	htmlmap["html"] = TAG;
	htmlmap["i"] = TAG;
	htmlmap["iframe"] = TAG;
	htmlmap["img"] = SELF_CLOSING;
	htmlmap["input"] = SELF_CLOSING;
	htmlmap["ins"] = TAG;
	htmlmap["kbd"] = TAG;
	htmlmap["keygen"] = SELF_CLOSING;
	htmlmap["label"] = TAG;
	htmlmap["legend"] = TAG;
	htmlmap["li"] = TAG;
	htmlmap["link"] = SELF_CLOSING;
	htmlmap["main"] = TAG;
	htmlmap["map"] = TAG;
	htmlmap["mark"] = TAG;
	htmlmap["menu"] = TAG;
	htmlmap["menuitem"] = TAG;
	htmlmap["meta"] = SELF_CLOSING;
	htmlmap["meter"] = TAG;
	htmlmap["nav"] = TAG;
	htmlmap["noscript"] = TAG;
	htmlmap["object"] = TAG;
	htmlmap["ol"] = TAG;
	htmlmap["optgroup"] = TAG;
	htmlmap["option"] = TAG;
	htmlmap["output"] = TAG;
	htmlmap["p"] = TAG;
	htmlmap["param"] = SELF_CLOSING;
	htmlmap["pre"] = TAG;
	htmlmap["progress"] = TAG;
	htmlmap["q"] = TAG;
	htmlmap["rp"] = TAG;
	htmlmap["rt"] = TAG;
	htmlmap["ruby"] = TAG;
	htmlmap["s"] = TAG;
	htmlmap["samp"] = TAG;
	htmlmap["script"] = TAG;
	htmlmap["section"] = TAG;
	htmlmap["select"] = TAG;
	htmlmap["small"] = TAG;
	htmlmap["source"] = SELF_CLOSING;
	htmlmap["span"] = TAG;
	htmlmap["strong"] = TAG;
	htmlmap["style"] = TAG;
	htmlmap["sub"] = TAG;
	htmlmap["summary"] = TAG;
	htmlmap["sup"] = TAG;
	htmlmap["table"] = TAG;
	htmlmap["tbody"] = TAG;
	htmlmap["td"] = TAG;
	htmlmap["textarea"] = TAG;
	htmlmap["tfoot"] = TAG;
	htmlmap["th"] = TAG;
	htmlmap["thead"] = TAG;
	htmlmap["time"] = TAG;
	htmlmap["title"] = TAG;
	htmlmap["tr"] = TAG;
	htmlmap["track"] = SELF_CLOSING;
	htmlmap["u"] = TAG;
	htmlmap["ul"] = TAG;
	htmlmap["var"] = TAG;
	htmlmap["video"] = TAG;
	htmlmap["wbr"] = SELF_CLOSING;
}

bool htmltags::tokenizeHTMLFile(std::string& filename) {
	std::string s;
	std::ifstream fin;


	fin.open( filename.c_str(), std::ifstream::in);
	if ( !fin.fail() ) {
		while ( fin ) {
			s = "";
			while ( fin && fin.peek() != '<' )
				fin.ignore();

			if ( fin && fin.peek() == '<' ) {
				fin.ignore();
				//Possible HTML Tagname, tagnames end in >, SPACE, [, or newline (carriage return too)
				while ( fin && fin.peek() != '>' && fin.peek() != ' ' && fin.peek() != '[' && fin.peek() != '\n' && fin.peek() != '\r' )
					s += fin.get();

				//Got tag name
				tokens.push(s);

				while ( fin && fin.peek() != '>' )
					fin.ignore();
			}
		}
	} else {
		throw std::runtime_error("Unable to open/read file!");
	}
	fin.close();
	return true;
}

bool htmltags::tokenizeHTMLFile( char * filename ) {
	std::string s(filename);
	return tokenizeHTMLFile( s );
}

std::string htmltags::getNextToken() {
	if ( !tokens.empty() ) {
		std::string s = tokens.front();
		tokens.pop();
		return s;
	} else {
		throw std::runtime_error("Tokens underflow!");
	}

}

bool htmltags::hasTokens() const {
	return !tokens.empty();
}

unsigned short htmltags::isTag( std::string& tag ) {
	std::map<std::string,unsigned short>::iterator it;
	bool closing = false;
	unsigned int tagType;

	if ( tag.empty() )
		return INVALID;

	stringToLower( tag );

	if ( tag.at(0) == '/' ) {
		closing = true;
		tag = tag.substr(1);
	}

	it = htmlmap.find(tag);
	if ( it != htmlmap.end() ) {
		tagType =htmlmap[tag];
		if ( tagType == TAG && !closing )
			return OPENING_TAG;
		else if ( tagType == SELF_CLOSING && !closing )
			return SELF_CLOSING;
		else if ( tagType == TAG && closing )
			return CLOSING_TAG;
		else
			return INVALID;
	}

	return INVALID;

}

void htmltags::stringToLower( std::string& s ) {

	std::transform(s.begin(), s.end(), s.begin(), ::tolower);


}
}




