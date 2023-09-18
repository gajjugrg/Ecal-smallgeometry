/// \file optical/OpNovice2/src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
//

#include "TrackingAction.hh"
#include "TrackInformation.hh"

#include "G4TrackingManager.hh"
#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TrackingAction::TrackingAction()
:G4UserTrackingAction()
{;}

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  // Create trajectory only for track in tracking region
  TrackInformation* trackInfo = 
    (TrackInformation*)(aTrack->GetUserInformation());

  if (!trackInfo) {
    trackInfo = new TrackInformation(aTrack); 
    trackInfo->SetIsFirstPVTX(true);
    aTrack->SetUserInformation(trackInfo);
  }

  trackInfo->SetIsFirstPVTX(true);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  if (secondaries)
  {
    TrackInformation* info = 
      (TrackInformation*)(aTrack->GetUserInformation());
    size_t nSeco = secondaries->size();
    if (nSeco > 0)
    {
      for(size_t i=0; i < nSeco; i++)
      { 
        TrackInformation* infoNew = new TrackInformation(info);
        (*secondaries)[i]->SetUserInformation(infoNew);
      }
    }
  }
}
