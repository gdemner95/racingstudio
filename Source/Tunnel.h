/*
  ==============================================================================

    Tunnel.h
    Created: 29 Feb 2016 9:56:22pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef TUNNEL_H_INCLUDED
#define TUNNEL_H_INCLUDED
#include "JuceHeader.h"

using namespace FMOD::Studio;
class trackTunnel{
public:
    void create(Studio::System* system, EventDescription* desc){
        ERRCHECK(system->getEvent ("event:/reverbs/tunnel", &desc));
        ERRCHECK(desc->createInstance(&tunnel));
        ERRCHECK(tunnel->start());
    }
    void setVector(FMOD_3D_ATTRIBUTES car3D){
        tunnel->set3DAttributes(&car3D);
    }
    FMOD_3D_ATTRIBUTES getVector(){
        FMOD_3D_ATTRIBUTES attr3d;
        tunnel->get3DAttributes(&attr3d);
        return attr3d;
    }
private:
    EventInstance* tunnel;
    
};




#endif  // TUNNEL_H_INCLUDED
