#include "voter.h"


voter::voter() : name(""), vote("") {
	
}

voter::voter(string Name)  : name(Name), vote("") {
	
}

void voter::toVote(string voteName) {
	if(vote!="")
		throw voteException();
	vote = voteName;
}
string voter::getVote() {
	return vote;
}
string voter::getName() {
	return name;
}
void voter::reset() {
	vote="";
}
voter::~voter() {
	
}