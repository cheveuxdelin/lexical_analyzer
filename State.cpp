#include "State.h"

State::State()
{
	this->definition = "";
	this->className = "";
	this->rules = nullptr;
}

State::State( string definition, string className)
{
	this->definition = definition;
	this->className = className;
}

void State::setRules(unordered_map<string, State*>* rules)
{
	this->rules = rules;
}

void State::printRules()
{
	if (rules != nullptr)
	{
		for (auto i = rules->begin(); i != rules->end(); i++)
		{
			cout << i->first << " " << i->second->getDefinition() << endl;
		}
	}
	
}


string State::getDefinition()
{
	return this->definition;
}

State* State::getTransition(string rule)
{
	//POR QUE FUNCIONA ASI?
	if (rules->find(rule) == rules->end())
	{
		return nullptr;
	}
	else
	{
		return (*rules)[rule];
	}
}

int State::getNumTransitions()
{
	return rules->size();
}

string State::getClassName()
{
	return this->className;
}
