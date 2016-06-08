#include <iostream>
#include <sstream>
#include <vector>
#include "poll.h"
#include "election.h"
#define VSVERSION "0.1.0" 
using namespace std;

/**
	Выводит приветствующие сообщение.
*/
void printcopyright() {
	cout << "VoteSystem version " << VSVERSION << endl << "Copyright (C) 2016, ShiftDj" << endl << endl;
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
			if(current->getState()!=0) {
				cout << "Election is already started or finished" << endl; 
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
			if(current->getState()!=0) {
				cout << "Election is already started or finished" << endl; 
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
			current = new election;
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
				switch(current->getState()) {
					case 0:
					cout << "Election isn't started" << endl;
					break;
					
					case 2:
					cout << "Election is already finished" << endl;
					break;
				}
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
				size_t* winners = current->finish(polls, n);
				if(winners==nullptr) {
					cout << "But nobody voted, so nobody won" << endl;
				}
				if(n==1) {
					cout << (*current)[winners[0]]->getName() << " won" << endl;
				}
				else {
					cout << "Winners are: " << endl;
					for(size_t i=0; i<n; i++)
						cout << '\t' << (*current)[winners[i]]->getName() << endl;
				}
			} catch(electionException e) {
				cout << "Election isn't started or already finished" << endl;
			}
		}
		else if(line=="reset") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			delete current;
			current = nullptr;
			for(size_t i=0; i<polls.size(); i++)
				polls[i].reset();
		}
		else if(line=="vote") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			if(current->getState()!=1) {
				cout << "Election wasn't started" << endl; 
				continue;
			}
			size_t ind1 = -1;
			size_t ind2 = -1;
			string line2;
			ss >> line >> line2;
			ind2 = current->getIndex(line2);
			if(ind2==-1) {
				cout << "Candidate not found" << endl;
				continue;
			}
			for(size_t i=0; i<polls.size(); i++) {
				ind1 = polls[i].getIndex(line);
				if(ind1!=-1)  {
					try {
						polls[i][ind1].toVote(line2);
					} catch(voteException e) {
						cout << line << " already voted" << endl;
					}
					break;
				}
			}
			if(ind1==-1) {
				cout << "Voter not found" << endl;
				continue;
			}
		}
		else if(line=="status") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			switch(current->getState()) {
				case 0:
				cout << "Election isn't started" << endl;
				break;
				
				case 1:
				cout << "Election started" << endl;
				break;
				
				case 2:
				cout << "Election is finished" << endl;
				break;
			}
		}
		else if(line=="stats") {
			if(current==nullptr) {
				cout << "There isn't election" << endl;
				continue;
			}
			if(current->getState()!=2) {
				cout << "Election wasn't finished" << endl; 
				continue;
			}
			ss >> line;
			if(line == "poll") {
				int ind = -1;
				ss >> line;
				for(size_t i=0; i<polls.size(); i++) 
					if(polls[i].getName()==line)  {
						ind = i;
						break;
					}
				if(ind==-1) {
					cout << "Poll not found" << endl;
					continue;
				}
				for(size_t i=0; i<polls[ind].size(); i++) 
					if(polls[ind][i].getVote()!="") 
						cout << polls[ind][i].getName() << " voted for " << polls[ind][i].getVote() << endl;
				
			}
			else if(line == "voter") {
				int ind=-1;
				ss >> line;
				for(size_t i=0; i<polls.size(); i++) {
					ind = polls[i].getIndex(line);
					if(ind!=-1)  {
						if(polls[i][ind].getVote()!="") 
							cout << line << " voted for " << polls[i][ind].getVote() << endl;
						else
							cout << line << " didn't voted" << endl;
						break;
					}
				}
			}
			else if(line == "candidate") {
				ss >> line;
				size_t ind = current->getIndex(line);
				if(ind!=-1) 
					cout	<< line << " has " << current->getVotes(ind) << " votes" << endl
						<< "This is " << ((double)current->getVotes(ind))/current->getAll() << "% of all votes" << endl;
				else 
					cout << "Candidte not found" << endl;
			}
			else if(line=="all") {
				for(size_t i=0; i<polls.size(); i++) {
					for(size_t j=0; j<polls[i].size(); j++) {
						if(polls[i][j].getVote()!="") 
							cout <<  polls[i][j].getName() << " voted for " << polls[i][j].getVote() << endl;
						else
							cout << polls[i][j].getName() << " didn't voted" << endl;
					}
				}
				for(size_t i=0; i<current->size(); i++) 
					cout	<< (*current)[i]->getName() << " has " << current->getVotes(i) << " votes"  << endl
						<< "This is " << ((double)current->getVotes(i))/current->getAll() << "% of all votes" << endl;
			}
			else {
				cout << "stats [poll/voter/candidate/all]" << endl;
			}
		}
		else if(line=="save") {
			ss >> line;
			ofstream file(line);
			if(!file.is_open()) {
				cout << "Could not be opened" << endl;
				continue;
			}
			file << polls.size() << endl;
			for(size_t i=0; i<polls.size(); i++)
				polls[i].save(file);
			file.close();
		}
		else if(line=="open") {
			ss >> line;
			ifstream file(line);
			if(!file.is_open()) {
				cout << "Could not be opened" << endl;
				continue;
			}
			polls.clear();
			size_t size1, size2;
			file >> size1;
			for(size_t i=0; i<size1; i++) {
				file >> size2 >> line;
				poll temp(line);
				for(size_t j=0; j<size2; j++) {
					file >> line;
					temp.push_back(voter(line));
				}
				polls.push_back(temp);
			}
			file.close();
		} 
		else if(line=="quit") 
			break;
		else {
			cout << "Unknown command" << endl;
		}
	}
	return 0;
}