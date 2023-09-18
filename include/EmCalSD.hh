/// \file optical/LXe/include/ecalSD.hh
/// \brief Definition of the ecalSD class
//
//
#ifndef EmcalSD_h
#define EmcalSD_h 1

#include "EmCalHit.hh"

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class EmCalSD : public G4VSensitiveDetector
{
  public:

    EmCalSD(G4String name);
    virtual ~EmCalSD();

    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
    virtual void EndOfEvent(G4HCofThisEvent* );
    virtual void clear();
    virtual void DrawAll();
    virtual void PrintAll();
 
  private:

    EmCalHitsCollection* fScintCollection;
 
};

#endif
