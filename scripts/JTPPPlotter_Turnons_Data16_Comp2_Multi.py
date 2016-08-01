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

outputfile = TFile("makeResultPdf/Turnons.root","recreate")

## input files
#fin1 = TFile.Open("hist-20160425_PeriodJ_282625_r7734_WithOldCuts_eta32/hist-20160425_PeriodJ_282625_r7734.root")
#fin1 = TFile.Open("hist-Data16_AOD_run297041/hist-Data16_AOD_run297041.root")
#fin1 = TFile.Open("hist-Data16_AOD_run299584/hist-Data16_AOD_run299584.root")
#fin2 = TFile.Open("hist-20160425_PeriodJ_282625_r7734_WithOldCuts_eta32/hist-20160425_PeriodJ_282625_r7734.root")

fin1 = TFile.Open("hist-Data16_run300800/hist-Data16_run300800.root")
fin2 = TFile.Open("hist-Data16_run300800_eta20Cut/hist-Data16_run300800.root")

## sample name in the legend
#sampleName1 = "Data 2015"
#sampleName2 = "Data 2016"

#sampleName1 = "run 299584"
#sampleName2 = "Period J"

latexName = "run300800"
sampleName1_HLT = "|eta| < 2.8"
sampleName1_L1 = "|eta| < 2.6"
sampleName2 = "|eta| < 2.0"

AtlasStyle.SetAtlasStyle()
gStyle.SetOptStat(0) # get rid of statistics box

# set close or wider Xaxis range
closer = True

# open logfiles from InputHandler to obtain a list of turnons
turnOnData = open("logfile_turnOns.txt") # newest list of JTPP
turnOnList = turnOnData.readlines()

# remove the \n
turnOnList = ([s.strip('\n') for s in turnOnList])
print "Reading logfile_trigger.txt... selected TurnOns are: \n" + str(turnOnList)

# color array if needed
color = [ kRed+2, kBlue+2, kGreen+2, kCyan+2, kMagenta+2, kYellow+2, kRed-2, kBlue+0, kGreen-6, kCyan-2, kMagenta-7, kYellow-7 ]

# define multiHistoList
multiHistoList = ["HLT-multiJetTriggers", "HLT-singleJetTriggers", "L1-singleJetTriggers", "L1-forwardJetTriggers", "L1-multiJetTriggers"]

# -------------------------- TurnOns ----------------------------------

outputfile.cd()
c = TCanvas("c", sampleName2, 1)

# loop over all multi histograms
for multiHistoName in multiHistoList:

  ## Legend
  legend = TLegend(0.45,0.50,0.9,0.2)
  legend.SetFillColor(0)
  legend.SetTextFont(1)
  legend.SetHeader("")
  legend.SetFillStyle(0)


  # multigraph for errors
  MultiGr = TMultiGraph()


  histoCounter = 0

  # Loop over all turnons
  for turnOn in turnOnList:

    print "Filling... " + multiHistoName

    if (multiHistoName == "HLT-multiJetTriggers"):
      if (turnOn == "HLT_3j175-HLT_j110"): print "using... " + turnOn
      elif (turnOn == "HLT_4j85-HLT_j85"): print "using... " + turnOn
      elif (turnOn == "HLT_6j45-HLT_j60"): print "using... " + turnOn
      else: continue

    if (multiHistoName == "HLT-singleJetTriggers"):
      if (turnOn == "HLT_j25-HLT_j15"): print "using... " + turnOn
      elif (turnOn == "HLT_j60-HLT_j25"): print "using... " + turnOn
      elif (turnOn == "HLT_j110-HLT_j85"): print "using... " + turnOn
      else: continue

    if (multiHistoName == "L1-singleJetTriggers"):
      if (turnOn == "L1_J15-HLT_j15"): print "using... " + turnOn
#      elif (turnOn == "L1_J50-HLT_j25"): print "using... " + turnOn
#      elif (turnOn == "L1_J75-HLT_j45"): print "using... " + turnOn
      elif (turnOn == "L1_J100-HLT_j85"): print "using... " + turnOn
      else: continue

    if (multiHistoName == "L1-forwardJetTriggers"):
      if (turnOn == "L1_J20.31ETA49-HLT_j15_320eta490"): print "using... " + turnOn
      elif (turnOn == "L1_J50.31ETA49-HLT_j45_320eta490"): print "using... " + turnOn
      elif (turnOn == "L1_J75.31ETA49-HLT_j60_320eta490"): print "using... " + turnOn
      else: continue

    if (multiHistoName == "L1-multiJetTriggers"):
      if (turnOn == "L1_3J40-HLT_j60"): print "using... " + turnOn
      elif (turnOn == "L1_4J15-HLT_j45"): print "using... " + turnOn
      else: continue


    # Loopt over EvaluationType
    for EvalType in ["Emu"]: # ["Emu", "TDT"]:

      histoName1 = "TurnOns" + "/" + "effic_pt_" + EvalType + "_" + turnOn 
      histoName1Denum = "TurnOns" + "/" + "effic_DENUM_pt_" + EvalType + "_" + turnOn

      histo1 = fin1.Get(histoName1)
      histo1Denum = fin1.Get(histoName1Denum)

      histo2 = fin2.Get(histoName1)
      histo2Denum = fin2.Get(histoName1Denum)

      # Rebin
      histo1.Rebin(3)
      histo1Denum.Rebin(3)
      histo2.Rebin(3)
      histo2Denum.Rebin(3)

      ErrGraph1 = TGraphAsymmErrors(histo1, histo1Denum, 'b(1,1) mode')
      ErrGraph2 = TGraphAsymmErrors(histo2, histo2Denum, 'b(1,1) mode')

      # Divide histograms
      histo1.Divide(histo1, histo1Denum, 1.0, 1.0 , "")
      histo2.Divide(histo2, histo2Denum, 1.0, 1.0 , "")

      # get rid of non fully efficient region
      if (turnOn == "HLT_j110-HLT_j85"):
        for n in range (0, 28):
          histo1.SetBinContent(n, -1)
          ErrGraph1.SetPoint(n, 1000, 1000)

          histo2.SetBinContent(n, -1)
          ErrGraph2.SetPoint(n, 1000, 1000)

      if (turnOn == "L1_J75.31ETA49-HLT_j60_320eta490"):
        for n in range (0, 24):
          histo1.SetBinContent(n, -1)
          ErrGraph1.SetPoint(n, 1000, 1000)

          histo2.SetBinContent(n, -1)
          ErrGraph2.SetPoint(n, 1000, 1000)

      if (turnOn == "L1_J50.31ETA49-HLT_j45_320eta490"):
        for n in range (0, 18):
          histo1.SetBinContent(n, -1)
          ErrGraph1.SetPoint(n, 1000, 1000)

          histo2.SetBinContent(n, -1)
          ErrGraph2.SetPoint(n, 1000, 1000)

      if (turnOn == "HLT_j60-HLT_j25"):
        for n in range (0, 10):
          histo1.SetBinContent(n, -1)
          ErrGraph1.SetPoint(n, 1000, 1000)

          histo2.SetBinContent(n, -1)
          ErrGraph2.SetPoint(n, 1000, 1000)

      if (turnOn == "L1_J75-HLT_j45"):
        for n in range (0, 20):
          histo1.SetBinContent(n, -1)
          ErrGraph1.SetPoint(n, 1000, 1000)

          histo2.SetBinContent(n, -1)
          ErrGraph2.SetPoint(n, 1000, 1000)

      if (turnOn == "L1_J100-HLT_j85"):
        for n in range (0, 20):
          histo1.SetBinContent(n, -1)
          ErrGraph1.SetPoint(n, 1000, 1000)

          histo2.SetBinContent(n, -1)
          ErrGraph2.SetPoint(n, 1000, 1000)


      # Set Axis Titles
      histo1.GetXaxis().SetTitle("offline pt [GeV]")
      histo1.GetYaxis().SetTitle("efficiency")

      # Set Title offset
      histo1.GetXaxis().SetTitleOffset(1.4)
      histo1.GetYaxis().SetTitleOffset(1.4)

      # Set Line style
      histo1.SetLineStyle(0)

      # Set Marker Style
      histo1.SetMarkerStyle(20)
      ErrGraph1.SetMarkerStyle(20)
      histo2.SetMarkerStyle(24)
      ErrGraph2.SetMarkerStyle(24)

      # Set Line color
      histo1.SetLineColor(color[histoCounter])
      ErrGraph1.SetLineColor(color[histoCounter])
      histo2.SetLineColor(color[histoCounter])
      ErrGraph2.SetLineColor(color[histoCounter])

      # Set marker color
      histo1.SetMarkerColor(color[histoCounter])
      ErrGraph1.SetMarkerColor(color[histoCounter])
      histo2.SetMarkerColor(color[histoCounter])
      ErrGraph2.SetMarkerColor(color[histoCounter])

      # Set range
      histo1.GetYaxis().SetRangeUser(0.0, 1.1)
      histo1.GetXaxis().SetRangeUser(20.0, 600.0)
      if (closer):
        if (multiHistoName == "HLT-multiJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 350.0)
        if (multiHistoName == "HLT-singleJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 250.0)
        if (multiHistoName == "L1-singleJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 300.0)
        if (multiHistoName == "L1-forwardJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 300.0)
        if (multiHistoName == "L1-multiJetTriggers"): histo1.GetXaxis().SetRangeUser(20.0, 250.0)



      # Add legend entry
      # different legend entries for HLT and L1  trigger plots:
      if "L1" in multiHistoName:
        legend.AddEntry(histo1,turnOn.rsplit('-',1)[0]  + " " + sampleName1_L1, "p")
      else:
        legend.AddEntry(histo1,turnOn.rsplit('-',1)[0]  + " " + sampleName1_HLT, "p")
      legend.AddEntry(histo2,turnOn.rsplit('-',1)[0]  + " " + sampleName2, "p")

      # check the histoCounter and therefore if Draw need to be with the option "Same" or without
      if (histoCounter == 0):
        histo1.Draw("hist p")
        MultiGr.Add(ErrGraph1)
      else:
        histo1.Draw("Same hist p")
        MultiGr.Add(ErrGraph1)

      histo2.Draw("Same hist p")
      MultiGr.Add(ErrGraph2)

      histoCounter +=1

      c.Update()

      # Draw legend and ATLAS style label
      legend.Draw("Same")
      AtlasStyle.ATLAS_LABEL(0.5, 0.55, internal = False, preliminary = True, color=1)
      AtlasStyle.myText(0.5, 0.5, 1, "#sqrt{s} = 13 TeV")


      c.Update()

    # Set Title
    l = TLatex(20,1.11, "#font[12]{" + latexName + "}")
    l.Draw("Same")

    # Draw multiGraph
    MultiGr.Draw("P")

    # Write out to file
    MultiGr.Write()

    c.Update()

# save pdf and eps files
## convert names latex friendly
#triggerPDFNamePrae = re.sub("_","-", turnOn)
#triggerPDFName =  re.sub(".31ETA","-31ETA", triggerPDFNamePrae)

  c.SaveAs("makeResultPdf/plots/"+"efficienciesPT-" + multiHistoName + ".pdf")
  c.SaveAs("makeResultPdf/plots/"+"efficienciesPT-" + multiHistoName + ".pdf")


outputfile.Close()



