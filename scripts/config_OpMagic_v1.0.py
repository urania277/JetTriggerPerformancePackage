# config file for JetTriggerPerformancePackage (JTPP)
#
# Please follow the instructions below in order to set the parameters in the correct way
# and to obtain performance plots of you choice.
#

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
# In the following, the initial parameters for JTPP are set.
# Please change ONLY the boolean values (True or False) and the string content
# but NOT the expressions of the initial variables (i.e. the expressions starting with 'm_'
#
c.setalg("InputHandler", { "m_name"                   : "MultijetAlgo",
#
# ============= 0. General Parameters =============
#
# Determine whether the ntuple contains REAL DATA or MC. In case of MC, this option will automatically switch of parameters that exist for real data only
#
                           "m_isData"                                : True,
#
# Debug options
#
                           "m_debug"                                 : False,
                           "m_debugInExecute"                        : False,
#
# Select how many events you would like to study for this run.
# If '-1' is selected, all events are used.
#
                           "m_doOnlyThisNumberOfEvents"              : -1,
#
# Specific options for REAL DATA
#
                           "m_checkLArError"                         : True,
#
#
# ============= 1. Kinematics =============
#
# The following parameters will only affect the kinematic plots
#
# Switch on the generation of Kinematic Plots for offline, trigger and/or truth jets
#
                           "m_doOfflineJetKinematics"                : False,
                           "m_doTriggerJetKinematics"                : False,
                           "m_doTruthJetKinematics"                  : False,
#
# Select triggers which kinematic plots you would like to generate.
# STUDYALL is the option to obtain kinematics for ANY trigger that are included in the ntuple
#
                           "m_TriggerName"                           : "STUDYALL; HLT_j25; HLT_j60; HLT_j175; HLT_j360; HLT_j25_320eta490",
#
# Generate leading, subleading and third jet (in pt ordering) and/or the nth jet of each jet trigger
#
                           "m_doLeadSubleadThirdJetKinematics"       : False,
                           "m_doNthJetKinematics"                    : False,
#
# Option to separate kinematic plots in BINS OF ETA
#
                           "m_doKinematicsInBinsOfEta"               : False,
#
# Options to plot kinematics of additional observables:
#
                           "m_doyStar"                               : False,
                           "m_doDeltaPhi"                            : False,
                           "m_doPTBalance"                           : False,
                           "m_doMHT"                                 : False,
                           "m_doMHTPhi"                              : False,
                           "m_doEMFrac"                              : False,
                           "m_doHECFrac"                             : False,
                           "m_doFracSamplingMax"                     : False,
#
# ============= 2. Response =============
#
#
# Switch on the generation of Pt Response Plots for offline, trigger and/or truth jets
#
                           "m_doOfflineTruthResponse"                : False,
                           "m_doTriggerTruthResponse"                : False,
                           "m_doTriggerOfflineResponse"              : False,
#
# Switch on the generation of Mjj Response Plots for offline, trigger and/or truth jets
#
                           "m_doMjjResponseOffVsTruth"               : False,
                           "m_doMjjResponseTrigVsTruth"              : False,
                           "m_doMjjResponseTrigVsOff"                : False,
#
# ============= 3. TurnOns (Trigger Efficiencies) =============
#
#
# Switch on the generation of turnons
#
                           "m_doTurnOns"                             : True,
#
# Select triggers which turnon plots you would like to generate.
# The syntax for turnon plots is 'probe-trigger'-'reference-trigger', e.g. HLT_j25-HLT_j15
#
                           "m_TurnOnName"                            : "HLT_j25-HLT_j15; HLT_j60-HLT_j25; HLT_j110-HLT_j85; HLT_j360-HLT_j260",
#
# Select the STRATEGY of turnOn generation.
# The available options are the Trigger Decision Tool (TDT), Emulation or Trigger Before Preascale. Note that more than one strategy can be selected
# and will be created independently of each other
#
                           "m_useTriggerDecisionTool"                : False,
                           "m_useEmulation"                          : True,
                           "m_useTriggerBeforePraescale"             : False,
# TODO CUTS
                           #cuts:
                           "m_doCuts"                                : False,
# CLEANING                           "m_doCleaning"                            : False,
                           } )

