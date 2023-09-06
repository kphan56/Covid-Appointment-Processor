/*-----------------------------------------------------------
Module: Menu
Filename: Menu.h
Version 1.1
Author	Kevin Phan
-----------------------------------------------------------*/

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds
{
    class Menu {
        char* m_text;
        int m_noOfSel;  
        void display()const;
    public:
        Menu();
        Menu(const char* MenuContent, int NoOfSelections);
        virtual ~Menu();
        int& operator>>(int& Selection);
        Menu (const Menu& menu);
        Menu& operator= (const Menu& menu);
    };
}


#endif
