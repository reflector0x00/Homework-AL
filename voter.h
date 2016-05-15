#pragma once
#include <string>
using namespace std;

class voter {
	string name;
	string vote;
	public:
	voter();
	voter(string Name);
	void toVote(string v);
	string getVote();
	~voter();
};

