/*
 * MyFile.h
 *
 *  Created on: Oct 23, 2020
 *      Author: user
 */

#ifndef MYFILE_H_
#define MYFILE_H_
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class MyFile {
public:
	//big three
	MyFile();
	virtual ~MyFile();
	MyFile(const MyFile& file);
	MyFile& operator=(const MyFile& file);
	MyFile& operator=(const string name);

	//operator == to check if the names are equal
	bool operator==(const string name);
	//operator!= to check if the names are not equal
	bool operator!=(string name);

	int operator[](const int& pos);

	class badIndex{
	public:
		void print(){
			cout << "index out of bound"<<endl;
		}
	};
private:
	string filename;
};

#endif /* MYFILE_H_ */
