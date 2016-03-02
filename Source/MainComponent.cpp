#include "MainComponent.h"
//#include "Event Paths.h"
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
    Logger::outputDebugString(String(name));
    
    EventDescription* desc = nullptr;
    if (name != "car" && name != "camera"){
        //crowd is set to mission control, therefor must be triggered at the same time
        if(name =="missioncontrol"){
            objectDictionary.addEvent(name, gameObjectInstanceID, object.create(system, desc, name));
            objectDictionary.addEvent("crowd", gameObjectInstanceID, object.create(system, desc, "crowd"));
            
        }
        else
            objectDictionary.addEvent(name, gameObjectInstanceID, object.create(system, desc, name));   //other events are independent
    }
    else {
        //the car sounds
        skid.create(system, desc);
        engine.create(system, desc);
        tyres.create(system, desc);
        crash.create(system, desc);
    }
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
    
    CarVCA->setFaderLevel(1.0);
    EnvironmentVCA->setFaderLevel(0.8);
    gearBus->setFaderLevel(1.0);
    atmosBus->setFaderLevel(1.0);
    crashBus->setFaderLevel(0.9);
    engineBus->setFaderLevel(1.0);
    skidBus->setFaderLevel(0.3);
    tyresBus->setFaderLevel(0.5);
    crowdBus->setFaderLevel(1.0);
    reverbBus->setFaderLevel(0.75);
    wiresBus->setFaderLevel(1.0);
}

void MainContentComponent::handleDestroy (String const& name, int gameObjectInstanceID)
{
}

void MainContentComponent::handleVector (String const& name, int gameObjectInstanceID, String const& param, const Vector3* vector)
{
    //camera and car are not assigned as objects in the dictionary
    if(name != "camera" && name != "car"){
        
        objectDictionary.setVector(gameObjectInstanceID, param, vector);
    }
    //camera and car vector data must be assigned seperately
    else if (name == "camera")
    {
        FMOD_3D_ATTRIBUTES camera3D;
        camera.setVector(camera3D, system, vector, param);
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
}

void MainContentComponent::handleHit (String const& name, int gameObjectInstanceID, Collision const& collision)
{
    if(collisionWait > 0)
        return;
    else{
        EventDescription* desc = nullptr;
        if(name == "car")
            car.handleHit(system, desc, collision.velocity);
//            crash.handleHit(system, desc, collision.velocity);//passes the description and the velocity
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
            car.changeGear(system, desc, value);
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