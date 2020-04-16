#pragma once
#ifndef SDDS_VEHICLE_H_
#define SDDS_VEHICLE_H_
#include "ReadWritable.h"

namespace sdds {
	class Vehicle :public ReadWritable {
		char m_licensePlate[9];
		char* m_model;
		int m_spotNum;
	public:
		Vehicle();
		Vehicle(const char*, const char*);
		Vehicle(const Vehicle&) = delete;
		Vehicle& operator= (const Vehicle&) = delete;
		~Vehicle();
		int getParkingSpot();
		void setParkingSpot(const int spotNum);
		friend bool operator==(const Vehicle&, const char*);
		friend bool operator==(const Vehicle&, const Vehicle&);
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&)const;
	protected:
		void setEmpty();
		bool isEmpty()const;
		const char* getLicensePlate()const;
		const char* getMakeModel()const;
		void setMakeModel(const char* model);
	};
}
#endif