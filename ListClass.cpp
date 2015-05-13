//---------------------------------------------------------------------------
// IMPLEMENTATION FILE (ListClass.cpp)
// This file implements the ListClass member functions
//---------------------------------------------------------------------------

#include "ListClass.h" // For ListClass specification


//---------------------------------------------------------------------------

ListClass::ListClass() // Default construcutor
{

	list = new ItemType[SIZE]; // Allocating a new list

	// Setting the default values of the ItemType
	for(int i = 0; i < SIZE; i++)
	{
		list[i].next = nullptr;
		list[i].wordCt = 0;

	} // END for
	
	// Setting currPos to the beginning of the array
	currPos = 0;

	// Setting counters to their initial value of 0
	collisionCt = 0; 
	uniqueWordCt = 0;
	totWordCt = 0;
	
}// END Default Constructor

//---------------------------------------------------------------------------

ListClass::~ListClass() // Destrucutor
{
	// Calling helper function to clear the list
	Clear();

}// END ListClass Destructor
//---------------------------------------------------------------------------

bool ListClass::IsEmpty() const// returns TRUE if list is empty
{
	return(uniqueWordCt == EMPTY);

}// END IsEmpty

//---------------------------------------------------------------------------

bool ListClass::IsFull() const// returns TRUE if list is full
{
	return false;

}// END IsFull

//---------------------------------------------------------------------------

ItemType ListClass::Retrieve() const //returns elmnt specified by currPos
{
	return list[currPos];

}// END Retrieve

//---------------------------------------------------------------------------

bool ListClass::Find( /*IN*/ KeyType target) // Value to search for
// sets PDM currPos to position of target..(or where it would be found)
{			
	// Hashing target value
	int hashKey = Hash(target);

	if(hashKey < SIZE) // If the hash key is within the range of the array...
	{

		if(list[hashKey].key != EMPTY_STRING) // If the hash key is not an empty string...
		{
			// Hash key is within the bounds of the array,
			// Current position set to hash key, return true
			currPos = hashKey;
			return true;

		} // END if
		else
		{
			// Hash key is empty string (does not exist)
			// Return false
			return false;

		} // END else

	} // END if
	else
	{
		// Hash key is outside bounds of array, return false
		return false;

	} // END else

} // END Find
		
//---------------------------------------------------------------------------

void ListClass::Insert(/*IN*/ ItemType newItem) // Item to be inserted
{	
	// Incrementing the total word count (non-unique) after each attempted insert.
	totWordCt++;

	//Running the item through the hash function to obtain the hash key
	int hashKey = Hash(newItem.key);


	if(list[hashKey].key == EMPTY_STRING) // If the key field contains an empty string, insert
	{

		uniqueWordCt++; // Incrementing the unique word count to indicate a new word inserted

		list[hashKey].wordCt++; // Incrementing the current key's word count

		list[hashKey].key = newItem.key; // Inserting the new key into the field

	} // END if
	else if(list[hashKey].key == newItem.key)
	{
		// If the current key to be inserted is the same as the key in the field
		list[hashKey].wordCt++; // Increment the word count for that key

	} // END else if
	else // Item must be chained to the current position in the array
	{

		// Temporary pointer to point to linked list
		ItemType* temp = list[hashKey].next;
		
		bool dupKey = false; // True if duplicate key value is found in linked list

		while(temp != nullptr && !dupKey)
		{
			if(temp->key == newItem.key)
			{
				// If the key to be inserted is equal to the key in the current position...
				dupKey = true;
				temp->wordCt++; // Word count incremented 

			} // END if

			// moving temp to the next position in the linked list
			temp = temp->next;

		} // END while



		if(!dupKey)
		{
			// If there is not a duplicate key...

			// Incrementing unique word & collision counter
			uniqueWordCt++;
			collisionCt++;

			// Unique word with non-unique key must be handled by the CRP
			CollisionResolution(hashKey, newItem);

		} // END if


	} // END else


} // END Insert		 
		
//---------------------------------------------------------------------------

void ListClass::Delete()	
// deletes record found at currPos
{	
	//Local Variables
  ItemType tempItem;
  tempItem.next = nullptr;
  tempItem.wordCt = 0;

  list[currPos] = tempItem;


}// END Delete
		
//---------------------------------------------------------------------------

void ListClass::Clear()
//clears list
{
	// Local variable declarations
	ItemType* temp; // Temporary pointer

	// Defaulting a temporary item to initial values
	ItemType tempItem; 
	tempItem.next = nullptr;
	tempItem.wordCt = 0;

	for(int i = 0; i < SIZE; i++) // Iterating through the list
	{
		if(list[i].next == nullptr)
		{
			// If the current index of array has no chains,
			// Reset the value in that index
			list[i] = tempItem;

		} // END if
		else
		{
			// If the current index of the array has chains,
			// Delete the chains
			while(list[i].next != nullptr)
			{
				temp = list[i].next;
				list[i].next = list[i].next->next;
				delete temp;

			} // END while

			// Reset the value in that index
			list[i] = tempItem;

		} // END else

	} // END for

	// Resetting values to default positions
	currPos = -1;        // Current position in array
	collisionCt = 0;     // Total number of collisions
	uniqueWordCt = 0;    // Total number of unique words
	totWordCt = 0;       // Total number of non-unique words

} // END Clear


//---------------------------------------------------------------------------

int ListClass::Hash(/*IN*/string word) // Word to be hashed
{


	// Local variable declarations
	int sum = 0;
	int hashKey = 0;
	bool add = true;
	_int8 lower;
	_int8 upper;

	srand(1234);
	int seed;

	if(word.length() > 1)
	{
		for(size_t i = 0; i < word.length()-1; i++)
		{
			seed = rand() % (SIZE / 5);
			upper = (int)word[i];
			lower = (int)word[i+1];

			__asm
			{
				push eax
				mov ah, upper
				mov al, lower
				xor ah, al
				mov byte ptr sum, al
				add byte ptr sum, ah
				pop eax

			} // END inline 

			hashKey += sum;
			hashKey += seed;

		} // END for

		hashKey += (int)word[word.length()-1];


	}
	else
	{
		hashKey = (int)word[0];
	}


	if(hashKey > SIZE-1)
	{
		hashKey = hashKey >> 1;
		if(hashKey > SIZE-1)
		{
			hashKey = hashKey >> 1;
			if(hashKey > SIZE-1)
			{
				hashKey = hashKey >> 1;
			}

		}
		
	}

	hashKey = hashKey % SIZE;

	return hashKey;


} // END Hash

//---------------------------------------------------------------------------

int ListClass::GetCollisions()
{
	return collisionCt;

} // END GetCollisions

//---------------------------------------------------------------------------

int ListClass::GetUniqueWordCount()
{
	return uniqueWordCt;

} // END GetUniqueWordCount

//---------------------------------------------------------------------------

int ListClass::GetTotalWordCount()
{
	return totWordCt;

} // END GetTotalWordCount

//---------------------------------------------------------------------------

void ListClass::CollisionResolution(/*IN*/int hashKey,      // Hash key to be resolved
	                                /*IN*/ItemType newItem) // Item to be inserted
{

	if(list[hashKey].next == nullptr)
	{
		// If the linked list is empty, append a new ItemType to the front 
		list[hashKey].next = new ItemType;

		// Inserting data into the new ItemType
		list[hashKey].next->key = newItem.key;

		// Setting the word count in the new field to 1
		list[hashKey].next->wordCt = 1;

		// Nulling the next field of the new position
		list[hashKey].next->next = nullptr;

	} // END if
	else
	{
		// Setting a temporary pointer the the front of the linked list
		ItemType* temp = list[hashKey].next;

		// Allocating a new ItemType to the front of the linked list
		list[hashKey].next = new ItemType;

		// Inserting a new item into the new node
		list[hashKey].next->key = newItem.key;

		// Setting the word count in the new field to 1
		list[hashKey].next->wordCt = 1;

		// Reconnecting the front of the list to the next position
		list[hashKey].next->next = temp;

	} // END else


} // END CollisionResolution

//---------------------------------------------------------------------------

/* TEMPORARY */
void ListClass::Print()
{
	for(int i = 0; i < SIZE; i++)
	{
		if(list[i].key == "")
		{
			cout << "[EMPTY]" << endl;
		}
		else
		{
			ItemType* temp = list[i].next;

			cout << "[" << list[i].key << "]";

			if(temp != nullptr)
			{
				while(temp != nullptr)
				{
					cout << "-->[" << temp->key << "]";

					temp = temp->next;
				}
			}
			
			cout << "\n";
		}
	}
}

//---------------------------------------------------------------------------

float ListClass::GetListOccupancy()
{
	float percentOcc; // Percent occupancy
	int occCt = 0;    // Counter for spaces in array occupied

	for(int i = 0; i < SIZE; i++)
	{
		if(list[i].key != EMPTY_STRING)
		{
			occCt++;
		} // END if

	} // END for

	// Calculating the percent occupancy
	percentOcc = ((float)occCt / (float)SIZE) * (float)PERCENT_MULTIPLIER;


	return percentOcc;

} // END GetListOccupancy
 
//---------------------------------------------------------------------------

void ListClass::PrintUniqueWords(/*IN/OUT*/FunctionType visit, // User defined function
	                             /*IN/OUT*/ofstream& dout)     // Output file variable
{
	ItemType item; // temporary item

	string output; // string to store the output to be sent to client

	// Iterating through the list
	for(int i = 0; i < SIZE; i++)
	{
		// If the key field is not empty
		if(list[i].key != EMPTY_STRING)
		{
			// Pointing a temporary pointer to the linked list in the array
			ItemType* temp = list[i].next;

			// Appending the word count to the key for final output
			output = list[i].key + SPACE + to_string(static_cast<long long>(list[i].wordCt)) + OUTPUT_MSG;

			// Sending the values back to the client
			visit(output, dout);

			// If temp is not null, iterate through the linked list
			if(temp != nullptr)
			{
				while(temp != nullptr)
				{
					// Appending the word count to the key for final output
					output = temp->key + SPACE + to_string(static_cast<long long>(temp->wordCt)) + OUTPUT_MSG;
					visit(output, dout);

					// Moving temp to the next position
					temp = temp->next;

				} // END while

			} // END if

		} // END if

	} // END for

}// END PrintUniqueWords







