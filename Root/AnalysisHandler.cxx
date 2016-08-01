/*--------------------------------------------------------------------
AnalysisHandler.cxx

AnalysisHandler contains methods concerning Matching.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/AnalysisHandler.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



AnalysisHandler::AnalysisHandler()
{
  if (m_debug) std::cout << "Starting constructor AnalysisHandler()..." << std::endl;
}

AnalysisHandler::~AnalysisHandler()
{
  if (m_debug) std::cout << "Starting destructor AnalysisHandler()..." << std::endl;
}

void  AnalysisHandler::findBestMatching(std::vector<float>* refVec_pt, std::vector<float>* refVec_eta, std::vector<float>* refVec_phi, std::vector<float>* refVec_E, std::vector<float>* matchVec_pt, std::vector<float>* matchVec_eta, std::vector<float>* matchVec_phi, std::vector<float>* matchVec_E, std::vector<int> &matchingIndexList, std::vector<double> &DeltaRList, double DeltaRMax)
{
  if (m_debug) std::cout << "Starting findBestMatching()... Magic will happen here!" << std::endl;

   double BestDeltaR, DeltaR;
   int BestID;

   TLorentzVector refVec;
   TLorentzVector matchVec;

   double refRap, matchRap;

   for (int n = 0; n < refVec_pt->size(); n++){

     //initialise value
     BestDeltaR = DeltaRMax;
     BestID = -1;
     refVec.SetPtEtaPhiE(refVec_pt->at(n), refVec_eta->at(n), refVec_phi->at(n), refVec_E->at(n));
     refRap = refVec.Rapidity();

     for (int m = 0; m < matchVec_pt->size(); m++){

       matchVec.SetPtEtaPhiE(matchVec_pt->at(m), matchVec_eta->at(m), matchVec_phi->at(m), matchVec_E->at(m));
       matchRap = matchVec.Rapidity();
       DeltaR = sqrt(pow(matchRap - refRap, 2) + pow(matchVec_phi->at(m) - refVec_phi->at(n), 2));

       if (DeltaR < BestDeltaR) {
	 BestDeltaR = DeltaR;
	 matchingIndexList[n] = m;
	 DeltaRList[n] = DeltaR;
       }
     }
   }

}

