/*--------------------------------------------------------------------
TriggerHistoPack.cxx

TriggerHistoPack is a compact class managing all kinematic and response histograms of one specific trigger.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/TriggerHistoPack.h>
#include <EventLoop/Worker.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



TriggerHistoPack::TriggerHistoPack(std::string triggerDir, std::string trigger, int nthJet, ConfigStatus* a_CS):
    m_triggerDir(triggerDir),
    m_trigger(trigger),
    m_nthJet(nthJet),
    CS(a_CS),
    ptRespOffVsTruthMatrix(nullptr),
    ptRespTrigVsTruthMatrix(nullptr),
    ptRespTrigVsOffMatrix(nullptr),
    //    ptRespOffVsTruthMatrixPtBins(nullptr),
    //    ptRespTrigVsTruthMatrixPtBins(nullptr),
    //    ptRespTrigVsOffMatrixPtBins(nullptr),
    //    ptRespOffVsTruthMatrixEtaBins(nullptr),
    //    ptRespTrigVsTruthMatrixEtaBins(nullptr),
    //    ptRespTrigVsOffMatrixEtaBins(nullptr),
    mjjRespOffVsTruthMatrix(nullptr),
    mjjRespTrigVsTruthMatrix(nullptr),
    mjjRespTrigVsOffMatrix(nullptr)
{
  if (m_debug) std::cout << "Starting constructor TriggerHistoPack()..." << std::endl;

  myTools = new ToolsJTPP();
}

TriggerHistoPack::~TriggerHistoPack()
{
  if (m_debug) std::cout << "Starting destructor TriggerHistoPack()..." << std::endl;
}

void TriggerHistoPack::BookAll(EL::Worker* wk)
{
 if (m_debug) std::cout << "Starting BookAll()..." << std::endl;


   // --- BINNING
  const int  ptRoughBinNumber = 26;
  double ptRoughBinning[ptRoughBinNumber] = { 30.0, 50.0, 70, 90, 110, 130, 150, 170, 190, 210, 230, 250, 270, 290, 310, 310, 330, 350, 370, 390, 410, 430, 450, 470, 490, 510};

  const int ptFineBinNumber = 50;
  double ptFineBinning[ptFineBinNumber] = {15. ,20. ,25. ,35. ,45. ,55. ,70. ,85. ,100. ,116. ,134. ,152. ,172. ,194. ,216. ,240. ,264. ,290. ,318. ,346.,376.,408.,442.,478.,516.,556.,598.,642.,688.,736.,786.,838.,894.,952.,1012.,1076.,1162.,1250.,1310.,1420.,1530.,1750.,1992.,2242.,2500.,2850.,3200.,3600.,4000.,4600.};

  const int etaBinNumber = 17;
  double etaBinning[etaBinNumber] = {-4.9,-3.1,-2.8,-2.1,-1.8,-1.5,-1.2,-0.8,0.0,0.8,1.2,1.5,1.8,2.1,2.8,3.1,4.9};

  const int etaOneBinNumber = 2;
  double etaOneBin[etaOneBinNumber] = {-4.9, 4.9};

  const int etaAreaBinNumber = 4;
  double etaAreaBin[etaAreaBinNumber] = {0.0, 0.8, 1.6, 4.9};

  const int ptOneBinNumber = 2;
  double ptOneBin[ptOneBinNumber] = {30.0, 510.0};

  const int mjjBinNumber = 173;
  double mjjBinning[mjjBinNumber] = {50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 150.0, 160.0, 170.0, 180.0, 190.0, 203.0, 216.0, 229.0, 243.0, 257.0, 272.0, 287.0, 303.0, 319.0, 335.0, 352.0, 369.0, 387.0, 405.0, 424.0, 443.0, 462.0, 482.0, 502.0, 523.0, 544.0, 566.0, 588.0, 611.0, 634.0, 657.0, 681.0, 705.0, 730.0, 755.0, 781.0, 807.0, 834.0, 861.0, 889.0, 917.0, 946.0, 976.0, 1006.0, 1037.0, 1068.0, 1100.0, 1133.0, 1166.0, 1200.0, 1234.0, 1269.0, 1305.0, 1341.0, 1378.0, 1416.0, 1454.0, 1493.0, 1533.0, 1573.0, 1614.0, 1656.0, 1698.0, 1741.0, 1785.0, 1830.0, 1875.0, 1921.0, 1968.0, 2016.0, 2065.0, 2114.0, 2164.0, 2215.0, 2267.0, 2320.0, 2374.0, 2429.0, 2485.0, 2542.0, 2600.0, 2659.0, 2719.0, 2780.0, 2842.0, 2905.0, 2969.0, 3034.0, 3100.0, 3167.0, 3235.0, 3305.0, 3376.0, 3448.0, 3521.0, 3596.0, 3672.0, 3749.0, 3827.0, 3907.0, 3988.0, 4070.0, 4154.0, 4239.0, 4326.0, 4414.0, 4504.0, 4595.0, 4688.0, 4782.0, 4878.0, 4975.0, 5074.0, 5175.0, 5277.0, 5381.0, 5487.0, 5595.0, 5705.0, 5817.0, 5931.0, 6047.0, 6165.0, 6285.0, 6407.0, 6531.0, 6658.0, 6787.0, 6918.0, 7052.0, 7188.0, 7326.0, 7467.0, 7610.0, 7756.0, 7904.0, 8055.0, 8208.0, 8364.0, 8523.0, 8685.0, 8850.0, 9019.0, 9191.0, 9366.0, 9544.0, 9726.0, 9911.0, 10100.0, 10292.0, 10488.0, 10688.0, 10892.0, 11100.0, 11312.0, 11528.0, 11748.0, 11972.0, 12200.0, 12432.0, 12669.0, 12910.0, 13156.0 };

   // Reading Binning from config file

  // PtResponse_etaBinNumber
  const int PtResponse_etaBinNumber = std::count(CS->PtResponse_etaBinning.begin(),CS->PtResponse_etaBinning.end(),',') +1;
  double PtResponse_etaBinning[PtResponse_etaBinNumber] = {0.0};
  myTools->stringToArray(CS->PtResponse_etaBinning,PtResponse_etaBinning,",");

  // PtResponse_ptBinNumber
  const int PtResponse_ptBinNumber = std::count(CS->PtResponse_ptBinning.begin(),CS->PtResponse_ptBinning.end(),',') +1;
  double PtResponse_ptBinning[PtResponse_ptBinNumber] = {0.0};
  myTools->stringToArray(CS->PtResponse_ptBinning,PtResponse_ptBinning,",");

  // MjjResponse_etaBinNumber
  const int MjjResponse_etaBinNumber = std::count(CS->MjjResponse_etaBinning.begin(),CS->MjjResponse_etaBinning.end(),',') +1;
  double MjjResponse_etaBinning[MjjResponse_etaBinNumber] = {0.0};
  myTools->stringToArray(CS->MjjResponse_etaBinning,MjjResponse_etaBinning,",");

  // MjjResponse_mjjBinNumber
  const int MjjResponse_mjjBinNumber = std::count(CS->MjjResponse_mjjBinning.begin(),CS->MjjResponse_mjjBinning.end(),',') +1;
  double MjjResponse_mjjBinning[MjjResponse_mjjBinNumber] = {0.0};
  myTools->stringToArray(CS->MjjResponse_mjjBinning,MjjResponse_mjjBinning,",");

  // --- RESPONSE PLOTS
  if (CS->doOfflineTruthResponse){
      ptRespOffVsTruthMatrix = new ResponseMatrix("ptRespOffVsTruth", m_triggerDir + "/"+"ptRespOffVsTruth", CS);
      ptRespOffVsTruthMatrix ->BookAll(PtResponse_ptBinning, PtResponse_etaBinning, PtResponse_ptBinNumber, PtResponse_etaBinNumber, wk);
  }

  if (CS->doTriggerTruthResponse){
      ptRespTrigVsTruthMatrix = new ResponseMatrix("ptRespTrigVsTruth", m_triggerDir + "/"+"ptRespTrigVsTruth", CS);
      ptRespTrigVsTruthMatrix ->BookAll(PtResponse_ptBinning, PtResponse_etaBinning, PtResponse_ptBinNumber, PtResponse_etaBinNumber, wk);
  }

  if (CS->doTriggerOfflineResponse){
      ptRespTrigVsOffMatrix = new ResponseMatrix("ptRespTrigVsOff", m_triggerDir + "/"+"ptRespTrigVsOff", CS);
      ptRespTrigVsOffMatrix ->BookAll(PtResponse_ptBinning, PtResponse_etaBinning, PtResponse_ptBinNumber, PtResponse_etaBinNumber, wk);
  }


  if (CS->doMjjResponseOffVsTruth){
      mjjRespOffVsTruthMatrix = new ResponseMatrix("mjjRespOffVsTruth", m_triggerDir + "/"+"mjjRespOffVsTruth", CS);
      mjjRespOffVsTruthMatrix ->BookAll(MjjResponse_mjjBinning, MjjResponse_etaBinning, MjjResponse_mjjBinNumber, MjjResponse_etaBinNumber, wk);
  }

  if (CS->doMjjResponseTrigVsTruth){
      mjjRespTrigVsTruthMatrix = new ResponseMatrix("mjjRespTrigVsTruth", m_triggerDir + "/"+"mjjRespTrigVsTruth",CS);
      mjjRespTrigVsTruthMatrix ->BookAll(MjjResponse_mjjBinning, MjjResponse_etaBinning, MjjResponse_mjjBinNumber, MjjResponse_etaBinNumber, wk);
  }

  if (CS->doMjjResponseTrigVsOff){
      mjjRespTrigVsOffMatrix = new ResponseMatrix("mjjRespTrigVsOff", m_triggerDir + "/"+"mjjRespTrigVsOff", CS);
      mjjRespTrigVsOffMatrix ->BookAll(MjjResponse_mjjBinning, MjjResponse_etaBinning, MjjResponse_mjjBinNumber, MjjResponse_etaBinNumber, wk);
    }

  // --- KINEMATICS
  m_jetType.push_back("jet");
  m_jetType.push_back("trigJet");
  m_jetType.push_back("truthJet");

  for (int i=0; i<m_jetType.size(); i++){

      // check if jetType should be done
      if ((i == 0) && (!CS->doOfflineJetKinematics)) continue;
      if ((i == 1) && (!CS->doTriggerJetKinematics)) continue;
      if ((i == 2) && (!CS->doTruthJetKinematics)) continue;

      KinematicMatrix* kinematic = new KinematicMatrix(m_jetType.at(i), m_triggerDir + "/" + m_jetType.at(i) + "Kinematics", m_nthJet, CS);

      kinematic->Book("E", "E", ptFineBinNumber-1, ptFineBinning, wk); //Due to problems in the JTPPPlotter with the logscale: use ptFineBinning
      kinematic->Book("pt", "pt", ptFineBinNumber-1, ptFineBinning, wk);
      kinematic->Book("phi", "phi", 50, -3.5, 3.5, wk);
      kinematic->Book("eta", "eta", etaBinNumber-1, etaBinning, wk);
      //more observables
      if(CS->doMjj)       kinematic->Book("mjj", "mjj", mjjBinNumber-1, mjjBinning, wk);
      if(CS->doM23)       kinematic->Book("m23", "m23", mjjBinNumber-1, mjjBinning, wk);
      if(CS->doyStar)     kinematic->Book("yStar", "yStar", 20, -0.7, 0.7, wk);
      if(CS->doDeltaPhi)  kinematic->Book("deltaPhi", "deltaPhi", 25, 0.0001, 3.5, wk);
      if(CS->doPTBalance) kinematic->Book("pTBalance", "pTBalance", 25, 0.0001, 1.0, wk);
      if(CS->doHT)        kinematic->Book("HT", "HT", 50, 0.0001, 1000, wk);
      if(CS->doMHT)       kinematic->Book("MHT", "MHT", 50, 0.0001, 1000, wk);
      if(CS->doMHTPhi)    kinematic->Book("MHTPhi", "MHTPhi", 25, -3.5, 3.5, wk);
      if(CS->doEMFrac)    kinematic->Book("EMFrac", "EMFrac", 25, 0.0, 1.0, wk);
      if(CS->doHECFrac)   kinematic->Book("HECFrac", "HECFrac", 25, 0.0, 1.0, wk);
      if(CS->doFracSamplingMax) kinematic->Book("FracSamplingMax", "FracSamplingMax", 25, 0.0, 1.0, wk);


      m_kinematicMap[m_jetType.at(i)] = kinematic;
  }

}

void TriggerHistoPack::FillAll(EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet,  std::vector<int> &matchingIndexList_TriggvsOff, std::vector<int> &matchingIndexList_OffvsTruth, std::vector<int> &matchingIndexList_TriggvsTruth, double m_weight)
{
 if (m_debug) std::cout << "Starting FillAll()..." << std::endl;

  // --- 1. pt Response plots ---

  // ATTENTION: the given eta vector should be the one observable that is used for the binning!
  // i.e. option 0: eta of ProbeValue; 1: eta of RefValue


  // OfflineTruthResponse
 if (CS->doOfflineTruthResponse){
     if (m_debug) std::cout << "Starting Filling of ptRespOffVsTruth..." << std::endl;
     ptRespOffVsTruthMatrix ->Fill(ED_jet->pt, ED_truthJet->pt, ED_truthJet->eta, m_weight, 1);
  }

 if (CS->doTriggerOfflineResponse){
     if (m_debug) std::cout << "Starting Filling of ptRespTrigVsOff..." << std::endl;
     ptRespTrigVsOffMatrix ->Fill(ED_trigJet->pt, ED_jet->pt, ED_jet->eta, matchingIndexList_TriggvsOff, m_weight, 1);
  }

 if (CS->doTriggerTruthResponse){
     if (m_debug) std::cout << "Starting Filling of ptRespTrigVsTruth..." << std::endl;
     ptRespTrigVsTruthMatrix ->Fill(ED_trigJet->pt, ED_truthJet->pt, ED_truthJet->eta, matchingIndexList_TriggvsTruth, m_weight, 1);
  }

  // --- 2. mjj Response plots ---

 if (CS->doMjjResponseOffVsTruth){
     if ((matchingIndexList_OffvsTruth[0] != -1) && (matchingIndexList_OffvsTruth[1] != -1)){
        if (m_debug) std::cout << "Starting Filling of mjjRespOffVsTruth..." << std::endl;
        mjjRespOffVsTruthMatrix ->Fill(ED_jet->mjj, ED_truthJet->GetMjj(matchingIndexList_OffvsTruth[0],matchingIndexList_OffvsTruth[1]), ED_truthJet->eta->at(0), m_weight, 1);
     }
 }

 if (CS->doMjjResponseTrigVsTruth){
     if ((matchingIndexList_TriggvsTruth[0] != -1) && (matchingIndexList_TriggvsTruth[1] != -1)){
        if (m_debug) std::cout << "Starting Filling of mjjRespTrigVsTruth..." << std::endl;
        mjjRespTrigVsTruthMatrix ->Fill(ED_trigJet->mjj, ED_truthJet->GetMjj(matchingIndexList_TriggvsTruth[0],matchingIndexList_TriggvsTruth[1]), ED_truthJet->eta->at(0), m_weight, 1);
     }
 }

 if (CS->doMjjResponseTrigVsOff){
     if ((matchingIndexList_TriggvsOff[0] != -1) && (matchingIndexList_TriggvsOff[1] != -1)){
        if (m_debug) std::cout << "Starting Filling of mjjRespTrigVsOff..." << std::endl;
        mjjRespTrigVsOffMatrix ->Fill(ED_trigJet->mjj, ED_jet->GetMjj(matchingIndexList_TriggvsOff[0],matchingIndexList_TriggvsOff[1]), ED_jet->eta->at(0), m_weight, 1);
     }
 }

 // --- 3. Kinematic plots ---

 // Fill all offline Kinematics
 if (CS->doOfflineJetKinematics){
     if (m_debug) std::cout << "Starting Filling Kinematics jet..." << std::endl;
     //Fill all with considering Cleaning
     m_kinematicMap[m_jetType.at(0)]->FillAll(ED_jet, m_weight);
 }

 // Fill all trigger jets Kinematics
 if (CS->doTriggerJetKinematics){
     if (m_debug) std::cout << "Starting Filling Kinematics trigJet..." << std::endl;
     //Fill all with considering Cleaning
     m_kinematicMap[m_jetType.at(1)]->FillAll(ED_trigJet, m_weight);
 }

 // Fill all truth jets Kinematics
 if (CS->doTruthJetKinematics){
     if (m_debug) std::cout << "Starting Filling Kinematics truthJet..." << std::endl;
     m_kinematicMap[m_jetType.at(2)]->FillAll(ED_truthJet, m_weight);
 }

}
