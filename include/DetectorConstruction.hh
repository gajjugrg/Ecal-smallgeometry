/// \file optical/OpNovice2/include/DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4OpticalSurface.hh"

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RunManager.hh"
#include <vector>

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction();
        virtual ~DetectorConstruction();

        G4Material* GetWorldMaterial() const {return fWorldMaterial;}
        G4Material* GetPVTMaterial() const {return fPVTMaterial;}

        virtual G4VPhysicalVolume* Construct() override;
        void ConstructSDandField() override;


    private:
        void DefineMaterials();
        G4double fExpHall_x;
        G4double fExpHall_y;
        G4double fExpHall_z;

        G4VPhysicalVolume* fPVT_vert;
        G4VPhysicalVolume* fPVT_hrzn;

        G4double fPVT_x;
        G4double fPVT_y;
        G4double fPVT_z;

        G4LogicalVolume* fWorld_LV;
        G4LogicalVolume* fPVT_LV_hrzn;
        G4LogicalVolume* fPVT_LV_vert;

        G4Material* fWorldMaterial;
        G4Material* fPVTMaterial;

        G4OpticalSurface* fSurface;
        G4OpticalSurface* fSurf_PVT;

        G4MaterialPropertiesTable* fPVTMPT;
        G4MaterialPropertiesTable* fWorldMPT;
        G4MaterialPropertiesTable* fSurfaceMPT;
        G4MaterialPropertiesTable* fSurf_PVTMPT;
        G4Element* fC;
        G4Element* fH;

        std::vector<G4VisAttributes*>fVisAttributes;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*DetectorConstruction_h*/
