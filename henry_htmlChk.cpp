
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stack>
//#include "stack.h"
//#include "linkedlist.h"
#include <list>

#include "htmltags.h"

using namespace DSPROJ;

//Precondition: The file is valid
//postcondtion: The file is opened
void openfile(std::ifstream& f,const char file[] );

//Precondition: the file is not at the end.
//postcondtion: returns a tag.
std::string getTag(std::istream& f);

//precondtion:The list is not empty
//postcontion:The list is sorted and duplicates are removed
void removeDups(std::list<std::string> &q);



int main(int argc, char *argv[]) {


		std::ifstream htmlfile;
		std::string tag;
		unsigned short  tagValue = 0;
		htmltags tagMap;

		std::stack<std::string> tagStack;
		std::list<std::string>tags, noMatch,uniqeTags;
		std::string temp;

		//Checks if file is valid and opens it
		openfile(htmlfile, argv[1]);

		//adding tags to a linked list
		while(htmlfile && htmlfile.peek() != EOF){
			tag	= getTag(htmlfile);
			std::cout<<tag<<" ";
			tags.push_back(tag);
		}
		htmlfile.close();

		//iterates through the list adding valid tags to the Stack.
		for (std::list<std::string>::iterator it=tags.begin(); it!=tags.end(); ++it){
				tag = *it;
				tagValue = tagMap.isTag(tag);
				 if(tagValue == tagMap.OPENING_TAG){
					std::cout<<"Tag "<< tag<<" is pushed to the top of the stack"<<std::endl;

					 tagStack.push(tag);
				 }else if(tagValue == tagMap.SELF_CLOSING){
					 uniqeTags.push_back(tag);

				 }
				 else if(tagValue == tagMap.CLOSING_TAG){

					 if(!tagStack.empty()){
						 temp = tagStack.top();
						 if(temp == tag){
							 std::cout<<"Tag " << tag << " matches the top of the stack"<<std::endl;
							 tagStack.pop();
						 }else{
							 std::cout<<"The closing tag "<< tag << " doesn't match the tag on the top of the stack "<<tagStack.top()<<"." <<std::endl;
							 noMatch.push_back(tag);


						 }
					 }else{
						 std::cout<<"The stack is empty and it wasn't  added to the stack."<<std::endl;
					 }

				 }

			}

			std::cout << "\nProccesing is complete. ";
			//Check if the stack is empty
			if(!tagStack.empty()){
				std::cout<<"These unmatched tags remain on the stack:[";
				while(!tagStack.empty() ){
					std::cout<<tagStack.top()<<" ";
					tagStack.pop();
				}
				std::cout<<"]"<<std::endl;
			}else{
				std::cout<<"No mismatched tags were found."<<std::endl;
			}


			removeDups(tags);
			//checks if the self closing list is empty and outputs list if its not empty.
			if(!uniqeTags.empty()){
				std::cout<<"\nUnique tags In sorted order: ";
				for (std::list<std::string>::iterator it=tags.begin(); it!=tags.end(); ++it){
					std::cout<<*it << " ";
				}
			}else{
				std::cout<<"\nNo unique tags found.";
			}






	return 0;
}

//Precondition: The file is valid
//postcondtion: The file is opened
void openfile(std::ifstream& f, const char file[]) {
	f.open(file);
	if ( f.fail() ) {
			std::cerr << "Could not open input file" << std::endl;
			std::exit(1);
	}
}
//Precondition: the file is not at the end.
//postcondtion: returns a tag.
std::string getTag(std::istream& f){

	char symbol;
	std::string tag;
	//chekck
	while((f && f.peek() != '>') && (f && f.peek() != EOF)){

				 if ((strchr("<", f.peek( )) != NULL))
				 {
					 f.ignore();
					 while((f && f.peek() != ' ') && ( f.peek() != '>') && ( f.peek() != '\n')){
						 f >> symbol;
						 tag += symbol;
					 }
				 }else
					f.ignore();
	}
	f.ignore();
	return tag;


}
//precondtion:The list is not empty
//postcontion:The list is sorted and duplicates are removed
void removeDups(std::list<std::string> &q){

	for (std::list<std::string>::iterator it=q.begin(); it!=q.end(); ++it){
		std::string &tag = *it;
		if ( tag.at(0) == '/' ) {

				tag = tag.substr(1);
			}
	}

	q.sort();
	q.unique();





}
