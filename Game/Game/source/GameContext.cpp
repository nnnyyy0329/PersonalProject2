#include "GameContext.h"
#include "CameraManager.h"

CameraManager& GameContext::GetCameraManager() const
{
	return *m_cameraManager; 
}