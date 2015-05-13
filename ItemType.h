#ifndef item_h
#define item_h



#include <string>
using namespace std;

//DEFINE KEYTYPE : necessary for ordering of class
typedef string KeyType;

struct ItemType	
{		
	int wordCt;
	KeyType key;		// ID which will be used to order the class.
	ItemType* next;

  //string stuff		// Other elements in the list record will subsequently appear here for your client project

};


#endif
