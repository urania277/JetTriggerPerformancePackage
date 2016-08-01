import ROOT
from xAH_config import xAH_config

c = xAH_config()

doTruthOnly = True

#
# Process Ntuple
#
c.setalg("InputHandler", { "m_name"                   : "MultijetAlgo",
                           "m_debug"                                 : False,
                           "m_TriggerName"                           : "STUDYALL",
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
                           "m_doMjjResponseAndResolution_OffVsTruth" : True,
                           "m_doMjjResponseAndResolution_TrigVsTruth": True,
                           "m_doMjjResponseAndResolution_TrigVsOff"  : True,
                           "m_doOnlyThisNumberOfEvents"              : -1,
                                    } ) 
