/// \file optical//include/EventAction.hh
/// \brief Definition of the EventAction class
//

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "CLHEP/Random/RanecuEngine.h"

class G4Event;
class DetectorConstruction;

class EventAction : public G4UserEventAction
{
  public:

    EventAction();
    virtual ~EventAction();

  public:

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void SetEventVerbose(G4int v){fVerbose=v;}

    void IncPhotonCount_Scint(){fPhotonCount_Scint++;}
    void IncPhotonCount_Ceren(){fPhotonCount_Ceren++;}
    void IncEDep(G4double dep){fTotE+=dep;}
    void IncAbsorption(){fAbsorptionCount++;}
    void IncBoundaryAbsorption(){fBoundaryAbsorptionCount++;}
    void IncHitCount(G4int i=1){fHitCount+=i;}

    G4int GetPhotonCount_Scint()const {return fPhotonCount_Scint;}
    G4int GetPhotonCount_Ceren()const {return fPhotonCount_Ceren;}
    G4int GetHitCount()const {return fHitCount;}
    G4double GetEDep()const {return fTotE;}
    G4int GetAbsorptionCount()const {return fAbsorptionCount;}
    G4int GetBoundaryAbsorptionCount() const {return fBoundaryAbsorptionCount;}

    //Gets the total photon count produced
    G4int GetPhotonCount(){return fPhotonCount_Scint+fPhotonCount_Ceren;}


  private:


    G4int fScintCollID;
    G4int fVerbose;

    G4int fHitCount;
    G4int fPhotonCount_Scint;
    G4int fPhotonCount_Ceren;
    G4int fAbsorptionCount;
    G4int fBoundaryAbsorptionCount;

    G4double fTotE;
   
   // G4double cellEnergy;
    G4double scintEnergy;
   // G4int cellX;
   // G4int layer_num;
   //  G4int rem;
    const G4double conversionFactor = 50;
    CLHEP::HepRandomEngine* engine;

};

#endif
