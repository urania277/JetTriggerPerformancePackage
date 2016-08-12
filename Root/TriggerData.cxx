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
    event_passedTriggers(nullptr)
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
	probeTriggers.push_back(trigger1);
	boolProbeTriggers.push_back(false);
	refTriggers.push_back(trigger2);
	boolRefTriggers.push_back(false);

	//fill pt threshold
	//level = myTools->splitString(trigger1,"j"
	//if (

	n++;
    } while(turnon.compare("String TOO SHORT") != 0);
    probeTriggers.pop_back(); //remove last entry since it is just "String TOO SHORT"
    boolProbeTriggers.pop_back();
    refTriggers.pop_back();
    boolRefTriggers.pop_back();

    // Cout of all selected turn-ons
    std::cout << "\n=== Selected Turn-ons ===" << std::endl;
    for (unsigned int i=0; i<probeTriggers.size(); i++){
	std::cout << "probe: " << probeTriggers.at(i) << " ::: ref: " << refTriggers.at(i) << std::endl;
    }
    std::cout << "======================== \n" << std::endl;

    // Initialise counting of passed events per trigger
    for (unsigned int n=0; n < nTriggers; n++){
	nPassedEvents.push_back(0);
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

void TriggerData::SetAllnthJetPtEta()  // IMPORTANT: RUN AFTER TriggerEfficiencyMatrix::BookAll !!! (For nthJetRaw to be filled properly)
{
    if (m_debug) std::cout << "Starting method SetAllnthJet()..." << std::endl;

    // Fill config_nthJet
    for (unsigned int n=0; n < config_triggerName.size(); n++){
	config_nthJet.push_back(this->GetnthJet(config_triggerName.at(n)));
	std::cout << "config_triggerName.at(n): " << config_triggerName.at(n) << " ::: config_nthJet.at(n): " << config_nthJet.at(n) << std::endl;
    }

    // Fill nthJetProbe and nthJetRef
    for (unsigned int n=0; n < probeTriggers.size(); n++){
	nthJetProbe.push_back(this->GetnthJet(probeTriggers.at(n)));
	ptThresholdProbeTrigger.push_back(this->GetPtThreshold(probeTriggers.at(n)));
	etaMinProbeTrigger.push_back(this->GetEtaMin(probeTriggers.at(n)));
	etaMaxProbeTrigger.push_back(this->GetEtaMax(probeTriggers.at(n)));
	isL1Probe.push_back(this->isTriggerL1(probeTriggers.at(n)));
	std::cout << "probeTriggers.at(n): " << probeTriggers.at(n) << " ::: nthJetProbe.at(n): " << nthJetProbe.at(n) << std::endl;
	std::cout << "ptThresholdProbeTrigger.at(n): " << ptThresholdProbeTrigger.at(n) << std::endl;
	std::cout << "etaMinProbeTrigger.at(n): " << etaMinProbeTrigger.at(n) << std:: endl;
	std::cout << "etaMaxProbeTrigger.at(n): " << etaMaxProbeTrigger.at(n) << std:: endl;
	std::cout << "isL1Probe.at(n): " << isL1Probe.at(n) << std:: endl;

	nthJetRef.push_back(this->GetnthJet(refTriggers.at(n)));
	ptThresholdRefTrigger.push_back(this->GetPtThreshold(refTriggers.at(n)));
	etaMinRefTrigger.push_back(this->GetEtaMin(refTriggers.at(n)));
	etaMaxRefTrigger.push_back(this->GetEtaMax(refTriggers.at(n)));
	isL1Ref.push_back(this->isTriggerL1(refTriggers.at(n)));
	std::cout << "refTriggers.at(n): " << refTriggers.at(n) << " ::: nthJetRef.at(n): " << nthJetRef.at(n) << std::endl;
	std::cout << "ptThresholdRefTrigger.at(n): " << ptThresholdRefTrigger.at(n) << std::endl;
	std::cout << "etaMinRefTrigger.at(n): " << etaMinRefTrigger.at(n) << std:: endl;
	std::cout << "etaMaxRefTrigger.at(n): " << etaMaxRefTrigger.at(n) << std:: endl;
	std::cout << "isL1Ref.at(n): " << isL1Ref.at(n) << std:: endl;

    }

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
    if (cut1.compare("320eta490") == 0) return 3.6;  // min forward HLT value
    else { if (cut1.compare("31ETA49") == 0) return 3.6; // min forward L1 value
	else return 0.0;
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
    if (cut1.compare("320eta490") == 0) return 4.5;  // max forward HLT value
    else {
	if (cut1.compare("31ETA49") == 0) return 4.5; // max forward L1 value
	else{
        if (myTools->splitString(triggerString ,"_", 0).compare("L1") == 0) return 2.6; // TODO change back to 2.6 !!!
        else return 2.8; // TODO change back to 2.8 !!!
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
