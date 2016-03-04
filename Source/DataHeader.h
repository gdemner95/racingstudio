/*
  ==============================================================================

    DataHeader.h
    Created: 5 Feb 2016 2:47:08pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef DATAHEADER_H_INCLUDED
#define DATAHEADER_H_INCLUDED
#include "JuceHeader.h"
#include "MasterObject.h"
using namespace FMOD::Studio;

/** Assert on results that are not OK and not in the errorExceptions array. */
static bool ERRCHECK_EXCEPT (FMOD_RESULT result, Array<FMOD_RESULT> const& errorExceptions)
{
    if (result == FMOD_OK)                  return true;
    if (errorExceptions.contains (result))  return false;
    
    ERRCHECK (result);
    return false;
}

template<class ObjectType>
class EventObjects {
public:
    void addEvent(String const& name, int ID, EventInstance* event){
        ids.add(ID);
        events.add(event);
        names.add(name);
    }
    EventInstance* getEvent(int ID){
        int eventIndex = ids.indexOf(ID);
        
        return events.getUnchecked(eventIndex);
    }
    void setVector(int ID, String const& param, const Vector3* vector){
        int index = ids.indexOf(ID);
        if(names[index] == "crowd")
        {
            int ind = names.indexOf("missioncontrol");
            EventInstance* mc = getEvent(ind);
            
            EventInstance* tempEvent = getEvent(ID);
            FMOD_3D_ATTRIBUTES attr3d;
            ERRCHECK(mc->get3DAttributes(&attr3d));
            if(param == "vel")  attr3d.velocity    =  *vector;
            if(param == "pos")  attr3d.position    =  *vector;
            if(param == "dir")  attr3d.forward     =  *vector;
            if(param == "up")   attr3d.up          =  *vector;
            
            ERRCHECK(tempEvent->set3DAttributes (&attr3d));
        }
        else
        {
        EventInstance* tempEvent = getEvent(ID);
        FMOD_3D_ATTRIBUTES attr3d;
        ERRCHECK(tempEvent->get3DAttributes(&attr3d));
        if(param == "vel")  attr3d.velocity    =  *vector;
        if(param == "pos")  attr3d.position    =  *vector;
        if(param == "dir")  attr3d.forward     =  *vector;
        if(param == "up")   attr3d.up          =  *vector;
        
        ERRCHECK(tempEvent->set3DAttributes (&attr3d));
        }
    }

private:
    Array<int> ids;
    Array<String> names;
    Array<EventInstance*> events;
    Studio::System* system;
    Array<FMOD_RESULT> errExcept;
};




#endif  // DATAHEADER_H_INCLUDED
