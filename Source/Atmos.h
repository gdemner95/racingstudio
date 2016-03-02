/*
  ==============================================================================

    Atmos.h
    Created: 29 Feb 2016 9:55:53pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef ATMOS_H_INCLUDED
#define ATMOS_H_INCLUDED
#include "JuceHeader.h"
#include "MasterObject.h"
using namespace FMOD::Studio;
class trackAtmos{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/enironments/atmos", &desc));
        ERRCHECK(desc->createInstance(&atmos));
        ERRCHECK(atmos->start());
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        atmos->set3DAttributes(&car3D);
    }
    FMOD_3D_ATTRIBUTES getVector(){
        FMOD_3D_ATTRIBUTES attr3d;
        atmos->get3DAttributes(&attr3d);
        return attr3d;
    }
private:
    EventInstance* atmos;
    
};

#endif  // ATMOS_H_INCLUDED
