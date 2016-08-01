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
                           "m_TriggerName"                           : "STUDYALL; HLT_j360; HLT_j360_a10_lcw_sub_L1J100; HLT_4j85; HLT_5j60; HLT_6j45; HLT_7j45; HLT_ht850_L1J75",
                           "m_debug"                                 : False,
                           "m_debugInExecute"                        : False,
                           "m_doOfflineJetKinematics"                : True,
                           "m_doTriggerJetKinematics"                : True,
                           "m_doTruthJetKinematics"                  : True,
                           "m_doLeadSubleadThirdJetKinematics"       : True,
                           "m_doKinematicsInBinsOfEta"               : False,
                           "m_doEtainBinsOfPt"                       : False,
                           "m_doOfflineTruthResponse"                : True,
                           "m_doTriggerTruthResponse"                : True,
                           "m_doTriggerOfflineResponse"              : True,
                           "m_doMjjResponseOffVsTruth"               : True,
                           "m_doMjjResponseTrigVsTruth"              : True,
                           "m_doMjjResponseTrigVsOff"                : True,
                           "m_doOnlyThisNumberOfEvents"              : -1,
                                    } )
