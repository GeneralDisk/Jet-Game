//
//  LEGACY_CODE.cpp
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/27/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//


/**
if (i == 0 && j == 0) { //initial sector choice
    sector = randi(1,3);
    tileIndex = sector*3-randi(1,3);//initial tile
}
else if (i == 0 && j != 0) { // subsiquent tiles in first sector
    prev = tileIndex%3 + 1;
    if (prev == 1 || prev == 2) {
        tileIndex = sector*3-randi(1,2);
    }
    else
        tileIndex = sector*3-3;
        }

if (i != 0) { // choose new sector for each line based on previous line's sector
    if (j == 0) { //choose new start tile for each line based on previous line's start tile
        
        if (sector == 2 || sector == 3) {
            sector = randi(1,2);
        }
        else
            sector = 3;
            
            prev = ( terrainList[i-1]->gfxIndex[j])%3+1;
            if (sector == 3) { //if sector is 3, it doesn't matter which start tile we use, in fact, we never have to look down if sector is 1 for this row
                tileIndex = sector*3-randi(1,3);
            }
            else { //otherwise, match the previous tile's orientation
                tileIndex = sector*3-(4-prev);
                
            }
    }
    else { //decide all subsiquent tiles by looking at previous tile and also at the tile below
        if (sector == 3) {
            prev = tileIndex%3 + 1;
            if (prev == 1 || prev == 2) {
                tileIndex = sector*3-randi(1,2);
            }
            else
                tileIndex = sector*3-3;
                }
        else { //look at tile below
            prev = (terrainList[i-1]->gfxIndex[j])%3+1;
            tileIndex = sector*3-(4-prev);
            
            
        }
    }
    
}
**/

/**
 //update position based on velocity
 vec newPosition = vadd(entityList[i]->pos, entityList[i]->vel);
 int halfwidth = entityList[i]->width/2;
 int halfheight = entityList[i]->height/2;
 
 
 
 //BOUNDARIES
 
 
 if (entityList[i]->type == E_PLAYERSHIP) { //playership boundaries
 //set horizontile boundaries
 if ((newPosition.x + halfwidth) >= G_WIDTH) {
 newPosition.x = G_WIDTH - (halfwidth);
 }
 else if ((newPosition.x - halfwidth) <= 0) {
 newPosition.x = 0 + (halfwidth);
 }
 
 //set vertical boundaries
 if ((newPosition.y + halfheight) >= (G_HEIGHT)) {
 newPosition.y = (G_HEIGHT) - (halfheight);
 }
 else if ((newPosition.y - halfheight) <= (0)) {
 newPosition.y = (0) + (halfheight);
 }
 }
 else if (entityList[i]->type == E_JET) { //enemy jet boundaries, jets are dumb, so they can fly off the screen on the bottom and never go back up
 //set horizontile boundaries
 if ((newPosition.x + halfwidth) >= G_WIDTH) {
 entityList[i]->reverseXVel();
 newPosition = vadd(entityList[i]->pos, entityList[i]->vel);
 //newPosition.x = G_WIDTH - (halfwidth);
 }
 else if ((newPosition.x - halfwidth) <= 0) {
 entityList[i]->reverseXVel();
 newPosition = vadd(entityList[i]->pos, entityList[i]->vel);
 //newPosition.x = 0 + (halfwidth);
 }
 
 }//enemy jet boundaries, maybe make enemy jets have AI behavior???
 
 entityList[i]->pos = newPosition;
 
 //if entities would move past a certain threashold, delete them
 //delete entities that are off the screen
 if (entityList[i]->type == E_PLAYER_WEAPON) {
 if (entityList[i]->pos.y > (G_HEIGHT+entityList[i]->height)) {
 delete entityList[i];
 entityList[i] = nullptr;
 }
 }
 else if ( (entityList[i]->pos.y > (G_HEIGHT*1.5)) || (entityList[i]->pos.y < (0-entityList[i]->height)) || (entityList[i]->pos.x < (0-entityList[i]->width)) || (entityList[i]->pos.x > (G_WIDTH+entityList[i]->width))) {
 delete entityList[i];
 entityList[i] = nullptr;
 } **/



/**
 player *player_ship = new player; //dynamically create new player so it will persist in memory after constructor
 player_ship->type = E_PLAYERSHIP;
 player_ship->height = PLAYER_SHIP_H;
 player_ship->width = PLAYER_SHIP_W;
 player_ship->pos = vmake(G_WIDTH/2.0f,(0+(PLAYER_SHIP_H/2)));
 player_ship->gfxSet[0] = T_BSHIP_LL;
 player_ship->gfxSet[1] = T_BSHIP_L;
 player_ship->gfxSet[2] = T_BSHIP_C;
 player_ship->gfxSet[3] = T_BSHIP_R;
 player_ship->gfxSet[4] = T_BSHIP_RR;
 player_ship->curGfx = T_BSHIP_C;
 player_ship->vel = vmake(0,0); //initialze velocity to 0
 player_ship->inertia = 0; //initial inertia
 
 //player_ship.gfxSet = {T_BSHIP_L, T_BSHIP_C, T_BSHIP_R, T_BSHIP_RR};
 
 //create function to add entity to entityList, hell, maybe make entitylist it's own class...
 entityList[0] = player_ship; **/




/**
 if ( (entityList[i]->pos.y > (G_HEIGHT*1.5f)) || (entityList[i]->pos.y < (G_HEIGHT*-1.5f)) || (entityList[i]->pos.x < (G_WIDTH*-1.5f)) || (entityList[i]->pos.x > (G_WIDTH*1.5f))) {
 delete entityList[i];
 entityList[i] = nullptr;
 }
 **/


/**
 entity *yo;
 weapon test, test2;
 weapon *tester = new weapon;
 tester->damage = 100.f;
 
 
 yo = tester;
 std::cout << static_cast<weapon*>(yo)->damage << std::endl;
 delete yo;
 **/
//use static_cast<derivedClass*>(baseclassPTR)->derivedClassMember  to access derived class members from base classes



/**if ((entityList[i]->type != E_PLAYER_WEAPON || entityList[j]->type != E_PLAYER_WEAPON)&&
 ( (entityList[i]->type != E_JET) || (entityList[j]->type != E_JET))&&
 (entityList[i]->type != E_PLAYER_WEAPON || entityList[j]->type != E_ENEMY_WEAPON)&&
 (entityList[i]->type != E_ENEMY_WEAPON || entityList[j]->type != E_PLAYER_WEAPON )&&
 (entityList[i]->type != E_ENEMY_WEAPON || entityList[j]->type != E_ENEMY_WEAPON)
 ) { **/


/**
 //playership collisions with weapons
 if (entityList[i]->type == E_ENEMY_WEAPON) {
 static_cast<player*>(entityList[j])->hp -= static_cast<weapon*>(entityList[i])->damage;
 //cout << "PLAYER HP: " <<static_cast<player*>(entityList[j])->hp << endl;
 //entityList[j]->RGBA.setVal(0.f, 0.f, 0.f, 1.f);
 if (entityList[j]->getHitTimer() <= 0.f) {
 entityList[j]->getHitTimer() = COLLISION_TIMER_VAL;
 }
 
 //delete the weapon afterwards
 entityList[i]->state = ES_DESTROYED;
 entityList[i]->isActive = false;
 j = MAX_ENTITIES;
 
 
 }//PSHIP j was hit by enemy weapon i
 else if (entityList[j]->type == E_ENEMY_WEAPON) {
 static_cast<player*>(entityList[i])->hp -= static_cast<weapon*>(entityList[j])->damage;
 //cout << "PLAYER HP: " <<static_cast<player*>(entityList[i])->hp << endl;
 //entityList[j]->RGBA.setVal(0.f, 0.f, 0.f, 1.f);
 if (entityList[i]->getHitTimer() <= 0.f) {
 entityList[i]->getHitTimer() = COLLISION_TIMER_VAL;
 }
 
 //delete the weapon afterwards
 entityList[j]->state = ES_DESTROYED;
 entityList[j]->isActive = false;
 
 }//PSHIP i was hit by enemy weapon j
 
 //Playership collison with enemy jet
 if (entityList[i]->type == E_JET || entityList[j]->type == E_JET) {
 //show each object got hit
 if (entityList[j]->getHitTimer() <= 0.f) {
 entityList[j]->getHitTimer() = COLLISION_TIMER_VAL;
 }
 
 if (entityList[i]->getHitTimer() <= 0.f) {
 entityList[i]->getHitTimer() = COLLISION_TIMER_VAL;
 }
 
 entityList[i]->getHp() -= COLLISION_DAMAGE;
 entityList[j]->getHp() -= COLLISION_DAMAGE;
 vcollide(entityList[i]->vel, entityList[j]->vel);
 
 
 }
 
 **/

//rudimentary background generator
/**
 if ((gCameraPos) >= (G_HEIGHT)*(bkgMultiplier+0.5f))
 bkgMultiplier += 2.0f;
 
 if ((gCameraPos) >= (G_HEIGHT)*(bkgMultiplier2+0.5f))
 bkgMultiplier2 += 2.0f;
 
 gCore.RenderCenteredSprite(vmake(G_WIDTH/2.0f,(((G_HEIGHT * bkgMultiplier) - gCameraPos))), vmake(G_WIDTH,G_HEIGHT), T_BKG, defaul, 0, 0);
 gCore.RenderCenteredSprite(vmake(G_WIDTH/2.0f,(((G_HEIGHT * bkgMultiplier2) - gCameraPos))), vmake(G_WIDTH,G_HEIGHT), T_BKG, defaul, 0, 0);
 **/

//**** OPEN DEVICE (MAKE OWN FUNCTION) ****//
/**
 ALCdevice *device;
 ALCcontext *context;
 device = alcOpenDevice(NULL);
 if (!device) {
 std::cout << "Error: Unable to open device\n";
 return(retval);
 }
 
 context = alcCreateContext(device, NULL);
 alcMakeContextCurrent(context);
 if (!context) {
 std::cout << "Error: Unable to create current context\n";
 }
 
 //**** CREATE SOUND SOURCE ****/
/**
 ALuint source;
 ALuint buf;
 ALuint freq = sampleRate;
 ALuint format = 0;
 
 alGenBuffers(1, &buf);
 alGenSources(1, &source);
 
 //based on the soundfile in question, set the AL format type to match
 if (bitsPerSample == 8) {
 if (channels == 1) {
 format = AL_FORMAT_MONO8;
 }
 else if (channels == 2) {
 format = AL_FORMAT_STEREO8;
 }
 }
 else if (bitsPerSample == 16) {
 if (channels == 1) {
 format = AL_FORMAT_MONO16;
 }
 else if (channels == 2) {
 format = AL_FORMAT_STEREO16;
 }
 }
 
 alBufferData(buf, format, buffer, dataSize, freq);
 
 //positions of listener and source
 ALfloat SourcePos[] = {0.0, 0.0, 0.0};
 ALfloat SourceVel[] = {0.0, 0.0, 0.0};
 ALfloat ListenerPos[] = {0.0, 0.0, 0.0};
 ALfloat ListenerVel[] = {0.0, 0.0, 0.0};
 ALfloat ListenerOri[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
 
 alListenerfv(AL_POSITION, ListenerPos);
 alListenerfv(AL_VELOCITY, ListenerVel);
 alListenerfv(AL_ORIENTATION, ListenerOri);
 
 alSourcei(source, AL_BUFFER, buf);
 alSourcef(source, AL_PITCH, 1.0f);
 alSourcef(source, AL_GAIN, 1.0f);
 alSourcefv(source, AL_POSITION, SourcePos);
 alSourcefv(source, AL_VELOCITY, SourceVel);
 alSourcei(source, AL_LOOPING, AL_FALSE);
 
 //***** PLAY SOUND *****/
//alSourcePlay(source);






/**
 // =============================================================== testing whether or not the libraries are working correctly
 void gEngine::testGFX(void) {
 {
 // Build texture
 GLuint texid;
 byte pixels[256 * 256 * 4];
 for (int i = 0; i < 256; i++)
 {
 for (int j = 0; j < 256; j++)
 {
 pixels[4*(i*256 + j)    ] = (byte)( 3 * (i + j));
 pixels[4*(i*256 + j) + 1] = (byte)(17 * (2 * i + j));
 pixels[4*(i*256 + j) + 2] = (byte)(23 * (3 * i + 251 * j));
 pixels[4*(i*256 + j) + 3] = (byte)0xFF;
 }
 }
 glGenTextures( 1, &texid );
 glBindTexture( GL_TEXTURE_2D, texid );
 glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
 
 // Init sound
 ALCcontext *context;
 ALCdevice *device;
 ALuint sndsource;
 ALuint sndbuffer;
 device = alcOpenDevice(NULL);
 if (device)
 {
 context = alcCreateContext(device, NULL);
 alcMakeContextCurrent(context);
 alGenSources(1, &sndsource);
 alGetError();
 
 // Build sound effect & play
 byte snddata[128 * 1024];
 for (int i = 0; i < 128 * 1024; i++)
 snddata[i] = (byte)rand();
 alGenBuffers(1, &sndbuffer);
 alBufferData(sndbuffer, AL_FORMAT_STEREO8, snddata, 128 * 1024, 44100);
 alSourcei(sndsource, AL_BUFFER, sndbuffer);
 alSourcei(sndsource, AL_LOOPING, AL_TRUE);
 alSourcePlay(sndsource);
 }
 
 // Set up rendering
 glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
 glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho( -1.f, 1.f, -1.f, 1.f, 0.0, 1.0);
 glEnable(GL_TEXTURE_2D);
 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
 // Go!
 float angle = 0.f;
 
 while (glfwGetWindowParam(GLFW_OPENED) && !glfwGetKey(GLFW_KEY_ESC))
 {
 glClear( GL_COLOR_BUFFER_BIT );
 glBindTexture( GL_TEXTURE_2D, texid );
 
 glPushMatrix();
 glRotatef( angle, 0.0f, 0.0f, 1.0f );
 glBegin( GL_QUADS );
 glTexCoord2d(0.0, 0.0); glVertex2f(-.9f, -.9f);
 glTexCoord2d(1.0, 0.0); glVertex2f( .9f, -.9f);
 glTexCoord2d(1.0, 1.0); glVertex2f( .9f,  .9f);
 glTexCoord2d(0.0, 1.0); glVertex2f(-.9f,  .9f);
 glEnd();
 glPopMatrix();
 
 angle += 1.f;
 
 glfwSwapBuffers();
 }
 
 // End all
 glDeleteTextures( 1, &texid );
 alDeleteSources(1, &sndsource);
 alDeleteBuffers(1, &sndbuffer);
 context = alcGetCurrentContext();
 device = alcGetContextsDevice(context);
 alcMakeContextCurrent(NULL);
 alcDestroyContext(context);
 alcCloseDevice(device);
 
 glfwCloseWindow();
 }
 glfwTerminate();
 //}
 
 //cout << "FUCKING CRACKERS\n";
 }
**/
/**
 if (curSelectedMenuIndex == 1) { //go to grass lvl
 curMenu = M_NULL;
 game_state = GS_PLAYING;
 currentLevel = 1;
 resetGame();
 }
 else if (curSelectedMenuIndex == 2) { //go to ocean lvl
 curMenu = M_NULL;
 game_state = GS_PLAYING;
 currentLevel = 2;
 resetGame();
 }
 else if (curSelectedMenuIndex == curMenuSize-1) { //go back to main menu
 curMenu = M_MAIN_MENU;
 } **/


/**
int sector = 0;
int prevSector = 0;
int sectorBelowType = 0;
int tileBelowType = 0;
int prevTileType = 0;
int tileIndex = 0;
int tileBelowIndex = 0;

for (int i = 0; i < numLines; i++) {
    terrainList[i] = new line(tilesPerLine);
    for (int j = 0; j < tilesPerLine; j++) {
        if (i == 0 && j == 0) { //initial sector choice
            sector = randi(0,3);
            if (sector < 3) {
                tileIndex = sector*3+randi(0,2);//initial tile
            }
            else{
                tileIndex = randi(9,12);
            }
        }
        else if (i == 0 && j != 0) { // subsiquent tiles in first line
            prevTileType = tileIndex%3;
            if (sector < 3) {
                if (prevTileType == 0 || prevTileType == 1) {
                    int chance = 0;
                    if (sector == 0) {
                        chance = 50;
                        tileIndex = 9;
                    }
                    else if (sector == 1) {
                        chance = 33;
                        int rng = randi(11,12);
                        tileIndex = rng;
                    }
                    else {
                        chance = 50;
                        tileIndex = 10;
                    }
                    
                    if (randchance(chance)) {
                        tileIndex = sector*3+randi(1,2);
                        
                    }
                    else
                        sector = 3;
                        }
                else if (prevTileType == 2) {
                    tileIndex = sector*3;
                }
            }
            else { //else if the prevSector >= 3, it's a special tile, new shit must be done!
                if (tileIndex == 9 || tileIndex == 10) {
                    if (randchance(50)) {
                        sector = 1;
                        tileIndex = sector*3+randi(1,2);
                    }
                    else {
                        sector = 3;
                        tileIndex = randi(11,12);
                    }
                }
                else if (tileIndex == 11) {
                    int rng = randi(1,3);
                    
                    if (rng < 3) {
                        sector = 0;
                        tileIndex = sector*3 + rng;
                    }
                    else {
                        sector = 3;
                        tileIndex = 9;
                    }
                }
                else if (tileIndex == 12) {
                    int rng = randi(1,3);
                    
                    if (rng < 3) {
                        sector = 2;
                        tileIndex = sector*3 + rng;
                    }
                    else {
                        sector = 3;
                        tileIndex = 10;
                    }
                }
                else
                    cout << "DEVESTATING ERROR\n";
                    }
                    }
                    
                    if (i != 0) { // choose new sector for each line based on previous line's sector
                        tileBelowIndex = terrainList[i-1]->gfxIndex[j];
                        sectorBelowType = tileBelowIndex/3;
                        tileBelowType = tileBelowIndex%3;
                        if (j == 0) { //choose new start tile for each line based on previous line's start tile
                            //choose new sector of tile based on the tile below's sector
                            int rng;
                            if (sectorBelowType == 1 || sectorBelowType == 2) {
                                rng = randi(1,17);
                                if (rng <= 9) {
                                    sector = randi(0,1);
                                }
                                else {
                                    sector = 3;
                                }
                            }
                            else if (sectorBelowType == 0) {
                                sector = 2;
                            }
                            else { //else sector >= 3
                                rng = randi(1,14);
                                if (rng <= 8) {
                                    sector = randi(0,1);
                                }
                                else {
                                    sector = 3;
                                }
                            }
                            
                            if (sector == 2) { //if sector is 2, it doesn't matter which start tile we use
                                tileIndex = sector*3+randi(0,2);
                            }
                            else if (sector == 0 || sector == 1) { //else if, match the previous tile's orientation
                                tileIndex = sector*3+tileBelowType;
                            }
                            else { // otherwise, sector >= 3, get us a special case here
                                if (tileBelowType == 0 || tileBelowIndex == 9) {
                                    tileIndex = 10;
                                }
                                else if (tileBelowType == 1 || tileBelowIndex == 10 || tileBelowIndex == 12) {
                                    if (randchance(50)) {
                                        tileIndex = 9;
                                    }
                                    else {
                                        tileIndex = 11;
                                    }
                                }
                                else if (tileBelowType == 2 || tileBelowIndex == 11) {
                                    tileIndex = 12;
                                }
                                else {
                                    cout << "CATACLYSMIC ERROR!\n";
                                }
                            }
                        }
                        else { //decide all subsiquent tiles by looking at previous tile and also at the tile below
                            prevTileType = tileIndex%3;
                            prevSector = tileIndex/3;
                            
                            int prevTile = tileIndex;
                            int rightExpansions[13];
                            int upExpansions[13];
                            for (int z = 0; z < 13; z++) {
                                rightExpansions[z] = -1;
                                upExpansions[z] = -1;
                            }
                            int sizeR = 0; int sizeU = 0;
                            
                            if (prevSector < 3) {
                                if (prevTileType == 0 || prevTileType == 1) {
                                    int chance = 0;
                                    if (prevSector == 0) {
                                        chance = 50;
                                        tileIndex = 9;
                                        
                                        rightExpansions[tileIndex] = tileIndex;
                                        sizeR++;
                                    }
                                    else if (prevSector == 1) {
                                        chance = 33;
                                        int rng = randi(11,12);
                                        tileIndex = rng;
                                        
                                        rightExpansions[11] = 11;
                                        sizeR++;
                                        rightExpansions[12] = 12;
                                        sizeR++;
                                    }
                                    else {
                                        chance = 50;
                                        tileIndex = 10;
                                        rightExpansions[tileIndex] = tileIndex;
                                        sizeR++;
                                    }
                                    tileIndex = sector*3+1;
                                    rightExpansions[tileIndex] = tileIndex;
                                    sizeR++;
                                    tileIndex = sector*3+2;
                                    rightExpansions[tileIndex] = tileIndex;
                                    sizeR++;
                                }
                                else if (prevTileType == 2) {
                                    tileIndex = 0*3;
                                    rightExpansions[tileIndex] = tileIndex;
                                    sizeR++;
                                    tileIndex = 1*3;
                                    rightExpansions[tileIndex] = tileIndex;
                                    sizeR++;
                                    tileIndex = 2*3;
                                    rightExpansions[tileIndex] = tileIndex;
                                    sizeR++;
                                }
                            }
                            else { //else if the prevSector >= 3, it's a special tile, new shit must be done!
                                if (prevTile == 9 || prevTile == 10) {
                                    sector = 1;
                                    rightExpansions[sector*3+1] = sector*3+1;
                                    sizeR++;
                                    rightExpansions[sector*3+2] = sector*3+2;
                                    sizeR++;
                                    
                                    rightExpansions[11] = 11;
                                    sizeR++;
                                    rightExpansions[12] = 12;
                                    sizeR++;
                                }
                                else if (prevTile == 11) {
                                    sector = 0;
                                    tileIndex = sector*3;
                                    rightExpansions[tileIndex+1] = tileIndex+1;
                                    sizeR++;
                                    rightExpansions[tileIndex+2] = tileIndex+2;
                                    sizeR++;
                                    
                                    sector = 3;
                                    tileIndex = 9;
                                    rightExpansions[tileIndex] = tileIndex;
                                    sizeR++;
                                }
                                else if (prevTile == 12) {
                                    sector = 2;
                                    tileIndex = sector*3;
                                    rightExpansions[tileIndex+1] = tileIndex+1;
                                    sizeR++;
                                    rightExpansions[tileIndex+2] = tileIndex+2;
                                    sizeR++;
                                    
                                    sector = 3;
                                    tileIndex = 10;
                                    rightExpansions[tileIndex] = tileIndex;
                                    sizeR++;
                                }
                                else
                                    cout << "DEVESTATING ERROR\n";
                            }
                            /**************************//**
                            //choose new sector of tile based on the tile below's sector
                            if (sectorBelowType > 0) { //if sectorBlow is 1, 2, or 3, then possible solutions exist in sectors 0, 1, and 3
                                //MARK: possible bugs here, think about tileBelowType for tile 12
                                if (sectorBelowType == 1 || sectorBelowType == 2) {
                                    upExpansions[0*3+tileBelowType] = 0*3+tileBelowType;
                                    sizeU++;
                                    upExpansions[1*3+tileBelowType] = 1*3+tileBelowType;
                                    sizeU++;
                                    
                                }
                                
                                if ((tileBelowType == 0 && sectorBelowType < 3) || tileBelowIndex == 9) {
                                    if (tileBelowIndex == 9) {
                                        tileIndex = 0;
                                        upExpansions[tileIndex] = tileIndex;
                                        sizeU++;
                                        tileIndex = 3;
                                        upExpansions[tileIndex] = tileIndex;
                                        sizeU++;
                                    }
                                    tileIndex = 10;
                                    upExpansions[tileIndex] = tileIndex;
                                    sizeU++;
                                }
                                else if ((tileBelowType == 1 && sectorBelowType < 3) || tileBelowIndex == 10 || tileBelowIndex == 12) {
                                    if (tileBelowIndex == 10 || tileBelowIndex == 12) {
                                        tileIndex = 1;
                                        upExpansions[tileIndex] = tileIndex;
                                        sizeU++;
                                        tileIndex = 4;
                                        upExpansions[tileIndex] = tileIndex;
                                        sizeU++;
                                    }
                                    tileIndex = 9;
                                    upExpansions[tileIndex] = tileIndex;
                                    sizeU++;
                                    
                                    tileIndex = 11;
                                    upExpansions[tileIndex] = tileIndex;
                                    sizeU++;
                                }
                                else if ((tileBelowType == 2 && sectorBelowType < 3) || tileBelowIndex == 11) {
                                    if (tileBelowIndex == 11) {
                                        tileIndex = 0*3 + 2;
                                        upExpansions[tileIndex] = tileIndex;
                                        sizeU++;
                                        tileIndex = 1*3 + 2;
                                        upExpansions[tileIndex] = tileIndex;
                                        sizeU++;
                                    }
                                    tileIndex = 12;
                                    upExpansions[tileIndex] = tileIndex;
                                    sizeU++;
                                }
                                else {
                                    cout << "CATACLYSMIC ERROR SECOND COMMING!\n";
                                }
                            }
                            else if (sectorBelowType == 0) { //if sectorBelow is 0, then possible solutions exist only in sector 2
                                sector = 2;
                                
                                tileIndex = sector*3;
                                upExpansions[tileIndex] = tileIndex;
                                sizeU++;
                                upExpansions[tileIndex+1] = tileIndex+1;
                                sizeU++;
                                upExpansions[tileIndex+2] = tileIndex+2;
                                sizeU++;
                            }
                            else {
                                cout << "AHHHHH ERROR!\n";
                            }
                            
                            int validExpansions[13];
                            int sizeV = 0;
                            for (int z = 0; z < 13; z++) {
                                if ((rightExpansions[z] == upExpansions[z]) && (rightExpansions[z] != -1)) {
                                    validExpansions[sizeV] = rightExpansions[z];
                                    sizeV++;
                                }
                            }
                            if ((sizeV) == 0) {
                                tileIndex = 0;
                                sector = 0;
                                cout << "\n******** no match found on line " << i << " spot " << j << " ********** -- Tilebelow " << tileBelowIndex << "\n";
                            }
                            else {
                                int rng2 = randi(0, (sizeV-1));
                                
                                tileIndex = validExpansions[rng2];
                                sector = tileIndex/3;
                            }
                        }
                    }
                    
                    terrainList[i]->gfxIndex[j] = tileIndex;
                    //terrainList[i]->content[j] = game->forest[tileIndex];
                    terrainList[i]->content[j] = game->levelTextures[game->currentLevel-1][tileIndex];
                    terrainList[i]->pos[j] = vmake( (tileW/2 + (j*tileW)),(tileH/2 + (i*tileH)));
                    }
                    }
                    
   **/



