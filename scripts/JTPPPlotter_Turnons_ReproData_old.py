#!/bin/python
########################################################################
# The JTPPPlotterCompPMvsDS by Edgar Kellermann (2016/03/14)
# especially optimised to make comparison plots between trigger and offline plots
# that were created by JTPP
########################################################################

from ROOT import *
import math
import sys
import re
from array import array
import AtlasStyle
from JTPPPlotter_RatioUtils import divideGraphs

#import JESResponseFitter # Thank you, Antonio!
#import prettyPalette


#ROOT.gROOT.SetBatch(True)

#the 2D plots
  #KEY: TH2D     mjj_vs_BCHCORRCELL_NominalJES;1 Nominal JES
  #KEY: TH2D     pt_vs_BCHCORRCELL_NominalJES;1  Nominal JES

outputfile = TFile("makeResultPdf/JetTriggerPerformancePlots.root","recreate")

## determine the input files
fin1 = TFile.Open("hist-20160425_PeriodJ_282625_r7734/hist-20160425_PeriodJ_282625_r7734.root")

## sample name in the legend
sampleName1 = "reprocessed Data"

## for normalisation reason
## CD: why not reading this from the cutflow, or from a histogram with GetEntries() ?
#NEvents1 = 99619
#NEvents2 = 723433

AtlasStyle.SetAtlasStyle()
gStyle.SetOptStat(0) # get rid of statistics box

closer = True

# open logfiles from InputHandler to see what we need to read out
turnOnData = open("logfile_turnOns.txt")
turnOnList = turnOnData.readlines()

# remove the \n
turnOnList = ([s.strip('\n') for s in turnOnList])
print "Reading logfile_trigger.txt... selected TurnOns are: \n" + str(turnOnList)

color = [ kRed+2, kBlue+2, kGreen+2, kCyan+2, kMagenta+2, kYellow+2, kRed-2, kBlue+0, kGreen-6, kCyan-2, kMagenta-7, kYellow-7 ]

# read mapping.txt to get the mapping
mappingData = open("mapping.txt")
mappingList = mappingData.readlines()

mappingList = ([s.strip('\n') for s in mappingList])
print "Reading mapping.txt... \n" + str(mappingList)

# -------------------------- TurnOns ----------------------------------

for turnOn in turnOnList:  # triggerList: WE ONLY LOOK AT J60


  print "turnOn:" + turnOn

  outputfile.cd()
  c = TCanvas()

  legend = TLegend(0.5,0.40,0.75,0.25)

  legend.SetFillColor(0)
  legend.SetTextFont(1)

  legendName1 = turnOn.split("-")

  legend.SetHeader(legendName1[0])
  legend.SetFillStyle(0)

  # multigraph
  MultiGr = TMultiGraph()

  # EvaluationType
  for EvalType in ["Emu", "TDT"]:

    histoName1 = "TurnOns" + "/" + "effic_pt_" + EvalType + "_" + turnOn
    histoName1Denum = "TurnOns" + "/" + "effic_DENUM_pt_" + EvalType + "_" + turnOn

    histo1 = fin1.Get(histoName1)
    histo1Denum = fin1.Get(histoName1Denum)

    ErrGraph1 = TGraphAsymmErrors(histo1, histo1Denum, 'b(1,1) mode')

    #Divide histograms
    histo1.Divide(histo1, histo1Denum, 1.0, 1.0 , "")

    histo1.GetXaxis().SetTitle("offline pt [GeV]")
    histo1.GetXaxis().SetTitle("offline pt [GeV]")

    histo1.GetYaxis().SetTitle("efficiency")
#    histo1.Scale(1, "width")

    histo1.SetLineColor(kRed+2)
    histo1.SetMarkerColor(kRed+2)
    ErrGraph1.SetLineColor(kRed+2)
    ErrGraph1.SetMarkerColor(kRed+2)

    histo1.GetYaxis().SetRangeUser(0.0, 1.1)
    histo1.GetXaxis().SetRangeUser(20.0, 300.0)
    if (closer):
      if (turnOn == "HLT_j25-HLT_j15"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "HLT_j60-HLT_j25"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "HLT_j110-HLT_j85"): histo1.GetXaxis().SetRangeUser(20.0, 250.0)
      if (turnOn == "HLT_j360-HLT_j260"): histo1.GetXaxis().SetRangeUser(20.0, 700.0)
      if (turnOn == "L1_J15-HLT_j15"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "L1_J20-HLT_j25"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "L1_J100-HLT_j85"): histo1.GetXaxis().SetRangeUser(60.0, 300.0)
      if (turnOn == "HLT_3j175-HLT_j110"): histo1.GetXaxis().SetRangeUser(20.0, 350.0)
      if (turnOn == "HLT_4j85-HLT_j85"): histo1.GetXaxis().SetRangeUser(20.0, 250.0)
      if (turnOn == "HLT_6j45-HLT_j60"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "L1_3J40-HLT_j60"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "L1_4J15-HLT_j45"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "HLT_j25_320eta490-HLT_j15_320eta490"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "HLT_j60_320eta490-HLT_j25_320eta490"): histo1.GetXaxis().SetRangeUser(20.0, 250.0)
      if (turnOn == "L1_J15.31ETA49-HLT_j15_320eta490"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)
      if (turnOn == "L1_J40.31ETA49-HLT_j15_320eta490"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)

    histo1.SetLineStyle(0)
    if (EvalType == "Emu"):
      histo1.SetMarkerStyle(20)
      ErrGraph1.SetMarkerStyle(20)
    else:
      histo1.SetMarkerStyle(24)
      ErrGraph1.SetMarkerStyle(24)
    histo1.GetXaxis().SetTitleOffset(1.4)
    histo1.GetYaxis().SetTitleOffset(1.4)


    legend.AddEntry(histo1, sampleName1 + " (" + EvalType + ")","lp")


    histo1.Write()

    if (EvalType == "Emu"):
      histo1.Draw("hist p")
      MultiGr.Add(ErrGraph1)
    else:
      histo1.Draw("Same p")
      MultiGr.Add(ErrGraph1) 

    c.Update()

    legend.Draw("Same")
    AtlasStyle.ATLAS_LABEL(0.5, 0.55, internal = False, preliminary = True, color=1)
    AtlasStyle.myText(0.5, 0.5, 1, "#sqrt{s} = 13 TeV")


    c.Update()

  MultiGr.Draw("P")
  c.Update()

  triggerPDFNamePrae = re.sub("_","-", turnOn)
  triggerPDFName =  re.sub(".31ETA","-31ETA", triggerPDFNamePrae)

  c.SaveAs("makeResultPdf/plots/"+"efficienciesPT-" + EvalType + "-" + triggerPDFName + ".pdf")
  c.SaveAs("makeResultPdf/plots/"+"efficienciesPT-" + EvalType + "-" + triggerPDFName + ".pdf")


outputfile.Close()



