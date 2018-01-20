//Reid_Nolan_HW8_[Concordance]
//Concordance.h
//**********************************************************************************************//
//Author: Reid S. Nolan																			//
//Date: 04/27/2017																				//
//Reid_Nolan_HW8_[Concordance] Concordance Class Header File									//
//C++ Class for creating a concordance for text files											//
//**********************************************************************************************//
#pragma once
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>

class Concordance
{
public:
	Concordance();
	~Concordance();

	vector<string> wordInFile;
	vector<int> lineNumbers;
	vector<vector<int>> lineNumbersList;

	static void sortWords(Word &word, vector<Word> &wordList);
	static void matchWords(vector<Word> wordList, vector<string> &wordInFile, vector<int> &lineNumbers, vector<vector<int>> &lineNumbersList);
	static void showConcordance(const vector<string> wordInFile, const vector<int> lineNumbers, const vector<vector<int>> lineNumbersList);
	static void saveConcordance(const vector<string> wordInFile, const vector<int> lineNumbers, const vector<vector<int>> lineNumbersList, ofstream &outFile);

private:
	static void vecDelete(vector<int> &vecToDelete);
	static size_t maxLineLength(vector<string> const &wordInFile);
};