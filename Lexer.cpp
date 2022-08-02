#include "Lexer.h"

//DEFAULT CONSTRUCTOR
Lexer::Lexer()
{
	this->initialState = nullptr;
	this->errorState = nullptr;
	reservedWords.insert("define");
}

//CONSTRUCTOR WITH ARGUMENTS
Lexer::Lexer(string states, string definitions)
{
	loadStates(definitions);
	loadRules(states);
	this->initialState = this->states["q0"];
	this->errorState = this->states["q-1"];
	reservedWords.insert("define");
}

//LOAD DEFINITIONS
void Lexer::loadStates(string filename)
{
	ifstream file(filename);
	string line;
	string statename;
	string definition;
	string color;
	while (getline(file, line))
	{
		stringstream ss(line);
		getline(ss, statename, ',');
		getline(ss, definition, ',');
		getline(ss, color);
		this->states.emplace(statename, new State(definition, color));
	}
	file.close();
}

//LOAD RULES
void Lexer::loadRules(string filename)
{
	//LOAD FILE
	ifstream file(filename);
	string line;
	string s;

	//TRANSITIONS
	vector<string> transitions;
	getline(file, line);
	stringstream ss(line);
	while (getline(ss, s, ','))
	{
		transitions.push_back(s);
	}

	//RULES
	while (getline(file, line))
	{
		unordered_map<string, State*>* rules = new unordered_map<string, State*>;
		stringstream ss(line);

		//STATE NAME
		string statename;
		getline(ss, statename, ',');

		int pos = 0;
		while (getline(ss, s, ','))
		{
			pos += 1;
			if (s != "")
			{
				rules->emplace(transitions[pos], this->states[s]);
			}
		}
		states[statename]->setRules(rules);
	}
	file.close();
}

//ANALYZER
void Lexer::analyze(fs::path path, string resultPath)
{
	string filePath = resultPath + "/" + path.stem().string() + ".html";
	//string filePath = resultPath + "/" + "a" + ".html";

	ofstream os(filePath);
	os << "<!DOCTYPE html>\n";
	os << "<html>\n";
	os << "\t<head>\n";
	os << "\t\t<link rel=\"stylesheet\" href=\"styles.css\">\n";
	os << "\t\t<title>Lexical Analyzer</title>\n";
	os << "\t</head>\n";
	os << "\t<body>\n";
	os << "\t\t<h1>SCHEME LEXICAL ANALYZER</H1>\n";
	

	//OPENING FILE
	ifstream file(path.string());
	string line;
	char read; //FOR CONVERTING TO STRING
	while (getline(file, line))
	{
		os << "\t\t";
		vector<vector<string>> fileLine;
		stringstream ss(line);
		State* currentState = this->initialState;
		string lex = "";
		string l = "";
		while (ss.get(read))
		{
			l = string(1, read);
			State* nextState = currentState->getTransition(l);

			//COMMENT
			if (currentState->getDefinition() == "comment")
			{
				//SPACE
				if (l == " ")
				{
					lex = lex + "&nbsp";
				}
				//TAB
				else if (l == "\t")
				{
					lex = lex + "&nbsp&nbsp&nbsp&nbsp";
				}
				//ELSE
				else
				{
					lex = lex + l;
				}
			}
			//SPACE
			else if (l == " ")
			{
				//EMPTY LEX, ADD SPACE
				if (lex == "")
				{
					os << "&nbsp";
				}
				//ELSE, ADD LEX
				else
				{
					os << createHTMLElement(lex, currentState);
					currentState = initialState;
					lex = "";
					ss.unget();
				}
			}
			//TAB
			else if (l == "\t")
			{
				//EMPTY LEX, ADD TAB
				if (lex == "")
				{
					os << "&nbsp&nbsp&nbsp&nbsp";
				}
				//ELSE, ADD LEX
				else
				{
					os << createHTMLElement(lex, currentState);
					currentState = initialState;
					lex = "";
					ss.unget();
				}
			}
			//SYMBOL
			else if (currentState->getDefinition() == "symbol")
			{
				lex = lex + l;
			}
			//NULL TRANSITION
			else if (nextState == nullptr)
			{
				//CHAR NOT RECOGNIZED
				if (initialState->getTransition(l) == nullptr)
				{
					//UNARY STATES
					if (currentState->getNumTransitions() == 0 || lex ==  "-")
					{
						os << createHTMLElement(lex, currentState);
						currentState = initialState;
						lex = "";
						ss.unget();
					}
					//ELSE -> ERROR
					else
					{
						lex = lex + l;
						currentState = errorState;
					}
				}
				//LOGIC STATE
				else if (currentState->getDefinition() == "logic" && initialState->getTransition(l)->getNumTransitions() > 0 && l != "-" && l != ";")
				{
					lex = lex + l;
					currentState = errorState;
				}
				//UNARY STATES AND STATE EXCEPTIONS
				else if (currentState->getNumTransitions() == 0 || initialState->getTransition(l)->getNumTransitions() == 0 || lex == "-" || l == "-" || l == ";")
				{
					os << createHTMLElement(lex, currentState);
					currentState = initialState;
					lex = "";
					ss.unget();
				}
				//ELSE -> ERROR
				else
				{
					lex = lex + l;
					currentState = errorState;
				}
			}
			//TRANSITION
			else
			{
				lex = lex + l;
				currentState = nextState;
			}
		}
		//END OF LINE
		if (lex != "")
		{
			os << createHTMLElement(lex, currentState);
		}
		os << "<br>";
		os << "\n";	
	}
	os << "\t</body>\n";
	os << "</html>";
}

string Lexer::createHTMLElement(string lex, State* state)
{
		//RESERVED WORDS
		if (this->reservedWords.find(lex) != reservedWords.end())
		{
			return "<span class=" + this->states["q15"]->getClassName() + ">" + lex + "</span>";
		}
		//ELSE
		else
		{
			 
		}
		{
			return "<span class=" + state->getClassName() + ">" + lex + "</span>";
		}
}