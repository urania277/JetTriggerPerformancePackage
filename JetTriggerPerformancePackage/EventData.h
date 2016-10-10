/*--------------------------------------------------------------------
EventData.h

EventData contains the event observables of one jet type (offline, trigger, truth etc.).

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#ifndef JetTriggerPerformancePackage_EVENTDATA_H
#define JetTriggerPerformancePackage_EVENTDATA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "TLorentzVector.h"


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>

class EventData: public BaseJTPP
{
 public:
  EventData(std::string jetType);
  ~EventData();

  // check if lead and sublead are good, so scalar obsverables are good for using
  virtual bool isLSGood();

  // determine the "transverse energy" of the particle using E, pt, phi and eta
  virtual float GetEt(int n);
  virtual float GetMjj(int i, int j);
  virtual float GetYStar(int i, int j);
  virtual float GetHT();

  const std::string m_jetType;

  //Standard kinematic observables
  std::vector<float>* E;
  std::vector<float>* pt;
  std::vector<float>* phi;
  std::vector<float>* eta;
  float mjj;
  float m23;

  //Only for Data samples:
  std::vector<int>* passedCleaning;

  // one vector that decribes if jet is good for plotting or not
  std::vector<bool> isGood; //e.g. passed Cleaning


  //More kinematic observables
  float yStar;
  float deltaPhi;
  float pTBalance;
  float MHT;
  float MHTPhi;
  std::vector<float>*   EMFrac;
  std::vector<float>*   HECFrac;
  std::vector<float>*   FracSamplingMax;
  std::vector<float>*   Timing;
};

#endif // JetTriggerPerformancePackage_EVENTDATA_H
