import ROOT
from xAH_config import xAH_config

c = xAH_config()

GRL = "$ROOTCOREBIN/data/ZprimeDM/data15_13TeV.periodAllYear_DetStatus-v64-pro19_DQDefects-00-01-02_PHYS_StandardGRL_All_Good.xml"

#
#  Data Config
#
if not args.is_MC:
    applyGRL           = True

#
#  MC Config
#
else:
    applyGRL           = False


doTruthOnly = True

#
# Process Ntuple
#
c.setalg("InputHandler", { "m_name"                   : "MultijetAlgo",
                           #triggers of Interest
                           "m_TriggerName"                           : "STUDYALL; HLT_j25; HLT_j60; HLT_j175; HLT_j360; HLT_j0_1i2c200m8000TLA; HLT_j0_0i1c500m900TLA; L1_J100",
                           #debug
                           "m_debug"                                 : True,
                           "m_debugInExecute"                        : False,
                           #Data or MC:
                           "m_isData"                                : True,
                           #For Data samples:
                           "m_checkLArError"                         : True,
                           #Kinematics:
                           "m_doOfflineJetKinematics"                : True,
                           "m_doTriggerJetKinematics"                : True,
                           "m_doTruthJetKinematics"                  : False,
                           #More setups for kinematic
                           "m_doLeadSubleadThirdJetKinematics"       : False,
                           "m_doNthJetKinematics"                    : False,
                           "m_doKinematicsInBinsOfEta"               : False,
                           "m_doEtainBinsOfPt"                       : False,
                           #More Kinematics
                           "m_doyStar"                               : True,
                           "m_doDeltaPhi"                            : False,
                           "m_doPTBalance"                           : False,
                           "m_doMHT"                                 : False,
                           "m_doMHTPhi"                              : False,
                           "m_doEMFrac"                              : False,
                           "m_doHECFrac"                             : False,
                           "m_doFracSamplingMax"                     : False,
                           #ptResponse:
                           "m_doOfflineTruthResponse"                : False,
                           "m_doTriggerTruthResponse"                : False,
                           "m_doTriggerOfflineResponse"              : False,
                           #mjjResponse:
                           "m_doMjjResponseOffVsTruth"               : False,
                           "m_doMjjResponseTrigVsTruth"              : False,
                           "m_doMjjResponseTrigVsOff"                : False,
                           #Turn-ons
                           "m_doTurnOns"                             : True,
                           "m_TurnOnName"                            : "HLT_j0_1i2c200m8000TLA-L1_J100; HLT_j0_0i1c500m900TLA-L1_J100",
                           "m_useTriggerDecisionTool"                : True,
                           "m_useEmulation"                          : False,
                           "m_useTriggerBeforePraescale"             : False,
                           #cuts:
                           "m_doCuts"                                : True,
                           "m_doCleaning"                            : False,
                           "m_doOnlyThisNumberOfEvents"              : -1,
                           } )

