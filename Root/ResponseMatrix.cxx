/*--------------------------------------------------------------------
ResponseMatrix.cxx

ResponseMatrix is a special class inherenting from HistogramMatrix that
contains all response histograms of a specific jet type (offline, trigger, truth etc.)

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/


#include <JetTriggerPerformancePackage/ResponseMatrix.h>
#include <JetTriggerPerformancePackage/ToolsJTPP.h>
#include <iostream>
#include <assert.h>



ResponseMatrix::ResponseMatrix(std::string key, ConfigStatus* a_CS):
    HistogramMatrix(key, false, false), CS(a_CS), // the "false" booleans deactivate leadSubleadThird and nthJet Plot options
    m_key(key), ptMinBinPos(2), ptMaxBinPos(3), etaMinBinPos(5), etaMaxBinPos(6), delimiter("_")
{
  if (m_debug) std::cout << "Starting constructor ResponseMatrix()..." << std::endl;
}

ResponseMatrix::ResponseMatrix(std::string key, std::string directory, ConfigStatus* a_CS):
    HistogramMatrix(directory, false, false), CS(a_CS), // the "false" booleans deactivate leadSubleadThird and nthJet Plot options
    m_key(key), ptMinBinPos(2), ptMaxBinPos(3), etaMinBinPos(5), etaMaxBinPos(6), delimiter("_")
{
  if (m_debug) std::cout << "Starting constructor ResponseMatrix()..." << std::endl;
}

ResponseMatrix::~ResponseMatrix()
{
  if (m_debug) std::cout << "Starting destructor ResponseMatrix()..." << std::endl;
}

void ResponseMatrix::BookAll(double* ptBinEdges, double* etaBinEdges, int ptBinNumber, int etaBinNumber, EL::Worker* wk)
{
  if (m_debug) std::cout << "Starting BookAll()..." << std::endl;
  std::string name1;

  for(int n = 0; n < (ptBinNumber-1); n++){
    for(int m = 0; m < (etaBinNumber-1); m++){
      name1 = this->createHistoName(ptBinEdges[n], ptBinEdges[n+1], etaBinEdges[m], etaBinEdges[m+1]);
      Book(name1, name1, CS->Response_BinNumbers, CS->Response_MinBin, CS->Response_MaxBin, wk);
    }
  }

  // saving pt binning
  for(int n = 0; n < ptBinNumber; n++){
    //std::cout << "ptBinEdges["<<n<<"] = " << ptBinEdges[n] << std::endl;
    m_ptBinEdges.push_back(ptBinEdges[n]);
  }

  // saving eta binning
  for(int m = 0; m < etaBinNumber; m++){
    //std::cout << "etaBinEdges["<<m<<"] = " << etaBinEdges[m] << std::endl; 
    m_etaBinEdges.push_back(etaBinEdges[m]);
  }
      
  
}

std::string ResponseMatrix::createHistoName(double d_ptBE1, double d_ptBE2, double d_etaBE1, double d_etaBE2)
{
    if (m_debug) std::cout << "Starting createHistoName()..." << std::endl;

  std::string ptBE1, ptBE2, etaBE1, etaBE2;
  ToolsJTPP* tools = new ToolsJTPP();

  // create strings out of doubles with given precision
  ptBE1 = tools->ftos(d_ptBE1, 5);
  ptBE2 = tools->ftos(d_ptBE2,5);
  etaBE1 = tools->ftos(d_etaBE1,2);
  etaBE2 = tools->ftos(d_etaBE2,2);

  return m_key + "_pt_" + ptBE1 + "_" + ptBE2 + "_eta_" + etaBE1 + "_" + etaBE2;
}

void ResponseMatrix::Fill(double probeValue, double refValue, double eta, double weight, int binningType)
{

  if (m_debug) std::cout << "Starting Fill()..." << std::endl;

  ToolsJTPP* Tools = new ToolsJTPP();
  std::string currentName;
  int ptMinBin, ptMaxBin, etaMinBin, etaMaxBin;
  int binValue;
  bool foundHisto = false;

  // Calculate response
  double resp = probeValue/refValue;

  if (resp < 0.0) return; //std::cout << "Response is NEGATIVE!" << std::endl;

  // binningType: 0 -> probeValue as binning, 1 -> refValue as binning
  assert(("binningType MUST be 0 or 1",((binningType==0)||(binningType==1))));
  if (binningType == 0) binValue = probeValue;
  else binValue = refValue;

  //------------------------

  //filter for very low jets ?????
  if (refValue > m_ptBinEdges.at(0)){
    for(int n = 0; n < (m_ptBinEdges.size()-1); n++){
      for(int m = 0; m < (m_etaBinEdges.size()-1); m++){
	if ((m_ptBinEdges.at(n) <= binValue) && (binValue < m_ptBinEdges.at(n+1)) && (m_etaBinEdges.at(m) <= eta) && (eta < m_etaBinEdges.at(m+1))){
	  currentName = this->createHistoName(m_ptBinEdges.at(n), m_ptBinEdges.at(n+1), m_etaBinEdges.at(m), m_etaBinEdges.at(m+1));
	  foundHisto = true;
	  if (m_debug) std::cout << "found right histo with new technique: " << currentName << "for: pt " << binValue << "and eta: " << eta << std::endl;
	  m_map[currentName]->Fill(resp, weight);
	  break;
	}
      }
      if (foundHisto) break;
    }
  }

  

  //  // Find right histogram and book it
  //  std::map<std::string, TH1D*>::iterator it = m_map.begin();
  //  
  //  while(it != m_map.end()){
  //    currentName = it->first;
  //
  //    //get min and max bin in pt and eta of that histo
  //    ptMinBin = std::stoi(Tools->splitString(currentName,  delimiter, ptMinBinPos));
  //    ptMaxBin = std::stoi(Tools->splitString(currentName,  delimiter, ptMaxBinPos));
  //    etaMinBin = std::stoi(Tools->splitString(currentName,  delimiter, etaMinBinPos));
  //    etaMaxBin = std::stoi(Tools->splitString(currentName,  delimiter, etaMaxBinPos));
  //
  //    if ((ptMinBin <= binValue) && (binValue < ptMaxBin) && (etaMinBin <= eta) && (eta < etaMaxBin)){
  //      if (m_debug) std::cout << "Found right response histogram:" << std::endl;
  //      if (m_debug) std::cout << ptMinBin << " <= "<< binValue << " < "<< ptMaxBin << " && " << etaMinBin << " <= "<< eta << " < "<< etaMaxBin << std::endl;
  //
  //      //Filling of histo
  //      if (m_debug) std::cout << "currentName:" << currentName << std::endl;
  //      m_map[currentName]->Fill(resp, weight);
  //    } // if-condition
  //    it++;
  //  }// while-loop

}

void ResponseMatrix::Fill(std::vector<float>* probeValueVec, std::vector<float>* refValueVec, std::vector<float>* etaVec, double weight, int binningType)
{
  int nMax;
  if (probeValueVec->size() <= refValueVec->size()) nMax = probeValueVec->size();
  else nMax = refValueVec->size();

  for (unsigned int n = 0; n < nMax; n++){

    // check for negative Values and skip them
    if ((probeValueVec->at(n) > 0.0) && (refValueVec->at(n) > 0.0)){
      this->Fill(probeValueVec->at(n), refValueVec->at(n), etaVec->at(n), weight, binningType);
    }
  }

}

void ResponseMatrix::Fill(std::vector<float>* probeValueVec, std::vector<float>* refValueVec, std::vector<float>* etaVec, std::vector<int> &matchingIndex, double weight, int binningType)
{
  int nMax;
  if (probeValueVec->size() <= refValueVec->size()) nMax = probeValueVec->size();
  else nMax = refValueVec->size();
      
  for (unsigned int n = 0; n < nMax; n++){

    // check for negative Values and skip them
    if ((probeValueVec->at(n) > 0.0) && (refValueVec->at(n) > 0.0)){
      // checking matching
      if (matchingIndex[n] != -1){
	this->Fill(probeValueVec->at(n), refValueVec->at(matchingIndex[n]), etaVec->at(matchingIndex[n]), weight, binningType);
      }
    }
  }

}
