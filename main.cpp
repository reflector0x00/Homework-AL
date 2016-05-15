#include <iostream>
#include <string>
#include <vector>
#include "voter.h"
#define VSVERSION "0.0.0" 
using namespace std;


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