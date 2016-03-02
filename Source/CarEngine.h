/*
  ==============================================================================

    CarEngine.h
    Created: 29 Feb 2016 1:59:14pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef CARENGINE_H_INCLUDED
#define CARENGINE_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class CarEngine{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/car/engine", &desc));
        ERRCHECK(desc->createInstance(&engine));
        setRpm(800);
        ERRCHECK(engine->start());
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        engine->set3DAttributes(&car3D);
    }
    void setRpm(double value){
        engine->getParameter("rpm", &rpm);
        rpm->setValue(value);
    }
    FMOD_3D_ATTRIBUTES getVector(){
        FMOD_3D_ATTRIBUTES car;
        engine->get3DAttributes(&car);
        return car;
    }
    
private:
    EventInstance* engine;
    Studio::ParameterInstance* rpm;
};


#endif  // CARENGINE_H_INCLUDED
