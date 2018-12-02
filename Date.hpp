#pragma once
#include <iostream>

class Date
{
	int day;
	int month;
	int year;
	int format;

public:
	Date();
	Date(std::string const &s);

	void add(int days);
	void sub(int days);

	friend int operator-(Date const &d1, Date const &d2); // return difference between dates in days
	friend std::istream & operator>>(std::istream &is, Date &d);
	friend std::ostream & operator<<(std::ostream &os, Date const &d);
};

int operator-(Date const &d1, Date const &d2);
std::istream & operator>>(std::istream &is, Date &d);
std::ostream & operator<<(std::ostream &os, Date const &d);