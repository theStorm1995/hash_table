
# Professor P Tests (PuhP Tests)

This is a simple framework for C++ unit testing, with the ability to output results in a format compatible with [Gradescope auto grading](https://gradescope-autograders.readthedocs.io/en/latest/).

# Copyright

Copyright 2022 Mike Peralta; All rights reserved - Except my students and colleagues, who may use this for homework and assignments.

Better license coming soon.

## Dependencies

Depends on the nlohmann::json library, which has been included in this repository (Licensed under the MIT License <http://opensource.org/licenses/MIT>).

## Usage

All classes and methods are contained in the single *PuhPTests.h* header file. Interesting classes are:

|Class         |Purpose|
|:-            |:-|
|Tests         |Main container for all tests. Only one instance is needed. Can generate useful output for the student/user or Gradescope.|
|Test          |Represents one unit test and contains convenience assertion methods that can adjust points earned. Can run multiple assertions per Test.|
|OutputCapture |An RAII-like class that attempts to capture stdout and stderr. On creation, begins capturing. Does not seem to work with subshell capture, such as calls to ```system```. Would probably work with popen or similar, if piped to ```cin``` and ```cerr```|

### Example

Here is a shortened version of a testing program made recently (2022-03-05). It grades units, outputs a *results.json* file for gradescope, outputs somewhat friendlier text for the student/user, and exits.

```cpp

//
#include <iostream>
#include <string>
#include <vector>

//
#include "Executor.hpp"
#include "Parser.hpp"
#include "puhp-tests/PuhPTests.h"

//
using std::cout, std::cin, std::endl;
using std::string;
using std::vector;

//
using PuhPTests::Tests, PuhPTests::Test, PuhPTests::OutputCapture;

//	PROTO
Test testArgumentParsing();

//
int main()
{
	//
	Parser parser;
	
	//
	cout << "Begin tests" << endl;
	
	//
	Tests tests;
	
	//
	vector<std::function<Test()>> functions = {
		testArgumentParsing
	};
	
	//
	for ( auto f : functions ) {
		tests << f();
	}
	
	cout << endl;
	
	cout << tests.getPassFailLogsAsString() << endl;
	
	//
	tests.writeResultsAsGradescopeJson();
	tests.printTestsSummary();
	
	//
	cout << "Tests complete" << endl;
	
	return 0;
}

//
Test testArgumentParsing()
{
	//
	Test t("Argument parsing");
	
	//
	Parser p;
	
	//
	t.assertNoException(
		[&t, p]()
		{
			//
			std::map<string, vector<string>> data;
			data["echo"] = vector<string>{"echo"};
			data["echo Hello"] = vector<string>{"echo", "Hello"};
			data["echo \"Hello\""] = vector<string>{"echo", "Hello"};
			data["echo Hello hey!"] = vector<string>{"echo", "Hello", "hey!"};
			data["echo \"Hello hey!\""] = vector<string>{"echo", "Hello hey!"};
			data["echo \"With inner quote \\\" there\""] = vector<string>{"echo", "With inner quote \" there"};
			data["echo \"With inner backslash \\\\ there\""] = vector<string>{"echo", "With inner backslash \\ there"};
			
			//
			for ( auto item : data) {
				
				//
				auto parsed = p.parseCommand(item.first.c_str());
				
				//
				t.assertEqual(parsed, item.second, 1, "Parsed vector should be correct for <<<" + item.first + ">>>");
				
				//
				cout << "Oh hi " << item.first << " ==> " << item.second.size() << endl;
			}
			
		}, 1, "No exceptions while testing argument parsing."
	);
	
	//
	t.assertNoException(
		[&t, p]()
		{
			//
			auto parts = p.parseCommand("weffiuh 3238737 wefiuhfh \"82828 22266\" yo");
			
			//
			OutputCapture capture;
			p.printParts(parts);
			
			//
			t.assertEqual(
				capture.getStdout(),
				"Parts:\n> [0] == weffiuh\n> [1] == 3238737\n> [2] == wefiuhfh\n> [3] == 82828 22266\n> [4] == yo\n",
				1,
				"Checking rendered argument list"
			);
			
			
		}, 1, "No exceptions while testing parsed argument rendering"
	);
	
	// Want an exception if we have an unterminated quote
	t.assertException(
		[&t, p]()
		{
			//
			p.parseCommand("echo \"Hello");
			
		}, 1, "Unterminated quote should throw an exception"
	);
	
	// Want an exception if we end on a backslash
	t.assertException(
		[&t, p]()
		{
			//
			p.parseCommand("echo \\");
			
		}, 1, "Backslash just before EOF should throw an exception"
	);
	
	return t;
}

```
