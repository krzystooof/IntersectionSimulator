#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class TimeSpan {
public:
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;

	TimeSpan(unsigned int seconds) {
		this->hours = seconds / 3600;
		this->minutes = (seconds - (this->hours * 3600)) / 60;
		this->seconds = seconds - (this->hours * 3600) - (this->minutes * 60);
	}
	int getHours() const {
		return hours;
	}
	int getMinutes() const {
		return minutes;
	}
	int getSeconds() const {
		return seconds;
	}
};

ostream &operator<<(ostream &o, TimeSpan &time) {
	o << time.hours;
	o << ":";
	o << setfill('0') << setw(2) << time.minutes;
	o << ":";
	o << setfill('0') << setw(2) << time.seconds;
	return o;
}