/// \file optical/OpNovice2/include/TrackInformation.hh
/// \brief Definition of the TrackInformation class
//
//
//

#ifndef TrackInformation_h
#define TrackInformation_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"

class TrackInformation : public G4VUserTrackInformation 
{
public:
  TrackInformation();
  TrackInformation(const G4Track* aTrack);
  TrackInformation(const TrackInformation* aTrackInfo);
  virtual ~TrackInformation();
   
  inline void *operator new(size_t);
  inline void operator delete(void *aTrackInfo);

  TrackInformation& operator =(const TrackInformation& right);
  
  void SetSourceTrackInformation(const G4Track* aTrack);
  virtual void Print() const;

public:
  inline G4bool GetIsFirstPVTX() const {return fFirstPVTX;}
  inline void   SetIsFirstPVTX(G4bool b) {fFirstPVTX = b;}

private:
  G4bool    fFirstPVTX;
};

extern G4ThreadLocal
 G4Allocator<TrackInformation> * aTrackInformationAllocator;

inline void* TrackInformation::operator new(size_t)
{
  if(!aTrackInformationAllocator)
    aTrackInformationAllocator = new G4Allocator<TrackInformation>;
  return (void*)aTrackInformationAllocator->MallocSingle();
}

inline void TrackInformation::operator delete(void *aTrackInfo)
{ aTrackInformationAllocator->FreeSingle((TrackInformation*)aTrackInfo);}

#endif

