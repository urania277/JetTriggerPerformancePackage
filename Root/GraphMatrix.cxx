/*--------------------------------------------------------------------
GraphMatrix.cxx

The original class for all classes containing histograms.
Histograms are generally saved in a std::map.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/GraphMatrix.h>
#include <iostream>
#include <assert.h>

GraphMatrix::GraphMatrix(std::string directory):
    m_directory(directory)
{
  if (m_debug) std::cout << "Starting constructor GraphMatrix()..." << std::endl;
}

GraphMatrix::~GraphMatrix()
{
  if (m_debug) std::cout << "Starting destructor GraphMatrix()..." << std::endl;
}

void GraphMatrix::Book(std::string name, int n, EL::Worker* wk)
{
    if (m_debug) std::cout << "Starting method GraphMatrix::BookAll()..." << std::endl;

    //TGraphAsymmErrors* graph = new TGraphAsymmErrors();
    //m_map[name] = graph;
    //wk->addOutput(m_map[name]);
}

void GraphMatrix::Divide(std::string name, TH1D *TH_Nom, TH1D *TH_Den, std::string option, EL::Worker* wk)
{
  if (m_debug) std::cout << "Starting method Divide()..." << std::endl;

  //TGraphAsymmErrors* graph = new TGraphAsymmErrors(TH_Nom, TH_Den, option.c_str());
  //m_map[name] = graph;
  //wk->addOutput(m_map[name]);

  //m_map[name]->Divide(TH_Nom, TH_Den, option.c_str());
}
