/// \file optical/OpNovice2/include/RunAction.hh
/// \brief Definition of the RunAction class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#ifndef Run_h
#define Run_h 1

#include "G4OpBoundaryProcess.hh"
#include "G4Run.hh"

class G4ParticleDefinition;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class Run : public G4Run
{
  public:
    Run();
    ~Run();

    void SetPrimary(G4ParticleDefinition* particle, G4double energy);

    // spectrum of Cerenkov radiation
    void AddCerenkovEnergy(G4double en) {fCerenkovEnergy += en;}
    void AddScintillationEnergy(G4double en) {fScintEnergy += en;}

    void AddCerenkov(void) {fCerenkovCount += 1;}
    void AddScintillation(void) {fScintCount += 1;}
    void AddRayleigh(void) {fRayleighCount += 1;}
    
    void AddOpAbsorption(void) {fOpAbsorption += 1;}
    void AddOpAbsorptionPrior(void) {fOpAbsorptionPrior += 1;}

    void AddFresnelRefraction(void) {
      fBoundaryProcs[FresnelRefraction] += 1;
    }
    void AddFresnelReflection(void) {
      fBoundaryProcs[FresnelReflection] += 1;
    }
    void AddTransmission(void) {fBoundaryProcs[Transmission] += 1;}
    void AddTotalInternalReflection(void) 
      {fBoundaryProcs[TotalInternalReflection] += 1;}
    void AddLambertianReflection(void)  
      {fBoundaryProcs[LambertianReflection] += 1;}
    void AddLobeReflection(void) {fBoundaryProcs[LobeReflection] += 1;}
    void AddSpikeReflection(void) {fBoundaryProcs[SpikeReflection] += 1;}
    void AddBackScattering(void) {fBoundaryProcs[BackScattering] += 1;}
    void AddAbsorption(void) {fBoundaryProcs[Absorption] += 1;}
    void AddDetection(void) {fBoundaryProcs[Detection] += 1;}
    void AddNotAtBoundary(void) {fBoundaryProcs[NotAtBoundary] += 1;}
    void AddSameMaterial(void) {fBoundaryProcs[SameMaterial] += 1;}
    void AddStepTooSmall(void) {fBoundaryProcs[StepTooSmall] += 1;}
    void AddNoRINDEX(void) {fBoundaryProcs[NoRINDEX] += 1;}

    void AddTotalSurface(void) {fTotalSurface += 1;}
    void AddPolishedLumirrorAirReflection(void) 
      {fBoundaryProcs[PolishedLumirrorAirReflection] += 1;}
    void AddPolishedLumirrorGlueReflection(void) 
      {fBoundaryProcs[PolishedLumirrorGlueReflection] += 1;}
    void AddPolishedAirReflection(void) 
      {fBoundaryProcs[PolishedAirReflection] += 1;}
    void AddPolishedTeflonAirReflection(void) 
      {fBoundaryProcs[PolishedTeflonAirReflection] += 1;}
    void AddPolishedTiOAirReflection(void) 
      {fBoundaryProcs[PolishedTiOAirReflection] += 1;}
    void AddPolishedTyvekAirReflection(void) 
      {fBoundaryProcs[PolishedTyvekAirReflection] += 1;}
    void AddPolishedVM2000AirReflection(void) 
      {fBoundaryProcs[PolishedVM2000AirReflection] += 1;}
    void AddPolishedVM2000GlueReflection(void) 
      {fBoundaryProcs[PolishedVM2000GlueReflection] += 1;}

    void AddEtchedLumirrorAirReflection(void) 
      {fBoundaryProcs[EtchedLumirrorAirReflection] += 1;}
    void AddEtchedLumirrorGlueReflection(void) 
      {fBoundaryProcs[EtchedLumirrorGlueReflection] += 1;}
    void AddEtchedAirReflection(void) 
      {fBoundaryProcs[EtchedAirReflection] += 1;}
    void AddEtchedTeflonAirReflection(void) 
      {fBoundaryProcs[EtchedTeflonAirReflection] += 1;}
    void AddEtchedTiOAirReflection(void) 
      {fBoundaryProcs[EtchedTiOAirReflection] += 1;}
    void AddEtchedTyvekAirReflection(void) 
      {fBoundaryProcs[EtchedTyvekAirReflection] += 1;}
    void AddEtchedVM2000AirReflection(void) 
      {fBoundaryProcs[EtchedVM2000AirReflection] += 1;}
    void AddEtchedVM2000GlueReflection(void) 
      {fBoundaryProcs[EtchedVM2000GlueReflection] += 1;}

    void AddGroundLumirrorAirReflection(void) 
      {fBoundaryProcs[GroundLumirrorAirReflection] += 1;}
    void AddGroundLumirrorGlueReflection(void) 
      {fBoundaryProcs[GroundLumirrorGlueReflection] += 1;}
    void AddGroundAirReflection(void) 
      {fBoundaryProcs[GroundAirReflection] += 1;}
    void AddGroundTeflonAirReflection(void) 
      {fBoundaryProcs[GroundTeflonAirReflection] += 1;}
    void AddGroundTiOAirReflection(void) 
      {fBoundaryProcs[GroundTiOAirReflection] += 1;}
    void AddGroundTyvekAirReflection(void) 
      {fBoundaryProcs[GroundTyvekAirReflection] += 1;}
    void AddGroundVM2000AirReflection(void) 
      {fBoundaryProcs[GroundVM2000AirReflection] += 1;}
    void AddGroundVM2000GlueReflection(void) 
      {fBoundaryProcs[GroundVM2000GlueReflection] += 1;}

    void AddDichroic(void) {fBoundaryProcs[Dichroic] += 1;}

    virtual void Merge(const G4Run*);

    void EndOfRun();

  private:
    // primary particle
    G4ParticleDefinition* fParticle;
    G4double fEkin;

    G4double fCerenkovEnergy;
    G4double fScintEnergy;

    // number of particles
    G4int fCerenkovCount;
    G4int fScintCount;
    // number of events
    G4int fRayleighCount;
    
    // non-boundary processes
    G4int fOpAbsorption;

    // prior to boundary:
    G4int fOpAbsorptionPrior;

    // boundary proc
    std::vector<G4int> fBoundaryProcs;

    G4int fTotalSurface;

};


#endif /* Run_h */
