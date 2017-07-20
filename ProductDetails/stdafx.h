// stdafx.h : include file for standard system include files,
// Stephen La Pierre - original SlapWare 2/3/2011 3:25pm

#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
    #define _WIN32_WINNT 0x0502	// Change this to the appropriate value to target other versions of Windows.
#endif		

#pragma warning( disable : 4267 )  // Disable warning messages
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"user32.lib")
#pragma comment(lib, "Ws2_32.lib")

//#include <stdio.h>
//#include <tchar.h>

// TODO: reference additional headers your program requires here
