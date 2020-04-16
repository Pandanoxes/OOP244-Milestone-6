#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "Menu.h"

namespace sdds {
	MenuItem::MenuItem() {
		this->item = nullptr;
	}

	MenuItem::MenuItem(const char* item_) {
		if (item_ != nullptr && item_[0] != '\0') {
			this->item = nullptr;
			this->item = new char[strlen(item_) + 1];
			strcpy(this->item, item_);
		}
		else
			this->item = nullptr;
	}

	std::ostream& MenuItem::display(std::ostream& os)const {
		if (this->item != nullptr)
			os << this->item << std::endl;
		return os;
	}

	MenuItem::~MenuItem() {
		delete[] this->item;
		this->item = nullptr;
	}

	Menu::Menu() {
		this->setEmpty();
	}

	Menu::Menu(const char* title_, int indentation_) {
		if (title_ != nullptr && title_[0] != '\0') {
			this->title = nullptr;
			this->title = new char[strlen(title_) + 1];
			strcpy(this->title, title_);
			this->indentation = indentation_;
			this->num = 0;
		}
		else
			*this = Menu();
	}

	Menu::Menu(const Menu& menu_) {
		this->setEmpty();
		*this = menu_;
	};

	Menu& Menu::operator=(const Menu& menu_) {
		if (this != &menu_) {
			if (!menu_.isEmpty()) {
				if (this->num != 0 && this->menuItem[0] != nullptr)
					this->emptyMenuItem();
				*this = menu_.title;
				for (int i = 0; i < menu_.num;i++)
					this->add(menu_.menuItem[i]->item);
				this->num = menu_.num;
				this->indentation = menu_.indentation;
			}
			else {
				this->emptyMenuItem();
				this->emptyTitle();
				this->setEmpty();
			}
		}
		return *this;
	}

	Menu:: operator bool() const {
		return (this->title != nullptr) ? true : false;
	}

	bool Menu::isEmpty()const {
		return (this->title == nullptr) ? true : false;
	}

	std::ostream& Menu::display(std::ostream& os)const {
		if (this->isEmpty())
			os << "Invalid Menu!" << std::endl;
		else {
			this->indent();
			os << this->title << std::endl;
			if (num == 0)
				os << "No Items to display!" << std::endl;
			else {
				for (int i = 0; i < this->num;i++) {
					this->indent();
					os << i + 1 << "- ";
					this->menuItem[i]->display(os);
				}
				this->indent();
				os << "> ";
			}
		}
		return os;
	}

	Menu& Menu:: operator = (const char* newTitle) {
		if (newTitle[0] != '\0') {
			this->emptyTitle();
			this->title = new char[strlen(newTitle) + 1];
			strcpy(this->title, newTitle);
		}
		return *this;
	}

	void Menu::add(const char* menuItem_) {
		if (menuItem_ == nullptr) {
			if (!isEmpty())
				this->emptyTitle();
			this->emptyMenuItem();
			this->indentation = 0;
			this->num = 0;
		}
		else {
			if (this->num < 10 && title != nullptr) {
				menuItem[this->num] = new MenuItem(menuItem_);
				this->num++;
			}
		}
	}

	Menu& Menu::operator<<(const char* menuItemName) {
		this->add(menuItemName);
		return *this;
	}

	int Menu::run()const {
		int i = 0;
		this->display();
		if (this->num != 0)
		{
			std::cin >> i;
			while (std::cin.fail() || i <= 0 || i > this->num) {
				(std::cin.fail()) ? std::cout << "Invalid Integer, try again: " : std::cout << "Invalid selection, try again: ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cin >> i;
			}
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		return i;
	}

	Menu::operator int()const {
		return run();
	}

	Menu::~Menu() {
		this->emptyTitle();
		this->emptyMenuItem();
	}

	void Menu::indent() const {
		for (int i = 0;i < this->indentation;i++)
			std::cout << "    ";
	}

	void Menu::setEmpty() {
		this->title = nullptr;
		this->indentation = 0;
		this->num = 0;
	}

	void Menu::emptyTitle() {
		delete[] this->title;
		this->title = nullptr;
	}

	void Menu::emptyMenuItem() {
		for (int i = 0; i < this->num;i++) {
			delete this->menuItem[i];
			this->menuItem[i] = nullptr;
		}
	}
}