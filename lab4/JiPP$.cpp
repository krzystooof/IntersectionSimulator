#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Shape
{
public:
	Shape(string name) {
		this->name = name;
		cout << "Ksztalt " << name << " utworzony" << endl;
	}
	~Shape() {
		cout << "Ksztalt " << name << " usuniety" << endl;
	}
	void setName(string name) {
		this->name = name;
	}
	string getName() const {
		return name;
	}
	virtual double area() = 0;

private:
	string name;
};


class Rectangle : public Shape
{
private:
	double height, width;
	string name;
public:
	Rectangle(string name, double width, double height):Shape(name) {
		this->name = name;
		this->height = height;
		this->width = width;
		cout << "Prostokat " << name << " utworzony" << endl;
	}
	~Rectangle() {
		cout << "Prostokat " << name << " usuniety" << endl;
	}
	virtual double area() {
		cout << "Pole = " << height * width << endl;
		return height*width;
	}
};

class Square : public Rectangle
{
public:
	Square(string name, double width) :Rectangle(name, width, width) {
		this->name = name;
		this->width = width;
		cout << "Kwadrat " << name << " utworzony" << endl;
	}
	~Square() {
		cout << "Kwadrat " << this->name << " usunięty" << endl;
	}
	virtual double area() {
		cout << "Pole = " << width * width << endl;
		return  width * width;
	}

private:
	string name;
	double width;
};

void task1() {
	cout << "Kwadrat:" << endl;
	Square s("kwadrat1", 2.0);
	s.area();
	cout << "Prostokat:" << endl;
	Rectangle r("prostokat1", 2.0, 3.0);
	r.area();
	cout << "Ksztalt: " << endl;

	cout << endl << endl << "Referencja:" << endl;
	Rectangle r_ref = Square("kwadrat_ref",2.0);
	r_ref.area();
	//shape nie mozna wywolac
}

class Funkcja
{
protected:
	Funkcja() {
		cout << "Funckja stworzona" << endl;
	}
public:
	virtual double oblicz(double x) = 0;
private:

};

class FunkcjaLiniowa : Funkcja
{
public:
	FunkcjaLiniowa(double a, double b) : Funkcja() {
		cout << "FunkcjaLiniowa " << a << "  " << b << " stworzona" << endl;
		this->a = a;
		this->b = b;
	}
	virtual double oblicz(double x) {
		return a * x + b;
	}

private:
	double a, b;
};

void task2() {
	FunkcjaLiniowa f(1.0, 2.0);
	cout << f.oblicz(1);
}

class ShapeContainer {
private:
	vector<Shape*> c;
public:
	ShapeContainer() {}
	void add(Shape *s) {
		c.push_back(s);
	}
	void displayAll() {
		for (auto f : c) {
			f->area();
		}
	}
};

void task3() {
	ShapeContainer c;
	Square a("kwadrat1", 2.0);
	c.add(&a);
	Rectangle b("prostokat1", 2.0, 3.0);
	c.add(&b);
	c.displayAll();
}



int main()
{
	int task=1;
	while (task != 0) {
		cout << "Podaj numer zadania: ";
		cin >> task;
		switch (task)
		{
		case 0:
			break;
		case 1:
			task1();
			break;
		case 2:
			task2();
			break;
		case 3:
			task3();
			break;
		default:
			cout << "Nie ma takiego zadania!";
			break;
		}
		cout <<  endl;
	}
}


