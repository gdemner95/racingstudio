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
        printf("ID = %d", ID);
    }
    EventInstance* getEvent(int ID){
        int eventIndex = ids.indexOf(ID);
        
        return events.getUnchecked(eventIndex);
    }
    void setVector(int ID, Vector3* vector){
        
    }
    
    EventInstance* createEvent(String const& name, EventDescription* desc){
        MasterObject object;
        EventInstance* event;
        object.create(system, desc, name);
        
        return event;
    }
private:
    Array<int> ids;
    Array<String> names;
    Array<EventInstance*> events;
    Studio::System* system;
    Array<FMOD_RESULT> errExcept;
};




#endif  // DATAHEADER_H_INCLUDED
