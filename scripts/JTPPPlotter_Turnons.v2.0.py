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

inputDataList = ["hist-Data16_run300800_newCut.root", "hist-Data16_run300800_oldCuts.root"]

# please put here the header string in the turnon plots for each file
inputDataTurnonHeader = ["new Cut", "old Cut"]

# Select ATLAS Labeling
ATLAS_Internal = True
ATLAS_Preliminary = False

######## TURNONS ########

# Enable Evaluation Types
PlotTDT             = False
PlotEmulation       = True
PlotBeforePraescale = False #TODO

# Enable Combined Plots
EnableCombinedTurnons = True

# NOTE: If several datasets are listed in inputDataList, the same
# turnons from the different datasets are plotted together in one plot

if (not EnableCombinedTurnons):

    #select if all turnons from logfile should be plotted
    PlotAllTurnonsFromLogfile = False #TODO

    #otherwise create turnon list
    TurnonList=["HLT_j360-HLT_j260","HLT_j110-HLT_j85","HLT_j25-HLT_j15","HLT_j60-HLT_j25"]

    #set the min and the max x-axis range for the selected turnons respectively
    minXList = [250.0,  20.0,  20.0,  20.0]
    maxXList = [600.0, 160.0,  40.0, 110.0]

    #set legend entries
    # Set Legend Settings
    TurnonLegendHeader = "Data 2016"
    TurnonLegendEntryList = ["HLT_j360","HLT_j110","HLT_j25","HLT_j60"]

    #rebin factor (has to be a factor of 1200)
    rebinList = [5, 5, 5, 5]

else:

    #create list of name combined plots
    CombinedTurnonsList=["HLT-high", "HLT-low"]

    #set the min and the max x-axis range for the selected turnons respectively
    minXList = [ 80.0,  20.0]
    maxXList = [600.0, 160.0]

    #set legend entries
    TurnonLegendHeader = "Data 2016"
    TLegendEntryList = CombinedTurnonsList

    #rebin factor (has to be a factor of 1200)
    rebinList = [5, 5, 5, 5]

    #declare list of contents for every combined plot (do not touch this line)
    ContentCombinedTurnonsList = []
    ContentCombinedTurnonsLegendEntry = []

    #select content for combined plot number 1
    ContentCombinedTurnonsList.append(["HLT_j360-HLT_j260","HLT_j110-HLT_j85"])
    ContentCombinedTurnonsLegendEntry.append(["HLT_j360","HLT_j110"])

    #select content for combined plot number 2
    ContentCombinedTurnonsList.append(["HLT_j25-HLT_j15","HLT_j60-HLT_j25"])
    ContentCombinedTurnonsLegendEntry.append(["HLT_j25","HLT_j60"])

    #can be continued....

# Line and Marker Style
TLineStyle = 0
TMarkerStyle = [20, 24] # Marker style for different input data

######## GENERAL STYLE ########

# list of colors (feel free to change colors if you are not satisfied)
colorList = [ kRed+2, kBlue+2, kGreen+2, kCyan+2, kMagenta+2, kYellow+2, kRed-2, kBlue+0, kGreen-6, kCyan-2, kMagenta-7, kYellow-7 ]


################## CREATING TURNONS  ########################################

if (not EnableCombinedTurnons): CombinedTurnonsList = [""]

# Gstyle and ATLAS Style
AtlasStyle.SetAtlasStyle()
gStyle.SetOptStat(0) # get rid of statistics box

# opening all output files
finList = []

for inputData in inputDataList:
    finList.append(TFile.Open(inputData))


# Create PraefixList
EvalTypeList = []

if (PlotTDT): EvalTypeList.append("TDT")
if (PlotEmulation): EvalTypeList.append("Emu")
if (PlotBeforePraescale): EvalTypeList.append("TBP")

NCombinedTurnons = 0
for CombinedTurnons in CombinedTurnonsList:

    # select proper TurnonList
    if (EnableCombinedTurnons):
        TurnonList = ContentCombinedTurnonsList[NCombinedTurnons]
        TurnonLegendEntryList= ContentCombinedTurnonsLegendEntry[NCombinedTurnons]

    if (EnableCombinedTurnons):
        # create canvas, multigraph, legend
        c = TCanvas()
        c.SetGrid()
        MultiGr = TMultiGraph()
        legend = TLegend(0.5,0.40,0.85,0.2)
        legend.SetFillColor(0)
        legend.SetTextFont(1)
        legend.SetHeader(TurnonLegendHeader)
        legend.SetFillStyle(0)

    for EvalType in EvalTypeList:

        NTurnon = 0
        print "TurnonList: " + str(TurnonList)
        for TurnonName in TurnonList:

            if (not EnableCombinedTurnons):
                # create canvas, multigraph, legend
                c = TCanvas()
                c.SetGrid()
                MultiGr = TMultiGraph()
                legend = TLegend(0.5,0.40,0.85,0.2)
                legend.SetFillColor(0)
                legend.SetTextFont(1)
                legend.SetHeader(TurnonLegendHeader)
                legend.SetFillStyle(0)

            NData = 0
            for fin  in finList:

                # create histo names
                histoName = "TurnOns" + "/" + "effic_pt_" + EvalType + "_" + TurnonName # NOM in the future #TODO
                histoNameDN = "TurnOns" + "/" + "effic_DENUM_pt_" + EvalType + "_" + TurnonName #DENOM in the future?

                # load histograms from Data
                histo = fin.Get(histoName)
                histoDN = fin.Get(histoNameDN)

                # rebin
                print "NTurnon: " + str(NTurnon)
                histo.Rebin(rebinList[NTurnon])
                histoDN.Rebin(rebinList[NTurnon])

                # Divide to obtain Turnons #TODO USE TGraphs!!!
                ErrGraph = TGraphAsymmErrors(histo, histoDN, 'b(1,1) mode')

                # HISTO COSMETICS

                ### histo style
                ErrGraph.SetLineStyle(TLineStyle)
                print "TMarkerStyle[NData]: " + str(TMarkerStyle[NData])
                ErrGraph.SetMarkerStyle(TMarkerStyle[NData])
                ErrGraph.SetLineColor(colorList[NTurnon])
                ErrGraph.SetMarkerColor(colorList[NTurnon])

                #c.Update()

                ## Add graph
                MultiGr.Add(ErrGraph)

                c.Update()

                ## add legend entry
                legend.AddEntry(ErrGraph,TurnonLegendEntryList[NTurnon] + " - " + inputDataTurnonHeader[NData],"p")

                NData +=1

                c.Update()

            if (not EnableCombinedTurnons):
                # Draw Multipraph
                MultiGr.Draw("APE")

                # set range
                MultiGr.GetXaxis().SetLimits(minXList[NTurnon], maxXList[NTurnon])
                MultiGr.GetYaxis().SetLimits(0.0, 1.2)

                ### axis style
                MultiGr.GetXaxis().SetTitleOffset(1.4)
                MultiGr.GetYaxis().SetTitleOffset(1.4)

                MultiGr.GetYaxis().SetTitle("entries/width")
                MultiGr.GetXaxis().SetTitle("offline pt [GeV]")

                #Draw Legend
                legend.Draw("Same")

                # ATLAS Style Setting
                AtlasStyle.ATLAS_LABEL(0.5, 0.55, internal = ATLAS_Internal, preliminary = ATLAS_Preliminary, color=1)
                AtlasStyle.myText(0.5, 0.5, 1, "#sqrt{s} = 13 TeV")

                c.Update()

                # Save Turnons
                c.SaveAs("makeResultPdf/plots/efficienciesPT" + TurnonName +".pdf")
                c.SaveAs("makeResultPdf/plots/efficienciesPT" + TurnonName +".eps")

            NTurnon += 1

    if (EnableCombinedTurnons):
        # Draw Multipraph
        MultiGr.Draw("APE")

        # set range
        MultiGr.GetXaxis().SetLimits(minXList[NCombinedTurnons], maxXList[NCombinedTurnons])
        MultiGr.GetYaxis().SetLimits(0.0, 1.2)

        ### axis style
        MultiGr.GetXaxis().SetTitleOffset(1.4)
        MultiGr.GetYaxis().SetTitleOffset(1.4)

        MultiGr.GetYaxis().SetTitle("entries/width")
        MultiGr.GetXaxis().SetTitle("offline pt [GeV]")

        #Draw Legend
        legend.Draw("Same")

        # ATLAS Style Setting
        AtlasStyle.ATLAS_LABEL(0.5, 0.55, internal = ATLAS_Internal, preliminary = ATLAS_Preliminary, color=1)
        AtlasStyle.myText(0.5, 0.5, 1, "#sqrt{s} = 13 TeV")

        c.Update()

        # Save Turnons
        c.SaveAs("makeResultPdf/plots/efficienciesPT" + CombinedTurnons +".pdf")
        c.SaveAs("makeResultPdf/plots/efficienciesPT" + CombinedTurnons +".eps")

    NCombinedTurnons +=1
