###########################################################################
#
# This is JTPPPlotter.v2.0.py providing plot mechanisms for JTPP.
#
# by Edgar Kellermann (edgar.kellermann@cern.ch)
###########################################################################

from ROOT import *
import math
import sys
import re
from array import array
import AtlasStyle

################### CONFIGURATIONS ########################################

# Select input data:

inputDataList = ["hist-Data16_run300800.root", "hist-Data16_run300800_oldCuts.root"]

#### KINEMATICS ####

# Select wanted plots:

## Select plots from logfile (i.e. all provided plots)
ReadLogfileForKinematics = False

if (ReadLogfileForKinematics):
    print "Reading Logfile...."
    # TODO Implement reading logfile

## Otherwise pick wanted plots and but them into the lists
else:

    # jetType (jet = offline/reco jets)
    jetTypeList = ["jet", "trigJet"]
    #["jet", "trigJet", "truthJet"]

    # all jets, leading, sublead, third, nth jets
    praefixList = [""]
    # ["","lead", "sublead", "third", "nth"]

    # observables
    obsList = ["E","phi"]
    # ["E", "pt", "phi", "eta", "mjj", "yStar", "mjj", "m23", "yStar", "deltaPhi", "pTBalance", "MHT", "MHTPhi", "EMFrac", "HECFrac", "FracSamplingMax"]

    # etaBins # TODO Implement proper list
    etaBinsList = [""]

    # triggers of interest
    triggerList = ["HLT_j360"]

# Select ratio plots at the buttom of the canvas
EnableRatioPlots = False

# Select if histos should be plotted together on one canvas and  the criteria for combination
EnableHistoCombination = True

CriteriaOfHistoCombination = "trigger" # other options: "inputData", "trigger", "jetType", "praefix", "obs", "etaBins"

#### TURNONS ####

# TODO

#### STYLE ####

# list of colors (feel free to change colors if you are not satisfied)
colorList = [ kRed+2, kBlue+2, kGreen+2, kCyan+2, kMagenta+2, kYellow+2, kRed-2, kBlue+0, kGreen-6, kCyan-2, kMagenta-7, kYellow-7 ]

###############################################################################

# opening all output files
finList = []

for inputData in inputDataList:
    finList.append(TFile.Open(inputData))

# Looping in a proper way
listSize = 6

list = [inputDataList] *listSize
var = ["ThereWillBeString"] * listSize

# permuting lists depending on the combination criteria (since the criteria has to be in the last loop)
if (CriteriaOfHistoCombination == "etaBins"):   i = 0
if (CriteriaOfHistoCombination == "obs"):       i = 1
if (CriteriaOfHistoCombination == "praefix"):   i = 2
if (CriteriaOfHistoCombination == "jetType"):   i = 3
if (CriteriaOfHistoCombination == "trigger"):   i = 4
if (CriteriaOfHistoCombination == "inputData"): i = 5
if (not EnableHistoCombination):                i = 0

#list[(0+i)%listSize] = inputDataList
list[(0+i)%listSize] = finList
list[(1+i)%listSize] = triggerList
list[(2+i)%listSize] = jetTypeList
list[(3+i)%listSize] = praefixList
list[(4+i)%listSize] = obsList
list[(5+i)%listSize] = etaBinsList

for var[0] in list[0]:
    for var[1] in list[1]:
        for var[2] in list[2]:
            for var[3] in list[3]:
                for var[4] in list[4]:

                    #create Canvas
                    if (EnableHistoCombination):
                        c = TCanvas()
                        NPlots = 0

                    for var[5] in list[5]:

                        #create Canvas
                        if (not EnableHistoCombination):
                            print "shouldn't show up"
                            c = TCanvas()
                            NPlots = 0

                        # identify what the var[] list actually contains:
                        #                        inputData = var[(0+i)%listSize]
                        fin = var[(0+i)%listSize]
                        trigger   = var[(1+i)%listSize]
                        jetType   = var[(2+i)%listSize]
                        praefix   = var[(3+i)%listSize]
                        obs       = var[(4+i)%listSize]
                        etaBins   = var[(5+i)%listSize]

                        # no lead, sublead, third for scalar observables:
                        if (((obs == "mjj")|(obs == "m23")|(obs == "yStar")|(obs == "deltaPhi")|(obs == "pTBalance")|(obs == "MHT")|(obs == "MHTPhi")) & (praefix != "")): continue

                        # loading histogram
                        histoName = trigger + "/" + jetType + "Kinematics/" + praefix + jetType + etaBins +  "_" + obs

                        # opening file
                        #if (NPlots == 0): fin = TFile.Open(inputData)

                        # loading histo
                        histo = fin.Get(histoName)

                        # HISTO COSMETICS

                        ### histo style
                        histo.SetLineStyle(1)
                        histo.SetMarkerStyle(0)
                        histo.SetLineColor(colorList[NPlots])
                        histo.SetMarkerColor(colorList[NPlots])

                        ### axis style
                        histo.GetXaxis().SetTitleOffset(1.4)
                        histo.GetYaxis().SetTitleOffset(1.4)

                        histo.GetYaxis().SetTitle("entries/width")
                        if ((obs == "pt")| (obs == "E")| (obs == "mjj")| (obs == "m23")| (obs == "MHT")):
                            histo.GetXaxis().SetTitle(obs + " [GeV]")

                        c.Update()

                        # drawing plots
                        if (NPlots == 0): histo.Draw("HIST")
                        else: histo.Draw("Same HIST")

                        c.Update()

                        # increasing NPlots
                        if (EnableHistoCombination): NPlots += 1

                        print NPlots


                        if (not EnableHistoCombination):
                            c.SaveAs("makeResultPdf/plots/"+ trigger + "-" + praefix + "-" + jetType + "-" + etaBins + "-" + obs +".pdf")
                            c.SaveAs("makeResultPdf/plots/"+ trigger + "-" + praefix + "-" + jetType + "-" + etaBins + "-" + obs +".eps")

                    if (EnableHistoCombination):
                        # modify name with respect to Criteria
                        subName = trigger + "-" + praefix + "-" + jetType + "-" + etaBins + "-" + obs
                        modSubName = subName.replace(var[listSize-1], "")
                        c.SaveAs("makeResultPdf/plots/"+ "Comb" + "-" + modSubName +".pdf")
                        c.SaveAs("makeResultPdf/plots/"+ "Comb" + "-" + modSubName +".eps")

