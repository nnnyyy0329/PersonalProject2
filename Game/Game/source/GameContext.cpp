#include "GameContext.h"
#include "ObjectManager.h"
#include "CameraManager.h"

ObjectManager& GameContext::GetObjectManager() const
{
	return *m_objectManager;
}

CameraManager& GameContext::GetCameraManager() const
{
	return *m_cameraManager; 
}