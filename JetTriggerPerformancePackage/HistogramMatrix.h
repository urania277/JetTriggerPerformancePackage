/*--------------------------------------------------------------------
HistogramMatrix.h

The original class for all classes containing histograms.
Histograms are generally saved in a std::map.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#ifndef JetTriggerPerformancePackage_HISTOGRAMMATIX_H
#define JetTriggerPerformancePackage_HISTOGRAMMATIX_H

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
#include <JetTriggerPerformancePackage/BaseJTPP.h>
#include <JetTriggerPerformancePackage/ConfigStatus.h>

class HistogramMatrix: public BaseJTPP
{
 protected:
  std::map<std::string, TH1D*> m_map;
  const std::string m_directory;

  // number of nth Jet
  const int  m_nthJet;

  const std::string lead = "lead";
  const std::string sublead = "sublead";
  const std::string third = "third";
  const std::string nth = "nth";

  //ConfigStatus
  const bool doLeadSubleadThird;
  const bool doNthJets;

 public:
  HistogramMatrix(bool a_doLeadSubleadThird, bool a_doNthJets);
  HistogramMatrix(std::string directory,bool a_doLeadSubleadThird, bool a_doNthJets);
  HistogramMatrix(std::string directory, int nthJet, bool a_doLeadSubleadThird, bool a_doNthJets);
  virtual ~HistogramMatrix();

  virtual  void Book(std::string name1, std::string name2, int nBins, double xMin, double xMax, EL::Worker* wk);
  virtual  void Book(std::string name1, std::string name2, int nBins, double* xBinning,  EL::Worker* wk);

  virtual  void coutAllBookings();

  virtual  void Fill(std::string name, double value, bool isGood, double weight);
  virtual  void Fill(std::string name, int value, bool isGood, double weight);
  virtual  void Fill(std::string name, std::vector<float>* valueVector, std::vector<bool>* isGood, double weight);
  virtual  void FillConsiderLeadSubThird(std::string name, double value, int n, bool isGood, double weight);


  virtual  bool isBooked(std::string name);

};

#endif // JetTriggerPerformancePackage_HISTOGRAMMATIX_H
