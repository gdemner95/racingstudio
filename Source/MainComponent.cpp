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
    if (collisionWait > 0)
        --collisionWait;
    
    if (system != nullptr)
        if (system->isValid())
            ERRCHECK (system->update());
}

void MainContentComponent::handleCreate (String const& name, int gameObjectInstanceID)
{
    if (name != "car" && name != "camera"){
        //crowd is set to mission control, therefor must be triggered at the same time
        if(name == "missioncontrol")
        {
            objectDictionary.addEvent(name, gameObjectInstanceID, object.create(system, name));
            objectDictionary.addEvent("crowd", gameObjectInstanceID, object.create(system, "crowd"));
        }
        else
            objectDictionary.addEvent(name, gameObjectInstanceID, object.create(system, name));   //other events are independent
    }
    else
        car.handleCreate(system);
    channels.init(system);
}

void MainContentComponent::handleDestroy (String const& name, int gameObjectInstanceID)
{
}

void MainContentComponent::handleVector (String const& name, int gameObjectInstanceID, String const& param, const Vector3* vector)
{
    //camera and car are not assigned as objects in the dictionary
    if(name != "camera" && name != "car")
        objectDictionary.setVector(gameObjectInstanceID, param, vector);

    else if (name == "camera")  camera.setVector(system, vector, param);
    else if(name == "car")      car.handleVector(vector, param);
}

void MainContentComponent::handleHit (String const& name, int gameObjectInstanceID, Collision const& collision)
{
    if(collisionWait > 0)
        return;
    
    if(name == "car" && collision.velocity > 0) car.handleHit(system, collision.velocity);
}

void MainContentComponent::handleBool (String const& name, int gameObjectInstanceID, String const& param, bool flag)
{
}

void MainContentComponent::handleInt (String const& name, int gameObjectInstanceID, String const& param, int value)
{    
    if(param == "gear")         car.changeGear(system, value);
}

void MainContentComponent::handleReal (String const& name, int gameObjectInstanceID, String const& param, double value)
{
    if(param == "skid")         car.handleSkid(value);
    if(param == "load")         car.handleLoad(value);
    if(param == "rpm")          car.setRpm(value);
    if(param == "speed")        car.handleSpeed(value);
    if(param == "torque")       car.handleForce(value);
}

void MainContentComponent::handleString (String const& name, int gameObjectInstanceID, String const& param, String const& content)
{
}

void MainContentComponent::handleOther (String const& name, String const& t, String const& value)
{
}