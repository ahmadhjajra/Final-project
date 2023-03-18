/*
 * System.cpp
 *
 *  Created on: Oct 23, 2020
 *      Author: user
 */

#include "System.h"
#include <windows.h>
#include <stdio.h>



System::System(){
	// TODO Auto-generated constructor stub
	size=0;
}

System::~System() {
	// TODO Auto-generated destructor stub

}

//******************************************************************

bool System::found(const string& name){
	std::ifstream infile(name);
	return infile.good();
}

//*******************************************************************



//*******************************************************************



//*******************************************************************
// mkdir command
void System::createDir(const string& name){

	int check = _mkdir(name.c_str());
	if(check == 0)cout << "\tDirectory " << name << " has been made" << endl;
	else
		cout <<"\tCannot make Directory " << name << " !" << endl;
}

//******************************************************************
//rmdir command
void System::removeDir(const string& name){
	if(this->user != "admin"){
		cout << this->user << " \tis not eligible to delete Directory" << name << endl;
		return;
	}
	DIR *d = opendir(name.c_str());
	struct dirent * dp;
	short cnt =0,check;
	if (d == NULL) {
		cout << "\tCan't find Directory in the given name -> " << name << endl;
		return;
	}
	while ((dp = readdir(d)) != NULL) {
			if(dp->d_name != NULL && dp->d_name != '\0'){
				cnt++;
			}
	}
	if(cnt == 2){
		 check = _rmdir(name.c_str());
	}
	if(check == 0) cout << "\tDirectory has been deleted succefully"<<endl;

	else
		cout << "\tError deleting give folder"<<endl;

}

//*******************************************************************


void System::chmod(const string& num, const string& file){
	if(!found(file)) throw (FileNotFoundException(file));
	int number = std::stoi( num );
	if(number < 0 || number > 7) throw(Errors::numError());
	if(file.find("history.txt")){
		if(!check(file)) return;
	}

	string str="";
	str +="chmod ";
	str += num;
	str +="55 ";
	str += file;
	system(str.data());


}


//*******************************************************************
//ls command
void System::listDir(){
	char buff[100];
	GetCurrentDir( buff, 100);
	string current_working_dir(buff);
	struct dirent *entry;
	DIR *dir = opendir(current_working_dir.c_str());
	if (dir == NULL) {
	      return;
	}
	string userFile = user;
	userFile.append("history.txt");
	if(user == "admin"){
		while ((entry = readdir(dir)) != NULL){
			string temp = entry->d_name;
			if(temp.compare(".") == 0 || temp.compare("..") == 0|| temp.compare(".cproject") == 0 || temp.compare(".project") == 0 ||
					temp.compare(".settings") == 0 || temp.compare("all") == 0 || temp.compare("Debug") == 0) continue;
			if((temp.find(".cpp")) != std::string::npos)continue;
			if((temp.find(".h")) != std::string::npos)continue;
			if((temp.find(".zip")) != std::string::npos) continue;
			cout <<"\t" <<entry->d_name << endl;
		}
		closedir(dir);
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		string temp = entry->d_name;
		if ((temp.find("history.txt")) != std::string::npos) {
		    if(temp != userFile) continue;
		}
		if(temp.compare(".") == 0 || temp.compare("..") == 0|| temp.compare(".cproject") == 0 || temp.compare(".project") == 0 ||
			temp.compare(".settings") == 0 || temp.compare("all") == 0 || temp.compare("Debug") == 0) continue;
		if((temp.find(".cpp")) != std::string::npos)continue;
		if((temp.find(".h")) != std::string::npos)continue;
		if((temp.find(".zip")) != std::string::npos) continue;

		cout << "\t" << entry->d_name << endl;
	}
	closedir(dir);
}

//*******************************************************************

bool System::check(const string& temp){
	string username = user;
	username.append("history.txt");
	if (temp.find("history.txt") != std::string::npos) {
			if (temp != username){
				return false;
			}
			return true;
		}
	return true;
}

//*******************************************************************
int System::getFileSize(const string& name){
	ifstream infile(name);
	infile.seekg(0, std::ios::end);
	int file_size = infile.tellg();
	infile.close();
	return file_size;
}

//*******************************************************************

void System::editFile(const string& name){
	if (user == "admin"){
		string filename = "notepad \"" + name + "\"";
		system(filename.c_str());
		return;
	}
	string username = user;
	username.append("history.txt");
	if (name.find("history") != std::string::npos) {
		if (name != username){
			cout << "\nUser " << user <<" is not eligible to edit another user file"<< endl;
			return;
		}
	}
	string filename = "notepad \"" + name + "\"";
	system(filename.c_str());
}


//*******************************************************************

void System::read(const string& name, const int& pos){
	if(!found(name)) throw (FileNotFoundException(name));
	int size = getFileSize(name);
	if(pos > size) throw Errors::readError();
	ifstream infile(name);
	char c;
	infile.seekg(pos);
	infile >> c;
	cout << c;
	infile.close();
}

//*******************************************************************

void System::writeChar(const string& name, const int& pos, const char& character){
	if(!found(name)) throw (FileNotFoundException(name));
	int size = getFileSize(name);
	if(pos > size) throw Errors::writeError();
	ofstream out(name);
	out.seekp(pos);
	out << character;
	out.close();
}

//********************************************************************

void System::write(const string& name, const string& line){
	std::ofstream out;
	if(line.size() == 0 )return;
	if(user == "admin"){
		out.open(name,std::ios::app);
		out << line+"\n";
		out.close();
		return;
	}
	string username = user;
	username.append("history.txt");
	if (name.find("history") != std::string::npos) {
		if (name != username){
			cout << "\tUser " << user <<" is not eligible to edit another user file"<< endl;
			return;
		}
	}
	out.open(name,std::ios::app);
	out <<line+"\n";
	out.close();
}


//********************************************************************

void System::printExitMessage(){
	cout << "\tProgram is shutting down, GoodBye!" << endl;
}
//********************************************************************

void System::touch(const string& name){
	if(!found(name)){
		addFile(name);
		return;
	}
	SYSTEMTIME thesystemtime;
	GetSystemTime(&thesystemtime);
	FILETIME thefiletime;
	SystemTimeToFileTime(&thesystemtime,&thefiletime);
	HANDLE filename = CreateFile(name.data(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFileTime(filename,(LPFILETIME) NULL,(LPFILETIME) NULL,&thefiletime);
	CloseHandle(filename);


}

//********************************************************************

void System::addFile(const string& name){
	std::ofstream outfile (name);
	outfile << std::endl;
	outfile.close();
}

//*********************************************************************

void System::copy(const string& src,const string& tar){

	if(!found(src)) throw (FileNotFoundException(src));
	if(!found(tar)) touch(tar);
	if (user == "admin" || (check(src) && check(tar))){
		ifstream input(src.data());
		ofstream output(tar.data());
		output.clear();
		string temp;
		while(!input.eof()){
			getline(input,temp);
			output<<temp<<'\n';
		}
	}
}

//*********************************************************************

void System::rem(const string& name){
	if(!found(name)) throw (FileNotFoundException(name));
	if(user == "admin"){
		remove(name.data());
		return;
	}
	bool check1 = check(name);
	if(!check1){
		cout << "\tUser " << user << " is not eligible to delete " << name << endl;
		return;
	}
	remove(name.data());
}

//*********************************************************************

void System::move(const string& src,const string& tar){
	copy(src,tar);
	rem(src);
}

//*********************************************************************

void System::cat(const string& name)
{
	if(!found(name)) throw (FileNotFoundException(name));
    string temp;
    ifstream input(name.data());
    if(user == "admin"){
    	while(!input.eof()){
    		getline(input,temp);
    	    cout<<"\t"<<temp<<"\n";
    	}
    	input.close();
    }
    if (!(check(name))){
    	cout << "\tUser " << user << " is not eligible to view " << name <<" data" <<endl;
    	input.close();
    	return;
    }
    while(!input.eof()){
        getline(input,temp);
         cout<< "\t"<<temp<<"\n";
    }
    input.close();
}

//*********************************************************************

void System::head(const string& name , const int& num)
{
	if(!found(name)) throw (FileNotFoundException(name));
    int temp = num;
    string temp1;
    ifstream input(name.data());
    if(user == "admin"){
    	while(!input.eof() && temp-- != 0){
    		getline(input,temp1);
    	    cout<<temp1<<"\n";
    	}
    	input.close();
    }
    if (!(check(name))){
    	cout << "\tUser " << user << " is not eligible to view " << name <<" data" <<endl;
        input.close();
        return;
    }
    while(!input.eof() && temp-- != 0){
        getline(input,temp1);
         cout<<temp1<<"\n";
    }
    input.close();
}

//********************************************************************

void System::showPrivacy(const string& file){
	if(!found(file)) throw (FileNotFoundException(file));
	struct stat st;
	string s="";
	if(user == "admin"){
		if(stat(file.data(), &st) == 0){
			mode_t perm = st.st_mode;
			s += (perm & S_IRUSR) ? 'r' : '-';
			s += (perm & S_IWUSR) ? 'w' : '-';
			s += (perm & S_IXUSR) ? 'x' : '-';
			cout << s << endl;;
		}
		return;
	}
	if (!(check(file))){
	    	cout << "\tUser " << user << " is not eligible to view " << file <<" permissions" <<endl;
	        return;
	}
	if(stat(file.data(), &st) == 0){
		mode_t perm = st.st_mode;
		s += (perm & S_IXUSR) ? 'x' : '-';
	    s += (perm & S_IRUSR) ? 'r' : '-';
	    s += (perm & S_IWUSR) ? 'w' : '-';

	    cout << "\t" << s << endl;
	}
}

//*******************************************************************

void System::diff(const string& file1, const string& file2){
	if(!found(file1)) throw (FileNotFoundException(file1));
	if(!found(file2)) throw (FileNotFoundException(file2));
	if(user.compare("admin") != 0){
		if (file1.find("history.txt") || file2.find("history.txt")){
			if(!check(file1) || !check(file2)){
				cout << "\tUser " << user << " is not eligible to view one of the files contents" <<endl;
				return;
			}
		}
	}
	std::vector<string> file1Data;
	std::vector<string> file2Data;
	// now we save the data of each file in the vectors
	std::string temp;
	ifstream read1(file1);
	if(read1.fail()){
		cerr << "\tCan't open " << file1 << endl;
		return;
	}
	while(getline(read1,temp)){  //read all the content of file1
			//getline(read1,temp);
			file1Data.push_back(temp);
		    read1.peek();

	}
	read1.close();
	ifstream read2(file2);
	if(read2.fail()) {
		cerr << "\tCan't open " << file2 << endl;
		return;
	}
	while(getline(read2,temp)){ //read all the content of file2
		//getline(read1,temp);
		file2Data.push_back(temp);
		read2.peek();
	}
	read2.close();
	//bool eq = (file1Data.size() == file2Data.size()); // here we check if the files have equal length
	diffHandle(file1,file2,file1Data,file2Data);


}


//********************************************************************

int System::checkMatches(std::vector<string>& first,std::vector<string>& second){
	int cnt =0;
	if (first.size() == second.size()){
		unsigned int i =0;
		unsigned int j =0;
		//unsigned int mismatch =0;
		while(i < first.size() || j < second.size()){
			if (first[i] == second[j]){
				i++; j++;
				cnt++;
			}else{
				first[i].erase();
			}
		}
	}
	return cnt;
}

//********************************************************************

void System::diffHandle(const string& file1,const string& file2,std::vector<string> &first, std::vector<string>& second){
	/*int checkFirst =-1;
	string toCheck = second[0];
	for (unsigned int i = 0; i < first.size(); i++){
		if(first[i].compare(toCheck) == 0){ // found first equal
			checkFirst = i;
			break;
		}
	}
	if(checkFirst == -1) {
		cout << "\tNo match has been found need to change "<<file1 << " from 0 to " << first.size() << endl;
		for (unsigned int i = 0; i < second.size(); i++){
			cout << "\t> " << second[i] << endl;
		}
			return;
	}else{
		cout << "\tNeed to add from the begining of the file to " << checkFirst << endl;
		cout << "\t >" << toCheck << endl;
	}
	string toCheck = second[0];
	for (unsigned int i = 0; i < first.size(); i++){
		if(first[i].compare(toCheck) == 0){ // found first equal
				checkFirst = i;
		}
	}
*/
}

//********************************************************************

void System::tail(const string& name , const int& num)
{
	if(num <= 0) {
		cout << "\tError with negative number in tail\n";
		cout << "\tyour parameter is = " << num << endl;
		return;
	}
	std::vector<string> myvector;
	string temp;
	if(!found(name)) throw (FileNotFoundException(name));
	ifstream input(name.data());
	if(user == "admin"){
		while(!input.eof())
		{
			getline(input,temp);
			myvector.push_back(temp);
		}
		input.close();
		int size = myvector.size();
		if(num >= size){
			for (int i=0; i<size; ++i)
				std::cout <<myvector[i] << '\n';
			return;
		}else{
			int temp1 = size - num;
			for (int i=0; i<temp1; ++i)
			myvector.erase(myvector.begin());
		}
		for (unsigned i=0; i<=myvector.size(); ++i)
			std::cout <<myvector[i] << '\n';
		return;
	}
	if (!(check(name))){
		cout << "\tUser " << user << " is not eligible to view " << name <<" data" <<endl;
		input.close();
		return;
	}
	while(!input.eof()){
		getline(input,temp);
		myvector.push_back(temp);
	}
	input.close();
	int size = myvector.size();
	if(num >= size){
		for (int i=0; i<size; ++i)
			std::cout <<myvector[i] << '\n';
		return;
	}else{
		int temp1 = size - num;
		for (int i=0; i<temp1; ++i)
			myvector.erase(myvector.begin());
	}
	for (unsigned i=0; i<=myvector.size(); ++i)
		std::cout <<myvector[i] << '\n';
}

//**********************************************************************

bool System::is_number(const std::string& s){
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

//***********************************************************************

void System::concatFiles(const string& from, const string& to){
	std::ofstream of_a(to, std::ios_base::binary | std::ios_base::app);
	std::ifstream if_b(from, std::ios_base::binary);

	of_a.seekp(0, std::ios_base::end);
	of_a << if_b.rdbuf();
	of_a.close();
	if_b.close();
}

//***********************************************************************

void System::fgrepfile(const string& file,const string& str){

	const char* filename = file.data();
	char fullFilename[MAX_PATH];
	GetFullPathName(filename, MAX_PATH, fullFilename, nullptr);
	if(str.compare("users.txt") == 0) {return;}
	if (file.find(".txt") != std::string::npos){
		if(!(check(file))){
			cout << "\tUser " << user << " can't view " << file << " since he is not the owner"<< endl;
			return;
		}
		ifstream input(file);
		if (input.fail()){
			return;
		}
		cout << "Opened file " << file << endl;
		string temp="";
		while(!input.eof()){
			getline(input,temp);
			if(temp.compare(str) == 0){
				cout << "\tFound " << str << " in file - " << file <<" and the path is: "
						"\n\t " << fullFilename << endl;
				break;
			}
		}
		input.close();
	}
	return;


}

//***********************************************************************

void System::fgrep(const string& directory,const string& str){
	DIR *dir;
	struct dirent *ent;
	string temp = "";
	if ((dir = opendir (directory.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			switch (ent->d_type) {
				case DT_REG:
					fgrepfile(ent->d_name,str);
					break;
				case DT_DIR:
				        // Directory
					if(ent->d_name[0] != '.' && !isdigit(ent->d_name[0]) && isalpha(ent->d_name[0])){
				    	string temp = ent->d_name;
				    	string path = directory+temp+"\\";
				    	fgrep(path,str);
				    }
				    break;
				default:
					break;
			}

		}
	closedir (dir);
	} else {
			  //cerr << "No permission to open  " <<directory << endl;
		return ;
	}
}

//***********************************************************************

void System::recursiveLocate(const string& directory,const string&file){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (directory.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			switch (ent->d_type) {
			    case DT_REG:
			        if( strcmp(ent->d_name,file.c_str()) == 0){
			        	cout << "\tFound " << file << " in " << directory << endl;
			        }
			        break;
			    case DT_DIR:
			    	if(ent->d_name[0] != '.' && !isdigit(ent->d_name[0]) && isalpha(ent->d_name[0])){
			    		string temp = ent->d_name;
			    		string path = directory+temp+"\\";
			    		recursiveLocate(path,file);
			    	}
			        break;
			    default:
			        break;
			}

		  }
		  closedir (dir);
		} else {
		  return ;
		}
}

//***********************************************************************


void System::printCommandList(){
	std::cout << "\techo STRING - prints the String to command line.\n"
				 "\tls - prints the current folder files.\n"
				 "\thistory - prints the current user last 15 commands (avoiding ambiguity)\n"
				 "\ttouch FILENAME - if file not found, makes a file. if file already found changes timestamp of the given file\n"
				 "\tcat FILENAME - prints all the file content\n"
				 "\thead FILENAME NUMBER - prints the first NUMBER of lines of given file (default NUMBER = 10)\n"
				 "\ttail FILENAME NUMBER = prints the last NUMBER of lines of given file (default NUMBER = 10)\n"
				 "\tcopy SOURCEFILE TOFILE - copies SOURCEFILE to TOFILE\n"
				 "\tmove SOURCEFILE TOFILE - moves the content of SORCESFILE to TOFILE (note SOURCEFILE won't be found after this command)\n"
				 "\tSOURCEFILE > TOFILE - chains the SOURCESFILE to TOFILE\n"
				 "\tTOFILE < SOURCEFILE - chains the SOURCESFILE to TOFILE\n"
				 "\tdiff FILE1 FILE2 - prints the difference between FILE1 and FILE2\n"
				 "\tchmod FILENAME NUMBER - sets a new permission to the file or directory.(note NUMBER has to be suitable)\n"
				 "\tfind FILENAME - checks if the FILENAME exists in the current folder.\n"
				 "\tmkdir NAME - makes a new directory of the given NAME in the current path.\n"
				 "\trmdir NAME - delete a directory in the current path, Only if the directory is empty.\n"
				 "\tshow privacy FILENAME - shows the permissions of the file or directory.\n"
				 "\tdate - shows today date.\n"
				 "\tfgrep STRING - search files for lines that matches fixed STRING.\n"
				 "\tlocate FILENAME - find the file in all of the system.(note this command is not like find!).\n";
}

//************************************************************************************

void System::printDate(){
	time_t timeToday;
	time(&timeToday);
	cout << "\t" <<asctime(localtime(&timeToday)) << endl;
}


//**************************************************************************************




















