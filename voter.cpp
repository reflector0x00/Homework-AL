/**
	@file
	@brief Файл исходного кода для класса избирателя
*/
#include "voter.h"


voter::voter() : name(""), vote("") {
	
}


/**
	@brief Конструктор копирования класса
	@param o Объект копирования
*/
voter::voter(const voter& o) : name(o.name), vote(o.vote) {
	
}

/**
	@brief Параметрический конструктор класса
	@param Name Имя изберателя
*/
voter::voter(string Name)  : name(Name), vote("") {
	
}


/**
	@brief Голосует за указанного кандидата
	@param voteName Имя выбираемого кандидата на выборах
	@throw voteException В случае попытки повторного голосования
*/
void voter::toVote(string voteName) {
	if(vote!="")
		throw voteException();
	vote = voteName;
}

/**
	@brief Возвращает имя выбранного кандидата
	@return Имя выбранного кандидата или пустую строку в случае, если не проголосовал
*/
string voter::getVote() {
	return vote;
}

/**
	@brief Возвращает имя избирателя
	@return Имя избирателя
*/
string voter::getName() {
	return name;
}

/**
	@brief Сбрасывает голос для возможности голосования
*/
void voter::reset() {
	vote="";
}


voter::~voter() {
	
}