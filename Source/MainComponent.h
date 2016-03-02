#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../common/FMODHeaders.h"
//#include "Event Paths.h"
#include "DataHeader.h"
#include "MasterCar.h"
#include "CarCrash.h"
#include "CarEngine.h"
#include "CarGear.h"
#include "CarSkid.h"
#include "CarTyres.h"
#include "Camera.h"
//#include "Atmos.h"
//#include "Crowd.h"
//#include "MissionControl.h"
//#include "Overbridge.h"
//#include "Tunnel.h"
//#include "Underbridge.h"
//#include "Wires.h"

using namespace FMOD::Studio;

class MainContentComponent  : public Component,
public GameEngineServer
{
public:
    MainContentComponent();
    ~MainContentComponent();
    
    void initFMODStudio();
    void shutdownFMODStudio();
    
    void resized() override;
    
    void handleConnect() override;
    void handleDisconnect() override;
    void tick() override;
    
    static bool ERRCHECK_EXCEPT (FMOD_RESULT result, Array<FMOD_RESULT> const& errorExceptions);
    
    void handleCreate (String const& name, int gameObjectInstanceID) override;
    void handleDestroy (String const& name, int gameObjectInstanceID) override;
    void handleVector (String const& name, int gameObjectInstanceID, String const& param, const Vector3* vector) override;
    void handleHit (String const& name, int gameObjectInstanceID, Collision const& collision) override;
    void handleBool (String const& name, int gameObjectInstanceID, String const& param, bool flag) override;
    void handleInt (String const& name, int gameObjectInstanceID, String const& param, int value) override;
    void handleReal (String const& name, int gameObjectInstanceID, String const& param, double value) override;
    void handleString (String const& name, int gameObjectInstanceID, String const& param, String const& content) override;
    void handleOther (String const& name, String const& t, String const& value) override;
    
    int currentGear = 0;
    int previousGear = 0;
    
private:
    Studio::System* system = nullptr;
    
    CarCrash crash;
    CarTyres tyres;
    CarEngine engine;
    CarSkid skid;
    CarGear gear;
    playerCamera camera;

    Array<FMOD_RESULT> errExcept;

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
    userCar car;
    int collisionWait;
    MasterObject object;
    EventObjects<MasterObject> objectDictionary;
    NormalisableRange<double> engineRange;
};

#endif  // MAINCOMPONENT_H_INCLUDED
