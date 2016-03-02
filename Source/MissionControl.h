/*
  ==============================================================================

    MissionControl.h
    Created: 29 Feb 2016 9:56:16pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef MISSIONCONTROL_H_INCLUDED
#define MISSIONCONTROL_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class trackMc{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/reverbs/missioncontrol", &desc));
        ERRCHECK(desc->createInstance(&missioncontrol));
        ERRCHECK(missioncontrol->start());
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        missioncontrol->set3DAttributes(&car3D);
    }
    FMOD_3D_ATTRIBUTES getVector(){
        FMOD_3D_ATTRIBUTES attr3d;
        missioncontrol->get3DAttributes(&attr3d);
        return attr3d;
    }
private:
    EventInstance* missioncontrol;
    Studio::ParameterInstance* skidValue;
    
};




#endif  // MISSIONCONTROL_H_INCLUDED
