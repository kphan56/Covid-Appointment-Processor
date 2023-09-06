/*-----------------------------------------------------------
Module: TriagePatient
Filename: TriagePatient.cpp
Version 1.0
Author	Kevin Phan
-----------------------------------------------------------*/

#include "TriagePatient.h"
#include "utils.h"

using namespace std;
namespace sdds {
   int nextTriageTicket = 1;

   TriagePatient::TriagePatient() : Patient(nextTriageTicket, true)
   {
	   symptoms = nullptr;
	   nextTriageTicket++;
   }
   
   TriagePatient::~TriagePatient()
   {
	   delete[] symptoms;
   }

   char TriagePatient::type() const
   {
	   return 'T';
   }

   ostream& TriagePatient::csvWrite(ostream& ostr)const
   {
	   Patient::csvWrite(ostr);
	   ostr << ",";
	   ostr << symptoms;
	   return ostr;
   }

   istream& TriagePatient::csvRead(istream& istr)
   {
	   delete[] symptoms;
	   Patient::csvRead(istr);
	   istr.ignore(200, ',');
	   symptoms = getcstr(nullptr, istr, '\n');
	   nextTriageTicket = number() + 1;
	   return istr;
   }

   ostream& TriagePatient::write(ostream& ostr)const
   {
	   if (fileIO() == true)
	   {
		   csvWrite(ostr);
	   }
	   else
	   {
		   ostr << "TRIAGE" << endl;
		   Patient::write(ostr);
		   ostr << endl;
		   ostr << "Symptoms: " << symptoms << endl;
	   }
	   return ostr;
   }

   istream& TriagePatient::read(istream& istr)
   {
	   if (fileIO() == true)
	   {
		   csvRead(istr);
	   }
	   else
	   {
		   delete[] symptoms;
		   symptoms = nullptr;
		   Patient::read(istr);
		   istr.ignore(2000, '\n');
		   symptoms = getcstr("Symptoms: ", istr, '\n');
	   }
	   return istr;
   }
}