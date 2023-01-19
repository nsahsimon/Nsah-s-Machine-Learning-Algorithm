#ifndef QUESTION
#define QUESTION

#include<stdlib.h>
#include<iostream>
#include<string.h>
//#include<vector>


using namespace std;

struct Question {
	string _question;
	string _option1;
	string _option2;
	string _option3;
	string _option4;
	int _demResponse = 0;
	int _repResponse = 0;
	
	
	Question(string question, string option1, string option2, string option3, string option4, int demResponse, int repResponse) {
		_question = question;
		_option1 = option1;
		_option2 = option2;
		_option3 = option3;
		_option4 = option4;
		_demResponse = demResponse;
		_repResponse = repResponse;
	}
	
	Question(string question, string option1, string option2, string option3, string option4) {
		_question = question;
		_option1 = option1;
		_option2 = option2;
		_option3 = option3;
		_option4 = option4;
	}
	
	Question() {
		
	}
	
	void test() {
		cout<<"Running code in question class!!"<<endl;
	}
};


#endif
