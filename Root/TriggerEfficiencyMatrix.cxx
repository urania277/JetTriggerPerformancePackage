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
    m_key(key), HistogramMatrix(directory, false, false), // "false" booleans deactivate options for LeadSubleadThird and NthJet plots which are not needed for Turnons in general
    CS(a_CS),
    // eta values for the emulation of turnons
     calo_HLT_cen_etaMin(0.0),
     calo_HLT_cen_etaMax(3.2),
     calo_HLT_fwd_etaMin(3.2),
     calo_HLT_fwd_etaMax(100.0),
     calo_L1_cen_etaMin(0.0),
     calo_L1_cen_etaMax(3.1),
     calo_L1_fwd_etaMin(3.1),
     calo_L1_fwd_etaMax(100.0)
{
    if (m_debug) std::cout << "Starting constructor TriggerEfficiencyMatrix()..." << std::endl;

    tools = new ToolsJTPP();

    // Defining cutHandler
    std::cout << "\n==== Turnon Cut Selection ====" << std::endl;
    cutHandler = new CutHandler(CS->cutStringTurnons);

    // Defining GraphMatrix
    graphMatrix = new GraphMatrix(directory);
}

TriggerEfficiencyMatrix::~TriggerEfficiencyMatrix()
{
  if (m_debug) std::cout << "Starting destructor TriggerEfficiencyMatrix()..." << std::endl;
}

void TriggerEfficiencyMatrix::BookAll(TriggerData* TD, ConfigStatus* CS, EL::Worker* wk)
{
    if (m_debug) std::cout << "Starting Book()..." << std::endl;

    // Determine m_xAxix, i.e. the plotted variable (differs for pt or ht triggers)
    for (unsigned int n=0; n < TD->probe_triggerName.size(); n++){
        if (TD->probe_isHT.at(n)){
            m_xAxis.push_back("ht");
            m_BinNumber.push_back(CS->HtTurnon_BinNumbers);
            m_BinMax.push_back(CS->HtTurnon_MaxBin);
            m_BinMin.push_back(CS->HtTurnon_MinBin);
        }
        else{
            m_xAxis.push_back("pt");
            m_BinNumber.push_back(CS->PtTurnon_BinNumbers);
            m_BinMax.push_back(CS->PtTurnon_MaxBin);
            m_BinMin.push_back(CS->PtTurnon_MinBin);
        }
    }

    // Book Denominator plots
    for (unsigned int n=0; n < TD->ref_triggerName.size(); n++){

	    if (CS->useTriggerDecisionTool){
        std::string name = m_xAxis.at(n) + "_" + m_denom + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
	    }

	    if (CS->useEmulation){
        std::string name = m_xAxis.at(n) + "_" + m_denom + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
        }

	    if (CS->useTriggerBeforePraescale){
        std::string name = m_xAxis.at(n) + "_" + m_denom + "_" + m_TBP + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
        }
    }

    // Book nominator turnon plots
    for (unsigned int n=0; n < TD->probe_triggerName.size(); n++){

	if (CS->useTriggerDecisionTool){
        std::string name = m_xAxis.at(n) + "_" + m_nom + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
    }

	if (CS->useEmulation){
        std::string name = m_xAxis.at(n) + "_" + m_nom + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
    }

	if (CS->useTriggerBeforePraescale){
        std::string name = m_xAxis.at(n) + "_" + m_nom + "_" + m_TBP + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
    }

    }

    // Book divided turnon plots
    for (unsigned int n=0; n < TD->probe_triggerName.size(); n++){

    if (CS->useTriggerDecisionTool){
        std::string name = m_xAxis.at(n) + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
    }

    if (CS->useEmulation){
        std::string name = m_xAxis.at(n) + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
    }

    if (CS->useTriggerBeforePraescale){
        std::string name = m_xAxis.at(n) + "_" + m_TBP + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
        this->Book(name, name, m_BinNumber.at(n), m_BinMin.at(n), m_BinMax.at(n), wk); // book its corresponding histogram here...
    }

    }

    std::cout << "=== All Bookings ===" << std::endl;
    this->coutAllBookings();
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

void TriggerEfficiencyMatrix::FillAll(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet, L1Data* L1D, double weight, ConfigStatus* CS)
{
    if (m_debug) std::cout << "Starting FillAll()..." << std::endl;

    //TDT
    if (CS->useTriggerDecisionTool){
    this->FillUsingTDT(TD, ED_jet, ED_trigJet, ED_truthJet, weight, CS);
    }

    //Emu
    if (CS->useEmulation){
    this->FillUsingEmu(TD, ED_jet, ED_trigJet,ED_truthJet, L1D, weight, CS);
    }

    //TBP
    if (CS->useTriggerBeforePraescale){
	//	this->FillUsingTBP();
    }

}

void TriggerEfficiencyMatrix::FillUsingTDT(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet, double weight, ConfigStatus* CS)
{
    if (m_debug) std::cout << "Starting FillUsingTDT()..." << std::endl;

    int nthJetAfterCutsProbe, nthJetAfterCutsRef;
    float ptNthJetAfterCutsProbe;

    for (unsigned int n=0; n < TD->probe_triggerName.size(); n++){

    // 0. Check if trigger is HT trigger
    if (TD->probe_isHT.at(n)) this->FillUsingTDT_ht(n, TD, ED_jet, ED_trigJet, ED_truthJet, weight, CS);

    // otherwise continue with default turnons
    else {

        // 1. Get nthJetAfterCuts and the corresponding pt value
        nthJetAfterCutsProbe = this->nthJetAfterCuts(TD, TD->probe_nthJet.at(n), TD->probe_etaMin.at(n), TD->probe_etaMax.at(n), ED_jet, ED_trigJet, ED_truthJet);

        if (nthJetAfterCutsProbe == 0) continue; // continue if no proper jet was found
        ptNthJetAfterCutsProbe = ED_jet->pt->at(nthJetAfterCutsProbe-1);

        // 2. Check if ref trigger fired and fill denominator
        if (TD->ref_passedTrigger.at(n)){
            this->Fill(m_xAxis.at(n) + "_" + m_denom + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n), ptNthJetAfterCutsProbe , true, weight);
        }

        // 3. Check if probe and ref trigger fired and fill nominator
        if ((TD->probe_passedTrigger.at(n))&&(TD->ref_passedTrigger.at(n))){
            this->Fill(m_xAxis.at(n) + "_" + m_nom + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n), ptNthJetAfterCutsProbe , true, weight);
            this->Fill(m_xAxis.at(n) + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n), ptNthJetAfterCutsProbe , true, weight);
        }
    }

    }
}

void TriggerEfficiencyMatrix::FillUsingTDT_ht(int pos, TriggerData *TD, EventData *ED_jet, EventData *ED_trigJet, EventData *ED_truthJet, double weight, ConfigStatus *CS)
{
    if (m_debug) std::cout << "Starting FillUsingTDT_ht()..." << std::endl;

    // 1. Event Selection

    // 2. Check if ref trigger fired and fill denominator
    if (TD->ref_passedTrigger.at(pos)){
        this->Fill(m_xAxis.at(pos) + "_" + m_denom + "_" + m_TDT + "_" + TD->probe_triggerName.at(pos) + "-" + TD->ref_triggerName.at(pos), ED_jet->GetHT(), true, weight);
    }

    // 3. Check if probe and ref trigger fired and fill nominator
    if ((TD->probe_passedTrigger.at(pos))&&(TD->ref_passedTrigger.at(pos))){

        this->Fill(m_xAxis.at(pos) + "_" + m_nom + "_" + m_TDT + "_" + TD->probe_triggerName.at(pos) + "-" + TD->ref_triggerName.at(pos), ED_jet->GetHT() , true, weight);
        this->Fill(m_xAxis.at(pos) + "_" + m_TDT + "_" + TD->probe_triggerName.at(pos) + "-" + TD->ref_triggerName.at(pos), ED_jet->GetHT() , true, weight);
    }
}

void TriggerEfficiencyMatrix::FillUsingEmu(TriggerData* TD, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet, L1Data* L1D, double weight, ConfigStatus* CS)
{
    if (m_debug) std::cout << "Starting FillUsingEmu()..." << std::endl;

    int nthJetAfterCutsProbe, nthJetAfterCutsRef;
    float ptNthJetAfterCutsProbe;

    for (unsigned int n=0; n < TD->probe_triggerName.size(); n++){
    if (!TD->ref_passedTrigger.at(n)) continue; //speed things up

    // 0. Check if trigger is HT trigger
    if (TD->probe_isHT.at(n)) this->FillUsingEmu_ht(n, TD, ED_jet, ED_trigJet, ED_truthJet, weight, CS);

    // otherwise continue with default turnons
    else {

        // 1. Get nthJetAfterCuts and the corresponding pt value
        //nthJetAfterCutsProbe = this->nthJetAfterCutsChristiansVersion(TD, TD->probe_nthJet.at(n), TD->probe_etaMin.at(n), TD->probe_etaMax.at(n), ED_jet);
        nthJetAfterCutsProbe = this->nthJetAfterCuts(TD, TD->probe_nthJet.at(n), TD->probe_etaMin.at(n), TD->probe_etaMax.at(n), ED_jet, ED_trigJet, ED_truthJet);

        // continue if no proper jet was found
        if (nthJetAfterCutsProbe == 0) continue;

        // get pt value to corresponding nth Jet
        ptNthJetAfterCutsProbe = ED_jet->pt->at(nthJetAfterCutsProbe-1);

        // 2. Check if ref trigger fired (in TDT) and fill Denumerator
        if (TD->ref_passedTrigger.at(n)){
            this->Fill(m_xAxis.at(n) + "_" + m_denom + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n), ptNthJetAfterCutsProbe , true, weight);
        }

        // 3. Check if probe and ref trigger fired and fill numerator
        // Important: we check TDT for ref trigger and emulation for ref and probe trigger
        if ((this->passedEmulation(TD->probe_isL1.at(n), TD->probe_nthJet.at(n), TD->probe_ptThreshold.at(n), TD->probe_etaMin.at(n),
                   TD->probe_etaMax.at(n), ED_trigJet, L1D))
            && (TD->ref_passedTrigger.at(n))){
                this->Fill(m_xAxis.at(n) + "_" + m_nom + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n), ptNthJetAfterCutsProbe , true, weight);
                this->Fill(m_xAxis.at(n) + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n), ptNthJetAfterCutsProbe , true, weight);
        }
    }
    }

}

void TriggerEfficiencyMatrix::FillUsingEmu_ht(int pos, TriggerData *TD, EventData *ED_jet, EventData *ED_trigJet, EventData *ED_truthJet, double weight, ConfigStatus *CS)
{
    if (m_debug) std::cout << "Starting FillUsingEmu_ht()..." << std::endl;

    // 1. Event Selection

    // 2. Check if ref trigger fired and fill denominator
    if (TD->ref_passedTrigger.at(pos)){
        this->Fill(m_xAxis.at(pos) + "_" + m_denom + "_" + m_Emu + "_" + TD->probe_triggerName.at(pos) + "-" + TD->ref_triggerName.at(pos), ED_jet->GetHT(), true, weight);
    }

    // 3. Check if probe and ref trigger fired and fill nominator
    if ((this->passedEmulationOfHtTrigger(TD->probe_HTThreshold.at(pos),ED_trigJet))&&(TD->ref_passedTrigger.at(pos))){

        this->Fill(m_xAxis.at(pos) + "_" + m_nom + "_" + m_Emu + "_" + TD->probe_triggerName.at(pos) + "-" + TD->ref_triggerName.at(pos), ED_jet->GetHT() , true, weight);
        this->Fill(m_xAxis.at(pos) + "_" + m_Emu + "_" + TD->probe_triggerName.at(pos) + "-" + TD->ref_triggerName.at(pos), ED_jet->GetHT() , true, weight);
    }
}

void TriggerEfficiencyMatrix::FillUsingTBP()
{
    if (m_debug) std::cout << "Starting FillUsingTBP()..." << std::endl;

    // TODO UNDER CONSTRUCTION
}

void TriggerEfficiencyMatrix::FillUsingTBP_ht()
{
    if (m_debug) std::cout << "Starting FillUsingTBP_ht()..." << std::endl;
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

void  TriggerEfficiencyMatrix::DivideEfficiencyPlots(TriggerData* TD, ConfigStatus* CS, EL::Worker* wk)
{
    if (m_debug) std::cout << "Starting CreateEfficiencyPlots()..." << std::endl;

    if (CS->useTriggerDecisionTool){
        for (unsigned int n=0; n < TD->ref_triggerName.size(); n++){
            std::string turnOnName = m_key + "_" + m_xAxis.at(n) + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
            std::string nomName = m_key + "_" + m_xAxis.at(n) + "_" + m_nom + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
            std::string denomName = m_key + "_" + m_xAxis.at(n) + "_" + m_denom + "_" + m_TDT + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);

            m_map[turnOnName]->Sumw2();
            m_map[turnOnName]->Divide(m_map[denomName]);

        }
    }

    if (CS->useEmulation){
        for (unsigned int n=0; n < TD->ref_triggerName.size(); n++){
            std::string turnOnName = m_key + "_" + m_xAxis.at(n) + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
            std::string nomName = m_key + "_" + m_xAxis.at(n) + "_" + m_nom + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);
            std::string denomName = m_key + "_" + m_xAxis.at(n) + "_" + m_denom + "_" + m_Emu + "_" + TD->probe_triggerName.at(n) + "-" + TD->ref_triggerName.at(n);

            m_map[turnOnName]->Sumw2();
            m_map[turnOnName]->Divide(m_map[denomName]);
        }
    }

    std::cout << "final dummy_counter result: " << dummy_counter << std::endl;
}

// Returns number of nth jet after the wished cuts, if value is 0, no nth jet exists
int TriggerEfficiencyMatrix::nthJetAfterCuts(TriggerData* TD, int nthJet, float etaMin, float etaMax, EventData* ED_jet, EventData* ED_trigJet, EventData* ED_truthJet)
{
    if (m_debug) std::cout << "Starting nthJetAfterCuts()..." << std::endl;

    int passedJets = 0;
    int posLastPassedJet = 0;

    for (unsigned int n=0; n < ED_jet->eta->size(); n++){


	// Reset CutHandler for every jet
	cutHandler->Reset();

    // Apply default cuts
    cutHandler->AddCut(ED_jet->eta->at(n), etaMin, "absmin");
    cutHandler->AddCut(ED_jet->eta->at(n), etaMax, "absmax");
    //cutHandler->AddCut(ED_jet->Timing->at(n), 10.0, "absmax"); //TODO PUTBACK

    // Additional Cuts if needed
    cutHandler->UseCutStringMethod(ED_jet, ED_trigJet, ED_truthJet);

	// Isolation for multijets only
    if (nthJet > 1) cutHandler->CheckIsolation(n, ED_jet, 0.6, 20);

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

    float calo_etaMin, calo_etaMax;
    int passedJets = 0;
    int posLastPassedJet = 0;

    // fill calo_etaMin and calo_etaMax (Bad Coding, need changing) TODO!!!
    if (isL1){
	if (etaMax <= 3.5) { // L1 central jet region
        calo_etaMin = calo_L1_cen_etaMin;
        calo_etaMax = calo_L1_cen_etaMax;
    } else {             // L1 fwd jet region
        calo_etaMin = calo_L1_fwd_etaMin;
        calo_etaMax = calo_L1_fwd_etaMax;
	}
    } else {
	if (etaMax <= 3.5) { // HLT central jet region
        calo_etaMin = calo_HLT_cen_etaMin;
        calo_etaMax = calo_HLT_cen_etaMax;
    } else {             // HLT fwd jet region
        calo_etaMin = calo_HLT_fwd_etaMin;
        calo_etaMax = calo_HLT_fwd_etaMax;
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
    cutHandler->AddCut(jetEta, calo_etaMin, "absmin");
    cutHandler->AddCut(jetEta, calo_etaMax, "absmax");

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

bool TriggerEfficiencyMatrix::passedEmulationOfHtTrigger(float HtThreshold, EventData *ED_trigJet)
{
    if (m_debug) std::cout << "passedEmulationOfHtTrigger()..." << std::endl;

    // Calculate HT on trigger level using ED_trigJet
    float Ht = ED_trigJet->GetHT_triggerLevel();

    if (Ht > HtThreshold) return true;
    else return false;
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
