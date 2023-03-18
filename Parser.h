/*
 * Parser.h
 *
 *  Created on: Oct 26, 2020
 *      Author: user
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "MyFile.h"

class Parser {
public:
	Parser();
	virtual ~Parser();

	/* checks how many white spaces the string has after trimming*/
	int checkDelim(string& str);

	void parseWithOne(string& str,string& command, string& name);

	void parseWithTwo(string& str, string& command, string&, string& rec);

	/* removes all the white spaces at the beggining of the string*/
	void trim(string& str);
};

#endif /* PARSER_H_ */
