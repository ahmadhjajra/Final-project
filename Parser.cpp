/*
 * Parser.cpp
 *
 *  Created on: Oct 26, 2020
 *      Author: user
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

void Parser::trim(string& str)
{
   size_t p = str.find_first_not_of(" ");
   str.erase(0, p);
   p = str.find_first_not_of("\t");
   str.erase(0,p);

   p = str.find_last_not_of(" ");
   if (string::npos != p)
      str.erase(p+1);
}

int Parser::checkDelim(string& str){
	int check =0;
	for (auto it = str.cbegin() ; it != str.cend(); ++it) {
			if(*it == ' '){
				check++;
			}
	}
	return check;
}

void Parser::parseWithOne(string& str,string& command, string& name){
	size_t pos = 0;
	std::string delimiter = " ";
	while ((pos = str.find(delimiter)) != std::string::npos) {
			command = str.substr(0,pos);
			str.erase(0,pos + delimiter.length());
	}
	name = str;
}

void Parser::parseWithTwo(string& str, string& command, string& name, string& rec){
	size_t pos = 0;
	bool flag = false;
	std::string delimiter = " ";
	while ((pos = str.find(delimiter)) != std::string::npos) {
			if(flag){
				name = str.substr(0,pos);
			}
			if(!flag){
				command = str.substr(0,pos);
				flag = true;
			}
			str.erase(0,pos + delimiter.length());
	}
	rec = str;
}
