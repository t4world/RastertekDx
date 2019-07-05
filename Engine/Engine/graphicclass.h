#ifndef _GRAPHICCLASS_H_
#define _GRAPHICCLASS_H_
#include <windows.h>
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
class GraphicClass
{
public:
	GraphicClass();
	GraphicClass(const GraphicClass&);
	~GraphicClass();
	bool Initialize(int weight, int height, HWND hHwnd);
	void Showdown();
	bool Frame();

private: 
	bool Render();
};
#endif

