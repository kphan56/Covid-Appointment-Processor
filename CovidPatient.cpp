/*-----------------------------------------------------------
Module: CovidPatient
Filename: CovidPatient.cpp
Version 1.0
Author	Kevin Phan
-----------------------------------------------------------*/

#include <iostream>
#include "CovidPatient.h"
using namespace std;
namespace sdds {
   int nextCovidTicket = 1;

   CovidPatient::CovidPatient() : Patient(nextCovidTicket, false)
   {
	   nextCovidTicket++;
   }

   char CovidPatient::type() const
   {
	   return 'C';
   }

   istream& CovidPatient::csvRead(istream& istr)
   {
	   Patient::csvRead(istr);
	   nextCovidTicket = number() + 1;
	   istr.ignore(200, '\n');
	   return istr;
   }

   istream& CovidPatient::read(istream& istr)
   {
	   if (fileIO() == true)
	   {
		   istr.ignore(2000, '\n');
		   csvRead(istr);
	   }
	   else
	   {
		   Patient::read(istr);
	   }
	   return istr;
   }

   ostream& CovidPatient::write(ostream& ostr) const
   {
	   if (fileIO() == true)
	   {
		   Patient::csvWrite(ostr);
	   }
	   else
	   {
		   ostr << "COVID TEST" << endl;
		   Patient::write(ostr) << endl;
	   }
	   return ostr;
   }
}