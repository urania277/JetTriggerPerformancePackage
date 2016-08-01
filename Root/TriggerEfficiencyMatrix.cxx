/*--------------------------------------------------------------------
TriggerEfficiencyMatrix.cxx

In TriggerEfficiencyMatrix the turnons plots are created and stored.
Also the methods for the turnon specific event selection can be found here.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/TriggerEfficiencyMatrix.h>
#include <JetTriggerPerformancePackage/ToolsJTPP.h>
#include <iostream>
#include <assert.h>



TriggerEfficiencyMatrix::TriggerEfficiencyMatrix(std::string key, std::string directory, ConfigStatus* a_CS):
    m_key(key), HistogramMatrix(directory, a_CS)
{
    if (m_debug) std::cout << "Starting constructor TriggerEfficiencyMatrix()..." << std::endl;

    tools = new ToolsJTPP();
    cutHandler = new CutHandler();
}

TriggerEfficiencyMatrix::~TriggerEfficiencyMatrix()
{
  if (m_debug) std::cout << "Starting destructor TriggerEfficiencyMatrix()..." << std::endl;
}

void TriggerEfficiencyMatrix::BookAll(TriggerData* TD, ConfigStatus* CS, EL::Worker* wk)
{
    if (m_debug) std::cout << "Starting Book()..." << std::endl;

    // Book Denominator (= Denumerator xD) plots
    for (unsigned int n=0; n < TD->refTriggers.size(); n++){

	    if (CS->useTriggerDecisionTool){
		std::string name = m_raw + "_" + m_TDT + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
		this->Book(name, name, 1200, 0.0, 1200.0, wk); // book its corresponding histogram here...
	    }

	    if (CS->useEmulation){
		std::string name = m_raw + "_" + m_Emu + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
		this->Book(name, name, 1200, 0.0, 1200.0, wk); // book its corresponding histogram here...
	    }

	    if (CS->useTriggerBeforePraescale){
		std::string name = m_raw + "_" + m_TBP + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
		this->Book(name, name, 1200, 0.0, 1200.0, wk); // book its corresponding histogram here...
	    }
    }

    // Book actual turnon plots
    for (unsigned int n=0; n < TD->probeTriggers.size(); n++){

	if (CS->useTriggerDecisionTool){
	    std::string name = m_pt + "_" + m_TDT + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
	    this->Book(name, name, 1200, 0.0, 1200.0, wk); // book its corresponding histogram here...
	}

	if (CS->useEmulation){
	    std::string name = m_pt + "_" + m_Emu + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
	    this->Book(name, name, 1200, 0.0, 1200.0, wk); // book its corresponding histogram here...
	}

	if (CS->useTriggerBeforePraescale){
	    std::string name = m_pt + "_" + m_TBP + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
	    this->Book(name, name, 1200, 0.0, 1200.0, wk); // book its corresponding histogram here...
	}

    }

    // book Crosschecks histos
    this->Book("notInTLATrigger_lead_jet_eta", "notInTLATrigger_lead_jet_eta", 20, -4.9, 4.9, wk);
    this->Book("notInTLATrigger_sublead_jet_eta", "notInTLATrigger_sublead_jet_eta", 20, -4.9, 4.9, wk);

    this->Book("notInTLATrigger_lead_trigJet_eta", "notInTLATrigger_lead_trigJet_eta", 20, -4.9, 4.9, wk);
    this->Book("notInTLATrigger_sublead_trigJet_eta", "notInTLATrigger_sublead_trigJet_eta", 20, -4.9, 4.9, wk);

    this->Book("notInTLATrigger_lead_jet_phi", "notInTLATrigger_lead_jet_phi", 50, -3.5, 3.5, wk);
    this->Book("notInTLATrigger_sublead_jet_phi", "notInTLATrigger_sublead_jet_phi", 50, -3.5, 3.5, wk);

    this->Book("notInTLATrigger_lead_trigJet_phi", "notInTLATrigger_lead_trigJet_phi", 50, -3.5, 3.5, wk);
    this->Book("notInTLATrigger_sublead_trigJet_phi", "notInTLATrigger_sublead_trigJet_phi", 50, -3.5, 3.5, wk);

    this->Book("notInTLATrigger_jet_mjj", "notInTLATrigger_jet_mjj", 300, 0.0, 1200.0, wk);

    this->Book("notInTLATrigger_trigJet_mjj", "notInTLATrigger_trigJet_mjj", 300, 0.0, 1200.0, wk);

    this->Book("notInTLATrigger_jet_m23", "notInTLATrigger_jet_m23", 300, 0.0, 1200.0, wk);

    this->Book("notInTLATrigger_trigJet_m23", "notInTLATrigger_trigJet_m23", 300, 0.0, 1200.0, wk);



    // initialise dummy counter
    dummy_counter = 0;

}

void TriggerEfficiencyMatrix::Book(std::string name1, std::string name2, int nBins, double xMin, double xMax, EL::Worker* wk)
{
  if (m_debug) std::cout << "Starting Book()..." << std::endl;
  HistogramMatrix::Book(m_key + "_" + name1, m_key + "_" + name2, nBins, xMin, xMax,  wk);
}

void TriggerEfficiencyMatrix::Book(std::string name1, std::string name2, int nBins, double* xBinning, EL::Worker* wk)
{
  if (m_debug) std::cout << "Starting Book()..." << std::endl;
  HistogramMatrix::Book(m_key + "_" + name1, m_key + "_" + name2, nBins, xBinning , wk);
}

void TriggerEfficiencyMatrix::FillAll(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, L1Data* L1D, double weight, ConfigStatus* CS)
{
    if (m_debug) std::cout << "Starting FillAll()..." << std::endl;

    //TDT
    if (CS->useTriggerDecisionTool){
	this->FillUsingTDT(TD, ED_jet, ED_trigJet, weight, CS);
    }

    //Emu
    if (CS->useEmulation){
	this->FillUsingEmu(TD, ED_jet, ED_trigJet, L1D, weight, CS);
    }

    //TBP
    if (CS->useTriggerBeforePraescale){
	//	this->FillUsingTBP();
    }

}

void TriggerEfficiencyMatrix::FillUsingTDT(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, double weight, ConfigStatus* CS)
{
    if (m_debug) std::cout << "Starting FillUsingTDT()..." << std::endl;

    int nthJetAfterCutsProbe, nthJetAfterCutsRef;
    float ptNthJetAfterCutsProbe;

    for (unsigned int n=0; n < TD->probeTriggers.size(); n++){

	//TODO uncomment again	if (!TD->boolRefTriggers.at(n)) continue; //speed things up

	// 1. Get nthJetAfterCuts and the corresponding pt value
	nthJetAfterCutsProbe = this->nthJetAfterCuts(TD, TD->nthJetProbe.at(n), TD->etaMinProbeTrigger.at(n), TD->etaMaxProbeTrigger.at(n), ED_jet);

	if (nthJetAfterCutsProbe == 0) continue; // continue if no proper jet was found
	ptNthJetAfterCutsProbe = ED_jet->pt->at(nthJetAfterCutsProbe-1);

	// TODO cout for crosscheck
	//	if ((TD->boolRefTriggers.at(n)) && ((ED_jet->mjj > 600.0) || (ED_jet->m23 > 600.0))) {
	// if probe trigger is HLT j0 0i1c500m900TLA, it did not fire, but L1_J100 fired and the trigger jet mjj value is in between 500 and 900, then:
	if ((n == 1) && (TD->boolProbeTriggers.at(n) == 0)  && (TD->boolRefTriggers.at(n) == 1) && (ED_trigJet->mjj > 500.0) && (ED_trigJet->mjj < 900.0)) {
	    //std::cout << "==============================" << std::endl;
	    //std::cout << "ptThresholdProbeTrigger.at(n): " << TD->ptThresholdProbeTrigger.at(n) << std::endl;
	    //std::cout << "probeTriggers.at(n): " << TD->probeTriggers.at(n) << std::endl;

	    //std::cout << "TD->boolProbeTriggers.at(n): " << TD->boolProbeTriggers.at(n) << std::endl;
	    //std::cout << "TD->boolRefTriggers.at(n): " << TD->boolRefTriggers.at(n) << std::endl;

	    //std::cout << "ED_jet->eta->at(0): " << ED_jet->eta->at(0) << std::endl;
	    this->Fill("notInTLATrigger_lead_jet_eta", ED_jet->eta->at(0), true, weight);
	    //std::cout << "ED_jet->eta->at(1): " << ED_jet->eta->at(1) << std::endl;
	    this->Fill("notInTLATrigger_sublead_jet_eta",  ED_jet->eta->at(1), true, weight);

	    //std::cout << "ED_trigJet->eta->at(0): " << ED_trigJet->eta->at(0) << std::endl;
	    this->Fill("notInTLATrigger_lead_trigJet_eta",  ED_trigJet->eta->at(0), true, weight);
	    //std::cout << "ED_trigJet->eta->at(1): " << ED_trigJet->eta->at(1) << std::endl;
	    this->Fill("notInTLATrigger_sublead_trigJet_eta",  ED_trigJet->eta->at(1), true, weight);

	    //std::cout << "ED_jet->phi->at(0): " << ED_jet->phi->at(0) << std::endl;
	    this->Fill("notInTLATrigger_lead_jet_phi",  ED_jet->phi->at(0), true, weight);
	    //std::cout << "ED_jet->phi->at(1): " << ED_jet->phi->at(1) << std::endl;
	    this->Fill("notInTLATrigger_sublead_jet_phi",  ED_jet->phi->at(1), true, weight);

	    //std::cout << "ED_trigJet->phi->at(0): " << ED_trigJet->phi->at(0) << std::endl;
	    this->Fill("notInTLATrigger_lead_trigJet_phi",  ED_trigJet->phi->at(0), true, weight);
	    //std::cout << "ED_trigJet->phi->at(1): " << ED_trigJet->phi->at(1) << std::endl;
	    this->Fill("notInTLATrigger_sublead_trigJet_phi",  ED_trigJet->phi->at(1), true, weight);

	    //std::cout << "ED_jet->mjj: " << ED_jet->mjj << std::endl;
	    this->Fill("notInTLATrigger_jet_mjj",  ED_jet->mjj, true, weight);
	    //std::cout << "ED_jet->m23: " << ED_jet->m23 << std::endl;
	    this->Fill("notInTLATrigger_jet_m23",  ED_jet->m23, true, weight);

	    //std::cout << "ED_trigJet->mjj: " << ED_trigJet->mjj << std::endl;
	    this->Fill("notInTLATrigger_trigJet_mjj",  ED_trigJet->mjj, true, weight);
	    //std::cout << "ED_trigJet->m23: " << ED_trigJet->m23 << std::endl;
	    this->Fill("notInTLATrigger_trigJet_m23",  ED_trigJet->m23, true, weight);

	    //std::cout << "ED_jet->yStar: " << ED_jet->yStar << std::endl;
	    //std::cout << "ED_trigJet->yStar: " << ED_trigJet->yStar << std::endl;
	}

	// TODO little hack for TLA triggers
	// set bool true if you want to fill mjj instead of the nth jet pt
	bool makeMjjPlots = false;
	if (makeMjjPlots){
	    // if HLT-j0-1i2c200m8000TLA, use offline m23
	    if (TD->probeTriggers.at(n).compare("HLT_j0_1i2c200m8000TLA") == 0)  ptNthJetAfterCutsProbe = ED_jet->m23;

	    // if HLT-j0-0i1c500m900TLA, use offline mjj
	    if (TD->probeTriggers.at(n).compare("HLT_j0_0i1c500m900TLA") == 0) ptNthJetAfterCutsProbe = ED_jet->mjj;
	}

	// 2. Check if ref trigger fired and fill Denumerator
	if (TD->boolRefTriggers.at(n)){
	    this->Fill(m_raw + "_" + m_TDT + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n), ptNthJetAfterCutsProbe , true, weight);
	}

	// 3. Check if probe and ref trigger fired and fill numerator
	if ((TD->boolProbeTriggers.at(n))&&(TD->boolRefTriggers.at(n))){
	    this->Fill(m_pt + "_" + m_TDT + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n), ptNthJetAfterCutsProbe , true, weight);
	}

    }
}

void TriggerEfficiencyMatrix::FillUsingEmu(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, L1Data* L1D, double weight, ConfigStatus* CS)
{
    if (m_debug) std::cout << "Starting FillUsingEmu()..." << std::endl;

    int nthJetAfterCutsProbe, nthJetAfterCutsRef;
    float ptNthJetAfterCutsProbe;

    // CROSSCHECK
    int ptThr;

    for (unsigned int n=0; n < TD->probeTriggers.size(); n++){
	if (!TD->boolRefTriggers.at(n)) continue; //speed things up

	// CROSSCHECK
	ptThr = TD->ptThresholdProbeTrigger.at(n);

	// 1. Get nthJetAfterCuts and the corresponding pt value
	//nthJetAfterCutsProbe = this->nthJetAfterCutsChristiansVersion(TD, TD->nthJetProbe.at(n), TD->etaMinProbeTrigger.at(n), TD->etaMaxProbeTrigger.at(n), ED_jet);
	nthJetAfterCutsProbe = this->nthJetAfterCuts(TD, TD->nthJetProbe.at(n), TD->etaMinProbeTrigger.at(n), TD->etaMaxProbeTrigger.at(n), ED_jet);

	// continue if no proper jet was found
	if (nthJetAfterCutsProbe == 0) continue;

	// get pt value to corresponding nth Jet
	ptNthJetAfterCutsProbe = ED_jet->pt->at(nthJetAfterCutsProbe-1);

	// 2. Check if ref trigger fired (in TDT) and fill Denumerator
	if (TD->boolRefTriggers.at(n)){
	    this->Fill(m_raw + "_" + m_Emu + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n), ptNthJetAfterCutsProbe , true, weight);
	}

	// 3. Check if probe and ref trigger fired and fill numerator
	// Important: we check TDT for ref trigger and emulation for ref and probe trigger
	if ((this->passedEmulation(TD->isL1Probe.at(n), TD->nthJetProbe.at(n), TD->ptThresholdProbeTrigger.at(n), TD->etaMinProbeTrigger.at(n),
				   TD->etaMaxProbeTrigger.at(n), ED_trigJet, L1D))
	    && (TD->boolRefTriggers.at(n))){
	    this->Fill(m_pt + "_" + m_Emu + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n), ptNthJetAfterCutsProbe , true, weight);
	}
    }

}

void TriggerEfficiencyMatrix::FillUsingTBP()
{
    if (m_debug) std::cout << "Starting FillUsingTBP()..." << std::endl;

    // TODO UNDER CONSTRUCTION
}

void  TriggerEfficiencyMatrix::Fill(std::string obs, double value, bool isGood, double weight)
{
  if (m_debug) std::cout << "Starting Fill()..." << std::endl;
  HistogramMatrix::Fill(m_key + "_" + obs, value, isGood , weight);
}

void  TriggerEfficiencyMatrix::Fill(std::string obs, int value, bool isGood, double weight)
{
  if (m_debug) std::cout << "Starting Fill()..." << std::endl;
  HistogramMatrix::Fill(m_key + "_" + obs, value, isGood , weight);
}

void  TriggerEfficiencyMatrix::Fill(std::string obs, std::vector<float>* valueVector, std::vector<bool>* isGood, double weight)
{
  if (m_debug) std::cout << "Starting Fill()..." << std::endl;
  HistogramMatrix::Fill(m_key + "_" + obs, valueVector, isGood, weight);
  }

void  TriggerEfficiencyMatrix::DivideEfficiencyPlots(TriggerData* TD, ConfigStatus* CS)
{
    if (m_debug) std::cout << "Starting CreateEfficiencyPlots()..." << std::endl;

    if (CS->useTriggerDecisionTool){
	for (unsigned int n=0; n < TD->refTriggers.size(); n++){
	    std::string turnOnName = m_key + "_" + m_pt + "_" + m_TDT + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
	    std::string refName = m_key + "_" + m_raw + "_" + m_TDT + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
	    //	    m_map[turnOnName]->Sumw2();
	    //	    m_map[turnOnName]->Divide(m_map[turnOnName],m_map[refName], 1.0, 1.0 , "B"); //binominal errors
	}
    }

    if (CS->useEmulation){
	for (unsigned int n=0; n < TD->refTriggers.size(); n++){
	    std::string turnOnName = m_key + "_" + m_pt + "_" + m_Emu + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
	    std::string refName = m_key + "_" + m_raw + "_" + m_Emu + "_" + TD->probeTriggers.at(n) + "-" + TD->refTriggers.at(n);
	    //	    m_map[turnOnName]->Sumw2();
	    //	    m_map[turnOnName]->Divide(m_map[turnOnName],m_map[refName], 1.0, 1.0 , "B"); //binominal errors
	}
    }

    std::cout << "final dummy_counter result: " << dummy_counter << std::endl;
}

// Returns number of nth jet after the wished cuts, if value is 0, no nth jet exists
int TriggerEfficiencyMatrix::nthJetAfterCuts(TriggerData* TD, int nthJet, float etaMin, float etaMax, EventData* ED)
{
    if (m_debug) std::cout << "Starting nthJetAfterCuts()..." << std::endl;

    int passedJets = 0;
    int posLastPassedJet = 0;

    for (unsigned int n=0; n < ED->eta->size(); n++){


	// Reset CutHandler for every jet
	cutHandler->Reset();

	// Apply cuts
	cutHandler->AddCut(ED->eta->at(n), etaMin, "absmin");
	cutHandler->AddCut(ED->eta->at(n), etaMax, "absmax");
	cutHandler->AddCut(ED->Timing->at(n), 10.0, "absmax");

	// Isolation for multijets only
	if (nthJet > 1) cutHandler->CheckIsolation(n, ED, 0.6, 20);

	// check if jet passed cuts
	if (cutHandler->passedCuts()){
	    passedJets++;
	    posLastPassedJet = n+1;
	}

	// check if nthJetAfterCuts was found
	if (passedJets == nthJet)  return posLastPassedJet;
    }

    //    if (nthJet > 0) std::cout << "return 0: " << std::endl;
    return 0;

}

int TriggerEfficiencyMatrix::nthJetAfterCutsTLA(TriggerData* TD, int nthJet, float etaMin, float etaMax, EventData* ED)
{
    if (m_debug) std::cout << "Starting nthJetAfterCuts()..." << std::endl;

    int passedJets = 0;
    int posLastPassedJet = 0;

    for (unsigned int n=0; n < ED->eta->size(); n++){


	// Reset CutHandler for every jet
	cutHandler->Reset();

	// Apply cuts
	cutHandler->AddCut(ED->eta->at(n), etaMin, "absmin");
	cutHandler->AddCut(ED->eta->at(n), etaMax, "absmax");
	cutHandler->AddCut(ED->Timing->at(n), 10.0, "absmax");

	//Additional cut for TLA triggers: |yStar| < 0.6
	cutHandler->AddCut(ED->yStar, 0.6, "absmax");

	// Isolation for multijets only
	if (nthJet > 1) cutHandler->CheckIsolation(n, ED, 0.6, 20);

	// check if jet passed cuts
	if (cutHandler->passedCuts()){
	    passedJets++;
	    posLastPassedJet = n+1;
	}

	// check if nthJetAfterCuts was found
	if (passedJets == nthJet)  return posLastPassedJet;
    }

    //    if (nthJet > 0) std::cout << "return 0: " << std::endl;
    return 0;

}

int TriggerEfficiencyMatrix::nthJetAfterCutsChristiansVersion(TriggerData* TD, int nthJet, float etaMin, float etaMax, EventData* ED)
{
    if (m_debug) std::cout << "Starting nthJetAfterCutsChristiansVersion()..." << std::endl;

    int passedJets = 0;
    int posLastPassedJet = 0;

    for (unsigned int n=0; n < ED->eta->size(); n++){


	///// Cut 1: eta cut to simulate Christian's CentralJets
	// Reset CutHandler for every jet
	cutHandler->Reset();

	// Apply cuts
	cutHandler->AddCut(ED->eta->at(n), etaMin, "absmin");
	cutHandler->AddCut(ED->eta->at(n), etaMax, "absmax");


	// check if jet passed cuts
	if (cutHandler->passedCuts()){

	    ///// Cut 2: timing cut
	    cutHandler->Reset();
	    cutHandler->AddCut(ED->Timing->at(n), 10.0, "absmax");

	    if (cutHandler->passedCuts()){
		posLastPassedJet = n+1;
		return posLastPassedJet;
	    } else { dummy_counter++; return 0;}
	}

    }

    //    if (nthJet > 0) std::cout << "return 0: " << std::endl;
    return 0;

}

bool TriggerEfficiencyMatrix::passedEmulation(bool isL1, int nthJet, float ptThreshold, float etaMin, float etaMax, EventData* ED_trigJet, L1Data* L1D)
{
    if (m_debug) std::cout << "Starting passedEmulation()..." << std::endl;


    // use L1D for L1 triggers and ED_trigJet for HLT jets
    float jetEta, jetEt;
    int jetSize;
    if (isL1) jetSize = L1D->eta->size();
    else jetSize = ED_trigJet->eta->size();

    float modifiedEtaMin, modifiedEtaMax;
    int passedJets = 0;
    int posLastPassedJet = 0;

    // fill modifiedEtaMin and modifiedEtaMax (Bad Coding, need changing) TODO!!!
    if (isL1){
	if (etaMax <= 3.5) { // L1 central jet region
	    modifiedEtaMin = 0.0;
	    modifiedEtaMax = 3.1;
	} else {
	    modifiedEtaMin = 3.2;
	    modifiedEtaMax = 4.9;
	}
    } else {
	if (etaMax <= 3.5) { // HLT central jet region
	    modifiedEtaMin = 0.0;
	    modifiedEtaMax = 3.2;
	} else {
	    modifiedEtaMin = 3.2;
	    modifiedEtaMax = 4.9;
	}
    }

    for (unsigned int n=0; n < jetSize; n++){

	// use L1 jets or HLT jets
	if (isL1){
	    jetEta = L1D->eta->at(n);
	    jetEt = L1D->pt.at(n);
	} else {
	    jetEta = ED_trigJet->eta->at(n);
	    jetEt = ED_trigJet->GetEt(n);
	}

	// Reset CutHandler for every jet
	cutHandler->Reset();

	// Apply cuts
	cutHandler->AddCut(jetEta, modifiedEtaMin, "absmin");
	cutHandler->AddCut(jetEta, modifiedEtaMax, "absmax");

	//pt Threshold, using L1D for L1 triggers and ED_trigJet for HLT jets
	cutHandler->AddCut(jetEt, ptThreshold, "mineq");

	// check if jet passed cuts
	if (cutHandler->passedCuts()){
	    passedJets++;
	    posLastPassedJet = n+1;
	}

	// check if nthJetAfterCuts was found
	if (passedJets == nthJet) {return true;}
    }

    return false;
}

int TriggerEfficiencyMatrix::nthJetAfterCutsEmu()
{
    if (m_debug) std::cout << "Starting ApplyCutsEmu()..." << std::endl;

    // TODO UNDER CONSTRUCTION
    return true;
}

int TriggerEfficiencyMatrix::nthJetAfterCutsTBP()
{
    if (m_debug) std::cout << "Starting ApplyCutsTBP()..." << std::endl;

    // TODO UNDER CONSTRUCTION
    return true;
}
