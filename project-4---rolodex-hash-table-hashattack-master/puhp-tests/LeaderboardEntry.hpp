#ifndef PUHP_TESTS_LEADERBOARD_ENTRY_H
#define PUHP_TESTS_LEADERBOARD_ENTRY_H


//
#include "./deps/json.hpp"


//
#include "./Enums.hpp"


//
#include <stdexcept>
#include <string>


//
namespace PuhPTests
{
	//
	class LeaderboardEntry
	{
		//
		public:
			
			//
			LeaderboardEntry() {}
			
			//
			LeaderboardEntry(std::string name, std::string value)
			{
				//
				this->setName(name);
				this->setValue(value);
			}
			
			//
			void setName(std::string name) { this->name_ = name; }
			std::string getName() const { return this->name_; }
			
			void setValue(std::string value) { this->value_ = value; }
			std::string getValue() const { return this->value_; }
			
			//
			nlohmann::json toGradescopeJson() const
			{
				//
				nlohmann::json j;
				
				//
				j["name"] = this->getName();
				j["value"] = this->getValue();
				
				return j;
			}
			
		//
		private:
			
			//
			std::string name_, value_;
	};
}








#endif
