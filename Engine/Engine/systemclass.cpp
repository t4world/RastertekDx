#include "systemclass.h"

SystemClass::SystemClass()
{
	m_input = 0;
	m_Graphic = 0;
}

SystemClass::SystemClass(const SystemClass &other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int screenWidth = 0;
	int screenHeight = 0;
	bool result;
	InitializeWindow(screenHeight, screenHeight);
	m_input = new InputClass();
	if (m_input == 0)
	{
		return false;
	}
	m_input->Initialize();
	m_Graphic = new GraphicClass();
	if (m_Graphic == 0)
	{
		return false;
	}
	result = m_Graphic->Initialize(screenWidth,screenHeight,m_hwnd);
	if (result == false)
	{
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	if (m_Graphic)
	{
		m_Graphic->Showdown();
		delete m_Graphic;
		m_Graphic = 0;
	}
	if (m_input)
	{
		delete m_input;
		m_input = 0;
	}
	ShutdownWindows();
}

void SystemClass::Run()
{
	MSG msg;
	bool done = false;
	bool result;
	ZeroMemory(&msg, sizeof(MSG));
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(msg.message== WM_QUIT)
		{
			done = true;
		}
		else 
		{
			result = Frame();
			if (result == false)
			{
				done = true;
			}
		}
	}

}

LRESULT SystemClass::MessaageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case  WM_KEYDOWN:
		m_input->KeyDown((unsigned int)(wParam));
		return 0;
	case  WM_KEYUP:
		m_input->KeyUp((unsigned int)(wParam));
		return 0;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

bool SystemClass::Frame()
{
	bool result;
	if (m_input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}
	result = m_Graphic->Frame();
	if (!result)
	{
		return false;
	}
	return true;
}

void SystemClass::InitializeWindow(int & width, int & height)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSetting;
	int xPos;
	int yPos;
	m_hinstance = GetModuleHandle(NULL);
	ApplicationHandle = this;
	m_applicationName = L"Engine";
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		memset(&dmScreenSetting, 0, sizeof(dmScreenSetting));
		dmScreenSetting.dmSize = sizeof(dmScreenSetting);
		dmScreenSetting.dmPelsWidth = (unsigned long)width;
		dmScreenSetting.dmPelsHeight = (unsigned long)height;
		dmScreenSetting.dmBitsPerPel = 32;
		dmScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSetting, CDS_FULLSCREEN);
		xPos = yPos = 0;
	}
	else 
	{
		width = 800;
		height = 600;
		xPos = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		yPos = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		xPos, yPos, width, width, NULL, NULL, m_hinstance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	ShowCursor(false);
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(true);
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;
	ApplicationHandle = NULL;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case  WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case  WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return ApplicationHandle->MessaageHandler(hWnd, message, wParam, lParam);
	}
}
