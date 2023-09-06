/*-----------------------------------------------------------
Module: CovidPatient
Filename: CovidPatient.h
Version 1.0
Author	Kevin Phan
-----------------------------------------------------------*/

#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_
#include "Patient.h"
namespace sdds {
	class CovidPatient : public Patient
	{
	public:
		CovidPatient();
		virtual char type() const;
		std::ostream& write(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::istream& read(std::istream& istr);
	};
}
#endif



