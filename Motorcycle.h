#pragma once
#ifndef SDDS_MOTORCYCLE_H_
#define SDDS_MOTORCYCLE_H_
#include "Vehicle.h"
namespace sdds {
	class Motorcycle :public Vehicle {
		bool m_SidecarFlag;
	public:
		Motorcycle();
		Motorcycle(const char*, const char*);
		Motorcycle(const Motorcycle&) = delete;
		Motorcycle& operator=(const Motorcycle&) = delete;
		std::istream& read(std::istream & = std::cin);
		std::ostream& write(std::ostream & = std::cout)const;
	};
}
#endif