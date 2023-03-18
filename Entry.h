/*
 * Entry.h
 *
 *  Created on: Nov 21, 2020
 *      Author: user
 */

#ifndef ENTRY_H_
#define ENTRY_H_
#include "System.h"
#include "Parser.h"

class Entry {
public:
	Entry();
	virtual ~Entry();

	bool entryMain(string& usernamecurrent);



	//***********************************
	//checks for the user name and password
	bool auth(string& pass);
private :
	Parser parse;
	string username;
	string password;

};

#endif /* ENTRY_H_ */
