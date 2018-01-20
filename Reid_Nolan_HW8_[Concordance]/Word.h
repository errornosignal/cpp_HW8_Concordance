//Reid_Nolan_HW8_[Concordance]
//Word.h
//**********************************************************************************************//
//Author: Reid S. Nolan																			//
//Date: 04/27/2017																				//
//Reid_Nolan_HW8_[Concordance] Word Class Header File											//
//C++ Class for getting and formatting data stored in a tect file								//
//**********************************************************************************************//

#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Word
{
public:
	Word();
	~Word();

	vector<Word> wordList;
	
	void setWordItself(const string nextWord);
	void setLineNumber(const size_t j);
	string getWordItself();	
	int getLineNumber();
	static void parseOutWords(Word word, vector<string> &book, vector<Word> &wordList);

private:
	string wordItself;
	int frequency;
	int lineNumber;

	static void handleAccentedChar(string &wordString);
	static void removeLeadingPunct(string &wordString);
	static void removeTrailingPunct(string &wordString);
};