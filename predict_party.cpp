#ifndef PREDICT
#define PREDICT

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "model.hpp"
#include "question.hpp"
#include "questions.hpp"
#include<math.h>

using namespace std;

string predictParty(unsigned char* responses, float responseCount = 5, float thresh = 1.5) {
	
}


void modelSummary(Model model, int questionCount) {
	float* relWeightPerQtn = model.relWeightPerQtnFunc();
	float* stdDevOfResponsesPerQtn = model.stdDevOfResponsesPerQtn;
	float** relFreq = model.relFreqOfResponsesPerQtnFunc();
	for(int i = 0; i < questionCount; i++ ) {
		cout<<"relWeight :"<<relWeightPerQtn[i]<<", stddev: "<<stdDevOfResponsesPerQtn[i];
		for(int j = 0; j < 4; j++) {
			cout<<"\t"<<"opt"<<j + 1<<": "<<relFreq[i][j]<<", ";
		}
		cout<<"\n"<<endl;
	}
	cout<<"\n"<<endl;
}

bool compileModel(Model* models, char** partyDataFiles, char** partyModelNames, int dataFileCount) {

	FILE* partyFile;
	for(int i = 0; i < dataFileCount; i++ ) {
		cout<<"Working opening data file: "<<partyDataFiles[i]<<endl;
		Model newModel = Model(partyModelNames[i]);
		fstream partyFileStream;
    
	    // Open party data file stream
	    cout<<"Trying to open data file: "<<partyDataFiles[i]<<endl;
	    partyFileStream.open(partyDataFiles[i], ios::in);
		if (partyFileStream.is_open()) { 
		cout<<partyDataFiles[i]<<" party file is OPEN"<<endl;
        	char responses[10];
        	string resp;
        
        	///Extracting reponse information from data files
	        while (getline(partyFileStream, resp)) { 
	            cout << resp << "\n"; 
	            for(int j = 0; j < 10; j++) {
	            	int index = resp[j] - 49;
					newModel.freqOfResponsesPerQtn[j][index] = newModel.freqOfResponsesPerQtn[j][index] + 1;
				}
				
	        }
			
			float** relFreq = newModel.relFreqOfResponsesPerQtnFunc();
			float* relWeight = newModel.relWeightPerQtnFunc();
				
	        partyFileStream.close();
			models[i] = newModel;
		}
	
	}
	
	return true;
}

int main() {
	int dataFileCount = 2;
	char* partyDataFiles[4] = {"party1.txt", "party2.txt"};//, "party2.txt", "party3.txt", "party4.txt"};
	char* partyModelNames[4] = {"party1", "party2" , "party3", "party4"};
	Model models[4];
	compileModel(models, partyDataFiles, partyModelNames, dataFileCount);
	cout<<"Printing Model Summary"<<endl;
	for(int i = 0; i < dataFileCount; i++) {
		modelSummary(models[i], 10);
	}
	unsigned char sampleData[9] = {1, 2, 4, 4, 1, 4, 3, 1, 1};
	
	float confidenceList[4];
	for(int i = 0; i < dataFileCount; i++) {
		confidenceList[i] = models[i].absConfidence(sampleData, 9);
		cout<<"Party"<<i+1<<" confidence: "<<confidenceList[i]<<endl;
	}
	
	float maxConfidence = 0;
	int indexOfMax = 0;
	
	for(int i = 0; i < dataFileCount; i++) {
		if(confidenceList[i] >= maxConfidence) {
			maxConfidence = confidenceList[i];
			indexOfMax = i;
		}
	}
	
	
	cout<<"The predicted party: "<<partyModelNames[indexOfMax]<<" , Confidence: "<<maxConfidence<<endl;
}

#endif
