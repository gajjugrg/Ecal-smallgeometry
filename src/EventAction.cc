#include "EventAction.hh"
#include "EmCalHit.hh"
#include "Run.hh"
#include "HistoManager.hh"
#include "DetectorConstruction.hh"

#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
    : fScintCollID(-1),fVerbose(0)
{
    fHitCount = 0;
    fPhotonCount_Scint = 0;
    fPhotonCount_Ceren = 0;
    fAbsorptionCount = 0;
    fBoundaryAbsorptionCount = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event*) {

    fHitCount = 0;
    fPhotonCount_Scint = 0;
    fPhotonCount_Ceren = 0;
    fAbsorptionCount = 0;
    fBoundaryAbsorptionCount = 0;

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    if(fScintCollID<0)
        fScintCollID=SDman->GetCollectionID("scintCollection");
}

void EventAction::EndOfEventAction(const G4Event* anEvent){

    EmCalHitsCollection* scintHC = nullptr;
    G4HCofThisEvent* hitsCE = anEvent->GetHCofThisEvent();

    //Get the hit collections
    if(hitsCE){
        if(fScintCollID>=0) {
            scintHC = (EmCalHitsCollection*)(hitsCE->GetHC(fScintCollID));
        }
    }

    //Hits in scintillator
    G4double tEdep[3501]={0.0};
    if(scintHC){
        int n_hit = scintHC->entries();
        G4double edep = 0.;
        G4int pos;
        for(G4int i=0; i<n_hit; i++){ 
            //gather info on hits in scintillator
            pos=(*scintHC)[i]->GetPos(); 
            edep=(*scintHC)[i]->GetEdep(); 
            tEdep[pos] += edep;
        }
    }
    auto analysisManager = G4AnalysisManager::Instance();
    engine = new CLHEP::RanecuEngine;

    G4double photoelectron;
    G4double smearedPE;

   for(G4int copyNo = 1; copyNo <= 3500; copyNo++){
       scintEnergy  = tEdep[copyNo]/CLHEP::MeV;
       photoelectron = scintEnergy*conversionFactor;
       smearedPE = CLHEP::RandPoisson::shoot(engine,photoelectron);
       analysisManager->FillH1(11, copyNo, smearedPE);

       analysisManager->FillNtupleIColumn(0, copyNo);
       analysisManager->FillNtupleDColumn(1, smearedPE);
       analysisManager->AddNtupleRow(); 
   }


/*
    for( G4int copyNo = 1; copyNo <= 3500; copyNo++){
        layer_num = (copyNo -1)/70 + 1;
        rem = (copyNo - 1)%70 +1;
        if(rem <= 35) {
            cellX = rem;
            for(G4int cellY = 1; cellY <= 35; cellY++){
                if(tEdep[(layer_num -1)*70 + rem] == 0.0 || tEdep[(layer_num -1)*70+ 35 + cellY] == 0.0 ){ 
                    cellEnergy = 0.0/CLHEP::MeV;
                }
                else{ 
                    cellEnergy = (tEdep[(layer_num -1)*70 + rem] +
                            tEdep[(layer_num -1)*70+ 35 + cellY])/CLHEP::MeV;
                }
                photoelectron = cellEnergy*conversionFactor;
                smearedPE = CLHEP::RandPoisson::shoot(engine, photoelectron);
                analysisManager->FillH2(layer_num, cellX, cellY, smearedPE);
                analysisManager->FillH2(0, cellX, cellY,smearedPE);
            }
        }
    }
*/
    delete engine;

    if(fVerbose>0){
        G4cout << "\tTotal energy deposition in scintillator : "
            << fTotE / keV << " (keV)" << G4endl;
    }
    if(fVerbose>0){
        //End of event output. later to be controlled by a verbose level
        G4cout << "\tNumber of photons produced by scintillation in this event : "
            << fPhotonCount_Scint << G4endl;
        G4cout << "\tNumber of photons produced by cerenkov in this event : " 
            << fPhotonCount_Ceren << G4endl;
        G4cout << "\tNumber of photons absorbed (OpAbsorption) in this event : "
            << fAbsorptionCount << G4endl;
        G4cout << "\tNumber of photons absorbed at boundaries (OpBoundary) in this event : " 
            << fBoundaryAbsorptionCount << G4endl;
        G4cout << "Unaccounted for photons in this event : " 
            << (fPhotonCount_Scint + fPhotonCount_Ceren -
                    fAbsorptionCount - fHitCount - fBoundaryAbsorptionCount)  << G4endl;
    }


}
