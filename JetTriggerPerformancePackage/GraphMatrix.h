/*--------------------------------------------------------------------
GraphMatrix.h

The original class for all classes containing TGraphsAsymmetricErrors.
Histograms are generally saved in a std::map.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#ifndef JetTriggerPerformancePackage_GRAPHMATIX_H
#define JetTriggerPerformancePackage_GRAPHMATIX_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iterator>

// Root intern
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TGraphAsymmErrors.h>

// EventLoop
#include <EventLoop/Worker.h>


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>
#include <JetTriggerPerformancePackage/ConfigStatus.h>

class GraphMatrix: public BaseJTPP
{
 protected:
  std::map<std::string, TGraphAsymmErrors*> m_map;
  const std::string m_directory;


 public:
  GraphMatrix(std::string directory);
  virtual ~GraphMatrix();

  virtual void Book(std::string name, int n, EL::Worker* wk);
  virtual void Divide(std::string name,TH1D* TH_Nom, TH1D* TH_Den, std::string option, EL::Worker* wk);
//  virtual  void Book(std::string name1, std::string name2, int nBins, double xMin, double xMax, EL::Worker* wk);

};

#endif // JetTriggerPerformancePackage_GRAPHMATIX_H
