//
//  stdafx.h
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/18/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//

#ifndef stdafx_h
#define stdafx_h

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

//if windows machine
#ifdef _WINDOWS

#pragma pack(1)
#pragma warning(disable:4996) // Using open/close/read... for file access
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <GL/glu.h>
#include <al.h>
#include <alc.h>
#include <io.h>

//if apple machine
#elif defined(__APPLE__)

#include "TargetConditionals.h"
#if defined(__MACH__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
#include <unistd.h>
#include <GL/glfw.h>
#define GL_BGRA_EXT GL_BGRA
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#endif
#endif

//all c++ libraries needed



#endif /* stdafx_h */
