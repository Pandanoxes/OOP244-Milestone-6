#define _CRT_SECURE_NO_WARNINGS
#include "Vehicle.h"
#include <string.h>
#include <stdlib.h>

namespace sdds {
	Vehicle::Vehicle() {
		this->setEmpty();
	}

	Vehicle::Vehicle(const char* licensePlate, const char* model) {
		if ((licensePlate != nullptr && licensePlate[0] != '\0') && (model != nullptr && model[0] != '\0') && strlen(licensePlate) < 9 && strlen(model) > 2) {
			strcpy(this->m_licensePlate, licensePlate);
			this->m_model = nullptr;
			this->m_model = new char[strlen(model) + 1];
			strcpy(this->m_model, model);
			this->m_spotNum = 0;
		}
		else this->setEmpty();
	}

	Vehicle::~Vehicle() {
		delete[] this->m_model;
	}

	int Vehicle::getParkingSpot() {
		return this->m_spotNum;
	}

	void Vehicle::setParkingSpot(const int spotNum) {
		this->m_spotNum = spotNum;
	}

	bool operator==(const Vehicle& vehicle, const char* licencePlate) {
		bool valid = true;
		if (strlen(vehicle.getLicensePlate()) == strlen(licencePlate)) {
			int max = strlen(licencePlate);
			for (int i = 0; i < max;i++)
				if (tolower(vehicle.getLicensePlate()[i]) != tolower(licencePlate[i])) {
					valid = false;
					break;
				}
		}
		else
			valid = false;
		return valid;
	}

	bool operator==(const Vehicle& vehicle1, const Vehicle& vehicle2) {
		return vehicle1 == vehicle2.getLicensePlate();
	}

	std::istream& Vehicle::read(std::istream& is) {
		if (this->isCsv()) {
			int tempSpotNum = 0;
			char tempLicensePlate[9];
			char tempModel[61];
			is >> tempSpotNum;
			is.ignore();
			is.get(tempLicensePlate, 9, ',');
			is.ignore();
			is.get(tempModel, 60, ',');
			is.ignore();
			this->m_spotNum = tempSpotNum;
			int max = strlen(tempLicensePlate);
			for (int i = 0;i < max;i++)
				tempLicensePlate[i] = toupper(tempLicensePlate[i]);

			strcpy(this->m_licensePlate, tempLicensePlate);
			this->setMakeModel(tempModel);
		}
		else {
			bool valid = false;
			char tempLicensePlate[10];
			char tempModel[62];
			std::cout << "Enter Licence Plate Number: ";
			do {
				is.get(tempLicensePlate, 10, '\n');
				if (strlen(tempLicensePlate) > 8 || is.fail()) {
					is.clear();
					std::cout << "Invalid Licence Plate, try again: ";
					valid = true;
				}
				else  valid = false;

				is.ignore(2000, '\n');
			} while (valid);

			int max = strlen(tempLicensePlate);
			for (int i = 0;i < max;i++)
				tempLicensePlate[i] = toupper(tempLicensePlate[i]);

			strcpy(this->m_licensePlate, tempLicensePlate);
			std::cout << "Enter Make and Model: ";
			do {
				is.get(tempModel, 62, '\n');
				if (strlen(tempModel) > 60 || strlen(tempModel) < 2 || is.fail()) {
					is.clear();
					std::cout << "Invalid Make and model, try again: ";
					valid = true;
				}
				else
					valid = false;
				is.ignore(2000, '\n');
			} while (valid);

			this->setMakeModel(tempModel);
			this->setParkingSpot(0);
		}
		return is;
	}

	std::ostream& Vehicle::write(std::ostream& os)const {
		if (this->isEmpty())
			os << "Invalid Vehicle Object" << std::endl;
		else if (this->isCsv())
			os << this->m_spotNum << "," << this->getLicensePlate() << "," << this->getMakeModel() << ",";
		else {
			os << "Parking Spot Number: ";
			(this->m_spotNum <= 0) ? os << "N/A" : os << this->m_spotNum;
			os << "\nLicence Plate: " << this->getLicensePlate() << "\nMake and Model: " << this->getMakeModel() << std::endl;
		}
		return os;
	}

	void Vehicle::setEmpty() {
		this->m_licensePlate[0] = '\0';
		this->m_model = nullptr;
		this->m_spotNum = 0;
	}

	bool Vehicle::isEmpty()const {
		return ((this->m_licensePlate[0] == '\0' && this->m_model == nullptr) || this->m_spotNum < 0) ? true : false;
	}

	const char* Vehicle::getLicensePlate()const {
		return this->m_licensePlate;
	}

	const char* Vehicle::getMakeModel()const {
		return this->m_model;
	}

	void Vehicle::setMakeModel(const char* model) {
		if (model != nullptr && model[0] != '\0') {
			if (this->m_model != nullptr)
				delete[] this->m_model;

			this->m_model = nullptr;
			this->m_model = new char[strlen(model) + 1];
			strcpy(this->m_model, model);
		}
		else
		{
			delete[] this->m_model;
			this->setEmpty();
		}
	}
}