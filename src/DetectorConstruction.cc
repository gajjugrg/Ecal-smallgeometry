/// \file optical/OpNovice2/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4MaterialTable.hh"
#include "G4OpticalSurface.hh"
#include "G4PhysicalConstants.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "EmCalSD.hh"
#include "EmCalHit.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
{

    // These values are half of the original dimesions
    fExpHall_x = fExpHall_y = fExpHall_z = 1*m; 
    fPVT_x    = 15.0*mm; //strip_width
    fPVT_y    = 525.0*mm; //block size
    fPVT_z    = 5.0*mm; //scintillator thickness

    fPVT_hrzn = nullptr;
    fPVT_vert = nullptr;

    fPVTMPT    = new G4MaterialPropertiesTable();
    fWorldMPT   = new G4MaterialPropertiesTable();
    fSurfaceMPT = new G4MaterialPropertiesTable();
    fSurf_PVTMPT = new G4MaterialPropertiesTable();

    //Surface between PVT and outerlayer
    fSurface = new G4OpticalSurface("Surface");
    fSurface->SetType(dielectric_dielectric);
    fSurface->SetFinish(ground);
    fSurface->SetModel(unified);
    fSurface->SetMaterialPropertiesTable(fSurfaceMPT);
    
    //# The surface of PVT
    fSurf_PVT = new G4OpticalSurface("Surf_PVT");
    fSurf_PVT->SetType(dielectric_dielectric);
    fSurf_PVT->SetFinish(polished);
    fSurf_PVT->SetModel(unified);
    fSurf_PVT->SetMaterialPropertiesTable(fSurf_PVTMPT);

    fPVT_LV_hrzn  = nullptr;
    fPVT_LV_vert  = nullptr;
    fWorld_LV = nullptr;

    fC = fH = nullptr;
    DefineMaterials();
}

DetectorConstruction::~DetectorConstruction()
{ 
    for (auto visAttributes: fVisAttributes){
        delete visAttributes;
    }
}

void DetectorConstruction::DefineMaterials(){
    G4double a;
    G4double z;
    G4double density;

    G4int polyVT = 1;
    G4int nC_VT = 10 * polyVT;
    G4int nH_VT = 11 * polyVT;

    fH = new G4Element("H", "H", z = 1., a = 1.01 * g / mole);
    fC = new G4Element("C", "C", z = 6., a = 12.01 * g / mole);

    // Materials
    //PolyVinylToluene
    fPVTMaterial = new G4Material("PVT", density = 1.032 * g / cm3, 2);
    fPVTMaterial->AddElement(fH, nH_VT);
    fPVTMaterial->AddElement(fC, nC_VT);

    //fWorldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");

    // Vacuum
    fWorldMaterial = new G4Material("Vacuum", z = 1., a = 1.01 * g / mole, density = CLHEP::universe_mean_density, kStateGas, 0.1 * kelvin, 1.e-19 * pascal);

    // Materials Properties tables
    const G4int nEntries = 4;
    G4double pvt_Energy[nEntries] = { 2.00 * eV, 2.87 * eV, 2.90 * eV, 3.47 * eV };
    G4double rIndexPVT[nEntries]  = { 1.5, 1.5, 1.5, 1.5 };
    G4double absorption1[nEntries] = { 2. * cm, 2. * cm, 2. * cm, 2. * cm };
    G4double scintilFast[nEntries] = { 0.0, 0.0, 1.0, 1.0 };
    fPVTMPT = new G4MaterialPropertiesTable();
    fPVTMPT->AddProperty("RINDEX", pvt_Energy, rIndexPVT, nEntries);
    fPVTMPT->AddProperty("ABSLENGTH", pvt_Energy, absorption1, nEntries);
    fPVTMPT->AddProperty("FASTCOMPONENT", pvt_Energy, scintilFast, nEntries);
    fPVTMPT->AddConstProperty("SCINTILLATIONYIELD", 10. / keV);
    fPVTMPT->AddConstProperty("RESOLUTIONSCALE", 1.0);
    fPVTMPT->AddConstProperty("FASTTIMECONSTANT", 2.1 * ns);
    fPVTMPT->AddConstProperty("SLOWTIMECONSTANT", 14.2 * ns);
    fPVTMPT->AddConstProperty("YIELDRATIO", 0.8); 

    fPVTMaterial->SetMaterialPropertiesTable(fPVTMPT);
    fPVTMaterial->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

    G4cout << "---------*******-----------------" << G4endl;
    G4cout << "PVT G4MaterialPropertiesTable" << G4endl;
    fPVTMPT->DumpTable();
    G4cout << "---------*******-----------------" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    fWorldMaterial->SetMaterialPropertiesTable(fWorldMPT);

    // ------------- Volumes --------------
    // The experimental Hall
    G4Box* world_box = new G4Box("World", 0.5*fExpHall_x, 0.5*fExpHall_y, 0.5*fExpHall_z);

    fWorld_LV = new G4LogicalVolume(world_box, fWorldMaterial, "World", 0, 0, 0);
    G4VPhysicalVolume* world_PV = new G4PVPlacement(0, G4ThreeVector(), fWorld_LV, "World", 0, false, 0);

    // The PVT
    G4Box* PVT_box_hrzn = new G4Box("PVT", 0.5*fPVT_x, 0.5*fPVT_y, 0.5*fPVT_z);
    G4Box* PVT_box_vert = new G4Box("PVT", 0.5*fPVT_y, 0.5*fPVT_x, 0.5*fPVT_z);
    fPVT_LV_hrzn = new G4LogicalVolume(PVT_box_hrzn, fPVTMaterial, "PVT", 0, 0, 0);
    fPVT_LV_vert = new G4LogicalVolume(PVT_box_vert, fPVTMaterial, "PVT", 0, 0, 0);   
    G4int layer_num = 50; // Each layer = 1 layer horizontal & vertically placed scintillator 
    G4int fiber_num = 35; // This is number of scintillator in each vertical/horizontal layer
    G4int copy_num = 1;   // This keeps track the of the scintillator the photon is
                          // the copy number should starts form 1.
    G4double total_thickness = 500.0*mm; // this is thickness in length
    G4double zPos = -0.5*total_thickness + 0.5*fPVT_z;
    G4double xPos = -0.5*fPVT_y + 0.5*fPVT_x;
    G4double yPos = -0.5*fPVT_y + 0.5*fPVT_x;

    for(G4int i = 0; i < layer_num; ++i){
        // Scintillators lying the X-direction
        for(G4int j = 0; j < fiber_num; ++j){
            new G4PVPlacement(0, G4ThreeVector(xPos, 0, zPos), fPVT_LV_hrzn, "PVT", fWorld_LV, true, copy_num);
            xPos += fPVT_x;
            copy_num++;
        }
        zPos += fPVT_z;
        //Scintillators lying the Y-direction
       for(G4int k = 0; k < fiber_num; ++k){
            new G4PVPlacement(0, G4ThreeVector(0, yPos, zPos), fPVT_LV_vert,"PVT", fWorld_LV, true, copy_num);
            yPos += fPVT_x;
            copy_num++;
        }
        zPos += fPVT_z;
        xPos = -0.5*fPVT_y + 0.5*fPVT_x;
        yPos = -0.5*fPVT_y + 0.5*fPVT_x;
    }


    // Visualization attributes -----------
    // Instantiation of a set of visualization attributes with cyan colour
    auto visAttributes = new G4VisAttributes(G4Colour(0.,1.,1.));
    fPVT_LV_hrzn->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
   
    visAttributes = new G4VisAttributes(G4Colour(0.,0.,1.)); 
    fPVT_LV_vert->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);



    // ------------- Surface --------------
    G4LogicalBorderSurface* surface_hrzn = new G4LogicalBorderSurface("Surf_hrzn", fPVT_hrzn, world_PV, fSurface);
    G4LogicalBorderSurface("Surf_vert", fPVT_vert, world_PV, fSurface);
    G4LogicalSkinSurface("Surf_PVT", fPVT_LV_hrzn, fSurf_PVT);
    G4LogicalSkinSurface("Surf_PVT", fPVT_LV_vert, fSurf_PVT);
    //here we dump the surface information

    G4double pp[] = {2.0*eV, 3.5*eV};
    const G4int num = sizeof(pp)/sizeof(G4double);
    G4double reflectivity[] = {1., 1.};
    assert(sizeof(reflectivity) == sizeof(pp));
    G4double efficiency[] = {0.0, 0.0};
    assert(sizeof(efficiency) == sizeof(pp));

    fSurf_PVTMPT->AddProperty("REFLECTIVITY",pp,reflectivity,num);
    fSurf_PVTMPT->AddProperty("EFFICIENCY",pp,efficiency,num);
    fSurf_PVT->SetMaterialPropertiesTable(fSurf_PVTMPT);

    G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>(surface_hrzn->GetSurface(fPVT_hrzn,world_PV)->GetSurfaceProperty());
    G4cout << "******  opticalSurface->DumpInfo:" << G4endl;
    if (opticalSurface) { opticalSurface->DumpInfo(); }
    G4cout << "******  end of opticalSurface->DumpInfo" << G4endl;

    return world_PV;
}

void DetectorConstruction::ConstructSDandField()
{
    auto sdManager = G4SDManager::GetSDMpointer();
    G4String SDname;
    auto EmCal = new EmCalSD(SDname="/EMcalorimeter");
    sdManager->AddNewDetector(EmCal);
    fPVT_LV_hrzn->SetSensitiveDetector(EmCal);
    fPVT_LV_vert->SetSensitiveDetector(EmCal);
}


