/*
  ==============================================================================

    Crowd.h
    Created: 29 Feb 2016 9:56:08pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef CROWD_H_INCLUDED
#define CROWD_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class trackCrowd{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/environments/crowd", &desc));
        ERRCHECK(desc->createInstance(&crowd));
        ERRCHECK(crowd->start());
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        crowd->set3DAttributes(&car3D);
    }
    FMOD_3D_ATTRIBUTES getVector(){
        FMOD_3D_ATTRIBUTES attr3d;
        crowd->get3DAttributes(&attr3d);
        return attr3d;
    }
private:
    EventInstance* crowd;
    
};




#endif  // CROWD_H_INCLUDED
