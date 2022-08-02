#pragma once
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

class State
{
public:
	State();
	State(string definition, string className);

	void setRules(unordered_map<string, State*>* rules);

	void printRules();
	string getDefinition();
	State* getTransition(string rule);
	int getNumTransitions();
	string getClassName();
private:
	unordered_map<string, State*>* rules; // rule -> state
	string definition;
	string className;
};

