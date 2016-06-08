#include "election.h"



election::election() : vector<voter*>(), state(0), votes(nullptr), maximum(0), all(0) {}
election::election(const election& o) : vector<voter*>(o), state(0), votes(nullptr), maximum(0), all(0) {}
int election::getIndex(string VoterName) {
	for(size_t i = 0; i<size(); i++) {
		if((*this)[i]->getName()==VoterName)
			return i;
	}
	return -1;
}

void election::start() {
	if(state!=0) 
		throw electionException();
	state = 1;
	votes = new size_t[size()];
	memset(votes, 0, size()*sizeof(size_t));
}

size_t* election::finish(vector<poll> &polls, size_t& n) {
	if(state!=1) 
		throw electionException();
	state = 2;
	
	for(size_t i=0; i<polls.size(); i++) 
		for(size_t j=0; j<polls[i].size(); j++) {
			string v = polls[i][j].getVote();
			if(v!="") {
				votes[getIndex(v)]++;
				all++;
			}
		}
	
	
	for(size_t i=0; i<size(); i++) {
		if(votes[i]>maximum) 
			maximum = votes[i];
	}
	if(maximum==0)
		return nullptr;
	vector <size_t> inds;
	for(size_t i=0; i<size(); i++) {
		if(votes[i]==maximum)
			inds.push_back(i);
	}
	size_t* winners = new size_t[inds.size()];
	for(size_t i=0; i<inds.size(); i++) 
		winners[i] = inds[i];
	n = inds.size();
	return winners;
}

size_t election::getState() {
	return state;
}

size_t election::getMaximum() {
	return maximum;
}

size_t election::getAll() {
	return all;
}

size_t election::getVotes(size_t i) {
	return votes[i];
}


election::~election() {
	if(votes!=nullptr)
		delete [] votes;
}