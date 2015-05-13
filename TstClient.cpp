// ____________________________________________________________________________________________________________________
//| AUTHOR: Steven Gibson                                                                                              |
//| PROJECT NAME: ListClass                                                                                            |
//| FILENAME: TstClient.cpp                                                                                            |
//| DATE: 12/22/2014                                                                                                   |
//| LAST MODIFIED: 12/25/2014                                                                                          |
//|                                                                                                                    |
//| STATEMENT OF PURPOSE: This program will test the methods of the ListClass implemented as a hash table.             |
//|                                                                                                                    |
//|                                                                                                                    |
//| INPUT: Data will be read in from an input file.                                                                    |
//|                                                                                                                    |
//| PROCESSING: Program will utilize test modules & main to test the methods of the client. The hash function will read|
//|             in a value and use bit shifting and ASCII manipulation to attempt to generate a (hopefully) unique key.|
//|             The collision resolution policy (chaining) will resolve any collisions by appending the duplicate hash |
//|             key's value to the end of a linked list attached to that position in the array.                        |
//|                                                                                                                    |
//| OUTPUT: Output will be sent to a file, specified by a constant value, detailing the file name, total number of     |
//|         unique words, total number of unique words, a list of unique words and the number of times they occur in   |
//|         the file, the CRP that was used, the number of collisions that occurred, and the percentage of occupancy.  |
//|                                                                                                                    |
//| ASSUMPTIONS: Words will be delimited in the input file by whitespace, commas, periods, semi colons, colons,        |
//|              parenthesis, braces, quotes(single and double, or any relational operator.                            |
//|                                                                                                                    |
//| EXCEPTION/ERROR HANDLING: Attempting to retrieve on empty or insert a diplicate key will result in exeptions thrown|
//|                                                                                                                    |
//| METHOD/FUNCTION SUMMARY:                                                                                           |
//|  **NOTE parameters are documented below                                                                            |
//|                                                                                                                    |
//|     void PrintToFile  -- Prints the unique words, with their number of occurrences in the file to a specified      |
//|                          output file.                                                                              |
//|                                                                                                                    |
//| *See function pre/post for more information                                                                        |
//|____________________________________________________________________________________________________________________|

// Included Libraries
#include "ListClass.h" // For use of ListClass objects
#include <iostream>    // for basic io
#include <fstream>     // For file io
#include <iomanip>     // For io formattting
#include <string>      // For use of the string datatype
#include <cctype>      // For use of toupper function


using namespace std;


//--Constant Declarations---------------------------------------
const string CRP_USED = "Chaining";   // Collision Resolution Policy used

const string IN_FILE = "hash.txt";    // Input file name

const string OUT_FILE = "Stats.out";  // Output file name

const int LOW_ASCII_NUM = 48;         // Lower ASCII range for numbers

const int HIGH_ASCII_NUM = 57;        // Upper ASCII range for numbers

const int ASCII_UNDERSCORE = 95;      // ASCII value for an underscore

const int LOW_ASCII_LET = 65;         // Lower ASCII range for letters (uppercase)

const int HIGH_ASCII_LET = 90;        // Upper ASCII range for letters (lowercase)
//--------------------------------------------------------------


// Function Prototypes
void PrintToFile(/*IN*/const string& key,   // Key to be printed
	             /*IN/OUT*/ofstream& dout); // Output file variable



void main()
{
	//--Local variable declarations
	ListClass my;  // Initializing a ListClass object for testing

	ItemType item; // for testing inserts, finds and deletes

	ifstream din;  // Input file variable

	ofstream dout; // Output file variable

	string input;  // To store data coming in from file

	char letter;   // To store individual letters coming in from file
	//-----------------------------

	// Attempting to open the input file
	din.open(IN_FILE.c_str());


	if(din) // If the file exists...
	{
		// Opening the output file
		dout.open(OUT_FILE.c_str());

		// Priming Read
		din.get(letter);
		letter = toupper(letter); // Standardizing the case

		while(din)
		{
			if((letter >= LOW_ASCII_NUM && letter <= HIGH_ASCII_NUM) || letter == ASCII_UNDERSCORE || letter >= LOW_ASCII_LET && letter <= HIGH_ASCII_LET)
			{
				// If within the valid ASCII range, append character to end of string
				input = input + letter;
			
			} // END if
			else
			{
				if(input != EMPTY_STRING && (input[0] < LOW_ASCII_NUM || input[0] > HIGH_ASCII_NUM))
				{
					// If a delimeter is hit, (detailed in header documentation) insert the key into list
					item.key = input;
					my.Insert(item);

				} // END if

				input = ""; // After a valid word is read in, default string to empty

			} // END else

			// Modifying the LCV
			din.get(letter);
			letter = toupper(letter); // Standardizing the case

		} // END while

	
		if(input != EMPTY_STRING && (input[0] < LOW_ASCII_NUM || input[0] > HIGH_ASCII_NUM))
		{
			item.key = input;
			my.Insert(item);

		} // END if
	
		/* TEMP */
		cout << "Collisions: " << my.GetCollisions() << endl;
		cout << "Unique Words: " << my.GetUniqueWordCount() << endl;

		my.GetListOccupancy();
	
		my.Print();

		// Output to be sent to output file
		dout << "Statistics" << endl;
		dout << "-------------------------------------" << endl;
		dout << "Input File: " << IN_FILE << endl;
		dout << "Total non-unique words: " << my.GetTotalWordCount() << endl;
		dout << "Total unique words: " << my.GetUniqueWordCount() << endl;
		my.PrintUniqueWords(PrintToFile, dout);
		dout << "Collision Resolution Policy used: " << CRP_USED << endl;
		dout << "Number of collisions: " << my.GetCollisions() << endl;
		dout << "Percentage of occupancy: " << fixed << setprecision(2) << my.GetListOccupancy()  << "%" << endl;

	}
	// Closing input & output files
	din.close();
	dout.close();
	
} // END main

//---------------------------------------------------------------------------

void PrintToFile(/*IN*/const string& key,  // Key to be printed
	             /*IN/OUT*/ofstream& dout) // Output file variable
{
	dout << setw(25) << key << endl;

} // END PrintToFile

