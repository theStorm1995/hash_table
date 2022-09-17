#ifndef PUHP_TESTS_LEADERBOARD_H
#define PUHP_TESTS_LEADERBOARD_H


//
#include "./deps/json.hpp"


//
#include "./Enums.hpp"
#include "./LeaderboardEntry.hpp"


//
#include <map>
#include <stdexcept>
#include <string>


//
namespace PuhPTests
{
	//
	class Leaderboard
	{
		//
		public:
			
			//
			Leaderboard() {}
			
			//
			Leaderboard(std::string sort_key)
			{
				this->sort_key_ = sort_key;
			}
			
			//
			Leaderboard(std::string sort_key, LeaderboardSortDirection sort_direction)
			{
				this->sort_key_ = sort_key;
				this->sort_direction_ = sort_direction;
			}
			
			//
			Leaderboard(const Leaderboard& other)
			{
				this->copyOther(other);
			}
			
			//
			void addEntry(std::string name, std::string value)
			{
				LeaderboardEntry entry(name, value);
				this->addEntry(entry);
			}
			void addEntry(std::string name, int value)
			{
				this->addEntry(name, std::to_string(value));
			}
			void addEntry(std::string name, long value)
			{
				this->addEntry(name, std::to_string(value));
			}
			void addEntry(std::string name, size_t value)
			{
				this->addEntry(name, std::to_string(value));
			}
			
			//
			void addEntry(const LeaderboardEntry& entry)
			{
				//
				this->entries_[entry.getName()] = entry;
				
				//
				if ( this->sort_key_.empty() ) {
					this->sort_key_ = entry.getName();
				}
			}
			
			//
			void setSortKey(std::string k) { this->sort_key_ = k; }
			std::string getSortKey() const { return this->sort_key_; }
			
			//
			static std::string sortDirectionToString(LeaderboardSortDirection d)
			{
				switch(d)
				{
					case LeaderboardSortDirection::Ascending:
						return "Ascending";
					
					case LeaderboardSortDirection::Default:
						return "Default";
					
					case LeaderboardSortDirection::Descending:
						return "Descending";
				}
				
				throw std::runtime_error("Unsupported Leaderboard sort direction");
			}
			static std::string sortDirectionToGradescopeString(LeaderboardSortDirection d)
			{
				switch(d)
				{
					case LeaderboardSortDirection::Ascending:
						return "asc";
					
					case LeaderboardSortDirection::Default:
						return "desc";
					
					case LeaderboardSortDirection::Descending:
						return "desc";
				}
				
				throw std::runtime_error("Unsupported Leaderboard sort direction");
			}
			
			//
			void setSortDirection(LeaderboardSortDirection d)
			{
				switch(d)
				{
					case LeaderboardSortDirection::Ascending:
					case LeaderboardSortDirection::Default:
					case LeaderboardSortDirection::Descending:
						this->sort_direction_ = d;
						return;
				}
				
				throw std::runtime_error("Unsupported Leaderboard sort direction: " + Leaderboard::sortDirectionToString(d));
			}
			LeaderboardSortDirection getSortDirection() const { return this->sort_direction_; }
			std::string getSortDirectionAsString() const
			{
				return Leaderboard::sortDirectionToString( this->getSortDirection() );
			}
			std::string getSortDirectionAsGradescopeString() const
			{
				return Leaderboard::sortDirectionToGradescopeString( this->getSortDirection() );
			}
			
			//
			nlohmann::json toGradescopeJson() const
			{
				//
				nlohmann::json j;
				
				//
				bool found_sort_key = false;
				for ( auto itr : this->entries_ ) {
					
					//
					std::string name = itr.first;
					LeaderboardEntry entry = itr.second;
					
					//
					auto jj = entry.toGradescopeJson();
					
					//
					if ( entry.getName() == this->sort_key_ ) {
						
						//
						found_sort_key = true;
						
						//
						jj["order"] = this->getSortDirectionAsGradescopeString();
					}
					
					j.push_back(jj);
				}
				
				//
				if ( found_sort_key == false ) {
					throw std::runtime_error("Did not find sort key while rendering Leaderboard entries");
				}
				
				return j;
			}
			
			//
			Leaderboard& operator=(const Leaderboard& other)
			{
				return this->copyOther(other);
			}
			
		
		//
		private:
			
			//
			std::map<std::string, LeaderboardEntry> entries_;
			
			std::string sort_key_;
			LeaderboardSortDirection sort_direction_ = LeaderboardSortDirection::Default;
			
			//
			Leaderboard& copyOther(const Leaderboard& other)
			{
				//
				this->entries_ = other.entries_;
				this->sort_key_ = other.sort_key_;
				this->sort_direction_ = other.sort_direction_;
				
				return *this;
			}
	};
}








#endif
