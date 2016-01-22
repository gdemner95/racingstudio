#include "MainComponent.h"
MainContentComponent::MainContentComponent()
{
    setSize (200, 200);
    
    // launches the other, game, app
    launchGame();
}

MainContentComponent::~MainContentComponent()
{
}


void MainContentComponent::initFMODStudio()
{
}

void MainContentComponent::shutdownFMODStudio()
{
}

void MainContentComponent::resized()
{
}

void MainContentComponent::handleConnect()
{
}

void MainContentComponent::handleDisconnect()
{
}

void MainContentComponent::tick()
{
}

//void MainContentComponent::handleCreate (String const& name, int gameObjectInstanceID)
//{
//}
//
//void MainContentComponent::handleDestroy (String const& name, int gameObjectInstanceID)
//{
//}
//
//void MainContentComponent::handleVector (String const& name, int gameObjectInstanceID, String const& param, const Vector3* vector)
//{
//}
//
//void MainContentComponent::handleHit (String const& name, int gameObjectInstanceID, Collision const& collision)
//{
//}
//
//void MainContentComponent::handleBool (String const& name, int gameObjectInstanceID, String const& param, bool flag)
//{
//}
//
//void MainContentComponent::handleInt (String const& name, int gameObjectInstanceID, String const& param, int value)
//{
//}
//
//void MainContentComponent::handleReal (String const& name, int gameObjectInstanceID, String const& param, double value)
//{
//}
//
//void MainContentComponent::handleString (String const& name, int gameObjectInstanceID, String const& param, String const& content)
//{
//}
//
//void MainContentComponent::handleOther (String const& name, String const& t, String const& value)
//{
//}



