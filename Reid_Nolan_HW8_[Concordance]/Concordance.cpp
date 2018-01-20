//Reid_Nolan_HW8_[Concordance]
//Concordance.cpp
//**********************************************************************************************//
//Author: Reid S. Nolan																			//
//Date: 04/27/2017																				//
//Reid_Nolan_HW8_[Concordance] COncordance Class Source File									//
//C++ Class for creating a concordance for text files											//
//**********************************************************************************************//
#include "stdafx.h"
#include "Word.h"
#include "Concordance.h"

//constructors
Concordance::Concordance()
{
	Word word;
}

//destructors
Concordance::~Concordance()
{
}

//class functions
void Concordance::sortWords(Word &word, vector<Word> &wordList)
{
	sort(wordList.begin(), wordList.end(), [](Word &one, Word &two)	//sort word objects in list by word and then line number
	{
		return (one.getWordItself() < two.getWordItself()) || ((one.getWordItself() == two.getWordItself()) && (one.getLineNumber() < two.getLineNumber()));
	}); 
}

void Concordance::matchWords(vector<Word> wordList, vector<string> &wordInFile, vector<int> &lineNumbers, vector<vector<int>>&lineNumbersList)
{
	for (size_t i = 0; i < wordList.size(); i++) //loop through words in vector
	{
		if (i < wordList.size()-1) //leave the last element alone...for now
		{
			if (wordList[i].getWordItself() == wordList[i + 1].getWordItself()) //check if word matches next word
			{
				lineNumbers.push_back(wordList[i].getLineNumber()); //if word matches the next, only get line number and append to vector
				continue;
			}
			else
			{
				wordInFile.push_back(wordList[i].getWordItself()); //if word does not match the next word, get word aad line number and append to vector
				lineNumbers.push_back(wordList[i].getLineNumber());		
				lineNumbersList.push_back(lineNumbers); //append line numbers for each word to another 2-d vector
				vecDelete(lineNumbers); //reset line number vector for next iteration
			}			
		}
		else if (i == wordList.size()-1) //now we can take care of that last element
		{
			if (wordList[i].getWordItself() == wordList[i - 1].getWordItself()) //if last word does matches the previous
			{
				wordInFile.push_back(wordList[i].getWordItself()); //if word matches the previous word, get word aad line number and append to vector
				lineNumbers.push_back(wordList[i].getLineNumber());
				lineNumbersList.push_back(lineNumbers); //append line numbers for each word to another 2-d vector
				vecDelete(lineNumbers); //reset line number vector before leaving the function
			}
			else {/*do nothing*/}
		}
		else {/*do nothing*/ }
	}	
}

void Concordance::showConcordance(const vector<string> wordInFile, const vector<int> lineNumbers, const vector<vector<int>> lineNumbersList)
{	
	const string firstColumnHeader = "Words"; //define first column header
	const string secondColumnheader = "Count"; //define third column header
	const string thirdColumnheader = "Line Numbers"; //define second column header
	const string columnBreak = " | "; //define column break
	const string elementDelim = ", "; //define element delimiter
	const int maxQty = 10; //set max qty for second column output
	int columnBreakLength = columnBreak.length(); //get length of column break string
	int longestWordLength = maxLineLength(wordInFile); //get length of longest word in vector

	if (firstColumnHeader.length() > maxLineLength(wordInFile)) //set width of first column accordingly
	{
		longestWordLength = firstColumnHeader.length();
	}
	else {/*do nothing*/ }

	cout << endl << left << "\\\\beginning of output\\\\" << endl;
	cout << setw(longestWordLength) << firstColumnHeader << columnBreak << setw(secondColumnheader.length()+1) << secondColumnheader << columnBreak << thirdColumnheader << right << endl; //format column headers

	for (size_t i = 0; i < wordInFile.size(); i++) //loop through vector for output
	{
		cout << setw(longestWordLength) << wordInFile[i] << columnBreak << setw(secondColumnheader.length()) << lineNumbersList[i].size() << "x" << columnBreak; //set width of word colum to longest word length
		for (size_t j = 0; j < lineNumbersList[i].size(); j++) //loop thorough line number list
		{
			//cout << setw(0); //reset output width
			if (j < lineNumbersList[i].size() - 1) //for all but last line number in list
			{
				if (j >= 10 && j % maxQty == 0) //format second column width by quantity
				{
					cout << endl;
					cout << setw(longestWordLength + (columnBreakLength*2) + secondColumnheader.length() +1 ) << " "; //for shifting over line numbers to the right
				}else {/*do nothing*/ }

				cout << lineNumbersList[i][j] << elementDelim; //add delimiters between elements
			}
			else //for last element in vector
			{
				if (j >= 10 && j % maxQty == 0) //format second column width by quantity
				{
					cout << endl;
					cout << setw(longestWordLength + (columnBreakLength * 2) + secondColumnheader.length() + 1) << " "; //for shifting over line numbers to the right
				}else {/*do nothing*/ }

				cout << lineNumbersList[i][j]; //no delimiter for last element
			}
		}
		cout << endl;
	}
	cout << left << "\\\\end of output\\\\" << endl;
}

void Concordance::saveConcordance(const vector<string> wordInFile, const vector<int> lineNumbers, const vector<vector<int>> lineNumbersList, ofstream &outFile)
{
	const string firstColumnHeader = "Words"; //define first column header
	const string secondColumnheader = "Count"; //define third column header
	const string thirdColumnheader = "Line Numbers"; //define second column header
	const string columnBreak = " | "; //define column break
	const string elementDelim = ", "; //define element delimiter
	const int maxQty = 10; //set max qty for second column output
	int columnBreakLength = columnBreak.length(); //get length of column break string
	int longestWordLength = maxLineLength(wordInFile); //get length of longest word in vector

	if (firstColumnHeader.length() > maxLineLength(wordInFile)) //set width of first column accordingly
	{
		longestWordLength = firstColumnHeader.length();
	}
	else {/*do nothing*/ }

	outFile << "Created on: " << __TIMESTAMP__ << endl;
	outFile << endl << left << "\\\\beginning of file\\\\" << endl;
	outFile << setw(longestWordLength) << firstColumnHeader << columnBreak << setw(secondColumnheader.length() + 1) << secondColumnheader << columnBreak << thirdColumnheader << right << endl; //format column headers

	for (size_t i = 0; i < wordInFile.size(); i++) //loop through vector for output
	{
		outFile << setw(longestWordLength) << wordInFile[i] << columnBreak << setw(secondColumnheader.length()) << lineNumbersList[i].size() << "x" << columnBreak; //set width of word colum to longest word length
		for (size_t j = 0; j < lineNumbersList[i].size(); j++) //loop thorough line number list
		{
			//cout << setw(0); //reset output width
			if (j < lineNumbersList[i].size() - 1) //for all but last line number in list
			{
				if (j >= 10 && j % maxQty == 0) //format second column width by quantity
				{
					outFile << endl;
					outFile << setw(longestWordLength + (columnBreakLength * 2) + secondColumnheader.length() + 1) << " "; //for shifting over line numbers to the right
				}
				else {/*do nothing*/ }

				outFile << lineNumbersList[i][j] << elementDelim; //add delimiters between elements
			}
			else //for last element in vector
			{
				if (j >= 10 && j % maxQty == 0) //format second column width by quantity
				{
					outFile << endl;
					outFile << setw(longestWordLength + (columnBreakLength * 2) + secondColumnheader.length() + 1) << " "; //for shifting over line numbers to the right
				}
				else {/*do nothing*/ }

				outFile << lineNumbersList[i][j]; //no delimiter for last element
			}
		}
		outFile << endl;
	}
	outFile << left << "\\\\end of file\\\\";
}

void Concordance::vecDelete(vector<int> &vecToDelete)
{
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end()); //empty vector
	vector<int>().swap(vecToDelete);
}

struct sizeLess //for maxLineLength function
{
	template<class T> bool operator()(T const &a, T const &b) const //struct for maxLineLength
	{
		return a.size() < b.size();
	}
};

size_t Concordance::maxLineLength(vector<string> const &wordInFile) //users sizeLess struct
{
	return max_element(wordInFile.begin(), wordInFile.end(), sizeLess())->size(); //get length of longest word in vector
}