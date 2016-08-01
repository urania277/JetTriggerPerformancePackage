/*--------------------------------------------------------------------
CutHandler.h

CutHandler is a compact class containing all necessary methods to apply cuts in kinematics or turnons.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/


#ifndef JetTriggerPerformancePackage_CUTHANDLER_H
#define JetTriggerPerformancePackage_CUTHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "TLorentzVector.h"


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>
#include <JetTriggerPerformancePackage/EventData.h>
#include <JetTriggerPerformancePackage/TriggerData.h>

class CutHandler: public BaseJTPP
{
 private:
  bool m_passedCuts;
  std::map<std::string, bool> m_passedTrigger;

  virtual float GetR(int pos1, int pos2, EventData* ED);

 public:
  CutHandler();
  virtual ~CutHandler();

  virtual void Reset();
  virtual void Reset(std::vector<bool> &boolConfTriggers);
  virtual void SearchTrigger(std::vector<std::string> confTriggers, std::vector<std::string>* passedTriggersOfEvent, std::vector<bool> &boolConfTriggers);
  //  virtual void SearchTrigger(TriggerData* TD);
  virtual void AddCut(bool status);
  virtual void AddCut(float observable, float cutValue, std::string option);
  virtual void ApplyTriggerSpecificCut(std::string triggerName, std::vector<std::string> confTriggers, std::vector<bool> &boolConfTriggers, float observable, float cutValue, std::string option);
  virtual void CheckIsolation(int pos, EventData* ED, float R, float ptMin);

  virtual bool passedCuts();
};

#endif // JetTriggerPerformancePackage_CUTHANDLER_H
