#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{
	SystemClass *system;
	bool result;
	system = new SystemClass;
	if (system == 0)
	{
		return 0;
	}
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}
	system->Shutdown();
	delete system;
	system = 0;
	return 0;
}