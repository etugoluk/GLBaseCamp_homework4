#include "Date.hpp"
#include <regex>
#include <sstream>
#include <stdexcept>

Date::Date()
{
	day = 1;
	month = 1;
	year = 1970;
	format = 0;
}

Date::Date(std::string const &s)
{
	std::stringstream ss(s);
	char ch;

	if (std::regex_match (s, std::regex("(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[012])\\.\\d\\d\\d\\d")))
	{
    	format = 0;
    	ss >> day >> ch >> month >> ch >> year; 
	}
	else if (std::regex_match (s, std::regex("(0[1-9]|[12][0-9]|3[01])\\-(0[1-9]|1[012])\\-\\d\\d\\d\\d")))
	{
	    format = 1;
	    ss >> day >> ch >> month >> ch >> year; 
	}
	else if (std::regex_match (s, std::regex("\\d\\d\\d\\d\\.(0[1-9]|1[012])\\.(0[1-9]|[12][0-9]|3[01])") ))
	{
	    format = 2;
	    ss >> year >> ch >> month >> ch >> day; 
	}
	else
		throw std::invalid_argument("Bad format");
}

void	Date::add(int days)
{
	if (days <= 0)
	{
		std::cout << "Argument should be a positive number!" << std::endl;
	}
	while (1)
	{
		int begin_day = day;
		day += days;

		if (month == 2 && year % 4 == 0 && day > 29)
		{
			month++;
			day = 1;
			days -= 29 - begin_day + 1;
		}
		else if (month == 2 && year % 4 != 0 && day > 28)
		{
			month++;
			day = 1;
			days -= 28 - begin_day + 1;
		}
		else if ((month == 4 || month == 6 ||
					month == 9 || month == 11) && day > 30)
		{
			month++;
			day = 1;
			days -= 30 - begin_day + 1;
		}
		else if (day > 31)
		{
			month++;
			day = 1;
			days -= 31 - begin_day + 1;
		}
		else
			break;

		if (month > 12)
		{
			year++;
			month = 1;
		}
	}
}

void	Date::sub(int days)
{
	if (days <= 0)
	{
		std::cout << "Argument should be a positive number!" << std::endl;
	}
	while (1)
	{
		int begin_day = day;
		day -= days;

		if (day < 0)
		{
			--month;
			if (month < 1)
			{
				--year;
				month = 12;
			}

			days -= begin_day;
			if (month == 2 && year % 4 == 0)
			{
				day = 29;
			}
			else if (month == 2 && year % 4 != 0)
			{
				day = 28;
			}
			else if ((month == 4 || month == 6 ||
						month == 9 || month == 11))
			{
				day = 30;
			}
			else
			{
				day = 31;
			}
		}
		else
			break;
	}
}

int	operator-(Date const &d1, Date const &d2)
{
	if ((d1.year < d2.year) || 
			(d1.year == d2.year && d1.month < d2.month) || 
			(d1.year == d2.year && d1.month == d2.month && d1.day < d2.day))
		return -1;

	int result = 0;

	//counting the part of first year - from 01.01.d1.year to d1.day.d1.month.d1.year
	result += d1.day;
	for (int i = d1.month - 1; i > 0; --i)
	{
		if (i == 2 && d1.year % 4 == 0)
			result += 29;
		else if (i == 2 && d1.year % 4 != 0)
			result += 28;
		else if (i == 4 || i == 6 ||
					i == 9 || i == 11)
			result += 30;
		else
			result += 31;
	}

	//counting the part of second year - from d2.day.d2.month.d2.year to 31.12.d2.year
	if (d2.month == 2 && d2.year % 4 == 0)
		result += 29 - d2.day;
	else if (d2.month == 2 && d1.year % 4 != 0)
		result += 28 - d2.day;
	else if (d2.month == 4 || d2.month == 6 ||
				d2.month == 9 || d2.month == 11)
		result += 30 - d2.day;
	else
		result += 31 - d2.day;

	for (int i = d2.month + 1; i <= 12; ++i)
	{
		if (i == 2 && d1.year % 4 == 0)
			result += 29;
		else if (i == 2 && d1.year % 4 != 0)
			result += 28;
		else if (i == 4 || i == 6 ||
					i == 9 || i == 11)
			result += 30;
		else
			result += 31;
	}

	if (d1.year == d2.year)
	{
		if (d2.year % 4 == 0)
			result -= 366;
		else
			result -= 365;
	}
	//counting the difference between year1 and year2 
	for (int i = d2.year + 1; i < d1.year; ++i)
	{
		result += (i % 4 == 0) ? 366 : 365;
	}

	return result;
}

std::istream & operator>>(std::istream &is, Date &d)
{
	std::cout << "Enter year: ";
	is >> d.year;
	std::cout << "Enter month: ";
	is >> d.month;
	if (d.month < 1 || d.month > 12)
		throw std::invalid_argument("Bad format");
	std::cout << "Enter day: ";
	is >> d.day;
	if ((d.month == 2 && d.year % 4 == 0 && (d.day < 1 || d.day > 29))
		|| (d.month == 2 && d.year % 4 != 0 && (d.day < 1 || d.day > 28))
		|| ((d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) && (d.day < 1 || d.day > 30))
		|| d.day > 31)
		throw std::invalid_argument("Bad format");

	d.format = 0;

	return is;
}

std::ostream & operator<<(std::ostream &os, Date const &d)
{
	switch (d.format)
	{
		case 0 :
			if (d.day < 10)
				os << "0";
			os << d.day << ".";
			if (d.month < 10)
				os << "0";
			os << d.month << ".";
			if (d.year < 10)
				os << "000";
			else if (d.year < 100)
				os << "00";
			else if (d.year < 1000)
				os << "0";
			os << d.year;
			break;
		case 1 :
			if (d.day < 10)
				os << "0";
			os << d.day << "-";
			if (d.month < 10)
				os << "0";
			os << d.month << "-";
			if (d.year < 10)
				os << "000";
			else if (d.year < 100)
				os << "00";
			else if (d.year < 1000)
				os << "0";
			os << d.year;
			break;
		case 2 :
			if (d.year < 10)
				os << "000";
			else if (d.year < 100)
				os << "00";
			else if (d.year < 1000)
				os << "0";
			os << d.year << ".";
			if (d.month < 10)
				os << "0";
			os << d.month << ".";
			if (d.day < 10)
				os << "0";
			os << d.day;
			break;
	}

	return os;
}
