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
			for(size_t i=0; i<polls.size(); i++) {
				if(polls[i].getIndex(line)!=-1) {
					cout << "Voter allready exists" << endl;
					continue;
				}
			}
			polls[ind].push_back(voter(line));
		}
		else if(line=="list") {}
		else if(line=="remove") {}
		else if(line=="create") {}
		else if(line=="merge") {}
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
		else {}
	}
}