/*
 * MyDir.h
 *
 *  Created on: Oct 26, 2020
 *      Author: user
 */

#ifndef MYDIR_H_
#define MYDIR_H_
#include "MyFile.h"

class MyDir {
public:
	MyDir();
	virtual ~MyDir();

	void makeDir(const string& name);

	void deleteDir(const string& name); // only if the directory is empty
};

#endif /* MYDIR_H_ */
