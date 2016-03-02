/*
  ==============================================================================

    Underbridge.h
    Created: 29 Feb 2016 9:56:34pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef UNDERBRIDGE_H_INCLUDED
#define UNDERBRIDGE_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class trackUnderbridge{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/reverbs/underbridge", &desc));
        ERRCHECK(desc->createInstance(&underbridge));
        ERRCHECK(underbridge->start());
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        underbridge->set3DAttributes(&car3D);
    }
    FMOD_3D_ATTRIBUTES getVector(){
        FMOD_3D_ATTRIBUTES attr3d;
        underbridge->get3DAttributes(&attr3d);
        return attr3d;
    }
private:
    EventInstance* underbridge;
    
};




#endif  // UNDERBRIDGE_H_INCLUDED
