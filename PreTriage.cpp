/*-----------------------------------------------------------
Module: PreTriage
Filename: PreTriage.cpp
Version 1.0
Author	Kevin Phan
-----------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "PreTriage.h"

using namespace std;
namespace sdds
{
	PreTriage::PreTriage(const char* dataFilename)
	{
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		m_appMenu = Menu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2);
		m_pMenu = Menu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2);
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		load();
	}


	void PreTriage::run(void)
	{
		int selection;
		m_appMenu >> selection;
		switch (selection)
		{
		case 0:
			break;
		case 1:
			reg();
			break;
		case 2:
			admit();
			break;
		}
	}


	PreTriage::~PreTriage()
	{
		int row = 0;

		ofstream fout;
		fout.open(m_dataFilename);

		fout << m_averCovidWait << "," << m_averTriageWait << endl;
		cout << "Saving Average Wait Times,\n";
		cout << "   COVID Test: " << m_averCovidWait << "\n";
		cout << "   Triage: " << m_averTriageWait << "\n";

		cout << "Saving m_lineup...\n";

		if (fout.is_open())
		{
			while (row < m_lineupSize)
			{
				m_lineup[row]->fileIO(true);
				fout << *m_lineup[row] << endl;
				cout << row + 1 << "- " << *m_lineup[row];
				cout << endl;
				row++;
			}
		}
		fout.close();

		for (auto i = 0; i < m_lineupSize; ++i)
		{
			removePatientFromLineup(i);
			i--;
		}
		delete[] m_dataFilename;
		m_dataFilename = nullptr;
		cout << "done!\n";
	}

	void PreTriage::load()
	{
		cout << "Loading data...\n";
		ifstream fin;
		fin.open(m_dataFilename);
		char commaDelim = ',';
		Patient* thePatient = nullptr;
		char d;

		if (fin.is_open() && fin.get(d))
		{
			fin >> m_averCovidWait >> commaDelim;
			fin >> m_averTriageWait; 
			fin.get(d);

			while (fin.get(d) && m_lineupSize < maxNoOfPatients)
			{
				if (d == 'C')
				{
					thePatient = new CovidPatient();
				}
				else if (d == 'T')
				{
					thePatient = new TriagePatient();
				}
				else
				{
					break;
				}

				if (thePatient != nullptr)
				{
					thePatient->fileIO(true); 
					thePatient->csvRead(fin.get(d));
					thePatient->fileIO(false);
					m_lineup[m_lineupSize] = thePatient; 
					m_lineupSize++;
				}
			}
		}

		if (m_lineupSize >= maxNoOfPatients)
		{
			cout << "Warning: number of records exceeded 100\n";
		}
		if (m_lineupSize == 0)
		{
			cout << "No data or bad data file!\n";
		}
		if (m_lineupSize != 0)
		{
			cout << m_lineupSize << " Records imported...\n";
		}

		cout << endl;

		fin.close();
	}

	void PreTriage::reg()
	{
		if (m_lineupSize >= maxNoOfPatients)
		{
			cout << "Line up full!\n";
		}
		else
		{
			int selection;
			m_pMenu >> selection;
			switch (selection)
			{
			case 1:
			for (auto i = 0; i < maxNoOfPatients; ++i)
			{
				if (m_lineup[i] == nullptr)
				{
					m_lineup[i] = new CovidPatient();
					m_lineup[i]->setArrivalTime();
					cout << "Please enter patient information: \n";
					cin >> *m_lineup[i];
					cout << "\n";
					cout << "******************************************\n";
					cout << *m_lineup[i];
					cout << "Estimated Wait Time: ";
					cout << getWaitTime(*m_lineup[i]) << endl;
					cout << "******************************************\n\n";
					m_lineupSize++;
					break;
				}
			}
			break;

			case 2:
			for (auto i = 0; i < maxNoOfPatients; ++i)
			{
				if (m_lineup[i] == nullptr)
				{
					m_lineup[i] = new TriagePatient();
					m_lineup[i]->setArrivalTime(); 
					cout << "Please enter patient information: \n";
					m_lineup[i]->fileIO(false);
					cin >> *m_lineup[i];
					cout << "\n";
					cout << "******************************************\n";
					cout << *m_lineup[i];
					cout << "Estimated Wait Time: ";
					cout << getWaitTime(*m_lineup[i]) << endl;
					cout << "******************************************\n\n";
					m_lineupSize++;
					break;
				}
			}
			break;
			}
		}
		run();
	}

	const Time PreTriage::getWaitTime(const Patient& p)const
	{
		unsigned int noOfPats = 0;
		if (p.type() == 'C')
		{
			for (auto i = 0; i < m_lineupSize; ++i) 
			{
				if (m_lineup[i]->type() == p.type()) 
				{
					noOfPats++;
				}
			}
			return m_averCovidWait * noOfPats;
		}
		else
		{
			for (auto i = 0; i < m_lineupSize; ++i)
			{
				if (m_lineup[i]->type() == p.type())
				{
					noOfPats++;
				}
			}
			return m_averTriageWait * noOfPats;
		}
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		if (p.type() == 'C')
		{
			m_averCovidWait = ((m_averCovidWait.setToNow() - Time(p)) + (m_averCovidWait * ((unsigned int)p.number() - 1))) / (unsigned int)p.number();
		}
		if (p.type() == 'T')
		{
			m_averTriageWait = ((m_averTriageWait.setToNow() - Time(p)) + (m_averTriageWait * ((unsigned int)p.number() - 1))) / (unsigned int)p.number();
		}
	}

	int PreTriage::indexOfFirstInLine(char type) const
	{
		int index;
		for (auto i = 0; i < m_lineupSize; ++i)
		{
			if (m_lineup[i]->type() == type)
			{
				index = i;
				return index;
			}
		}
		return -1;
	}

	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	void PreTriage::admit()
	{
		int selection;
		m_pMenu >> selection;
		switch (selection)
		{
		case 0:
			break;
		case 1:
			indexOfFirstInLine('C');
			if (indexOfFirstInLine('C') == -1)
			{
				break;
			}
			else
			{
				int i = indexOfFirstInLine('C');
				cout << '\n';
				cout << "******************************************\n";
				m_lineup[i]->fileIO(false);
				cout << "Calling for " << *m_lineup[i];
				cout << "******************************************\n\n";
				setAverageWaitTime(*m_lineup[i]);
				removePatientFromLineup(i);
				break;
			}
		case 2:
			indexOfFirstInLine('T');
			if (indexOfFirstInLine('T') == -1)
			{
				break;
			}
			else
			{
				int i = indexOfFirstInLine('T');
				cout << '\n';
				cout << "******************************************\n";
				m_lineup[i]->fileIO(false);
				cout << "Calling for " << *m_lineup[i];
				cout << "******************************************\n\n";
				setAverageWaitTime(*m_lineup[i]);
				removePatientFromLineup(i);
				break;
			}
		}
		run();
	}
}