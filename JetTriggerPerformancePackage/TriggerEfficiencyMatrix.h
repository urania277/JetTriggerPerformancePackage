/*--------------------------------------------------------------------
TriggerEfficiencyMatrix.h

In TriggerEfficiencyMatrix the turnons plots are created and stored.
Also the methods for the turnon specific event selection can be found here.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#ifndef JetTriggerPerformancePackage_TRIGGEREFFICIENCYMATRIX_H
#define JetTriggerPerformancePackage_TRIGGEREFFICIENCYMATRIX_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iterator>

// Root intern
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>

// EventLoop
#include <EventLoop/Worker.h>

//Own classes
#include <JetTriggerPerformancePackage/HistogramMatrix.h>
#include <JetTriggerPerformancePackage/EventData.h>
#include <JetTriggerPerformancePackage/L1Data.h>
#include <JetTriggerPerformancePackage/TriggerData.h>
#include <JetTriggerPerformancePackage/ConfigStatus.h>
#include <JetTriggerPerformancePackage/CutHandler.h>
#include <JetTriggerPerformancePackage/ToolsJTPP.h>

class TriggerEfficiencyMatrix: public HistogramMatrix
{
 private:
  const std::string m_key;
  const std::string m_raw = "DENUM_pt";
  const std::string m_pt = "pt";
  const std::string m_TDT = "TDT";
  const std::string m_Emu = "Emu";
  const std::string m_TBP = "TBP";

  int dummy_counter;

  // ToolsJTPP
  ToolsJTPP* tools;
  CutHandler* cutHandler;

  // TODO Crosscheck
  TH2D* PtvsEta;

 public:
  TriggerEfficiencyMatrix(std::string key, std::string directory, ConfigStatus* a_CS);
  virtual ~TriggerEfficiencyMatrix();

  virtual  void Book(std::string name1, std::string name2, int nBins, double xMin, double xMax, EL::Worker* wk);
  virtual  void Book(std::string name1, std::string name2, int nBins, double* xBinning, EL::Worker* wk);

  virtual  void BookAll(TriggerData* TD, ConfigStatus* CS, EL::Worker* wk);

  virtual  void FillAll(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet, L1Data* L1D, double weight, ConfigStatus* CS);

  virtual  void Fill(std::string obs, double value, bool isGood, double weight);
  virtual  void Fill(std::string obs, int value, bool isGood, double weight);
  virtual  void Fill(std::string obs, std::vector<float>* valueVector, std::vector<bool>* isGood, double weight);

  virtual  void FillUsingTDT(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet, double weight, ConfigStatus* CS);
  virtual  void FillUsingEmu(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet, L1Data* L1D, double weight, ConfigStatus* CS);
  virtual  void FillUsingTBP();

  virtual  int nthJetAfterCuts(TriggerData* TD, int nthJet, float etaMin, float etaMax, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet);
  virtual  int nthJetAfterCutsTLA(TriggerData* TD, int nthJet, float etaMin, float etaMax, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet);
  virtual  int nthJetAfterCutsChristiansVersion(TriggerData* TD, int nthJet, float etaMin, float etaMax, EventData* ED);

  virtual  bool passedEmulation(bool isL1, int nthJet, float ptThreshold, float etaMin, float etaMax, EventData* ED_trigJet, L1Data* L1D);
  virtual  int nthJetAfterCutsEmu();
  virtual  int nthJetAfterCutsTBP();

  virtual  void DivideEfficiencyPlots(TriggerData* TD, ConfigStatus* CS);

};

#endif // JetTriggerPerformancePackage_TRIGGEREFFICIENCYMATRIX_H
