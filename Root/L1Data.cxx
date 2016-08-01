/*--------------------------------------------------------------------
L1Data.cxx

L1Data is a simpler version of the EventData class containing all event observables of L1 jets.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/L1Data.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



L1Data::L1Data(std::string jetType):
    m_jetType(jetType), Et(nullptr), eta(nullptr), phi(nullptr)
{
  if (m_debug) std::cout << "Starting constructor L1Data()..." << std::endl;
}

L1Data::~L1Data()
{
  if (m_debug) std::cout << "Starting destructor L1Data()..." << std::endl;
}

void L1Data::FillEAndPTVector()
{
    if (m_debug) std::cout << "Starting destructor FillEAndPTVector()..." << std::endl;

    float energy;
    //reset E and pt vector
    E.clear();
    pt.clear();

    for (unsigned n=0; n < this->Et->size(); n++){

	// calculate E (and pt)
	energy = Et->at(n)/(sin(2*atan(exp(-eta->at(n)))));

	E.push_back(energy);
	pt.push_back(Et->at(n)); // since jets are assumed to be massless
    }
}
