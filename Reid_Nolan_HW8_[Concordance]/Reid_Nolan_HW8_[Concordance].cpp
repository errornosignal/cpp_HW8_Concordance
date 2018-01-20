//Reid_Nolan_HW8_[Concordance]
//Reid_Nolan_HW8_[Concordance].cpp : Defines the entry point for the console application.
//**********************************************************************************************//
//Author: Reid S. Nolan																			//
//Date: 04/27/2017																				//
//Reid_Nolan_HW8_[Concordance] Main Program														//
//C++ program for creating a concordance based on a user selected text file.					//
//**********************************************************************************************//

#include "stdafx.h"
#include "Word.h"
#include "Concordance.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

//function prototypes
string mainMenuSelectionPrompt();
string fileSelectionPrompt();
string getConsoleInput_string(const string prompt);
void readFileByLine(fstream &inFile, vector<string> &book);
void displayBook(const vector<string> book);
void vecDelete(vector<string> &vecToDelete);
void vecDelete(vector<Word> &vecToDelete);
void vecDelete(vector<int> &vecToDelete);
void vecDelete(vector<vector<int>> &vecToDelete);
void displayProgramHeader();
void displayMainMenu();
void displayLoadingFile(const string fileToOpen);
void displayLoadedFile(const string fileToOpen);
void displayNoInputFile(const string fileToOpen);
void displayInvalidFileName();
void displayNoConcordance();
void displayCreatingConcordance();
void displaySortingWords();
void displayMatchingWords();
void displayConcordanceCreated();
void displayNoDataExists();
void displaySavingToDisk();
void displaySavedToDisk(string outputFileName);
void displaySaveToDiskFailed();
void displayCleaningMemory();
void displayExitingProgram();

int main()
{		
	Word word; //create new object instance
	Concordance concordance; //create new object instance

	vector<string> book; //create vector to store contents of input file
	string fileToOpen = ""; //variable for input file selection

	displayProgramHeader(); //display program header

	while (true) //loop until user quits
	{		
		

		string mainMenuChoice = ""; //variable for main menu selection

		displayMainMenu();

		bool mainMenuChoiceGood = false; //set loop condition, get user input until valid
		while (!mainMenuChoiceGood)
		{
			vector<string> validMainInput{ "0", "1", "2", "3", "4", "5", }; //create vector with menu options

			mainMenuChoice = getConsoleInput_string(mainMenuSelectionPrompt()); //get user input and set to variable

			if (find(begin(validMainInput), end(validMainInput), mainMenuChoice) != end(validMainInput)) //match user input against vector contents
			{
				mainMenuChoiceGood = true; //set loop condition to true to exit
			}
			else {/*do nothing*/ }

			vecDelete(validMainInput); //empty vector
		}

		if (mainMenuChoice == "1")
		{
			//READ A TEXT FILE INTO MEMORY

			fstream inFile; //create new input file			

			fileToOpen = getConsoleInput_string(fileSelectionPrompt()); //get user input and set to variable

			size_t found = fileToOpen.find_last_of("."); //display error on invalid file name
			while(found == string::npos)
			{
				displayInvalidFileName();
				break;
			}

			inFile.open(fileToOpen);

			while (!inFile && found != string::npos) //if file not opened and file name is valid
			{
				displayNoInputFile(fileToOpen); //display failed to open input file message
				break;
			}

			while (inFile) //if input file is open
			{	
				if (book.size() > 0) //check vector for existing content
				{
					displayCleaningMemory();
					vecDelete(book); //empty vector
					vecDelete(word.wordList); //empty vector
					vecDelete(concordance.wordInFile); //empty vector
					vecDelete(concordance.lineNumbers); //empty vector
					vecDelete(concordance.lineNumbersList); //empty vector
				}
				else {/*do nothing*/ }

				displayLoadingFile(fileToOpen);
				readFileByLine(inFile, book);
				inFile.close();
				displayLoadedFile(fileToOpen);
			}
		}
		else if (mainMenuChoice == "2")
		{
			//VIEW THE CURRENT TEXT FILE

			if (book.size() > 0) //check vector for existing content
			{
				displayBook(book);

			}
			else
			{
				displayNoDataExists();
			}
		}
		else if (mainMenuChoice == "3")
		{
			//CREATE CONCORDANCE FOR THE CURRENT TEXT FILE

			if (book.size() != 0) //verify vector has existing content
			{
				displayCreatingConcordance();
				Word::parseOutWords(word, book, word.wordList); //format words and add property values to object

				displaySortingWords();
				Concordance::sortWords(word, word.wordList); //sort word objects in list by word and then line number

				displayMatchingWords();
				Concordance::matchWords(word.wordList, concordance.wordInFile, concordance.lineNumbers, concordance.lineNumbersList); //ignore duplicate words, but keep line numbers

				displayConcordanceCreated();
			}
			else
			{
				displayNoDataExists();
			}
		}
		else if (mainMenuChoice == "4")
		{
			//VIEW THE CURRENT CONCORDANCE		

			if (concordance.wordInFile.size() > 0) //check vector for existing content
			{
				Concordance::showConcordance(concordance.wordInFile, concordance.lineNumbers, concordance.lineNumbersList); //output concordance to console
			}
			else
			{
				displayNoConcordance();
			}
			
			//Concordance::showConcordance(concordance.wordInFile, concordance.lineNumbers, concordance.lineNumbersList); //output concordance to console
		}
		else if (mainMenuChoice == "5")
		{
			//SAVE THE CURRENT CONCORDANCE TO DISK

			if (concordance.wordInFile.size() > 0) //check vector for existing content
			{
				ofstream outFile; //create new output file

				size_t lastIndex = fileToOpen.find_last_of("."); //strinp off file extension
				string rawName = fileToOpen.substr(0, lastIndex);
				string outputFileName = "[" + rawName + "]_concordance.txt"; //set output file name

				outFile.open(outputFileName);

				while (!outFile) //if output is not file open
				{
					displaySaveToDiskFailed();
					break;
				}

				while (outFile) //if output file open
				{
					displaySavingToDisk();
					Concordance::saveConcordance(concordance.wordInFile, concordance.lineNumbers, concordance.lineNumbersList, outFile); //output concordance to file
					outFile.close();
					displaySavedToDisk(outputFileName);
					break;
				}
			}
			else
			{
				displayNoConcordance();
			}
		}
		else
		{
			//EXIT CONCORDANCE.EXE
			displayCleaningMemory();	
			break;
		}
	}	

	vecDelete(book); //empty vector
	vecDelete(word.wordList); //empty vector
	vecDelete(concordance.wordInFile); //empty vector
	vecDelete(concordance.lineNumbers); //empty vector
	vecDelete(concordance.lineNumbersList); //empty vector

	displayExitingProgram(); //display exiting program status message and prompt for confirmation before exit
	cin.get(); //get user confirmetion before teminating
	return 0;
}

//functions
string mainMenuSelectionPrompt()
{
	return "Make a selection> ";
}

string fileSelectionPrompt()
{
	return "Enter name of file to open> ";
}

string getConsoleInput_string(const string prompt)
{
	string userInput_string = "";

	bool inputGood = false;
	while (!inputGood)
	{
		cout << prompt;
		getline(cin, userInput_string);

		if (userInput_string.length() > 0)
		{
			inputGood = true;
		}
		else {/*do nothing*/ }
	}
	return userInput_string;
}

void readFileByLine(fstream &inFile, vector<string> &book)
{
	string line = "";
	int lineCount = 0;

	while (getline(inFile, line))
	{
		book.push_back(line);
		lineCount++;
	}
}

void displayBook(const vector<string> book)
{
	cout << endl << "\\\\begininng of file\\\\" << endl;
	for (size_t i = 0; i < book.size(); i++)
	{
		cout << fixed << right << setw(5) << i + 1 << "| " << book[i] << endl;
	}
	cout << "\\\\end of file\\\\" << endl;
}

void vecDelete(vector<string> &vecToDelete)
{
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<string>().swap(vecToDelete);
}

void vecDelete(vector<Word> &vecToDelete)
{
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<Word>().swap(vecToDelete);
}

void vecDelete(vector<int> &vecToDelete)
{
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<int>().swap(vecToDelete);
}

void vecDelete(vector<vector<int>> &vecToDelete)
{
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<vector<int>>().swap(vecToDelete);
}

void displayProgramHeader()
{
	cout << "// Reid_Nolan_HW8_[Concordance].cpp" << endl;
}

void displayMainMenu()
{
	cout << endl << "---------------Main Menu---------------" << endl;
	cout << "1. Select a text file to load into memory." << endl;
	cout << "2. View the current text file with line numbers." << endl;
	cout << "3. Create concordance for the current text file." << endl;
	cout << "4. View the current concordance." << endl;
	cout << "5. Save the current concordance to disk." << endl;
	cout << "0. Exit Concordance.exe." << endl << endl;
}

void displayLoadingFile(const string fileToOpen)
{
	cout << endl << "Loading \"" << fileToOpen << "\" into memory..." << endl;
}

void displayLoadedFile(const string fileToOpen)
{
	cout << endl << "Successfully loaded \"" << fileToOpen << "\" into memory." << endl;
}

void displayNoInputFile(const string fileToOpen)
{
	cout << endl << "Error: \"" << fileToOpen << "\" could not be opened." << endl;
	cout << "-Ensure that \"" << fileToOpen << "\" has been placed in the current" << endl;
	cout << " working directory and is not open in another program." << endl;
}

void displayInvalidFileName()
{
	cout << endl << "Error: Invaid file name." << endl;
}

void displayNoConcordance()
{
	cout << endl << "Error: No concordance currently exists." << endl;
}

void displayCreatingConcordance()
{
	cout << endl << "Creating concordance..." << endl;
}

void displaySortingWords()
{
	cout << endl << "Sorting contents..." << endl;
}

void displayMatchingWords()
{
	cout << endl << "Matching words..." << endl;
}

void displayConcordanceCreated()
{
	cout << endl << "Concordance created successfully." << endl;
}

void displayNoDataExists()
{
	cout << endl << "Error: No data currently stored in memory." << endl;
}

void displaySavingToDisk()
{
	cout << endl << "Saving concordance to disk..." << endl;
}

void displaySavedToDisk(string outputFileName)
{
	cout << endl << "Concordance successfully written to ""\"" << outputFileName << "\"." << endl;
}

void displaySaveToDiskFailed()
{
	cout << endl << "Error: Concordance could not be saved to disk." << endl;
}

void displayCleaningMemory()
{
	cout << endl << "Cleaning up memory..." << endl;
}

void displayExitingProgram()
{
	cout << endl << "Exiting program..." << endl;
	cout << "Press [Enter] to exit.";
}