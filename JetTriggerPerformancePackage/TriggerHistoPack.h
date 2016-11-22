/*--------------------------------------------------------------------
TriggerHistoPack.h

TriggerHistoPack is a compact class managing all kinematic and response histograms of one specific trigger.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/


#ifndef JetTriggerPerformancePackage_TRIGGERHISTOPACK_H
#define JetTriggerPerformancePackage_TRIGGERHISTOPACK_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "TLorentzVector.h"


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>
#include <JetTriggerPerformancePackage/HistogramMatrix.h>
#include <JetTriggerPerformancePackage/ResponseMatrix.h>
#include <JetTriggerPerformancePackage/KinematicMatrix.h>
#include <JetTriggerPerformancePackage/AnalysisHandler.h>
#include <JetTriggerPerformancePackage/EventData.h>
#include <JetTriggerPerformancePackage/ConfigStatus.h>
#include <JetTriggerPerformancePackage/ToolsJTPP.h>


class TriggerHistoPack: public BaseJTPP
{
 private:
  const std::string m_triggerDir;
  const std::string m_trigger;

  const int  m_nthJet;


 public:
  // method
  TriggerHistoPack(std::string triggerDir, std::string trigger, int nthJet, ConfigStatus* a_CS);
  virtual ~TriggerHistoPack();

  void BookAll(EL::Worker* wk);
  void FillAll(EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet, std::vector<int> &matchingIndexList_TriggvsOff, std::vector<int> &matchingIndexList_OffvsTruth, std::vector<int> &matchingIndexList_TriggvsTruth, double m_weight);

 private:
  //ConfigStatus
  ConfigStatus* CS;

  // myTools
  ToolsJTPP* myTools;

  // member variables
  ResponseMatrix* ptRespOffVsTruthMatrix; 
  ResponseMatrix* ptRespTrigVsTruthMatrix; 
  ResponseMatrix* ptRespTrigVsOffMatrix; 

  //  ResponseMatrix* ptRespOffVsTruthMatrixPtBins; 
  //  ResponseMatrix* ptRespTrigVsTruthMatrixPtBins; 
  //  ResponseMatrix* ptRespTrigVsOffMatrixPtBins; 

  //  ResponseMatrix* ptRespOffVsTruthMatrixEtaBins; 
  //  ResponseMatrix* ptRespTrigVsTruthMatrixEtaBins; 
  //  ResponseMatrix* ptRespTrigVsOffMatrixEtaBins; 

  ResponseMatrix* mjjRespOffVsTruthMatrix; 
  ResponseMatrix* mjjRespTrigVsTruthMatrix; 
  ResponseMatrix* mjjRespTrigVsOffMatrix; 

  std::vector<std::string> m_jetType;
  std::map<std::string, KinematicMatrix*> m_kinematicMap; 
};

#endif // JetTriggerPerformancePackage_TRIGGERHISTOPACK_H
