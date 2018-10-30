// Michaela Vuklisevicova
// COMSC-110 Term Project, Spring 2017
// Pull out all the email addresses from a text file

#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


class toLower {public: char operator()(char c) const {return tolower(c);}};

string getFileName()
{
	string result;
	cout << "Enter the file name: ";
	getline (cin, result);
	return result;
} // getFileName

bool isValidEmailCharacter (char c)
{
	bool result = false;
	if (c >= 'A' && c <= 'Z') result = true;
	if (c >= 'a' && c <= 'z') result = true;
	if (c >= '0' && c <= '9') result = true;
	if (c == '.' || c == '-' || c == '+') result = true;
	return result;
} // isValidEmailCharacter

int main()
{
	// default file names
	string defaultInput = "fileContainingEmails.txt";
	string defaultOutput = "copyPasteMyEmails.txt";
			
	// empty list for up to 1,000 email addresses
	const int CAPACITY = 1000;
	int nEmails = 0;
	string email[CAPACITY];

	// input file name
	ifstream fin;
	cout << "Is this the INPUT file name: " << defaultInput << "?" << endl;
	cout << "If yes, press 'Enter'. " << endl;
	cout << "If no, press anything except 'Enter'. ";
	if (cin.get() == '\n')
	{
		fin.open(defaultInput.c_str());
		if (!fin.good()) throw "I/O error";
		cout << "File for input: " << defaultInput << endl;
	} // if
	else
	{
		cin.ignore();
		string fileName = getFileName();
		defaultInput = fileName;
		defaultOutput = fileName;
		fin.open(fileName.c_str());
		if (!fin.good()) throw "I/O error";
	} // else
		
	int startIndex;
	int endIndex;
	string lcEmail[CAPACITY];
	while (fin.good())
	{
		string lineOfTheFile;
		getline (fin, lineOfTheFile);
		
		int dotCounter = 0;
		for (int i = 0; i < lineOfTheFile.length(); i++)
		{
			if (lineOfTheFile[i] == '@')
			{
				for (int j = i - 1; j > 0; j--)
				{
					char c = lineOfTheFile[j];
					bool valid = isValidEmailCharacter(c);
					if (valid != true) break;
					startIndex = j;
				} // for
				
				for (int k = i + 1; k < lineOfTheFile.length(); k ++)
				{
					char c = lineOfTheFile[k];
					bool valid = isValidEmailCharacter(c);
					if (valid != true) break;
					if (c == '.') dotCounter++;
					endIndex = k + 1;
				} // for
				
				// store email addresses
				if (nEmails < CAPACITY && dotCounter > 0) 
					email[nEmails++] = lineOfTheFile.substr(startIndex, endIndex - startIndex);
			} // if
											
			// erase duplicate email addresses - no matter casing
			for (int i = 0; i < nEmails; i++)
			{
				lcEmail[i] = email[i];		//transfer all email addresses to lowercase form
				transform(lcEmail[i].begin(), lcEmail[i].end(), lcEmail[i].begin(), toLower());
			} // for 
			for (int i = 0; i < (nEmails-1); i++)
				if (lcEmail[nEmails-1] == lcEmail[i]) nEmails--;
		} // for
	} // while
	fin.close();		// close the input file

	// output file name*/
	if (nEmails > 0)
	{
		ofstream fout;
		cout << "Is this the OUTPUT file name: " << defaultOutput << "?" << endl;
		cout << "If yes, press 'Enter'. " << endl;
		cout << "If no, press anything except 'Enter'. ";
		if (cin.get() == '\n')
		{
			fout.open(defaultOutput.c_str());
			if (!fout.good()) throw "I/O error";
			cout << "File for output: " << defaultOutput << endl;
		} // if
		else
		{
			cin.ignore();
			string fileName = getFileName();
			fout.open(fileName.c_str());
			if (!fout.good()) throw "I/O error";
			defaultOutput = fileName;
		} // else
		
		//	print each email to the output file
		for (int i = 0; i < nEmails - 2; i++)
			fout << email[i] << "; ";
		fout << email[nEmails-1];
		
		fout.close();		// close the output file
	} // if
	
		
	// console output
	if (nEmails == 0) cout << "Sorry, no valid email address was found in the file: " << defaultInput << endl;
	for (int i = 0; i < nEmails; i++)
		cout << email[i] << endl;
	cout << nEmails << " valid email addresses were found and copied to the file " << defaultOutput << endl;
	cout << "Dear user, now you are able to open the file " << defaultOutput;
	cout << " and copy its content which is all valid email addresses, and paste";
	cout << "it to any 'to', 'cc', or 'bcc' field of your email message. For privacy ";
	cout << "protection of the receivers, it is best to use the 'bcc' field, ";
	cout << "as the other email addresses will not appear in the message." << endl;
	
	return 0;
} // main