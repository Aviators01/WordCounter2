/*
Timothy Queva
CS2010 Lab5
October 26, 2020
*/

/*
This program is a modified word counter program. Template was provided by Franco Carlacci. Function implementation
in the Dictionary.cpp file and certain minor fixes were done by myself.

Program is designed to take 
*/

#include <iostream>

using namespace std;

const int  MAX = 100;

typedef enum {F,T} BOOL;
typedef string WORD;
typedef WORD DICTION[MAX];

//Function prototypes
int LocateWord(DICTION, WORD,int);
BOOL FullDictionary(DICTION,int);
BOOL InsertWord(DICTION, int [],int &,WORD);
WORD GetNextWord(void);
void DumpDictionary(DICTION ,int[],int);

//Global variables
DICTION dictionary;  //your dictionary 
WORD word; 
int wCount[MAX];   //tracks word frequencies
int curr=0;         // tracks how many words are currently in dictionary, 

int main (void) {
	int pos;
	
	while (T){
		word = GetNextWord();
		if (0 == word.length()){
			DumpDictionary(dictionary, wCount, curr);
			break;
		}
		
		if ((pos = LocateWord(dictionary, word, curr)) >= 0) wCount[pos]++;
		else if (InsertWord(dictionary, wCount, curr, word) == F) cout << "dictionary full " << word << " cannot be added\n";
	}
	return 0;
}