#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include "wtypes.h" // for GetDesktopWindow

class SystemUtils {
public:
	static void GetDesktopResolution(int& horizontal, int& vertical) {
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		horizontal = desktop.right;
		vertical = desktop.bottom;
	}
};

#endif