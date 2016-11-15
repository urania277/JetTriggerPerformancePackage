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
    virtual float GetHTThreshold(std::string triggerString);
    virtual float GetEtaMin(std::string triggerString);
    virtual float GetEtaMax(std::string triggerString);
    virtual bool isTriggerL1(std::string triggerString);
    virtual bool isTriggerHT(std::string triggerString);


    // === Members ===

    // ---- For Kinematics ----
    // number of triggers in config file
    int nTriggers;

    // names of triggers in config file
    std::vector< std::string> config_triggerName;

    // passed triggers of an event
    std::vector<std::string>* event_passedTriggers; //passedtriggersofevent
    std::vector<float>* event_triggerPrescales;
    std::vector<unsigned int>* event_isPassBits;
    std::vector<std::string>* event_isPassBitsNames;

    // nth Jet of config file
    std::vector< int> config_nthJet;

    // passed this trigger in the config file this event?
    std::vector< bool> config_passedTriggers;//boolConfTriggers;

    // count number of passed Events
    std::vector< int> nPassedEvents; //TODO

    // ---- For Turnons ----
    // strings for turn-ons, one entry corresponds for one histogram request
    std::vector< std::string> probe_triggerName; // list of probe triggers
    std::vector< std::string> ref_triggerName; // list of ref triggers

    // corresponding nthJets
    std::vector< int> probe_nthJet;
    std::vector< int> ref_nthJet;

    // corresponding bools for passing
    std::vector< bool> probe_passedTrigger;
    std::vector< bool> ref_passedTrigger;

    // corresponding passBits
    std::vector< unsigned int> probe_passBits;
    std::vector< unsigned int> ref_passBits;

    // corresponding prescaledOut bools
    std::vector< bool> probe_prescaledOut;
    std::vector< bool> ref_prescaledOut;

    // corresponding pt threshold of triggers
    std::vector< float> probe_ptThreshold;
    std::vector< float> ref_ptThreshold;

    // corresponding eta region
    std::vector< float> probe_etaMin;
    std::vector< float> ref_etaMin;
    std::vector< float> probe_etaMax;
    std::vector< float> ref_etaMax;

    // is L1 or not
    std::vector< bool> probe_isL1;
    std::vector< bool> ref_isL1;

    // is HT or not
    std::vector< bool> probe_isHT;
    std::vector< bool> ref_isHT;

    // corresponding HT threshold of triggers
    std::vector< float> probe_HTThreshold;
    std::vector< float> ref_HTThreshold;

    // Turnon Event Selection
     const float HLT_cen_etaMin;
     const float HLT_cen_etaMax;
     const float HLT_fwd_etaMin;
     const float HLT_fwd_etaMax;
     const float L1_cen_etaMin;
     const float L1_cen_etaMax;
     const float L1_fwd_etaMin;
     const float L1_fwd_etaMax;
     const float TurnonCut_Timing;

    // other used classes
    ToolsJTPP* myTools;
};

#endif // JetTriggerPerformancePackage_TRIGGERDATA_H
