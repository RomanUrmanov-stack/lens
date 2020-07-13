#include "../inc/lensDetectorConstruction.hh"

//TODO: 1. find a new way to kill photons in the detector volume, 2. finish four pieces lens,  (diffusal reflection in lens is about 2.5 percent)
        // 3. ask about screwers in the lens, 4. optical surfaces, 5. start other parts of the project

//STATIC GEOMETRY DEFINITON BEGINING
G4double lensDetectorConstruction::world_x = 3.0*m, lensDetectorConstruction::world_y = 3.0*m, lensDetectorConstruction::world_z = 3.0*m;
G4double lensDetectorConstruction::crystal_x = 30.0*mm, lensDetectorConstruction::crystal_y = 30.0*mm, lensDetectorConstruction::crystal_z = 150.0*mm;
G4double lensDetectorConstruction::window_x = 2.5*mm,  lensDetectorConstruction::window_y = 2.5*mm, lensDetectorConstruction::window_z = 0.5*mm;
G4double lensDetectorConstruction::grease_x = 2.5*mm, lensDetectorConstruction::grease_y = 2.5*mm, lensDetectorConstruction::grease_z = 0.015*mm;
G4double lensDetectorConstruction::gap = 0.005*mm;
G4double lensDetectorConstruction::teflon_thickness = 0.2*mm;
G4double lensDetectorConstruction::pt_thickness = 0.03*mm;
G4double lensDetectorConstruction::al_thickness = 0.02*mm;

G4TwoVector lensDetectorConstruction::main_solid_lens_1(17.5*mm, 27.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_2(27.5*mm, 17.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_3(27.5*mm, -17.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_4(17.5*mm, -27.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_5(-17.5*mm, -27.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_6(-27.5*mm, -17.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_7(-27.5*mm, 17.5*mm);
G4TwoVector lensDetectorConstruction::main_solid_lens_8(-17.5*mm, 27.5*mm);
G4double lensDetectorConstruction::main_solid_lens_z = 4*mm;

G4ThreeVector lensDetectorConstruction::lens_punchhole_location_1(0*mm, 20*mm, 0*mm);
G4ThreeVector lensDetectorConstruction::lens_punchhole_location_2(22.5*mm, 0*mm, 0*mm);
G4ThreeVector lensDetectorConstruction::lens_punchhole_location_3(0*mm, -20*mm, 0*mm);
G4ThreeVector lensDetectorConstruction::lens_punchhole_location_4(-22.5*mm, 0*mm, 0*mm);
G4double lensDetectorConstruction::lens_punchhole_rad = 2.5*mm;
////STATIC GEOMETRY DEFINITION END

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

    G4double air_refractive_index[entries] = {1.0003, 1.0003};
    mp_table_air->AddProperty("RINDEX", photon_energy, air_refractive_index, entries)->SetSpline(true);

    air->SetMaterialPropertiesTable(mp_table_air);

    G4LogicalVolume* logic_world = new G4LogicalVolume(solid_world, air, "World");
    G4VPhysicalVolume* phys_world = new G4PVPlacement (0, G4ThreeVector(), logic_world, "World", 0, false, 0, checkOverlaps);

    //WORLD DESCRIPTION END

    //CRYSTAL DESCRIPTION BEGINNING 

    G4Box *solid_crystal = new G4Box("Crystal", crystal_x, crystal_y, crystal_z);
    
    G4Element* el_Cs = new G4Element("Caesium", "Cs", 55., 132.9*g/mole);
    G4Element* el_I = new G4Element("Iodine", "I", 53., 126.9*g/mole);

    G4Material* CsI = new G4Material("CaesiumIodide", 4.51*g/cm3, 2);
    CsI->AddElement(el_Cs, 1);
    CsI->AddElement(el_I, 1);

    G4double crystal_refrative_index[entries] = {1.95, 1.95};
    G4double crystal_absorption_length[entries] = {2000*cm, 2000*cm};//1500-2000 cm

    G4MaterialPropertiesTable* mp_table_crystal = new G4MaterialPropertiesTable();
    mp_table_crystal->AddProperty("RINDEX", photon_energy, crystal_refrative_index, entries)->SetSpline(true);
    mp_table_crystal->AddProperty("ABSLENGTH", photon_energy, crystal_absorption_length, entries)->SetSpline(true);

    CsI->SetMaterialPropertiesTable(mp_table_crystal);

    G4LogicalVolume* logic_crystal = new G4LogicalVolume(solid_crystal, CsI, "Crystal");
    G4VPhysicalVolume* phys_crystal = new G4PVPlacement(0, G4ThreeVector(), logic_crystal, "Crystal", logic_world, false, 0, checkOverlaps); 

    //CRYSTAL DESCRIPTION END

    //PD WINDOW DESCRIPTION BEGINNING

    G4Box* solid_window = new G4Box("Window", window_x, window_y, window_z);
    G4Element* el_H = new G4Element("Hydrogen", "H", 1, 1.008*g/mole);
    G4Element* el_C = new G4Element("Carbon", "C", 6, 12.011*g/mole);

    G4Material* epoxy_resin = new G4Material("EpoxyResin", 1.2*g/cm3, 2);
    epoxy_resin->AddElement(el_H, 2);
    epoxy_resin->AddElement(el_C, 2);

    G4double window_refractive_index[entries] = {1.56, 1.56};

    G4MaterialPropertiesTable* mp_table_window = new G4MaterialPropertiesTable();
    mp_table_window->AddProperty("RINDEX", photon_energy, window_refractive_index, entries)->SetSpline(true);

    epoxy_resin->SetMaterialPropertiesTable(mp_table_window);

    //lgSensitiveDetector* sd_window = new lgSensitiveDetector("PhotoDiode", "lg_hits_collection");
    //G4SDManager* sd_manager = G4SDManager::GetSDMpointer(); 
    //sd_manager->AddNewDetector(sd_window);

    G4RotationMatrix* pd_rot_mat_1 = new G4RotationMatrix();
    pd_rot_mat_1->rotateY(0.5 * pi *rad);
    pd_rot_mat_1->rotateX(0.25 * pi*rad);

    G4RotationMatrix* pd_rot_mat_2 = new G4RotationMatrix();
    pd_rot_mat_2->rotateY(0.5 * pi*rad);
    pd_rot_mat_2->rotateX(0.75 * pi*rad);
    
    G4LogicalVolume* logic_window = new G4LogicalVolume(solid_window, epoxy_resin, "Window");
    G4VPhysicalVolume* phys_window_1 = new G4PVPlacement(pd_rot_mat_1, G4ThreeVector(-22.5*mm - grease_z * sqrt(2) - window_z/sqrt(2), 22.5*mm + grease_z * sqrt(2) + window_z/sqrt(2), crystal_z + main_solid_lens_z + gap), logic_window, "Window_1", logic_world, false, 0, checkOverlaps);
    G4VPhysicalVolume* phys_window_2 = new G4PVPlacement(pd_rot_mat_2, G4ThreeVector(22.5*mm + grease_z * sqrt(2) + window_z/sqrt(2), 22.5*mm + grease_z * sqrt(2) + window_z/sqrt(2), crystal_z + main_solid_lens_z + gap), logic_window, "Window_2", logic_world, false, 0, checkOverlaps);
    G4VPhysicalVolume* phys_window_3 = new G4PVPlacement(pd_rot_mat_1, G4ThreeVector(22.5*mm + grease_z * sqrt(2) + window_z/sqrt(2), -22.5*mm - grease_z * sqrt(2) - window_z/sqrt(2), crystal_z + main_solid_lens_z + gap), logic_window, "Window_3", logic_world, false, 0, checkOverlaps);
    G4VPhysicalVolume* phys_window_4 = new G4PVPlacement(pd_rot_mat_2, G4ThreeVector(-22.5*mm - grease_z * sqrt(2) - window_z/sqrt(2), -22.5*mm - grease_z * sqrt(2) - window_z/sqrt(2), crystal_z + main_solid_lens_z + gap), logic_window, "Window_4", logic_world, false, 0, checkOverlaps);
    
    //PD WINDOW DESCRIPTION END

    //LENS DESCRIPTION BEGINNING
    std::vector<G4TwoVector> main_solid_lens_plane = { main_solid_lens_1, main_solid_lens_2, main_solid_lens_3, main_solid_lens_4,
                                                        main_solid_lens_5, main_solid_lens_6, main_solid_lens_7, main_solid_lens_8 };
    G4ExtrudedSolid* main_solid_lens = new G4ExtrudedSolid("MainSolidLens", main_solid_lens_plane, main_solid_lens_z, 0, 1, 0, 1);

    G4Material* plexiglass = nist_manager->FindOrBuildMaterial("G4_PLEXIGLASS");
    G4MaterialPropertiesTable* mp_table_plexiglass = new G4MaterialPropertiesTable();

    G4double plexiglass_refrative_index[entries] = { 1.489, 1.489 };
    G4double plexiglass_absorption_length[entries] = { 2000*cm, 2000*cm };
    mp_table_plexiglass->AddProperty("RINDEX", photon_energy, plexiglass_refrative_index, entries)->SetSpline(true);
    mp_table_plexiglass->AddProperty("ABSLENGTH", photon_energy, plexiglass_absorption_length, entries)->SetSpline(true);

    plexiglass->SetMaterialPropertiesTable(mp_table_plexiglass); 

    //flat lens
    G4Tubs* lens_punchhole = new G4Tubs("LensPunchHole", 0*mm, lens_punchhole_rad, main_solid_lens_z * 1.1, 0*rad, 2 * pi*rad); 

    G4UnionSolid* top_right_punchholes = new G4UnionSolid("TopRightPunchholes", lens_punchhole, lens_punchhole, 0, lens_punchhole_location_1 - lens_punchhole_location_2);
    G4UnionSolid* bottom_left_pucnhholes = new G4UnionSolid("BottomLeftPucnhholes", lens_punchhole, lens_punchhole, 0, lens_punchhole_location_4 - lens_punchhole_location_3);
    G4UnionSolid* flat_lens_punchholes = new G4UnionSolid("FlatLensPucnhholes", top_right_punchholes, bottom_left_pucnhholes, 0, lens_punchhole_location_4 + lens_punchhole_location_3);

    G4SubtractionSolid* solid_flat_lens = new G4SubtractionSolid("FlatLens", main_solid_lens, flat_lens_punchholes, 0, G4ThreeVector(22.5*mm, 0.0, 0.0));

    G4LogicalVolume* logic_flat_lens = new G4LogicalVolume(solid_flat_lens, plexiglass, "FlatLens");
    G4VPhysicalVolume* phys_flat_lens = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + main_solid_lens_z + gap), logic_flat_lens, "FlatLens", logic_world, false, 0, checkOverlaps);
    //four pieces lense

    //GREASE DESCRPTION BEGINNING

    G4Box* solid_grease = new G4Box("EpoxyGrease", grease_x, grease_y, grease_z);
    G4MultiUnion* union_grease = new G4MultiUnion("UnionGrease");

    G4RotationMatrix* grease_rot_mat_1 = new G4RotationMatrix();
    grease_rot_mat_1->rotateY(0.5 * pi*rad);
    grease_rot_mat_1->rotateZ(0.75 * pi*rad);

    G4RotationMatrix* grease_rot_mat_2 = new G4RotationMatrix();
    grease_rot_mat_2->rotateY(0.5 * pi*rad);
    grease_rot_mat_2->rotateZ(0.25 * pi*rad);

    G4Transform3D grease_trans_1 = G4Transform3D(*grease_rot_mat_1, G4ThreeVector(-22.5*mm - grease_z/sqrt(2), 22.5 + grease_z/sqrt(2), 0.0));
    G4Transform3D grease_trans_2 = G4Transform3D(*grease_rot_mat_2, G4ThreeVector(22.5*mm + grease_z/sqrt(2), 22.5 + grease_z/sqrt(2), 0.0));
    G4Transform3D grease_trans_3 = G4Transform3D(*grease_rot_mat_1, G4ThreeVector(22.5*mm + grease_z/sqrt(2), -22.5 - grease_z/sqrt(2), 0.0));
    G4Transform3D grease_trans_4 = G4Transform3D(*grease_rot_mat_2, G4ThreeVector(-22.5*mm - grease_z/sqrt(2), -22.5 - grease_z/sqrt(2), 0.0));

    union_grease->AddNode(*solid_grease, grease_trans_1);
    union_grease->AddNode(*solid_grease, grease_trans_2);
    union_grease->AddNode(*solid_grease, grease_trans_3);
    union_grease->AddNode(*solid_grease, grease_trans_4);

    union_grease->Voxelize();

    G4LogicalVolume* logic_union_grease = new G4LogicalVolume(union_grease, epoxy_resin, "UnionGrease");
    G4VPhysicalVolume* phys_union_grease = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + main_solid_lens_z + gap), logic_union_grease, "UnionGrease", logic_world, false, 0, checkOverlaps);

    //GREASE DESCRIPTION END

    //necessary dummy union
    G4MultiUnion* top_hat_union = new G4MultiUnion("TopHatUnion");
    G4Transform3D hat_trans = G4Transform3D(G4RotationMatrix(), G4ThreeVector());

    top_hat_union->AddNode(*union_grease, hat_trans);
    top_hat_union->AddNode(*main_solid_lens, hat_trans);

    top_hat_union->Voxelize();

    //LAYERS OF AIR (except the top ones)

    //between crystal and teflon
    G4Box* solid_back_air = new G4Box("BackAir", crystal_x, crystal_y, gap * 0.5);

    G4LogicalVolume* logic_back_air = new G4LogicalVolume(solid_back_air, air, "BackAir");
    G4VPhysicalVolume* phys_back_air = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -crystal_z - gap * 0.5), logic_back_air, "BackAir", logic_world, false, 0, checkOverlaps);

    G4Box* subtr_solid_side_air = new G4Box("SubtractionBoxSideAir", crystal_x + gap, crystal_y + gap, crystal_z);
    G4SubtractionSolid* solid_side_air = new G4SubtractionSolid("SideAir", subtr_solid_side_air, solid_crystal, 0, G4ThreeVector());

    G4LogicalVolume* logic_side_air = new G4LogicalVolume(solid_side_air, air, "SideAir");
    G4VPhysicalVolume* phys_side_air = new G4PVPlacement(0, G4ThreeVector(), logic_side_air, "SideAir", logic_world, false, 0, checkOverlaps); 

    //between crystal and lens
    G4LogicalVolume* logic_front_air = new G4LogicalVolume(solid_back_air, air, "FrontAir");
    G4VPhysicalVolume* phys_front_air = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + gap * 0.5), logic_front_air, "FrontAir", logic_world, false, 0, checkOverlaps);

    //between lens and teflon
    std::vector<G4TwoVector> lens_air_dummy_plane = { main_solid_lens_1 + G4TwoVector(0.0, gap), main_solid_lens_2 + G4TwoVector(gap, 0.0),
                                                      main_solid_lens_3 + G4TwoVector(gap, 0.0), main_solid_lens_4 - G4TwoVector(0.0, gap),
                                                      main_solid_lens_5 - G4TwoVector(0.0, gap), main_solid_lens_6 - G4TwoVector(gap, 0.0),
                                                      main_solid_lens_7 - G4TwoVector(gap, 0.0), main_solid_lens_8 + G4TwoVector(0.0, gap) };
    G4ExtrudedSolid* solid_lens_air_dummy = new G4ExtrudedSolid("LensAirDummy", lens_air_dummy_plane, main_solid_lens_z + gap * 0.5, 0, 1, 0, 1);

    G4SubtractionSolid* solid_lens_air = new G4SubtractionSolid("LensAir", solid_lens_air_dummy, top_hat_union, 0, G4ThreeVector(0.0, 0.0, -gap * 0.5));

    G4LogicalVolume* logic_lens_air = new G4LogicalVolume(solid_lens_air, air, "LensAirDummy");
    G4VPhysicalVolume* phys_lens_air = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + main_solid_lens_z + gap * 1.5), logic_lens_air, "LensAirDummy", logic_world, false, 0, checkOverlaps);

    //between teflon and pt
    G4LogicalVolume* logic_air_pt_teflon_back = new G4LogicalVolume(solid_back_air, air, "BackAirTeflonPT");
    G4VPhysicalVolume* phys_air_tp_teflon_back = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -crystal_z - gap * 1.5 - teflon_thickness), logic_air_pt_teflon_back, "BackAirTeflonPT", logic_world, false, 0 ,checkOverlaps); 

    G4Box* subtr_solid_air_pt_side = new G4Box("SubtractionBoxTeflonPTSide", crystal_x + 2 * gap + teflon_thickness, crystal_y + 2 * gap + teflon_thickness, crystal_z);
    G4Box* mod_crystal_pt_air = new G4Box("ModCrystalPTAir", crystal_x + gap + teflon_thickness, crystal_y + gap + teflon_thickness, crystal_z);
    G4SubtractionSolid* solid_air_pt_teflon_side = new G4SubtractionSolid("SubtractionBoxTeflonPTSide", subtr_solid_air_pt_side, mod_crystal_pt_air, 0, G4ThreeVector());

    G4LogicalVolume* logic_air_pt_teflon_side = new G4LogicalVolume(solid_air_pt_teflon_side, air, "AirPTTeflonSide");
    G4VPhysicalVolume* phys_air_pt_teflon_side = new G4PVPlacement(0, G4ThreeVector(), logic_air_pt_teflon_side, "AirPTTeflonSide", logic_world, false, checkOverlaps);

    //between pt and al
    G4LogicalVolume* logic_air_pt_al_back = new G4LogicalVolume(solid_back_air, air, "BackAirAlPT");
    G4VPhysicalVolume* phys_air_pt_al_back = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -crystal_z - gap * 2.5 - teflon_thickness - pt_thickness), logic_air_pt_al_back, "BackAirAlPT", logic_world, false, 0 ,checkOverlaps); 

    //TEFLON DESCRIPTION BEGINNING

    //crystal teflon
    G4Material* teflon = nist_manager->FindOrBuildMaterial("G4_TEFLON");

    G4double teflon_refractive_index[entries] = {1.35, 1.35};

    G4MaterialPropertiesTable* mp_table_teflon = new G4MaterialPropertiesTable();
    mp_table_teflon->AddProperty("RINDEX", photon_energy, teflon_refractive_index, entries)->SetSpline(true);

    teflon->SetMaterialPropertiesTable(mp_table_teflon);

    //side crystal teflon
    G4double subtr_box_teflon_x = crystal_x + gap + teflon_thickness, subtr_box_teflon_y = crystal_y + gap + teflon_thickness, subtr_box_teflon_z = crystal_z + gap * 0.5 + teflon_thickness * 0.5;
    G4Box* subtr_box_teflon_side = new G4Box("SubtractionBoxTeflon", subtr_box_teflon_x, subtr_box_teflon_y, subtr_box_teflon_z);
    G4Box* mod_solid_crystal_teflon = new G4Box("IntersectionProblemSolver", crystal_x + gap, crystal_y + gap, crystal_z + gap * 0.5);

    G4ThreeVector subtr_box_teflon_trans(0.0, 0.0, teflon_thickness * 0.5);
    G4SubtractionSolid* solid_teflon_side = new G4SubtractionSolid("CrystalTeflon", subtr_box_teflon_side, mod_solid_crystal_teflon, 0, subtr_box_teflon_trans);

    G4LogicalVolume* logic_teflon_side = new G4LogicalVolume(solid_teflon_side, teflon, "TeflonSide");
    G4VPhysicalVolume* phys_teflon_side = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -teflon_thickness * 0.5 - gap * 0.5), logic_teflon_side, "TeflonSide", logic_world, false, 0, checkOverlaps);

    //flat lens teflon
    G4MultiUnion* subtr_lens_air_teflon_dummy = new G4MultiUnion("SubtrLensTeflonDummy");

    G4Transform3D lens_air_trans = G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.0, 0.0, gap * 0.5)); 
    G4Transform3D window_1_trans = G4Transform3D(*grease_rot_mat_1, G4ThreeVector(-22.5*mm - grease_z * sqrt(2) - window_z/sqrt(2), 22.5*mm + grease_z * sqrt(2) + window_z/sqrt(2), 0.0));
    G4Transform3D window_2_trans = G4Transform3D(*grease_rot_mat_2, G4ThreeVector(22.5*mm + grease_z * sqrt(2) + window_z/sqrt(2), 22.5*mm + grease_z * sqrt(2) + window_z/sqrt(2), 0.0));
    G4Transform3D window_3_trans = G4Transform3D(*grease_rot_mat_1, G4ThreeVector(22.5*mm + grease_z * sqrt(2) + window_z/sqrt(2), -22.5*mm - grease_z * sqrt(2) - window_z/sqrt(2), 0.0));
    G4Transform3D window_4_trans = G4Transform3D(*grease_rot_mat_2, G4ThreeVector(-22.5*mm - grease_z * sqrt(2) - window_z/sqrt(2), -22.5*mm - grease_z * sqrt(2) - window_z/sqrt(2), 0.0));

    subtr_lens_air_teflon_dummy->AddNode(*top_hat_union, hat_trans);
    subtr_lens_air_teflon_dummy->AddNode(*solid_lens_air, lens_air_trans);
    subtr_lens_air_teflon_dummy->AddNode(*solid_window, window_1_trans);
    subtr_lens_air_teflon_dummy->AddNode(*solid_window, window_2_trans);
    subtr_lens_air_teflon_dummy->AddNode(*solid_window, window_3_trans);
    subtr_lens_air_teflon_dummy->AddNode(*solid_window, window_4_trans);

    subtr_lens_air_teflon_dummy->Voxelize();

    std::vector<G4TwoVector> lens_teflon_dummy_plane = { main_solid_lens_1 + G4TwoVector(0.0, gap + teflon_thickness), main_solid_lens_2 + G4TwoVector(gap + teflon_thickness, 0.0),
                                                         main_solid_lens_3 + G4TwoVector(gap + teflon_thickness, 0.0), main_solid_lens_4 - G4TwoVector(0.0, gap + teflon_thickness),
                                                         main_solid_lens_5 - G4TwoVector(0.0, gap + teflon_thickness), main_solid_lens_6 - G4TwoVector(gap + teflon_thickness, 0.0),
                                                         main_solid_lens_7 - G4TwoVector(gap + teflon_thickness, 0.0), main_solid_lens_8 + G4TwoVector(0.0, gap + teflon_thickness) };
    G4ExtrudedSolid* solid_lens_teflon_dummy = new G4ExtrudedSolid("LensTeflonDummy", lens_teflon_dummy_plane, main_solid_lens_z + gap * 0.5 + teflon_thickness * 0.5, 0, 1, 0, 1);

    G4SubtractionSolid* solid_lens_teflon = new G4SubtractionSolid("LensTeflon", solid_lens_teflon_dummy, subtr_lens_air_teflon_dummy, 0, G4ThreeVector(0.0, 0.0, -gap * 0.5 - teflon_thickness * 0.5));

    G4LogicalVolume* logic_lens_teflon = new G4LogicalVolume(solid_lens_teflon, teflon, "LensTeflon");
    G4VPhysicalVolume* phys_lens_teflon = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + main_solid_lens_z + gap * 1.5 + teflon_thickness * 0.5), logic_lens_teflon, "LensTeflon", logic_world, false, 0, checkOverlaps);

    //top crystal teflon
    G4Box* top_teflon_subtr = new G4Box("TopSubtrTeflon", crystal_x, crystal_y, teflon_thickness * 0.5);
    G4SubtractionSolid* solid_teflon_top = new G4SubtractionSolid("TopCrystal_teflon", top_teflon_subtr, solid_lens_teflon_dummy, 0, G4ThreeVector());

    G4LogicalVolume* logic_teflon_top = new G4LogicalVolume(solid_teflon_top, teflon, "TeflonTop");
    G4VPhysicalVolume* pysh_teflon_top = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + gap + teflon_thickness * 0.5), logic_teflon_top, "TeflonTop", logic_world, false, 0, checkOverlaps);

    //TEFLON DESCRIPTION END

    //TOP LAYERS OF AIR
    G4Box* top_air_teflon_pt_subtr = new G4Box("TopAirTeflonPT", crystal_x, crystal_y, gap * 0.5);
    G4SubtractionSolid* solid_top_air_teflon_pt = new G4SubtractionSolid("TopAirTeflonPT", top_air_teflon_pt_subtr, solid_lens_teflon_dummy, 0, G4ThreeVector());

    G4LogicalVolume* logic_air_pt_teflon_top = new G4LogicalVolume(solid_top_air_teflon_pt, air, "AirPtTeflonTop");
    G4VPhysicalVolume* phys_air_pt_teflon_top = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + gap * 1.5 + teflon_thickness), logic_air_pt_teflon_top, "AirPtTeflonTop", logic_world, false, checkOverlaps);

    G4Box* top_air_pt_al_subtr = new G4Box("TopAirptAl", crystal_x, crystal_y, gap * 0.5);
    G4SubtractionSolid* solid_top_air_pt_al = new G4SubtractionSolid("TopAirptAl", top_air_pt_al_subtr, solid_lens_teflon_dummy, 0, G4ThreeVector());

    G4LogicalVolume* logic_air_al_pt_top = new G4LogicalVolume(solid_top_air_pt_al, air, "AirAlPTTop");
    G4VPhysicalVolume* phys_air_al_pt_top = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + gap * 2.5 + teflon_thickness + pt_thickness), logic_air_al_pt_top, "AirAlPTTop", logic_world, false, checkOverlaps);

    //POLYETHYLENE TEREPHTHALATE DESCRIPTION BEGINNING

    G4Element* el_O = new G4Element("Oxygen", "O", 8, 15.999*g/mole);
    G4Material* pt = new G4Material("Polyethylene terephthalate", 1.38*g/cm3, 22);

    pt->AddElement(el_C, 10);
    pt->AddElement(el_H, 8);
    pt->AddElement(el_O, 4);

    G4double pt_refractive_index[entries] = { 1.57, 1.57 };
    G4MaterialPropertiesTable* mp_table_pt = new G4MaterialPropertiesTable();

    mp_table_pt->AddProperty("RINDEX", photon_energy, pt_refractive_index, entries)->SetSpline(true);

    //side pt
    G4double subtr_box_pt_x = crystal_x + gap * 2 + teflon_thickness + pt_thickness, subtr_box_pt_y = crystal_y + gap * 2 + teflon_thickness + pt_thickness, subtr_box_pt_z = crystal_z + gap + teflon_thickness * 0.5 + pt_thickness * 0.5;
    G4Box* subtr_box_pt_side = new G4Box("SubtrBoxPTSide", subtr_box_pt_x, subtr_box_pt_y, subtr_box_pt_z);
    G4Box* mod_solid_crystal_pt = new G4Box("IntersectionProblemSolverPT", crystal_x + gap * 2 + teflon_thickness, crystal_y + gap * 2 + teflon_thickness, crystal_z + gap + teflon_thickness * 0.5);

    G4ThreeVector subtr_box_pt_trans = G4ThreeVector(0.0, 0.0, pt_thickness * 0.5);
    G4SubtractionSolid* solid_pt_side = new G4SubtractionSolid("SidePT", subtr_box_pt_side, mod_solid_crystal_pt, 0, subtr_box_pt_trans);

    G4LogicalVolume* logic_pt_side = new G4LogicalVolume(solid_pt_side, pt, "SidePT");
    G4VPhysicalVolume* phys_pt_side = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -pt_thickness * 0.5 - gap - teflon_thickness * 0.5), logic_pt_side, "PTSide", logic_world, false, 0, checkOverlaps);

    //top pt
    G4Box* subtr_box_pt_top = new G4Box("TopPT", crystal_x, crystal_y, pt_thickness * 0.5);
    G4SubtractionSolid* solid_pt_top = new G4SubtractionSolid("TopPT", subtr_box_pt_top, solid_lens_teflon_dummy, 0, G4ThreeVector());

    G4LogicalVolume* logic_pt_top = new G4LogicalVolume(solid_pt_top, pt, "PTTop");
    G4VPhysicalVolume* phys_pt_top = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + 2 * gap + teflon_thickness + pt_thickness * 0.5), logic_pt_top, "PTTop", logic_world, false, 0, checkOverlaps); 

    //POLYETHYLENE TEREPHTHALATE DESCRIPTION END

    //ALUMINIUM DESCRIPTION BEGINNING

    G4Material* al = nist_manager->FindOrBuildMaterial("G4_Al");

    G4double al_refraction_index[entries] = { 0.28, 0.96 };

    G4MaterialPropertiesTable* mp_table_al = new G4MaterialPropertiesTable();
    mp_table_al->AddProperty("RINDEX", photon_energy, al_refraction_index, entries)->SetSpline(true);

    //side al
    G4double subtr_box_al_x = crystal_x + gap * 3 + teflon_thickness + pt_thickness + al_thickness, subtr_box_al_y = crystal_y + gap * 3 + teflon_thickness + pt_thickness + al_thickness, subtr_box_al_z = crystal_z + gap * 1.5 + teflon_thickness * 0.5 + pt_thickness * 0.5 + al_thickness * 0.5;
    G4Box* subtr_box_al_side = new G4Box("SubtrBoxAlSide", subtr_box_al_x, subtr_box_al_y, subtr_box_al_z);
    G4Box* mod_solid_crystal_al = new G4Box("IntersectionProblemSolverAl", crystal_x + gap * 3 + teflon_thickness + pt_thickness, crystal_y + gap * 3 + teflon_thickness + pt_thickness, crystal_z + gap * 1.5 + teflon_thickness * 0.5 + pt_thickness * 0.5);

    G4ThreeVector subtr_box_al_trans = G4ThreeVector(0.0, 0.0, al_thickness * 0.5);
    G4SubtractionSolid* solid_al_side = new G4SubtractionSolid("SideAl", subtr_box_al_side, mod_solid_crystal_al, 0, subtr_box_al_trans);

    G4LogicalVolume* logic_al_side = new G4LogicalVolume(solid_al_side, al, "SideAl");
    G4VPhysicalVolume* phys_al_side = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -gap * 1.5 - teflon_thickness * 0.5 - pt_thickness * 0.5 - al_thickness * 0.5 + 0.001*mm), logic_al_side, "AlSide", logic_world, false, 0, checkOverlaps);

    //top al
    G4Box* subtr_box_al_top = new G4Box("TopAl", crystal_x, crystal_y, al_thickness * 0.5);
    G4SubtractionSolid* solid_al_top = new G4SubtractionSolid("TopAl", subtr_box_al_top, solid_lens_teflon_dummy, 0, G4ThreeVector());

    G4LogicalVolume* logic_al_top = new G4LogicalVolume(solid_al_top, al, "AlTop");
    G4VPhysicalVolume* phys_al_top = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + gap * 3 + teflon_thickness + pt_thickness + al_thickness * 0.5), logic_al_top, "AlTop", logic_world, false, 0, checkOverlaps); 

    //ALUMUNIUM DESCRIPTION END

    return phys_world;
}