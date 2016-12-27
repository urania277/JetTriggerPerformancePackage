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

void  AnalysisHandler::findBestMatching(EventData* ED_ref, EventData* ED_match, std::vector<int> &matchingIndexList, std::vector<double> &DeltaRList, double DeltaRMax)
{
  if (m_debug) std::cout << "Starting findBestMatching()... Magic will happen here!" << std::endl;

   double BestDeltaR, DeltaR;
   int BestID, minVecSize;

   TLorentzVector refVec;
   TLorentzVector matchVec;

   double refRap, matchRap;

   if (m_debug) std::cout << "ED_ref->pt->size(): "   << ED_ref->pt->size()   << std::endl;
   if (m_debug) std::cout << "ED_match->pt->size(): " << ED_match->pt->size() << std::endl;

    
    
   if (ED_ref->pt->size() <= ED_match->pt->size()) minVecSize = ED_ref->pt->size();
   else minVecSize = ED_match->pt->size();


   if (m_debug) std::cout << "minVecSize: " << minVecSize << std::endl;
    
    
   for (int n = 0; n < ED_ref->pt->size(); n++){

     //initialise value
     BestDeltaR = DeltaRMax;
     BestID = -1;
     refVec.SetPtEtaPhiE(ED_ref->pt->at(n), ED_ref->eta->at(n), ED_ref->phi->at(n), ED_ref->E->at(n));
     refRap = refVec.Rapidity();

     for (int m = 0; m < minVecSize; m++){

       matchVec.SetPtEtaPhiE(ED_match->pt->at(m), ED_match->eta->at(m), ED_match->phi->at(m), ED_match->E->at(m));
       matchRap = matchVec.Rapidity();
       DeltaR = matchVec.DeltaR(refVec);

       //CD: this would not be correct - think of two jets that are at 3.14/-3.14 in phi...
       //sqrt(pow(matchRap - refRap, 2) + pow(ED_match->phi->at(m) - ED_ref->phi->at(m), 2));

       if (DeltaR < BestDeltaR) {
        BestDeltaR = DeltaR;
        matchingIndexList[n] = m;
        DeltaRList[n] = DeltaR;
       }
     }
   }

}

