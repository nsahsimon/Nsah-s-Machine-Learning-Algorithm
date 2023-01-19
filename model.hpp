
#ifndef MODEL
#define MODEL


#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<math.h>

using namespace std;


float sumFunc(float* list, int itemCount ){
	float sum = 0;
	for(int i = 0; i < itemCount; i++) {
		sum = sum + list[i];
	}
	return sum;
}

float meanFunc(float* list, int itemCount) {
	float totalFrequency = sumFunc(list, itemCount);
	float weightedSum = 0;
	for(int i = 0; i < itemCount; i++) {
		weightedSum = weightedSum + (i + 1) * list[i];
	}
	float mean = weightedSum / totalFrequency;
	return mean;
	
}

float stdDev(float* list, int itemCount) {
	float totalFrequency = sumFunc(list, itemCount);
	float weightedSum = 0;
	float mean = meanFunc(list, itemCount);
	for(int i = 0; i < itemCount; i++) {
		weightedSum = weightedSum + (i + 1  - mean) * (i + 1  - mean) * list[i];
	}
	float stdDev = sqrt(weightedSum / totalFrequency);
	return stdDev;
	
}


class Model {
	public:
	string partyName;
	float freqOfResponsesPerQtn[10][4];
	float* stdDevOfResponsesPerQtn = new float[10];
	float** relFreqOfResponsesPerQtn = new float*[10]; // 10 questions and 4 possible responses per question
	float _relStdDevOfResponsesPerQtn[10]; // The smaller the standard deviation of the responses of a given question, the better a factor it is to predict the users party or the greater its weight
	float* relWeightPerQtn = new float[10];
		
	// Constructor1
	Model(string _partyName) {
		partyName = _partyName;
		
		//initialize arrays with zeroes
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < 4; j++) {
				freqOfResponsesPerQtn[i][j] = 0.0;
			}
		}
		
	}
	
	//Constructor 2
	Model() {
		//initialize arrays with zeroes
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < 4; j++) {
				freqOfResponsesPerQtn[i][j] = 0.0;
			}
		}
	}
	
	
	float** relFreqOfResponsesPerQtnFunc() {
//		float** relFreqOfResponsesPerQtn = new float*[10];
		for(int i = 0; i < 10; i++) {
			relFreqOfResponsesPerQtn[i] = new float[4];
			float sum = sumFunc(freqOfResponsesPerQtn[i], 4);
			float mean = meanFunc(freqOfResponsesPerQtn[i], 4);
			for(int j = 0; j < 4; j++) {
//				cout<<freqOfResponsesPerQtn[i][j] / sum<<endl;
				if(sum != 0) {
					relFreqOfResponsesPerQtn[i][j] = freqOfResponsesPerQtn[i][j] / sum;
				}else {
					relFreqOfResponsesPerQtn[i][j] = 0.0;
				}
				
			}
		}
		
		
			///Just to see the frequency of responses peroption
//				for (int j = 0; j < 10; j++) {
//					cout << "Response frequency for question "<<j+1<<endl;
//					for(int k = 0; k < 4; k++) {
//						cout <<"\t"<<"option"<<k+1<<" :"<<freqOfResponsesPerQtn[j][k] <<" / "<<relFreqOfResponsesPerQtn[j][k]<<", ";
//					}
//					
//					cout<<"\n"<<endl;
//				}
		return relFreqOfResponsesPerQtn;
	}	
	
	float* relStdDevOfResponsesPerQtnFunc() {
		
//		float stdDevOfResponsesPerQtn[10];
		float relStdDevOfResponsesPerQtn[10];
		for(int i = 0; i < 10; i++) {
			stdDevOfResponsesPerQtn[i] = stdDev(freqOfResponsesPerQtn[i], 4);
		}
		
		float sumOfStdDevs = sumFunc(stdDevOfResponsesPerQtn, 10);
		if(sumOfStdDevs != 0) {
			for(int i = 0; i < 10; i++) {
				relStdDevOfResponsesPerQtn[i] = stdDevOfResponsesPerQtn[i] / sumOfStdDevs;
			} 
		} else { // All standard deviations are equal to each other and equal to zero
//			relStdDevOfResponsesPerQtn[i] = stdDevOfResponsesPerQtn[i] / 10;
		}
		
		return relStdDevOfResponsesPerQtn;
		
	} 
	
	float* relWeightPerQtnFunc() {
//		float* relWeightPerQtn = new float[10];
		float weightPerQtn[10];
//		float stdDevOfResponsesPerQtn[10];
		float relStdDevOfResponsesPerQtn[10];
		for(int i = 0; i < 10; i++) {
			stdDevOfResponsesPerQtn[i] = stdDev(freqOfResponsesPerQtn[i], 4);
		}
		
		float sumOfStdDevs = sumFunc(stdDevOfResponsesPerQtn, 10);
		cout<<"sum of stddevs: "<<sumOfStdDevs<<endl;
		if(sumOfStdDevs != 0) {
			for(int i = 0; i < 10; i++) {
				weightPerQtn[i] = (sumOfStdDevs - stdDevOfResponsesPerQtn[i]) / sumOfStdDevs;
			} 
		} else { // All standard deviations are equal to each other and equal to zero
			for(int i = 0; i < 10; i++) {
				weightPerQtn[i] = 1;
			} 
			
		}
		
		float sumOfWeightPerQtn = sumFunc(weightPerQtn, 10);
		for(int i = 0; i < 10; i++) {
				relWeightPerQtn[i] = weightPerQtn[i] / sumOfWeightPerQtn;
//				cout<<"relWeight :"<<relWeightPerQtn[i]<<", stddev: "<<stdDevOfResponsesPerQtn[i]<<endl;
			} 
		
		return relWeightPerQtn;
	}
	
	// Returns the a number proportional to the probability that the user belongs to the party defined by this model 
	// This value is computed based on the current responses provided by the user at the time of compuationt  
	float absConfidence(unsigned char* responses, int responseCount) {
		float absConfidence = 0.0;
		cout<<"Calculating confidence level: "<<endl;
		for(int i = 0; i < responseCount; i++) {
//			float prevAbsConfidence = abs
//			cout<<"absConfidence: "<<absConfidence<<" = "<<relWeightPerQtn[i]<<" * "<<relFreqOfResponsesPerQtn[i][responses[i] - 1]<<endl;
			absConfidence = absConfidence + relWeightPerQtn[i] * relFreqOfResponsesPerQtn[i][responses[i] - 1];
			
		}
		return absConfidence;
	}
	
};


#endif
