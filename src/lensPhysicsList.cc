#include "lensPhysicsList.hh"

lensPhysicsList::lensPhysicsList():G4VUserPhysicsList()
{}

lensPhysicsList::~lensPhysicsList()
{}

void lensPhysicsList::ConstructParticle()
{
   // G4OpticalPhoton::Definition();
}

void lensPhysicsList::ConstructProcess()
{
   // AddTransportation();
}

void lensPhysicsList::SetCuts()
{
   // SetCutsWithDefault();
}