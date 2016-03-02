/*
  ==============================================================================

    CarSkid.h
    Created: 29 Feb 2016 1:59:52pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef CARSKID_H_INCLUDED
#define CARSKID_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class CarSkid{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/car/skid", &desc));
        ERRCHECK(desc->createInstance(&skid));
        ERRCHECK(skid->start());
    }
    void setSkid(double value){
        skid->getParameter("amount", &skidValue);
        skidValue->setValue(value);
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        skid->set3DAttributes(&car3D);
    }
private:
    EventInstance* skid;
    Studio::ParameterInstance* skidValue;
    
};




#endif  // CARSKID_H_INCLUDED
