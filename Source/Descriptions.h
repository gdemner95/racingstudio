/*
  ==============================================================================

    Descriptions.h
    Created: 2 Mar 2016 12:17:40pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef DESCRIPTIONS_H_INCLUDED
#define DESCRIPTIONS_H_INCLUDED
#include "JuceHeader.h"
// class that holds the paths against a key to be referenced from
class EventPaths
{
public:
    void setData()
    {
        dataMap.set("crash",            "event:/car/crash");
        dataMap.set("engine",           "event:/car/engine");
        dataMap.set("gear",             "event:/car/gear");
        dataMap.set("skid",             "event:/car/skid");
        dataMap.set("tyres",            "event:/car/tyres");
        dataMap.set("atmos",            "event:/environment/atmos");
        dataMap.set("crowd",            "event:/environment/crowd");
        dataMap.set("wires",            "event:/environment/electric-wires");
        dataMap.set("overbridge",       "event:/reverbs/overbridge");
        dataMap.set("tunnel",           "event:/reverbs/tunnel");
        dataMap.set("underbridge",      "event:/reverbs/underbridge");
        dataMap.set("missioncontrol",   "event:/reverbs/missioncontrol");
    }
    String getData(String const& name)
    {
        Logger::outputDebugString(dataMap[name]);
        return dataMap[name];
    }
    HashMap<String, String> dataMap;
private:
};

#endif  // DESCRIPTIONS_H_INCLUDED
