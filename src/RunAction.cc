/// \file optical/OpNovice2/src/RunAction.cc
/// \brief Implementation of the RunAction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Make this appear first!
#include "G4Timer.hh"

#include "RunAction.hh"
#include "HistoManager.hh"
#include "PrimaryGeneratorAction.hh"

#include "Run.hh"
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(PrimaryGeneratorAction* prim)
    : G4UserRunAction(),
    fTimer(nullptr),
    fRun(nullptr),
    fHistoManager(nullptr),
    fPrimary(prim)
{
    fTimer = new G4Timer;
    fHistoManager = new HistoManager();

    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);

    analysisManager->CreateNtuple("scint", "ecal: scintillation edep");
    analysisManager->CreateNtupleIColumn("ScintID");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->FinishNtuple(); 


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
    delete fTimer;
    delete fHistoManager;
}

G4Run* RunAction::GenerateRun()
{
    fRun = new Run();
    return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

    if (fPrimary) {
        G4ParticleDefinition* particle = 
            fPrimary->GetParticleGun()->GetParticleDefinition();
        G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
        fRun->SetPrimary(particle, energy);
    }

    //histograms
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->IsActive()) {
        analysisManager->OpenFile();
    }

    fTimer->Start();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
    fTimer->Stop();
    G4cout << "number of event = " << aRun->GetNumberOfEvent()
        << " " << *fTimer << G4endl;

    if (isMaster) fRun->EndOfRun();

    // save histograms
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->IsActive()) {
        analysisManager->Write();
        analysisManager->CloseFile();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
