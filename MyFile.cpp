/*
 * MyFile.cpp
 *
 *  Created on: Oct 23, 2020
 *      Author: user
 */

#include "MyFile.h"

MyFile::MyFile():filename("") {
	// TODO Auto-generated constructor stub

}

//************************************************************
MyFile::~MyFile() {
	// TODO Auto-generated destructor stub
}


//************************************************************
MyFile::MyFile(const MyFile& file):filename(file.filename){

}


//************************************************************
MyFile& MyFile::operator =(const MyFile& file){
	filename = file.filename;
	return *this;
}

//************************************************************
MyFile& MyFile::operator =(const string name){
	filename = name;
	return *this;
}

//************************************************************
bool MyFile::operator ==(const string name){
	if(filename == name) return true;
	return false;
}

//************************************************************
bool MyFile::operator !=(string name){
	if((*this)==name) return false;
	return true;
}

//************************************************************
int MyFile::operator [](const int& pos){
	ofstream out(filename.data(),ios::app);
	out.seekp(0,ios::end);
	if(pos < 0 || pos>out.tellp()){
		throw badIndex();
	}
	out.seekp(pos);
	return out.tellp();
}
