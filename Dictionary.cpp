/*
Timothy Queva
CS2010 Lab5
October 26, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;
using std::string;

const int  MAX = 100;

typedef enum {F,T} BOOL;
typedef string WORD;
typedef WORD DICTION[MAX];

//Function prototypes
int LocateWord(DICTION, WORD,int);
BOOL FullDictionary(DICTION,int);
BOOL InsertWord(DICTION, int [],int &,WORD);
WORD GetNextWord(void);
void DumpDictionary(DICTION,int[],int);
void histogram(DICTION,int[],int);
void wList(DICTION,int[],int);

//Adds word to dictionary if curr<MAX. Else, returns F
BOOL InsertWord(DICTION d, int wCount[], int &curr, WORD word){
	if(curr<MAX){
		d[curr]=word;
		wCount[curr]=1;
		(curr)++;
		return T;
	}
	else return F;
}

//Prints histogram, then sorts dictionary alphabetically, then prints list of words with their totals
void DumpDictionary(DICTION d, int wCount[], int curr) {
	/*Note to self: don't forget to add prototypes when you add a new function
	or otherwise correctly order the functions. Otherwise you will get an error
	from the compiler saying that an added function was not declared in this scope.*/
	
	histogram(d,wCount,curr); 	//Histogram display function.
	
	//This sorts the dictionary alphabetically
	//Used bubble sort because of time constraint and because dictionary is only 100 words
	WORD wSwap;
	int nSwap=1;
	int top=curr-2;
	for(top;top>=0;top--){
		for(int i=0;i<=top;i++){
			if(d[i]>d[i+1]){
				//Swaps the words
				wSwap = d[i];
				d[i] = d[i+1];
				d[i+1] = wSwap;
				
				//Swaps the corresponding word total
				nSwap = wCount[i];
				wCount[i] = wCount[i+1];
				wCount[i+1] = nSwap;
			}
		}
	}
	
	wList(d,wCount,curr);	//Prints word list with corresponding frequency totals.
}

//Displays the histogram
void histogram(DICTION d, int wCount[], int curr){
	//Histogram heading
	cout << string("/-----------\\ \n")
				+ ("| Histogram |\n")
				+("\\-----------/ \n") << endl;
	
	const int ALIGN=2;	//Sets histogram alignment
	
	//Finds the word that occurs the most often
	int most=1;
	for(int i=0;i<curr;i++)	if(most < wCount[i]) most = wCount[i];
	
	//Prints out the stars in their correct location
	while (most>0){
		cout << setw(ALIGN) << left << " ";
		for(int index=0;index<curr;index++){
			if (wCount[index] >= most){
				cout << "* ";
			}
			else cout << "  ";
		}
		cout << endl;
		most--;
	}
	
	//Adds dashed line to denote histogram base
	cout << setw(ALIGN) << " ";
	for(int i=0;i<curr;i++) cout << "- ";
	cout << endl;
	
	
	//Finds the longest word
	int largest=0;
	for(int i=0;i<curr;i++){
		if(largest < d[i].size()){
			largest = d[i].size();
		}
	}
	
	//Adds the words underneath the histogram
	for(int wIndex=0;wIndex<largest;wIndex++){
		cout << setw(ALIGN) << " ";
		for(int str=0;str<curr;str++){
			/*if statement explained: for example, we have two words "hi" and "bye". The if/else statement keeps us in
			  bounds by preventing from printing position 2 of "hi" (segmentation error) but allowing us to print
			  position 2 of "bye" which would be the 'e'.
			*/
			if(d[str].size()<wIndex) cout << "  ";	//if word size 
			else cout << d[str][wIndex] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

//Displays the list of words along with their totals
void wList(DICTION d, int wCount[], int curr){
	//Heading prompts for user
	cout << string("/------------\\ \n")
	+ ("| Dictionary |\n")
	+ ("\\------------/ \n \n ")
	+ ("Word		Frequency\n")
	+ ("-------------------------") << endl;
	
	//Outputs word and their total
	for(int i=0;i<curr;i++){
		cout << setw(15) << left << d[i] << "	" << setw(8) << right << wCount[i] << endl;
	}
}

//retrieves word in input stream and returns the word or empty string if no more words in stream
WORD GetNextWord(void){
	char ch;
	WORD w = "";
	BOOL cbuilding = F;
	
	while(cin.good()){
		//Characters input to word section
		ch=cin.get();
		ch=tolower(ch);
		if(isalpha(ch)){
			w.push_back(ch);
			cbuilding=T;		//this line enables else condition to executes once we finished building word
		}
		//else if code section executes once non-alphabet character is encountered
		else if(cbuilding){
			return w;
		}
	}
	return w;
}

//Returns T if dictionary is full. F if not full
BOOL FullDictionary(DICTION d, int curr) {
	if(curr>99) return T;
	else return F;
}

//Checks dictionary for word and returns its location if it exists in dictionary
int LocateWord(DICTION d, WORD word, int curr) {
	for(int index=0;index<curr;index++) if(d[index] == word) return index;
	
	return -1;
}