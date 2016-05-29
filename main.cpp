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


int main() {
	vector<poll> polls;
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
		else if(line=="delete") {}
		else if(line=="register") {}
		else if(line=="recall") {}
		else if(line=="init") {}
		else if(line=="start") {}
		else if(line=="finish") {}
		else if(line=="reset") {}
		else if(line=="vote") {}
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