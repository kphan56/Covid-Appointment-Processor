/*-----------------------------------------------------------
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	Kevin Phan
-----------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include "Menu.h"
#include "utils.h"

using namespace std;
namespace sdds
{
	Menu::Menu()
	{
		m_text = nullptr;
		m_noOfSel = 0;
	}
	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{
		m_text = nullptr;
		m_noOfSel = NoOfSelections;
		m_text = new char[strlen(MenuContent) + 1];
		strcpy(m_text, MenuContent);
	}

	Menu::~Menu()
	{
		delete[] m_text;
	}

	Menu::Menu(const Menu& menu)
	{
		m_text = nullptr;
		m_noOfSel = menu.m_noOfSel;

		m_text = new char[strlen(menu.m_text) + 1];
		strcpy(m_text, menu.m_text);
	}

	Menu& Menu::operator= (const Menu& menu)
	{
		if (this != &menu)
		{
			delete[] m_text;
			m_text = nullptr;
			m_noOfSel = menu.m_noOfSel;
			m_text = new char[strlen(menu.m_text) + 1];
			strcpy(m_text, menu.m_text);
		}
		return *this;
	}

	void Menu::display() const
	{
		cout << m_text << endl;
		cout << "0- Exit" << endl;
	}

	int& Menu::operator>>(int& Selection)
	{
		Selection = 0;
		int minVal = 0;
		display();
		Selection = getInt(minVal, m_noOfSel, "> ", "Invalid option ", true);
		return Selection;
	}
}
