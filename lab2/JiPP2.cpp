#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <time.h>
#include <windows.h>
#include <memory>
#include "TimeSpan.h"

using namespace std;

void task1() {
	cout << "Podaj sekundy do przeliczenia: ";
	int s;
	cin >> s;
	TimeSpan time(s);
	cout << s << " sekund to " << time;
}

class Student {

private:
	int index;
	string name, surname;
public:
	Student(int index_number, string name, string surname) {
		this->index = index_number;
		this->name = name;
		this->surname = surname;
	}


	int getIndex() const {
		return index;
	}
	string getName() const {
		return name;
	}
	string getSurname() const {
		return surname;
	}
};

ostream &operator<<(ostream &o, Student s) {
	return o << s.getIndex() << " " << s.getName() << " " << s.getSurname();
}

class BazaStudentow
{
private:
	vector<Student> base;
public:
	BazaStudentow(Student s) {
		this->base.push_back(s);
	}
	BazaStudentow() {}

	void add(int i, string n, string s) {
		this->base.push_back(Student(i, n, s));
	}
	void print() {
		for (auto i : this->base) {
			cout << i << endl;
		}
	}
	void search(int indx) {
		for (auto i : this->base) {
			if (i.getIndex() == indx) cout << i;
		}
	}
	void erase(int indx) {
		for (int i = 0; i < this->base.size(); i++) {
			if (this->base[i].getIndex() == indx) this->base.erase(this->base.begin() + i);
		}
	}
	void erase() {
		this->base.clear();
	}
};
void task2() {
	BazaStudentow baza = BazaStudentow();
	cout << "BAZA STUDENTOW v0.0001" << endl;
	int number = 1;
	while (number != 0) {
		cout << "0. Wyjscie" << endl
			<< "1. Wypisz baze" << endl
			<< "2. Dodaj studenta" << endl
			<< "3. Wyszukaj studenta po numerze indeksu" << endl
			<< "4. Usun studenta po numerze indeksu" << endl
			<< "5. Usun baze danych" << endl
			<< "6. Zapisz baze do pliku" << endl
			<< "7. Odczytaj baze z pliku" << endl;
		cin >> number;
		if (number == 1)	baza.print();
		else if (number == 2) {
			cout << "Podaj numer indeksu, imie i nazwisko: ";
			string name, surname;
			int indx;
			cin >> indx >> name >> surname;
			baza.add(indx, name, surname);
		}
		else if (number == 3) {
			cout << "Podaj numer indeksu: ";
			int indx;
			cin >> indx;
			baza.search(indx);
		}
		else if (number == 4) {
			cout << "Podaj numer indeksu: ";
			int indx;
			cin >> indx;
			baza.erase(indx);
		}
		else if (number == 5) baza.erase();
		else if (number == 6) {

		}
		else if (number == 7);
		else if (number == 0);
		else cout << "BLEDNE POLECENIE!" << endl;
		cout << endl;


	}
}

struct Node
{
	int value;
	Node * left;
	Node * right;

	/*Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}*/
	Node(int v) : value(v)
	{
		this->left = nullptr;
		this->right = nullptr;
	}
	/*~Node()
	{
		cout << "Drzewo zostalo usuniete.\n";
	}*/
};
class BSTree
{
private:
	Node *n;
	void insert(Node *ne, int v);
	bool isEmpty(Node *ne);
	bool contains(Node *ne, int v);
	void printInOrder(Node *ne);
	void clear(Node *ne);
public:
	BSTree();
	~BSTree();
	void insert(int v) { insert(n, v); }
	bool isEmpty() { return isEmpty(n); }
	bool contains(int v) { return contains(n, v); }
	void printInOrder() { printInOrder(n); }
	void clear() { clear(n); }
};
BSTree::BSTree()
{
	n = NULL;
}
void BSTree::insert(Node *ne, int v)
{
	if (!ne)
	{
		ne = new Node(v);
		n = ne;
	}
	else
	{
		if (v < ne->value)
		{
			if (!ne->left)
			{
				Node *treeTemp = new Node(v);
				ne->left = treeTemp;
			}
			else
				insert(ne->left, v);
		}
		else
		{
			if (!ne->right)
			{
				Node *treeTemp = new Node(v);
				ne->right = treeTemp;
			}
			else
				insert(ne->right, v);
		}
	}
}
bool BSTree::isEmpty(Node *ne)
{
	if (ne == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
bool BSTree::contains(Node *ne, int v)
{
	if (ne == nullptr)
	{
		return 0;
	}
	else if (ne->value == v)
	{
		return 1;
	}
	else if (v < n->value) contains(ne->left, v);
	else if (v > n->value) contains(ne->right, v);
	else return 0;
}
void BSTree::printInOrder(Node *ne)
{
	if (ne)
	{
		printInOrder(ne->left);
		cout << ne->value << "\t";
		printInOrder(ne->right);
	}
}
void BSTree::clear(Node *ne)
{
	if (ne)
	{
		Node *root = ne;
		Node *left = ne->left;
		Node *right = ne->right;
		delete(root);
		delete(left);
		delete(right);
	}
}
BSTree::~BSTree()
{
	clear();
}
class Wymierna
{
public:
	string wymierna;
	double p, q;
	Wymierna(string w)
	{
		string p1, q1;
		for (int i = 0; i < w.length(); i++)
		{
			if (w[i] == '/')
			{
				p1 += w.substr(0, i);
				q1 += w.substr(i + 1, w.length() - i);
				break;
			}
		}
		double p2 = atoi(p1.c_str());
		double q2 = atoi(q1.c_str());

		this->p = p2;
		this->q = q2;
	}
	bool czy_okres()
	{
		int p1 = p;
		int q1 = q;
		string res;

		map <int, int> mp;
		mp.clear();

		int rem = p1 % q1;

		while ((rem != 0) && (mp.find(rem) == mp.end()))
		{
			mp[rem] = res.length();
			rem = rem * 10;
			int res_part = rem / q1;
			res += to_string(res_part);

			rem = rem % q1;
		}
		if (rem != 0)
			return 1;
		else
			return 0;
	}
	int okres()
	{
		int p1 = p;
		int q1 = q;
		string res;

		map <int, int> mp;
		mp.clear();

		int rem = p1 % q1;

		while ((rem != 0) && (mp.find(rem) == mp.end()))
		{
			mp[rem] = res.length();
			rem = rem * 10;
			int res_part = rem / q1;
			res += to_string(res_part);

			rem = rem % q1;
		}
		return atoi(res.substr(mp[rem]).c_str());
	}
	void wyswietl()
	{
		bool a = czy_okres();
		if (a)
		{
			int li = p / q;
			int ok = okres();
			cout << li << "." << "(" << ok << ")" << endl;
		}
		else
		{
			double li = p / q;
			cout << li << endl;
		}
	}
};
class Doskonala
{
private:
	bool czy_podzielnik(int p, int l);
	bool czy_doskonala(int l);
public:
	int n;
	Doskonala(int n1)
	{
		this->n = n1;
	}
	void pierwsza_dosk()
	{
		for (int i = 1; i <= 1000; i++)
		{
			if (czy_doskonala(i))
			{
				cout << "Pierwsza liczba doskonala jest: " << i << endl;
				break;
			}
		}
	}
	void wieksza_dosk(int d)
	{
		for (int i = d; i <= 1000000; i++)
		{
			if (czy_doskonala(i))
			{
				cout << "Pierwsza liczba doskonala wieksza od " << d << " jest: " << i << endl;
				break;
			}
		}
	}
	void n_dosk()
	{
		vector<int> dosk;
		dosk.push_back(0);
		for (int i = 1; i <= 10000; i++)
		{
			if (czy_doskonala(i))
			{
				dosk.push_back(i);
			}
		}
		cout << "Liczba doskonala o n=" << n << " to: " << dosk[n] << endl;
	}
};
bool Doskonala::czy_podzielnik(int p, int l)
{
	if (l%p == 0)
		return 1;
	else
		return 0;
}
bool Doskonala::czy_doskonala(int l)
{
	int suma = 0;

	for (int i = 1; i <= (l / 2); i++)
	{
		if (czy_podzielnik(i, l))
		{
			suma += i;
		}
	}
	if (suma == l)
		return 1;
	else
		return 0;
}
int random(int min, int max)
{
	static default_random_engine e{};
	uniform_real_distribution<double> d(min, max);
	return d(e);
}
void sortowanie_babelkowe(int *tab, int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = n - 1; j >= 1; j--)
		{
			if (tab[j] < tab[j - 1])
			{
				int bufor;
				bufor = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = bufor;
			}
		}
	}
}
void quicksort(int *tab, int lewy, int prawy)
{
	int v = tab[(lewy + prawy) / 2];
	int i, j, x;
	i = lewy;
	j = prawy;
	do
	{
		while (tab[i] < v) i++;
		while (tab[j] > v) j--;
		if (i <= j)
		{
			x = tab[i];
			tab[i] = tab[j];
			tab[j] = x;
			i++;
			j--;
		}
	} while (i <= j);
	if (j > lewy) quicksort(tab, lewy, j);
	if (i < prawy) quicksort(tab, i, prawy);
}
void heapify(int *tab, int n, int i) {
	int temp;
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && tab[l] > tab[largest])
		largest = l;
	if (r < n && tab[r] > tab[largest])
		largest = r;
	if (largest != i) {
		temp = tab[i];
		tab[i] = tab[largest];
		tab[largest] = temp;
		heapify(tab, n, largest);
	}
}
void heapSort(int *tab, int n) {
	int temp;
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(tab, n, i);
	for (int i = n - 1; i >= 0; i--) {
		temp = tab[0];
		tab[0] = tab[i];
		tab[i] = temp;
		heapify(tab, i, 0);
	}
}
void Wypelnij(int *tab1, int *tab2, int *tab3)
{
	for (int i = 0; i < 11300; i++)
	{
		tab1[i] = random(0, 1000);
		tab2[i] = tab1[i];
		tab3[i] = tab1[i];
	}
}
void Pomiar(int *tab1, int *tab2, int *tab3)
{
	clock_t start, stop;
	double czas;
	/*for (int i = 0; i < 1000; i++)
	{

	}*/
	start = clock();
	sortowanie_babelkowe(tab1, 11300);
	stop = clock();
	czas = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "Bubble: " << czas << endl;
	start = clock();
	quicksort(tab2, 0, 11299);
	stop = clock();
	czas = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "Quicksort: " << czas << endl;
	start = clock();
	heapSort(tab3, 11300);
	stop = clock();
	czas = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "Heapsort: " << czas << endl;
}

void Zad3()
{
	BSTree bst;
	cout << (bst.isEmpty() ? "Drzewo jest puste" : "Drzewo nie jest puste") << endl;
	bst.insert(5);
	bst.insert(3);
	bst.insert(7);
	bst.insert(4);
	bst.insert(2);
	cout << (bst.isEmpty() ? "Drzewo jest puste" : "Drzewo nie jest puste") << endl;
	cout << "Drzewo zawiera element o wartosci 3: " << bst.contains(3) << endl;
	cout << "Drzewo zawiera element o wartosci 9: " << bst.contains(9) << endl;
	bst.printInOrder();
	cout << endl;
	cout << (bst.isEmpty() ? "Drzewo jest puste" : "Drzewo nie jest puste") << endl;
}
void Zad5()
{
	Wymierna a{ "9/20" }, b{ "2/3" };
	a.wyswietl();
	b.wyswietl();
}
void Zad6()
{
	Doskonala pierwsza(3);
	pierwsza.n_dosk();
	pierwsza.pierwsza_dosk();
	pierwsza.wieksza_dosk(1000);

	/*if (czy_doskonala(liczba))
		cout << "T";
	else
		cout << "N";*/
		/*pierwsza_dosk();
		wieksza_dosk(497);
		n_dosk(4);*/
}
void Zad7()
{
	int *tab1, *tab2, *tab3;
	tab1 = new int[11300];
	tab2 = new int[11300];
	tab3 = new int[11300];
	/*for (int i = 0; i < 300; i++)
	{
		tab1[i] = random(0, 1000);
		tab2[i] = tab1[i];
		tab3[i] = tab1[i];
	}*/
	Wypelnij(tab1, tab2, tab3);

	/*sortowanie_babelkowe(tab1, 300);
	quicksort(tab2, 0, 299);
	heapSort(tab3, 300);*/
	/*for (int i = 0; i < 300; i++)
	{
		cout <<tab1[i] << " " << tab2[i] << " " << tab3[i] << endl;
	}*/
	Pomiar(tab1, tab2, tab3);

}
void Zad8()
{

}


int main()
{
	while (true)
	{
		cout << "Podaj numer zadania: ";
		int number;
		cin >> number;
		switch (number)
		{
		case 1:
			task1();
			break;
		case 2:
			task2();
			break;
		case 3:
			Zad3();
			break;
		case 5:
			Zad5();
			break;
		case 6:
			Zad6();
			break;
		case 7:
			Zad7();
			break;
		case 8:
			Zad8();
			break;
		default:
			cout << "Nie ma takiego zadania!";
			break;
		}
		cout << endl;
	}
}

