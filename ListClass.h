//Author: Steven Gibson
//Date: 12/22/2014
//Last Modified: 12/25/2014
//Purpose: Provides the specifications for a list as a hash table
//Error Handling: None
//-----------------------------------------------------------------------------------------------
//Summary of Methods
//  **NOTE parameters are documented below
//
//		ListClass                 -- Default constructor, instantiates a ListClass object & sets PDMs to their initial values.
//
//		~ListClass                -- Destructor, returns dynamically allocated memory and resets PDMs to their inital values.
//
//		bool IsEmpty              -- True if the list contains no keys.
//
//		bool IsFull               -- Never true, data can always be chained in list.
//
//		ItemType Retrieve         -- Retrieves the value specified by currPos (Find must be called prior).
//
//		bool Find                 -- Finds the location of a key in the list, true if value is found. If found, currPos set to that index.
//
//		void Insert               -- Inserts a value into the list. Does not allow for duplicate keys.
//
//		void Delete               -- Deletes an item from the list specified at currPos (Find must be called prior).
//
//		void Clear                -- Clears all values from the list.
//
//		int Hash                  -- Converts a string key into an integer hash key.
//
//		int GetCollisions         -- Returns the total number of collision occurrences in the list.
//
//		int GetUniqueWordCount    -- Returns the total number of unique words in the list.
//
//		int GetTotalWordCount     -- Returns the total number of non-unique words in the list.
//
//		float GetListOccupancy    -- Returns the percentage of the list that is occupied.
//
//		void CollisionResolution  -- Resolves duplicate hash keys by chaining them to the index of the array where the collision occurred.
//
//		void PrintUniqueWords     -- Prints a list of the unique words found and the # of their individual occurrences.
//
// *See method pre/post for more details
//-----------------------------------------------------------------------------------------------


#include <iostream>
#include <string>
#include "ItemType.h"  // For use of ItemType record



// Constant Declarations 
const int SIZE = 500;							    // Size of array
const int FIRST_POSITION = 0;						// List minimum 
const int EMPTY = 0;								// List empty
const int PERCENT_MULTIPLIER = 100;					// Percent to multiply
const string EMPTY_STRING = "";                     // Empty string
const char SPACE = ' ';                             // Space character
const string OUTPUT_MSG = " time(s)";               // Message appended in output


// typedef declarations
typedef ItemType* listArr;
typedef void(*FunctionType)(const string&, ofstream&); // function pointer used to return an ItemType record 


// Class Declarations 
class ListClass 
{
	public: 

		//PRE: None
		//POST: PDMs set to their default values.
		ListClass(); // Default constructor;

		//PRE: A list object has been instantiated
		//POST: Object destructed and resources returned
		~ListClass(); // Destructor

		//PRE: A list object has been instantiated
		//POST: If List has no elements true is returned, otherwise false. 
		bool IsEmpty() const; 

		//PRE: A list object has been instantiated
		//POST: If List is full, true is returned, otherwise false. 
		bool IsFull() const; 

		//PRE: currPos contains valid position in list (FindPosition has been called)
		//POST: Returns a record of type ItemType specified by currPos. 
		ItemType Retrieve() const; 
	
		//PRE: Target contains a keyType value to search List for.
		//POST: True if target is found within list. currPos set to element's location in list. False otherwise
		bool Find(/*IN*/KeyType target);  // Value to be found
		
		//PRE: A key to be hashed is passed to the function
		//POST:target has been inserted at the location specified by the generated hash key
		void Insert(/*IN*/ ItemType newItem); // Item to be inserted

		//PRE: currPos contains the location of the element to be deleted (Find must be called prior)
		//POST: Element has been deleted from list. 
		void Delete(); 

		//Pre: List exists. 
		//Post: List has been cleared
		void Clear(); 

		//PRE: A list object has been instantiated
		//POST: The number of collisions are returned
		int GetCollisions();

		//PRE: A list object has been instantiated
		//POST: The number of unique words is returned
		int GetUniqueWordCount();

		//PRE: A list object has been instantiated
		//POST: The total number of words is returned
		int GetTotalWordCount();

		//PRE: A list object has been instantiated
		//POST: The percent occupancy of the list is returned
		float GetListOccupancy();

		void Print(); /* TEMPORARY */

		//PRE: A client defined function & an output file variable has been passed
		//POST: A list of unique words and their number of occurrences has been returned
		void PrintUniqueWords(/*IN/OUT*/FunctionType visit, // Client defined function
			                  /*IN/OUT*/ofstream& dout);    // Output file variable

	protected:

		//PRE: A string value has been passed to the method
		//POST: A (hopefully) unique hash key has been returned
		int Hash(/*IN*/string word); // Word to be hashed

		//PRE: A hash key and an item to insert is passed to the list
		//POST: A new item has been chained to the front of the current index of the array
		void CollisionResolution(/*IN*/int hashKey,       // Hash key to be resolved
			                     /*IN*/ItemType newItem); // New item to be inserted



//-----------------------------------------------------------------------------------------------


	private: 

		int currPos;         // Specifies current position in the List 
		listArr list;		 // Pointer to the list 

		int collisionCt;     // Total number of collisions
		int uniqueWordCt;    // Total number of unique words
		int totWordCt;       // Total number of non-unique words

};// END ListClass 