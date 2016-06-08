/**
	@file
	@brief Заголовочный файл для класса избирателя
*/
#pragma once
#include <string>
#include <stdexcept>
using namespace std;

/**
	@brief Класс исключения голосования
	Вызывается  в случае повторного голосования
*/
class voteException : public exception {};

/**
	@brief Класс избирателя
	Описывает элементраный класс системы голосования. 
*/
class voter {
	string name;
	string vote;
	public:
	voter();
	voter(const voter& o);
	voter(string Name);
	void toVote(string voteName);
	string getVote();
	string getName();
	void reset();
	~voter();
};

