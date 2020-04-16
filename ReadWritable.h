#pragma once
#ifndef SDDS_READWRITABLE_H_
#define SDDS_READWRITABLE_H_
#include <iostream>
namespace sdds {
	class ReadWritable {
		bool flag;
	public:
		ReadWritable();
		virtual ~ReadWritable() = default;
		bool isCsv()const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream & = std::cin) = 0;
		virtual std::ostream& write(std::ostream & = std::cout)const = 0;
	};
	std::istream& operator>>(std::istream&, ReadWritable&);
	std::ostream& operator<<(std::ostream&, const ReadWritable&);
}
#endif