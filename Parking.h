#pragma once
#ifndef SDDS_PARKING_H_
#define SDDS_PARKING_H_
#define MAXSPOTS 100
#include "Menu.h"
#include"Vehicle.h"

namespace sdds {
	class Parking {
		char* m_fileName;
		Menu m_parkingMenu;
		Menu m_vehicleMenu;
		int m_numSpots;
		Vehicle* m_parkingSpot[MAXSPOTS];
		int m_numParkedVehicle;
		bool isEmpty()const;
		void parkingStatus();
		void parkVehicle();
		void returnVehcile();
		void listParkedVehicle();
		bool closeParking();
		bool exitParkingApp();
		bool loadDataFile();
		void saveDataFile()const;
		void setEmpty();
		Parking(const Parking&) = delete;
		Parking& operator=(const Parking&) = delete;
	public:
		Parking();
		Parking(const char*, int);
		~Parking();
		int run();
		bool comfirm();
	};
}
#endif