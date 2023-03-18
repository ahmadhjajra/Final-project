/*
 * Errors.h
 *
 *  Created on: Oct 23, 2020
 *      Author: user
 */

#ifndef ERRORS_H
#define ERRORS_H
#include <iostream>
using namespace std;

// class for all the errors that can be made at the control line

class Errors
{
    public:
        Errors();
        virtual ~Errors();

    class ActionErrors
    {
        public:
        virtual ~ActionErrors(){};
        virtual void print()
        {

        }
    };

    class readError : public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE read FILENAME POSITION"<<endl;
        }
    };


    class writeError :public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE write FILENAME POSITION CHARACTER"<<endl;
        }
    };

    class foundError : public ActionErrors
    {
    	public:
    	virtual void print()
    	{
    		cerr << "ERROR : USAGE find FILENAME" <<endl;
    	}
    };

   class dirError: public ActionErrors
   {
   	   public:
    	virtual void print(){
    		cerr << "ERROR : USAGE of directory name"<<endl;
    	}
   };
   class touchError :public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE touch FILENAME"<<endl;
        }
    };


   class copyError :public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE copy SOURCE_FILENAME TARGET_FILENAME"<<endl;
        }
    };


   class removeError :public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE remove FILENAME"<<endl;
        }
    };


    class moveError :public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE move SOURCE_FILENAME TARGET_FILENAME"<<endl;
        }
    };



    class catError :public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE cat FILENAME"<<endl;
        }
    };



    class headError :public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE head FILENAME [n]"<<endl;
        }
    };



    class tailError :public ActionErrors
    {
        public:
        virtual void print()
        {
            cerr<<"ERROR: USAGE tail FILENAME [n]"<<endl;
        }
    };

    class numError : public ActionErrors
    {
    	public:
    	virtual void print(){
    		cerr << "ERROR: Usage number" << endl;
    	}
    };




};

#endif // ERRORS_H
