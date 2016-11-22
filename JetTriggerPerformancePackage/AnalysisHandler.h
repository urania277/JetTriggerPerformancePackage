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
#include <JetTriggerPerformancePackage/EventData.h>

class AnalysisHandler: public BaseJTPP
{
 public:
  AnalysisHandler();
  virtual ~AnalysisHandler();

  virtual void  findBestMatching(EventData* ED_ref, EventData* ED_match, std::vector<int> &matchingIndex, std::vector<double> &DeltaR, double DeltaRMax);

};

#endif // JetTriggerPerformancePackage_ANALYSISHANDLER_H
