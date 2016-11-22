/*--------------------------------------------------------------------
CutHandler.cxx

CutHandler is a compact class containing all necessary methods to apply cuts in kinematics or turnons.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/CutHandler.h>
#include <JetTriggerPerformancePackage/ToolsJTPP.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



CutHandler::CutHandler():
m_passedCuts(true) // In dubio pro reo
{
  if (m_debug) std::cout << "Starting constructor CutHandler()..." << std::endl;

  myTools = new ToolsJTPP();

}

CutHandler::CutHandler(std::string cutString):
m_passedCuts(true) // In dubio pro reo
{
  if (m_debug) std::cout << "Starting constructor CutHandler()..." << std::endl;

  myTools = new ToolsJTPP();
  this->InitialiseCutStringMethod(cutString);
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
  if (m_debug) std::cout << "confTriggers.size(): " << confTriggers.size() << std::endl; //TODO
  for (unsigned int n=0; n < confTriggers.size(); n++){

      // Check if this event passed this trigger
      if (m_debug) std::cout << "passedTriggersOfEvent->size(): " << passedTriggersOfEvent->size() << std::endl; //TODO
      for (unsigned int m=0; m < passedTriggersOfEvent->size(); m++){

           if (m_debug) std::cout << "confTriggers.at(n): " << confTriggers.at(n) << std::endl; //TODO
           if (m_debug) std::cout << "passedTriggersOfEvent->at(m): " << passedTriggersOfEvent->at(m) << std::endl; //TODO

	  if (confTriggers.at(n).compare(passedTriggersOfEvent->at(m)) == 0) boolConfTriggers[n] = true;
      }
      // STUDYALL always passes and gets 'true' if STUDYALL is in confTriggers
      if (confTriggers.at(n).compare("STUDYALL") == 0) boolConfTriggers[n] = true;
  }
  if (m_debug) std::cout << "End of SearchTrigger" << std::endl; //TODO

}

void CutHandler::SearchPassBits(std::vector<std::string> confTriggers, std::vector<unsigned int> &confPassedBits, std::vector<std::string> *passBitsNames, std::vector<unsigned int> *passBits)
{
    if (m_debug) std::cout << "Starting SearchPassBits()..." << std::endl;

    //Loop over wanted chains
    for (unsigned int n=0; n < confTriggers.size(); n++){

        // reset passBits to 0
        confPassedBits[n] = 0;

        // Loop over passBits
        for (unsigned int m=0; m < passBits->size(); m++){

            if (confTriggers.at(n).compare(passBitsNames->at(m)) ==0){

                confPassedBits[n] = passBits->at(m);
            }
        }
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

void CutHandler::InitialiseCutStringMethod(std::string cutString)
{
    if (m_debug) std::cout << "Starting AddCutString()..." << std::endl;

    //--- split cutString cut by cut ---
    std::string cutj;

    // check if string is not empty, otherwise set everything to -1
    if (cutString.compare("") == 0) {
        vec_jetType_index.push_back(0);
        vec_jetType_index.push_back(1);
        return;
    }

    int n = 0;
    do{
    cutj = myTools->splitString(cutString,"; ", n);
    vec_cuts.push_back(cutj);
    n++;
    } while( cutj.compare("String TOO SHORT") != 0);
    vec_cuts.pop_back(); //remove last entry since it is just "String TOO SHORT"

    // Cout of all selected cuts
    std::cout << "\n=== Selected cuts ===" << std::endl;
        for (unsigned int i=0; i< vec_cuts.size(); i++){
        std::cout << "cut " << i << ": " << vec_cuts.at(i) << std::endl;
    }
    if (vec_cuts.size() == 0) std::cout << "No Cuts selected \n" << std::endl;
    std::cout << "======================== \n" << std::endl;

    //--- parsing each cut ---
    for (unsigned int i=0; i < vec_cuts.size(); i++){

        // What is the operator?
        if (vec_cuts.at(i).find(">")!=std::string::npos) vec_cut_options.push_back("min");
        else if (vec_cuts.at(i).find("<")!=std::string::npos) vec_cut_options.push_back("max");
        else{
            // case of operator cannot be read
            std::cout << "CutHandler::AddCutString CANNOT READ THE OPERATOR OF CUT " << i << std::endl << "Please check your config file" << std::endl;

            // set operator to larger
            vec_cut_options.push_back("min");
        }

        // Do we have a absolute value?
        if (vec_cuts.at(i).compare("|") > 0) vec_cut_options.at(i) = "abs" + vec_cut_options.at(i);

        // Get the index number of the vector. If observable is a scalar, set vec_index to -1
        std::string sIndex = myTools->splitString(myTools->splitString(vec_cuts.at(i),"[", 1),"]",0);

        if (sIndex.compare("String TOO SHORT") == 0) vec_index.push_back(-1);
        else vec_index.push_back(stoi(sIndex));

        // Identify the observable and give it a observable number for later
        if (vec_cuts.at(i).find("E"              )!=std::string::npos) vec_obs_index.push_back(0);
        if (vec_cuts.at(i).find("pt"             )!=std::string::npos) vec_obs_index.push_back(1);
        if (vec_cuts.at(i).find("phi"            )!=std::string::npos) vec_obs_index.push_back(2);
        if (vec_cuts.at(i).find("eta"            )!=std::string::npos) vec_obs_index.push_back(3);

        if (vec_cuts.at(i).find("mjj"            )!=std::string::npos) vec_obs_index.push_back(4);
        if (vec_cuts.at(i).find("m23"            )!=std::string::npos) vec_obs_index.push_back(5);
        if (vec_cuts.at(i).find("yStar"          )!=std::string::npos) vec_obs_index.push_back(6);
        if (vec_cuts.at(i).find("deltaPhi"       )!=std::string::npos) vec_obs_index.push_back(7);
        if (vec_cuts.at(i).find("pTBalance"      )!=std::string::npos) vec_obs_index.push_back(8);
        if (vec_cuts.at(i).find("MHT"            )!=std::string::npos) vec_obs_index.push_back(9);
        if (vec_cuts.at(i).find("MHTPhi"         )!=std::string::npos) vec_obs_index.push_back(10);
        if (vec_cuts.at(i).find("EMFrac"         )!=std::string::npos) vec_obs_index.push_back(11);
        if (vec_cuts.at(i).find("HECFrac"        )!=std::string::npos) vec_obs_index.push_back(12);
        if (vec_cuts.at(i).find("FracSamplingMax")!=std::string::npos) vec_obs_index.push_back(13);
        if (vec_cuts.at(i).find("Timing"         )!=std::string::npos) vec_obs_index.push_back(14);
        if (vec_cuts.at(i).find("Ht"             )!=std::string::npos) vec_obs_index.push_back(15);

        // Get the jet type

        // default: offline jets:
        vec_jetType_index.push_back(0);

        if (vec_cuts.at(i).find("trig"           )!=std::string::npos) vec_jetType_index.at(i) = 1;
        if (vec_cuts.at(i).find("truth"          )!=std::string::npos) vec_jetType_index.at(i) = 2;

        // Get the cut value
        std::string delimiter;
        if (vec_cut_options.at(i).find("min")!=std::string::npos) delimiter = ">";
        else delimiter="<";

        std::string sCutValue = myTools->splitString(vec_cuts.at(i),delimiter,1);

        vec_cutValue.push_back(std::stof(sCutValue));
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

void CutHandler::UseCutStringMethod(EventData *ED, EventData *trigED, EventData *truthED)
{
    if (m_debug) std::cout << "Starting UseCutStringMethod()..." << std::endl;

    // Reset
    this->Reset();

    // Loop over every cut
    for (int i=0; i < vec_cuts.size(); i++){

        // separate with respect to jetType
        switch (vec_jetType_index.at(i)) {
        case -1: // no cut
            break;
        case 0: // offline jets
            this->AddCutWithThisJetType(ED,vec_obs_index.at(i), vec_index.at(i), vec_cut_options.at(i), vec_cutValue.at(i));
            break;
        case 1: // trigger jets
            this->AddCutWithThisJetType(trigED,vec_obs_index.at(i), vec_index.at(i), vec_cut_options.at(i), vec_cutValue.at(i));
            break;
        case 2: // truth jets
            this->AddCutWithThisJetType(truthED,vec_obs_index.at(i), vec_index.at(i), vec_cut_options.at(i), vec_cutValue.at(i));
            break;
        }

    }

}

void CutHandler::AddCutWithThisJetType(EventData *ED, int obs_index, int index, std::string cut_options, float cut_value)
{
    if (m_debug) std::cout << "Starting AddCutWithThisJetType()..." << std::endl;

    // reading obs_index in order to find the proper observable
    switch (obs_index) {
    case 0:
        this->AddCut(ED->E->at(index), cut_value, cut_options);
        break;
    case 1:
        this->AddCut(ED->pt->at(index), cut_value, cut_options);
        break;
    case 2:
        this->AddCut(ED->phi->at(index), cut_value, cut_options);
        break;
    case 3:
        this->AddCut(ED->eta->at(index), cut_value, cut_options);
        break;
    case 4:
        this->AddCut(ED->Mjj(), cut_value, cut_options);
        break;
    case 5:
        this->AddCut(ED->M23(), cut_value, cut_options);
        break;
    case 6:
        this->AddCut(ED->YStar(), cut_value, cut_options);
        break;
    case 7:
        this->AddCut(ED->deltaPhi, cut_value, cut_options);
        break;
    case 8:
        this->AddCut(ED->pTBalance, cut_value, cut_options);
        break;
    case 9:
        this->AddCut(ED->MHT, cut_value, cut_options);
        break;
    case 10:
        this->AddCut(ED->MHTPhi, cut_value, cut_options);
        break;
    case 11:
        this->AddCut(ED->EMFrac->at(index), cut_value, cut_options);
        break;
    case 12:
        this->AddCut(ED->HECFrac->at(index), cut_value, cut_options);
        break;
    case 13:
        this->AddCut(ED->FracSamplingMax->at(index), cut_value, cut_options);
        break;
    case 14:
        this->AddCut(ED->Timing->at(index), cut_value, cut_options);
        break;
    case 15:
        this->AddCut(ED->GetHT(), cut_value, cut_options);
        break;

    }


}
