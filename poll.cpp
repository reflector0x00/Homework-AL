#include "poll.h"

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

void poll::reset() {
	for(size_t i=0; i<size(); i++)
		(*this)[i].reset();
}

void poll::save(ofstream& file) {
	file << size() << " " << name << " ";
	for(size_t i=0; i<size(); i++)
		file << (*this)[i].getName() << " ";
	file << endl;
}

poll::~poll() {}