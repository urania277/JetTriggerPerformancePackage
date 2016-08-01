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
                           "m_TriggerName"                           : "STUDYALL", #All triggered by DS trigger anyway, no trigger Info available
                           "m_debug"                                 : False,
                           "m_debugInExecute"                        : False,
                           #Data or MC:
                           "m_isData"                                : True,
                           #For Data samples:
                            "m_checkLArError"                        : True,
                           #Kinematics:
                           "m_doOfflineJetKinematics"                : False,
                           "m_doTriggerJetKinematics"                : True,
                           "m_doTruthJetKinematics"                  : False,
                           #More setups for kinematic
                           "m_doLeadSubleadThirdJetKinematics"       : True,
                           "m_doNthJetKinematics"                    : False,
                           "m_doKinematicsInBinsOfEta"               : True,
                           "m_doEtainBinsOfPt"                       : False,
                           #More Kinematics
                           "m_doyStar"                               : True,
                           "m_doDeltaPhi"                            : True,
                           "m_doPTBalance"                           : True,
                           "m_doMHT"                                 : True,
                           "m_doMHTPhi"                              : True,
                           "m_doEMFrac"                              : True,
                           "m_doHECFrac"                             : True,
                           "m_doFracSamplingMax"                     : True,
                           #ptResponse:
                           "m_doOfflineTruthResponse"                : False,
                           "m_doTriggerTruthResponse"                : False,
                           "m_doTriggerOfflineResponse"              : False,
                           #mjjResponse:
                           "m_doMjjResponseOffVsTruth"               : False,
                           "m_doMjjResponseTrigVsTruth"              : False,
                           "m_doMjjResponseTrigVsOff"                : False,
                           #cuts:
                           "m_doCuts"                                : True,
                           "m_doCleaning"                            : True,
                           "m_doOnlyThisNumberOfEvents"              : -1,
                                    } )
