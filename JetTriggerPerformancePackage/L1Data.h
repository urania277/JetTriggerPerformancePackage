/*--------------------------------------------------------------------
L1Data.h

L1Data is a simpler version of the EventData class containing all event observables of L1 jets.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#ifndef JetTriggerPerformancePackage_L1DATA_H
#define JetTriggerPerformancePackage_L1DATA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "TLorentzVector.h"


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>

class L1Data: public BaseJTPP
{
 public:
  L1Data(std::string jetType);
  ~L1Data();

  // fill E and pt vector
  virtual void FillEAndPTVector();

  const std::string m_jetType;

  std::vector<float>* Et;
  std::vector<float>* phi;
  std::vector<float>* eta;

  std::vector <float> E;
  std::vector <float> pt;
};

#endif // JetTriggerPerformancePackage_L1DATA_H
