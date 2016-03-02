/*
  ==============================================================================

    CarCrash.h
    Created: 29 Feb 2016 2:00:10pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef CARCRASH_H_INCLUDED
#define CARCRASH_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class CarCrash{
public:
    void handleHit(Studio::System* system, EventDescription* desc, double velocity){
        ERRCHECK(system->getEvent("event:/car/crash", &desc));
        ERRCHECK (desc->createInstance (&crashInstance));
        ERRCHECK(crashInstance->getParameter("intensity", &intensityParameter));
        intensityParameter->setValue(velocity);
        ERRCHECK (crashInstance->start());
        printf("%f\n", velocity);
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        crashInstance->set3DAttributes(&car3D);
    }
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/car/crash", &desc));
        ERRCHECK(desc->createInstance(&crashInstance));
    }
private:
//    Studio::System* system;
    EventInstance* crashInstance;
    Studio::ParameterInstance* intensityParameter;
};




#endif  // CARCRASH_H_INCLUDED
