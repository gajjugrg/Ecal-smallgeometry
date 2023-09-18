/// \file optical/OpNovice2/src/HistoManager.cc
/// \brief Implementation of the HistoManager class
//
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
    : fFileName("eCal")
{
    Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
    // Create or get analysis manager
    // The choice of analysis technology is done via selection of a namespace
    // in HistoManager.hh
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetFileName(fFileName);
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetActivation(true);    // enable inactivation of histograms

    // Define histogram indices, titles
    G4int maxHisto = 13;
    G4String id[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "10","11","12","13" };

    G4String title[] = {
        "dummy",                                        // 0
        "Cerenkov spectrum",                            // 1
        "scintillation spectrum",                       // 2
        "boundary process status",                      // 3
        "X momentum dir of backward-going photons",     // 4
        "Y momentum dir of backward-going photons",     // 5
        "Z momentum dir of backward-going photons",     // 6
        "X momentum dir of forward-going photons",      // 7
        "Y momentum dir of forward-going photons",      // 8
        "Z momentum dir of forward-going photons",      // 9
        "energy deposition in scintillator per event",  //10
        "scintillator ID vs energy",                    //11
        "scintillation photons per event",              //12
        "scintillation photons creation time",          //13
    };

    // Default values (to be reset via /analysis/h1/set command)               
    G4int nbins = 100;
    G4double vmin = 0.;
    G4double vmax = 100.;

    // Create all histograms as inactivated 
    for (G4int k=0; k <= maxHisto; ++k) {
        G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
        analysisManager->SetH1Activation(ih, false);
    }
//    G4int maxLayer = 50;
//    for (G4int j=0; j <= maxLayer; j++){
//
//        G4String name = "Layer" + std::to_string(j);
//        G4int Hist = analysisManager->CreateH2(name,name, 35, 0, 35, 35, 0, 35);
//        analysisManager ->SetH2Activation(Hist, true);
//    }
//    G4int Hist = analysisManager->CreateH2("hist2d", "Cell vs energy", 3500, 0, 3500, 35, 0, 35);
//    analysisManager->SetH2Activation(Hist, true);
}
