#ifndef COLLECT
#define COLLECT

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include "questions.hpp"
#include "question.hpp"
#include "model.hpp"
#include<math.h>

using namespace std;

string politicalOrientation(unsigned char* responses, float responseCount = 5, float thresh = 1.5) {
	// Calculate the average response
	float sum = 0;
	float average = 0;
	
	for(int i = 0; i < responseCount; i++) {
		sum = sum + responses[i];
	}
	
	if (sum == 0) average = 0;
	else {
		average = sum / responseCount;
	}
		
	if (thresh < average) {
		return "Republican";
	} else {
		return "Democrat";
	}
}


void saveResponses(FILE* partyFile, char* responses) {
	fputs(responses, partyFile);
	fputs("\n", partyFile);
	while(1) {
		int status = fclose(partyFile);
		if(status == 0) {
			break;
		}
	}
	
}

int main() {
	cout<<"**Welcome to our C++ political survey program**"<<endl;
	int qtnCount = 11;
	char responses[10] = {}; 
//	Question qtns[11]={
//		Question(
//			"What should the government do to improve the economy?",
//			"Make people work and not give free money",
//			"Give people money in hopes of imiproving the economy by spending",
//			"option 3",
//			"option 4"
//		), 
//		Question(
//			"What should the government do with illegal immigration?",
//			"Let them in the country even if they cross the border illegally as fast as possible and make them work. ",
//			"Let them apply 1st at their country and wait a couple of years for them to enter the country legally",
//			"option 3",
//			"optioin 4"
//		),
//		Question(
//			"How  should the government fight inflation?",
//			"By printing more money.",
//			"By giving loans to small business to create more jobs.",
//			"option 3",
//			"option 4"
//		),
//		Question(
//			"Should the government tax the rich?",
//			"Yes",
//			"No",
//			"Maybe",
//			"Doesn't matter"
//		),
//
//		Question(
//			"Question 5",
//			"Option 1",
//			"Option 2",
//			"Option 3",
//			"Option 4"
//		),
//		Question(
//			"Question 6",
//			"Option 1 ",
//			"Option 2 ",
//			"Option 3",
//			"Option 4"
//		),
//		Question(
//			"Question 7",
//			"Option 1",
//			"Option 2",
//			"Option 3",
//			"Option 4"
//		),
//		Question(
//			"Question 8",
//			"Option 1",
//			"Option 2",
//			"Option 3",
//			"Option 4"
//		),
//		Question(
//			"Question 9",
//			"Option 1",
//			"Option 2",
//			"Option 3",
//			"Option 4"
//		),
//		Question(
//			"Question 10",
//			"Option 1",
//			"Option 2",
//			"Option 3",
//			"Option 4"
//		),
//		Question(
//			"Which political party do you align with?",
//			"Party 1",
//			"Party 2",
//			"Party 3",
//			"Party 4"
//		),
//		
//		
//	};
//	
	
	char newResponse;
	for(int i = 0; i < qtnCount; i++) {
		repeat:
		cout<<endl;
		cout<<qtns[i]._question<<endl;
		cout<<"\t"<<"1. "<<qtns[i]._option1<<endl;
		cout<<"\t"<<"2. "<<qtns[i]._option2<<endl;
		cout<<"\t"<<"3. "<<qtns[i]._option1<<endl;
		cout<<"\t"<<"4. "<<qtns[i]._option2<<endl;
		cout<<"\t"<<"Ans: ";
		cin>>newResponse;
//		scanf("%c", &newResponse);
		if(newResponse != '1' && newResponse != '2' && newResponse != '3' && newResponse != '4') {
			cout<<"Invalid response"<<endl;
			goto repeat;
		}
		
		char partyFilename[11] = {'p','a', 'r', 't', 'y','1','.','t','x','t'};
		if( i == qtnCount - 1) {
			switch(newResponse){
				case '1':
					partyFilename[5] = '1';
					break;
				case '2':
					partyFilename[5] = '2';
					break;
				case '3':
					partyFilename[5] = '3';
					break;
				case '4':
					partyFilename[5] = '4';
					break;
				default:
					break;
					
			}
			
			FILE* partyFile = fopen(partyFilename, "a");
			saveResponses(partyFile, responses);
		
		}
		
		else responses[i] = newResponse;
			
		}
	
	cout<<"Thank you for taking the time to complete the survey."<<endl;
	return 0;

}

#endif
