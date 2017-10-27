#include <Windows.h>
#include <string>

using namespace std;

#define GMEXPORT extern "C" __declspec (dllexport)

// Converts to a wide string
wstring towstr(const string str) {
	wstring buffer;
	buffer.resize(MultiByteToWideChar(CP_UTF8, 0, &str[0], -1, 0, 0));
	MultiByteToWideChar(CP_UTF8, 0, &str[0], -1, &buffer[0], buffer.size());
	return &buffer[0];
}

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpvReserved) {
	return TRUE;
}

GMEXPORT double window_maximize(void* handle) {
	return ShowWindow((HWND)handle, SW_SHOWMAXIMIZED);
}

GMEXPORT double window_set_focus(void* handle) {
	return SetForegroundWindow((HWND)handle);
}

GMEXPORT double message_yesnocancel(char* text, char* title) {
	wstring wtext = towstr(text);
	wstring wtitle = towstr(title);
	switch (MessageBox(NULL, &wtext[0], &wtitle[0],  MB_YESNOCANCEL)) {
		case IDYES:
			return 1;
		case IDNO:
			return 0;
		case IDCANCEL:
			return -1;
	}
	return -1;
}