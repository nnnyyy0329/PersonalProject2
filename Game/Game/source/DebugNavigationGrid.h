#pragma once
#include "NavigationGrid.h"

class DebugNavigationGrid
{
public:

	void Render(const NavigationGrid& navigationGrid) const;

	void DrawCell(
	float minX,
	float minZ,
	float maxX,
	float maxZ,
	int color) const;
};

