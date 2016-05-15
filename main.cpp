#include <iostream>
#include <string>
#include <vector>
#define VSVERSION "0.0.0" 
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


voter::voter() : name(""), vote("") {
	
}
voter::voter(string Name)  : name(Name), vote("") {
	
}
void voter::toVote(string v) {
	
}
string voter::getVote() {
	
}
voter::~voter() {
	
}

void printcopyright() {
	cout << "VoteSystem version " << VSVERSION << endl << "Copyright (C) 2016, ShiftDj" << endl << endl;
}

int main() {
	string line;
	printcopyright();
	while(1) {
		cout << "> ";
		getline(cin, line);
	}
}