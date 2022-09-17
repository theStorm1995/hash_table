// Name: Nathan Storm 
// CWID: 885905158
// Email: nathanstorm95@csu.fullerton.edu

//
#include "MyRolodex.hpp"
#include "MyHashTable.hpp"
#include "Address.hpp"


/**
 * TODO: Finish the implementation for this class
 */


//	More includes?


//
namespace CPSC131::MyRolodex
{
	/// Your welcome
	MyRolodex::MyRolodex() {}
	
	/**
	 * Return true if a person exists in the Rolodex
	 */
	bool MyRolodex::exists(std::string name) const
	{
		//
		if(table_.exists(name)) {
			return true;
		}
		
		//
		return false;
	}
	
	/**
	 * Allow the user to add an address using its parts.
	 * This should probably just call on the other overload
	 */
	void MyRolodex::add(std::string name, std::string line1, std::string line2, std::string city, std::string state, int zip, std::string country)
	{
		//
		CPSC131::MyRolodex::Address address;

		//
		address.line1 = line1;
		address.line2 = line2;
		address.city = city;
		address.state = state;
		address.zip = zip;
		address.country = country;

		//
		this->add(name, address);
	}
	
	/**
	 * Add an entry into the Rolodex
	 * The person's name is the key, and their Address is the value.
	 * The Address comes in the form of the Address struct, defined in another source file.
	 */
	void MyRolodex::add(std::string name, Address address)
	{
		table_.add(name, address);
	}
	
	/**
	 * Return an address structure associated with a person
	 */
	Address MyRolodex::get(std::string name) const
	{
		return table_.get(name);
	}
	
	/**
	 * Remove a person from the Rolodex
	 */
	void MyRolodex::remove(std::string name)
	{
		table_.remove(name);
	}
	
	/**
	 * Clear the Rolodex of all information.
	 * (Hint: The table also has this method)
	 */
	void MyRolodex::clear()
	{
		table_.clear();
	}
	
	/**
	 * Return true if the Rolodex is empty, false otherwise
	 */
	bool MyRolodex::empty()
	{
		//
		if(table_.empty()) {
			return true;
		}

		//
		return false;
	}
	
	/**
	 * Return the number of entries in this Rolodex
	 */
	size_t MyRolodex::size()
	{
		return table_.size();
	}
}






















