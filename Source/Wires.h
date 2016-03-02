/*
  ==============================================================================

    Wires.h
    Created: 29 Feb 2016 9:55:49pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef WIRES_H_INCLUDED
#define WIRES_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class object {
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
    void initialiseEvents(){
        EventDescription* desc = nullptr;
        for (int i = 0; i < ids.size(); i++){
            ERRCHECK_EXCEPT (system->getEvent ("event:/environment/electric-wires", &desc), errExcept);
        }
        
    }
private:
    Array<int> ids;
    Array<String> names;
    Array<EventInstance*> events;
    Studio::System* system;
    Array<FMOD_RESULT> errExcept;
    
};
class trackWires{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/environment/electric-wires", &desc));
        ERRCHECK(desc->createInstance(&wires));
        ERRCHECK(wires->start());
        setVector(getVector());
    }
    void setVector(FMOD_3D_ATTRIBUTES attr3d){
        wires->set3DAttributes(&attr3d);
    }
    EventInstance* getWires(){
        return wires;
    }
    FMOD_3D_ATTRIBUTES getVector(){
        FMOD_3D_ATTRIBUTES attr3d;
        wires->get3DAttributes(&attr3d);
        return attr3d;
    }
private:
    EventInstance* wires;
};




#endif  // WIRES_H_INCLUDED
