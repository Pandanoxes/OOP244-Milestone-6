#define _CRT_SECURE_NO_WARNINGS
#include"Parking.h"
#include"Car.h"
#include"Motorcycle.h"
#include <fstream>

#include <string.h>
#include <string>
namespace sdds {
	Parking::Parking() {
		this->setEmpty();
	}

	Parking::Parking(const char* fileName, int numSpots) {
		if ((fileName != nullptr && fileName[0] != '\0') && (numSpots >= 10 && numSpots <= MAXSPOTS)) {
			this->m_fileName = new char[strlen(fileName) + 1];
			strcpy(this->m_fileName, fileName);
			this->m_numSpots = numSpots;
			for (int i = 0;i < numSpots;i++)
				this->m_parkingSpot[i] = nullptr;
			this->m_numParkedVehicle = 0;
		}
		else
			this->setEmpty();
		if (this->loadDataFile()) {
			this->m_parkingMenu = Menu("Parking Menu, select an action:");
			this->m_parkingMenu << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Close Parking (End of day)" << "Exit Program";
			this->m_vehicleMenu = Menu("Select type of the vehicle:", 1);
			this->m_vehicleMenu << "Car" << "Motorcycle" << "Cancel";
		}
		else {
			std::cout << "Error in data file" << std::endl;
			this->setEmpty();
		}
	}

	Parking::~Parking() {
		delete[] m_fileName;
		for (int i = 0;i < this->m_numSpots;i++) {
			if (this->m_parkingSpot[i] != nullptr)
			{
				delete this->m_parkingSpot[i];
				this->m_parkingSpot[i] = nullptr;
			}
		}
	}

	bool Parking::isEmpty()const {
		return (this->m_fileName == nullptr) ? true : false;
	}

	void Parking::parkingStatus() {
		std::cout << "****** Seneca Valet Parking ******\n*****  Available spots: ";
		std::cout.setf(std::ios::left);
		std::cout.width(4);
		std::cout << (this->m_numSpots - this->m_numParkedVehicle);
		std::cout.unsetf(std::ios::left);
		std::cout << " *****" << std::endl;
	}

	void Parking::parkVehicle() {
		if (this->m_numParkedVehicle < this->m_numSpots) {
			bool valid = true;
			int selection = this->m_vehicleMenu.run();

			switch (selection) {
			case 1: {
				for (int i = 0;i < this->m_numSpots;i++) {
					if (this->m_parkingSpot[i] == nullptr) {
						this->m_parkingSpot[i] = new Car();
						std::cin >> *this->m_parkingSpot[i];
						for (int j = 0;j < this->m_numSpots;j++) {
							if (i == j)
								continue;
							if (this->m_parkingSpot[j] != nullptr) {
								if (*this->m_parkingSpot[i] == *this->m_parkingSpot[j]) {
									std::cout << "\nCan not park; license plate already in the system!" << std::endl;
									std::cout << *this->m_parkingSpot[i];
									std::cout << std::endl;
									valid = false;
									delete this->m_parkingSpot[i];
									this->m_parkingSpot[i] = nullptr;
									break;
								}
								else
									valid = true;
							}
						}
						if (valid) {
							m_parkingSpot[i]->setParkingSpot(i + 1);
							std::cout << "\nParking Ticket" << std::endl;
							std::cout << *this->m_parkingSpot[i];
							this->m_numParkedVehicle++;
							std::cout << std::endl;
						}
						break;
					}
				}
			}
				  break;
			case 2: {
				for (int i = 0;i < this->m_numSpots;i++) {
					if (this->m_parkingSpot[i] == nullptr) {
						this->m_parkingSpot[i] = new Motorcycle();
						std::cin >> *this->m_parkingSpot[i];
						for (int j = 0;j < this->m_numSpots;j++) {
							if (i == j)
								continue;
							if (this->m_parkingSpot[j] != nullptr) {
								if (*this->m_parkingSpot[i] == *this->m_parkingSpot[j]) {
									std::cout << "\nCan not park; license plate already in the system!" << std::endl;
									std::cout << *this->m_parkingSpot[i];
									std::cout << std::endl;
									valid = false;
									delete this->m_parkingSpot[i];
									this->m_parkingSpot[i] = nullptr;
									break;
								}
								else
									valid = true;
							}
						}
						if (valid) {
							m_parkingSpot[i]->setParkingSpot(i + 1);
							std::cout << "\nParking Ticket" << std::endl;
							std::cout << *this->m_parkingSpot[i];
							this->m_numParkedVehicle++;
							std::cout << std::endl;
						}
						break;
					}
				}
			}
				  break;
			case 3:
				std::cout << "Parking cancelled" << std::endl;
				break;
			}
		}
		else
			std::cout << "Parking is full" << std::endl;
	}

	void Parking::returnVehcile() {
		bool found = false;
		char tempLicensePlate[10];
		std::cout << "Return Vehicle" << std::endl;
		std::cout << "Enter Licence Plate Number: ";
		do {
			std::cin.get(tempLicensePlate, 10, '\n');
			std::cin.ignore(2000, '\n');
			int max = strlen(tempLicensePlate);
			for (int i = 0; i < max;i++)
				tempLicensePlate[i] = toupper(tempLicensePlate[i]);

			if (strlen(tempLicensePlate) > 8 || strlen(tempLicensePlate) < 1)
				std::cout << "Invalid Licence Plate, try again: ";
		} while (strlen(tempLicensePlate) > 8 || strlen(tempLicensePlate) < 1);
		for (int i = 0;i < this->m_numSpots;i++)
		{
			if (this->m_parkingSpot[i] != nullptr) {
				if (*this->m_parkingSpot[i] == tempLicensePlate) {
					found = true;
					std::cout << "\nReturning: " << std::endl;
					std::cout << *this->m_parkingSpot[i];
					std::cout << std::endl;
					delete this->m_parkingSpot[i];
					this->m_parkingSpot[i] = nullptr;
					this->m_numParkedVehicle--;
					break;
				}
			}
		}
		if (!found)
			std::cout << "\nLicense plate " << tempLicensePlate << " Not found\n" << std::endl;
	}

	void Parking::listParkedVehicle() {
		std::cout << "*** List of parked vehicles ***" << std::endl;
		for (int i = 0;i < this->m_numSpots;i++) {
			if (this->m_parkingSpot[i] != nullptr) {
				std::cout << *this->m_parkingSpot[i];
				std::cout << "-------------------------------" << std::endl;
			}
		}
	}

	bool Parking::closeParking() {
		bool valid = false;
		std::cout << "This will Remove and tow all remaining vehicles from the parking!" << std::endl;
		std::cout << "Are you sure? (Y)es/(N)o: ";
		valid = comfirm();
		if (valid) {
			std::cout << "Closing Parking" << std::endl;
			for (int i = 0;i < this->m_numSpots;i++) {
				if (this->m_parkingSpot[i] != nullptr) {
					std::cout << "\nTowing request\n" << "*********************" << std::endl;
					std::cout << *this->m_parkingSpot[i];
					delete this->m_parkingSpot[i];
					this->m_parkingSpot[i] = nullptr;
					this->m_numParkedVehicle--;
				}
			}
		}
		return valid;
	}

	bool Parking::exitParkingApp() {
		bool valid = false;
		std::cout << "This will terminate the program!\nAre you sure? (Y)es/(N)o: ";
		valid = comfirm();
		return valid;
	}

	bool Parking::loadDataFile() {
		bool valid = false;

		if (!this->isEmpty()) {
			std::ifstream file(this->m_fileName);
			char tempFirstChar;
			if (file.is_open()) {
				valid = true;

				while (!file.eof() && valid && this->m_numSpots >= this->m_numParkedVehicle) {
					Vehicle* tempVehicle = nullptr;
					if (file.get(tempFirstChar)) {
						file.ignore();

						if (tempFirstChar == 'M')
							tempVehicle = new Motorcycle();
						else if (tempFirstChar == 'C')
							tempVehicle = new Car();
						if (tempVehicle) {
							tempVehicle->setCsv(true);
							file >> *tempVehicle;
							tempVehicle->setCsv(false);
							if (file) {
								this->m_parkingSpot[tempVehicle->getParkingSpot() - 1] = tempVehicle;
								this->m_numParkedVehicle++;
							}
							else {
								delete tempVehicle;
								valid = false;
							}
						}
					}
				}
				file.close();
			}
		}
		return valid;
	}

	void Parking::saveDataFile()const {
		if (!this->isEmpty()) {
			std::ofstream file(this->m_fileName);
			if (file.is_open()) {
				for (int i = 0; i < this->m_numSpots;i++) {
					if (this->m_parkingSpot[i] != nullptr) {
						this->m_parkingSpot[i]->setCsv(true);
						file << *this->m_parkingSpot[i];
					}
				}
				file.close();
			}
		}
	}

	int Parking::run() {
		int i = 0;
		if (!this->isEmpty()) {
			bool valid = false;
			while (!valid) {
				this->parkingStatus();
				int selection = this->m_parkingMenu.run();
				switch (selection) {
				case 1:
					this->parkVehicle();
					break;
				case 2:
					this->returnVehcile();
					break;
				case 3:
					this->listParkedVehicle();
					break;
				case 4:
					valid = this->closeParking();
					if (valid)
						this->saveDataFile();
					else
						std::cout << "Aborted!" << std::endl;
					break;
				case 5:
					valid = this->exitParkingApp();
					if (valid) {
						std::cout << "Exiting program!" << std::endl;
						this->saveDataFile();
					}
					break;
				}
			}
		}
		else
			i = 1;
		return i;
	}

	void Parking::setEmpty() {
		this->m_fileName = nullptr;
		this->m_parkingMenu = Menu();
		this->m_vehicleMenu = Menu();
		this->m_numSpots = 0;
		this->m_numParkedVehicle = 0;
		for (int i = 0;i < MAXSPOTS;i++)
			this->m_parkingSpot[i] = nullptr;
	}

	bool Parking::comfirm() {
		std::string comfirm;
		std::cin >> comfirm;
		while ((comfirm != "Y" && comfirm != "y") && (comfirm != "N" && comfirm != "n")) {
			std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			std::cin >> comfirm;
		}
		std::cin.ignore(2000, '\n');
		return (comfirm == "Y" || comfirm == "y") ? true : false;
	}
}