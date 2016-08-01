/*--------------------------------------------------------------------
AnalysisHandler.h

AnalysisHandler contains methods concerning Matching.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/
#ifndef JetTriggerPerformancePackage_ANALYSISHANDLER_H
#define JetTriggerPerformancePackage_ANALYSISHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include "TLorentzVector.h"


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>

class AnalysisHandler: public BaseJTPP
{
 public:
  AnalysisHandler();
  virtual ~AnalysisHandler();

  virtual void  findBestMatching(std::vector<float>* refVec_pt, std::vector<float>* refVec_eta, std::vector<float>* refVec_phi, std::vector<float>* refVec_E, std::vector<float>* matchVec_pt, std::vector<float>* matchVec_eta, std::vector<float>* matchVec_phi, std::vector<float>* matchVec_E, std::vector<int> &matchingIndex, std::vector<double> &DeltaR, double DeltaRMax);

};

#endif // JetTriggerPerformancePackage_ANALYSISHANDLER_H
