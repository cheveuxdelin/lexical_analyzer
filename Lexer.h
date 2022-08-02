#pragma once
#include "state.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <filesystem>
namespace fs = std::filesystem;

class Lexer
{
public:
	Lexer();
	Lexer(string states, string definitions);

	void analyze(fs::path path, string resultPath);
private:
	void loadStates(string filename);
	void loadRules(string filename);
	string createHTMLElement(string lex, State* state);
	unordered_map<string, State*> states;
	State* initialState;
	State* errorState;
	set<string> reservedWords;
};

