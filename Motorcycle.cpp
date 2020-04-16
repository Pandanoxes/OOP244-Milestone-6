#include"Motorcycle.h"
#include <iostream>
namespace sdds {
	Motorcycle::Motorcycle() {
		this->m_SidecarFlag = false;
	}

	Motorcycle::Motorcycle(const char* licensePlate, const char* model) :Vehicle(licensePlate, model) {
		if ((licensePlate == nullptr && licensePlate[0] == '\0') || (model == nullptr && model[0] == '\0'))
			this->m_SidecarFlag = false;
	}

	std::istream& Motorcycle::read(std::istream& is) {
		if (this->isCsv()) {
			this->Vehicle::read(is);
			is >> this->m_SidecarFlag;
			is.ignore(2000, '\n');
		}
		else {
			std::cout << "\nMotorcycle information entry" << std::endl;
			this->Vehicle::read(is);
			std::cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			std::string comfirm;
			std::cin >> comfirm;
			while ((comfirm != "Y" && comfirm != "y") && (comfirm != "N" && comfirm != "n")) {
				std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				std::cin >> comfirm;
			}
			(comfirm == "Y" || comfirm == "y") ? this->m_SidecarFlag = true : this->m_SidecarFlag = false;
		}
		return is;
	}

	std::ostream& Motorcycle::write(std::ostream& os)const {
		if (this->isEmpty())
			os << "Invalid Motorcycle Object" << std::endl;
		else if (this->isCsv()) {
			os << "M,";
			this->Vehicle::write(os);
			os << this->m_SidecarFlag << std::endl;
		}
		else
		{
			os << "Vehicle type: Motorcycle" << std::endl;
			this->Vehicle::write(os);
			if (this->m_SidecarFlag)
				os << "With Sidecar" << std::endl;
		}
		return os;
	}
}