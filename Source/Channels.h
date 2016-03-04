/*
 ==============================================================================
 
 Channels.h
 Created: 4 Mar 2016 2:17:22pm
 Author:  George Demner
 
 ==============================================================================
 */

#ifndef CHANNELS_H_INCLUDED
#define CHANNELS_H_INCLUDED

using namespace FMOD::Studio;

class busVca{
public:
    void init(Studio::System* system){
        
        system->getVCA("vca:/Car", &CarVCA);
        system->getVCA("vca:/Environment", &EnvironmentVCA);
        system->getBus("bus:/gear", &gearBus);
        system->getBus("bus:/atmos", &atmosBus);
        system->getBus("bus:/crash", &crashBus);
        system->getBus("bus:/engine", &engineBus);
        system->getBus("bus:/skid", &skidBus);
        system->getBus("bus:/tyres", &tyresBus);
        system->getBus("bus:/crowd", &crowdBus);
        system->getBus("bus:/Reverb", &reverbBus);
        system->getBus("bus:/Environment", &wiresBus);
        
        CarVCA->setFaderLevel(0.8);
        EnvironmentVCA->setFaderLevel(1.0);
        gearBus->setFaderLevel(1.0);
        atmosBus->setFaderLevel(1.0);
        crashBus->setFaderLevel(0.4);
        engineBus->setFaderLevel(0.8);
        skidBus->setFaderLevel(0.3);
        tyresBus->setFaderLevel(0.5);
        crowdBus->setFaderLevel(1.0);
        reverbBus->setFaderLevel(0.75);
        wiresBus->setFaderLevel(1.0);
    }
private:
    Bus* gearBus;
    Bus* atmosBus;
    Bus* crashBus;
    Bus* wiresBus;
    Bus* engineBus;
    Bus* crowdBus;
    Bus* skidBus;
    Bus* tyresBus;
    Bus* reverbBus;
    
    VCA* EnvironmentVCA;
    VCA* CarVCA;
};



#endif  // CHANNELS_H_INCLUDED
