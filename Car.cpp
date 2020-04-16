#include "Car.h"
#include<iostream>
namespace sdds {
	Car::Car() {
		this->m_carWashFlag = false;
	}

	Car::Car(const char* licensePlate, const char* model) :Vehicle(licensePlate, model) {
		if ((licensePlate == nullptr && licensePlate[0] == '\0') || (model == nullptr && model[0] == '\0'))
			this->m_carWashFlag = false;
	}

	std::istream& Car::read(std::istream& is) {
		if (this->isCsv()) {
			this->Vehicle::read(is);
			is >> this->m_carWashFlag;
			is.ignore(2000, '\n');
		}
		else {
			std::cout << "\nCar information entry" << std::endl;
			this->Vehicle::read(is);
			std::cout << "Carwash while parked? (Y)es/(N)o: ";
			std::string comfirm;
			std::cin >> comfirm;
			while ((comfirm != "Y" && comfirm != "y") && (comfirm != "N" && comfirm != "n")) {
				std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				std::cin >> comfirm;
			}  
			(comfirm == "Y" || comfirm == "y") ? this->m_carWashFlag = true : this->m_carWashFlag = false;
		}  
		return is;
	}  

	std::ostream& Car::write(std::ostream& os)const {
		if (this->isEmpty())
			os << "Invalid Car Object" << std::endl;
		else if (this->isCsv()) {
			os << "C,";
			this->Vehicle::write(os);
			os << this->m_carWashFlag << std::endl;
		}
		else
		{
			os << "Vehicle type: Car" << std::endl;
			this->Vehicle::write(os);
			(this->m_carWashFlag) ? os << "With Carwash" << std::endl : os << "Without Carwash" << std::endl;
		}  
		return os;
	}  
} 