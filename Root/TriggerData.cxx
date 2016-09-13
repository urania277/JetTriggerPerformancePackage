/*--------------------------------------------------------------------
TriggerData.cxx

TriggerData contains all necessary information about triggers for Kinematics, Response and Turnons.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/TriggerData.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



TriggerData::TriggerData(std::string TriggerName, std::string TurnOnName, ConfigStatus* CS):
    event_passedTriggers(nullptr),
    HLT_cen_etaMin(CS->HLT_cen_etaMin),
    HLT_cen_etaMax(CS->HLT_cen_etaMax),
    HLT_fwd_etaMin(CS->HLT_fwd_etaMin),
    HLT_fwd_etaMax(CS->HLT_fwd_etaMax),
    L1_cen_etaMin (CS->L1_cen_etaMin),
    L1_cen_etaMax (CS->L1_cen_etaMax),
    L1_fwd_etaMin (CS->L1_fwd_etaMin),
    L1_fwd_etaMax (CS->L1_fwd_etaMax),
    TurnonCut_Timing(CS->TurnonCut_Timing)
{

    if (m_debug) std::cout << "Starting constructor TriggerData()..." << std::endl;


    //split TriggerName and fill config_triggerName
    myTools = new ToolsJTPP();
    std::string trigger;

    int n = 0;
    do{
	trigger = myTools->splitString(TriggerName,"; ", n);
	config_triggerName.push_back(trigger);
	config_passedTriggers.push_back(false);
	n++;
    } while( trigger.compare("String TOO SHORT") != 0);
    config_triggerName.pop_back(); //remove last entry since it is just "String TOO SHORT"
    config_passedTriggers.pop_back();

    // Cout of all selected triggers
    std::cout << "\n=== Selected Triggers ===" << std::endl;
    for (unsigned int i=0; i<config_triggerName.size(); i++){
	std::cout << "trigger " << i << ": " << config_triggerName.at(i) << std::endl;
    }
    std::cout << "======================== \n" << std::endl;

    nTriggers = config_triggerName.size();

    // TURNONS
    // split TurnOnName and fill probeTrigger and refTrigger
    std::string turnon, trigger1, trigger2, level, pt;
    n = 0;
    do{
        turnon = myTools->splitString(TurnOnName,"; ", n);
        trigger1 = myTools->splitString(turnon,"-", 0);
        trigger2 = myTools->splitString(turnon,"-", 1);
        probe_triggerName.push_back(trigger1);
        probe_passedTrigger.push_back(false);
        ref_triggerName.push_back(trigger2);
        ref_passedTrigger.push_back(false);

        //fill pt threshold
        //level = myTools->splitString(trigger1,"j"
        //if (

        n++;
     } while(turnon.compare("String TOO SHORT") != 0);
     probe_triggerName.pop_back(); //remove last entry since it is just "String TOO SHORT"
     probe_passedTrigger.pop_back();
     ref_triggerName.pop_back();
     ref_passedTrigger.pop_back();

     // Cout of all selected turn-ons
     std::cout << "\n=== Selected Turn-ons ===" << std::endl;
      for (unsigned int i=0; i<probe_triggerName.size(); i++){
        std::cout << "probe: " << probe_triggerName.at(i) << " ::: ref: " << ref_triggerName.at(i) << std::endl;
       }
    std::cout << "======================== \n" << std::endl;

    // Initialise counting of passed events per trigger
    for (unsigned int n=0; n < nTriggers; n++){
        nPassedEvents.push_back(0);
    }

    // Fill config_nthJet
    for (unsigned int n=0; n < config_triggerName.size(); n++){
        config_nthJet.push_back(this->GetnthJet(config_triggerName.at(n)));
        //std::cout << "config_triggerName.at(n): " << config_triggerName.at(n) << " ::: config_nthJet.at(n): " << config_nthJet.at(n) << std::endl;
    }

    // Fill probe_nthJet and ref_nthJet
    for (unsigned int n=0; n < probe_triggerName.size(); n++){
        probe_nthJet.push_back(this->GetnthJet(probe_triggerName.at(n)));
        probe_ptThreshold.push_back(this->GetPtThreshold(probe_triggerName.at(n)));
        probe_etaMin.push_back(this->GetEtaMin(probe_triggerName.at(n)));
        probe_etaMax.push_back(this->GetEtaMax(probe_triggerName.at(n)));
        probe_isL1.push_back(this->isTriggerL1(probe_triggerName.at(n)));
        /*std::cout << "probe_triggerName.at(n): " << probe_triggerName.at(n) << " ::: probe_nthJet.at(n): " << probe_nthJet.at(n) << std::endl;
        std::cout << "probe_ptThreshold.at(n): " << probe_ptThreshold.at(n) << std::endl;
        std::cout << "probe_etaMin.at(n): " << probe_etaMin.at(n) << std:: endl;
        std::cout << "probe_etaMax.at(n): " << probe_etaMax.at(n) << std:: endl;
        std::cout << "probe_isL1.at(n): " << probe_isL1.at(n) << std:: endl;*/

        ref_nthJet.push_back(this->GetnthJet(ref_triggerName.at(n)));
        ref_ptThreshold.push_back(this->GetPtThreshold(ref_triggerName.at(n)));
        ref_etaMin.push_back(this->GetEtaMin(ref_triggerName.at(n)));
        ref_etaMax.push_back(this->GetEtaMax(ref_triggerName.at(n)));
        ref_isL1.push_back(this->isTriggerL1(ref_triggerName.at(n)));
        /*std::cout << "ref_triggerName.at(n): " << ref_triggerName.at(n) << " ::: ref_nthJet.at(n): " << ref_nthJet.at(n) << std::endl;
        std::cout << "ref_ptThreshold.at(n): " << ref_ptThreshold.at(n) << std::endl;
        std::cout << "ref_etaMin.at(n): " << ref_etaMin.at(n) << std:: endl;
        std::cout << "ref_etaMax.at(n): " << ref_etaMax.at(n) << std:: endl;
        std::cout << "ref_isL1.at(n): " << ref_isL1.at(n) << std:: endl;*/

    }

}

TriggerData::~TriggerData()
{
    if (m_debug) std::cout << "Starting destructor TriggerData()..." << std::endl;
}

void TriggerData::UpdateCounting()
{
    if (m_debug) std::cout << "Starting destructor UpdateCounting()..." << std::endl;

    for (unsigned int n=0; n < nTriggers; n++){
	if (config_passedTriggers.at(n)) nPassedEvents.at(n)++;
    }
}

void TriggerData::CoutCounting()
{
    if (m_debug) std::cout << "Starting method CoutCounting()..." << std::endl;

    std::cout << "==== Number of passed events per trigger ======" << std::endl;
    for (unsigned int n=0; n < nTriggers; n++){
	std::cout << config_triggerName.at(n) << " ::: " << nPassedEvents.at(n) << std::endl;
    }
    std::cout << "===============================================" << std::endl;
}


int TriggerData::GetnthJet(std::string triggerString)
{
    if (m_debug) std::cout << "Starting method CoutCounting()..." << std::endl;

    std::string jJ = "j";

    // change jJ for L1 to "J"
    if (myTools->splitString(triggerString ,"_", 0).compare("L1") == 0) jJ = "J";

    std::string cut1 = myTools->splitString(triggerString ,"_", 1);
    std::string cut2 = myTools->splitString(cut1 ,jJ, 0);
    // fill vector with 1 if cut2 is empty, i.e. trigger is cutting on first jet
    if (triggerString.compare("STUDYALL") == 0) return 1;
    else {
	if (cut2.compare("") == 0) return 1;
	else return stoi(cut2);
    }

}

float TriggerData::GetPtThreshold(std::string triggerString)
{
    if (m_debug) std::cout << "Starting method GetPtThreshold()..." << std::endl;

    std::string jJ = "j";
    bool additionalCut = false;
    std::string cut3;

    // change jJ for L1 to "J"
    if (myTools->splitString(triggerString ,"_", 0).compare("L1") == 0){
	jJ = "J";
	additionalCut = true;
    }

    std::string cut1 = myTools->splitString(triggerString ,"_", 1);
    std::string cut2 = myTools->splitString(cut1 ,jJ, 1);
    if (additionalCut) cut3 = myTools->splitString(cut2, ".", 0);
    else cut3 = cut2;

    if (triggerString.compare("STUDYALL") == 0) return 0.0; // everything will pass
    else {
	return std::stof(cut3);
    }

}

float TriggerData::GetEtaMin(std::string triggerString)
{
    if (m_debug) std::cout << "Starting method GeEtaMin()..." << std::endl;

    std::string dotscore = "_";
    int pos = 2;

    // change jJ for L1 to "J"
    if (myTools->splitString(triggerString ,"_", 0).compare("L1") == 0){
	dotscore = ".";
	pos = 1;
    }

    std::string cut1 = myTools->splitString(triggerString , dotscore, pos);
    if (cut1.compare("320eta490") == 0) return HLT_fwd_etaMin;  // min forward HLT value
    else {
        if (cut1.compare("31ETA49") == 0) return L1_fwd_etaMin; // min forward L1 value
    else{
        if (myTools->splitString(triggerString ,"_", 0).compare("L1") == 0) return L1_cen_etaMin; // min central L1 value
        else return HLT_cen_etaMin; // min central HLT value
        }
    }
}

float TriggerData::GetEtaMax(std::string triggerString)
{
    if (m_debug) std::cout << "Starting method GeEtaMax()..." << std::endl;

    std::string dotscore = "_";
    int pos = 2;

    // change jJ for L1 to "J"
    if (myTools->splitString(triggerString ,"_", 0).compare("L1") == 0){
	dotscore = ".";
	pos = 1;
    }

    std::string cut1 = myTools->splitString(triggerString , dotscore, pos);
    if (cut1.compare("320eta490") == 0) return HLT_fwd_etaMax;  // max forward HLT value
    else {
    if (cut1.compare("31ETA49") == 0) return L1_fwd_etaMax; // max forward L1 value
	else{
        if (myTools->splitString(triggerString ,"_", 0).compare("L1") == 0) return L1_cen_etaMax; // max central L1 value
        else return HLT_cen_etaMax; // max central HLT value
        }
    }
}

bool TriggerData::isTriggerL1(std::string triggerString)
{
    if (m_debug) std::cout << "Starting method isTriggerL1()..." << std::endl;

    //std::cout << "myTools->splitString(...): " << myTools->splitString(triggerString ,"_", 0) << std::endl;
    if (myTools->splitString(triggerString ,"_", 0).compare("L1") == 0) return true;
    else return false;
}
