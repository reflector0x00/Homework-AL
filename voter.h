#pragma once
#include <string>
#include <stdexcept>
using namespace std;

class voteException : public exception {};

class voter {
	string name;
	string vote;
	public:
	voter();
	voter(string Name);
	void toVote(string voteName);
	string getVote();
	string getName();
	void reset();
	~voter();
};

