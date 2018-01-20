//Reid_Nolan_HW8_[Concordance]
//Word.cpp
//**********************************************************************************************//
//Author: Reid S. Nolan																			//
//Date: 04/27/2017																				//
//Reid_Nolan_HW8_[Concordance] Word Class Source File											//
//C++ Class for getting and formatting data stored in a tect file								//
//**********************************************************************************************//
#include "stdafx.h"
#include "Word.h"

using namespace std;

//constructors
Word::Word()
{
	//class variables
	wordItself = "";
	frequency = 0;
	lineNumber = 0;
}

//destructors
Word::~Word()
{
}

//setters
void Word::setWordItself(const string nextWord)
{
	wordItself = nextWord;
}

void Word::setLineNumber(const size_t j)
{
	lineNumber = j;
}

//getters
string Word::getWordItself()
{
	return wordItself;
}

int Word::getLineNumber()
{
	return lineNumber;
}

//other class functions
void Word::parseOutWords(Word word, vector<string> &book, vector<Word> &wordList)
{	
	for (size_t i = 0; i < book.size(); i++) //loop through lines elements in vector
	{
		if (!book[i].empty()) //test for contenct
		{
			stringstream ss(book[i]); //declare and initialize local variables
			string wordString = "";

			while (getline(ss, wordString, ' ')) //separate word in lines
			{				
				handleAccentedChar(wordString); //handle the french in Sherlock.txt
				
				if (!wordString.empty()) //checks for non-empty string
				{
					removeLeadingPunct(wordString); //recursively removes leading punctiation from string

					if (!wordString.empty()) //checks for non-empty string
					{
						removeTrailingPunct(wordString); //recursively removes trailing punctiation

						for (size_t j = 0; j < wordString.length(); j++) //loops through string
						{
							wordString[j] = tolower(wordString[j]); //converts string to lower case
						}

						word.setWordItself(wordString); //set string value to word object
						word.setLineNumber(i + 1); //set line number value to word object
						wordList.push_back(word); //add object to list
					}
					else {/*do nothing*/ }
				}
			}
		}
		else {/*do nothing*/ }
	}	
}

void Word::handleAccentedChar(string &wordString) //specifically for the accented French characters in Sherlock.txt
{
	for (size_t j = 0; j < wordString.length(); j++) //loop through string elemets
	{
		if ((wordString[j] == -61)) //if const char[2] 'è' is hit...
		{
			wordString[j] = 'e'; //...then, set to 'e'
			wordString[j + 1] = ' '; //...then, clear the addional char at the end
			wordString.pop_back(); //...finally, just to be sure
		}
		else {/*do nothing*/ }
	}
}

void Word::removeLeadingPunct(string &wordString)
{
	if (!isalnum(wordString[0])) //if first char ispunct, the opposite of isalnum...
	{
		wordString.erase(wordString.begin()); //...then, remove that char
		if (!wordString.empty() && !isalnum(wordString[0])) //if string is not empty and the first char is not punct...
		{
			removeLeadingPunct(wordString); //...then, get recursive on it
		}
	}
	else {/*do nothing*/ }
}

void Word::removeTrailingPunct(string &wordString)
{
	if (!isalnum(wordString[wordString.length() - 1])) //if last char ispunct, the opposite of isalnum...
	{
		
		wordString.pop_back(); //...then, remove that char
		if (!wordString.empty() && !isalnum(wordString.length() - 1)) //if string is not empty and the last char is not punct...
		{
			removeTrailingPunct(wordString); //...then, get recursive on it
		}
	}
	else {/*do nothing*/ }
}