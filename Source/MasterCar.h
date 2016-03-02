/*
  ==============================================================================

    MasterCar.h
    Created: 2 Mar 2016 5:07:39pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef MASTERCAR_H_INCLUDED
#define MASTERCAR_H_INCLUDED

#include "JuceHeader.h"
#include "CarCrash.h"
#include "CarEngine.h"
#include "CarGear.h"
#include "CarSkid.h"
#include "CarTyres.h"
#include "Descriptions.h"

class userCar{
public:
    void handleHit(Studio::System* system, EventDescription* desc, double velocity){
        EventInstance* crashInstance;
        Studio::ParameterInstance* intensityParameter;
        ERRCHECK(system->getEvent((paths.getData("crash")).toRawUTF8(), &desc));
        ERRCHECK (desc->createInstance (&crashInstance));
        ERRCHECK(crashInstance->getParameter("intensity", &intensityParameter));
        intensityParameter->setValue(velocity);
        ERRCHECK (crashInstance->start());
        printf("%f\n", velocity);
    }
    void changeGear(Studio::System* system, EventDescription* desc, double value){
        EventInstance* gearEvent;
        Studio::ParameterInstance* gearChange;
        ERRCHECK(system->getEvent ((paths.getData("gear")).toRawUTF8(), &desc));
        ERRCHECK (desc->createInstance (&gearEvent));
        
        ERRCHECK(gearEvent->getParameter("blowoff", &gearChange));
        
        ERRCHECK(gearChange->setValue(value));
        ERRCHECK (gearEvent->start());
    }
private:
    float speed;
    int gear;
    
    EventPaths paths;
};



#endif  // MASTERCAR_H_INCLUDED
