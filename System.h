/*
 * System.h
 *
 *  Created on: Oct 23, 2020
 *      Author: user
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
#include "Errors.h"
#include "MyFile.h"
#include <list>
#include <direct.h>
#define GetCurrentDir _getcwd
#include <dirent.h>
#include <ctime>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <cstdlib>
#include <limits.h>       //For PATH_MAX
#include <chrono>



class System {
public:
	System();
	virtual ~System();

	//read from the file
	void read(const string& name,const int& pos);

	//write to a file
	void writeChar(const string& name,const int& pos, const char& character);

	//writes a string to the end of file
	void write(const string& name, const string& line);

	//add new file
	void touch(const string& name);

	//copy file to other
	void  copy(const string& src,const string &tar);

	//remove(delete file)
	void rem(const string& name);

	//move function
	void move (const string& src,const string& tar);

	//print the file to screen
	void cat(const string& name);

	//print head 10 rows by default
	void head(const string& name, const int& num = 10);

	//print tail 10 rows by default
	void tail(const string& name,const int& num=10);

	//bool function to check if the file is valid
	bool found(const string& name);

	void addFile(const string& name);

	int getFileSize(const string& name);


	//print the input history
	void printList();

	//print all the command if a brief case
	void printCommandList();

	//prints all the file in the directory we working on
	void listDir();

	//prints current date
	void printDate();

	// creates a directory in the path
	void createDir(const string& name);

	void removeDir(const string& name);

	void editFile(const string& name);

	bool is_number(const std::string& s);

	void printExitMessage();

	void concatFiles(const string& from, const string& to);

	void showPrivacy(const string& file);

	void diff(const string& file1,const string& file2);

	void chmod(const string& num, const string& file);

	void locate(const string&file);

	void fgrep(const string& directory, const string& str);

	void fgrepfile(const string& file,const string& str);

	void recursiveLocate(const string& directory,const string&file);

	void diffHandle(const string& file1,const string& file2,std::vector<string>& first,std::vector<string>& second);

	int checkMatches(std::vector<string>& first,std::vector<string>& second);


	void setUser(const string& username){
		user = username;
	}

	bool check(const string& temp);

	class FileNotFoundException{
	public:
		FileNotFoundException():name(""){}
		FileNotFoundException(const string& n):name(n){}

		void print(){
			cout << "ERROR: "<<name<<" does not exist or cannot be processed"<<endl;
		}
	private:
		string name;

	};
private:
	int size;
	string user;
};

#endif /* SYSTEM_H_ */
