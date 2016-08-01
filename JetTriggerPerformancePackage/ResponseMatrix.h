/*--------------------------------------------------------------------
ResponseMatrix.h

ResponseMatrix is a special class inherenting from HistogramMatrix that
contains all response histograms of a specific jet type (offline, trigger, truth etc.)

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#ifndef JetTriggerPerformancePackage_RESPONSEMATRIX_H
#define JetTriggerPerformancePackage_RESPONSEMATRIX_H

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
#include <JetTriggerPerformancePackage/ConfigStatus.h>

class ResponseMatrix: public HistogramMatrix
{
 private:
  const std::string m_key;
  std::vector<double> m_ptBinEdges;
  std::vector<double> m_etaBinEdges;

  // private functions
  virtual std::string createHistoName(double ptBE1, double ptBE2, double etaBE1, double etaBE2);

  //position of the pt and eta bin ranges
  //that are fixed by the name convention
  const int ptMinBinPos, ptMaxBinPos, etaMinBinPos, etaMaxBinPos;
  const std::string delimiter;

 public:
  ResponseMatrix(std::string key, ConfigStatus* a_CS);
  ResponseMatrix(std::string key, std::string directory, ConfigStatus* a_CS);
  virtual ~ResponseMatrix();

  virtual void BookAll(double* ptBinEdges, double* etaBinEdges, int ptBinNumber, int etaBinNumber, EL::Worker* wk);

  virtual void Fill(double probeValue, double refValue, double eta, double weight, int binningType);
  virtual void Fill(std::vector<float>* probeValueVec, std::vector<float>* refValueVec, std::vector<float>* etaVec, double weight, int binningType);
  virtual void Fill(std::vector<float>* probeValueVec, std::vector<float>* refValueVec, std::vector<float>* etaVec, std::vector<int> &matchingIndex , double weight, int binningType);

};

#endif // JetTriggerPerformancePackage_HISTOGRAMMATIX_H
