/*--------------------------------------------------------------------
TriggerData.h

TriggerData contains all necessary information about triggers for Kinematics, Response and Turnons.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/
#ifndef JetTriggerPerformancePackage_TRIGGERDATA_H
#define JetTriggerPerformancePackage_TRIGGERDATA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "TLorentzVector.h"


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>
#include <JetTriggerPerformancePackage/ToolsJTPP.h>
#include <JetTriggerPerformancePackage/ConfigStatus.h>

class TriggerData: public BaseJTPP
{
 public:
    // === Constructors ===
    TriggerData(std::string TriggerName, std::string TurnOnName, ConfigStatus* CS);
    ~TriggerData();

    // === Methods ===
    // counting passed events per trigger and writing them out
    virtual void UpdateCounting();
    virtual void CoutCounting();
    virtual int  GetnthJet(std::string triggerString);
    virtual float GetPtThreshold(std::string triggerString);
    virtual float GetEtaMin(std::string triggerString);
    virtual float GetEtaMax(std::string triggerString);
    virtual bool isTriggerL1(std::string triggerString);

    // === Members ===

    // ---- For Kinematics ----
    // number of triggers in config file
    int nTriggers;

    // names of triggers in config file
    std::vector< std::string> config_triggerName;

    // passed triggers of an event
    std::vector<std::string>* event_passedTriggers; //passedtriggersofevent

    // nth Jet of config file
    std::vector< int> config_nthJet;

    // passed this trigger in the config file this event?
    std::vector< bool> config_passedTriggers;//boolConfTriggers;

    // count number of passed Events
    std::vector< int> nPassedEvents; //TODO

    // ---- For Turnons ----
    // strings for turn-ons, one entry corresponds for one histogram request
    std::vector< std::string> probeTriggers; // list of probe triggers
    std::vector< std::string> refTriggers; // list of ref triggers

    // corresponding nthJets
    std::vector< int> nthJetProbe;
    std::vector< int> nthJetRef;

    // corresponding bools for passing
    std::vector< bool> boolProbeTriggers;
    std::vector< bool> boolRefTriggers;

    // corresponding pt threshold of triggers
    std::vector< float> ptThresholdProbeTrigger;
    std::vector< float> ptThresholdRefTrigger;

    // corresponding eta region
    std::vector< float> etaMinProbeTrigger;
    std::vector< float> etaMinRefTrigger;
    std::vector< float> etaMaxProbeTrigger;
    std::vector< float> etaMaxRefTrigger;

    // is L1 or not
    std::vector< bool> isL1Probe;
    std::vector< bool> isL1Ref;

    // other used classes
    ToolsJTPP* myTools;
};

#endif // JetTriggerPerformancePackage_TRIGGERDATA_H
