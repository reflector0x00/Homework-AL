/**
	@file
	@brief Заголовочный файл для класса избирательного участка
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "voter.h"
using namespace std;



/**
	@brief Класс избирательного участка
	Контейнерный класс для избирателей. Наследован от vector<voter>
*/
class poll : public vector<voter> {
	string name;
	public:
	poll();
	poll(const poll& o);
	poll(string Name);
	string getName();
	int getIndex(string VoterName);
	void reset();
	void save(ofstream& file);
	~poll();
};