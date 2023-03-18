/*
 * main.cpp
 *
 *  Created on: Oct 23, 2020
 *      Author: user
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "System.h"
#include "Errors.h"
#include "Parser.h"
#include "Entry.h"
using namespace std;


int main()
{

	goto start;
start:
	System system;
	Parser parser;
	Entry entry;
    string action;
    string command;
    string name;
    string rec;
    string to;
    string pos;
    string character;
    string username;
    bool auth,first=true;
    string historyFile;

    auth = entry.entryMain(username);
    if(!auth){
    	system.printExitMessage();
    	return 0;
    }



    historyFile = username;
    historyFile.append("history.txt");

    system.setUser(username);
    if(!system.found(historyFile)){
    	system.touch(historyFile);
    }
    do{
    	std::getline (std::cin,action);
    	parser.trim(action);
    	system.write(historyFile,action);
    	if(first){
    		first = false;
    		cout << "$"<<username << ": ";
    		continue;
    	}
  try{
	  command="";
      name = "";
      rec = "";
      to = "";
      pos = "";
      character = "";
      	  // check equals to how many whitespaces string has
      	 int check = parser.checkDelim(action);
      	 //parsing line to get parameters!!!!
      	 if(check == 0){
      		if(action == "help"){
      			system.printCommandList();
      		}
      		else if(action == "ls")
      		{
      			system.listDir();
      		}
      		else if(action == "history")
      		{
      			system.cat(historyFile);
      		}
      		else if(action == "date"){
      		    system.printDate();
      		}
      		 else if(action == "fgrep")
      		{
      			 //cin >> name;
      			std::getline(std::cin, name);
      			 auto t1 = std::chrono::high_resolution_clock::now();
      			 system.fgrep("C:\\",name);
      			 auto t2 = std::chrono::high_resolution_clock::now();
      			 auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
      			 cout << "\tFinished running fgrep command after " << duration/1000 << " seconds" << endl;
      		}
      		 else if(action == "logout"){
      			 goto start;
      		 }
      		else if(action == "exit")
      		{
      			std::cout << "GoodBye!" << std::endl;
      			return 0;
      		}
      		else cerr<<"ERROR: command is not supported"<<endl;

      	 }else
      	 if(check == 1){
      		 parser.parseWithOne(action,command,name);

      		 if(command == "echo"){
      			 std::cout << "\t"+name << std::endl;
      		 }
      		 else if(command == "touch")
      		 {
      			if(name == "") throw Errors::touchError();
      			system.touch(name);
      		 }
      		 else if(command == "cat")
      		 {
      			if(name == "") throw Errors::catError();
      			system.cat(name);
      		 }
      		 else if(command == "remove")
      		 {
      			if(name == "") throw Errors::removeError();
      			system.rem(name);
      		 }
      		 else if(command == "find")
      		 {
      	    	 if(name == "") throw Errors::foundError();
      	    	 if(system.found(name)) cout << "File " << name << " has been found!" << endl;
      	     }
      		 else if(command == "mkdir")
      		 {
      	    	 if(name =="") throw Errors::dirError();
      	    	 system.createDir(name);
      	     }
      		 else if(command == "rmdir")
      		 {
      	    	 system.removeDir(name);
      	     }
      		 else if(command == "edit")
      		 {
      	    	 system.editFile(name);
      	     }
      		 else if(command == "write")
      		 {
      	    	 cout << "Enter the line to be chained to end of file \n";
      	    	std::getline (std::cin,rec);
      	    	system.write(name,rec);
      	     }
      		 else if(command == "privacy")
      		 {
      	    	 system.showPrivacy(name);
      	     }
      		 else if(command == "locate")
      		 {
      			auto t1 = std::chrono::high_resolution_clock::now();
      			 system.recursiveLocate("C:\\",name);
      			auto t2 = std::chrono::high_resolution_clock::now();
      			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

      			 cout << "Finished running locate command after " << duration/1000 << " seconds"<< endl;
      		 }
      		 else
      	         cerr<<"ERROR: command is not supported"<<endl;
      	 }
      	 else if(check == 2){
      		 parser.parseWithTwo(action,command,name,rec);

      		 if(command == "copy"){

      			if(name == "" || rec == "")throw Errors::copyError();
      			system.copy(name,rec);

      		 }
      		 else if(command == "move"){

      			if(name == "" || rec == "")throw Errors::moveError();
      			system.move(name,rec);

      		 }
      		 else if(command == "head"){

      			 bool flag = system.is_number(rec);
      			 if(!flag) throw Errors::headError();
      			 stringstream tokenizer(rec);
      			 int temp =0;
      			 tokenizer >> temp;
      			 system.head(name,temp);
      		 }

      		 else if(command == "tail"){
      			 bool flag = system.is_number(rec);
      			 if(!flag) throw Errors::tailError();
      			 stringstream tokenizer(rec);
      			 unsigned int temp=0;
      			 tokenizer >> temp;
      			 system.tail(name,temp);
      		 }
      		 else if(name == ">"){
      			 system.concatFiles(command,rec);
      		 }
      		 else if(name == "<"){
      			 system.concatFiles(rec,command);
      		 }
      		 else if(command == "diff"){
      			 system.diff(name,rec);
      		 }else if(command =="chmod"){
      			 system.chmod(name,rec);
      		 }
      		 else cerr<<"ERROR: command is not supported"<<endl;

      	 }else
             cerr<<"ERROR: command is not supported"<<endl;



    }catch(System::FileNotFoundException& ex)
    {
        ex.print();
    }
    catch(MyFile::badIndex& ex)
    {
        ex.print();
    }
    catch(Errors::ActionErrors& ex)
    {
        ex.print();
    }


    }while(action != "exit");


    return 0;
}

