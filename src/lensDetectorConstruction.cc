#include "../inc/lensDetectorConstruction.hh"

//TODO: 1. multiply all detectors and grease volumes and place them where they belong, 2. consult on the PD window refraction index, 3. find a new way
        // to kill photons in the detector volume, 4. finish four pieces lens, 5. add lens-crystal air volume, 6. code main and other mandatory pieces of code
        // and compile to check geometry

//STATIC GEOMETRY DEFINITON BEGINING
G4double lensDetectorConstruction::world_x = 3.0*m, lensDetectorConstruction::world_y = 3.0*m, lensDetectorConstruction::world_z = 3.0*m;
G4double lensDetectorConstruction::crystal_x = 30.0*mm, lensDetectorConstruction::crystal_y = 30.0*mm, lensDetectorConstruction::crystal_z = 150.0*mm;
G4double lensDetectorConstruction::window_x = 2.5*mm,  lensDetectorConstruction::window_y = 2.5*mm, lensDetectorConstruction::window_z = 0.5*mm;
G4double lensDetectorConstruction::grease_x = 2.5*mm, lensDetectorConstruction::grease_y = 2.5*mm, lensDetectorConstruction::grease_z = 0.015*mm;
G4double lensDetectorConstruction::gap = 0.005*mm;
G4double lensDetectorConstruction::teflon_thickness = 0.2*mm;

G4TwoVector lensDetectorConstruction::main_solid_lens_1(17.5*mm, 27.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_2(27.5*mm, 17.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_3(27.5*mm, -17.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_4(17.5*mm, -27.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_5(-17.5*mm, -27.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_6(-27.5mm, -17.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_7(-27.5*mm, 17.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_8(-17.5*mm, 27.5*mm);
G4double lensDetectorConstruction::main_solid_lens_z = 4*mm;

G4ThreeVector lensDetectorConstruction::lens_punchhole_loaction_1(0*mm, 20*mm, 0*mm);
G4ThreeVector lensDetectorConstruction::lens_punchhole_loaction_2(22.5*mm, 0*mm, 0*mm);
G4ThreeVector lensDetectorConstruction::lens_punchhole_loaction_3(0*mm, -20*mm, 0*mm);
G4ThreeVector lensDetectorConstruction::lens_punchhole_loaction_4(-22.5*mm, 0*mm, 0*mm);
G4double lensDetectorConstruction::lens_punchhole_rad = 5*mm;
//STATIC GEOMETRY DEFINITION END

lensDetectorConstruction::lensDetectorConstruction():G4VUserDetectorConstruction()
{}

lensDetectorConstruction::~lensDetectorConstruction()
{}

G4VPhysicalVolume* lensDetectorConstruction::Construct()
{
    G4NistManager* nist_manager = G4NistManager::Instance();
    checkOverlaps = true;

    const G4int entries = 2;
    G4double photon_energy[entries] = {3.992*eV, 3.992*eV}; 

    //WORLD DESCRIPTION BEGINNING
    G4Box* solid_world = new G4Box("World", world_x, world_y, world_z);
    G4Material* air = nist_manager->FindOrBuildMaterial("G4_AIR");

    G4MaterialPropertiesTable* mp_table_air = new G4MaterialPropertiesTable();

    //possible another refractive indeces because of the energies!!!
    G4double air_refractive_index[entries] = {1.0003, 1.0003};
    mp_table_air->AddProperty("RINDEX", photon_energy, air_refractive_index, entries)->SetSpline(true);

    air->SetMaterialPropertiesTable(mp_table_air);

    G4LogicalVolume* logic_world = new G4LogicalVolume(solid_world, air, "World");
    G4VPhysicalVolume* phys_world = new G4PVPlacement (0, G4ThreeVector(), logic_world, "World", 0, false, 0, checkOverlaps);

    //WORLD DESCRIPTION END

    //CRYSTAL DESCRIPTION BEGINNING 

    G4Box *solid_crystal = new G4Box("Crystal", crystal_x, crystal_y, crystal_z);
    
    G4Element* el_Cs = nist_manager->FindOrBuildMaterial("G4_Cs");
    G4Element* el_I = nist_manager->FindorBuildMaterial("G4_I");

    G4Material* CsI = new G4Material ("CaesiumIodide", 4.51*g/cm3, 2);
    CsI->AddElement(el_Cs, 1);
    CsI->AddElement(el_I, 1);

    G4double crystal_refrative_index[entries] = {1.95, 1.95};
    G4double crystal_absorption_length[entries] = {4150*cm, 4150*cm};

    G4MaterialPropertiesTable* mp_table_crystal = new G4MaterialPropertiesTable();
    mp_table_crystal->AddProperty("RINDEX", photon_energy, crystal_refrative_index, entries)->SetSpline(true);
    mp_table_crystal->AddProperty("ABSLENGTH", photon_energy, crystal_absorption_length, entries)->SetSpline(true);

    CsI->SetMaterialPropertiesTable(mp_table_crystal);

    G4LogicalVolume* logic_crystal = new G4LogicalVolume(solid_crystal, CsI, "Crystal");
    G4VPhysicalVolume* phys_crystal = new G4PVPlacement(0, G4ThreeVector(), logic_crystal, "Crystal", logic_world, false, 0, checkOverlaps); 

    //CRYSTAL DESCRIPTION END

    //PD WINDOW DESCRIPTION BEGINNING

    G4Box* solid_window = new G4Box("Window", window_x, window_y, window_z);
    G4Element* elH = new G4Element("Hydrogen", "H", 1, 1.008*g/mole);
    G4Element* elC = new G4Element("Carbon", "C", 6, 12.011*g/mole);

    G4Material* epoxy_resin = new G4Material("EpoxyResin", 1.2*g/cm3, 2);
    epoxy_resin->AddElement(elH, 2);
    epoxy_resin->AddElement(elC, 2);

    G4double window_refractive_index[entries] = {1.56, 1.56};//find a new way to kill photons in the detector volume

    G4MaterialPropertiesTable* mp_table_window = new G4MaterialPropertiesTable();
    mp_table_window->AddProperty("RINDEX", photon_energy, window_refractive_index, entries)->SetSpline(true);
    mp_table_window->AddProperty("ABSLENGTH", photon_energy, window_absorption_length, entries)->SetSpline(true);

    epoxy_resin->SetMaterialPropertiesTable(mp_table_window);

    lgSensitiveDetector* sd_window = new lgSensitiveDetector("PhotoDiode", "lg_hits_collection");
    G4SDManager* sd_manager = G4SDManager::GetSDMpointer(); 
    sd_manager->AddNewDetector(sd_window);

    G4LogicalVolume* logic_window = new G4LogicalVolume(solid_window, epoxy_resin, "Window", 0, sd_window, 0, true);
    G4VPhysicalVolume* phys_window_1 = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + window_z * 0.5), logic_window, "Window", logic_world, false, 0, checkOverlaps);//we need three of these
    
    //PD WINDOW DESCRIPTION END

    //LENS DESCRIPTION BEGINNING
    std::vector<G4TwoVector> main_solid_lens_plane = { main_solid_lens_1, main_solid_lens_2, main_solid_lens_3, main_solid_lens_4,
                                                        main_solid_lens_5, main_solid_lens_6, main_solid_lens_7, main_solid_lens_8 };
    G4ExtrudedSoild* main_solid_lens = new G4ExtrudedSolid("MainSolidLens", main_solid_lens_plane, main_solid_lens_z); //possible that needs more arguments

    //flat lens
    G4Tubs* lens_punchhole = new G4Tubs("LensPunchHole", 0*mm, lens_punchole_rad, main_solid_lens_z, 0*rad, twopi); //possible problems with "twopi" constant

    G4UnionSolid* top_right_punchholes = new G4UnionSolid("TopRightPunchholes", lens_punchhole, lens_punchhole, 0, lens_punchhole_location_1 - lens_punchhole_location_2);
    G4UnionSolid* bottom_left_pucnhholes = new G4UnionSolid("BottomLeftPucnhholes", lens_punchhole, lens_punchhole, 0, lens_punchhole_location_4 - lens_punchhole_location_3);
    G4UnionSolid* flat_lens_punchholes = new G4UnionSolid("FlatLensPucnhholes", top_right_punchholes, bottom_left_pucnhholes, 0, lens_punchhole_location_4 + lens_punchhole_location_3);//Probably going to fail, prepare yourself

    G4SubtractionSolid* solid_flat_lens = new G4SubtractionSolid("FlatLens", main_solid_lens, flat_lens_punchholes, 0, G4ThreeVector());

    //four pieces lense


    //TEFLON DESCRIPTION BEGINNING

    //crystal teflon
    G4double subtr_box_teflon_x = crystal_x + gap + teflon_thickness, subtr_box_teflon_y = crystal_y + gap + teflon_thickness, subtr_box_teflon_z = crystal_z + gap * 0.5 + teflon_thickness;
    G4Box* subtr_box_teflon = new G4Box("SubtractionBoxTeflon", subtr_box_teflon_x, subtr_box_teflon_y, subtr_box_teflon_z);
    G4Box* mod_solid_crystal = new G4Box("IntersectionProblemSolver", crystal_x + gap, crystal_y + gap, crystal_z + gap * 0.5);

    G4ThreeVector subtr_box_teflon_trans(0.0, 0.0, teflon_thickness);
    G4SubtractionSolid* solid_teflon = new G4SubtractionSolid("Teflon", subtr_box_teflon, mod_solid_crystal, 0, subtr_box_teflon_trans);
    
    G4Material* teflon = nist_manager->FindOrBuildMaterial("G4_TEFLON");

    G4double teflon_refractive_index[entries] = {1.35, 1.35};

    G4MaterialPropertiesTable* mp_table_teflon = new G4MaterialPropertiesTable();
    mp_table_teflon->AddProperty("RINDEX", photon_energy, teflon_refractive_index, entries)->SetSpline(true);

    teflon->SetMaterialPropertiesTable(mp_table_teflon);

    G4LogicalVolume* logic_teflon = new G4LogicalVolume(solid_teflon, teflon, "Teflon");
    G4VPhysicalVolume* phys_teflon = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, teflon_thickness), logic_teflon, "Teflon", logic_world, false, 0, checkOverlaps);

    //lens teflon

    //TEFLON DESCRIPTION END

    //GREASE DESCRPTION BEGINNING

    G4Box* solid_grease = new G4Box("Grease", grease_x, grease_y, grease_z);

    G4LogicalVolume* logic_grease = new G4LogicalVolume(solid_grease, epoxy_resin, "EpoxyGrease");//there is a problem with no refraction on the grease-PD boundary
    G4VPhysicalVolume* phys_grease = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + grease_z), logic_grease, "EpoxyGrease", logic_world, false, 0, checkOverlaps);//we need three of these

    //GREASE DESCRIPTION END

    //LAYERS OF AIR BETWEEN CRYSTAL AND TEFLON

    G4Box* solid_back_air = new G4Box("BackAir", crystal_x, crystal_y, gap * 0.5);

    G4LogicalVolume* logic_back_air = new G4LogicalVolume(solid_back_air, air, "BackAir");
    G4VPhysicalVolume* phys_back_air = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -crystal_z - gap * 0.5), logic_back_air, "BackAir", logic_world, false, 0, checkOverlaps);

    G4Box* subtr_solid_side_air = new G4Box("SubtractionBoxSideAir", crystal_x + gap, crystal_y + gap, crystal_z);
    G4SubtractionSolid* solid_side_air = new G4SubtractionSolid("SideAir", subtr_solid_side_air, solid_crystal, 0, G4ThreeVector());

    G4LogicalVolume* logic_side_air = new G4LogicalVolume(solid_side_air, air, "SideAir");
    G4VPhysicalVolume* phys_side_air = new G4PVPlacement(0, G4ThreeVector(), logic_side_air, "SideAir", logic_world, false, 0, checkOverlaps); 

}