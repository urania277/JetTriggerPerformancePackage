#!/bin/python
########################################################################
# The JTPPPlotterCompTrigAndOffl by Edgar Kellermann (2016/03/14)
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

## determine the input files
fin1 = TFile.Open("hist-Data16_run298609/hist-Data16_run298609.root")
fin2 = TFile.Open("hist-20160425_PeriodJ_282625_r7734_woCuts/hist-20160425_PeriodJ_282625_r7734.root")

# label below ATLAS
labelBelowATLAS = "Data 2016"
#labelBelowATLAS = "Period J Data"

## sample name in the legend
sampleName1 = "Run 298609"
sampleName2 = "Period J Data"

## for normalisation reason
## CD: why not reading this from the cutflow, or from a histogram with GetEntries() ?
#NEvents1 = 99619
#NEvents2 = 723433

AtlasStyle.SetAtlasStyle()
gStyle.SetOptStat(0) # get rid of statistics box


# open logfiles from InputHandler to see what we need to read out
triggerData = open("logfile_trigger.txt")
triggerList = triggerData.readlines()

# remove the \n
triggerList = ([s.strip('\n') for s in triggerList])
print "Reading logfile_trigger.txt... selected Triggers are: \n" + str(triggerList)

color = [ kRed+2, kBlue+2, kGreen+2, kCyan+2, kMagenta+2, kYellow+2, kRed-2, kBlue+0, kGreen-6, kCyan-2, kMagenta-7, kYellow-7 ]



# -------------------------- Kinematic Plots ----------------------------------



for praefix in ["lead"]: # ["", "lead", "sublead", "third"]:
  for obs in ["eta"]:# "E", "pt", "phi", "yStar", "deltaPhi", "pTBalance", "MHT", "MHTPhi", "EMFrac", "HECFrac", "FracSamplingMax"]: #,  "mjj", "m23"]: JUST FOR NOW, UNBLINDING PROTECTION

    for trigger in triggerList:

      # for Drawing
      counter = 0

      outputfile.cd()
      c = TCanvas()

      if ((obs == "eta")| (obs == "phi")):
        legend = TLegend(0.65,0.40,0.8,0.60)
      else:
        legend = TLegend(0.5,0.60,0.75,0.75)
      if (trigger == "HLT_j360"):
        legend = TLegend(0.2,0.60,0.45,0.75)

      legend.SetFillColor(0)
      legend.SetTextFont(1)

      if (trigger == "STUDYALL"):
        legendName = "Any triggered Event"
      else:
        legendName = trigger
      legend.SetHeader(legendName)

      # no lead, sublead, third mjj:
      if (((obs == "mjj")|(obs == "m23")|(obs == "yStar")|(obs == "deltaPhi")|(obs == "pTBalance")|(obs == "MHT")|(obs == "MHTPhi")) & (praefix != "")): continue

      #no all jets for vector observables
      if (((obs == "E")|(obs == "pt")|(obs == "eta")|(obs == "phi")|(obs == "EMFrac")|(obs == "HECFrac")|(obs == "FracSamplingMax")) & (praefix == "")): continue


      #making the pads for the histoRatio:
      pad1 = TPad("pad1","pad1",0.05,0.30,1,1);
      pad2 = TPad("pad2","pad2",0.05,0.05,1,0.30);
      pad1.SetTopMargin(0.02);
      pad2.SetTopMargin(0.0);
      pad1.SetBottomMargin(0.0);
      pad2.SetBottomMargin(0.30);

      pad1.Draw();
      pad2.Draw();


      for jetType in ["jet", "trigJet"]:

        histoName = trigger + "/" + jetType + "Kinematics/" + praefix + jetType  +  "_" + obs

        print "====== Open: " + histoName

        histo1 = fin1.Get(histoName)
        histo2 = fin2.Get(histoName)

        if ((obs == "pt")| (obs == "E")| (obs == "mjj")| (obs == "m23")| (obs == "MHT")):
          histo1.GetXaxis().SetTitle(obs + " [GeV]")
          histo2.GetXaxis().SetTitle(obs + " [GeV]")
        else:
          histo1.GetXaxis().SetTitle(obs)
          histo2.GetXaxis().SetTitle(obs)

        histo1.GetYaxis().SetTitle("entries/width")
        histo1.Scale(1, "width")
        histo2.GetYaxis().SetTitle("entries/width")
        histo2.Scale(1, "width")

        #Sumw2 important for scaling and division
        histo1.Sumw2()
        histo2.Sumw2()


        #normalising using the Integral of the histogram
        Integral1 = histo1.Integral()
        Integral2 = histo2.Integral()
#        if((Integral1 != 0) & (Integral2 != 0)):
        histo1.Scale(1.0/Integral1)
        histo2.Scale(1.0/Integral2)

        # y axis title
        histo1.GetYaxis().SetTitle("events/width norm.")
        histo2.GetYaxis().SetTitle("events/width norm.")

        #print integral after normalisation
        #print "=== histo1.Integral(): " + str(histo1.Integral())
        #print "=== histo2.Integral(): " + str(histo2.Integral())

        histo1.SetLineColor(kRed+2)
        histo1.SetMarkerColor(kRed+2)
        histo2.SetLineColor(kBlue+2)
        histo2.SetMarkerColor(kBlue+2)


        histo1.SetLineStyle(1)
        histo1.SetMarkerStyle(0)
        histo1.GetXaxis().SetTitleOffset(1.4)
        histo1.GetYaxis().SetTitleOffset(1.4)

        histo2.SetLineStyle(1)
        histo2.SetMarkerStyle(0)
        histo2.GetXaxis().SetTitleOffset(1.4)
        histo2.GetYaxis().SetTitleOffset(1.4)

        if (jetType == "jet") : legendLabel = 

        legend.AddEntry(histo1,sampleName1 + " " + jetType,"lp")
        legend.AddEntry(histo2,sampleName2 + " " + jetType,"lp")

        histo1.Write()
        histo2.Write()

        #ratio plot; divide bin by bin
        histoRatio=histo1.Clone()
        histoRatio.Sumw2()
#        for i in range(0, histoRatio.GetNbinsX()+1):
#          if (histo2.GetBinContent(i) !=0):
#            histoRatio.SetBinContent(i, histo1.GetBinContent(i)/histo2.GetBinContent(i))
#          else:
#            histoRatio.SetBinContent(i, 0.0)
        histoRatio.Divide(histo2)

        ##Formatting and drawing
        c.Update()

        #set y axis range
        histo1.GetYaxis().SetRangeUser(0.0,0.3)
        histo2.GetYaxis().SetRangeUser(0.0,0.3)

        #drawing the main plot
        if ((obs == "pt")| (obs == "E")| (obs == "mjj")| (obs == "m23")):
          pad1.SetLogy(True)
          pad1.SetLogx(True)

        if ((obs == "HECFrac")| (obs == "MHT")| (obs == "pTBalance")| (obs == "deltaPhi")):
          pad1.SetLogy(True)


        #Filling pad 1
        pad1.cd()

        if (counter == 0):
          histo1.Draw("HIST")
          print "jetType in if: " + jetType
        else:
          print "jetType in else: " + jetType
          histo1.Draw("Same HIST")
        histo2.Draw("Same HIST")

        counter += 1

        c.Update()

        legend.Draw("Same")
        if ((obs == "eta")| (obs == "phi")| (obs == "yStar")| (obs == "EMFrac")):
          AtlasStyle.ATLAS_LABEL(0.6, 0.25, internal = True, preliminary = False, color=1)
          AtlasStyle.myText(0.65, 0.2, 1, "#sqrt{s} = 13 TeV")
          AtlasStyle.myText(0.65, 0.15, 1, labelBelowATLAS)
        else:
        #HLT_j360 special adjustment
          if (trigger == "HLT_j360"):
            AtlasStyle.ATLAS_LABEL(0.5, 0.85, internal = True, preliminary = False, color=1)
            AtlasStyle.myText(0.5, 0.8, 1, "#sqrt{s} = 13 TeV")
            AtlasStyle.myText(0.5, 0.75, 1, labelBelowATLAS)
          else:
            AtlasStyle.ATLAS_LABEL(0.5, 0.85, internal = True, preliminary = False, color=1)
            AtlasStyle.myText(0.5, 0.8, 1, "#sqrt{s} = 13 TeV")
            AtlasStyle.myText(0.5, 0.75, 1, labelBelowATLAS)


        c.Update()

        pad2.cd()
        pad2.SetLogy(False)
        if ((obs == "pt")| (obs == "E")| (obs == "mjj")| (obs == "m23")):
          histoRatio.GetXaxis().SetTitle(obs+" [GeV]")
          pad2.SetLogx(True) #only logscale for GeV related values


        histoRatio.GetXaxis().SetTitleSize(0.07)
        histoRatio.GetXaxis().SetLabelFont(42)
        histoRatio.GetXaxis().SetLabelSize(0.1)
        histoRatio.GetXaxis().SetTitleSize(0.1)
        histoRatio.GetYaxis().SetRangeUser(0.5,1.5)
        histoRatio.GetYaxis().SetTitle(sampleName1+"/"+sampleName2)
        histoRatio.GetYaxis().SetTitleOffset(0.7)
        histoRatio.GetYaxis().SetLabelFont(42)
        histoRatio.GetYaxis().SetLabelSize(0.1)
        histoRatio.GetYaxis().SetTitleSize(0.08)

        if (counter ==0):
          histoRatio.Draw("")
        else:
          histoRatio.Draw("Same")

        # black lines at 1.0 in ratio plot
        line1 = TLine(histoRatio.GetXaxis().GetXmin(), 1.0,histoRatio.GetXaxis().GetXmax(), 1.0);
        line1.SetLineColor(kBlack);
        line1.SetLineStyle(3);
        line1.Draw("Same");

        line2 = TLine(histoRatio.GetXaxis().GetXmin(), 1.1,histoRatio.GetXaxis().GetXmax(), 1.1);
        line2.SetLineColor(kBlack);
        line2.SetLineStyle(3);
        line2.Draw("Same");

        line3 = TLine(histoRatio.GetXaxis().GetXmin(), 0.9,histoRatio.GetXaxis().GetXmax(), 0.9);
        line3.SetLineColor(kBlack);
        line3.SetLineStyle(3);
        line3.Draw("Same");


      triggerPDFName = re.sub("_","", trigger)

      c.SaveAs("makeResultPdf/plots/"+triggerPDFName + praefix +"jet" + obs +".pdf")
      c.SaveAs("makeResultPdf/plots/"+triggerPDFName + praefix +"jet" + obs +".eps")


outputfile.Close()



