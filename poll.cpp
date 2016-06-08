/**
	@file
	@brief Файл исходного кода для класса избирательного участка
*/
#include "poll.h"

poll::poll() : vector<voter>(), name("") {
	
}

/**
	@brief Конструктор копирования класса
	@param o Объект копирования
*/
poll::poll(const poll& o) : vector<voter>(o), name(o.name) {
	
}

/**
	@brief Параметрический конструктор класса
	@param Name Название избирательного участка
*/
poll::poll(string Name) : vector<voter>(), name(Name) {}

/**
	@brief Возвращает название избирательного участка
	@return Название избирательного участка
*/
string poll::getName() {
	return name;
}

/**
	@brief Возвращает индекс избирателя по заданному имени
	@param VoterName Имя избирателя
	@return Индекс избирателя с заданным именем или -1, если такой отсутствует 
*/
int poll::getIndex(string VoterName) {
	for(size_t i = 0; i<size(); i++) {
		if((*this)[i].getName()==VoterName)
			return i;
	}
	return -1;
}

/**
	@brief Сбрасывает голос у всех избирателей для возможности голосования
*/
void poll::reset() {
	for(size_t i=0; i<size(); i++)
		(*this)[i].reset();
}

/**
	@brief Сохраняет базовую информацию о избирательном участке в заданный файл
	@param file Файл, в который производится сохранение данных
*/
void poll::save(ofstream& file) {
	file << size() << " " << name << " ";
	for(size_t i=0; i<size(); i++)
		file << (*this)[i].getName() << " ";
	file << endl;
}

poll::~poll() {}