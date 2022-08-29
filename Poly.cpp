#include "Poly.h"
#include <iostream>
#include <cstdlib>

Poly::Poly()
{
	// TODO	
	head = new PolyNode(-1, 0, NULL);
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	// TODO	
	head = new PolyNode(-1, 0, NULL);


	PolyNode* current = head;

	length = coeff.size();

	for (int i = 0; i < length; i++) {
		current->next = new PolyNode(deg[i], coeff[i], NULL);
		current = current->next;
	}
	
}

Poly::~Poly()
{

}


// Time complexity n
// Space complexity n
void Poly::addMono(int i, double c)
{
	// TODO
	PolyNode* current = head->next;
	PolyNode* previous = NULL;
	int temp = 0;
	//std::cout << length;
	//std::cout << "\033[1;31mlength: " << length << "\033[0m\n" << std::endl;

	while (true) {

		if (current == NULL) {
			if (length != 0) {
				previous->next = new PolyNode(i, c, NULL);
				length++;
				break;
			}
			head->next = new PolyNode(i, c, current);
			length++;
			break;
		}
		
		else if (current->deg == i) {
			current->coeff += c;
			if (current->coeff == 0) {
				if (temp == 0) {
					head->next = current->next;
					length--;
				}
				else {
					previous->next = current->next;
					length--;
				}
			}
			break;
		}
		
		else if (temp == 0) {
			if (current->deg < i) {
				head->next = new PolyNode(i, c, current);
				length++;
				break;
			}
		}

		else if (temp != 0) {
			if (current->deg < i && previous->deg > i) {
				previous->next = new PolyNode(i, c, current);
				length++;
				break;
			}
		}
		
		
		temp++;
		//std::cout << temp << std::endl;
		previous = current;
		current = current->next;
	}
}

// Time complexity n^2
// Space complexity n
void Poly::addPoly(const Poly& p)
{
	// TODO
	PolyNode* currentp = p.head->next;
	int degreep = 0;
	int coeffp = 0;
	while (currentp != NULL) {         //looping through the addpoly
		degreep = currentp->deg;
		coeffp = currentp->coeff;
		addMono(degreep, coeffp);
		currentp = currentp->next;
	}
}

// Time complexity n
// Space complexity n
void Poly::multiplyMono(int i, double c)
{
	// TODO
	//std::cout << "\033[1;31m" << "***********************" << "\033[0m\n" << std::endl;
	PolyNode* current = head;
	while (true) {
		if (current == NULL) {
			break;
		}
		else if (current->next == NULL) {
			break;
		}
		else if (c == 0) {
			head->next = NULL;
			length = 0;
			break;
		}
		else {
			current->next->deg += i;
			current->next->coeff *= c;
			if (current->next->coeff == 0) {
				current->next = current->next->next;
			}
		}
		current = current->next;
	}
}

// Time complexity n^3
// Space complexity n^2
void Poly::multiplyPoly(const Poly& p)
{
	// TODO
	PolyNode* currentp = p.head->next;
	PolyNode* currentmy = head->next;
	Poly temp = Poly();
	Poly tempfinal = Poly();
	int degreep = 0;
	int coeffp = 0;
	int degreemy = 0;
	int coeffmy = 0;

	while (currentp != NULL) {         //looping through the multiplying poly
		degreep = currentp->deg;
		coeffp = currentp->coeff;
		currentmy = head->next;

		while (currentmy != NULL) { //stores my poly in the temp poly
			degreemy = currentmy->deg;
			coeffmy = currentmy->coeff;
			temp.addMono(degreemy, coeffmy);
			currentmy = currentmy->next;
		}

		temp.multiplyMono(degreep, coeffp);
		tempfinal.addPoly(temp);
		temp.multiplyMono(1, 0); //clear temp (reset it)
		currentp = currentp->next;
	}

	head = tempfinal.head;
	length = tempfinal.length;
}

// Time complexity n
// Space complexity n
void Poly::duplicate(Poly& outputPoly)
{
	// TODO
	PolyNode* current = outputPoly.head;
	PolyNode* thisCurrent = head;
	outputPoly.length = length;
	while (true) {
		if (thisCurrent->next == NULL) {
			break;
		}
		else {
			int deg = thisCurrent->next->deg;
			double coeff = thisCurrent->next->coeff;
			current->next = new PolyNode(deg,coeff,NULL);
		}
		current = current->next;
		thisCurrent = thisCurrent->next;
	}
}

// Time complexity 1
// Space complexity 1
int Poly::getDegree()
{
	// TODO
	if (head->next == NULL) {
		return -1;
	}
	else {
		return head->next->deg;
	}
}

// Time complexity 1
// Space complexity 1
int Poly::getTermsNo()
{
	// TODO
	
	return length;//change this after completing this function
}

double Poly::power(int base, int exp)
{
	double output = 1;
	for (int i = 0; i < exp; i++) {
		output *= base;
	}

	return output;
}

double Poly::evaluate(double x)
{
	// TODO
	double output = 0;
	PolyNode* current = head;
	while (true) {
		if (current->next == NULL) {
			break;
		}
		else {
			output += current->next->coeff*power(x,current->next->deg);
		}
		current = current->next;
	}
	return output;//change this after completing this function
}

std::string Poly::toString()
{
	// TODO
	std::string output = "";
	PolyNode* current = head->next;
	output = "degree=" + std::to_string(current->deg) + "; ";
	for (int i = 0; i < length; i++) {
		output += "a(" + std::to_string(length - i + 1) + ")=" + std::to_string(current->coeff) + "; ";
		current = current->next;
	}
	std::cout << output;
	return output;//change this after completing this function
}
