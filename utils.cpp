/*-----------------------------------------------------------
Module: utils
Filename: utils.cpp
Version 1.1
Author	Kevin Phan
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {

    bool debug = false; 

    int getTime()
    {
       int mins = -1;
       if (debug) {
          Time t(0);
          cout << "Enter current time: ";
          do {
             cin.clear();
             cin >> t;   
             if (!cin) {
                cout << "Invlid time, try agian (HH:MM): ";
                cin.clear();
             }
             else {
                mins = int(t);
             }
             cin.ignore(1000, '\n');
          } while (mins < 0);
       }
       else {
          time_t t = time(NULL);
          tm lt = *localtime(&t);
          mins = lt.tm_hour * 60 + lt.tm_min;
       }
       return mins;
    }


    int getInt(const char* prompt) 
    {
        char delim[128];

        if (prompt != nullptr)
        {
            cout << prompt; 
        }

        int enter;
        cin >> enter;

        while (cin.fail())
        {
            cout << "Bad integer value, try again: ";
            cin.clear(); 
            cin.ignore(150, '\n');
            cin >> enter;
            
            while (cin.get(delim, '\n'))
            {
                cout << "Enter only an integer, try again: ";
                cin.clear(); 
                cin.ignore(150, '\n');
                cin >> enter;
            }
            cin.clear();
        }
        return enter;
    }

   int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
   {
       if (prompt != nullptr)
       {
           cout << prompt; 
       }

       int enter;
       cin >> enter;

       while (cin.fail() || enter < min || enter > max)
       {
           if (cin.fail())
               do
               {
                   cout << "Bad integer value, try again: ";
                   cin.clear(); 
                   cin.ignore(150, '\n');
                   cin >> enter;
               } while (cin.fail());

           char delim[128];

           while (cin.get(delim, '\n'))
           {
               cout << "Enter only an integer, try again: ";
               cin.clear(); 
               cin.ignore(150, '\n');
               cin >> enter;
           }
           cin.clear();

           if ((enter > max) || (enter < min))
           {
               if (errorMessage != nullptr)
               {
                   cout << errorMessage;
               }
               else if (errorMessage == nullptr)
               {
                   cout << "Invalid value, retry ";
               }
               if (showRangeAtError == true)
               {
                   cout << "[" << min << " <= value <= " << max << "]: ";
               }
               
               cin.clear(); 
               cin.ignore(150, '\n');
               cin >> enter;
           }
       }
       
       return enter;
   }

   char* getcstr(const char* prompt, std::istream& istr, char delimiter)
   {
       char* s;
       string input;

       if (prompt != nullptr)
       {
           cout << prompt;
       }
       
       getline(istr, input, delimiter);
        
       s = new char[input.length() + 1];
       strcpy(s, input.c_str());

       return s;
   }
}