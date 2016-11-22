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

//TrigDecisionTool
#include "TrigDecisionTool/TrigDecisionTool.h"

class CutHandler: public BaseJTPP
{
 private:
  bool m_passedCuts;
  std::map<std::string, bool> m_passedTrigger;

  //for cutString method
  std::vector< std::string> vec_cuts;
  std::vector< std::string > vec_cut_options;
  std::vector<int> vec_index; // index of the vector, i.e. leading, subleading pt, E, etc.
  std::vector<int> vec_obs_index; // vector that simplifies the identification of the selected observable
  std::vector<int> vec_jetType_index; // index representing the jetType
  std::vector<float> vec_cutValue;

  // my Tools for handling strings
  ToolsJTPP *myTools;

  virtual float GetR(int pos1, int pos2, EventData* ED);

 public:
  CutHandler();
  CutHandler(std::string cutString);
  virtual ~CutHandler();

  virtual void Reset();
  virtual void Reset(std::vector<bool> &boolConfTriggers);
  virtual void SearchTrigger(std::vector<std::string> confTriggers, std::vector<std::string>* passedTriggersOfEvent, std::vector<bool> &boolConfTriggers);
  virtual void SearchPassBits(std::vector<std::string> confTriggers, std::vector<unsigned int> &confPassedBits, std::vector<std::string>* passBitsNames, std::vector<unsigned int>* passBits);
  //  virtual void SearchTrigger(TriggerData* TD);
  virtual void AddCut(bool status);
  virtual void AddCut(float observable, float cutValue, std::string option);
  virtual void ApplyTriggerSpecificCut(std::string triggerName, std::vector<std::string> confTriggers, std::vector<bool> &boolConfTriggers, float observable, float cutValue, std::string option);
  virtual void CheckIsolation(int pos, EventData* ED, float R, float ptMin);
  virtual void UseCutStringMethod(EventData* ED, EventData* trigED, EventData* truthED);

  virtual bool passedCuts();

private:
  virtual void InitialiseCutStringMethod(std::string cutString);
  virtual void AddCutWithThisJetType(EventData* ED, int obs_index, int index, std::string cut_options, float cut_value);

};

#endif // JetTriggerPerformancePackage_CUTHANDLER_H
