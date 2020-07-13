#ifndef lensPhysicsList_h
#define lensPhysicsList_h

#include "G4VUserPhysicsList.hh"

#include "G4RunManager.hh"
#include "G4ProcessManager.hh"

#include "G4OpticalPhoton.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpAbsorption.hh"

#include "G4ParticleDefinition.hh"

class lensPhysicsList: public G4VUserPhysicsList
{
    public:
    lensPhysicsList();
    ~lensPhysicsList();

    protected:
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    virtual void SetCuts();
};

#endif