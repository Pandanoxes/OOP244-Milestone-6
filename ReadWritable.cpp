#include "ReadWritable.h"
namespace sdds {
	ReadWritable::ReadWritable() {
		this->flag = false;
	}

	bool ReadWritable::isCsv()const {
		return this->flag;
	}

	void ReadWritable::setCsv(bool value) {
		this->flag = value;
	}

	std::istream& operator>>(std::istream& is, ReadWritable& readWritable) {
		readWritable.read(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const ReadWritable& readWritable) {
		readWritable.write(os);
		return os;
	}
}