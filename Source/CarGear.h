/*
  ==============================================================================

    CarGear.h
    Created: 29 Feb 2016 1:59:31pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef CARGEAR_H_INCLUDED
#define CARGEAR_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class CarGear{
public:
    void changeGear(Studio::System* system, EventDescription* desc, double value){
        
        ERRCHECK(system->getEvent ("event:/car/gear", &desc));
        ERRCHECK (desc->createInstance (&gear));

        ERRCHECK(gear->getParameter("blowoff", &gearChange));

        ERRCHECK(gearChange->setValue(value));
        ERRCHECK (gear->start());
    }
private:
    EventInstance* gear;
    Studio::ParameterInstance* gearChange;
};



#endif  // CARGEAR_H_INCLUDED
