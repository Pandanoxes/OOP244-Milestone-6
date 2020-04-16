#pragma once
#ifndef SDDS_CAR_H_
#define SDDS_CAR_H_
#include "Vehicle.h"
namespace sdds {
	class Car :public Vehicle {
		bool m_carWashFlag;
	public:
		Car();
		Car(const char*, const char*);
		Car(const Car&) = delete;
		Car& operator=(const Car&) = delete;
		std::istream& read(std::istream & = std::cin);
		std::ostream& write(std::ostream & = std::cout)const;
	};
}
#endif