/**
	@file
	@brief Файл исходного кода для класса выборов
*/
#include "election.h"

election::election() : vector<voter*>(), state(0), votes(nullptr), maximum(0), all(0) {
	
}

/**
	@brief Конструктор копирования класса
	@param o Объект копирования
*/
election::election(const election& o) : vector<voter*>(o), state(0), votes(nullptr), maximum(0), all(0) {
	
}

/**
	@brief Возвращает индекс указателя на избирателя по заданному имени
	@param VoterName Имя избирателя
	@return Индекс указателя на избирателя с заданным именем или -1, если такой отсутствует 
*/
int election::getIndex(string VoterName) {
	for(size_t i = 0; i<size(); i++) {
		if((*this)[i]->getName()==VoterName)
			return i;
	}
	return -1;
}

/**
	@brief Начинает проведение выборов
	@throw electionException В случае неправильного состояния выборов
*/
void election::start() {
	if(state!=0) 
		throw electionException();
	state = 1;
	votes = new size_t[size()];
	memset(votes, 0, size()*sizeof(size_t));
}

/**
	@brief Завершает проведение выборов и возвращает победителей
	@param [in] polls Вектор избирательных участков, избератели которых проголосовали за кандидатов выборов
	@param [out] n Количество победителей выборов
	@return Массив индексов указтелей на победителей выборов
	@throw electionException В случае неправильного состояния выборов
*/
size_t* election::finish(vector<poll>& polls, size_t& n) {
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

/**
	@brief Возвращает состояние выборов
	@return Состояние выборов
	0 Выборы не начаты
	1 Выборы были начаты
	2 Выборы завершены
*/
size_t election::getState() {
	return state;
}

/**
	@brief Возвращает количество голосов у победителей
	@return Количество голосов у победителей
*/
size_t election::getMaximum() {
	return maximum;
}

/**
	@brief Возвращает общее число голосов
	@return Общее число голосов
*/
size_t election::getAll() {
	return all;
}

/**
	@brief Возвращает количество голосов за указаного кандидата
	@param i Индекс кандидата
	@return Количество голосов за указаного кандидата
*/
size_t election::getVotes(size_t i) {
	return votes[i];
}


election::~election() {
	if(votes!=nullptr)
		delete [] votes;
}