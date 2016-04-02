//
//  main.cpp
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/18/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//
//#include <iostream>
#include "gEngine.h"
#include "stdafx.h"
//#include "core.h"

using namespace std;


typedef unsigned char byte;
int Main(void) {
  
    // initialize openGL
    glViewport(0, 0, SYS_WIDTH, SYS_HEIGHT);
    glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0.0, G_WIDTH, 0.0, G_HEIGHT, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //initialize openAL
    ALCdevice *device;
    ALCcontext *context;
    device = alcOpenDevice(NULL);
    if (!device) {
        std::cout << "Error: Unable to open device\n";
    }
    
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    if (!context) {
        std::cout << "Error: Unable to create current context\n";
    }
    
    
    
    gEngine game;

    gState mygState = GS_PLAYING;
    
    
    while (mygState != GS_EXIT) {
        game.render();
        game.show();
        game.processInput();
        game.pump();
        mygState = game.runLogic();
        game.sleep(16);
        
    }

    return 0;
}
