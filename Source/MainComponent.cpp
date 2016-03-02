#include "MainComponent.h"
#include "Event Paths.h"
bool MainContentComponent::ERRCHECK_EXCEPT (FMOD_RESULT result, Array<FMOD_RESULT> const& errorExceptions)
{
    if (result == FMOD_OK)                  return true;
    if (errorExceptions.contains (result))  return false;
    
    ERRCHECK (result);
    return false;
}
MainContentComponent::MainContentComponent()
{
    collisionWait = 100;
    FMOD_Debug_Initialize (FMOD_DEBUG_LEVEL_NONE, FMOD_DEBUG_MODE_TTY, nullptr, nullptr);
    MasterObject();
    setSize (200, 200);
    
    engineRange.start = 0;
    engineRange.end = 95;
    engineRange.skew = 2;
    
    // launches the other, game, app
    launchGame();
}

MainContentComponent::~MainContentComponent()
{
}


void MainContentComponent::initFMODStudio()
{
    //load resource path
    File resourcesPath = getResourcesPath();
    
    //bank file path
    File bankPath = resourcesPath.getChildFile("Master Bank.bank");
    File stringsPath = resourcesPath.getChildFile("Master Bank.strings.bank");
    
    ERRCHECK(Studio::System::create(&system));
    ERRCHECK (system->initialize (64,
                                  FMOD_STUDIO_INIT_LIVEUPDATE | FMOD_STUDIO_INIT_ALLOW_MISSING_PLUGINS,
                                  FMOD_INIT_PROFILE_ENABLE, 0)); // extraDriverData = 0
    
    // Load the bank into the system
    Studio::Bank* bank;
    ERRCHECK (system->loadBankFile (bankPath.getFullPathName().toUTF8(),
                                    FMOD_STUDIO_LOAD_BANK_NORMAL,
                                    &bank));
    
    // Load the strings bank into the system - to translate from GUIDs
    Studio::Bank* stringsBank;
    ERRCHECK (system->loadBankFile (stringsPath.getFullPathName().toUTF8(),
                                    FMOD_STUDIO_LOAD_BANK_NORMAL,
                                    &stringsBank));
    
    
    
}

void MainContentComponent::shutdownFMODStudio()
{
    // release the system
    
    if (system != nullptr)
        if (system->isValid())
            ERRCHECK (system->release());
}

void MainContentComponent::resized()
{
}

void MainContentComponent::handleConnect()
{
    initFMODStudio();
}

void MainContentComponent::handleDisconnect()
{
    shutdownFMODStudio();
    JUCEApplication::getInstance()->systemRequestedQuit();
}

void MainContentComponent::tick()
{
    // we must call call update() regularly
    
    if (collisionWait > 0)
        --collisionWait; // decrement the counter
    
    if (system != nullptr)
        if (system->isValid())
            ERRCHECK (system->update());
}

void MainContentComponent::handleCreate (String const& name, int gameObjectInstanceID)
{
    EventDescription* desc = nullptr;
    if (name != "car" && name != "camera"){
        objectDictionary.addEvent(name, gameObjectInstanceID, object.create(system, desc, name));
    }
    else {
        skid.create(system, desc);
        engine.create(system, desc);
        tyres.create(system, desc);
        crash.create(system, desc);
        
    }

}

void MainContentComponent::handleDestroy (String const& name, int gameObjectInstanceID)
{
    
}

void MainContentComponent::handleVector (String const& name, int gameObjectInstanceID, String const& param, const Vector3* vector)
{
    if (name == "camera")
    {
        //pass in vector from the handleVector call, event/object, 
        FMOD_3D_ATTRIBUTES camera3D;
        ERRCHECK (system->getListenerAttributes(FMOD_MAIN_LISTENER, &camera3D));
        if(param == "vel")  camera3D.velocity    =  *vector;
        if(param == "pos")  camera3D.position    =  *vector;
        if(param == "dir")  camera3D.forward     =  *vector;
        if(param == "up")   camera3D.up          =  *vector;
        ERRCHECK (system->setListenerAttributes(FMOD_MAIN_LISTENER, &camera3D));
    }
    else if(name == "car")
    {
        FMOD_3D_ATTRIBUTES car3D;
        car3D = engine.getVector();
        
        if(param == "vel") car3D.velocity = *vector;
        if(param == "pos") car3D.position = *vector;
        if(param == "dir") car3D.forward = *vector;
        if(param == "up") car3D.up = *vector;
        
        engine.setVector(car3D);
        skid.setVector(car3D);
        crash.setVector(car3D);
        tyres.setVector(car3D);

    }
    else if(name == "missioncontrol")
    {
        FMOD_3D_ATTRIBUTES missionControl3D;
        missionControl3D = missionControl.getVector();
        
        if(param == "vel") missionControl3D.velocity = *vector;
        if(param == "pos") missionControl3D.position = *vector;
        if(param == "dir") missionControl3D.forward = *vector;
        if(param == "up") missionControl3D.up = *vector;
        
        missionControl.setVector(missionControl3D);
    }
//    else if(name == "wires")
//    {
//        FMOD_3D_ATTRIBUTES wires3D;
//        EventInstance* tempEvent = eventObject.getEvent(gameObjectInstanceID);
//        tempEvent->get3DAttributes(&wires3D);
//        
//        if(param == "vel") wires3D.velocity = *vector;
//        if(param == "pos") wires3D.position = *vector;
//        if(param == "dir") wires3D.forward = *vector;
//        if(param == "up") wires3D.up = *vector;
//        if(tempEvent != nullptr){
//            ERRCHECK(tempEvent->set3DAttributes(&wires3D));
//        }
//    }
    else if (name == "tunnel")
    {
        FMOD_3D_ATTRIBUTES tunnel3D;
        tunnel3D = tunnel.getVector();
        
        if(param == "vel") tunnel3D.velocity = *vector;
        if(param == "pos") tunnel3D.position = *vector;
        if(param == "dir") tunnel3D.forward = *vector;
        if(param == "up") tunnel3D.up = *vector;
        tunnel.setVector(tunnel3D);
    }
    else if (name == "atmos")
    {
        FMOD_3D_ATTRIBUTES atmos3D;
        atmos3D = atmos.getVector();
        
        if(param == "vel") atmos3D.velocity = *vector;
        if(param == "pos") atmos3D.position = *vector;
        if(param == "dir") atmos3D.forward = *vector;
        if(param == "up") atmos3D.up = *vector;
        atmos.setVector(atmos3D);
        
    }
    else if (name == "overbridge"){
        FMOD_3D_ATTRIBUTES overBridge3d;
        overBridge3d = overBridge.getVector();
        if(param == "vel") overBridge3d.velocity = *vector;
        if(param == "pos") overBridge3d.position = *vector;
        if(param == "dir") overBridge3d.forward = *vector;
        if(param == "up") overBridge3d.up = *vector;
        overBridge.setVector(overBridge3d);
    }
    else if (name == "underbridge")
    {
        FMOD_3D_ATTRIBUTES underBridge3d;
        underBridge3d = underBridge.getVector();
        if(param == "vel") underBridge3d.velocity = *vector;
        if(param == "pos") underBridge3d.position = *vector;
        if(param == "dir") underBridge3d.forward = *vector;
        if(param == "up") underBridge3d.up = *vector;
        underBridge.setVector(underBridge3d);
    }
    else if (name == "crowd")
    {
        FMOD_3D_ATTRIBUTES crowd3d;
        crowd3d = crowd.getVector();
        if(param == "vel") crowd3d.velocity = *vector;
        if(param == "pos") crowd3d.position = *vector;
        if(param == "dir") crowd3d.forward = *vector;
        if(param == "up") crowd3d.up = *vector;
        crowd.setVector(crowd3d);
    }
}

void MainContentComponent::handleHit (String const& name, int gameObjectInstanceID, Collision const& collision)
{
    if(collisionWait > 0)
        return;
    else{
        EventDescription* desc = nullptr;
        
        if(name == "car")
            crash.handleHit(system, desc, collision.velocity);
        
    }
}

void MainContentComponent::handleBool (String const& name, int gameObjectInstanceID, String const& param, bool flag)
{
}

void MainContentComponent::handleInt (String const& name, int gameObjectInstanceID, String const& param, int value)
{
    if(collisionWait > 0)
        return;
    else
    {
        EventDescription* desc = nullptr;
        if(param == "gear")
            gear.changeGear(system, desc, value);
    }
}

void MainContentComponent::handleReal (String const& name, int gameObjectInstanceID, String const& param, double value)
{
    
    if(collisionWait > 0)
        return;
    else{
        if(param == "skid")
            skid.setSkid(value);

        else if(param == "rpm")
            engine.setRpm(value);
        
        else if(param == "speed")
            tyres.setSpeed(value);
        
        else if(param == "torque")
            tyres.setForce(value);
        
    }
}
void MainContentComponent::handleString (String const& name, int gameObjectInstanceID, String const& param, String const& content)
{
}

void MainContentComponent::handleOther (String const& name, String const& t, String const& value)
{
}



