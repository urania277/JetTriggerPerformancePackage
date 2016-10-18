/*--------------------------------------------------------------------
KinematicMatrix.h

KinematicMatrix is a special class inherenting from HistogramMatrix that
contains all kinematic histograms of a specific jet type (offline, trigger, truth etc.)

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#ifndef JetTriggerPerformancePackage_KINEMATICMATRIX_H
#define JetTriggerPerformancePackage_KINEMATICMATRIX_H

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

// EventLoop
#include <EventLoop/Worker.h>


//Own classes
#include <JetTriggerPerformancePackage/HistogramMatrix.h>
#include <JetTriggerPerformancePackage/EventData.h>
#include <JetTriggerPerformancePackage/ConfigStatus.h>
#include <JetTriggerPerformancePackage/ToolsJTPP.h>

class KinematicMatrix: public HistogramMatrix
{
 private:
  const std::string m_key;
  std::vector <std::string> m_obs;
  const int  m_nthJet;

  // eta limits
  // TLA-Values
  const float etaLim1 = 0.8;
  const float etaLim2 = 1.6;
  const float etaLim3 = 4.9; 
  //MinBias-Value
  /*const float etaLim1 = 2.8;
  const float etaLim2 = 3.2;
  const float etaLim3 = 3.6; */

  //ToolsJTPP
  ToolsJTPP* t;

  //ConfigStatus
  ConfigStatus* CS;

 public:
  KinematicMatrix(std::string key, std::string directory, int nthJet, ConfigStatus* a_CS);
  virtual ~KinematicMatrix();

  virtual  void Book(std::string name1, std::string name2, int nBins, double xMin, double xMax , EL::Worker* wk);
  virtual  void Book(std::string name1, std::string name2, int nBins, double* xBinning, EL::Worker* wk);

  virtual  void Fill(std::string obs, int value, double weight, bool isGood);
  virtual  void Fill(std::string obs, double value, double weight, bool isGood);
  virtual  void Fill(std::string obs, double value, std::vector<float>* etaVector, double weight, bool isGood);
  virtual  void Fill(std::string obs, std::vector<float>* valueVector, double weight, std::vector<bool>* isGood);
  virtual  void Fill(std::string obs, std::vector<float>* valueVector, std::vector<float>* etaVector, double weight, std::vector<bool>* isGood);

  virtual  void FillAll(EventData* ED, double weight);

};

#endif // JetTriggerPerformancePackage_KINEMATICMATIX_H
