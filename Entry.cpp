/*
 * Entry.cpp
 *
 *  Created on: Nov 21, 2020
 *      Author: user
 */

#include "Entry.h"

Entry::Entry() {
	// TODO Auto-generated constructor stub
}

Entry::~Entry() {
	// TODO Auto-generated destructor stub
}


bool Entry::auth(string& pass){
	string s1;
	int cnt=1;
	while(s1 != pass){
		cin >> s1;
		if(s1 == pass) break;
		if(s1 == "exit") return false;
		if(cnt == 2){
			cout << "you have reached maximum number of tries program will quit!" << endl;
			return false;
		}
		cout << "Invalid password, please try again"<<endl;
		cnt++;
	}
	return true;
}

bool Entry::entryMain(string& usernamecurrent){
	string s1,s2,line;
	ifstream input("users.txt");
	cout << "Welcome to CpzTerminal\n";
	cout << "Enter a valid Username :" << endl;
	bool flag =false,error = false,passAuth = false;
	while(!input.eof() &&!flag){
		if(error){
			cout << "Enter a valid Username :" << endl;
		}
		error = false;
		cin >> username;
		parse.trim(username);

		while (getline(input,line)){
			std::istringstream iss(line);
			if (!(iss >> s1 >> s2)) { break; } // error
			if (s1 == username) break;
		}
		if(s1 == username){
			cout << "Enter Password : " << endl;
			cin >> password;
			parse.trim(password);
			if(parse.checkDelim(password) > 0){
				error = true;
				cout << "Invalid password, please try again"<<endl;
				continue;
			}
			if(s2 == password){
				cout << "Welcome " << username << endl;
				usernamecurrent = username;
				passAuth = true;
				flag = true;
			}else{
				cout << "Invalid password, please try again"<<endl;
				passAuth= auth(s2);
				if(passAuth) {
					cout << "Welcome " << username << endl;
					usernamecurrent = username;
				}
				break;
		}
	}
	}
	input.close();
	return passAuth;
}
