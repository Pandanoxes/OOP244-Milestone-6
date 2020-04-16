#pragma once
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include <iostream>

namespace sdds {
#define MAX_NO_OF_ITEMS 10
	class Menu;
	class MenuItem
	{
		friend class Menu;
		char* item;
		MenuItem();
		MenuItem(const char*);
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem&) = delete;
		std::ostream& display(std::ostream& os = std::cout)const;
		~MenuItem();
	};
	class Menu {
		MenuItem* menuItem[MAX_NO_OF_ITEMS];
		char* title;
		int indentation;
		int num;
	public:
		Menu();
		Menu(const char*, int indentation_ = 0);
		Menu(const sdds::Menu&);
		Menu& operator=(const Menu&);
		operator bool()const;
		bool isEmpty()const;
		std::ostream& display(std::ostream& os = std::cout)const;
		Menu& operator= (const char*);
		void add(const char*);
		Menu& operator<<(const char*);
		int run()const;
		operator int()const;
		~Menu();
		void indent()const;
		void setEmpty();
		void emptyTitle();
		void emptyMenuItem();
	};
}
#endif