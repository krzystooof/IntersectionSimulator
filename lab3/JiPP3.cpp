#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

unsigned int silnia(unsigned int n)
{
	if (n == 0 || n == 1)	return 1;
	else return n * silnia(n - 1);
}

class Exp {
private:
	vector<double> s;
	double x, epsylon,result;
public:
	Exp(double x, double epsylon) {
		this->epsylon = epsylon;
		this->x = x;
		s.push_back(1);
		s.push_back(x);
		int i = 1;
		result = 1+x;
		do{
			s.push_back(pow(x, i + 1) / silnia(i + 1));
			result += s[i];
			i++;
		} while (abs(s[i] - (s[i] - 1)) >= epsylon);
	}
	double getResult() const {
		return result;
	}
};
void task1() {
	cout << "Podaj x i epsilon: ";
	double x, e;
	cin >> x >> e;
	Exp exp = Exp(x, e);
	cout << exp.getResult() << endl;
}

class Teksty
{
private:
	string pomoc, sciezka;
	int ile_razy(string glowny){
		int razy = 0;
		for (int i = 0; i < glowny.size(); i++) {
			if (glowny[i] == this->pomoc[0]) {
				bool zgodny = true;
				int j = 0;
				while (zgodny == true && j<this->pomoc.size())
				{
					if (glowny[i + j] != this->pomoc[j]) zgodny = false;
					j++;
				}
				if (zgodny == true) razy++;
			}
		}
		return razy;
	}
public:
	int najlepszy;
	Teksty(string p, string f) {
		this->pomoc = p;
		this->sciezka = f;
		this->zestwienie = 0;
		this->najlepszy = 0;
	}
	Teksty() {
		this->pomoc = "";
		this->sciezka = "";
		this->zestwienie = 0;
		this->najlepszy = 0;
	}
	/*
	Teksty(const Teksty &t); //kopiujacy
	Teksty(Teksty &&t); //przenoszacy
	~Teksty();
	*/
	int zestwienie;
	void czytaj() {
		ifstream i;
		i.open(this->sciezka);
		if (i) {
			string ciag;
			cin.ignore();
			int j = 1;
			int max = 0;
			vector <string> ciagi;
			while (getline(i, ciag)) {
				ciagi.push_back(ciag);
				int razy = ile_razy(ciag);
				if (razy > max) {
					this->najlepszy = j-1;
					max = razy;
				}
				zestwienie+=razy;
				cout << j << " - " << razy << endl;
				j++;
			}
			cout << ciagi[this->najlepszy];
		}
		else cout << "BLAD ODCZYTU PLIKU!" << endl;
		i.close();
	}
};

void task2() {
	string pomoc, sciezka;
	cout << "Podaj ciag pomocniczy: ";
	cin >> pomoc;
	cout << "Podaj sciezke do pliku: ";
	cin >> sciezka;
	Teksty t = Teksty(pomoc, sciezka);
	t.czytaj();


}

class CountTime
{
private:
	double startTime, endTime, time;
public:
	CountTime() {}
	void start() {
		this->startTime = clock();
	}
	void stop() {
		this->endTime = clock();
	}
	void howMuchTime() {
		this->time = (endTime - startTime) / CLOCKS_PER_SEC;
		cout << "Czas wykonywania operacji: " << this->time << " sekund" << endl;
	}
	void showStartTime() {
		cout << "Czas poczatkowy: " << this->startTime / CLOCKS_PER_SEC << endl;
	}
	void showStopTime() {
		cout << "Czas koncowy: " << this->endTime / CLOCKS_PER_SEC << endl;
	}


};


int main()
{
	int wybor = 1;
	while (true && wybor != 0) {
		cout << "Podaj numer zadania: ";
		cin >> wybor;
		CountTime c = CountTime();
		switch (wybor)
		{
		case 1:
			c.start();
			c.showStartTime();
			task1();
			c.stop();
			c.showStopTime();
			c.howMuchTime();
			break;
		case 2:
			c.start();
			c.showStartTime();
			task2();
			c.stop();
			c.showStopTime();
			c.howMuchTime();
			break;
		default:
			cout << "Nie ma takiego zadania!";
			break;
		}
		cout << endl;
	}
}


