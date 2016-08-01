/*--------------------------------------------------------------------
CutHandler.cxx

CutHandler is a compact class containing all necessary methods to apply cuts in kinematics or turnons.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/CutHandler.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



CutHandler::CutHandler():
m_passedCuts(true) // In dubio pro reo
{
  if (m_debug) std::cout << "Starting constructor CutHandler()..." << std::endl;

}

CutHandler::~CutHandler()
{
  if (m_debug) std::cout << "Starting destructor CutHandler()..." << std::endl;
}

void CutHandler::Reset()
{
    if (m_debug) std::cout << "Starting Reset()..." << std::endl;

    m_passedCuts = true;
}

void CutHandler::Reset(std::vector<bool> &boolConfTriggers)
{
    if (m_debug) std::cout << "Starting Reset()..." << std::endl;

    for (unsigned int i = 0; i < boolConfTriggers.size(); i++){
	boolConfTriggers[i] = false;
    }

    m_passedCuts = true;
}


void CutHandler::SearchTrigger(std::vector<std::string> confTriggers, std::vector<std::string>* passedTriggersOfEvent, std::vector<bool> &boolConfTriggers)
{
    if (m_debug) std::cout << "Starting SearchTrigger()..." << std::endl;

  // Loop the wanted trigger chains
  for (unsigned int n=0; n < confTriggers.size(); n++){

      // Check if this event passed this trigger
      for (unsigned int m=0; m < passedTriggersOfEvent->size(); m++){

	  if (confTriggers.at(n).compare(passedTriggersOfEvent->at(m)) == 0) boolConfTriggers[n] = true;
      }
      // STUDYALL always passes and gets 'true' if STUDYALL is in confTriggers
      if (confTriggers.at(n).compare("STUDYALL") == 0) boolConfTriggers[n] = true;
  }

}

void CutHandler::AddCut(bool status)
{
    if (!status) m_passedCuts = false;
}

void CutHandler::AddCut(float observable, float cutValue, std::string option)
{
    //possible options:
    //"max": cutValue is maximal value
    //"min": cutValue is minimal value
    //"absmax": cutValue is maximal value of |observable|
    //"absmin": cutValue is minimal value of |observable|

    if (option.compare("max") == 0){
	if (observable > cutValue) m_passedCuts = false;
    }

    if (option.compare("min") == 0){
	if (observable < cutValue) m_passedCuts = false;
    }

    if (option.compare("maxeq") == 0){
	if (observable >= cutValue) m_passedCuts = false;
    }

    if (option.compare("mineq") == 0){
	if (observable <= cutValue) m_passedCuts = false;
    }

    if (option.compare("absmax") == 0){
	if (fabs(observable) > cutValue) m_passedCuts = false;
    }

    if (option.compare("absmin") == 0){
	if (fabs(observable) < cutValue) m_passedCuts = false;
    }
}

// Check observable and set boolConfTriggers false if event does not pass this cut
// ATTENTION: Apply this AFTER SearchTrigger()!!!!
void CutHandler::ApplyTriggerSpecificCut(std::string triggerName, std::vector<std::string> confTriggers, std::vector<bool> &boolConfTriggers, float observable, float cutValue, std::string option)
{
    //possible options:
    //"max": cutValue is maximal value
    //"min": cutValue is minimal value
    //"absmax": cutValue is maximal value of |observable|
    //"absmin": cutValue is minimal value of |observable|

    bool passedTriggerCut = true;

    if (option.compare("max") == 0){
	if (observable > cutValue) passedTriggerCut = false;
    }

    if (option.compare("min") == 0){
	if (observable < cutValue) passedTriggerCut = false;
    }

    if (option.compare("maxeq") == 0){
	if (observable >= cutValue) m_passedCuts = false;
    }

    if (option.compare("mineq") == 0){
	if (observable <= cutValue) m_passedCuts = false;
    }

    if (option.compare("absmax") == 0){
	if (fabs(observable) > cutValue) passedTriggerCut = false;
    }

    if (option.compare("absmin") == 0){
	if (fabs(observable) < cutValue) passedTriggerCut = false;
    }

    // Set right boolConfTriggers false
    if (!passedTriggerCut){
	for (unsigned int n=0; n < confTriggers.size(); n++){
	    if (confTriggers.at(n).compare(triggerName) == 0) boolConfTriggers[n] = false;
	}
    }

}

float CutHandler::GetR(int pos1, int pos2, EventData* ED)
{
    if (m_debug) std::cout << "Starting GetR()..." << std::endl;

    TLorentzVector vec1, vec2;
    float rap1, rap2;

    // 4vectors
    vec1.SetPtEtaPhiE(ED->pt->at(pos1), ED->eta->at(pos1), ED->phi->at(pos1), ED->E->at(pos1));
    vec2.SetPtEtaPhiE(ED->pt->at(pos2), ED->eta->at(pos2), ED->phi->at(pos2), ED->E->at(pos2));

    // rapidity
    rap1 = vec1.Rapidity();
    rap2 = vec2.Rapidity();

    // get R
    return sqrt(pow(rap1 - rap2, 2) + pow(ED->phi->at(pos1) - ED->phi->at(pos2), 2));

}

void CutHandler::CheckIsolation(int pos, EventData* ED, float R, float ptMin)
{
    if (m_debug) std::cout << "Starting CheckIsolation()..." << std::endl;

    //std::cout << "=== CheckIsolation..." << std::endl;
    //loop over all jets
    for (unsigned int n=0; n < ED->pt->size(); n++){

	//don't compare selected jet with itself
	if (n == pos) continue;

	//consider only jets with pt > ptMin
	if (ED->pt->at(n) < ptMin) continue;

	//std::cout << "GetR("<< pos<< ", "<< n<< ", ED): " << GetR(pos, n, ED) << std::endl;
	// compare distances
	if(GetR(pos, n, ED) < R) {
	    //std::cout << "jet is NOT isolated!" << std::endl;
	    m_passedCuts = false;
	    break; // no need to continue loop
	}
    }
    //std::cout << "jet is isolated!" << std::endl;
}

bool CutHandler::passedCuts()
{
  if (m_debug) std::cout << "Starting passedCuts()..." << std::endl;

  return m_passedCuts;
}

