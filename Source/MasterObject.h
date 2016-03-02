/*
  ==============================================================================

    MasterObject.h
    Created: 2 Mar 2016 11:52:18am
    Author:  George Demner

  ==============================================================================
*/

#ifndef MASTEROBJECT_H_INCLUDED
#define MASTEROBJECT_H_INCLUDED
#include "JuceHeader.h"
#include "Descriptions.h"
using namespace FMOD::Studio;
class MasterObject{
public:
    MasterObject(){
        paths.setData();
    }
    EventInstance* create(Studio::System* system, EventDescription* desc, String const& name){
        ERRCHECK(system->getEvent ((paths.getData(name)).toRawUTF8(), &desc));//pass in the string in the function call
        ERRCHECK(desc->createInstance(&event));
        FMOD_3D_ATTRIBUTES attr3d;
        
        ERRCHECK(event->start());
        
        return event;
    }

//    FMOD_3D_ATTRIBUTES getVector(){
//        FMOD_3D_ATTRIBUTES attr3d;
//        crowd->get3DAttributes(&attr3d);
//        return attr3d;
//    }
private:
    EventPaths paths;
    EventInstance* event;
};




#endif  // MASTEROBJECT_H_INCLUDED
