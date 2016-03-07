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
#include "Descriptions.h"

class userCar
{
public:
    void handleCreate(Studio::System* system)                                               //load all the event sounds and start the ones that are continuous
    {
        engineRange.start = 0.0;
        engineRange.end = 1.0;
        engineRange.skew = 2.0;
        EventDescription* desc;
        ERRCHECK(system->getEvent ("event:/car/engine", &desc));
        ERRCHECK(desc->createInstance(&engine));
        engine->getParameter("rpm", &rpm);
        engine->getParameter("load", &loadValue);
        setRpm(800);
        ERRCHECK(engine->start());
        
        ERRCHECK(system->getEvent ("event:/car/skid", &desc));
        ERRCHECK(desc->createInstance(&skid));
        ERRCHECK(skid->getParameter("amount", &skidValue));
        ERRCHECK(skid->start());
        
        ERRCHECK(system->getEvent ("event:/car/tyres", &desc));
        ERRCHECK(desc->createInstance(&carTyres));
        carTyres->getParameter("speed", &speedValue);
        carTyres->getParameter("force", &forceValue);
        ERRCHECK(carTyres->start());
        
        ERRCHECK(system->getEvent("event:/car/crash", &desc));
        ERRCHECK (desc->createInstance (&crashInstance));
        ERRCHECK(crashInstance->getParameter("intensity", &intensityParameter));

        ERRCHECK(system->getEvent ("event:/car/gear", &desc));
        ERRCHECK (desc->createInstance (&gearEvent));
        ERRCHECK(gearEvent->getParameter("blowoff", &gearChange));

    }
    void handleHit(Studio::System* system, double velocity)
    {
        intensityParameter->setValue(velocity);
        ERRCHECK (crashInstance->start());
    }
    void changeGear(Studio::System* system, double value)
    {
        gear = value;
        if (gear > prevGear)                                                                    //if the gear is less than the previous, play the blowoff sound
        {
            if(gear != -1){
            ERRCHECK(gearChange->setValue(value));
            prevGear = gear;
            }
        }
        else
        {
            ERRCHECK(gearChange->setValue(0.0));
        }
        ERRCHECK(gearEvent->start());
    }
    void setRpm(double value)
    {
        rpm->setValue(value);
    }
    void handleLoad(double value)
    {
        loadValue->setValue(engineRange.convertFrom0to1(value));                                //scales the load parameter using a normalisable range.
    }
    void handleSpeed(double value)
    {
        speed = value;
        speedValue->setValue(value);
    }
    void handleForce(double value)
    {
        forceValue->setValue(value);
    }
    void handleSkid(double value)
    {
        skidValue->setValue(value);
    }
    void handleVector(const Vector3* vector, String const& param)
    {
        FMOD_3D_ATTRIBUTES attr3d;
        
        ERRCHECK(engine->get3DAttributes(&attr3d));
        
        if(param == "vel")  attr3d.velocity    =  *vector;
        if(param == "pos")  attr3d.position    =  *vector;
        if(param == "dir")  attr3d.forward     =  *vector;
        if(param == "up")   attr3d.up          =  *vector;
        
        //sets all the vector values to the engine location.
        ERRCHECK(engine->set3DAttributes (&attr3d));
        ERRCHECK(skid->set3DAttributes (&attr3d));
        ERRCHECK(carTyres->set3DAttributes (&attr3d));
        ERRCHECK(gearEvent->set3DAttributes (&attr3d));
        ERRCHECK(crashInstance->set3DAttributes(&attr3d));
    }
private:
    EventInstance* engine;
    EventInstance* skid;
    EventInstance* carTyres;
    EventInstance* gearEvent;
    EventInstance* crashInstance;

    Studio::ParameterInstance* rpm;
    Studio::ParameterInstance* gearChange;
    Studio::ParameterInstance* intensityParameter;
    Studio::ParameterInstance* forceValue;
    Studio::ParameterInstance* skidValue;
    Studio::ParameterInstance* speedValue;
    Studio::ParameterInstance* loadValue;
    
    float speed = 0;
    int gear = 0;
    int prevGear = 0;
    
    NormalisableRange<float> engineRange;
    
    EventPaths paths;
};



#endif  // MASTERCAR_H_INCLUDED
