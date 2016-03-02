/*
  ==============================================================================

    VectorHeader.h
    Created: 29 Feb 2016 2:43:25pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef VECTORHEADER_H_INCLUDED
#define VECTORHEADER_H_INCLUDED
#include "JuceHeaders.h"
#include "DataHeader.h"

using namespace FMOD::Studio;

class VectorData{
public:
    void setVector(FMOD_3D_ATTRIBUTES attr3d, EventInstance* eventInstance, Vector3* vector){
        if(param == "vel") car3D.velocity = *vector;
        if(param == "pos") car3D.position = *vector;
        if(param == "dir") car3D.forward = *vector;
        if(param == "up") car3D.up = *vector;
        eventInstance->set3DAttributes(&attr3d);
    }
private:
    int i;
};

#endif  // VECTORHEADER_H_INCLUDED
