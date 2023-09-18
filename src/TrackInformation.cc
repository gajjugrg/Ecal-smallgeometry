/// \file optical/OpNovice2/src/TrackInformation.cc
/// \brief Implementation of the TrackInformation class
//
//
//

#include "TrackInformation.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"    

G4ThreadLocal G4Allocator<TrackInformation> *
                                   aTrackInformationAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TrackInformation::TrackInformation()
  : G4VUserTrackInformation()
{
  fFirstPVTX = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TrackInformation::TrackInformation(const G4Track*)
  : G4VUserTrackInformation()
{
  fFirstPVTX = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TrackInformation ::TrackInformation(const TrackInformation* aTrackInfo)
  : G4VUserTrackInformation()
{
  fFirstPVTX = aTrackInfo->fFirstPVTX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TrackInformation::~TrackInformation()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TrackInformation& TrackInformation::operator=
  (const TrackInformation& aTrackInfo)
{
  fFirstPVTX = aTrackInfo.fFirstPVTX;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TrackInformation::SetSourceTrackInformation(const G4Track*)
{
  fFirstPVTX = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TrackInformation::Print() const
{
  G4cout << "first time track incident on X: " << fFirstPVTX << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
