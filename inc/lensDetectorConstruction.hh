#ifndef lensDetectorConstruction_h
#define lensDetectorConstruction_h

#include "lensSensitiveDetector.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4ExtrudedSolid.hh"

#include "G4PhysicalConstants.h"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

#include <vector>

class G4LogicalVolume;
class G4PhysicalVolume;

class lensDetectorConstruction: public G4VUserDetectorConstruction
{
    public:
    lensDetectorConstruction();
    virtual ~lensDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    static std::vector<G4double> get_crystal_dimensions();

    static G4double world_x, world_y, world_z;
    static G4double crystal_x, crystal_y, crystal_z;
    static G4double window_x,  window_y, window_z;
    static G4double grease_x, grease_y, grease_z;

    static G4TwoVector main_solid_lens_1;
    static G4TwoVector main_solid_lens_2;
    static G4TwoVector main_solid_lens_3;
    static G4TwoVector main_solid_lens_4;
    static G4TwoVector main_solid_lens_5;
    static G4TwoVector main_solid_lens_6;
    static G4TwoVector main_solid_lens_7;
    static G4TwoVector main_solid_lens_8;
    static G4double main_solid_lens_z;

    static G4ThreeVector lens_punchhole_location_1;
    static G4ThreeVector lens_punchhole_location_2;
    static G4ThreeVector lens_punchhole_location_3;
    static G4ThreeVector lens_punchhole_location_4;
    static G4double lens_punchhole_rad;

    static G4double gap;
    static G4double teflon_thickness;
    G4bool checkOverlaps;
};

#endif
