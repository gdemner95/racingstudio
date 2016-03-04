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
class MasterObject
{
public:
    MasterObject()
    {
        paths.setData();
    }
    EventInstance* create(Studio::System* system, String const& name)
    {
        if(name == "missioncontrol")
        {
            EventDescription* desc;
            ERRCHECK(system->getEvent ((paths.getData(name)).toRawUTF8(), &desc));//pass in the string in the function call
            ERRCHECK(desc->createInstance(&event));
            ERRCHECK(event->start());
            ERRCHECK(system->getEvent ((paths.getData("crowd")).toRawUTF8(), &desc));//pass in the string in the function call
            ERRCHECK(desc->createInstance(&event));
            ERRCHECK(event->start());
        }
        else
        {
            EventDescription* desc;
            ERRCHECK(system->getEvent ((paths.getData(name)).toRawUTF8(), &desc));//pass in the string in the function call
            ERRCHECK(desc->createInstance(&event));
            ERRCHECK(event->start());
        }
        return event;
    }
    
private:
    EventPaths paths;
    EventInstance* event;
};




#endif  // MASTEROBJECT_H_INCLUDED
