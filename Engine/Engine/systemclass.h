//#pragma once
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
#include <windows.h>
#include "inputclass.h"
#include "graphicclass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();
	LRESULT CALLBACK MessaageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	bool Frame();
	void InitializeWindow(int &width, int &height);
	void ShutdownWindows();

private:
	LPCTSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	InputClass *m_input;
	GraphicClass *m_Graphic;

};


static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static SystemClass *ApplicationHandle = 0;
#endif // !_SYSTEMCLASS_H_

