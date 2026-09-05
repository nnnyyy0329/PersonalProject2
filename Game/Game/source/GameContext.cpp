#include "GameContext.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "NavigationGrid.h"

ObjectManager& GameContext::GetObjectManager() const
{
	return *m_objectManager;
}

CameraManager& GameContext::GetCameraManager() const
{
	return *m_cameraManager; 
}

NavigationGrid& GameContext::GetNavigationGrid() const
{
	return *m_navigationGrid;
}