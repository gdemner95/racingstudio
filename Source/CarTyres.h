/*
  ==============================================================================

    CarTyres.h
    Created: 29 Feb 2016 1:59:21pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef CARTYRES_H_INCLUDED
#define CARTYRES_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;

class CarTyres{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/car/tyres", &desc));
        ERRCHECK(desc->createInstance(&carTyres));
        ERRCHECK(carTyres->start());
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        carTyres->set3DAttributes(&car3D);
    }
    void setForce(double value){
        carTyres->getParameter("force", &forceValue);
        forceValue->setValue(value);
    }
    void setSpeed(double value){
        carTyres->getParameter("speed", &speedValue);
        speedValue->setValue(value);
    }
private:
    EventInstance* carTyres;
    Studio::ParameterInstance* forceValue;
    Studio::ParameterInstance* speedValue;
};



#endif  // CARTYRES_H_INCLUDED
