#include <windows.h>
#include <WinUser.h>
#include <highlevelmonitorconfigurationapi.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Dxva2.lib")
#pragma comment(lib, "Shcore.lib")

#include <iostream>

BOOL CALLBACK MyInfoEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MONITORINFOEX mi;
	mi.cbSize = sizeof(mi);
	if(GetMonitorInfo(hMonitor, &mi))
	{
		DEVMODE dm;
		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);

		if (EnumDisplaySettings(mi.szDevice, ENUM_CURRENT_SETTINGS, &dm))
		{
			std::wcout << "Monitor: " << mi.szDevice << std::endl;
			std::cout << "Height: " << dm.dmPelsHeight << std::endl;
			std::cout << "Width: " << dm.dmPelsWidth << std::endl;
			std::cout << "Refresh Rate: " << dm.dmDisplayFrequency << "Hz" << std::endl;
		}

		if (hdcMonitor != NULL)
		{
			DeleteDC(hdcMonitor);
		}
		return TRUE;
	}
	else
	{
		std::cout << "No monitors found" << std::endl;
	}	
}

int main()
{
	EnumDisplayMonitors(NULL, NULL, MyInfoEnumProc, 0);

	return 0;
}

