/*-----------------------------------------------------------
Module: Patient
Filename: Patient.h
Version 1.0
Author	Kevin Phan
-----------------------------------------------------------*/

#ifndef SDDS_PATIENT_H
#define SDDS_PATIENT_H
#include "IOAble.h"
#include "Ticket.h"

namespace sdds
{
	class Patient: public IOAble
	{
		Ticket theTicket;
		char* p_name;
		int OHIP;
		bool IOFlag;
	public:
		Patient(int t_num, bool flag);
		~Patient();
		Patient(const Patient&) = delete;
		Patient& operator = (const Patient&) = delete;
		virtual char type() const = 0;
		bool fileIO() const;
		void fileIO(bool flag);
		void setArrivalTime();
		bool operator ==(char C) const;
		bool operator ==(const Patient& P) const;
		int number() const;
		operator Time() const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}

#endif
