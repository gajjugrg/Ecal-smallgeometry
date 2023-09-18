#ifndef EmCalHit_h
#define EmCalHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"

#include "tls.hh"

class EmCalHit : public G4VHit
{
  public:
 
    EmCalHit();
    EmCalHit(G4VPhysicalVolume* pVol);
    virtual ~EmCalHit();
    EmCalHit(const EmCalHit &right);
    const EmCalHit& operator=(const EmCalHit &right);
    G4bool operator==(const EmCalHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
 
    virtual void Draw();
    virtual void Print();

    inline void SetEdep(G4double de) { fEdep = de; }
    inline void AddEdep(G4double de) { fEdep += de; }
    inline G4double GetEdep() { return fEdep; }

    inline void SetPos(G4int x) { fPos = x; }
    inline G4int GetPos() { return fPos; }

    inline const G4VPhysicalVolume * GetPhysV() { return fPhysVol; }

  private:
    G4double fEdep;
    G4int fPos;
    const G4VPhysicalVolume* fPhysVol;

};

typedef G4THitsCollection<EmCalHit> EmCalHitsCollection;

extern G4ThreadLocal G4Allocator<EmCalHit>* EmCalHitAllocator;

inline void* EmCalHit::operator new(size_t)
{
  if(!EmCalHitAllocator)
      EmCalHitAllocator = new G4Allocator<EmCalHit>;
  return (void *) EmCalHitAllocator->MallocSingle();
}

inline void EmCalHit::operator delete(void *aHit)
{
  EmCalHitAllocator->FreeSingle((EmCalHit*) aHit);
}

#endif
