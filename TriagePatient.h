/*-----------------------------------------------------------
Module: TriagePatient
Filename: TriagePatient.h
Version 1.0
Author	Kevin Phan
-----------------------------------------------------------*/

#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
#include "Patient.h"
namespace sdds {
	class TriagePatient : public Patient
	{
		char* symptoms;
	public:
		TriagePatient();
		~TriagePatient();
		virtual char type() const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}
#endif


