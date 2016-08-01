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
#from JTPPPlotter_RatioUtils import divideGraphs

#import JESResponseFitter # Thank you, Antonio!
#import prettyPalette


#ROOT.gROOT.SetBatch(True)

#the 2D plots
  #KEY: TH2D     mjj_vs_BCHCORRCELL_NominalJES;1 Nominal JES
  #KEY: TH2D     pt_vs_BCHCORRCELL_NominalJES;1  Nominal JES

outputfile = TFile("makeResultPdf/JetTriggerPerformancePlots.root","recreate")

## input files
fin1 = TFile.Open("hist-Data16/hist-Data16.root")
#fin1 = TFile.Open("hist-Data16_run296939/hist-Data16_run296939.root")
#fin1 = TFile.Open("hist-Data16_run296942/hist-Data16_run296942.root")

## sample name in the legend
sampleName1 = "Data 2016"
#sampleName1 = "2016 Data, Run 296939"
#sampleName1 = "2016 Data, Run 296942"

AtlasStyle.SetAtlasStyle()
gStyle.SetOptStat(0) # get rid of statistics box

# set close or wider Xaxis range
closer = True

# open logfiles from InputHandler to obtain a list of turnons
#turnOnData = open("logfile_turnOns_Data16.txt") # newest list of JTPP
turnOnData = open("logfile_turnOns.txt") # newest list of JTPP
turnOnList = turnOnData.readlines()

# remove the \n
turnOnList = ([s.strip('\n') for s in turnOnList])
print "Reading logfile_trigger.txt... selected TurnOns are: \n" + str(turnOnList)

# color array if needed
color = [ kRed+2, kBlue+2, kGreen+2, kCyan+2, kMagenta+2, kYellow+2, kRed-2, kBlue+0, kGreen-6, kCyan-2, kMagenta-7, kYellow-7 ]

# define multiHistoList
multiHistoList = ["HLT-multiJetTriggers", "HLT-singleJetTriggers-low", "HLT-singleJetTriggers-high", "HLT-forwardJetTriggers", 
"L1-multiJetTriggers", "L1-singleJetTriggers", "L1-forwardJetTriggers"]

# -------------------------- TurnOns ----------------------------------

outputfile.cd()
c = TCanvas("c", sampleName1, 1)

# loop over all multi histograms
for multiHistoName in multiHistoList:

  ## Legend
  legend = TLegend(0.5,0.40,0.75,0.25)
  legend.SetFillColor(0)
  legend.SetTextFont(1)
  legend.SetHeader("emulated")
  legend.SetFillStyle(0)


  # multigraph for errors
  MultiGr = TMultiGraph()


  histoCounter = 0

  # Loop over all turnons
  for turnOn in turnOnList:


    ## Decide which turnon will be in which multiHisto
    print "Filling... " + multiHistoName
    if (multiHistoName == "HLT-multiJetTriggers"):
      if (turnOn == "HLT_3j175-HLT_j110"): print "using... " + turnOn
      elif (turnOn == "HLT_4j85-HLT_j85"): print "using... " + turnOn
      elif (turnOn == "HLT_6j45-HLT_j60"): print "using... " + turnOn
      else: continue

    print "Filling... " + multiHistoName
    if (multiHistoName == "HLT-singleJetTriggers-low"):
      if (turnOn == "HLT_j25-HLT_j15"): print "using... " + turnOn
      elif (turnOn == "HLT_j60-HLT_j25"): print "using... " + turnOn
      elif (turnOn == "HLT_j110-HLT_j85"): print "using... " + turnOn
      else: continue

    print "Filling... " + multiHistoName
    if (multiHistoName == "HLT-singleJetTriggers-high"):
      if (turnOn == "HLT_j360-HLT_j260"): print "using... " + turnOn
      elif (turnOn == "HLT_j380-HLT_j260"): print "using... " + turnOn
      elif (turnOn == "HLT_j400-HLT_j260"): print "using... " + turnOn
      else: continue

    print "Filling... " + multiHistoName
    if (multiHistoName == "HLT-forwardJetTriggers"):
      if (turnOn == "HLT_j25_320eta490-HLT_j15_320eta490"): print "using... " + turnOn
      elif (turnOn == "HLT_j60_320eta490-HLT_j25_320eta490"): print "using... " + turnOn
      else: continue

    print "Filling... " + multiHistoName
    if (multiHistoName == "L1-multiJetTriggers"):
      if (turnOn == "L1_3J40-HLT_j60"): print "using... " + turnOn
      elif (turnOn == "L1_4J15-HLT_j45"): print "using... " + turnOn
      else: continue

    if (multiHistoName == "L1-singleJetTriggers"):
      if (turnOn == "L1_J15-HLT_j15"): print "using... " + turnOn
      elif (turnOn == "L1_J20-HLT_j25"): print "using... " + turnOn
      elif (turnOn == "L1_J100-HLT_j85"): print "using... " + turnOn
      else: continue


    if (multiHistoName == "L1-forwardJetTriggers"):
      if (turnOn == "L1_J15.31ETA49-HLT_j15_320eta490"): print "using... " + turnOn
      else: continue


    # Loopt over EvaluationType
    for EvalType in ["Emu"]: # ["Emu", "TDT"]:

      histoName1 = "TurnOns" + "/" + "effic_pt_" + EvalType + "_" + turnOn 
      histoName1Denum = "TurnOns" + "/" + "effic_DENUM_pt_" + EvalType + "_" + turnOn

      histo1 = fin1.Get(histoName1)
      histo1Denum = fin1.Get(histoName1Denum)

      ErrGraph1 = TGraphAsymmErrors(histo1, histo1Denum, 'b(1,1) mode')

      # Divide histograms
      histo1.Divide(histo1, histo1Denum, 1.0, 1.0 , "")

      # get rid of non fully efficient region
      if (turnOn == "HLT_j110-HLT_j85"):
        for n in range (0, 18):
          histo1.SetBinContent(n, -1)
          ErrGraph1.SetPoint(n, 1000, 1000)

      # Set Axis Titles
      histo1.GetXaxis().SetTitle("offline mjj [GeV]")
      histo1.GetYaxis().SetTitle("efficiency")

      # Set Title offset
      histo1.GetXaxis().SetTitleOffset(1.4)
      histo1.GetYaxis().SetTitleOffset(1.4)

      # Set Line style
      histo1.SetLineStyle(0)

      # Set Marker Style
      if (EvalType == "Emu"):
        histo1.SetMarkerStyle(20)
        ErrGraph1.SetMarkerStyle(20)
      else:
        histo1.SetMarkerStyle(24)
        ErrGraph1.SetMarkerStyle(24)

      # Set Line color
      histo1.SetLineColor(color[histoCounter])
      ErrGraph1.SetLineColor(color[histoCounter])

      # Set marker color
      histo1.SetMarkerColor(color[histoCounter])
      ErrGraph1.SetMarkerColor(color[histoCounter])

      # Set range
      histo1.GetYaxis().SetRangeUser(0.0, 1.1)
      histo1.GetXaxis().SetRangeUser(20.0, 1000.0)
#      if (closer):
#        if (multiHistoName == "HLT-multiJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 350.0)
#        if (multiHistoName == "HLT-singleJetTriggers-low"): histo1.GetXaxis().SetRangeUser(20.0, 250.0)
#        if (multiHistoName == "HLT-singleJetTriggers-high"): histo1.GetXaxis().SetRangeUser(300.0, 600.0)
#        if (multiHistoName == "HLT-forwardJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 150.0)
#        if (multiHistoName == "HLT_j360-HLT_j260"): histo1.GetXaxis().SetRangeUser(200.0, 600.0)
#        if (multiHistoName == "L1-multiJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 250.0)
#        if (multiHistoName == "L1-singleJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 300.0)
#        if (multiHistoName == "L1-forwardJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 200.0)


      # Add legend entry
      legend.AddEntry(histo1,turnOn.rsplit('-',1)[0],"p")

      # check the histoCounter and therefore if Draw need to be with the option "Same" or without
      if (histoCounter == 0):
        histo1.Draw("hist p")
        MultiGr.Add(ErrGraph1)
      else:
        histo1.Draw("Same hist p")
        MultiGr.Add(ErrGraph1)

      histoCounter +=1

      c.Update()

      # Draw legend and ATLAS style label
      legend.Draw("Same")
      AtlasStyle.ATLAS_LABEL(0.5, 0.55, internal = True, preliminary = False, color=1)
      AtlasStyle.myText(0.5, 0.5, 1, "#sqrt{s} = 13 TeV")


      c.Update()

    # Set Title
    l = TLatex(20,1.11, "#font[12]{" + sampleName1 + "}")
    l.Draw("Same")

    # Draw multiGraph
    MultiGr.Draw("P")

    c.Update()

# save pdf and eps files
## convert names latex friendly
#triggerPDFNamePrae = re.sub("_","-", turnOn)
#triggerPDFName =  re.sub(".31ETA","-31ETA", triggerPDFNamePrae)

  c.SaveAs("makeResultPdf/plots/"+"efficienciesPT-" + multiHistoName + ".pdf")
  c.SaveAs("makeResultPdf/plots/"+"efficienciesPT-" + multiHistoName + ".pdf")


outputfile.Close()



