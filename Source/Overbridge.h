/*
  ==============================================================================

    Overbridge.h
    Created: 29 Feb 2016 9:56:29pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef OVERBRIDGE_H_INCLUDED
#define OVERBRIDGE_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class trackOverbridge{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/reverbs/overbridge", &desc));
        ERRCHECK(desc->createInstance(&overbridge));
        ERRCHECK(overbridge->start());
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        overbridge->set3DAttributes(&car3D);
    }
    FMOD_3D_ATTRIBUTES getVector(){
        FMOD_3D_ATTRIBUTES attr3d;
        overbridge->get3DAttributes(&attr3d);
        return attr3d;
    }
private:
    EventInstance* overbridge;
};



#endif  // OVERBRIDGE_H_INCLUDED
