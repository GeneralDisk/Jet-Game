//
//  sys.h
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/18/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//

#ifndef sys_h
#define sys_h
// Resolution (real & virtual)

// Portrait 2:3 aspect ratio
#define SYS_WIDTH  512
#define SYS_HEIGHT 768
#define SYS_FULLSCREEN 0

// Main game coordinate system: width is 1000, height is 1500. Origin bottom left
#define G_WIDTH  1000
#define G_HEIGHT 1500

//========================================================================================
// Platform layer

void  SYS_Pump();
void  SYS_Show();
bool  SYS_GottaQuit();
void  SYS_Sleep(int ms);
bool  SYS_KeyPressed(int key);
ivec SYS_MousePos();
bool  SYS_MouseButonPressed(int button);

//-----------------------------------------------------------------------------
#ifdef _WINDOWS

#define SYS_KEY_UP    VK_UP
#define SYS_KEY_DOWN  VK_DOWN
#define SYS_KEY_LEFT  VK_LEFT
#define SYS_KEY_RIGHT VK_RIGHT
#define SYS_KEY_ENTER VK_ENTER
#define SYS_KEY_ESC VK_ESC

#define SYS_MB_LEFT   VK_LBUTTON
#define SYS_MB_RIGHT  VK_RBUTTON
#define SYS_MB_MIDDLE VK_MBUTTON

//-----------------------------------------------------------------------------
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if defined(__MACH__) && TARGET_OS_MAC && !TARGET_OS_IPHONE

#define SYS_KEY_UP    GLFW_KEY_UP
#define SYS_KEY_DOWN  GLFW_KEY_DOWN
#define SYS_KEY_LEFT  GLFW_KEY_LEFT
#define SYS_KEY_RIGHT GLFW_KEY_RIGHT
#define SYS_KEY_SPACE GLFW_KEY_SPACE
#define SYS_KEY_ENTER GLFW_KEY_ENTER
#define SYS_KEY_ESC   GLFW_KEY_ESC
//#define SYS_KEY_R     GLFW_KEY_1

#define SYS_MB_LEFT   GLFW_MOUSE_BUTTON_LEFT
#define SYS_MB_RIGHT  GLFW_MOUSE_BUTTON_RIGHT
#define SYS_MB_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE

#endif //defined(__MACH__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
#endif //defined(__APPLE__)


#endif /* sys_h */
