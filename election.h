#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "voter.h"
#include "poll.h"
using namespace std;

class electionException : public exception {};

class election : public vector<voter*> {
	size_t state;
	size_t *votes;
	size_t maximum;
	size_t all;
	public:
	election();
	election(const election& o);
	int getIndex(string VoterName);
	void start();
	size_t* finish(vector<poll> &polls, size_t& n);
	size_t getState();
	size_t getMaximum();
	size_t getVotes(size_t i);
	size_t getAll();
	~election();
};