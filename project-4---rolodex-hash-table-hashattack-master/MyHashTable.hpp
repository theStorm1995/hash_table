#ifndef MY_HASH_TABLE_HPP
#define MY_HASH_TABLE_HPP

// Name: Nathan Storm 
// CWID: 885905158
// Email: nathanstorm95@csu.fullerton.edu


/**
 * TODO: Complete this class!
 */


/// Your welcome
#include <forward_list>
#include <functional>
#include <memory>
#include <string>


//	More includes ... ?
#include <stdexcept>
#include <iostream>


///	Begin our class namespace
namespace CPSC131::MyHashTable
{
	//
	template<class VTYPE>
	class MyHashTable
	{
		//
		public:
			
			//
			static constexpr size_t DEFAULT_CAPACITY = 1024;
			static constexpr size_t ULLONG_WRAP_AT = 4294967295;
			
			/**
			 * Constructor
			 * 
			 * Probably easiest to do the following:
			 * 
			 *   1. Call on setCapacity() to set the table's capacity
			 */
			MyHashTable(size_t capacity = MyHashTable::DEFAULT_CAPACITY)
			{
				setCapacity(capacity);
			}
			
			/**
			 * Copy constructor
			 */
			MyHashTable(const MyHashTable& other)
			{
				// Copy the data 
	  			this->capacity_ = other.capacity_;
				this->size_ = other.size_; 
				this->n_collisions_ = other.n_collisions_;

				// Make a new table with the other tables capacity
				this->table_ = new std::forward_list<std::pair<std::string, VTYPE>>[this->capacity_];

				// Add all the values from the other table into the new one 
				for(size_t i = 0; i < this->capacity_ - 1; i++) {
					// 
					for(auto itr = other.table_[i].begin();
						itr != other.table_[i].end();
						itr++)
					{
						this->add((*itr).first, (*itr).second);
					} 
				}
			}
			
			/**
			 * Destructor
			 * 
			 * Deallocate the table (array of std::forward_list 's), and set the table to nullptr
			 * Don't double-deallocate if the table is already a null pointer
			 */
			~MyHashTable()
			{
 				if(table_ != nullptr) {
					this->clear();
					delete [] table_;
					table_ = nullptr;
				} 
			}
			
			/**
			 * Should return the capacity_ of this hash table
			 * Meaning, the total number of rows in this hash table
			 * Doesn't discern between used/unused/collided rows
			 */
			size_t capacity()
			{
				return capacity_;
			}
			
			/**
			 * Should return the number of items currently in the hash table
			 */
			size_t size()
			{
				return size_;
			}
			
			/**
			 * Return true if the table is empty, false otherwise
			 */
			bool empty()
			{
				if(size_ == 0) {
					return true;
				}
				return false;
			}
			
			/**
			 * Should return the number of collisions currently present in the hash table
			 */
			size_t n_collisions()
			{
				return n_collisions_;
			}
			
			/**
			 * Set the capacity for this table.
			 * Changes the total number of hash table rows available.
			 * 
			 * Existing entries should survive the change,
			 * 	so you probably want to do the following:
			 * 
			 *  1. Keep the existing table array pointer in a temporary pointer
			 *  
			 *  2. Re-initialize 'this' to contain a new empty table of the right capacity
			 *  
			 *  3. The temporary pointer should now contain the OLD data (old table),
			 *     while 'this' contains the brand new table of the new size.
			 * 
			 *  4. Iterate through all key/value pairs in the old data (temp pointer).
			 * 
			 *  5. For each key/value pair in the old data, call this->add() to insert
			 *     properly into the new table.
			 *  
			 *  6. Deallocate the old table by calling `delete []` on the temporary pointer.
			 * 
			 * Don't forget to check whether the current table is a nullptr before you
			 *  decide to do iterations!
			 */
			void setCapacity(size_t c)
			{
 				if (this->table_ != nullptr) {
					// Make a temp table thats equal to the current table
					std::forward_list<std::pair<std::string, VTYPE>> * temp_table = this->table_;
					auto temp_capacity = capacity_;

					// Create a new table with the new capacity 
					this->table_ = new std::forward_list<std::pair<std::string, VTYPE>>[c];
					this->capacity_ = c;
					this->size_ = 0;
					this->n_collisions_ = 0;

 					// Iterate down the array of Singly Linked Lists
					for(size_t i = 0; i < temp_capacity - 1; i++) {
						// Iterate through each list and add them to the new table
						for(auto itr = temp_table[i].begin();
							itr != temp_table[i].end();
							itr++)
						{
							this->add((*itr).first, (*itr).second);
						} 
					}

					// 
					delete [] temp_table;
					temp_table = nullptr;
				}
				else {
					this->table_ = new std::forward_list<std::pair<std::string, VTYPE>>[c];
				} 

				capacity_ = c;
			}
			
			///	Your welcome
			unsigned long long int hash(std::string key) const
			{
				return this->midSquareHash(key);
			}
			
			/**
			 * Implement the "modified mid square" hash function,
			 * as described in the instructions.
			 */
			unsigned long long int midSquareHash(std::string key) const
			{
				// Iterate thorough the string and change the chars to numbers
				// Then do a few arithmetic operations
				unsigned long long int hash_sum = 1;

				for (auto itr : key) {
					hash_sum *= static_cast<unsigned long long int>(itr);
					hash_sum %= ULLONG_WRAP_AT;
				}
				
				// Square's itself and then converts to string
				hash_sum *= hash_sum;
				std::string hash_string = std::to_string(hash_sum);

 				// Finds how long the sub string will be and the starting point 
				unsigned long long int sub_string_length = hash_string.length() / 2;
				unsigned long long int sub_string_start = sub_string_length / 2;

				// Creates substring
				hash_string = hash_string.substr(sub_string_start, sub_string_length);

				return (std::stoull(hash_string) % capacity_);
			}
			
			/**
			 * Implement your own custom hash functions to compete on the Gradescope Leaderboard!
			 * Four stubs are provided to make experimentation a little easier.
			 * Only the best hash function will count towards the leaderboard.
			 */
			unsigned long long int myCustomHashFunction1(std::string key) const
			{
				return 0;
			}
			unsigned long long int myCustomHashFunction2(std::string key) const
			{
				return 0;
			}
			unsigned long long int myCustomHashFunction3(std::string key) const
			{
				return 0;
			}
			unsigned long long int myCustomHashFunction4(std::string key) const
			{
				return 0;
			}
			
			/**
			 * Return true if a key exists in the table, or false otherwise.
			 */
			bool exists(std::string key) const
			{
				//
 				auto index = hash(key);
				std::forward_list<std::pair<std::string, VTYPE>> forward_list = table_[index];

				// Check if the key exists at its appropriate index
				for(auto itr = forward_list.begin(); itr != forward_list.end(); itr++) {
					//
					std::string pair_key = (*itr).first;

					//
					if(pair_key == key) {
						return true;
					}
				}

				//
				return false;
			}
			
			/**
			 * Add a key/value pair to this table.
			 * If the key already exists, throw a runtime_error.
			 */
			void add(std::string key, VTYPE value)
			{
				// Check if key exists
 				if (this->exists(key)) {
					throw std::runtime_error("Key already exists");
				} 

				// Get the index to store the pair and create the pair
				auto index = hash(key);
				std::pair<std::string, VTYPE> data = make_pair(key, value);

				// 
				if(!table_[index].empty()) {
					n_collisions_++;
				}

				//
				table_[index].push_front(data);
				size_++;
			}
			
			/**
			 * Should return a reference to the VTYPE value associated to the provided key.
			 * If the key/value pair isn't in the table, a runtime_error should be thrown.
			 */
			VTYPE& get(std::string key) const
			{
  				//
  				if(!this->exists(key)) {
					throw std::runtime_error("Key doesn't exist");
				}

				auto index = hash(key);

				// Find the key at the proper index
				for(auto itr = table_[index].begin();
					itr != table_[index].end();
					itr++)
				{
					//
					std::string pair_key = (*itr).first;

					//
					if(pair_key == key) {
						return (*itr).second;
					}
				}  
			}
			
			/**
			 * Remove a key/value pair that corresponds to the provided key.
			 * If no such key exists, throw a runtime_error.
			 */
			void remove(std::string key)
			{
				// Does the key exist?
   				if(!this->exists(key)) {
					throw std::runtime_error("Key doesn't exist");
				} 

				// Get the index where this key would be
  				auto index = hash(key);
				auto itr_prev = table_[index].before_begin();

				// Iterate through forward list to find the key
				for(auto itr = table_[index].begin(); itr != table_[index].end(); itr++) {
					//
					std::string pair_key = (*itr).first;

					//
					if(pair_key == key) {
						//
						table_[index].erase_after(itr_prev);

						//
						if(!table_[index].empty()) {
							n_collisions_--;
						}

						//
						size_--;
						break;
					}

					//
					itr_prev++;
				}   
			}
			
			/**
			 * Remove all entries in this table
			 * Iterate over each table row and call clear on the row's list
			 */
			void clear()
			{
				// Iterate through the table and clear all the lists. 
 				for(size_t i = 0; i < capacity_; i++) {
					table_[i].clear();
				} 

				//
				size_ = 0;
				n_collisions_ = 0;
			}
			
			/**
			 * Assignment Operator
			 */
			MyHashTable<VTYPE>& operator=(const MyHashTable<VTYPE>& other)
			{
				//
	  			this->capacity_ = other.capacity_;
				this->size_ = other.size_; 
				this->n_collisions_ = other.n_collisions_;

				//
				this->table_ = new std::forward_list<std::pair<std::string, VTYPE>>[this->capacity_];

				//
				for(size_t i = 0; i < this->capacity_ - 1; i++) {
					//
					for(auto itr = other.table_[i].begin();
						itr != other.table_[i].end();
						itr++)
					{
						this->add((*itr).first, (*itr).second);
					} 
				}

				//
				return *this;
			}
			
		//
		private:
			
			/**
			 * Keeps track of the capacity of this hash table
			 * (total number of rows in the table, whether used or not)
			 * (does not care about collisions)
			 */
			size_t capacity_ = 0;
			
			/**
			 * Keeps track of the total number of items currently in
			 * the hash table
			 */
			size_t size_ = 0;
			
			/**
			 * Keeps track of the number of collisions currently present in the table
			 */
			size_t n_collisions_ = 0;
			
			/**
			 * The actual hash table.
			 * We'll make this a fixed-sized array,
			 *   but dynamically allocated so we can resize whenever we need.
			 * 
			 * Try to imagine each table row is actually a complete forward_list.
			 * In a perfect situation where a table has no collisions, each list
			 *   will simply contain one item.
			 * 
			 * One "item" in this case refers to an std::pair<std::string, VTYPE>,
			 *   where the first part of the pair is the key and the second
			 *   is the value (of type VTYPE).
			 */
			std::forward_list<std::pair<std::string, VTYPE>> * table_ = nullptr;	
	};
}













#endif
