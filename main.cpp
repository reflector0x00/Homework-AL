#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "voter.h"
#define VSVERSION "0.0.0" 
using namespace std;


void printcopyright() {
	cout << "VoteSystem version " << VSVERSION << endl << "Copyright (C) 2016, ShiftDj" << endl << endl;
}

void printHelp() {
	cout << "";
}

class poll : public vector<voter> {
	string name;
	public:
	poll();
	poll(const poll& o);
	poll(string Name);
	string getName();
	int getIndex(string VoterName);
	~poll();
};

poll::poll() : vector<voter>(), name("") {}
poll::poll(const poll& o) : vector<voter>(o), name(o.name) {}
poll::poll(string Name) : vector<voter>(), name(Name) {}

string poll::getName() {
	return name;
}
int poll::getIndex(string VoterName) {
	for(size_t i = 0; i<size(); i++) {
		if((*this)[i].getName()==VoterName)
			return i;
	}
	return -1;
}

poll::~poll() {}

class electionException : public exception {};

class election : public vector<voter*> {
	size_t state;
	size_t *votes;
	size_t maximum;
	public:
	election();
	election(const election& o);
	int getIndex(string VoterName);
	void start();
	size_t* finish(size_t& n);
	size_t getState();
	size_t getMaximum();
	~election();
};

election::election() : vector<voter*>(), stat(0), votes(nullptr), maximum(0) {}
election::election(const election& o) : vector<voter*>(o), stat(0), votes(nullptr), maximum(0) {}
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

size_t* election::finish(size_t& n) {
	if(state!=1) 
		throw electionException();
	state = 2;
	
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
	n = nds.size();
	return winners;
}

size_t election::getState() {
	return state;
}

size_t election::getMaximum() {
	return maximum;
}


election::~election() {
	if(votes!=nullptr)
		delete [] votes;
}

int main() {
	vector<poll> polls;
	election* current = nullptr;
	string line;
	printcopyright();
	while(1) {
		cout << "> ";
		getline(cin, line);
		stringstream ss(line);
		ss >> line;
		if(line == "add") {
			int ind = -1;
			ss >> line;
			for(size_t i=0; i<polls.size(); i++) {
				if(polls[i].getName()==line) {
					ind = i;
					break;
				}
			}
			if(ind==-1) {
				cout << "Poll not found" << endl;
				continue;
			}
			ss >> line;
			size_t i;
			for(i=0; i<polls.size(); i++) {
				if(polls[i].getIndex(line)!=-1)
					break;
			}
			if(i!=polls.size()) {
				cout << "Voter allready exists" << endl;
				continue;
			}
			polls[ind].push_back(voter(line));
		}
		else if(line=="remove") {
			size_t ind;
			ss >> line;
			for(size_t i=0; i<polls.size(); i++) { 
				ind = polls[i].getIndex(line);
				if(ind!=-1) {
					polls[i].erase(polls[i].begin() + ind);
					break;
				}
			}
			if(ind==-1) 
				cout << "Voter not found" << endl;
		}
		else if(line=="list") {
			for(size_t i=0; i<polls.size(); i++) {
				cout << polls[i].getName() << ':' << endl;
				for(size_t j=0; j<polls[i].size(); j++)
					cout << '\t' << polls[i][j].getName() << endl;
			}
		}
		else if(line=="create") {
			ss >> line;
			size_t i;
			for(i=0; i<polls.size(); i++) { 
				if(polls[i].getName()==line) 
					break;
			}
			if(i!=polls.size()) {
				cout << "Poll already exists" << endl;
				continue;
			}
			polls.push_back(poll(line));
		}
		else if(line=="merge") {
			size_t ind1 = -1;
			size_t ind2 = -1;
			string line2;
			ss >> line >> line2;
			for(size_t i=0; i<polls.size(); i++) {
				if(polls[i].getName()==line) 
					ind1 = i;
				else if(polls[i].getName()==line2) 
					ind2 = i;
				if((ind1!=-1)&&(ind2!=-1))
					break;
				
			}
			if(ind1==-1) {
				cout << "First poll not found" << endl;
				continue;
			}
			else if(ind2==-1) {
				cout << "Second poll not found" << endl;
				continue;
			}
			for(size_t i=0; i<polls[ind1].size(); i++) {
				polls[ind2].push_back(polls[ind1][i]);
			}
			polls.erase(polls.begin() + ind1);
		}
		else if(line=="delete") {
			int ind = -1;
			ss >> line;
			for(size_t i=0; i<polls.size(); i++) {
				if(polls[i].getName()==line) {
					ind = i;
					break;
				}
			}
			if(ind==-1) {
				cout << "Poll not found" << endl;
				continue;
			}
			polls.erase(polls.begin() + ind);
		}
		else if(line=="register") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			size_t ind;
			ss >> line;
			for(size_t i=0; i<polls.size(); i++) { 
				ind = polls[i].getIndex(line);
				if(ind!=-1) {
					current->push_back(&polls[i][ind]);
					break;
				}
			}
			if(ind==-1) 
				cout << "Voter not found" << endl;
			
		}
		else if(line=="recall") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			ss >> line;
			size_t ind = current->getIndex(line);
			if(ind!=-1)
				current->erase(current->begin() + ind);
			else 
				cout << "Candidte not found" << endl;
		}
		else if(line=="init") {
			if(current!=nullptr) {
				cout << "Election already exists" << endl;
				continue;
			}
		}
		else if(line=="start") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			if(current->size()==0) {
				cout << "There aren't any candidtes" << endl;
				continue;
			}
			try {
				current->start();
			} catch(electionException e) {
				cout << "Election is already started or finished" << endl;
				continue;
			}
		}
		else if(line=="finish") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			try {
				size_t n;
				size_t* winners = current->finish(n);
				if(winners==nullptr) {
					cout << "But nobody voted, so nobody won" << endl;
				}
				if(n==1) {
					cout << (*current)[winners[0]].getName() << " won" << endl;
				}
				else {
					cout << "Winners are: " << endl;
					for(size_t i=0; i<n; i++)
						cout << '\t' << (*current)[winners[i]].getName() << endl;
				}
			} catch(electionException e) {
				cout << "Election isn't started or already finished" << endl;
				continue;
			}
		}
		else if(line=="reset") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			delete current;
			current = nullptr;
		}
		else if(line=="vote") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			size_t ind1 = -1;
			size_t ind2 = -1;
			string line2;
			ss >> line >> line2;
			for(size_t i=0; i<current->size(); i++) 
				if((*current)[i]->getName()==line2) { 
					ind2 = i;
					break;
				}
			else if(ind2==-1) {
				cout << "Candidate not found" << endl;
				continue;
			}
			for(size_t i=0; i<polls.size(); i++) {
				ind1 = polls[i].getIndex(line);
				if(ind1!=-1)  {
					try {
						polls[i][ind1].toVote(line2);
					} catch(voteException e) {
						cout << line1 << " already voted" << endl;
					}
					break;
				}
			}
			if(ind1==-1) {
				cout << "Voter not found" << endl;
				continue;
			}
		}
		else if(line=="stats") {
			
		}
		else if(line=="stats") {}
		else if(line=="stat") {}
		else if(line=="help") {}
		else if(line=="quit") 
			break;
		else {
			cout << "Unknown command" << endl;
		}
	}
	return 0;
}