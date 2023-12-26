#pragma once
#include "THeadList.h"

#include <string>
#include<sstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "TMonom.h"

using namespace std;

const int nonDisplayedZeros = 4; 
const double EPSILON = 1e-6;


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other); 
	TPolinom& operator+(TPolinom& q);
	void AddMonom(TMonom newMonom); 
	TPolinom MultMonom(TMonom monom); 
	TPolinom& operator*(double coef); 
	bool operator==(TPolinom& other);  
	string ToString(); 
};


TPolinom::TPolinom() :THeadList<TMonom>::THeadList() {}


TPolinom::TPolinom(TPolinom& other)
{
	pHead = new TNode<TMonom>;
	TNode<TMonom>* h = other.pHead->pNext;
	while (h != other.pStop) {
		this->AddMonom(h->value);
		h = h->pNext;
	}
}


TPolinom::TPolinom(string str) {
	size_t pos = 0;
	while (pos < str.length()) {
		double coef = 0.0;
		int degX = 0, degY = 0, degZ = 0;
		char var;
		if (isdigit(str[pos]) || str[pos] == '-' || str[pos] == '+') {
			size_t nextPos;
			coef = std::stod(str.substr(pos), &nextPos);
			pos += nextPos;
		}
		while (pos < str.length() && (str[pos] == 'x' || str[pos] == 'y' ||
			str[pos] == 'y' || str[pos] == 'z')) {
			var = tolower(str[pos]);
			pos++;
			if (pos < str.length() && str[pos] == '^') {
				pos++;
				size_t nextPos;
				int deg = std::stod(str.substr(pos), &nextPos);
				pos += nextPos;
				switch (var) {
				case 'x': degX = deg; break;
				case 'y': degY = deg; break;
				case 'z': degZ = deg; break;
				}
			}
			else {
				switch (var) {
				case 'x': degX = 1; break;
				case 'y': degY = 1; break;
				case 'z': degZ = 1; break;
				}
			}
		}
		this->AddMonom(TMonom(coef, degX, degY, degZ));
	}
}


TPolinom& TPolinom::operator=(TPolinom& other)
{
	if (this != &other) {
		while (!this->IsEmpty()) {
			this->DeleteFirst();
		}
		TNode<TMonom>* current = other.pHead->pNext;
		while (current != nullptr) {
			this->AddMonom(current->value);
			current = current->pNext;
		}
	}
	return *this;
}


void TPolinom::AddMonom(TMonom m)
{
	if (m.GetCoef() == 0) throw invalid_argument("Can't work. Change dates");
	this->Reset();
	bool isAdded = false;
	while (!this->IsEnd()) {
		if (this->pCurrent->value.GetIndex() == m.GetIndex()) {
			this->pCurrent->value.SetCoef(pCurrent->value.GetCoef() + m.GetCoef());
			if (fabs(this->pCurrent->value.GetCoef()) < EPSILON) {
				this->DeleteCurrent();
			}
			isAdded = true;
			break;
		}
		this->GoNext();
	}
	if (!isAdded) this->InsertLast(m);
	pHead->pNext = this->pFirst;
}


TPolinom TPolinom::MultMonom(TMonom monom)
{
	TPolinom res(*this);
	TNode<TMonom>* current = res.pHead->pNext;
	while (current != nullptr) {
		current->value.SetCoef(current->value.GetCoef() * monom.GetCoef());
		current->value.SetIndex(current->value.GetIndex() + monom.GetIndex());
		current = current->pNext;
	}
	return res;
}


TPolinom& TPolinom::operator+(TPolinom& other)
{
	if (other.IsEmpty()) throw invalid_argument("Can't work. Change dates");
	TNode<TMonom>* current = other.pHead->pNext;
	while (current != nullptr) {
		this->AddMonom(current->value);
		current = current->pNext;
	}
	return *this;
}


TPolinom& TPolinom::operator*(double coef)
{
	if (this->IsEmpty()) throw invalid_argument("Can't work. Change dates");
	TNode<TMonom>* current = this->pHead->pNext;
	while (current != nullptr) {
		current->value.SetCoef(current->value.GetCoef() * current->value.GetCoef());
		if (current->pNext == nullptr) break;
		current = current->pNext;
	}
	return *this;
}


bool TPolinom::operator==(TPolinom& other) {
	if (this->GetLength() != other.GetLength()) return false;
	TNode<TMonom>* thisCurrent = this->pHead->pNext;
	TNode<TMonom>* otherCurrent = other.pHead->pNext;
	while (thisCurrent != nullptr && otherCurrent != nullptr) {
		if (!(thisCurrent->value == otherCurrent->value)) { return false; }
		thisCurrent = thisCurrent->pNext;
		otherCurrent = otherCurrent->pNext;
	}
	return thisCurrent == otherCurrent;
}


string TPolinom::ToString() {
	string result;
	TNode<TMonom>* current = this->pHead->pNext;
	while (current != nullptr) {
		int degX = current->value.GetIndex() % 10;
		int degY = (current->value.GetIndex() / 10) % 10;
		int degZ = current->value.GetIndex() / 100;
		if (!result.empty()) result += (current->value.GetCoef() > 0) ? " + " : " - ";
		else if (current->value.GetCoef() < 0) { result += "-"; }
		result += to_string(abs(current->value.GetCoef()));
		if (degX > 0) {
			result += "x";
			if (degX > 1) {
				result += "^" + to_string(degX);
			}
		}
		if (degY > 0) {
			result += "y";
			if (degY > 1) {
				result += "^" + to_string(degY);
			}
		}
		if (degZ > 0) {
			result += "z";
			if (degZ > 1) {
				result += "^" + to_string(degZ);
			}
		}
		current = current->pNext;
	}
	return result;
}