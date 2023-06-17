#include"WordsData.h"
#include<iostream>
using namespace std;

//constructor
Keywords::Keywords() {
	this->idf = 0;
	this->new_tf = 0;
}

//destructor
Keywords::~Keywords() {
	delete this;
}

//set
void Keywords::SetValue(double idf, double new_tf) {
	this->idf = idf;
	this->new_tf = new_tf;
	return;
}

//Àò¨úidf, new_tf
double Keywords::getIdf() {
	return this->idf;
}

double Keywords::getNew_tf() {
	return this->new_tf;
}