
/**
 * You don't need to edit this file, although you can if you wish.
 * This source file will not be graded.
 * 
 * This is just an extra program you can use to debug your code.
 * Put whatever you want here, and use "make sandbox" to execute it.
 */

//
#include <iostream>
#include "MyHashTable.hpp"


//
using std::cout, std::cin, std::endl;


//
int main()
{
	//
	std::string s[5] {"bob", "bill", "ham", "billbop", "there"};
	unsigned long long int hash_int = 0;
	::CPSC131::MyHashTable::MyHashTable<std::string> table;

	table.setCapacity(1);

	for (auto itr : s) {
		table.add(itr, itr + "Value");
	}
	table.setCapacity(3);
		
	return 0;
}

