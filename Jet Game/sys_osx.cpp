//
//  sys_osx.cpp
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/18/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//

#include "stdafx.h"

#include "base.h"
#include "sys.h"

//========================================================================================
// Has to be provided by the game
extern int Main(void);

//========================================================================================
// Platform layer implementation
//the actual main function

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    int retval = -1;
    
    if (glfwInit() == GL_TRUE)
    {
        if (glfwOpenWindow(SYS_WIDTH, SYS_HEIGHT, 0, 0, 0, 0, 8, 0, SYS_FULLSCREEN ? GLFW_FULLSCREEN : GLFW_WINDOW) == GL_TRUE) /* rgba, depth, stencil */
        {
            retval = Main();
            glfwCloseWindow();
        }
        glfwTerminate();
    }
    return retval;
}

//-----------------------------------------------------------------------------
void SYS_Pump()
{
    // GLFW takes care...
}

//-----------------------------------------------------------------------------
void SYS_Show()
{
    glfwSwapBuffers();
}

//-----------------------------------------------------------------------------
bool SYS_GottaQuit()
{
    return glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED);
}

//-----------------------------------------------------------------------------
void SYS_Sleep(int ms)
{
    usleep(1000 * ms);
}

//-----------------------------------------------------------------------------
bool SYS_KeyPressed(int key)
{
    return glfwGetKey(key);
}

//-----------------------------------------------------------------------------

ivec SYS_MousePos()
{
    int x, y;
    ivec pos;
    glfwGetMousePos(&x, &y);
    pos.x = x;
    pos.y = SYS_HEIGHT - y;
    return pos;
}

//-----------------------------------------------------------------------------
bool SYS_MouseButonPressed(int button)
{
    return glfwGetMouseButton(button);
} 

