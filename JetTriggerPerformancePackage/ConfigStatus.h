/*--------------------------------------------------------------------
ConfigStatus.h

ConfigStatus is meant to be a container for all settings  that were made in the config file.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#ifndef JetTriggerPerformancePackage_CONFIGSTATUS_H
#define JetTriggerPerformancePackage_CONFIGSTATUS_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "TLorentzVector.h"


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>

class ConfigStatus: public BaseJTPP
{
 public:
    ConfigStatus(bool a_debug,
		 bool a_debugInExecute,
		 std::string a_TriggerName,
		 bool a_isData, bool a_checkLArError,
		 bool a_doOfflineJetKinematics,
		 bool a_doTriggerJetKinematics,
		 bool a_doTruthJetKinematics,
		 bool a_doLeadSubleadThirdJetKinematics,
		 bool a_doNthJetKinematics,
		 bool a_doKinematicsInBinsOfEta,
		 bool a_doEtainBinsOfPt,
		 bool a_doyStar,
		 bool a_doDeltaPhi,
		 bool a_doPTBalance,
		 bool a_doMHT,
		 bool a_doMHTPhi,
		 bool a_doEMFrac,
		 bool a_doHECFrac,
		 bool a_doFracSamplingMax,
		 bool a_doOfflineTruthResponse,
		 bool a_doTriggerTruthResponse,
		 bool a_doTriggerOfflineResponse,
		 bool a_doMjjResponseTrigVsOff,
		 bool a_doMjjResponseOffVsTruth,
		 bool a_doMjjResponseTrigVsTruth,
		 bool a_doTurnOns,
		 std::string a_TurnOnName,
		 bool a_useTriggerDecisionTool,
		 bool a_useEmulation,
		 bool a_useTriggerBeforePraescale,
		 bool a_doCuts,
		 bool a_doCleaning,
		 int a_doOnlyThisNumberOfEvents); // "a_" for argument
    virtual ~ConfigStatus();

    // Debug
    const bool debug;
    const bool debugInExecute;

    // Trigger Selection
    const std::string TriggerName;

    // Data or MC
    const bool isData;

    //For Data Samples
    const bool checkLArError;

    //Kinematics
    const bool doOfflineJetKinematics;
    const bool doTriggerJetKinematics;
    const bool doTruthJetKinematics;

    //More setups for kinematics
    const bool doLeadSubleadThirdJetKinematics;
    const bool doNthJetKinematics;
    const bool doKinematicsInBinsOfEta;
    const bool doEtainBinsOfPt;

    //More kinematics
    const bool doyStar;
    const bool doDeltaPhi;
    const bool doPTBalance;
    const bool doMHT;
    const bool doMHTPhi;
    const bool doEMFrac;
    const bool doHECFrac;
    const bool doFracSamplingMax;

    //ptResponse
    const bool doOfflineTruthResponse;
    const bool doTriggerTruthResponse;
    const bool doTriggerOfflineResponse;

    //mjjResponse
    const bool doMjjResponseTrigVsOff;
    const bool doMjjResponseOffVsTruth;
    const bool doMjjResponseTrigVsTruth;

    //turn-ons
    const bool doTurnOns;
    const std::string TurnOnName;
    const bool useTriggerDecisionTool;
    const bool useEmulation;
    const bool useTriggerBeforePraescale;

    //cuts and cleaning
    const bool doCuts;
    const bool doCleaning;
    const int doOnlyThisNumberOfEvents;

};

#endif // JetTriggerPerformancePackage_CONFIGSTATUS_H
