#include "test.hpp"
#include <iostream>

bool test::test_creation() {

	std::cout << "testing enemy creation" << std::endl;

	try {

		Enemy enemy;

		std::cout << "Success" << std::endl;
		return true;
	}
	catch (...) {
		std::cout << "failed" << std::endl;
		return false;
	}


}

