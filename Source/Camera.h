/*
  ==============================================================================

    Camera.h
    Created: 2 Mar 2016 4:25:32pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;

class playerCamera{
public:
    void setVector(FMOD_3D_ATTRIBUTES attr3d, Studio::System* system, const Vector3* vector, String const& param){
        ERRCHECK (system->getListenerAttributes(FMOD_MAIN_LISTENER, &attr3d));
        if(param == "vel")  attr3d.velocity    =  *vector;
        if(param == "pos")  attr3d.position    =  *vector;
        if(param == "dir")  attr3d.forward     =  *vector;
        if(param == "up")   attr3d.up          =  *vector;
        ERRCHECK (system->setListenerAttributes(FMOD_MAIN_LISTENER, &attr3d));
    }
private:
    
};




#endif  // CAMERA_H_INCLUDED
