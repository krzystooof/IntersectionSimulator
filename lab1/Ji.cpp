

#include "pch.h"
#include <iostream>
#include <string>



class StosStatyczny
{
 public:
	StosStatyczny() {
		for (int i = 0; i < 10; i++) {
			tab[i] = NULL;
		}
	}
	~StosStatyczny() {}

	bool pusty() {
		if (tab[0] == NULL) return true;
		else return false;
	}
	bool pelny() {
		if (tab[9] != NULL) return true;
		else return false;
	}
	void dodaj(int l) {
		int i = 0;
		while (true) {
				if (tab[i] == NULL) {
					tab[i] = l;
					std::cout << "Dodano element (" << l << ") na pozycji " << i << std::endl;
					break;
				}
				i++;
		}
	}
	void usun() {
		try
		{
			if (tab[0]==NULL) throw 0;
			int i = 9;
			while (true)
			{
				if (tab[i] != NULL) {
					std::cout << "Zdjety: " << tab[i] << "\n";
					tab[i] = NULL;
					break;
				}
				i--;
			}
		}
		catch (int w)
		{
			std::cout << "Blad: stos pusty\n";
		}
	}
	void szczytowy() {
		
			int i = 9;
			while (true)
			{
				if (tab[i] != NULL) {
					std::cout << "Szczytowy: " << tab[i] << "\n";
					break;
				}
				i--;
		
		}
	}
	void oproznij() {
		for (int i = 0; i < 10; i++) {
			tab[i] = NULL;
		}
	}
	virtual double pojemnosc() {
		int i = 0;
		while (tab[i] != NULL) {
			i++;
		}
		return i;
	}


private:
	int tab[10];
};

void task1() {
	std::cin.ignore();
	StosStatyczny s;
	std::string polecenie="";
	std::cout << "Podaj polecenia, aby zakonczyc wpisz '0':\n";
	while (polecenie != "0") {
		std::getline(std::cin, polecenie);		
		if (polecenie[0] == 'D') s.dodaj(int(polecenie[2]-48));
		if (polecenie[0] == 'U') s.usun();
		if (polecenie[0] == 'O') s.szczytowy();
	}
}


int main()
{
	int task = 1;
	while (task != 0) {
		std::cout << "Podaj numer zadania: ";
		std::cin >> task;
		switch (task)
		{
		case 1:
			task1();
			break;
		default:
			std::cout << "Nie ma takiego zadania!" << std::endl;
			break;
		}
	}
}


