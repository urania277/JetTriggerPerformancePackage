/*--------------------------------------------------------------------
EventData.cxx

EventData contains the event observables of one jet type (offline, trigger, truth etc.).

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/


#include <JetTriggerPerformancePackage/EventData.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "TLorentzVector.h"



EventData::EventData(std::string jetType):
    m_jetType(jetType), E(nullptr), pt(nullptr), eta(nullptr), phi(nullptr), mjj(0), m23(0), passedCleaning(nullptr), Timing(nullptr)
{
  if (m_debug) std::cout << "Starting constructor EventData()..." << std::endl;
}

EventData::~EventData()
{
  if (m_debug) std::cout << "Starting destructor EventData()..." << std::endl;
}

bool EventData::isLSGood()
{
    if (m_debug) std::cout << "Starting destructor isLSGood()..." << std::endl;
    if ((isGood.at(0)) && (isGood.at(1))) return true;
    else return false;
}

// calculate transverse Energy
float EventData::GetEt(int n)
{
    if (m_debug) std::cout << "Starting destructor GetEt()..." << std::endl;

    TLorentzVector vec;
    vec.SetPtEtaPhiE(pt->at(n), eta->at(n), phi->at(n), E->at(n));

    return vec.Et();
}
