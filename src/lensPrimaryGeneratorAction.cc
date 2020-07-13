#include "../inc/lensPrimaryGeneratorAction.hh"

lensPrimaryGeneratorAction::lensPrimaryGeneratorAction():G4VUserPrimaryGeneratorAction()
{
//     G4int n_of_particles = 1;
//     particle_gun = new G4ParticleGun(n_of_particles);

//     G4double particle_energy = 2.578*eV;

//     G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("opticalphoton");

//     particle_gun->SetParticleDefinition(particle);
//     particle_gun->SetParticleEnergy(particle_energy);
}

lensPrimaryGeneratorAction::~lensPrimaryGeneratorAction()
{
   // delete particle_gun;
}

void lensPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{

}