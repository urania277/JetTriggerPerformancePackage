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

float EventData::GetMjj(int i=0, int j=1)
{
    if (m_debug) std::cout << "Starting method Mjj()..." << std::endl;

    // crosscheck vector size
    if ((pt->size() < (i+1)) || (pt->size() < (j+1))) return 0.0;

    TLorentzVector vec1;
    TLorentzVector vec2;

    // fill Lorentz vectors
    vec1.SetPtEtaPhiE(pt->at(i), eta->at(i), phi->at(i), E->at(i));
    vec2.SetPtEtaPhiE(pt->at(j), eta->at(j), phi->at(j), E->at(j));

    // combine vectors
    TLorentzVector vecSum = vec1 + vec2;

    // return invariant mass
    return vecSum.M();
}

float EventData::GetYStar(int i=0, int j=1)
{
    if (m_debug) std::cout << "Starting method yStar()..." << std::endl;

    // crosscheck vector size
    if ((pt->size() < (i+1)) || (pt->size() < (j+1))) return -999.0;

    TLorentzVector vec1;
    TLorentzVector vec2;

    // fill Lorentz vectors
    vec1.SetPtEtaPhiE(pt->at(i), eta->at(i), phi->at(i), E->at(i));
    vec2.SetPtEtaPhiE(pt->at(j), eta->at(j), phi->at(j), E->at(j));

    // calculate rapidity and return yStar
    return 0.5* fabs(vec1.Rapidity() - vec2.Rapidity());
}

float EventData::GetHT()
{
    if (m_debug) std::cout << "Starting method GetHT()..." << std::endl;

    float HT = 0.0;

    // sum over all pt
    for (int j=0; j < pt->size(); j++){
        HT += pt->at(j);
    }

}
