/*--------------------------------------------------------------------
ConfigStatus.cxx

ConfigStatus is meant to be a container for all settings  that were made in the config file.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/ConfigStatus.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



ConfigStatus::ConfigStatus(bool a_debug,
			   bool a_debugInExecute,
			   std::string a_TriggerName,
			   bool a_isData,
			   bool a_checkLArError,
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
               bool a_doHT,
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
               float a_HLT_cen_etaMin,
               float a_HLT_cen_etaMax,
               float a_HLT_fwd_etaMin,
               float a_HLT_fwd_etaMax,
               float a_L1_cen_etaMin,
               float a_L1_cen_etaMax,
               float a_L1_fwd_etaMin,
               float a_L1_fwd_etaMax,
               float a_TurnonCut_Timing,
			   bool a_doCuts,
               std::string a_cutStringKinematics,
               std::string a_cutStringTurnons,
			   bool a_doCleaning,
			   int a_doOnlyThisNumberOfEvents):
    debug(a_debug),
    debugInExecute(a_debugInExecute),
    TriggerName(a_TriggerName),
    isData(a_isData),
    checkLArError(a_checkLArError),
    doOfflineJetKinematics(a_doOfflineJetKinematics),
    doTriggerJetKinematics(a_doTriggerJetKinematics),
    doTruthJetKinematics(a_doTruthJetKinematics),
    doLeadSubleadThirdJetKinematics(a_doLeadSubleadThirdJetKinematics),
    doNthJetKinematics(a_doNthJetKinematics),
    doKinematicsInBinsOfEta(a_doKinematicsInBinsOfEta),
    doEtainBinsOfPt(a_doEtainBinsOfPt),
    doyStar(a_doyStar),
    doDeltaPhi(a_doDeltaPhi),
    doPTBalance(a_doPTBalance),
    doHT(a_doHT),
    doMHT(a_doMHT),
    doMHTPhi(a_doMHTPhi),
    doEMFrac(a_doEMFrac),
    doHECFrac(a_doHECFrac),
    doFracSamplingMax(a_doFracSamplingMax),
    doOfflineTruthResponse(a_doOfflineTruthResponse),
    doTriggerTruthResponse(a_doTriggerTruthResponse),
    doTriggerOfflineResponse(a_doTriggerOfflineResponse),
    doMjjResponseTrigVsOff(a_doMjjResponseTrigVsOff),
    doMjjResponseOffVsTruth(a_doMjjResponseOffVsTruth),
    doMjjResponseTrigVsTruth(a_doMjjResponseTrigVsTruth),
    HLT_cen_etaMin(a_HLT_cen_etaMin),
    HLT_cen_etaMax(a_HLT_cen_etaMax),
    HLT_fwd_etaMin(a_HLT_fwd_etaMin),
    HLT_fwd_etaMax(a_HLT_fwd_etaMax),
    L1_cen_etaMin(a_L1_cen_etaMin),
    L1_cen_etaMax(a_L1_cen_etaMax),
    L1_fwd_etaMin(a_L1_fwd_etaMin),
    L1_fwd_etaMax(a_L1_fwd_etaMax),
    TurnonCut_Timing(a_TurnonCut_Timing),
    doCuts(a_doCuts),
    cutStringKinematics(a_cutStringKinematics),
    cutStringTurnons(a_cutStringTurnons),
    doCleaning(a_doCleaning),
    doOnlyThisNumberOfEvents(a_doOnlyThisNumberOfEvents),
    doTurnOns(a_doTurnOns),
    TurnOnName(a_TurnOnName),
    useTriggerDecisionTool(a_useTriggerDecisionTool),
    useEmulation(a_useEmulation),
    useTriggerBeforePraescale(a_useTriggerBeforePraescale)
{
  if (m_debug) std::cout << "Starting constructor ConfigStatus()..." << std::endl;
}

ConfigStatus::~ConfigStatus()
{
  if (m_debug) std::cout << "Starting destructor ConfigStatus()..." << std::endl;
}
