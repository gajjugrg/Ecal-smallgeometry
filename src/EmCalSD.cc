#include "EmCalSD.hh"
#include "EmCalHit.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

EmCalSD::EmCalSD(G4String name)
    : G4VSensitiveDetector(name)
{
    fScintCollection = nullptr;
    collectionName.insert("scintCollection");
}

EmCalSD::~EmCalSD() {}

void EmCalSD::Initialize(G4HCofThisEvent* hitsCE){
    fScintCollection = new EmCalHitsCollection(SensitiveDetectorName,collectionName[0]);
    //A way to keep all the hits of this event in one place if needed
    static G4int hitsCID = -1;
    if(hitsCID<0){
        hitsCID = GetCollectionID(0);
    }
    hitsCE->AddHitsCollection( hitsCID, fScintCollection );
}

G4bool EmCalSD::ProcessHits(G4Step* aStep, G4TouchableHistory*){
    G4double edep = aStep->GetTotalEnergyDeposit();
    if(edep==0.) return false; //No edep so dont count as hit

    G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
    G4VPhysicalVolume* thePrePV = theTouchable->GetVolume();

    G4int pos = thePrePV->GetCopyNo();
    EmCalHit* scintHit = new EmCalHit(thePrePV);

    scintHit->SetEdep(edep);
    scintHit->SetPos(pos);

    fScintCollection->insert(scintHit);

    return true;
}


void EmCalSD::EndOfEvent(G4HCofThisEvent* ) {}
void EmCalSD::clear() {} 
void EmCalSD::DrawAll() {} 
void EmCalSD::PrintAll() {} 
