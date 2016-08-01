/*--------------------------------------------------------------------
HistogramMatrix.cxx

The original class for all classes containing histograms.
Histograms are generally saved in a std::map.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/HistogramMatrix.h>
#include <iostream>
#include <assert.h>

HistogramMatrix::HistogramMatrix(ConfigStatus* a_CS):
    m_directory("HistogramMatrix"), m_nthJet(0), CS(a_CS)
{
  if (m_debug) std::cout << "Starting constructor HistogramMatrix()..." << std::endl;
}

HistogramMatrix::HistogramMatrix(std::string directory, ConfigStatus* a_CS):
    m_directory(directory), m_nthJet(0), CS(a_CS)
{
  if (m_debug) std::cout << "Starting constructor HistogramMatrix()..." << std::endl;
}


HistogramMatrix::HistogramMatrix(std::string directory, int nthJet, ConfigStatus* a_CS):
    m_directory(directory), m_nthJet(nthJet), CS(a_CS)
{
    if (m_debug) std::cout << "Starting constructor HistogramMatrix()..." << std::endl;
}

HistogramMatrix::~HistogramMatrix()
{
  if (m_debug) std::cout << "Starting destructor HistogramMatrix()..." << std::endl;
}


void HistogramMatrix::Book(std::string name1, std::string name2, int nBins, double xMin, double xMax, EL::Worker* wk)
{
  if (m_debug) std::cout << "Starting Book()..." << std::endl;

  TH1D* histo = new TH1D((m_directory+"/"+name1).c_str(), name2.c_str(), nBins, xMin, xMax);
  histo->Sumw2();
  m_map[name1] = histo;
  wk->addOutput(m_map[name1]);

  // Addition for leadJet, subleadJet and ThirdJet
  if (CS->doLeadSubleadThirdJetKinematics){
    // only book for vector values:
      if ((name1.find("_E")!=std::string::npos) || (name1.find("_pt")!=std::string::npos) ||  (name1.find("_eta")!=std::string::npos) || (name1.find("_phi")!=std::string::npos) || (name1.find("_EMFrac")!=std::string::npos) || (name1.find("_HECFrac")!=std::string::npos) || (name1.find("_FracSamplingMax")!=std::string::npos)){

      // leading
      TH1D* histoLead = new TH1D((m_directory+"/"+lead+name1).c_str(), (lead+name2).c_str(), nBins, xMin, xMax);
      m_map[lead+name1] = histoLead;
      wk->addOutput(m_map[lead+name1]);

      // subleading
      TH1D* histoSublead = new TH1D((m_directory+"/"+sublead+name1).c_str(), (sublead+name2).c_str(), nBins, xMin, xMax);
      m_map[sublead+name1] = histoSublead;
      wk->addOutput(m_map[sublead+name1]);

      // third
      TH1D* histoThird = new TH1D((m_directory+"/"+third+name1).c_str(), (third+name2).c_str(), nBins, xMin, xMax);
      m_map[third+name1] = histoThird;
      wk->addOutput(m_map[third+name1]);
    }
  }

  // nth Jet
  if (CS->doNthJetKinematics){
      // only book for vector values:
      if ((name1.find("_E")!=std::string::npos) || (name1.find("_pt")!=std::string::npos) ||  (name1.find("_eta")!=std::string::npos) || (name1.find("_phi")!=std::string::npos) || (name1.find("_EMFrac")!=std::string::npos) || (name1.find("_HECFrac")!=std::string::npos) || (name1.find("_FracSamplingMax")!=std::string::npos)){

	  // nth
	  TH1D* histo = new TH1D((m_directory+"/"+nth+name1).c_str(), (nth+name2).c_str(), nBins, xMin, xMax);
	  m_map[nth+name1] = histo;
	  wk->addOutput(m_map[nth+name1]);
      }
  }

  if (m_debug) std::cout << "Booked histo: " << name1 << std::endl;
}

void HistogramMatrix::Book(std::string name1, std::string name2, int nBins, double* xBinning, EL::Worker* wk)
{
  if (m_debug) std::cout << "Starting Book()..." << std::endl;

  TH1D* histo = new TH1D((m_directory+"/"+name1).c_str(), name2.c_str(), nBins, xBinning);
  m_map[name1] = histo;
  wk->addOutput(m_map[name1]);

  // Addition for leadJet, subleadJet and ThirdJet
  if (CS->doLeadSubleadThirdJetKinematics){
    // only book for vector values:
      if ((name1.find("_E")!=std::string::npos) || (name1.find("_pt")!=std::string::npos) ||  (name1.find("_eta")!=std::string::npos) || (name1.find("_phi")!=std::string::npos) || (name1.find("_EMFrac")!=std::string::npos) || (name1.find("_HECFrac")!=std::string::npos) || (name1.find("_FracSamplingMax")!=std::string::npos)){

      // leading
      TH1D* histoLead = new TH1D((m_directory+"/"+lead+name1).c_str(), (lead+name2).c_str(), nBins, xBinning);
      m_map[lead+name1] = histoLead;
      wk->addOutput(m_map[lead+name1]);

      // subleading
      TH1D* histoSublead = new TH1D((m_directory+"/"+sublead+name1).c_str(), (sublead+name2).c_str(), nBins, xBinning);
      m_map[sublead+name1] = histoSublead;
      wk->addOutput(m_map[sublead+name1]);

      // third
      TH1D* histoThird = new TH1D((m_directory+"/"+third+name1).c_str(), (third+name2).c_str(), nBins, xBinning);
      m_map[third+name1] = histoThird;
      wk->addOutput(m_map[third+name1]);
    }
  }

  // nth Jet
  if (CS->doNthJetKinematics){
      // only book for vector values:
      if ((name1.find("_E")!=std::string::npos) || (name1.find("_pt")!=std::string::npos) ||  (name1.find("_eta")!=std::string::npos) || (name1.find("_phi")!=std::string::npos) || (name1.find("_EMFrac")!=std::string::npos) || (name1.find("_HECFrac")!=std::string::npos) || (name1.find("_FracSamplingMax")!=std::string::npos)){

	  // nth
	  TH1D* histo = new TH1D((m_directory+"/"+nth+name1).c_str(), (nth+name2).c_str(), nBins, xBinning);
	  m_map[nth+name1] = histo;
	  wk->addOutput(m_map[nth+name1]);
      }
  }

  if (m_debug) std::cout << "Booked histo: " << name1 << std::endl;
}


void HistogramMatrix::coutAllBookings()
{
  if (m_debug) std::cout << "Starting coutAll()..." << std::endl;

    std::map<std::string, TH1D*>::iterator it = m_map.begin();

    std::cout << "Writing out all map entries... " << std::endl;
    while(it != m_map.end()){
      std::cout << "--- " << it->first <<  std::endl;
      it++;
    }
}


void HistogramMatrix::Fill(std::string name, int value, bool isGood, double weight)
{
  //  if (m_debug) std::cout << "Starting Fill()..." << std::endl;
  //assert(("This histogram is NOT booked!",this->isBooked(name)));

    if (isGood) m_map[name]->Fill(value, weight);
}


void HistogramMatrix::Fill(std::string name, double value, bool isGood, double weight)
{
    if (m_debug) std::cout << "Starting HistogramMatrix::Fill(): " << name << "..." << std::endl;
  //assert(("This histogram is NOT booked!",this->isBooked(name)));

    if (isGood) m_map[name]->Fill(value, weight);
}

// needed because of stupid implementation of Eta-Regions
void HistogramMatrix::FillConsiderLeadSubThird(std::string name, double value, int n, bool isGood, double weight)
{
    if (m_debug) std::cout << "Starting HistogramMatrix::FillConsiderLeadSubThird(): " << name << "..." << std::endl;
    //assert(("This histogram is NOT booked!",this->isBooked(name)));

    // check Goodness
    if (!isGood) return;

    m_map[name]->Fill(value, weight);

    // Addition for leading, subleading and third jet
    if(CS->doLeadSubleadThirdJetKinematics){
	if (n == 0) m_map[lead+name]->Fill(value, weight);
	if (n == 1) m_map[sublead+name]->Fill(value, weight);
	if (n == 2) m_map[third+name]->Fill(value, weight);
    }

    if(CS->doNthJetKinematics){
	if (n == m_nthJet) m_map[nth+name]->Fill(value, weight);
    }
}

void HistogramMatrix::Fill(std::string name, std::vector<float>* valueVector, std::vector<bool>* isGood, double weight)
{
  //  if (m_debug) std::cout << "Starting Fill()..." << std::endl;
  //assert(("This histogram is NOT booked!",this->isBooked(name)));

    for (unsigned int n = 0; n < valueVector->size(); n++){
	if (!isGood->at(n)) continue;
	m_map[name]->Fill(valueVector->at(n), weight);

	// Addition for leading, subleading and third jet
	if(CS->doLeadSubleadThirdJetKinematics){
	    if (n == 0) m_map[lead+name]->Fill(valueVector->at(0), weight);
	    if (n == 1) m_map[sublead+name]->Fill(valueVector->at(1), weight);
	    if (n == 2) m_map[third+name]->Fill(valueVector->at(2), weight);
	}

	if(CS->doNthJetKinematics){
	    if (n == m_nthJet) m_map[nth+name]->Fill(valueVector->at(n), weight);
	}

    }

}


bool HistogramMatrix::isBooked(std::string name)
{
  if (m_debug) std::cout << "Starting isBooked()..." << std::endl;

  if (m_map.find(name) != m_map.end()){
    if (m_debug) std::cout << name << " is booked." << std::endl;
    return true;
  } else {
    if (m_debug) std::cout << name << " is NOT booked." << std::endl;
    return false;
  }
}
