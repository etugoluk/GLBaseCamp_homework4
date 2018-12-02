#include "Date.hpp"

int main()
{
	try
	{
		Date d; //default constructor
		std::cout << "Default date: " << d << std::endl;

		// std::cin >> d; // input of date - can be exception if bad format of date
		// std::cout << "Input date: " << d << std::endl;

		//!!!exceptions!!!
		// Date bad1("43-13-2001");
		// Date bad2("12-12.1990");
		// Date bad3("1.2.3");

		Date d1("17-05-2016");
		Date d2("15.01.2023");

		std::cout << d1 << " - " << d2 << ": " << d1 - d2 << " days" << std::endl;
		std::cout << d2 << " - " << d1 << ": " << d2 - d1 << " days" << std::endl;
		std::cout << d1 << " - " << d1 << ": " << d1 - d1 << " days" << std::endl;


		d1.add(1365);
		std::cout << "Add 1365 days: " << d1 << std::endl;

		d1.sub(1365);
		std::cout << "Sub 1365 days: " << d1 << std::endl;

		d1.add(15);
		std::cout << "Add 15 days: " << d1 << std::endl;

		d1.sub(15);
		std::cout << "Sub 15 days: " << d1 << std::endl;

		d1.add(3);
		std::cout << "Add 3 days: " << d1 << std::endl;

		d1.sub(3);
		std::cout << "Sub 3 days: " << d1 << std::endl;

		d1.add(-5); //error message
		d1.sub(0); //error message
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}