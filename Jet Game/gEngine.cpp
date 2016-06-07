//
//  gEngine.cpp
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/18/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//

#include "gEngine.h"

//SYSTEM CONSTANTS
#define SCR_WIDTH 640
#define SCR_HEIGHT 480
#define G_CAMERA_SPEED 25.0f
#define SCR_FULLSCREEN 0

//STAT SCREEN CONSTANTS
#define STAT_SCREEN_INTRO_TIME 5.f

//MENU CONSTANTS
#define MAIN_MENU_BKG_TIME 60.f
#define MAIN_MENU_BKG_FADE_TIME 5.f

//LEVEL CONSTANTS
#define VICTORY_SCREEN_TIME 25.f
#define LEVEL_END_TIME 350.f
#define MAX_SPAWN_RATE 3.f

//TERRAIN CONSTATNS
#define MAX_CLOUDS 8
#define CLOUD_SIZE_MOD 4.f

//ITEM CONSTANTS
#define HP_BLOB_HEALTH_INCREASE 10.f
#define ITEM_SIZE_MODIFIER 6.f

//ALL SHIP CONSTANTS
#define VELOCITY_DECAY 0.5f
#define RELOAD_DECAY 0.1f
#define MAX_INERTIA 1.f
#define MIN_INERTIA -1.f
#define INERTIA_DECAY 0.1f
#define INERTIA_TILT 0.2f //amount ship changes inertia
#define TILT_RR_THREASHOLD 0.5f
#define TILT_LL_THREASHOLD -0.5f

//PLAYER SHIP CONSTANTS
#define PLAYER_SHIP_W 108 //18
#define PLAYER_SHIP_H 150 //25
#define PLAYER_SHIP_SIZE_MODIFIER 6.f
#define PSHIP entityList[0] //define player ship as the zeroth entity
#define INITIAL_PLAYER_HP 100.f
#define INITIAL_FORWARD_SPEED 10.f
#define MAX_X_VELOCITY 10.f
#define MAX_Y_VELOCITY 10.f
#define Y_INCREASE_VELOCITY 10.f
#define X_TURN_VELOCITY 5.f

#define DEATH_X_VEL 5.f

//PLAYER DEATH EXPLOSION CONSTANTS
#define DYING_TIME 15.f
#define PLAYER_EXPLOSION_TIME 6.f
#define PLAYER_EXPLOSION_SIZE_MODIFIER 9.0f
#define PLAYER_EXPLOSION_SPEED_MODIFIER 4.f

//BOSS CONSTANTS
#define BOSS_SIZE_MODIFER 6.f
#define BOSS_SEGMENT_HP 250.f  //debug: set back to 250.f
#define BOSS_SEGMENT_EXP_TIME 10.f
#define BOSS_SEG_EXP_NUM 8.f
#define BOSS_NUM_INTRO_FRAMES 100.f
#define BOSS_INTRO_TIME 10.f
#define BOSS_EXP_TIME BOSS_SEGMENT_EXP_TIME
#define BOSS_FINAL_EXP_SIZE_MOD 50.f
#define BOSS_FINAL_EXP_TIME ENEMY_EXPLOSION_TIME+2.f
#define BOSS_OMEGA_CHARGE_TIME 15.f
#define BOSS_OMEGA_CHAMBER_CYCLE_TIME 10.f
#define BOSS_OMEGA_SIZE_MOD 6.f

//ENEMY HP CONSTANTS
#define EN_JET_MAX_HP 30.f
#define EN_JET2_MAX_HP 30.f
#define EN_BLADE_MAX_HP 50.f
#define EN_REDJET_MAX_HP 60.f
#define EN_RED_BLOB_MAX_HP 50.f

//ENEMY SHIP CONSTANTS
#define ENEMY_SIZE_MOD 6.f
#define BLADE_SPEED_MOD 5.f
#define DIRECTION_CHANGE_TIME 5.f
#define DIRECTION_TIMER_DECAY 0.1f
#define EN_MAX_X_VELOCITY 5.f
#define EN_BLADE_MAX_X_VEL 10.f
#define EN_BLADE_MAX_Y_VEL 10.f
#define EN_BLADE_MIN_X_VEL 5.f
#define EN_BLADE_MIN_Y_VEL 5.f
//#define EN_MAX_Y_VELOCITY 5.f
#define EN_X_TURN_VELOCITY 2.5f
#define DIAGONAL_VEC vmake(5.f,-5.f)
#define STRAIGHT_VEC vmake(0.f, -5.f)


//ENEMY WEAPON CONSTANTS
#define EN_SINGLE_BLASTER_W 24.f
#define EN_SINGLE_BLASTER_H 66.f
#define EN_SINGLE_BLASTER_DMG 10.f
#define EN_SINGLE_BLASTER_RELOAD 10.f
#define EN_ROCKET_Y_VEL 12.f
#define EN_ROCKET_DMG 10.f
#define EN_ROCKET_RELOAD 8.f
#define EN_BLUE_LAZER_BLAST_TIME 20.f
#define EN_BLUE_LAZER_DMG 1.f
#define EN_BLUE_LAZER_RELOAD_TIME 10.f
#define EN_BLASTER_Y_VELOCITY MAX_Y_VELOCITY
#define EN_ROCKET_MAX_X_VEL 10.f
#define EN_ROCKET_DELTA_X_VEL 0.5f

//PLAYER WEAPON CONSTANTS
#define WEAPON_SIZE_MODIFER 6.f
#define OMEGA_BOMB_DMG 100.f
#define SINGLE_BLASTER_W 24.f
#define SINGLE_BLASTER_H 66.f
#define SINGLE_BLASTER_DMG 10.f
#define SINGLE_BLASTER_RELOAD 1.f
#define ROCKET_DAMAGE 20.f
#define ROCKET_RELOAD 4.f
#define BLASTER_Y_VELOCITY MAX_Y_VELOCITY+10.f
#define ROCKET_Y_VELOCITY MAX_Y_VELOCITY + 8.f
#define ROCKET_MAX_X_VEL 10.f
#define ROCKET_DELTA_X_VEL 1.f;

//COLLISON CONSTANTS
#define COLLISION_DAMAGE 20.f
#define BLADE_COLLISION_DAMAGE 40.f
#define COLLISION_TIMER_VAL 2.f
#define COLLISION_DECAY 0.5f

//EXPLOSION ANIMATION CONSTANTS
#define ENEMY_EXPLOSION_TIME 6.f  //how long explosions take
#define EXPLOSION_SIZE_MODIFIER 10.0f //controls size of explosions, increase to increase size
#define EXPLOSION_SPEED_MODIFIER 4.f //each animation in the explosion set gets this many frames, increase to slow animation

//STROBE ANIMATION CONSTANTS
#define STROBE_INTERVAL 0.35f

//VOLUME DEFAULTS
#define MAX_VOL 1.f
#define EXP_VOL 0.7f
#define IMPACT_VOL 0.4f
#define LASER_VOL 0.12f

//SCORE CONSTANTS
#define SCORE_GJET 10
#define SCORE_MJET 20
#define SCORE_BLADE 30
#define SCORE_BOSS1 100
#define SCORE_HP_UPG 5
#define SCORE_OMEGA_UPG 10
#define SCORE_PRIMARY_UPG 10
#define SCORE_SECONDARY_UPG 10
#define SCORE_TERTIARY_UPG 10
#define SCORE_PER_HP 1
#define SCORE_PER_ACCURACY 5



using namespace std;

//===============================================================
//define statistics
//Use only if defining static members of class
//float gEngine::main_timer;

//===============================================================
//class methods
gEngine::gEngine(void) {
    
    masterVolume = MAX_VOL;
    musicVolume = MAX_VOL;
    sfxVolume = MAX_VOL;
    //DEBUG: Music muting
    //musicVolume = 0.f;
    //sfxVolume = 0.f;
    victory = false;
    
    gCore.playSound(W_SSJ3, musicVolume*masterVolume, true);
    prevPress = false;
    currentLevel = randi(1,7);
    gameTerrain = new terrain(this);
    main_timer = 0.f;
    key_timer = 0.f;
    menu_switchBKG_timer = 0.f;
    dying_timer = 0.f;
    gCameraPos = 0.f;
    isBossSpawned = false;
    
    //statistic intialization
    enemiesSpawned = 0;
    enemiesKilled = 0;
    
    shotsFired = 0;
    shotsHit = 0;
    
    hpGained = 0.f;
    hpLost = 0.f;
    
    //menus
    curMenu = M_MAIN_MENU;
    
    prevMenu = M_NULL;
    curMenuSize = 2;
    curSelectedMenuIndex = 1;
    //MARK: UPDATE THIS SHIT, possibly with a single assignment function?
    mainMenu = new Menu(5);
    mainMenu->positionOfTop = vmake(G_WIDTH/2, G_HEIGHT*.70);
    mainMenu->items[0].setAtr("main menu", 4.f, true);
    mainMenu->items[1].setAtr("play", 4.f, true);
    mainMenu->items[2].setAtr("options", 4.f, true);
    mainMenu->items[3].setAtr("help/info", 4.f, true);
    mainMenu->items[4].setAtr("exit", 4.f, true);
    
    levelSelectMenu = new Menu(9);
    levelSelectMenu->positionOfTop = vmake(G_WIDTH/2, G_HEIGHT*.70);
    levelSelectMenu->items[0].setAtr("level select", 4.f, true);
    levelSelectMenu->items[1].setAtr("grass land", 4.f, true);
    levelSelectMenu->items[2].setAtr("forest", 4.f, true);
    levelSelectMenu->items[3].setAtr("ocean", 4.f, true);
    levelSelectMenu->items[4].setAtr("rocky mesa", 4.f, true);
    levelSelectMenu->items[5].setAtr("metalscape", 4.f, true);
    levelSelectMenu->items[6].setAtr("city bones", 4.f, true);
    levelSelectMenu->items[7].setAtr("lava", 4.f, true);
    levelSelectMenu->items[8].setAtr("back", 4.f, true);
    
    optionsMenu = new Menu(5);
    optionsMenu->positionOfTop = vmake(G_WIDTH/2, G_HEIGHT*.70);
    optionsMenu->items[0].setAtr("options", 4.f, true);
    optionsMenu->items[1].setAtr("master vol 100%", 4.f, true);
    optionsMenu->items[2].setAtr("music vol 100%", 4.f, true);
    optionsMenu->items[3].setAtr("sfx vol 100%", 4.f, true);
    optionsMenu->items[4].setAtr("back", 4.f, true);
    
    helpInfoMenu = new Menu(6);
    helpInfoMenu->positionOfTop = vmake(G_WIDTH/2, G_HEIGHT*.70);
    helpInfoMenu->items[0].setAtr("help/info", 4.f, true);
    helpInfoMenu->items[1].setAtr("welcome to jet game by maris kali, in this game kill enemy jets and achieve glory!", 2.5f, true, true);
    helpInfoMenu->items[2].setAtr("   ", 2.f, true, true);
    helpInfoMenu->items[3].setAtr("use the arrow keys or 'wasd' to navigate, use 'space' to fire and use 'q' to use your omega bomb.", 2.5f, true, true);
    helpInfoMenu->items[4].setAtr("   ", 2.f, true, true);
   // helpInfoMenu->items[2].setAtr("placeholder text", 4.f, true, true);
  //  helpInfoMenu->items[3].setAtr("placeholder text", 4.f, true, true);
  //  helpInfoMenu->items[4].setAtr("placeholder text", 4.f, true, true);
//    helpInfoMenu->items[5].setAtr("placeholder text", 4.f, true, true);
    helpInfoMenu->items[5].setAtr("back", 4.f, true);
    
    pauseMenu = new Menu(5);
    pauseMenu->positionOfTop = vmake(G_WIDTH/2, G_HEIGHT*.60);
    pauseMenu->items[0].setAtr("paused", 8.f, true);
    pauseMenu->items[1].setAtr("resume", 4.f, true);
    pauseMenu->items[2].setAtr("options", 4.f, true);
    pauseMenu->items[3].setAtr("main menu", 4.f, true);
    pauseMenu->items[4].setAtr("exit", 4.f, true);
    
    questionMenu = new Menu(3);
    questionMenu->positionOfTop = vmake(G_WIDTH/2, G_HEIGHT*.60);
    questionMenu->items[0].setAtr("are you sure?", 4.f, true);
    questionMenu->items[1].setAtr("yes", 4.f, true);
    questionMenu->items[2].setAtr("no", 4.f, true);
    
    currentMenu = mainMenu;
    
    game_state = GS_MAIN_MENU;

    //DEBUG
    //game_state = GS_STATSCREEN;
    //curMenu = M_NULL;
    //gCore.playSound(W_BIGBLUE_SS, true);

    //make player
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entityList[i] = nullptr;
    }
    for (int i = 0; i < MAX_ANIMATIONS; i++) {
        animationList[i] = nullptr;
    }
    player_stats.playerHP = INITIAL_PLAYER_HP;
    player_stats.weapons[0] = T_SINGLE_SHOT;
    player_stats.weapons[1] = T_BKG;
    player_stats.weapons[2] = T_BKG;
    player_stats.armorRating = 0.f;
    player_stats.shipType = silverShip2;
    player_stats.score = 0;
  
    
    //create the player ship
    
    createEntity(E_PLAYERSHIP, vmake(G_WIDTH/2.0f,(0+(gCore.getTexHeight(player_stats.shipType[2])/2))), vmake(0,0), 0, 0, 0, player_stats.shipType[2], player_stats.shipType); //this is how you insert entities into the entityList now
    //createAnimation(A_BLACK_FADE_IN, nullptr, vmake(G_WIDTH/2, G_HEIGHT/2), vmake(0,0), MAIN_MENU_BKG_FADE_TIME);
    static_cast<player*>(PSHIP)->numOmegaWeapon = 2;
    levelBoss = nullptr;

    //DEBUG
    //levelBoss = generateBoss(1);
    //createAnimation(A_EXP_REG, PSHIP, vmake(G_WIDTH/2.0f, G_HEIGHT/2.f), vmake(0,0), 5.f, EXPLOSION_SIZE_MODIFIER);
    
    
//    PSHIP->getCurWeapon() = T_DOUBLE_SHOT;
    
//    spawnItem(vmake(G_WIDTH/2.f, G_HEIGHT/2.f), 10);
}

//===============================================================
gEngine::~gEngine(void) {
    //MARK: cur
    for (int i = 0; i < MAX_ENTITIES; i++) {
        delete entityList[i];
        
    }
    for (int i = 0; i < MAX_ANIMATIONS; i++) {
        delete animationList[i];
    }
    delete gameTerrain;
    delete levelSelectMenu;
    delete optionsMenu;
    delete helpInfoMenu;
    delete pauseMenu;
    delete questionMenu;
    
    
    
}

//===============================================================
void gEngine::render(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    rgba defaul(1.f,1.f,1.f,1.f);
    rgba black(0.f,0.f,0.f,1.f);
    
    if (game_state != GS_MAIN_MENU && game_state != GS_STATSCREEN) {
        
        generateTerrain(currentLevel); //bkg level rendering
        
        //rudimentary render player HP Bar
        defaul.a = 0.75f;
        float playerHPpercent, playerHPbarWidth;
        playerHPbarWidth = 50.f;
        playerHPpercent = PSHIP->getHp()/player_stats.playerHP;
        //DEBUG uncomment to get hp bar back
        
        gCore.RenderCenteredSprite(vmake(0.f+25.f, (G_HEIGHT*playerHPpercent)/2.f), vmake(50.f, (G_HEIGHT*playerHPpercent)), T_HP_BAR, defaul, 0, 0);
        
        //omega indicator
        vec omegaPos;
        float omegaWidth, omegaHeight;
        omegaWidth = gCore.getTexWidth(T_OMEGA_BOMB_INDI)*3.f;
        omegaHeight = gCore.getTexHeight(T_OMEGA_BOMB_INDI)*3.f;
        for (int i = 0; i < static_cast<player*>(PSHIP)->numOmegaWeapon; i++) {
            omegaPos = vmake((playerHPbarWidth*1.5f + omegaWidth*1.5f*(i)), G_HEIGHT-omegaHeight*.6f);
            gCore.RenderCenteredSprite(omegaPos, vmake(omegaWidth, omegaHeight), T_OMEGA_BOMB_INDI, defaul, 0, 0);
        }
        
        //level progress bar indicator
        defaul.setVal(0.f,0.f,0.f,1.f);
        gCore.RenderCenteredSprite(vmake((G_WIDTH-12.f), (G_HEIGHT/2.f)), vmake(24.f, (G_HEIGHT)), T_LEVEL_BAR, defaul, 0, 0);
        float levelProgressPercent = main_timer/LEVEL_END_TIME;
        if (levelProgressPercent >= 1.f)
            levelProgressPercent = 1.f;
        defaul.setVal(1.f, 1.f, 1.f, 1.f);
        if (game_state != GS_BOSSFIGHT && (game_state == GS_PLAYING || game_state == GS_PAUSE)) {
            gCore.RenderCenteredSprite(vmake((G_WIDTH-12.f), (G_HEIGHT*levelProgressPercent)/2.f), vmake(24.f, (G_HEIGHT*levelProgressPercent)), T_LEVEL_BAR, defaul, 0, 0);
        }
        else if ((game_state == GS_BOSSFIGHT || game_state == GS_DYING || game_state == GS_PAUSE) && levelBoss != nullptr) { //render boss hp bar where level progress bar is
            float bossHPpercent;
            bossHPpercent = levelBoss->healthpool/levelBoss->maxHealth;
            //cout << bossHPpercent << endl;
            gCore.RenderCenteredSprite(vmake((G_WIDTH-12.f), (G_HEIGHT*bossHPpercent)/2.f), vmake(24.f, (G_HEIGHT*bossHPpercent)), T_BOSS_HP_BAR, defaul, 0, 0);
            
        }
        //render score
        renderScore(PSHIP->getScore(), player_stats.score);
        
        //render all entities
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (entityList[i] != nullptr) {
                if (entityList[i]->isRendered) {
                    bool shadow = false;
                    if (entityList[i]->type == E_PLAYERSHIP || entityList[i]->type == E_JET || entityList[i]->type == E_JET_2 || entityList[i]->type == E_RED_JET || entityList[i]->type == E_RED_BLOB || entityList[i]->type == E_BLADE || entityList[i]->type == E_BOSS) {
                        shadow = true;
                    }
                    TexIDs gfx = entityList[i]->curGfx;
                    
                    gCore.RenderCenteredSprite(entityList[i]->pos, vmake(entityList[i]->width, entityList[i]->height), entityList[i]->curGfx, entityList[i]->RGBA, 0, entityList[i]->flipGfx, shadow, entityList[i]->reverseGfx);
                    if (gfx < T_BKG || gfx > T_LAVA_EM) {
                        cout << "error badGFX: " << gfx << endl;
                    }
                    
                    
                }
            }
        }
        
        //render all animations
        
        for (int i = 0; i < MAX_ANIMATIONS; i++) {
            if (animationList[i] != nullptr) {
                if (animationList[i]->multiSegments && animationList[i]->type == A_BLUE_LAZER) {
                    //cout<< "-------\n" << animationList[i]->numGfx << endl;
                    float h, w;
                    vec pos = animationList[i]->pos;
                    for (int j = 0; j < animationList[i]->numGfx; j++) {
                        w = animationList[i]->width;
                        h = gCore.getTexHeight(animationList[i]->gfxSet[j])*animationList[i]->sizeMod;
                        if (j == 0) {
                            
                        }
                        else if (j == 1) {
                            h = pos.y - (gCore.getTexHeight(animationList[i]->gfxSet[j-1])*animationList[i]->sizeMod)/2 - (gCore.getTexHeight(animationList[i]->gfxSet[j+1])*animationList[i]->sizeMod);
                            pos.y = (0.25f)*(pos.y*2 - (gCore.getTexHeight(animationList[i]->gfxSet[j-1])*animationList[i]->sizeMod) + (gCore.getTexHeight(animationList[i]->gfxSet[j+1])*animationList[i]->sizeMod)*2);
                        }
                        else if (j == 2) {
                            pos.y = (h/2);
                        }
                        //cout << "x: " << pos.x << " y: " << pos.y << endl;
                        gCore.RenderCenteredSprite(pos, vmake(w, h), animationList[i]->gfxSet[j], animationList[i]->RGBA, 0, animationList[i]->flipGfx);
                    }
                }
                else
                    gCore.RenderCenteredSprite(animationList[i]->pos, vmake(animationList[i]->width, animationList[i]->height), animationList[i]->curGfx, animationList[i]->RGBA, 0, animationList[i]->flipGfx);
                //cout << "W: " << animationList[i]->width << " H: " << animationList[i]->height << endl;
                
            }
        }
        
        
        
    }
    else {
        generateTerrain(1);
        defaul.setVal(1.f, 1.f, 1.f, 1.f);
        
        for (int i = 0; i < MAX_ANIMATIONS; i++) {
            if (animationList[i] != nullptr) {
                if (animationList[i]->subtype == AS_FADE) {
                    gCore.RenderCenteredSprite(animationList[i]->pos, vmake(animationList[i]->width, animationList[i]->height), animationList[i]->curGfx, animationList[i]->RGBA, 0, animationList[i]->flipGfx);
                }
            }
        }
        
        gCore.RenderCenteredString("jet game", vmake(G_WIDTH/2, G_HEIGHT*.85), 6.f, defaul, 0);
        gCore.RenderCenteredString("created by maris kali", vmake(G_WIDTH/2, G_HEIGHT*.2), 2.f, defaul, 0);
        
    }
    
    
    if (game_state == GS_VICTORY) { //render specific for victory
        
        float percent = (main_timer)/(VICTORY_SCREEN_TIME-5.f);

        black.a = percent;
        gCore.RenderCenteredSprite(vmake(G_WIDTH/2, G_HEIGHT/2), vmake(G_WIDTH, G_HEIGHT), T_BKG, black, 0, 0); //black screen fade in
        
        //gCore.RenderCenteredString("you win!", vmake(G_WIDTH/2, G_HEIGHT*.7), 4.f, defaul, 0);
    }
    
    
    if (game_state == GS_STATSCREEN) {
        
        
        gCore.RenderCenteredSprite(vmake(G_WIDTH/2, G_HEIGHT/2), vmake(G_WIDTH, G_HEIGHT), T_BKG, defaul, 0, 0);

        gCore.RenderCenteredString("mayhem report", vmake(G_WIDTH/2, G_HEIGHT*.90), 4.f, defaul, 0);

        
        //char str[] = "shots fired: "+shotsFired;
        char conv[64];
        vec position;
        float yOffset = G_HEIGHT*0.05f;
        sprintf(conv, "shots fired: %d", shotsFired);
        position = gCore.RenderCenteredString(conv, vmake(G_WIDTH/2, G_HEIGHT*.75), 3.f, defaul, 0);
        position.y -= yOffset;
        //vprint(position);
        
        sprintf(conv, "shots hit: %d", shotsHit);
        position = gCore.RenderCenteredString(conv, position, 3.f, defaul, 0);
        position.y -= yOffset;
        //vprint(position);
        
        sprintf(conv, "accuracy: %g", ((float)shotsHit/(float)shotsFired)*100);
        strcat(conv, "%");
        position = gCore.RenderCenteredString(conv, position, 3.f, defaul, 0);
        position.y -= yOffset*2;
        
        //vprint(position);
        sprintf(conv, "enemies killed: %d", enemiesKilled);
        position = gCore.RenderCenteredString(conv, position, 3.f, defaul, 0);
        position.y -= yOffset;
        
        //vprint(position);
        sprintf(conv, "enemies that escaped your wrath: %d", enemiesSpawned-enemiesKilled);
        position = gCore.RenderCenteredString(conv, position, 3.f, defaul, 0);
        position.y -= yOffset*2;
        
        //vprint(position);
        sprintf(conv, "total hp lost: %g", hpLost);
        position = gCore.RenderCenteredString(conv, position, 3.f, defaul, 0);
        position.y -= yOffset;
        
        //vprint(position);
        sprintf(conv, "total hp gained: %g", hpGained);
        position = gCore.RenderCenteredString(conv, position, 3.f, defaul, 0);
        position.y -= yOffset;

        
        gCore.RenderCenteredString("-press 'enter' to continue-", vmake(G_WIDTH/2, G_HEIGHT*.10), 2.f, defaul, 0);
        
        
        float percent = main_timer/STAT_SCREEN_INTRO_TIME;
        black.a = 1.f - percent;
        gCore.RenderCenteredSprite(vmake(G_WIDTH/2, G_HEIGHT/2), vmake(G_WIDTH, G_HEIGHT), T_BKG, black, 0, 0); //black screen fade out
    }
    
    
    //Menu rendering
    //defaul.setVal(1.f, 1.f, 1.f, 1.f);
    
    switch (curMenu) {
        case M_NULL:
        {
            break;
        }
        case M_MAIN_MENU:
        {
            renderMenu(mainMenu);
            break;
        }
        case M_LEVEL_SELECT:
        {
            renderMenu(levelSelectMenu);
            break;
        }
        case M_OPTIONS:
        {
            renderMenu(optionsMenu);
            break;
        }
        case M_HELP_INFO:
        {
            renderMenu(helpInfoMenu);
            break;
        }
        case M_PAUSE:
        {
            renderMenu(pauseMenu);
            break;
        }
        case M_QUESTION:
        {
            renderMenu(questionMenu);
            break;
        }
        default:
        {
            cout << "Error: Should never see this...\n";
            break;
        }
    }
    
    
    
    
    //gCore.RenderCenteredString("hi", vmake(G_WIDTH/2, G_HEIGHT/2), 6.f, defaul, 0);
    //gCore.RenderCenteredString("k", vmake(G_WIDTH/2, G_HEIGHT/2-16*8), 6.f, defaul, 0);
    
}//end render()

//===============================================================
void gEngine::show(void) {
    SYS_Show(); //reset glfw buffers
}//end show()

//===============================================================
void gEngine::pump(void) {
    
    SYS_Pump(); //this literally does nothing on macOSX b/c glfw handles this

}//end pump()

//===============================================================
void gEngine::processInput(void) {
    //std::cout << PSHIP->vel.x << std::endl;
    bool left = SYS_KeyPressed(SYS_KEY_LEFT);
    bool right = SYS_KeyPressed(SYS_KEY_RIGHT);
    bool up = SYS_KeyPressed(SYS_KEY_UP);
    bool down = SYS_KeyPressed(SYS_KEY_DOWN);
    bool space = SYS_KeyPressed(SYS_KEY_SPACE);
    bool leftBracket = SYS_KeyPressed('[');
    bool rightBracket = SYS_KeyPressed(']');
    bool pressP = SYS_KeyPressed('P');
    bool pressQ = SYS_KeyPressed('Q');
    bool pressE = SYS_KeyPressed('E');
    bool pressX = SYS_KeyPressed('X');
    bool pressW = SYS_KeyPressed('W');
    bool pressA = SYS_KeyPressed('A');
    bool pressS = SYS_KeyPressed('S');
    bool pressD = SYS_KeyPressed('D');
    
    
    bool enter = SYS_KeyPressed(SYS_KEY_ENTER);
    
    
    
    if (rightBracket && !prevrightBracket) {
        //spawnEnemy();
        //cout << "SPAWN\n";
        //createEntity(E_POWERUP, vmake(G_WIDTH/2,G_HEIGHT*.85f), vmake(0,0), 0, 0, 0, T_UPG_SINGLE_SIDEWAYS_SHOT_M, greenShip);
        createEntity(E_JET, vmake(G_WIDTH/2,G_HEIGHT*.5f), vmake(0,0), 0, 0, 0, greenShip[2], greenShip, true);
    }
    
    
    
    if (game_state == GS_PLAYING || game_state == GS_BOSSFIGHT) {
        /**
        bool left = SYS_KeyPressed(SYS_KEY_LEFT);
        bool right = SYS_KeyPressed(SYS_KEY_RIGHT);
        bool up = SYS_KeyPressed(SYS_KEY_UP);
        bool down = SYS_KeyPressed(SYS_KEY_DOWN);
        bool space = SYS_KeyPressed(SYS_KEY_SPACE);
        bool leftBracket = SYS_KeyPressed('[');
        //bool rightBracket = SYS_KeyPressed(']');
        bool pressP = SYS_KeyPressed('P');**/
        
        //omega weapon
        if (pressQ && !prevpressQ) {
            static_cast<player*>(PSHIP)->fireOmegaBomb(this);
        //MARK CUR
        }
        
        //Pause control
        if (pressP && !prevpressP) {
            game_state = GS_PAUSE;
            curSelectedMenuIndex = 1; // entering pause menu
            curMenu = M_PAUSE;
            gCore.pauseAllSounds(); //pause all sounds
    
        }
        
        if (leftBracket && !prevleftBracket) {
            //reset game
            //DEBUGGING COMMAND
                resetGame();
        }
        /** DEBUG spawn enemies & playerinput
        if (press) {
            if (key_timer <= 0.f) {
                printEntityInfo();
                //cout << "EYA:SLKFJ\n";
                key_timer = 5.f;
            }
        }
        
        if (rightBracket) {
            if (key_timer <= 0.f) {
                spawnEnemy();
                key_timer = 5.f;
                //cout << "SPAWN\n";
            }
        } **/
        
        if ((pressX || pressE) && !prevpressX && !prevpressE) {
            //player_stats.orientation = player_stats.orientation*(-1);
            PSHIP->flipGfx = !PSHIP->flipGfx;
        }
        
        //Steering left and right
        if (left || pressA) {
            if (PSHIP->vel.x >= -(MAX_X_VELOCITY)) {
                PSHIP->vel.x -= X_TURN_VELOCITY;
                if (PSHIP->vel.x < -(MAX_X_VELOCITY)) //set speed limit
                    PSHIP->vel.x = -MAX_X_VELOCITY;
            }
            if (PSHIP->inertia > MIN_INERTIA)
                PSHIP->inertia -= INERTIA_TILT;
        }
        else if (right || pressD) {
            if (PSHIP->vel.x <= (MAX_X_VELOCITY)) {
                PSHIP->vel.x += X_TURN_VELOCITY;
                if (PSHIP->vel.x > (MAX_X_VELOCITY)) //set speed limit
                    PSHIP->vel.x = MAX_X_VELOCITY;
            }
            if (PSHIP->inertia < MAX_INERTIA)
                PSHIP->inertia += INERTIA_TILT;
        }
        else {
            if (PSHIP->vel.x > 0) {
                PSHIP->vel.x -= VELOCITY_DECAY;
            }
            else if (PSHIP->vel.x < 0) {
                PSHIP->vel.x += VELOCITY_DECAY;
            }
            
            if (PSHIP->inertia > 0) {
                PSHIP->inertia -= INERTIA_DECAY;
            }
            else if (PSHIP->inertia < 0) {
                PSHIP->inertia += INERTIA_DECAY;
            }
        }//decay
        
        //steering up and down
        //process forward and backward player movement
        if (up || pressW) {
            PSHIP->vel.y += Y_INCREASE_VELOCITY;
            if (PSHIP->vel.y > (MAX_Y_VELOCITY)) //set speed limit
                PSHIP->vel.y = MAX_Y_VELOCITY;
        }
        else if (down || pressS) {
            PSHIP->vel.y -= Y_INCREASE_VELOCITY;
            if (PSHIP->vel.y < -(MAX_Y_VELOCITY)) //set speed limit
                PSHIP->vel.y = -MAX_Y_VELOCITY;
        }
        else {
            if (PSHIP->vel.y > 0) {
                PSHIP->vel.y -= VELOCITY_DECAY;
            }
            else if (PSHIP->vel.y < 0) {
                PSHIP->vel.y += VELOCITY_DECAY;
            }
        }//possibly add vertical inertia?
        
        //Weapon fire
        //primary weapon
        
        if (space) {
            PSHIP->fireWeapons(this);
        }
        
    
    }
    //else if (game_state == GS_PAUSE) {
    
    
    if (curMenu != M_NULL) { //menu input control
        if (down && !prevdown) {
            curSelectedMenuIndex++;
            if (curSelectedMenuIndex >= curMenuSize) {
                curSelectedMenuIndex = 1;
            }
            while (currentMenu->items[curSelectedMenuIndex].notButton) {
                curSelectedMenuIndex++;
                if (curSelectedMenuIndex >= curMenuSize) {
                    curSelectedMenuIndex = 1;
                }
            }
            
        }

        if (up && !prevup) {
            curSelectedMenuIndex--;
            if (curSelectedMenuIndex <= 0) {
                curSelectedMenuIndex = curMenuSize-1;
            }
            while (currentMenu->items[curSelectedMenuIndex].notButton) {
                curSelectedMenuIndex--;
                if (curSelectedMenuIndex <= 0) {
                    curSelectedMenuIndex = curMenuSize-1;
                }
            }
        }
        
        
        if (left && right) {
            
        }
        else if (left) {
            if (curMenu == M_OPTIONS) {
                char conv[64];
                if (curSelectedMenuIndex == 1) { // master vol
                    masterVolume -= 0.01f;
                    if (masterVolume < 0.f) {
                        masterVolume = 0.f;
                    }
                    gCore.setMusicVolume(masterVolume*musicVolume);
                    gCore.setSfxVolume(masterVolume*sfxVolume);
                    sprintf(conv, "master vol %d", (int)(masterVolume*100));
                    strcat(conv, "%");
                    optionsMenu->items[1].setAtr(conv, 4.f, true);
                }
                else if (curSelectedMenuIndex == 2) { //musiv vol
                    musicVolume -= 0.01f;
                    if (musicVolume < 0.f) {
                        musicVolume = 0.f;
                    }
                    gCore.setMusicVolume(masterVolume*musicVolume);
                    sprintf(conv, "music vol %d", (int)(musicVolume*100));
                    strcat(conv, "%");
                    optionsMenu->items[2].setAtr(conv, 4.f, true);
                }
                else if (curSelectedMenuIndex == 3) { //sfx vol
                    sfxVolume -= 0.01f;
                    if (sfxVolume < 0.f) {
                        sfxVolume = 0.f;
                    }
                    gCore.setSfxVolume(masterVolume*sfxVolume);
                    sprintf(conv, "sfx vol %d", (int)(sfxVolume*100));
                    strcat(conv, "%");
                    optionsMenu->items[3].setAtr(conv, 4.f, true);
                }
                
            }
        }
        else if (right) {
            if (curMenu == M_OPTIONS) {
                char conv[64];
                if (curSelectedMenuIndex == 1) { // master vol
                    masterVolume += 0.01f;
                    if (masterVolume > 1.f) {
                        masterVolume = 1.f;
                    }
                    gCore.setMusicVolume(masterVolume*musicVolume);
                    gCore.setSfxVolume(masterVolume*sfxVolume);
                    sprintf(conv, "master vol %d", (int)(masterVolume*100));
                    strcat(conv, "%");
                    optionsMenu->items[1].setAtr(conv, 4.f, true);
                }
                else if (curSelectedMenuIndex == 2) { //musiv vol
                    musicVolume += 0.01f;
                    if (musicVolume > 1.f) {
                        musicVolume = 1.f;
                    }
                    gCore.setMusicVolume(masterVolume*musicVolume);
                    sprintf(conv, "music vol %d", (int)(musicVolume*100));
                    strcat(conv, "%");
                    optionsMenu->items[2].setAtr(conv, 4.f, true);
                }
                else if (curSelectedMenuIndex == 3) { //sfx vol
                    sfxVolume += 0.01f;
                    if (sfxVolume > 1.f) {
                        sfxVolume = 1.f;
                    }
                    gCore.setSfxVolume(masterVolume*sfxVolume);
                    sprintf(conv, "sfx vol %d", (int)(sfxVolume*100));
                    strcat(conv, "%");
                    optionsMenu->items[3].setAtr(conv, 4.f, true);
                }
            }
        }
        
        if (enter && !preventer) {
            switch (curMenu ) {
                case M_MAIN_MENU:
                {
                    prevMenu = M_MAIN_MENU;
                    if (curSelectedMenuIndex == 1) { //go to lvl select
                        curMenu = M_LEVEL_SELECT;
                    }
                    else if (curSelectedMenuIndex == 2) { //go to options
                        curMenu = M_OPTIONS;
                    }
                    else if (curSelectedMenuIndex == 3) { //go to help/info
                        curMenu = M_HELP_INFO;
                    }
                    else if (curSelectedMenuIndex == curMenuSize-1) { //go to question menu
                        //prevMenu = curMenu;
                        curMenu = M_QUESTION;
                    }
                    
                    break;
                }
                case M_LEVEL_SELECT:
                {
                    
                    if (curSelectedMenuIndex == curMenuSize-1) { //go back to main menu
                        curMenu = prevMenu;
                        prevMenu = M_LEVEL_SELECT;
                    }
                    else {
                        curMenu = M_NULL;
                        currentLevel = curSelectedMenuIndex;
                        game_state = GS_PLAYING;
                        resetGame();
                    }
                    break;
                }
                case M_OPTIONS:
                {
                    char conv[64];
                    /**
                    optionsMenu->items[1].setAtr("master vol 100%", 4.f, true);
                    optionsMenu->items[2].setAtr("music vol 100%", 4.f, true);
                    optionsMenu->items[3].setAtr("sfx vol 100%", 4.f, true);
                    **/
                    if (curSelectedMenuIndex == 1) { //toggle master volume control
                        if (masterVolume != 0.f) {
                            masterVolume = 0.f;
                        }
                        else
                            masterVolume = 1.f;
                        sprintf(conv, "master vol %d", (int)(masterVolume*100));
                        strcat(conv, "%");
                        optionsMenu->items[1].setAtr(conv, 4.f, true);
                        gCore.setMusicVolume(masterVolume*musicVolume);
                        gCore.setSfxVolume(masterVolume*sfxVolume);
                        //gCore.setGlobalVolume(masterVolume);
                        
                    }
                    else if (curSelectedMenuIndex == 2) { //toggld music control
                        if (musicVolume != 0.f) {
                            musicVolume = 0.f;
                        }
                        else
                            musicVolume = 1.f;
                        sprintf(conv, "music vol %d", (int)(musicVolume*100));
                        strcat(conv, "%");
                        optionsMenu->items[2].setAtr(conv, 4.f, true);
                        gCore.setMusicVolume(masterVolume*musicVolume);
                    }
                    else if (curSelectedMenuIndex == 3) { //toggle sfx control
                        if (sfxVolume != 0.f) {
                            sfxVolume = 0.f;
                        }
                        else
                            sfxVolume = 1.f;
                        sprintf(conv, "sfx vol %d", (int)(sfxVolume*100));
                        strcat(conv, "%");
                        optionsMenu->items[3].setAtr(conv, 4.f, true);
                        gCore.setSfxVolume(masterVolume*sfxVolume);
                    }
                    else if (curSelectedMenuIndex == curMenuSize-1) { //go back to previous menu
                        curMenu = prevMenu;
                        prevMenu = M_OPTIONS;
                    }

                    break;
                }
                case M_HELP_INFO:
                {
                    if (curSelectedMenuIndex == 1) {
                        
                    }
                    else if (curSelectedMenuIndex == curMenuSize-1) { //go back to main menu
                        curMenu = prevMenu;
                    }
                    break;
                }
                case M_PAUSE:
                {
                    if (curSelectedMenuIndex == 1) { //resume
                        game_state = GS_PLAYING;
                        curMenu = M_NULL;
                        gCore.pauseAllSounds(true); //resume sounds
                    }
                    else if (curSelectedMenuIndex == 2) { //options menu
                        curMenu = M_OPTIONS;
                        prevMenu = M_PAUSE;
                        
                    }
                    else if (curSelectedMenuIndex == 3) { //return to main menu
                        game_state = GS_MAIN_MENU;
                        curMenu = M_MAIN_MENU;
                        gCore.stopAllSounds();
                        gCore.playSound(W_SSJ3, musicVolume*masterVolume, true);
                    }
                    else if (curSelectedMenuIndex == curMenuSize-1) { //exit game
                        prevMenu = curMenu;
                        curMenu = M_QUESTION;

                        //game_state = GS_EXIT;
                    }
                    break;
                }
                case M_QUESTION:
                {
                    if (curSelectedMenuIndex == 1) { //yes, so exit
                        game_state = GS_EXIT;
                        curMenu = M_NULL;
                    }
                    else if (curSelectedMenuIndex == curMenuSize-1) { // no, so return to previous menu
                        curMenu = prevMenu;
                        
                    }
                    break;
                }
                default:
                {
                    cout << "Error: shouldn't ever see this...\n";
                    break;
                }
            }
            curSelectedMenuIndex = 1;
        }
    }
    
    if (game_state == GS_STATSCREEN) {
        if (main_timer >= STAT_SCREEN_INTRO_TIME) { //enable only after intro
            if (enter && !preventer) {
                
                
                if (currentLevel == size_of(levelTextures)) {
                    game_state = GS_MAIN_MENU;
                    curMenu = M_MAIN_MENU;
                    gCore.stopAllSounds();
                    gCore.playSound(W_SSJ3, musicVolume*masterVolume, true);
                }
                else {
                    currentLevel++;
                    resetGame();
                }
                
            }
        }
    }
    
    prevleft = SYS_KeyPressed(SYS_KEY_LEFT);
    prevright = SYS_KeyPressed(SYS_KEY_RIGHT);
    prevup = SYS_KeyPressed(SYS_KEY_UP);
    prevdown = SYS_KeyPressed(SYS_KEY_DOWN);
    prevspace = SYS_KeyPressed(SYS_KEY_SPACE);
    prevleftBracket = SYS_KeyPressed('[');
    prevrightBracket = SYS_KeyPressed(']');
    prevpressP = SYS_KeyPressed('P');
    prevpressQ = SYS_KeyPressed('Q');
    prevpressX = pressX;//SYS_KeyPressed('X');
    prevpressE = pressE;
    prevpressW = pressW;
    prevpressA = pressA;
    prevpressS = pressS;
    prevpressD = pressD;
    preventer = SYS_KeyPressed(SYS_KEY_ENTER);
    
    
}//end processInput()

//===============================================================
gState gEngine::runLogic(void) {
    //cout << gCore.randf(-5, 5) << endl;

    if (key_timer > 0.f)
        key_timer -= 0.1f;
    
    //controls bkg logic of the main menu screen
    if (game_state == GS_MAIN_MENU) {
        //randomly switch levels
        float menuChangeThreashold = MAIN_MENU_BKG_TIME;
        float menuFadeTime = MAIN_MENU_BKG_FADE_TIME;
        
        if (menu_switchBKG_timer >= menuChangeThreashold && menu_switchBKG_timer < (menuChangeThreashold + menuFadeTime)) {
            createAnimation(A_BLACK_FULL_TRANSITION, nullptr, vmake(G_WIDTH/2, G_HEIGHT/2), vmake(0,0), menuFadeTime*2);
            menu_switchBKG_timer = menuChangeThreashold + menuFadeTime;
        }
        else if (menu_switchBKG_timer >= menuChangeThreashold + menuFadeTime*2) {
            int newlvl = currentLevel;
            while (currentLevel == newlvl) {
                newlvl = (int)gCore.randi(1, size_of(levelTextures));
            }
            currentLevel = newlvl;
            gameTerrain->clearMap();
            gameTerrain->initializeMap(this);
            menu_switchBKG_timer = 0.f;
        }
        menu_switchBKG_timer += 0.1f;
    }
    
    //START IF 1
    if (game_state != GS_PAUSE) {
        
        main_timer += 0.1;

        gameTerrain->moveTerrain(this);
        
        //generate enemies
        if (game_state == GS_PLAYING) {
            //DEBUG uncomment
            generateLevelEnemies();
    
        }
        
        
        //BOSS Logic
        if (levelBoss != nullptr) {
            
            levelBoss->intro();
            levelBoss->updatePos();
            levelBoss->updateSegVel();
            levelBoss->fireControl(this);
            
            //calculate total boss health
            float bosshealth = 0.f;
            
            //check boss life, kill boss and start death animation if hp = 0
            for (int i = 0; i < levelBoss->numOfSegments; i++) {
                bosshealth += levelBoss->segments[i]->getHp();
                
            }
            levelBoss->healthpool = bosshealth;
            if (bosshealth <= 0.f) {
                
                bool check = levelBoss->death();
                if (check) {
                    //stopAllAnimations();
                    int aniIndex;
                    aniIndex = createAnimation(A_EXP_REG, nullptr, levelBoss->position, levelBoss->velocity, BOSS_FINAL_EXP_TIME, BOSS_FINAL_EXP_SIZE_MOD);
                    moveAniToFront(aniIndex);
                    PSHIP->getScore() += levelBoss->scoreVal;
                    delete[] levelBoss->segments;
                    delete levelBoss;
                    enemiesKilled++;
                    levelBoss = nullptr;
                    victory = true;
                }
            }
        }
        
        
        
        //AI Logic
        for (int i = 1; i < MAX_ENTITIES; i++) {
            if (entityList[i] != nullptr) {
                
                //secondary weapon rocket AI for player rockets
                if (entityList[i]->type == E_PLAYER_WEAPON && entityList[i]->subType == EST_SECONDARY_WEP) {
                    int closestEnemy = -1;
                    float distance = G_HEIGHT*G_WIDTH;
                    float newDist;
                    //search for enemy that is the closest to the rocket
                    for (int j = 1; j < MAX_ENTITIES; j++) {
                        if (entityList[j] != nullptr && i != j) {
                            
                            if (entityList[j]->type == E_JET || entityList[j]->type == E_JET_2 || entityList[j]->type == E_RED_JET || entityList[j]->type == E_BLADE || entityList[j]->type == E_RED_BLOB || entityList[j]->type == E_BOSS) { //if j entity is a possible target, find the distance
                                if (!entityList[i]->flipGfx && (entityList[i]->pos.y < (entityList[j]->pos.y + entityList[j]->height))) { //we only want to track towards enemeys in front of the rocket
                                    newDist = vdistance(entityList[i]->pos, entityList[j]->pos);
                                    if (distance > newDist) { //if the newDist is smaller than the previous distance
                                        distance = newDist;
                                        closestEnemy = j;
                                    }
                                }
                                else if (entityList[i]->flipGfx && (entityList[i]->pos.y > (entityList[j]->pos.y - entityList[j]->height))) { //track fliped rockets toward enemies further below
                                    newDist = vdistance(entityList[i]->pos, entityList[j]->pos);
                                    if (distance > newDist) { //if the newDist is smaller than the previous distance
                                        distance = newDist;
                                        closestEnemy = j;
                                    }

                                }
                            }
                        }
                    }//end for
                    
                    if (closestEnemy > 0) { //if the closest enemy was found, then track rocket towards enemy
                        entity *rocket, *enemy;
                        rocket = entityList[i];
                        enemy = entityList[closestEnemy];
                        
                        if (rocket->pos.x > (enemy->pos.x + enemy->width)) { //if the rocket is to the right of the enemy, move left
                            rocket->vel.x -= ROCKET_DELTA_X_VEL;
                            if (rocket->vel.x < -ROCKET_MAX_X_VEL) {
                                rocket->vel.x = -ROCKET_MAX_X_VEL;
                            }
                        }
                        else if (rocket->pos.x < (enemy->pos.x - enemy->width)) { //if the rocket is to the left of the enemy, move right
                            rocket->vel.x += ROCKET_DELTA_X_VEL;
                            if (rocket->vel.x > ROCKET_MAX_X_VEL) {
                                rocket->vel.x = ROCKET_MAX_X_VEL;
                            }
                        }
                        else if (rocket->vel.x > 0) {
                            rocket->vel.x -= VELOCITY_DECAY;
                        }
                        else if (rocket->vel.x < 0) {
                            rocket->vel.x += VELOCITY_DECAY;
                        }
                    }
                    
                }//end Rocket AI
                
                //Enemy rocket AI
                if (entityList[i]->type == E_ENEMY_WEAPON && entityList[i]->subType == EST_SECONDARY_WEP) {
                    entity *rocket;
                    rocket = entityList[i];
                    
                    if (rocket->pos.x > (PSHIP->pos.x + PSHIP->width)) { //if the rocket is to the right of the enemy, move left
                        rocket->vel.x -= EN_ROCKET_DELTA_X_VEL;
                        if (rocket->vel.x < -EN_ROCKET_MAX_X_VEL) {
                            rocket->vel.x = -EN_ROCKET_MAX_X_VEL;
                        }
                    }
                    else if (rocket->pos.x < (PSHIP->pos.x - PSHIP->width)) { //if the rocket is to the left of the enemy, move right
                        rocket->vel.x += EN_ROCKET_DELTA_X_VEL;
                        if (rocket->vel.x > EN_ROCKET_MAX_X_VEL) {
                            rocket->vel.x = EN_ROCKET_MAX_X_VEL;
                        }
                    }
                    else if (rocket->vel.x > 0) {
                        rocket->vel.x -= VELOCITY_DECAY;
                    }
                    else if (rocket->vel.x < 0) {
                        rocket->vel.x += VELOCITY_DECAY;
                    }
                }
                
                
                //enemy AI ****
                //collidable suicide enemies
                if (entityList[i]->type == E_BLADE && entityList[i]->state == ES_ALIVE) {
                    /**
                    Direction curEnemyDir = entityList[i]->getCurDirection();
                    if (curEnemyDir == D_LEFT) {
                        if (entityList[i]->vel.x >= -(EN_BLADE_MAX_X_VEL)) {
                            entityList[i]->vel.x = (-1)*randf(EN_BLADE_MIN_X_VEL, EN_BLADE_MAX_X_VEL);
                            if (entityList[i]->vel.x < -(EN_BLADE_MAX_X_VEL)) //set speed limit
                                entityList[i]->vel.x = -EN_MAX_X_VELOCITY;
                        }
                        if (entityList[i]->inertia > MIN_INERTIA)
                            entityList[i]->inertia -= INERTIA_TILT;
                    }
                    else if (curEnemyDir == D_RIGHT) {
                        if (entityList[i]->vel.x <= (EN_BLADE_MAX_X_VEL)) {
                            entityList[i]->vel.x = (1)*randf(EN_BLADE_MIN_X_VEL, EN_BLADE_MAX_X_VEL);
                            if (entityList[i]->vel.x > (EN_BLADE_MAX_X_VEL)) //set speed limit
                                entityList[i]->vel.x = EN_MAX_X_VELOCITY;
                        }
                        if (entityList[i]->inertia < MAX_INERTIA)
                            entityList[i]->inertia += INERTIA_TILT;
                    } **/
                }
                
                //jets that can steer and shoot
                if ((entityList[i]->type == E_JET || entityList[i]->type == E_JET_2 || entityList[i]->type == E_RED_JET || entityList[i]->type == E_RED_BLOB) && entityList[i]->state == ES_ALIVE) {
                    
                    //UPDATE enemy directional control
                    
                    //if entities can change direction
                    if (entityList[i]->getDirTimer() <= 0.f) {
                        int rngNum = gCore.randi(1, 100);
                        if (rngNum <= 33) {
                            entityList[i]->getCurDirection() = D_LEFT;
                        }
                        else if (rngNum <= 66) {
                            entityList[i]->getCurDirection() = D_RIGHT;
                        }
                        else {
                            entityList[i]->getCurDirection() = D_STRAIGHT;
                        }
                        entityList[i]->getDirTimer() = DIRECTION_CHANGE_TIME;
                        
                    }
                    else { //otherwise, decay direction change timer
                        entityList[i]->getDirTimer() -= DIRECTION_TIMER_DECAY;
                    }
                    
                    //UPDATE enemy velocity
                    //Steering left and right
                    Direction curEnemyDir = entityList[i]->getCurDirection();
                    if (curEnemyDir == D_LEFT) {
                        if (entityList[i]->vel.x >= -(EN_MAX_X_VELOCITY)) {
                            entityList[i]->vel.x -= EN_X_TURN_VELOCITY;
                            if (entityList[i]->vel.x < -(EN_MAX_X_VELOCITY)) //set speed limit
                                entityList[i]->vel.x = -EN_MAX_X_VELOCITY;
                        }
                        if (entityList[i]->inertia > MIN_INERTIA)
                            entityList[i]->inertia -= INERTIA_TILT;
                    }
                    else if (curEnemyDir == D_RIGHT) {
                        if (entityList[i]->vel.x <= (EN_MAX_X_VELOCITY)) {
                            entityList[i]->vel.x += EN_X_TURN_VELOCITY;
                            if (entityList[i]->vel.x > (EN_MAX_X_VELOCITY)) //set speed limit
                                entityList[i]->vel.x = EN_MAX_X_VELOCITY;
                        }
                        if (entityList[i]->inertia < MAX_INERTIA)
                            entityList[i]->inertia += INERTIA_TILT;
                    }
                    else {
                        if (entityList[i]->vel.x > 0) {
                            entityList[i]->vel.x -= VELOCITY_DECAY;
                        }
                        else if (entityList[i]->vel.x < 0) {
                            entityList[i]->vel.x += VELOCITY_DECAY;
                        }
                        
                        if (entityList[i]->inertia > 0) {
                            entityList[i]->inertia -= INERTIA_DECAY;
                        }
                        else if (entityList[i]->inertia < 0) {
                            entityList[i]->inertia += INERTIA_DECAY;
                        }
                    }//decay
                    
                    //UPDATE enemy tilt gfx
                    //player ship inertia logic
                    if (entityList[i]->inertia > TILT_RR_THREASHOLD) {
                        entityList[i]->curGfx = entityList[i]->getGfx(4);
                    }//RR
                    else if (entityList[i]->inertia > 0.1f) {
                        entityList[i]->curGfx = entityList[i]->getGfx(3);
                    }//R
                    else if (entityList[i]->inertia < TILT_LL_THREASHOLD) {
                        entityList[i]->curGfx = entityList[i]->getGfx(0);
                    }//LL
                    else if (entityList[i]->inertia < -0.1f) {
                        entityList[i]->curGfx = entityList[i]->getGfx(1);
                    }//L
                    else
                        entityList[i]->curGfx = entityList[i]->getGfx(2); //Center
                    //cout << "INERTIA " << entityList[i]->inertia << endl;
                    

                    //enemy weapon fire control
                    entityList[i]->fireWeapons(this);
                    
                    //primary weapon fire
                    /**
                    entity *enemyObj = entityList[i];
                    if (enemyObj->getReloadTimer() <= 0.f) {
                        if (gCore.randchance(50.f)) {
                            int weapIndex = createEntity(E_ENEMY_WEAPON, enemyObj->pos, vmake(0, EN_BLASTER_Y_VELOCITY), 0, 0, 0, enemyObj->getCurWeapon(), 0, 1);

                            if (weapIndex > 0) {
                                //entityList[weapIndex]->reverseYVel();
                                //entityList[weapIndex]->RGBA.setVal(0.f, 0.f, 1.f, 1.f);
                                enemyObj->getReloadTimer() = static_cast<weapon*>(entityList[weapIndex])->reloadInterval;
                            //cout << entityList[i]->getReloadTimer() << endl;
                            }
                        }//50% chance to fire their weapon
                        else
                            enemyObj->getReloadTimer() = EN_SINGLE_BLASTER_RELOAD; //refresh buffer between failed fire attempts
                        
                    }//fireweapon!
                    else {
                        enemyObj->getReloadTimer() -= RELOAD_DECAY;
                    }//otherwise, decay reload amount
                    
                    //secondary weapon fire
                    if (enemyObj->getReloadTimer(1) <= 0.f) {
                        if (gCore.randchance(50.f)) {
                            int weapIndex = createEntity(E_ENEMY_WEAPON, enemyObj->pos, vmake(0, EN_ROCKET_Y_VEL), 0, 0, 0, enemyObj->getCurWeapon(1), 0, 1);

                            if (weapIndex > 0) {
                                //entityList[weapIndex]->reverseYVel();
                                //entityList[weapIndex]->RGBA.setVal(0.f, 0.f, 1.f, 1.f);
                                enemyObj->getReloadTimer(1) = static_cast<weapon*>(entityList[weapIndex])->reloadInterval;
                                //cout << entityList[i]->getReloadTimer() << endl;
                            }
                        }
                        else
                            enemyObj->getReloadTimer(1) = EN_ROCKET_RELOAD; //refresh buffer between failed fire attempts
                    }
                    else {
                        enemyObj->getReloadTimer(1) -= RELOAD_DECAY;
                    } **/
                    
                }//only target enemies
            }//skip all empty spots in list
        }
        
        
        
        
        //player ship inertia logic
        if (PSHIP->inertia > TILT_RR_THREASHOLD) {
            PSHIP->curGfx = PSHIP->getGfx(4);
        }//RR
        else if (PSHIP->inertia > 0.1f) {
            PSHIP->curGfx = PSHIP->getGfx(3);
        }//R
        else if (PSHIP->inertia < TILT_LL_THREASHOLD) {
            PSHIP->curGfx = PSHIP->getGfx(0);
        }//LL
        else if (PSHIP->inertia < -0.1f) {
            PSHIP->curGfx = PSHIP->getGfx(1);
        }//L
        else
            PSHIP->curGfx = PSHIP->getGfx(2); //Center
        
        
        //update entity positions
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (entityList[i] != nullptr) {
                entityList[i]->updatePos();
                
            }
        }//end Update Positions
        
        //start IF 2
        if (game_state == GS_PLAYING || game_state == GS_BOSSFIGHT) {
        
            //collison detection
            
            float x11, x12, x21, x22, y11, y12, y21, y22;
            for (int i = 0; i < MAX_ENTITIES; i++) {
               
                if (entityList[i] != nullptr && entityList[i]->state == ES_ALIVE) {
                    // cout << "Checking entity i: " << i << endl;
                    
                    for (int j = i+1; j < MAX_ENTITIES; j++) { //NOTE: More efficient, but it doesn't work correctly
                    //NOTE: Maybe there's a more efficent way to do this than in n^2
                    //for (int j = 0; j < MAX_ENTITIES; j++) {
                        
                        
                        if ((entityList[j] != nullptr) && (j != i) && (entityList[j]->state == ES_ALIVE)) {
                            //cout << "   against j: " << j << endl;
                            //if (entityList[i] != nullptr) { //NEW STATEMENT
                                
                            //entityList[j]->RGBA.setVal(1.f, 1.f, 1.f, 1.f);
                            //cout << i << " " << j << endl;
                            //check if they're alligned along the x axis
                            x11 = (entityList[i]->pos.x - ((float)entityList[i]->width)/2); //inner x boundary of the i sprite
                            x12 = (entityList[i]->pos.x + ((float)entityList[i]->width)/2); //outer x bondary of the i sprite
                            x21 = (entityList[j]->pos.x - ((float)entityList[j]->width)/2); //inner x boundary of the j sprite
                            x22 = (entityList[j]->pos.x + ((float)entityList[j]->width)/2); //outer x bondary of the j sprite
                            
                            if (((x21 <= x12) && (x21 >= x11)) || ((x22 <= x12) && (x22 >= x11)) || ((x11 <= x22) && (x11 >= x21)) || ((x12 <= x22) && (x12 >= x21))) {
                                //now check if they're aligned on the y axis
                                y11 = (entityList[i]->pos.y - ((float)entityList[i]->height)/2); //lower y boundary of the i sprite
                                y12 = (entityList[i]->pos.y + ((float)entityList[i]->height)/2); //upper y bondary of the i sprite
                                y21 = (entityList[j]->pos.y - ((float)entityList[j]->height)/2); //lower y boundary of the j sprite
                                y22 = (entityList[j]->pos.y + ((float)entityList[j]->height)/2); //upper y bondary of the j sprite
                                
                                if (((y21 <= y12) && (y21 >= y11)) || ((y22 <= y12) && (y22 >= y11)) || ((y11 <= y22) && (y11 >= y21)) || ((y12 <= y22) && (y12 >= y21))) {

                                    //playership collisions
                                    if (entityList[i]->type == E_PLAYERSHIP || entityList[j]->type == E_PLAYERSHIP) {
                                        if (entityList[i]->isActive && entityList[j]->isActive) {
                                            //item pickup
                                            entity *ship, *otherE;
                                            if (entityList[i]->type == E_PLAYERSHIP) {
                                                ship = entityList[i];
                                                otherE = entityList[j];
                                            }
                                            else {
                                                ship = entityList[j];
                                                otherE = entityList[i];
                                            }
                                            
                                            
                                            //different types of collisons
                                            if (otherE->type == E_ENEMY_WEAPON) { // if otherE was an enemy weapon
                                                ship->getHp() -= static_cast<weapon*>(otherE)->damage;
                                                hpLost += static_cast<weapon*>(otherE)->damage;

                                                if (ship->getHitTimer() <= 0.f) {
                                                    ship->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                                
                                                //delete the weapon afterwards
                                                
                                                otherE->state = ES_DESTROYED;
                                                otherE->isActive = false;
                                                
                                                if (otherE->Id == i) {
                                                    j = MAX_ENTITIES;
                                                }//if i was just destroyed
                                                gCore.playSound(W_IMPACT_1, IMPACT_VOL*sfxVolume*masterVolume);
                                            }
                                            else if (otherE->type == E_ENEMY_LASER) { // if otherE was an enemy laser
                                                ship->getHp() -= static_cast<laser*>(otherE)->damage;
                                                hpLost += static_cast<laser*>(otherE)->damage;
                                                if (ship->getHitTimer() <= 0.f) {
                                                    ship->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                            }
                                            else if (otherE->type == E_JET || otherE->type == E_JET_2 || otherE->type == E_RED_JET || otherE->type == E_RED_BLOB) { //if otherE was an enemy jet
                                                //show each object got hit
                                                if (ship->getHitTimer() <= 0.f) {
                                                    ship->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                                
                                                if (otherE->getHitTimer() <= 0.f) {
                                                    otherE->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                                
                                                ship->getHp() -= COLLISION_DAMAGE;
                                                hpLost += COLLISION_DAMAGE;
                                                //otherE->getHp() -= COLLISION_DAMAGE;
                                                otherE->getHp() = 0.f;
                                                vcollide(ship->vel, otherE->vel);
                                                gCore.playSound(W_IMPACT_1, IMPACT_VOL*sfxVolume*masterVolume);
                                            }
                                            else if (otherE->type == E_BLADE) { //if otherE was a spinning blade of death
                                                if (ship->getHitTimer() <= 0.f) {
                                                    ship->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                                
                                                ship->getHp() -= BLADE_COLLISION_DAMAGE;
                                                hpLost += BLADE_COLLISION_DAMAGE;
                                                
                                                otherE->getHp() = 0.f;
                                                vcollide(ship->vel, otherE->vel);
                                                gCore.playSound(W_IMPACT_1, IMPACT_VOL*sfxVolume*masterVolume);
                                            }
                                            else if (otherE->type == E_BOSS) { //if you ram the boss
                                                //show each object got hit
                                                if (ship->getHitTimer() <= 0.f) {
                                                    ship->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                                
                                                if (otherE->getHitTimer() <= 0.f) {
                                                    otherE->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                                
                                                ship->getHp() -= COLLISION_DAMAGE;
                                                hpLost += COLLISION_DAMAGE;
                                                //otherE->getHp() -= COLLISION_DAMAGE;
                                                otherE->getHp() -= COLLISION_DAMAGE;
                                                vcollide(ship->vel, otherE->vel);
                                                
                                            }
                                            else if (otherE->type == E_HEALTHUP) { //if otherE was a healthpickup
                                                ship->getHp() += otherE->getHp();
                                                ship->getScore() += SCORE_HP_UPG;
                                                hpGained += otherE->getHp();
                                                gCore.playSound(W_POWERUP, sfxVolume*masterVolume);
                                                otherE->isActive = false; //delete item
                                            }
                                            else if (otherE->type == E_POWERUP) { //if otherE was a powerup
                                                if (otherE->subType == EST_NULL) {
                                                    if (otherE->curGfx == T_UPG_OMEGA_BOMB) { //if the otherE was an OmegaBomb
                                                        ship->getScore() += SCORE_OMEGA_UPG;
                                                        if (static_cast<player*>(PSHIP)->numOmegaWeapon < 3) { //if Player doesn't already have the max num of OmegaBombs
                                                            static_cast<player*>(PSHIP)->numOmegaWeapon++;
                                                        }
                                                    }
                                                }
                                                else if (otherE->subType == EST_PRIMARY_WEP) {
                                                    ship->getScore() += SCORE_PRIMARY_UPG;
                                                    if (ship->getCurWeapon() < otherE->getCurWeapon())
                                                        ship->getCurWeapon() = otherE->getCurWeapon();
                                                }
                                                else if (otherE->subType == EST_SECONDARY_WEP) {
                                                    ship->getScore() += SCORE_SECONDARY_UPG;
                                                    if (ship->getCurWeapon(1) < otherE->getCurWeapon(1))
                                                        ship->getCurWeapon(1) = otherE->getCurWeapon(1);
                                                    ship->subType = EST_SECONDARY_WEP; //activate secondary weaponsfire
                                                }
                                                else if (otherE->subType == EST_TERTIARY_WEP) {
                                                    ship->getScore() += SCORE_TERTIARY_UPG;
                                                    if (ship->getCurWeapon(2) < otherE->getCurWeapon(2))
                                                        ship->getCurWeapon(2) = otherE->getCurWeapon(2);
                                                    ship->subType = EST_TERTIARY_WEP;
                                                }
                                                gCore.playSound(W_POWERUP, sfxVolume*masterVolume);
                                                otherE->isActive = false; //delete item
                                            }
                                            
                                            
                                        }
                                    }//end playership collisions
                                    else if (entityList[i]->isActive && entityList[j]->isActive){ //only check entities that are both active
                                        //COLLISIONS BETWEEN EVERYTHING ELSE THAT IS ACTIVE BUT NOT PLAYERSHIPS
                                    
                                        //ignore: collisons between entities of the same time (weapon on weapon), and player_weapons w/ enemy_weapons
                                        //EXCLUSDE E_HEALTHUP and E_POWERUP
                                        if ((entityList[i]->type != entityList[j]->type)&&
                                            (entityList[i]->type != E_PLAYER_WEAPON || entityList[j]->type != E_ENEMY_WEAPON)&&
                                            (entityList[i]->type != E_ENEMY_WEAPON || entityList[j]->type != E_PLAYER_WEAPON )&&
                                            (entityList[i]->type != E_HEALTHUP && entityList[j]->type != E_HEALTHUP)&&
                                            (entityList[i]->type != E_POWERUP && entityList[j]->type != E_POWERUP)&&
                                            (entityList[i]->type != E_ENEMY_LASER && entityList[j]->type != E_ENEMY_LASER)
                                            ) {
                                            
                    
                                            
                                            //player weapon collisions (ASSUMED WITH ENEMY TYPE)
                                            if (entityList[i]->type == E_PLAYER_WEAPON) {
                                                shotsHit++;
                                                gCore.playSound(W_IMPACT_1, IMPACT_VOL*sfxVolume*masterVolume);
                                                
                                                //cout << "COLLISION DETECTED between WEAPON: " << i << " and ENEMY: " << j << "\n";
                                                
                                                static_cast<enemy*>(entityList[j])->hp -= static_cast<weapon*>(entityList[i])->damage;
                                                
                                                //entityList[j]->RGBA.setVal(0.f, 0.f, 0.f, 1.f);
                                                if (entityList[j]->getHitTimer() <= 0.f) {
                                                    entityList[j]->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                                
                                                //delete the weapon afterwards
                                                entityList[i]->isActive = false;
                                                entityList[i]->state = ES_DESTROYED;
                                                j = MAX_ENTITIES;
                                                /**
                                                delete entityList[i];
                                                entityList[i] = nullptr;
                                                j = MAX_ENTITIES;
                                                **/
                                                //cout << static_cast<enemy*>(entityList[i])->hp << endl;
                                            }// if i was the weapon
                                            else if (entityList[j]->type == E_PLAYER_WEAPON) {
                                                shotsHit++;
                                                gCore.playSound(W_IMPACT_1, IMPACT_VOL*sfxVolume*masterVolume);
                                                //cout << "COLLISION DETECTED between ENEMY: " << i << " WEAPON: " << j << "\n";
                                                
                                                static_cast<enemy*>(entityList[i])->hp -= static_cast<weapon*>(entityList[j])->damage;
                                                
                                                if (entityList[i]->getHitTimer() <= 0.f) {
                                                    entityList[i]->getHitTimer() = COLLISION_TIMER_VAL;
                                                }
                                                //entityList[j]->RGBA.setVal(0.f, 0.f, 0.f, 1.f);
                                                
                                                //delete weapon afterwards
                                                entityList[j]->isActive = false;
                                                entityList[j]->state = ES_DESTROYED;
                                                /**
                                                delete entityList[j];
                                                entityList[j] = nullptr;
                                                **/
                                                
                                                //cout << static_cast<enemy*>(entityList[i])->hp << endl;
                                            }// if j was the weapon
                                            
                                        }
                                        
                                        
                                    }
                                }//collison detected in this if statement
                            }
                           // }//end NEW STATE
                        }
                    }//cheak collisons against every other entity in existance
                }//for each entity
            }//end collison detection
        
        }//end IF 2
        
        //animation hit timers
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (entityList[i] != nullptr) {
                
                //collison animations
                if ((entityList[i]->type != E_ENEMY_WEAPON) && (entityList[i]->type != E_PLAYER_WEAPON)) {
                    if (entityList[i]->getHitTimer() > COLLISION_TIMER_VAL) { //code catches bugs with the hitTimers so we don't spawn black textures
                        //cout << "HIT TIMER ERROR val: " << entityList[i]->getHitTimer() << endl;
                        entityList[i]->getHitTimer() = 0.f;
                    }
                    if (entityList[i]->getHitTimer() > 0.f) {
                        
                        entityList[i]->RGBA.setVal(0.f, 0.f, 0.f, 1.f); //flashes black
                        entityList[i]->getHitTimer() -= COLLISION_DECAY;
                    }
                    else
                        entityList[i]->RGBA.setVal(1.f, 1.f, 1.f, 1.f);
                }
            }
        }
        
        //ANIMATION CONTROL
        //Trigger exp animations for entities below 0 hp and remove entities that are no longer active
        for (int i = 1; i < MAX_ENTITIES; i++) {
            if (entityList[i] != nullptr) {
                if (entityList[i]->isAnimated) {
                    entityList[i]->animation();
                }
                
                if (entityList[i]->getHp() <= 0.f && entityList[i]->type != E_POWERUP && entityList[i]->state != ES_DESTROYED) { //what happens when shit dies
                    entityList[i]->getHp() = 0.f;
                    if (entityList[i]->type != E_BOSS) {
                        if (entityList[i]->type != E_HEALTHUP) {
                            enemiesKilled++;
                            PSHIP->getScore() += entityList[i]->getScore(); //add the enemy's score val to player's current score
                            
                        }
                        createAnimation(A_EXP_REG, nullptr, entityList[i]->pos, vmake(0,0), ENEMY_EXPLOSION_TIME, EXPLOSION_SIZE_MODIFIER);
                        entityList[i]->isActive = false;
                        gCore.playSound(W_EXPLOSION_1, EXP_VOL*sfxVolume*masterVolume); //entity explosion sound
                    }
                    
                    entityList[i]->state = ES_EXPLODING;
                    /**
                    
                    entityList[i]->RGBA.setVal(1.f, 1.f, 1.f, 1.f);
                    entityList[i]->vel = vmake(0,0); //stop movement if exploding
                    entityList[i]->flipGfx = false;
                    entityList[i]->getHp() = 1.f;
                     **/
                    
                    if (gCore.randchance(50)) {
                        spawnItem(entityList[i]->pos, entityList[i]->getDropscale());
                    }//50% chance to drop item each time
                }
                
                
                if (entityList[i]->state == ES_EXPLODING) {
                    bool isExplosion = entityList[i]->expAnimation(0.f);
                    float w1, w2, h1, h2;
                    w1 = entityList[i]->width;
                    h1 = entityList[i]->height;
                    
                    if (isExplosion) {
                        vec pos = entityList[i]->pos;
                        int width = entityList[i]->width/2;
                        int height = entityList[i]->height/2;
                        
                        vec aniPos = vmake(pos.x+randf(-(float)width, (float)width), pos.y+randf(-(float)height, (float)height));
                        //cout << "POS of ent: (" << pos.x << "," << pos.y << ") , POS of exp: (" << aniPos.x << "," << aniPos.y << ")\n";
                        createAnimation(A_EXP_REG, entityList[i], aniPos, entityList[i]->vel, ENEMY_EXPLOSION_TIME, EXPLOSION_SIZE_MODIFIER);
                        gCore.playSound(W_EXPLOSION_1, EXP_VOL*sfxVolume*masterVolume);
                    }
                    w2 = gCore.getTexWidth(entityList[i]->curGfx)*BOSS_SIZE_MODIFER;
                    h2 = gCore.getTexHeight(entityList[i]->curGfx)*BOSS_SIZE_MODIFER;
                    
                    
                    if (h1 != h2 || w1 != w2) {
                        entityList[i]->pos.y = entityList[i]->pos.y + (h1 - h2)/2;
                        entityList[i]->width = w2;
                        entityList[i]->height = h2;
                    }
                } //play exploding animation
            
                
                if (entityList[i]->state == ES_DESTROYED) {
                    if (entityList[i]->type == E_BOSS && levelBoss != nullptr) {
                        
                    }
                    else
                        entityList[i]->isActive = false;
                }//set all destroyed objects to notActive
                
                
                if (entityList[i]->isActive == false) {
                    delete entityList[i];
                    entityList[i] = nullptr;
                }//delete all notActive objects
                
    //            if (entityList[i]->state == )
            }
        }
        
        //non entity animations (multiple explosions, laser beam charging, special effect, etc...
        for (int i = 0; i < MAX_ANIMATIONS; i++) {
            if (animationList[i] != nullptr) {
                if (animationList[i]->isActive) {
                    animationList[i]->updatePos(); //updates animation position relative to it's parent's velocity
                    
                    switch (animationList[i]->subtype) {
                        case AS_FADE: {
                            animationList[i]->fade();
                            break;
                        }
                        case AS_CYCLING:
                        {
                            animationList[i]->cycleGfx(); //cycle animation GFX
                            animationList[i]->width = gCore.getTexWidth(animationList[i]->curGfx)*animationList[i]->sizeMod;
                            animationList[i]->height = gCore.getTexHeight(animationList[i]->curGfx)*animationList[i]->sizeMod;
                            break;
                        }
                        case AS_STROBE_SIZE:
                        {
                            animationList[i]->strobeSize(); //strobe animation gfx
                            
                            break;
                            
                        }
                        case AS_EXPAND_SIZE:
                        {
                            animationList[i]->expandSize(); // expand size gfx
                            
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    
                }
                else {
                    delete animationList[i];
                    animationList[i] = nullptr;
                }
            }
        }
        
        
        //control playership health values
        if (PSHIP->getHp() > player_stats.playerHP)
            PSHIP->getHp() = player_stats.playerHP;
        
        //Game_state changer
        switch (game_state) {
            case GS_PLAYING:
            {
                if (static_cast<player*>(PSHIP)->deathCheck()) {
                //if (0) { //DEBUG make player invuln
                    game_state = GS_DYING;
                    gCore.stopSound(W_BIGBLUE_SS);
                    gCore.playSound(W_IND_FAILURE, musicVolume*MAX_VOL*masterVolume);
                }//then DEATH!!!
                
                //victory condition
                if (main_timer >= LEVEL_END_TIME) {
                    game_state = GS_BOSSFIGHT;
                }
                break;
            }
            case GS_DYING:
            {
                PSHIP->expAnimation(dying_timer);
                //if (dying_timer >= (DYING_TIME - PLAYER_EXPLOSION_TIME*1.5f) &&  (dying_timer < ((DYING_TIME - PLAYER_EXPLOSION_TIME*1.5f)+0.1f))) {
                if (dying_timer >= (DYING_TIME - PLAYER_EXPLOSION_TIME*1.5)) {
                    if (dying_timer < ((DYING_TIME - PLAYER_EXPLOSION_TIME*1.5f)+0.1f))
                        gCore.playSound(W_EXPLOSION_1, sfxVolume*masterVolume);
                    PSHIP->width = gCore.getTexWidth(PSHIP->curGfx)*PLAYER_EXPLOSION_SIZE_MODIFIER;
                    PSHIP->height = gCore.getTexHeight(PSHIP->curGfx)*PLAYER_EXPLOSION_SIZE_MODIFIER;
                }
                
                
                if (dying_timer >= DYING_TIME) {
                    
                    resetGame();
                }
                dying_timer += 0.1f;
                
                break;
            }
            case GS_BOSSFIGHT:
            {
                if (!isBossSpawned) { //if boss isn't spawned yet, spawn the boss
                    levelBoss = generateBoss(1);
                    isBossSpawned = true;
                }
                
                if (static_cast<player*>(PSHIP)->deathCheck()) {
                //    if (0) { //DEBUG make player invuln
                    game_state = GS_DYING;
                    gCore.stopSound(W_BIGBLUE_SS);
                    gCore.playSound(W_IND_FAILURE, musicVolume*MAX_VOL*masterVolume);
                }//then DEATH!!!
                
                if (victory) {
                    //cout << "victory?\n";
                    game_state = GS_VICTORY;
                    gCore.playSound(W_IND_VICTORY, sfxVolume*MAX_VOL*masterVolume);
                    player_stats.score += PSHIP->getScore();
                    PSHIP->getScore() = 0;
                    main_timer = 0.f;
                }
                break;
            }
            case GS_VICTORY: {
                
                //main_timer = 0.f;
                
                if (main_timer >= VICTORY_SCREEN_TIME) {
                    //cout << "shouldn't see this\n";
                    game_state = GS_STATSCREEN;
                    main_timer = 0.f;
                    gCore.stopAllSounds();
                    gCore.playSound(W_STAT_BRIEFING, musicVolume*masterVolume, true);
                    //currentLevel++;
                    //resetGame();
                }
                break;
            }
            default:
            {
                break;
            }
        }
        
        
        
        
        gCameraPos += G_CAMERA_SPEED;
    }//end IF 1
    
    return(game_state);
    
}//end runLogic()

//===============================================================
//gEngine sleep()
void gEngine::sleep(int ms) {
    
    SYS_Sleep(ms);

}//end sleep()

//MARK: Submethods
//==============================================================================================================================

void gEngine::renderMenu(Menu *menu) {
    if (menu != nullptr) {
        currentMenu = menu;
        curMenuSize = menu->listSize;
        rgba defaul(1.f,1.f,1.f,1.f);
        float spacer = 2.f;
        vec pos = menu->positionOfTop;
        for (int i = 0; i < menu->listSize; i++) {
            if (curSelectedMenuIndex == i) {
                menu->items[i].isChosen = true;
            }
            else if (i > 0)
                menu->items[i].isChosen = false;
            
            rgba RBGA;
            if (menu->items[i].isChosen || menu->items[i].notButton) {
                RBGA = defaul;
            }
            else {
                RBGA = defaul;
                RBGA.a = 0.5f;
            }
            if (i == 0) {
               // spacer = 2.f;
                spacer = 1.25f;
            }
            else {
                spacer = 1.25f;
            }
            pos.y = gCore.RenderCenteredString(menu->items[i].str, pos, menu->items[i].sizeMod, RBGA, 0).y - menu->items[i].sizeMod*16*spacer;
            //pos.y -= pauseMenu->items[i].sizeMod*16; //note: 16 is the pixel height of each font character
        }
    }
    else {
        cout << "Error: menu does not exist\n";
    }
}

//===============================================================
//renderScore()
void gEngine::renderScore(int levelScore, int overallScore) {
    
    char conv[64];
    rgba defaul(1.f,1.f,1.f,1.f);
    float w, h;
    float sizeMod = 2.0f;
    w = gCore.getTexWidth(T_SIZER_KROMASKY)*sizeMod; //find size of the font
    h = gCore.getTexHeight(T_SIZER_KROMASKY)*sizeMod;

    int check = (levelScore + overallScore)/10;
    int size = 1;
    
    while (check != 0) {
        check = check/10;
        size++;
    } //determine the # of digets in currentScore (i.e.  for 100, size = 3)
    
    vec position = vmake(G_WIDTH - (2.5*w + ((size-1)*w/2)  ), G_HEIGHT - (1.5*h)); //shift position of the score so that the rightmost side appears to never move with growing numbers
    
    sprintf(conv, "%d", (levelScore + overallScore));
    
    
    gCore.RenderCenteredString(conv, position, sizeMod, defaul, 0);
    
}

//===============================================================
//generateTerrain()
void gEngine::generateTerrain(int level) {
    rgba defaul(1.f,1.f,1.f,1.f);
    rgba black(0.f,0.f,0.f,1.f);
//    cout << "\n\n\n ++++++++++++++++++++++++++++++\n";
    for (int i = 0; i < gameTerrain->numLines; i++) { // generate background tilemap
        if (gameTerrain->terrainList[i] != nullptr) {
            for (int j = 0; j < gameTerrain->tilesPerLine; j++) {
                gCore.RenderCenteredSprite(gameTerrain->terrainList[i]->pos[j], vmake(gameTerrain->tileW, gameTerrain->tileH), gameTerrain->terrainList[i]->content[j], defaul, 0, 0);
                //DEBUG: made black lines to see shit
                //gCore.RenderCenteredSprite(vmake(j*gameTerrain->tileW,i*gameTerrain->tileH), vmake(2, G_HEIGHT*2), T_LEVEL_BAR, black, 0, 0);
                
                //cout << "TILE: " << ((i*gameTerrain->tilesPerLine)+j) << " id: " << gameTerrain->terrainList[i]->content[j] << " pos: (" << gameTerrain->terrainList[i]->pos[j].x << "," << gameTerrain->terrainList[i]->pos[j].y << ")\n";
             }
            //DEBUG: More black lines
            //gCore.RenderCenteredSprite(vmake(G_WIDTH/2,i*gameTerrain->tileH), vmake(G_WIDTH*2, 2), T_LEVEL_BAR, black, 0, 0);
        }
    }
    
    
    gameTerrain->generateClouds(this);
    //render clouds
  //  float w, h;
    defaul.a = 0.9f;
    for (int i = 0; i < MAX_CLOUDS; i++) {
        if (gameTerrain->cloudList[i] != nullptr) {
            if (gameTerrain->cloudList[i]->isActive) {
                //w = gCore.getTexWidth(gameTerrain->cloudList[i]->cloudGfx)*CLOUD_SIZE_MOD;
                //h = gCore.getTexHeight(gameTerrain->cloudList[i]->cloudGfx)*CLOUD_SIZE_MOD;
                gCore.RenderCenteredSprite(gameTerrain->cloudList[i]->pos, vmake(gameTerrain->cloudList[i]->width,gameTerrain->cloudList[i]->height), gameTerrain->cloudList[i]->cloudGfx, defaul, 0, 0, 1);
            }
        }
    }
}

//===============================================================
//createEntity()
//NOTES: USE 0 for w and h for weapons!
int gEngine::createEntity(EType eType, vec position, vec velocity, int w, int h, float inertia, TexIDs curGFX, TexIDs GFXset[6], bool flipGFX, bool reverseGFX) {
    
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (entityList[i] == nullptr) {
            entity *newEntity;
            switch (eType) {
                case E_PLAYERSHIP:
                {
                    player *newPlayer = new player;
                    newPlayer->subType = EST_PRIMARY_WEP;
                    newPlayer->explosionTimer = 0.f;
                    newPlayer->expTexAmount = size_of(nukeEXP);
                    for (int i = 0; i < (newPlayer->expTexAmount); i++) {
                        newPlayer->expGfxSet[i] = nukeEXP[i];
                    }
                    newPlayer->RGBA.setVal(1.f,1.f,1.f,1.f);
                    newPlayer->hp = player_stats.playerHP;
                    newPlayer->isAnimated = false;
                    newPlayer->reloadTimer = 0.f;
                    newPlayer->secondaryReloadTimer = 0.f;
                    newPlayer->currentWeapon = player_stats.weapons[0];
                    newPlayer->currentSecondaryWeapon = player_stats.weapons[1];
                    newPlayer->tertiaryReloadTimer = 0.f;
                    newPlayer->currentTertiaryWeapon = player_stats.weapons[2];
                    /**
                    newPlayer->gfxSet[0] = player_stats.shipType[0];
                    newPlayer->gfxSet[1] = player_stats.shipType[1];
                    newPlayer->gfxSet[2] = player_stats.shipType[2];
                    newPlayer->gfxSet[3] = player_stats.shipType[3];
                    newPlayer->gfxSet[4] = player_stats.shipType[4];
                    **/
                    newPlayer->gfxSet[0] = GFXset[0];
                    newPlayer->gfxSet[1] = GFXset[1];
                    newPlayer->gfxSet[2] = GFXset[2];
                    newPlayer->gfxSet[3] = GFXset[3];
                    newPlayer->gfxSet[4] = GFXset[4];
                    newPlayer->width = gCore.getTexWidth(curGFX)*PLAYER_SHIP_SIZE_MODIFIER;
                    newPlayer->height = gCore.getTexHeight(curGFX)*PLAYER_SHIP_SIZE_MODIFIER;
                    newPlayer->numGfx = 5;
                    newPlayer->curScore = 0;
                    newEntity = newPlayer;
                    break;
                }
                case E_JET:
                {
                    enemy *newEnemy = new enemy;
                    newEnemy->direction = D_STRAIGHT;
                    newEnemy->directionTimer = 0.f;
                    newEnemy->animationTimer = 0.f;
                    newEnemy->RGBA.setVal(1.f,1.f,1.f,1.f);
                    newEnemy->isAnimated = false;
                    newEnemy->hp = EN_JET_MAX_HP;
                    newEnemy->explosionTimer = 0.f;
                    newEnemy->dropscale = 1;
                    newEnemy->expTexAmount = size_of(regEXP);
                    for (int i = 0; i < (newEnemy->expTexAmount); i++) {
                        newEnemy->expGfxSet[i] = regEXP[i];
                    }
                    //cout << newEnemy->expTexAmount << endl;
                    //newEnemy->expGfxSet = regEXP;
                    newEnemy->reloadTimer = 0.f;
                    newEnemy->secondaryReloadTimer = 0.f;
                    newEnemy->currentWeapon = T_BLOB_SHOT;
                    newEnemy->currentSecondaryWeapon = T_BKG;
                    newEnemy->tertiaryReloadTimer = 0.f;
                    newEnemy->currentTertiaryWeapon = T_BKG;
                    newEnemy->gfxSet[0] = GFXset[0];
                    newEnemy->gfxSet[1] = GFXset[1];
                    newEnemy->gfxSet[2] = GFXset[2];
                    newEnemy->gfxSet[3] = GFXset[3];
                    newEnemy->gfxSet[4] = GFXset[4];
                    newEnemy->width = gCore.getTexWidth(curGFX)*ENEMY_SIZE_MOD;
                    newEnemy->height = gCore.getTexHeight(curGFX)*ENEMY_SIZE_MOD;
                    newEnemy->numGfx = 5;
                    newEnemy->hitTimer = 0.f;
                    newEnemy->scoreVal = SCORE_GJET;
                    newEntity = newEnemy;
                    break;
                }
                case E_JET_2: //bomber ship, only has secondary weapon
                {
                    enemy *newEnemy = new enemy;
                    newEnemy->subType = EST_SECONDARY_WEP;
                    newEnemy->direction = D_STRAIGHT;
                    newEnemy->directionTimer = 0.f;
                    newEnemy->animationTimer = 0.f;
                    newEnemy->RGBA.setVal(1.f,1.f,1.f,1.f);
                    newEnemy->isAnimated = false;
                    newEnemy->hp = EN_JET2_MAX_HP;
                    newEnemy->explosionTimer = 0.f;
                    newEnemy->dropscale = 1;
                    newEnemy->expTexAmount = size_of(regEXP);
                    for (int i = 0; i < (newEnemy->expTexAmount); i++) {
                        newEnemy->expGfxSet[i] = regEXP[i];
                    }
                    //cout << newEnemy->expTexAmount << endl;
                    //newEnemy->expGfxSet = regEXP;
                    newEnemy->reloadTimer = 0.f;
                    newEnemy->secondaryReloadTimer = 0.f;
                    newEnemy->currentWeapon = T_BKG; //default null texture
                    newEnemy->currentSecondaryWeapon = T_ROCKET2;
                    newEnemy->tertiaryReloadTimer = 0.f;
                    newEnemy->currentTertiaryWeapon = T_BKG;
                    newEnemy->numGfx = size_of(greenShip2);
                    newEnemy->width = gCore.getTexWidth(curGFX)*ENEMY_SIZE_MOD;
                    newEnemy->height = gCore.getTexHeight(curGFX)*ENEMY_SIZE_MOD;
                    for (int i = 0; i < (newEnemy->numGfx); i++) {
                        newEnemy->gfxSet[i] = GFXset[i];
                    }
                    newEnemy->hitTimer = 0.f;
                    newEnemy->scoreVal = SCORE_MJET;
                    newEntity = newEnemy;
                    break;
                }
                case E_RED_JET:
                {
                    enemy *newEnemy = new enemy;
                    newEnemy->subType = EST_SECONDARY_WEP;
                    newEnemy->direction = D_STRAIGHT;
                    newEnemy->directionTimer = 0.f;
                    newEnemy->animationTimer = 0.f;
                    newEnemy->RGBA.setVal(1.f,1.f,1.f,1.f);
                    newEnemy->isAnimated = false;
                    newEnemy->hp = EN_REDJET_MAX_HP;
                    newEnemy->explosionTimer = 0.f;
                    newEnemy->dropscale = 1;
                    newEnemy->expTexAmount = size_of(regEXP);
                    for (int i = 0; i < (newEnemy->expTexAmount); i++) {
                        newEnemy->expGfxSet[i] = regEXP[i];
                    }
                    //cout << newEnemy->expTexAmount << endl;
                    //newEnemy->expGfxSet = regEXP;
                    newEnemy->reloadTimer = 0.f;
                    newEnemy->secondaryReloadTimer = 0.f;
                    newEnemy->currentWeapon = T_BLOB_SHOT; //default null texture
                    newEnemy->currentSecondaryWeapon = T_ROCKET2;
                    newEnemy->tertiaryReloadTimer = 0.f;
                    newEnemy->currentTertiaryWeapon = T_BKG;
                    newEnemy->numGfx = size_of(redShip);
                    newEnemy->width = gCore.getTexWidth(curGFX)*ENEMY_SIZE_MOD;
                    newEnemy->height = gCore.getTexHeight(curGFX)*ENEMY_SIZE_MOD;
                    for (int i = 0; i < (newEnemy->numGfx); i++) {
                        newEnemy->gfxSet[i] = GFXset[i];
                    }
                    newEnemy->hitTimer = 0.f;
                    newEntity = newEnemy;
                    break;
                }
                case E_BLADE:
                {
                    enemy *newEnemy = new enemy;
                    newEnemy->subType = EST_NULL;

                    if (randchance(50)) {
                        newEnemy->direction = D_LEFT;
                        if (velocity.x > 0) {
                            velocity = vscale(velocity, -1);
                        }
                    }
                    else {
                        newEnemy->direction = D_RIGHT;
                        if (velocity.x < 0) {
                            velocity = vscale(velocity, -1);
                        }
                    }
                    
                    newEnemy->directionTimer = 0.f;
                    newEnemy->animationTimer = 0.f;
                    newEnemy->RGBA.setVal(1.f,1.f,1.f,1.f);
                    newEnemy->isAnimated = true;
                    newEnemy->hp = EN_BLADE_MAX_HP;
                    newEnemy->explosionTimer = 0.f;
                    newEnemy->dropscale = 1;
                    newEnemy->expTexAmount = size_of(regEXP);
                    for (int i = 0; i < (newEnemy->expTexAmount); i++) {
                        newEnemy->expGfxSet[i] = regEXP[i];
                    }
                    //cout << newEnemy->expTexAmount << endl;
                    //newEnemy->expGfxSet = regEXP;
                    newEnemy->reloadTimer = 0.f;
                    newEnemy->secondaryReloadTimer = 0.f;
                    newEnemy->currentWeapon = T_BKG; //default null texture
                    newEnemy->currentSecondaryWeapon = T_BKG; //default null txt
                    newEnemy->tertiaryReloadTimer = 0.f;
                    newEnemy->currentTertiaryWeapon = T_BKG;
                    newEnemy->numGfx = size_of(blade);
                    newEnemy->width = gCore.getTexWidth(curGFX)*ENEMY_SIZE_MOD;
                    newEnemy->height = gCore.getTexHeight(curGFX)*ENEMY_SIZE_MOD;
                    for (int i = 0; i < (newEnemy->numGfx); i++) {
                        newEnemy->gfxSet[i] = GFXset[i];
                    }
                    newEnemy->hitTimer = 0.f;
                    newEnemy->scoreVal = SCORE_BLADE;
                    newEntity = newEnemy;
                    break;
                }
                case E_BOSS:
                {
                    bossSegment *newBossSeg = new bossSegment;
                    newBossSeg->reloadTimer = 0.f;
                    newBossSeg->hp = BOSS_SEGMENT_HP;
                    newEntity = newBossSeg;
                    break;
                }
                case E_PLAYER_WEAPON:
                {
                    weapon *newWeapon = new weapon;
                    newWeapon->RGBA.setVal(1.f,1.f,1.f,1.f);
                    newWeapon->subType = EST_PRIMARY_WEP;
                    switch (curGFX) {
                        case T_SINGLE_SHOT:
                        {
                            newWeapon->damage = SINGLE_BLASTER_DMG;
                            newWeapon->isAnimated = false;
                            newWeapon->reloadInterval = SINGLE_BLASTER_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_SINGLE_SHOT)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_SINGLE_SHOT)*WEAPON_SIZE_MODIFER;
                            //cout << newWeapon->width << " " << newWeapon->height << endl;
                            break;
                        }
                        case T_DOUBLE_SHOT:
                        {
                            newWeapon->damage = SINGLE_BLASTER_DMG*2;
                            newWeapon->isAnimated = false;
                            newWeapon->reloadInterval = SINGLE_BLASTER_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_DOUBLE_SHOT)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_DOUBLE_SHOT)*WEAPON_SIZE_MODIFER;
                            break;
                        }
                        case T_TRIPLE_SHOT:
                        {
                            newWeapon->damage = SINGLE_BLASTER_DMG*3;
                            newWeapon->isAnimated = false;
                            newWeapon->reloadInterval = SINGLE_BLASTER_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_TRIPLE_SHOT)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_TRIPLE_SHOT)*WEAPON_SIZE_MODIFER;
                            break;
                        }
                        case T_QUAD_SHOT:
                        {
                            newWeapon->damage = SINGLE_BLASTER_DMG*4;
                            newWeapon->reloadInterval = SINGLE_BLASTER_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_QUAD_SHOT)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_QUAD_SHOT)*WEAPON_SIZE_MODIFER;
                            break;
                        }
                        case T_ROCKET1:
                        {
                            newWeapon->subType = EST_SECONDARY_WEP;
                            newWeapon->isAnimated = false;
                            newWeapon->damage = ROCKET_DAMAGE;
                            newWeapon->reloadInterval = ROCKET_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_ROCKET1)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_ROCKET1)*WEAPON_SIZE_MODIFER;
                            break;
                        }
                        case T_ROCKET2:
                        {
                            newWeapon->subType = EST_SECONDARY_WEP;
                            newWeapon->isAnimated = false;
                            newWeapon->damage = ROCKET_DAMAGE;
                            newWeapon->reloadInterval = ROCKET_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_ROCKET2)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_ROCKET2)*WEAPON_SIZE_MODIFER;
                            break;
                        }
                        case T_BLOB_SHOT:
                        {
                            newWeapon->damage = SINGLE_BLASTER_DMG;
                            newWeapon->isAnimated = false;
                            newWeapon->reloadInterval = SINGLE_BLASTER_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_BLOB_SHOT)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_BLOB_SHOT)*WEAPON_SIZE_MODIFER;
                            //cout << newWeapon->width << " " << newWeapon->height << endl;
                            break;
                        }
                        case T_SIDEWAYS_ML_SINGLE_SHOT:
                        {
                            newWeapon->damage = SINGLE_BLASTER_DMG;
                            newWeapon->isAnimated = false;
                            newWeapon->reloadInterval = SINGLE_BLASTER_RELOAD;
                            newWeapon->width = gCore.getTexWidth(curGFX)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(curGFX)*WEAPON_SIZE_MODIFER;
                            break;
                        }
                        default:
                        {
                            delete newWeapon;
                            return(-1);
                            break;
                        }
                    }//different weapon damage vals and reloadValues for different weapons
                    newEntity = newWeapon;
                    break;
                }
                case E_ENEMY_WEAPON:
                {
                    
                    weapon *newWeapon = new weapon;
                    newWeapon->RGBA.setVal(1.f,1.f,1.f,1.f);
                    switch (curGFX) {
                        case T_SINGLE_SHOT:
                        {
                            newWeapon->RGBA.setVal(0.f,1.f,1.f,1.f);
                            newWeapon->damage = EN_SINGLE_BLASTER_DMG;
                            newWeapon->isAnimated = false;
                            newWeapon->reloadInterval = EN_SINGLE_BLASTER_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_SINGLE_SHOT)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_SINGLE_SHOT)*WEAPON_SIZE_MODIFER;
                            
                            break;
                        }
                        case T_BLOB_SHOT:
                        {
                            
                            newWeapon->damage = EN_SINGLE_BLASTER_DMG;
                            newWeapon->isAnimated = false;
                            newWeapon->reloadInterval = EN_SINGLE_BLASTER_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_BLOB_SHOT)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_BLOB_SHOT)*WEAPON_SIZE_MODIFER;
                            //cout << newWeapon->width << " " << newWeapon->height << endl;
                            break;
                        }
                        case T_ROCKET2:
                        {
                            newWeapon->subType = EST_SECONDARY_WEP;
                            newWeapon->damage = EN_ROCKET_DMG;
                            newWeapon->reloadInterval = EN_ROCKET_RELOAD;
                            newWeapon->width = gCore.getTexWidth(T_ROCKET2)*WEAPON_SIZE_MODIFER;
                            newWeapon->height = gCore.getTexHeight(T_ROCKET2)*WEAPON_SIZE_MODIFER;
                            break;
                        }
                        default:
                        {
                            //cout << "invalid weapon entry\n";
                            delete newWeapon;
                            return(-1);
                            break;
                        }
                    }//different weapon damage vals and reloadValues for different weapons
                    newEntity = newWeapon;
                    break;
                }
                case E_ENEMY_LASER:
                {
                    laser* newLaser = new laser;

                    switch (curGFX) {
                        case T_BLUE_LASER_BASE:
                        {
                            //cout << "CHECKsqpasdoifj\n";
                            
                            newLaser->damage = EN_BLUE_LAZER_DMG;
                            newLaser->isAnimated = false;
                            newLaser->reloadInterval = EN_BLUE_LAZER_RELOAD_TIME;
                            newLaser->width = gCore.getTexWidth(T_BLUE_LASER_SHAFT)*WEAPON_SIZE_MODIFER;
                            newLaser->height = G_HEIGHT;
                            //curGFX = T_HP_BAR;

                        
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    newEntity = newLaser;
                    break;
                }
                case E_HEALTHUP:
                {
                    item *newItem = new item;
                    
                    switch (curGFX) {
                        case T_HP_BLOB1: {
                            newItem->hpIncrease = HP_BLOB_HEALTH_INCREASE;
                            newItem->numGFXanimations = size_of(hpBlob);
                            for (int i = 0; i < size_of(hpBlob); i++) {
                                newItem->gfxSet[i] = hpBlob[i];
                                
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    newItem->animation_timer = 0.f;
                    newItem->curGfx = curGFX;
                    newItem->width = gCore.getTexWidth(curGFX)*ITEM_SIZE_MODIFIER;
                    newItem->height = gCore.getTexHeight(curGFX)*ITEM_SIZE_MODIFIER;
                    
                    newItem->isAnimated = true;
                    newEntity = newItem;
                    break;
                }
                case E_POWERUP:
                {
                    item *newItem = new item;
                    newItem->hpIncrease = 0.f;
                    newItem->numGFXanimations = 0;
                    //cout << "creating powerup:\n";
                    //cout << "curGFX: " << curGFX << endl;
                    switch (curGFX) {
                        case T_UPG_OMEGA_BOMB:
                        {
                            newItem->wepUpgrade = T_UPG_OMEGA_BOMB;
                            newItem->subType = EST_NULL;
                            break;
                        }
                        case T_UPG_DOUBLE_SHOT:
                        {
                            newItem->wepUpgrade = T_DOUBLE_SHOT;
                            newItem->subType = EST_PRIMARY_WEP;
                            break;
                        }
                        case T_UPG_TRIPLE_SHOT:
                        {
                            newItem->wepUpgrade = T_TRIPLE_SHOT;
                            newItem->subType = EST_PRIMARY_WEP;
                            break;
                            
                        }
                        case T_UPG_SINGLE_ROCKET:
                        {
                            newItem->wepUpgrade = T_ROCKET1;
                            newItem->subType = EST_SECONDARY_WEP;
                            break;
                        }
                        case T_UPG_SINGLE_SIDEWAYS_SHOT_M:
                        {
                            newItem->wepUpgrade = T_SIDEWAYS_ML_SINGLE_SHOT;
                            newItem->subType = EST_TERTIARY_WEP;
                            break;
                        }
                        default:
                            break;
                    }
                    newItem->curGfx = curGFX;
                    //cout << "curGfx: " << newItem->curGfx << endl;
                    newItem->width = gCore.getTexWidth(curGFX)*ITEM_SIZE_MODIFIER;
                    newItem->height = gCore.getTexHeight(curGFX)*ITEM_SIZE_MODIFIER;
                    //newItem->width = 1;
                    //newItem->height = 1;
                    //cout << "W: " << newItem->width << " H: " << newItem->height << endl;
                    if (newItem->numGFXanimations) {
                        newItem->isAnimated = true;
                    }
                    newItem->isAnimated = false;
                    newEntity = newItem;
                    //cout << "curGfx: " << newEntity->curGfx << endl;

                    break;
                }
                default:
                {
                    cout << "Error: invalid entity type specified\n";
                    return(-1);
                    break;
                }
            }
            
            if (eType == E_ENEMY_LASER) {
                newEntity->isRendered = false;
            }
            else {
                newEntity->isRendered = true;
            }
            newEntity->type = eType;
            newEntity->state = ES_ALIVE;
            //newEntity->RGBA.setVal(0.f,0.f,0.f,1.f);
            newEntity->isActive = true;
            newEntity->pos = position;
            newEntity->vel = velocity;
            if (w != 0)
                newEntity->width = w;
            if (h != 0)
                newEntity->height = h;
            newEntity->Id = i;
            newEntity->inertia = inertia;
            newEntity->curGfx = curGFX;
            newEntity->flipGfx = flipGFX;
            newEntity->reverseGfx = reverseGFX;
            entityList[i] = newEntity;
            //cout << flipGFX << endl;
            return(i);
        }
    }//search for empty spot to put a new entity
    return(-1);

}//End createEntity()

//===============================================================
//createAnimation()
int gEngine::createAnimation(AType aType, entity *parentE, vec position, vec velocity, float animationLen, float sizeModifier, int numRepeats, bool flipGFX) {

    for (int i = 0; i < MAX_ANIMATIONS; i++) {
        if (animationList[i] == nullptr) {

            animation *newAnimation = new animation;
            newAnimation->type = aType;
            newAnimation->width = 0;
            newAnimation->height = 0;
            
            
            newAnimation->multiSegments = false;
            newAnimation->parent = parentE;
            newAnimation->isActive = true;
            newAnimation->sizeMod = sizeModifier;
            newAnimation->aniTimer = 0.f;
            newAnimation->aniLength = animationLen;
            newAnimation->pos = position;
            newAnimation->vel = velocity;
            newAnimation->RGBA = rgba(1.f,1.f,1.f,1.f);
            newAnimation->flipGfx = flipGFX;
            newAnimation->numOfRepeats = numRepeats;
            
            switch (aType) {
                case A_BLACK_FULL_TRANSITION:
                {
                    newAnimation->subtype = AS_FADE;
                    newAnimation->numGfx = 1;
                    newAnimation->curGfx = T_BKG;
                    newAnimation->gfxSet[0] = T_BKG;
                    newAnimation->height = G_HEIGHT;
                    newAnimation->width = G_WIDTH;
                    newAnimation->RGBA = rgba(0.f,0.f,0.f,0.f);
                    break;
                }
                case A_BLACK_FADE_IN:
                {
                    newAnimation->subtype = AS_FADE;
                    newAnimation->numGfx = 1;
                    newAnimation->curGfx = T_BKG;
                    newAnimation->gfxSet[0] = T_BKG;
                    newAnimation->height = G_HEIGHT;
                    newAnimation->width = G_WIDTH;
                    newAnimation->RGBA = rgba(0.f,0.f,0.f,0.f);
                    break;
                }
                case A_WHITE_FADE_IN:
                {
                    newAnimation->subtype = AS_FADE;
                    newAnimation->numGfx = 1;
                    newAnimation->curGfx = T_WHITE;
                    newAnimation->gfxSet[0] = T_WHITE;
                    newAnimation->height = G_HEIGHT;
                    newAnimation->width = G_WIDTH;
                    newAnimation->RGBA = rgba(1.f,1.f,1.f,1.f);
                    break;
                }
                case A_HALO:
                {
                    newAnimation->subtype = AS_EXPAND_SIZE;
                    newAnimation->numGfx = 1;
                    newAnimation->gfxSet[0] = T_HALO;
                    newAnimation->width = 12*6.f;
                    newAnimation->height = 12*6;
                    break;
                }
                case A_EXP_REG:
                {
                    newAnimation->subtype = AS_CYCLING;
                    newAnimation->numGfx = size_of(regEXP);
                    for (int j = 0; j < newAnimation->numGfx; j++) {
                        newAnimation->gfxSet[j] = regEXP[j];
                    }
                    
                    break;
                }
                case A_EXP_NUKE:
                {
                    newAnimation->subtype = AS_CYCLING;
                    newAnimation->numGfx = size_of(nukeEXP);
                    for (int j = 0; j < newAnimation->numGfx; j++) {
                        newAnimation->gfxSet[j] = nukeEXP[j];
                    }
                    break;
                }
                case A_BLUE_LAZER_CHARGE:
                {
                    newAnimation->subtype = AS_STROBE_SIZE;
                    newAnimation->gfxSet[0] = blueLaser[0];
                    newAnimation->numGfx = 1;
                    break;
                }
                case A_BLUE_LAZER:
                {
                    newAnimation->subtype = AS_STROBE_SIZE;
                    newAnimation->numGfx = size_of(blueLaser);
                    for (int j = 0; j < newAnimation->numGfx; j++) {
                        newAnimation->gfxSet[j] = blueLaser[j];
                    }
                    newAnimation->multiSegments = true;
                    newAnimation->height = position.y;
                    break;
                }
                default:
                {
                    newAnimation->numGfx = 0;
                    break;
                }
                    
            }
            
            if (newAnimation->numGfx > 0) {

                newAnimation->curGfx = newAnimation->gfxSet[0];
                if (newAnimation->width == 0)
                    newAnimation->width = gCore.getTexWidth(newAnimation->curGfx)*sizeModifier;
                if (newAnimation->height == 0)
                    newAnimation->height = gCore.getTexHeight(newAnimation->curGfx)*sizeModifier;
                newAnimation->iniWidth = newAnimation->width;
                newAnimation->iniHeight = newAnimation->height;
            }
            animationList[i] = newAnimation;
            return(i);
        }
    }
    
    
    
    return(-1);
}

//===============================================================
//stopAllAnimations
void gEngine::stopAllAnimations(void) {
    for (int i = 0; i < MAX_ANIMATIONS; i++) {
        if (animationList[i] != nullptr) {
            delete animationList[i];
            animationList[i] = nullptr;
        }
    }
}

//===============================================================
//moveAniToFront
void gEngine::moveAniToFront(int index) {
    for (int i = MAX_ANIMATIONS-1; i >= 0; i--) {
        if (animationList[i] == nullptr) {
            animationList[i] = animationList[index];
            animationList[index] = nullptr;
        }
    }
}

//===============================================================
//generateLevelEnemies()
void gEngine::generateLevelEnemies(void) {
    
    switch (currentLevel) {
        case 1:
        {
            generateEnemy(E_JET, (1.f + (MAX_SPAWN_RATE)*(main_timer/LEVEL_END_TIME)), L_TOP); //(1 + (Max spawn rate)*lvl progress)%  chance to generate an enemy ship every frame
            break;
        }
        case 2:
        {
            generateEnemy(E_JET, (2.f + (MAX_SPAWN_RATE)*(main_timer/LEVEL_END_TIME)), L_TOP); //(1 + (Max spawn rate)*lvl progress)%  chance to generate an enemy ship every frame
            if (main_timer >= LEVEL_END_TIME/2)
                generateEnemy(E_JET_2, (1.f + MAX_SPAWN_RATE*((main_timer - LEVEL_END_TIME/2)/LEVEL_END_TIME/2)), L_TOP);
            break;
        }
        case 3:
        {
            generateEnemy(E_JET, (2.f + (MAX_SPAWN_RATE)*(main_timer/LEVEL_END_TIME)), L_TOP);
            generateEnemy(E_JET_2, (1.f + (MAX_SPAWN_RATE/2)*((main_timer)/LEVEL_END_TIME)), L_TOP);
            if (main_timer >= LEVEL_END_TIME/2)
                generateEnemy(E_BLADE, (1.f + MAX_SPAWN_RATE*((main_timer - LEVEL_END_TIME/2)/LEVEL_END_TIME/2)), L_TOP);
            break;
        }
        case 4:
        {
            generateEnemy(E_JET, (1.f + (MAX_SPAWN_RATE/2)*(main_timer/LEVEL_END_TIME)), L_TOP);
            generateEnemy(E_JET_2, (1.f + (MAX_SPAWN_RATE/4)*((main_timer)/LEVEL_END_TIME)), L_TOP);
            generateEnemy(E_BLADE, (1.f + (MAX_SPAWN_RATE/4)*((main_timer/LEVEL_END_TIME))), L_TOP);
            if (main_timer >= LEVEL_END_TIME/3)
                generateEnemy(E_JET, (1.f + (MAX_SPAWN_RATE/4)*((main_timer - LEVEL_END_TIME/3)/LEVEL_END_TIME/3)), L_BOTTOM);
            break;
        }
        case 5:
        {
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            break;
        }
        default:
        {
            break;
        }
    }

}

//===============================================================
//generateEnemy()
void gEngine::generateEnemy(EType etype, float chanceToSpawn, location spawnLOC) {
    bool isGenerated;
    isGenerated = gCore.randchance(chanceToSpawn);

    if (isGenerated) {
        //find location
        vec spawnLoc;
        bool gfxOri;
        int velMod;
        switch (spawnLOC) {
            case L_TOP:
            {
                velMod = 1;
                gfxOri = true;
                spawnLoc = vmake((gCore.randf(G_WIDTH*.1, G_WIDTH*.9)),(gCore.randf(G_HEIGHT*1.1, G_HEIGHT*1.2)));
                break;
            }
            case L_BOTTOM:
            {
                velMod = -1;
                gfxOri = false;
                spawnLoc = vmake((gCore.randf(G_WIDTH*.1, G_WIDTH*.9)),(0 - gCore.randf(G_HEIGHT*0.1, G_HEIGHT*0.2)));
                break;
            }
            default:
            {
                velMod = 1;
                gfxOri = true;
                spawnLoc = vmake((gCore.randf(G_WIDTH*.1, G_WIDTH*.9)),(gCore.randf(G_HEIGHT*1.1, G_HEIGHT*1.2)));
                break;
            }
                
        }
        
        
        //create switch statement for different etypes or perhaps expand entity labels in createEntity
        //createEntity(etype, spawnLoc, STRAIGHT_VEC, PLAYER_SHIP_W, PLAYER_SHIP_H, 0.f, greenShip[2], greenShip, 1);
        if (etype == E_JET) {
            createEntity(etype, spawnLoc, vscale(STRAIGHT_VEC, velMod), 0, 0, 0.f, greenShip[2], greenShip, gfxOri);
        }
        else if (etype == E_JET_2) {
            createEntity(etype, spawnLoc, vscale(STRAIGHT_VEC, velMod), 0, 0, 0.f, greenShip2[2], greenShip2, gfxOri);
        }
        else if (etype == E_BLADE) {
            createEntity(etype, spawnLoc, vmake(randf(EN_BLADE_MIN_X_VEL, EN_BLADE_MAX_X_VEL), (velMod)*randf(EN_BLADE_MIN_Y_VEL, EN_BLADE_MAX_Y_VEL)), 0, 0, 0.f, blade[2], blade, gfxOri);
        }
        enemiesSpawned++;
    }//generate enemy
    
}//end generateEnemy()

//===============================================================
//generateBoss()
boss* gEngine::generateBoss(int level) {
    boss *newBoss = new boss;
    newBoss->velocity = vmake(0,0);
    newBoss->width = 0;
    newBoss->height = 0;
    newBoss->healthpool = 0;
    newBoss->maxHealth = 0;
    newBoss->introTimer = 0.f;
    newBoss->explosionTimer = 0.f;
    enemiesSpawned++;
    //cout << "CHECK}\n";[
    switch (level) {
        case 1:
        {
            newBoss->omegaWepTimer = 0.f;
            newBoss->omegaChamberCycleTime = BOSS_OMEGA_CHAMBER_CYCLE_TIME;
            newBoss->omegaWepChargeTime = BOSS_OMEGA_CHARGE_TIME;
            newBoss->omegaWepFireTime = EN_BLUE_LAZER_BLAST_TIME;
            newBoss->numOfSegments = 4;
            newBoss->scoreVal = SCORE_BOSS1;
            newBoss->segments = new entity*[newBoss->numOfSegments];
            
            
            newBoss->position = vmake(G_WIDTH/2, G_HEIGHT/2); //position of the centermost segment
            //for (int i = 0; i < newBoss->numOfSegments; i++) {
            
            
            vec pos; //= vmake(newBoss->position.x-(gCore.getTexWidth(boss1body[1]) + gCore.getTexWidth(boss1body[0])), newBoss->position.y);
            
            float distanceFromCenter = (gCore.getTexWidth(boss1body[1])/2 + gCore.getTexWidth(boss1body[0])/2)*BOSS_SIZE_MODIFER;

            //create the body entities for the boss
            for (int i = 0; i < 3; i++) {
                pos = vmake((newBoss->position.x - distanceFromCenter + distanceFromCenter*i), newBoss->position.y);
                
                newBoss->segments[i] = entityList[createEntity(E_BOSS, pos, newBoss->velocity, gCore.getTexWidth(boss1body[i])*BOSS_SIZE_MODIFER, gCore.getTexHeight(boss1body[i])*BOSS_SIZE_MODIFER, 0, boss1body[i], boss1body)];
                //entity *hello = entityList[0];
                
                for (int j = 0; j < size_of(boss1body); j++) {
                    newBoss->segments[i]->gfxSet[j] = boss1body[j];
                }
                newBoss->segments[i]->numGfx = size_of(boss1body);
                if (newBoss->height < newBoss->segments[i]->height) {
                    newBoss->height = newBoss->segments[i]->height;
                }
                newBoss->width += newBoss->segments[i]->width;
                newBoss->segments[i]->getCurWeapon() = T_BLOB_SHOT;
            }
            
            vec startPos = vmake(G_WIDTH/2, G_HEIGHT+(newBoss->height)/2 );
            newBoss->position = startPos;
            for (int i = 0; i < 3; i++) {
                pos = vmake((newBoss->position.x - distanceFromCenter + distanceFromCenter*i), newBoss->position.y);
                
                newBoss->segments[i]->pos = pos;

            }
            
            
            //centerpiece
            float offset = 25.f + 8; //*BOSS_SIZE_MODIFER;
            pos = vmake( newBoss->position.x-2.f, newBoss->position.y+offset);
            
            newBoss->segments[3] = entityList[createEntity(E_BOSS, pos, newBoss->velocity, gCore.getTexWidth(boss1charge[0])*BOSS_SIZE_MODIFER, gCore.getTexHeight(boss1charge[0])*BOSS_SIZE_MODIFER, 0, boss1charge[0], boss1charge)];
            for (int j = 0; j < size_of(boss1charge); j++) {
                newBoss->segments[3]->gfxSet[j] = boss1charge[j];
            }
            newBoss->segments[3]->numGfx = size_of(boss1charge);
            newBoss->segments[3]->getCurWeapon() = T_BLUE_LASER_BASE;
            vec endIntroPos = vmake(G_WIDTH, G_HEIGHT-((float)newBoss->height/2));
            newBoss->endIntroPosition = endIntroPos;
            newBoss->velocity = vmake(0.f, -(startPos.y - endIntroPos.y)/(BOSS_INTRO_TIME*10.f));
            
            
            newBoss->posBoundaries = bmake(0+((float)newBoss->width/2)*.30, G_WIDTH-((float)newBoss->width/2)*.30, (G_HEIGHT - ((float)newBoss->height)*.70), (G_HEIGHT + (float)newBoss->height*1.1));
            
            for (int i = 0; i < newBoss->numOfSegments; i++) {
                
                //DEBUG current weapons are placeholders
                newBoss->segments[i]->getCurWeapon() = T_BLOB_SHOT;
                
                newBoss->healthpool += newBoss->segments[i]->getHp();
            }
            newBoss->segments[newBoss->numOfSegments-1]->getCurWeapon() = T_BLUE_LASER_BASE;


            
            
            break;
        }
        default:
        {
            break;
        }
    }
    
    newBoss->maxHealth = newBoss->healthpool;
    return(newBoss);
    
}

//===============================================================
//spawnItem()
void gEngine::spawnItem(vec pos, int dropscale) {
    vec vel = vmake(gCore.randf(-1, 1), gCore.randf(-1,1));
    EType etype;
    TexIDs upg;
    
        
    
    if (gCore.randchance(dropscale*4)) {  //chance to spawn amazing item
        etype = E_POWERUP;
        upg = T_UPG_TRIPLE_SHOT;
    }
    else if (gCore.randchance(dropscale*5)) {
        etype = E_POWERUP;
        upg = T_UPG_SINGLE_ROCKET;
    }
    else if (gCore.randchance(dropscale*5)) {
        etype = E_POWERUP;
        upg = T_UPG_OMEGA_BOMB;
    }
    else if (gCore.randchance(dropscale*7)) {
        etype = E_POWERUP;
        upg = T_UPG_SINGLE_SIDEWAYS_SHOT_M;
    }
    else if (gCore.randchance(dropscale*10)) { //chance to spawn regular item
        etype = E_POWERUP;
        upg = T_UPG_DOUBLE_SHOT;
    }
    else if (gCore.randchance(dropscale*33)) { //chance to spawn healthblob
        etype = E_HEALTHUP;
    }
    else
        etype = E_NULL;
    
    
    switch (etype) {
        case E_HEALTHUP:
        {
            createEntity(etype, pos, vel, 0, 0, 0, T_HP_BLOB1, hpBlob);
            break;
        }
        case E_POWERUP:
        {
            createEntity(etype, pos, vel, 0, 0, 0, upg, {});
            break;
        }
        default:
        {
            break;
        }
    }
        
        
        
        
    
    
}//end spawnItem()


//===============================================================
//resetGame()
void gEngine::resetGame(void) {
    //cout << "Cur GS: " << game_state << endl;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        delete entityList[i];
        entityList[i] = nullptr;
    }
    for (int i = 0; i < MAX_ANIMATIONS; i++) {
        delete animationList[i];
        animationList[i] = nullptr;
    }
    
    gCore.stopAllSounds();
    gCore.playSound(W_BIGBLUE_SS, musicVolume*masterVolume, true);
    
    //statistic intialization
    enemiesSpawned = 0;
    enemiesKilled = 0;
    
    shotsFired = 0;
    shotsHit = 0;
    
    hpGained = 0.f;
    hpLost = 0.f;
    
    victory = false;
    gameTerrain->clearMap();
    gameTerrain->initializeMap(this);
    main_timer = 0.f;
    //key_timer = 0.f;
    dying_timer = 0.f;
    gCameraPos = 0.f;
    isBossSpawned = false;
    
    game_state = GS_PLAYING;
    
    //create the player ship
    
    createEntity(E_PLAYERSHIP, vmake(G_WIDTH/2.0f,(0+(gCore.getTexHeight(player_stats.shipType[2])/2))), vmake(0,0), 0, 0, 0, player_stats.shipType[2], player_stats.shipType); //this is how you insert entities into the entityList now
    static_cast<player*>(PSHIP)->numOmegaWeapon = 2;
    //static_cast<player*>(PSHIP)->currentTertiaryWeapon = T_SIDEWAYS_ML_SINGLE_SHOT;
    levelBoss = nullptr;
    //DEBUG
    //createAnimation(A_EXP_REG, nullptr, vmake(G_WIDTH/2, G_HEIGHT/2), vmake(0,0), ENEMY_EXPLOSION_TIME, EXPLOSION_SIZE_MODIFIER);
    //createAnimation(A_BLUE_LAZER_CHARGE, PSHIP, vmake(G_WIDTH/2, G_HEIGHT/2), vmake(0,0), ENEMY_EXPLOSION_TIME, EXPLOSION_SIZE_MODIFIER);
    //createAnimation(A_BLUE_LAZER, PSHIP, PSHIP->pos, vmake(0,0), EN_BLUE_LAZER_BLAST_TIME, EXPLOSION_SIZE_MODIFIER);
    //levelBoss = generateBoss(1);
    
    
    
}//end resetGame()

//===============================================================
//spawnEnemy()
//DEBUG FUNCTION
void gEngine::spawnEnemy(void) {
    cout << "spawning enemy id: ";
    vec velocity = vmake(EN_BLADE_MIN_X_VEL,EN_BLADE_MAX_Y_VEL);
    vec zero = vmake(0,0);
    int id = createEntity(E_RED_JET, vmake(G_WIDTH/2.0f,(G_HEIGHT-PLAYER_SHIP_H)), zero, 0, 0, 0, redShip[2],redShip, 0);
    cout << id << endl;
    
}//end spawnEnemy()

//===============================================================
//printEntityInfo()
//DEBUG FUNCTION
void gEngine::printEntityInfo(void) {
    cout << "ENTITY INFO! *****************************************\n";
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (entityList[i] != nullptr) {
            cout << "   i: " << i << " w: " << entityList[i]->width << " h: " << entityList[i]->height << " pos: (" << entityList[i]->pos.x << ", " << entityList[i]->pos.y  << ") type: ";
            EType etype =entityList[i]->type;
            switch (etype) {
                case E_JET: {
                    cout << "E_JET";
                    break;
                }
                case E_PLAYERSHIP: {
                    cout << "E_PLAYERSHIP";
                    break;
                }
                case E_ENEMY_WEAPON: {
                    cout << "E_ENEMY_WEAPON";
                    break;
                }
                case E_PLAYER_WEAPON: {
                    cout << "E_PLAYER_WEAPON";
                    break;
                }
                default: {
                    cout << "ERROR, NO TYPE";
                    break;
                }
            }
            cout << endl;
        }
    }
}


//MARK: non gEngine class methods
//==============================================================================================================================

//entity updatePos()
void entity::updatePos(void) {
    //update position based on velocity
    vec newPosition = vadd(pos, vel);
    int halfwidth = width/2;
    int halfheight = height/2;
    
    
    
    //BOUNDARIES
    
    
    if (type == E_PLAYERSHIP) { //playership boundaries
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
    else if (type == E_JET || type == E_JET_2 || type == E_RED_JET || type == E_RED_BLOB) { //enemy jet boundaries, jets are dumb, so they can fly off the screen on the bottom or top and never go back up
        //set horizontile boundaries
        if ((newPosition.x + halfwidth) >= G_WIDTH) {
            reverseXVel();
            newPosition = vadd(pos, vel);
            //newPosition.x = G_WIDTH - (halfwidth);
        }
        else if ((newPosition.x - halfwidth) <= 0) {
            reverseXVel();
            newPosition = vadd(pos, vel);
            //newPosition.x = 0 + (halfwidth);
        }
        
    }//enemy jet boundaries, maybe make enemy jets have AI behavior???
    else if (type == E_BLADE) { //blade boundaries, should just reverse velocity
        int multiplierX = 0, multiplierY = 0;
        if (vel.x > 0) {
            multiplierX = -1;
        }
        else if (vel.x < 0) {
            multiplierX = 1;
        }
        if (vel.y > 0) {
            multiplierY = -1;
        }
        else if (vel.y < 0) {
            multiplierY = 1;
        }
        
        if ((newPosition.x + halfwidth >= G_WIDTH)) {
            //reverseXVel();
            if (vel.x > 0)
                vel.x = (multiplierX)*randf(EN_BLADE_MIN_X_VEL, EN_BLADE_MAX_X_VEL);
            //cout << "B:XMAX\n";
        }
        else if ((newPosition.x - halfwidth) <= 0) {
            //reverseXVel();
            //cout << "B:XMIN\n";
            if (vel.x < 0)
                vel.x = (multiplierX)*randf(EN_BLADE_MIN_X_VEL, EN_BLADE_MAX_X_VEL);
        }
        
        if ((newPosition.y + halfheight >= G_HEIGHT)) {
            if (vel.y > 0)
                vel.y = (multiplierY)*randf(EN_BLADE_MIN_Y_VEL, EN_BLADE_MAX_Y_VEL);
            //cout << "B:YMAX\n";
            //reverseYVel();
        }
        else if (newPosition.y - halfheight <= 0) {
            //reverseYVel();
            //cout << "B:YMIN\n";
            if (vel.y < 0)
                vel.y = (multiplierY)*randf(EN_BLADE_MIN_Y_VEL, EN_BLADE_MAX_Y_VEL);
        }
        newPosition = vadd(pos,vel);
    }
    
    pos = newPosition;
    
    //if entities would move past a certain threashold, delete them
    //delete entities that are off the screen
    if (type == E_PLAYER_WEAPON) {
        if (pos.y > (G_HEIGHT+height) || pos.y < (0-height)) {
            isActive = false;
            
        }
    }
    else if ( (pos.y > (G_HEIGHT*1.5)) || (pos.y < (0-(G_HEIGHT*.2))) || (pos.x < (0-width)) || (pos.x > (G_WIDTH+width))) {
        isActive = false;
    }
    
}

//===============================================================
//laser updatePos()
void laser::updatePos(void) {
    if (parent != nullptr) {
        pos.x = parent->pos.x;
        pos.y = parent->pos.y - height/2;
        //cout << "new pos: (" << pos.x << "," << pos.y << ")\n";
    }
    else {
        isActive = false;
    }
}

//===============================================================
//animation updatePos()
void animation::updatePos(void) {
    if (parent != nullptr) {
        vel = parent->vel;
        pos = vadd(pos, vel);
    }
}

//===============================================================
//animation fade()
void animation::fade(void) {
    //cout << "Activated fade - " << aniTimer << "\n";
    
    
    float length, percent;
    
    if (type == A_BLACK_FULL_TRANSITION) {
        float halfTime = aniLength/2.f;
        length = halfTime;
        
        if (aniTimer <= length) {
            percent = (aniTimer)/length;
        }
        else{
            percent = 1.f - (aniTimer - length)/length;
        }
    }
    else if (type == A_BLACK_FADE_IN || type == A_WHITE_FADE_IN) {
      
        length = aniLength;
        
        percent = 1.f - (aniTimer/aniLength);
        

    }
    
    //float length = halfTime;
    
    
    
    
    
    RGBA.a = percent;
    //gCore.RenderCenteredSprite(vmake(G_WIDTH/2, G_HEIGHT/2), vmake(G_WIDTH, G_HEIGHT), T_BKG, black, 0, 0);
    
    
    if (aniTimer >= aniLength) {
        if (numOfRepeats <= 0) {
            isActive = false;
        }
        else {
            numOfRepeats--;
            aniTimer = -0.1f;
        }
    }
    aniTimer += 0.1f;
}

//===============================================================
//animation cycleGfx()
void animation::cycleGfx(void) {
    float interval = aniLength/(((float)numGfx));
    int gfxIndex;
    
    gfxIndex = (int)(aniTimer/interval);
    
    if (gfxIndex < numGfx) {
        curGfx = gfxSet[gfxIndex];
    }
    
    if (aniTimer >= aniLength) {
        if (numOfRepeats <= 0) {
            isActive = false;
        }
        else {
            numOfRepeats--;
            aniTimer = -0.1f;
        }
    }
    aniTimer += 0.1f;
}

//===============================================================
//animation sizeMod()
void animation::strobeSize(void) {
    float strobeInterval = STROBE_INTERVAL;
    //cout << aniTimer << " " <<  fmodf(aniTimer, strobeInterval) << endl;
    
    float newH = iniHeight*.90;
    float newW = iniWidth*.90;
    
    
    if (fmodf(aniTimer, strobeInterval*2) < 0.1f) {
        height = iniHeight;
        width = iniWidth;
        //cout << "GO\n";
    }
    else if (fmodf(aniTimer, strobeInterval) < 0.1f && aniTimer != 0.f) {
        //cout << "CHECK\n";
        //if (type != A_BLUE_LAZER)
        height = newH;
        
        width = newW;
    }
    
    
    if (aniTimer >= aniLength) {
        isActive = false;
    }
    aniTimer += 0.1f;
}

//animation expandSize()
void animation::expandSize(void) {
 
    float maxW = G_WIDTH*2.5;
    float maxH = G_HEIGHT*2.5;
    
    float intervals = aniLength/0.1f;
    float addW, addH;
    addW = (maxW - iniWidth)/intervals;
    addH = (maxH - iniHeight)/intervals;
    width += addW;
    height += addH;
    
    
    if (aniTimer >= aniLength) {
        isActive = false;
    }
    aniTimer += 0.1f;
}


//===============================================================
//weapon animation()
void weapon::animation(void) {
    
    //cout << "WEAPON ANIMATION\n";
    
}

//===============================================================
//item animation()
void item::animation(void) {
    //numGFXanimations;
    float timerVal = animation_timer;
    //cout << "SHOULDN'T BE SEEING THIS SHIT\n";
    if (animation_timer < 0) {
        timerVal = (timerVal*(-1));
    }//find abs of (timerVal)
    
    if ((int)timerVal != numGFXanimations)
        curGfx = gfxSet[(int)timerVal];
    
    
    if (timerVal >= ((float)numGFXanimations)) {
        animation_timer = -(float)(numGFXanimations-1);
    }
    else if (animation_timer >= -1 && animation_timer < 0) {
        animation_timer = 0.f;
    }
    
    animation_timer += 0.1f;
}

//player fireWeapons()
void player::fireWeapons(gEngine *game) {
    
    
    //determine orientation of the weapons based on the orientation of the ship
    int orientation;
    if (flipGfx) {
        orientation = -1;
    }
    else
        orientation = 1;
    
    //primary weapon
    if (reloadTimer <= 0.f) {
        int weapIndex = game->createEntity(E_PLAYER_WEAPON, pos, vmake(0, (orientation)*(BLASTER_Y_VELOCITY)), 0, 0, 0, currentWeapon, 0, flipGfx);
        //cout << "FIRE weapon: " << weapIndex << endl;
        
        if (weapIndex > 0) {
            game->gCore.playSound(W_LASER_SHOT, LASER_VOL*game->sfxVolume*game->masterVolume);
            game->shotsFired++;
            reloadTimer = static_cast<weapon*>(game->entityList[weapIndex])->reloadInterval;
        }
        
    }//fire player ship weapon
    else if (reloadTimer > 0.f)
        reloadTimer -= RELOAD_DECAY;
    
    //secondary weapon
    if (currentSecondaryWeapon != T_BKG) { //if PSHIP has a secondary weapon
        if (secondaryReloadTimer <= 0.f) {
            
            int weapIndex = game->createEntity(E_PLAYER_WEAPON, pos, vmake(0, (orientation)*(ROCKET_Y_VELOCITY)), 0, 0, 0, currentSecondaryWeapon, 0, flipGfx);
            if (weapIndex > 0) {
                secondaryReloadTimer = static_cast<weapon*>(game->entityList[weapIndex])->reloadInterval;
                game->shotsFired++;
            }
        }//fire player secondary weapon
        else if (secondaryReloadTimer > 0.f)
            secondaryReloadTimer -= RELOAD_DECAY;
    }
    
    //tertiary weapon
    
    if (currentTertiaryWeapon != T_BKG) {
        if (tertiaryReloadTimer <= 0.f) {
            int weapIndex = game->createEntity(E_PLAYER_WEAPON, pos, vmake(-1*(BLASTER_Y_VELOCITY), (orientation)*(BLASTER_Y_VELOCITY)), 0, 0, 0, currentTertiaryWeapon, 0, flipGfx, false);
            int weapIndex2 = game->createEntity(E_PLAYER_WEAPON, pos, vmake(BLASTER_Y_VELOCITY, (orientation)*(BLASTER_Y_VELOCITY)), 0, 0, 0, currentTertiaryWeapon, 0, flipGfx, true);
            if (weapIndex > 0 && weapIndex2 > 0) {
                game->shotsFired += 2; // b/c tertiary weapons fire two shots
                tertiaryReloadTimer = static_cast<weapon*>(game->entityList[weapIndex])->reloadInterval;
            }
        }
        else if (tertiaryReloadTimer > 0.f)
            tertiaryReloadTimer -= RELOAD_DECAY;
    }

}

//enemy fireWeapons()
void enemy::fireWeapons(gEngine *game) {
    
    //determine orientation of the weapons based on the orientation of the ship
    int orientation;
    if (flipGfx) {
        orientation = -1;
    }
    else
        orientation = 1;
    
    //entity *enemyObj = entityList[i];
    if (currentWeapon != T_BKG) {
        if (reloadTimer <= 0.f) {
            if (game->gCore.randchance(50.f)) {
                int weapIndex = game->createEntity(E_ENEMY_WEAPON, pos, vmake(0, (orientation)*(EN_BLASTER_Y_VELOCITY)), 0, 0, 0, currentWeapon, 0, flipGfx);
                
                if (weapIndex > 0) {
                    //entityList[weapIndex]->reverseYVel();
                    //entityList[weapIndex]->RGBA.setVal(0.f, 0.f, 1.f, 1.f);
                    reloadTimer = static_cast<weapon*>(game->entityList[weapIndex])->reloadInterval;
                    //cout << entityList[i]->getReloadTimer() << endl;
                }
            }//50% chance to fire their weapon
            else
                reloadTimer = EN_SINGLE_BLASTER_RELOAD; //refresh buffer between failed fire attempts
            
        }//fireweapon!
        else {
            reloadTimer -= RELOAD_DECAY;
        }//otherwise, decay reload amount
    }
    
    //secondary weapon fire
    if (currentSecondaryWeapon != T_BKG) {
        if (secondaryReloadTimer <= 0.f) {
            if (game->gCore.randchance(50.f)) {
                int weapIndex = game->createEntity(E_ENEMY_WEAPON, pos, vmake(0, (orientation)*(EN_ROCKET_Y_VEL)), 0, 0, 0, currentSecondaryWeapon, 0, flipGfx);
                
                if (weapIndex > 0) {
                    //entityList[weapIndex]->reverseYVel();
                    //entityList[weapIndex]->RGBA.setVal(0.f, 0.f, 1.f, 1.f);
                    secondaryReloadTimer = static_cast<weapon*>(game->entityList[weapIndex])->reloadInterval;
                    //cout << entityList[i]->getReloadTimer() << endl;
                }
            }
            else
                secondaryReloadTimer = EN_ROCKET_RELOAD; //refresh buffer between failed fire attempts
        }
        else {
            secondaryReloadTimer -= RELOAD_DECAY;
        }
    }
    
    //tertiary weapon fire
    if (currentTertiaryWeapon != T_BKG) {
        /**
        if (tertiaryReloadTimer <= 0.f) {
            if (game->gCore.randchance(50.f)) {
                //NOTE CHANGE 'EN_ROCKET_Y_VEL' if you please
                int weapIndex = game->createEntity(E_ENEMY_WEAPON, pos, vmake(0, EN_ROCKET_Y_VEL), 0, 0, 0, currentTertiaryWeapon, 0, 1);
                
                if (weapIndex > 0) {
                    //entityList[weapIndex]->reverseYVel();
                    //entityList[weapIndex]->RGBA.setVal(0.f, 0.f, 1.f, 1.f);
                    tertiaryReloadTimer = static_cast<weapon*>(game->entityList[weapIndex])->reloadInterval;
                    //cout << entityList[i]->getReloadTimer() << endl;
                }
            }
            else
                tertiaryReloadTimer = EN_ROCKET_RELOAD; //refresh buffer between failed fire attempts
        }
        else {
            tertiaryReloadTimer -= RELOAD_DECAY;
        } **/
    }
    
    
    
}

//===============================================================
//player fireOmegaBomb()
void player::fireOmegaBomb(gEngine *game) {
    if (numOmegaWeapon > 0) { //only fire if the player has a bomb availiable
        
        //logic of what happens to entities on the screen when the bomb is dropped
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (game->entityList[i] != nullptr) {
                if (game->entityList[i]->type != E_PLAYERSHIP) {
                    game->entityList[i]->getHp() -= OMEGA_BOMB_DMG; //deal dmg to all non-player entities
                }
                if (game->entityList[i]->type == E_PLAYER_WEAPON || game->entityList[i]->type == E_ENEMY_WEAPON) {
                    game->entityList[i]->isActive = false; //destroy all weapons;
                }
            }
        }
        
        game->createAnimation(A_WHITE_FADE_IN, nullptr, vmake(G_WIDTH/2,G_HEIGHT/2), vmake(0,0), 10);
        //Omega animation
        
        numOmegaWeapon--;
    }
}

//===============================================================
//player deathCheck()
bool player::deathCheck(void) {
    bool retval = false;
    
    if (hp <= 0.f) {
        state = ES_EXPLODING;
        retval = true;
        float x;
        if (pos.x > G_WIDTH/2) {
            x = -DEATH_X_VEL;
        }
        else {
            x = DEATH_X_VEL;
        }
        vel = vmake(x,0);
    }
    
    
    
    return(retval);
}

//===============================================================
//player expAnimation()
bool player::expAnimation(float dyingTimer) {
    float interval = PLAYER_EXPLOSION_TIME/(((float)expTexAmount));
    int expIndex;
    bool retval = false;
    
    expIndex = (int)(explosionTimer/interval);
    
    if (dyingTimer >= (DYING_TIME - PLAYER_EXPLOSION_TIME*1.5)) { //explode
        vel = vmake(0,0);
        if (expIndex < expTexAmount) {
            curGfx = expGfxSet[expIndex];
            retval = true;
        }
        
        if (explosionTimer >= PLAYER_EXPLOSION_TIME) {
            RGBA.setVal(0.f, 0.f, 0.f, 0.f);
            state = ES_DESTROYED;
            isRendered = false;
        }
        else {
            explosionTimer += (PLAYER_EXPLOSION_TIME/(((float)expTexAmount)))/PLAYER_EXPLOSION_SPEED_MODIFIER; //how many frames each animation gets
        }
        
        
    }
    else { //otherwise make the ship smaller and smaller
        
        if (vel.x > 0) {
            curGfx = gfxSet[4];
        }
        else {
            curGfx = gfxSet[0];
        }
        width = width*0.99;
        height = height*0.99;
    }
    return(retval);
    
}

//===============================================================
//enemy animation()
void enemy::animation(void) {
    //numGFXanimations;
    
    float timerVal = animationTimer;
    /**
    if (animationTimer < 0) {
        timerVal = (timerVal*(-1));
    }//find abs of (timerVal)
    **/
    if ((int)timerVal != numGfx)
        curGfx = gfxSet[(numGfx-1) - (int)timerVal];
    
    if (timerVal >= ((float)numGfx)) {
        //animationTimer = -(float)(numGfx-1);
        animationTimer = 0.f;
    }/**
    else if (animationTimer >= -1 && animationTimer < 0) {
        animationTimer = 0.f;
    }**/
    
    animationTimer += 0.1f*BLADE_SPEED_MOD;
}

//===============================================================
//enemy expAnimation()
bool enemy::expAnimation(float dyingTimer) {
    /**
    
    float interval = ENEMY_EXPLOSION_TIME/(((float)expTexAmount)); //amount of time in between each gfx change
    int expIndex;
    
    expIndex = (int)(explosionTimer/interval);
    
    if (expIndex < expTexAmount) {
        curGfx = expGfxSet[expIndex];
    }
    
    if (explosionTimer >= ENEMY_EXPLOSION_TIME) {
        state = ES_DESTROYED;
    }
    else {
        //explosionTimer += ENEMY_EXPLOSION_TIME/(((float)expTexAmount)/0.2f); // we wnat 2 frames per animation
        explosionTimer += (ENEMY_EXPLOSION_TIME/(((float)expTexAmount)))/EXPLOSION_SPEED_MODIFIER; //how many frames each animation gets
    }
    **/
    return(false);
}

//boss intro()
void boss::intro(void) {
    
    if (introTimer <= BOSS_INTRO_TIME) {
        introTimer += 0.1f;
        if (introTimer >= BOSS_INTRO_TIME) {
            velocity = DIAGONAL_VEC;
            posBoundaries.y2 = G_HEIGHT - ((float)width/2)*0.70;
            //posBoundaries.print();
            //cout << " CHECK\n";
        }

        
    }
    
}

//===============================================================
//boss fireControl
void boss::fireControl(gEngine *game) {
    //NOTE general fire control for all weapons except special omega weapon
    //cout << "check1\n";
    for (int i = 0; i < (numOfSegments-1); i++) {
        if (segments[i]->state == ES_ALIVE) {
            //cout << "check 2.1\n";
            if (segments[i]->getReloadTimer() <= 0.f) {
                if (game->gCore.randchance(100.f)) {
                    int weapIndex = game->createEntity(E_ENEMY_WEAPON, segments[i]->pos, vmake(0, -(EN_BLASTER_Y_VELOCITY)), 0, 0, 0, segments[i]->getCurWeapon(), 0, 1);
                    
                    if (weapIndex > 0) {
                        segments[i]->getReloadTimer() = randf(0.f, static_cast<weapon*>(game->entityList[weapIndex])->reloadInterval);
                    }
                }//50% chance to fire their weapon
                else
                    segments[i]->getReloadTimer() = EN_SINGLE_BLASTER_RELOAD;
                
            }//fireweapon!
            else {
                segments[i]->getReloadTimer() -= RELOAD_DECAY;
            }
        }
    }
    //laser control
    
    //omega weapon will always be the last segment
    entity *omegaSegment = segments[numOfSegments-1];
    if (omegaSegment->state == ES_ALIVE) {
        //animation for opening and closing the chamber
        if (omegaSegment->getReloadTimer() <= 0.f) { //fire omega weapon
            if (omegaWepTimer <= (omegaChamberCycleTime+omegaWepChargeTime+omegaWepFireTime)) { //controls weapon charging and firing AFTER WEAPON HAS OPENED
                if (omegaWepTimer < omegaChamberCycleTime) { // open omega chamber
                    float interval = omegaChamberCycleTime/(((float)omegaSegment->numGfx));
                    float aniTimer = omegaWepTimer - 0.f;  //omegaWepTimer - startpointOFanimation
                    int gfxIndex;
                    
                    gfxIndex = (int)(aniTimer/interval);
                    
                    if (gfxIndex < omegaSegment->numGfx) {
                        omegaSegment->curGfx = omegaSegment->gfxSet[gfxIndex];
                    }
                }
                
                if (omegaWepTimer >= omegaChamberCycleTime) { //begin charging weapon
                    if (omegaWepTimer < omegaChamberCycleTime+0.1) {
                        //NOTE: If you want diff types of animations for diff bosses, make this a switch case, and do it to the next animation too
                        game->createAnimation(A_BLUE_LAZER_CHARGE, omegaSegment, vmake(omegaSegment->pos.x,(omegaSegment->pos.y-45)), omegaSegment->vel, omegaWepChargeTime, BOSS_OMEGA_SIZE_MOD);
                    }
                }
                
                if (omegaWepTimer >= omegaChamberCycleTime+omegaWepChargeTime) { //fire actual lazer
                    
                    if (omegaWepTimer < omegaChamberCycleTime+omegaWepChargeTime+0.1) {

                        game->createAnimation(A_BLUE_LAZER, omegaSegment, vmake(omegaSegment->pos.x,(omegaSegment->pos.y-45)), omegaSegment->vel, omegaWepFireTime, BOSS_OMEGA_SIZE_MOD);
                        int wepIndex = game->createEntity(E_ENEMY_LASER, vmake(omegaSegment->pos.x,omegaSegment->pos.y/2), vmake(0,0), game->gCore.getTexWidth(omegaSegment->getCurWeapon())*BOSS_OMEGA_SIZE_MOD, 0, 0.f, omegaSegment->getCurWeapon(), game->blueLaser); //create laser hitbox

                        if (wepIndex > 0) {
                            static_cast<laser*>(game->entityList[wepIndex])->parent = segments[numOfSegments-1];
                            segments[numOfSegments-1]->Id = wepIndex;
                        }
                    }
                }
                omegaWepTimer += 0.1f;
            }
            else if (omegaWepTimer >= omegaChamberCycleTime+omegaWepChargeTime+omegaWepFireTime) { // cycle omega chamber closed
                if (segments[numOfSegments-1]->Id != -1) {
                    game->entityList[segments[numOfSegments-1]->Id]->isActive = false;
                    segments[numOfSegments-1]->Id = -1;
                }

                //cycle chamber code...
                float interval = omegaChamberCycleTime/(((float)omegaSegment->numGfx));
                float aniTimer = omegaWepTimer - (omegaChamberCycleTime+omegaWepChargeTime+omegaWepFireTime);  //omegaWepTimer - startpointOFanimation
                int gfxIndex;
                
                gfxIndex = omegaSegment->numGfx - ((int)(aniTimer/interval)) - 1 ;
                
                if (gfxIndex < omegaSegment->numGfx) {
                    omegaSegment->curGfx = omegaSegment->gfxSet[gfxIndex];
                }
                
                //reset timers and omega sequence, set reload timer
                if (omegaWepTimer >= omegaChamberCycleTime*2+omegaWepChargeTime+omegaWepFireTime) {
                    omegaWepTimer = 0.f;
                    omegaSegment->getReloadTimer() = EN_BLUE_LAZER_RELOAD_TIME;
                }
                else {
                    omegaWepTimer += 0.1f;
                }
            }
        }
        else
            omegaSegment->getReloadTimer() -= RELOAD_DECAY;
    }
}

//===============================================================
//boss updatePos()
void boss::updatePos(void) {
    vec newPos = vadd(position, velocity);
    //check x boundaries
    if (newPos.x < posBoundaries.x1 || newPos.x > posBoundaries.x2) { //boss is too far left
        velocity.x = velocity.x * (-1);
    }
    
    if (newPos.y < posBoundaries.y1 || newPos.y > posBoundaries.y2) {
        velocity.y = velocity.y * (-1);
    }
    
    
    
    position = vadd(position, velocity);
}

//===============================================================
//boss updateSegVel()
void boss::updateSegVel(void) {
    for (int i = 0; i < numOfSegments; i++) {
        if (segments[i] != nullptr) {
            segments[i]->vel = velocity;
        }
    }
}

//===============================================================
//boss death()
bool boss::death(void) {
    bool retval = false;
    if (explosionTimer == 0.f) {
        for (int i = 0; i < numOfSegments; i++) {
            segments[i]->state = ES_EXPLODING;
            static_cast<bossSegment*>(segments[i])->explosionTimer = 0.f;

        }
    }
    
    
    if (explosionTimer >= BOSS_EXP_TIME)
        retval = true;
    
    explosionTimer += 0.1f;
    return(retval);
}

//===============================================================
//bossSegment expAnimation()

bool bossSegment::expAnimation(float dyingTimer) {
    float interval = BOSS_SEGMENT_EXP_TIME / BOSS_SEG_EXP_NUM;
    bool retval = false;
    if (fmod(explosionTimer,interval) < 0.1f)
        retval = true;
    
    
    if (explosionTimer >= BOSS_SEGMENT_EXP_TIME) {
        state = ES_DESTROYED;
        int newIndex = (curGfx - gfxSet[0]) + 3;

        if (newIndex >= numGfx) {

        }
        else
            curGfx = gfxSet[newIndex];

    }
    else
        explosionTimer += 0.1f;
    return(retval);
}

//MARK: terrain methods
//==============================================================================================================================
//terrain()
terrain::terrain(gEngine *game) {
    //initialize clouds
    cloudList = new cloud*[MAX_CLOUDS];
    for (int i = 0; i < MAX_CLOUDS; i++) {
        cloudList[i] = nullptr;
    }
    //calculate how many lines will be in the array
    tileH = game->gCore.getTexHeight(T_BKG);
    tileW = game->gCore.getTexWidth(T_BKG);
    numLines = G_HEIGHT/tileH + 2; // we want there to be 2 more lines than the max height of the game
    terrainList = new line*[numLines];
    tilesPerLine = G_WIDTH/tileW + 1; //we want there to always be enough tiles to cross the whole screen
    initializeMap(game);
    
}

//===============================================================
//terrain ~terrain()
terrain::~terrain(void) {
    delete[] terrainList;
    for (int i = 0; i < MAX_CLOUDS; i++) {
        if (cloudList[i] != nullptr) {
            delete cloudList[i];
            cloudList[i] = nullptr;
        }
        
    }
    delete[] cloudList;
}

//===============================================================
//terrain initializeMap()
void terrain::initializeMap(gEngine *game) {
    //intialize clouds
    TexIDs gfx;
    float w, h;
    numClouds = randi(0,MAX_CLOUDS); // generate number of clouds to begin with
    for (int i = 0; i < MAX_CLOUDS; i++) {
        if (i < numClouds) {
            gfx = (TexIDs)randi((int)T_CLOUD_00,((int)T_CLOUD_00 + 7));
            w = game->gCore.getTexWidth(gfx)*CLOUD_SIZE_MOD;
            h = game->gCore.getTexHeight(gfx)*CLOUD_SIZE_MOD;
            vec newPos = vmake(randf(0,G_WIDTH), randf(0,G_HEIGHT));
            if (cloudList[i] != nullptr) {
                cloudList[i]->isActive = true;
                cloudList[i]->width = w;
                cloudList[i]->height = h;
                cloudList[i]->cloudGfx = gfx;
                cloudList[i]->pos = newPos;
            }
            else
                cloudList[i] = new cloud(gfx, newPos, w, h);
        }
        else {
            cloudList[i] = nullptr;
        }
    }
    
    
    //clearMap();
    int sector = 0;
    int prevSector = 0;
    int sectorBelowType = 0;
    int tileBelowType = 0;
    int prevTileType = 0;
    int tileIndex = 0;
    int tileBelowIndex = 0;
    //cout << "\n\n--------------- NEW ------------------\n\n";
    for (int i = 0; i < numLines; i++) {
        terrainList[i] = new line(tilesPerLine);
        for (int j = 0; j < tilesPerLine; j++) {
            if (i == 0 && j == 0) { //initial sector choice
                sector = randi(0,3);
                if (sector < 3) {
                    tileIndex = sector*3+randi(0,2);//initial tile
                }
                else{
                    tileIndex = randi(9,13); //MARK: Update for final tile
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
                        if (randchance(50)) { //MARK: UPDate
                            tileIndex = sector*3;
                        }
                        else {
                            //cout << "tile preceding 13: " << tileIndex << endl;
                            tileIndex = 13; //MARK: update
                            sector = 3;
                            
                        }
                        
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
                    else if (tileIndex == 13) { //MARK: update
                        sector = randi(0,3);
                        if (sector < 3) {
                            tileIndex = sector*3;
                        }
                        else
                            tileIndex = 13;
                        //cout << "tile following 13: " << tileIndex << endl;
                    }
                    else
                        cout << "DEVESTATING ERROR\n";
                }
                //cout << "j: " << j << "  tileI: " << tileIndex << endl;
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
                        sector = randi(2,3); //MARK: UPDate
                    }
                    else if (tileBelowIndex == 13) {
                        rng = randi(1,4); //MARK: UPDATE
                        if (rng < 4) {
                            sector = 2; //MARK: UPDATE
                        }
                        else {
                            sector = 3; //MARK: UPDATE
                        }
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
                        if (sectorBelowType == 0) { //if the sector below was a 0, the only option for tiles in the 3-4 sector range is 13
                            tileIndex = 13; //MARK: UPDATE
                        }
                        else if (tileBelowIndex == 13) {
                            tileIndex = 13; //MARK: UPDATE
                        }
                        else if (tileBelowType == 0 || tileBelowIndex == 9) {
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
                    int size = 14;//size_of((game->levelTextures[game->currentLevel-1]));
                    int prevTile = tileIndex;
                    int rightExpansions[size];
                    int upExpansions[size];
                    for (int z = 0; z < size; z++) {
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
                            tileIndex = 13; //MARK: UPDATE
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
                        else if (prevTile == 13) { //MARK: UPDATE
                            tileIndex = 0*3;
                            rightExpansions[tileIndex] = tileIndex;
                            sizeR++;
                            tileIndex = 1*3;
                            rightExpansions[tileIndex] = tileIndex;
                            sizeR++;
                            tileIndex = 2*3;
                            rightExpansions[tileIndex] = tileIndex;
                            sizeR++;
                            tileIndex = 13;
                            rightExpansions[tileIndex] = tileIndex;
                            sizeR++;
                        }
                        else
                            cout << "DEVESTATING ERROR\n";
                    }
                    /**************************/
                    //choose new sector of tile based on the tile below's sector
                    if (sectorBelowType > 0) { //if sectorBlow is 1, 2, or 3, then possible solutions exist in sectors 0, 1, and 3
                        //MARK: possible bugs here, think about tileBelowType for tile 12
                        if (sectorBelowType == 1 || sectorBelowType == 2) {
                            upExpansions[0*3+tileBelowType] = 0*3+tileBelowType;
                            sizeU++;
                            upExpansions[1*3+tileBelowType] = 1*3+tileBelowType;
                            sizeU++;
                            
                        }
                        if (tileBelowIndex == 13) { //MARK: IMPROVE
                            sector = 2;
                            tileIndex = sector*3+0;
                            upExpansions[tileIndex] = tileIndex;
                            sizeU++;
                            tileIndex = sector*3+1;
                            upExpansions[tileIndex] = tileIndex;
                            sizeU++;
                            tileIndex = sector*3+2;
                            upExpansions[tileIndex] = tileIndex;
                            sizeU++;
                            tileIndex = 13;
                            sector = 3;
                            upExpansions[tileIndex] = tileIndex;
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
                        else if (tileBelowIndex) {
                            //MARK: IMPROVE put something here?
                        }
                        else {
                            cout << "CATACLYSMIC ERROR SECOND COMMING!\n";
                        }
                    }
                    else if (sectorBelowType == 0) { //if sectorBelow is 0, then possible solutions exist only in sector 2, and tile 13
                        sector = 2;
                        
                        tileIndex = sector*3;
                        upExpansions[tileIndex] = tileIndex;
                        sizeU++;
                        upExpansions[tileIndex+1] = tileIndex+1;
                        sizeU++;
                        upExpansions[tileIndex+2] = tileIndex+2;
                        sizeU++;
                        tileIndex = 13; //MARK: UPDATE
                        sector = 3;
                        upExpansions[tileIndex] = tileIndex;
                        sizeU++;
                    }
                    else {
                        cout << "AHHHHH ERROR!\n";
                    }
                    
                    int validExpansions[size];
                    int sizeV = 0;
                    for (int z = 0; z < size; z++) {
                        //cout << rightExpansions[z] << " || " << upExpansions[z] << endl;
                        if ((rightExpansions[z] == upExpansions[z]) && (rightExpansions[z] != -1)) {
                            validExpansions[sizeV] = rightExpansions[z];
                            sizeV++;
                        }
                    }
                    if ((sizeV) == 0) {
                        tileIndex = 0;
                        sector = 0;
                        cout << "\n******** no match found on line " << i+1 << " spot " << j+1 << " ********** -- Tilebelow " << tileBelowIndex << "\n";
                        for (int z = 0; z < size; z++) {
                            cout << rightExpansions[z] << " || " << upExpansions[z] << endl;
                        }
                        
                        
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
    
    
}

//===============================================================
//terrain clearMap()
void terrain::clearMap(void) {
    for (int i = 0; i < numLines; i++) {
        delete terrainList[i];
        terrainList[i] = nullptr;
    }
    for (int i = 0; i < MAX_CLOUDS; i++) {
        if (cloudList[i] != nullptr)
            cloudList[i]->isActive = false;
    }
}

//===============================================================
//terrain generateLine()
void terrain::generateLine(gEngine *game) {
    if (terrainList[numLines-1] == nullptr) {
        terrainList[numLines-1] = new line(tilesPerLine);
        int index = numLines-1;
        int sector = 0;
        int prevSector = 0;
        int sectorBelowType = 0;
        int tileBelowType = 0;
        int prevTileType = 0;
        int tileIndex = 0;
        int tileBelowIndex = 0;
        int size = 14;
        
        sector = terrainList[index-1]->gfxIndex[0]/3;
        
        for (int j = 0; j < tilesPerLine; j++) {
            tileBelowIndex = terrainList[index-1]->gfxIndex[j];
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
                    sector = randi(2,3); //MARK: UPDate
                }
                else if (tileBelowIndex == 13) {
                    rng = randi(1,4); //MARK: UPDATE
                    if (rng < 4) {
                        sector = 2; //MARK: UPDATE
                    }
                    else {
                        sector = 3; //MARK: UPDATE
                    }
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
                    if (sectorBelowType == 0) { //if the sector below was a 0, the only option for tiles in the 3-4 sector range is 13
                        tileIndex = 13; //MARK: UPDATE
                    }
                    else if (tileBelowIndex == 13) {
                        tileIndex = 13; //MARK: UPDATE
                    }
                    else if (tileBelowType == 0 || tileBelowIndex == 9) {
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
                int rightExpansions[size];
                int upExpansions[size];
                for (int z = 0; z < size; z++) {
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
                        tileIndex = 13; //MARK: UPDATE
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
                    else if (prevTile == 13) { //MARK: UPDATE
                        tileIndex = 0*3;
                        rightExpansions[tileIndex] = tileIndex;
                        sizeR++;
                        tileIndex = 1*3;
                        rightExpansions[tileIndex] = tileIndex;
                        sizeR++;
                        tileIndex = 2*3;
                        rightExpansions[tileIndex] = tileIndex;
                        sizeR++;
                        tileIndex = 13;
                        rightExpansions[tileIndex] = tileIndex;
                        sizeR++;
                    }
                    else
                        cout << "DEVESTATING ERROR\n";
                }
                /**************************/
                //choose new sector of tile based on the tile below's sector
                if (sectorBelowType > 0) { //if sectorBlow is 1, 2, or 3, then possible solutions exist in sectors 0, 1, and 3
                    if (sectorBelowType == 1 || sectorBelowType == 2) {
                        upExpansions[0*3+tileBelowType] = 0*3+tileBelowType;
                        sizeU++;
                        upExpansions[1*3+tileBelowType] = 1*3+tileBelowType;
                        sizeU++;
                    }
                    if (tileBelowIndex == 13) { //MARK: IMPROVE
                        sector = 2;
                        tileIndex = sector*3+0;
                        upExpansions[tileIndex] = tileIndex;
                        sizeU++;
                        tileIndex = sector*3+1;
                        upExpansions[tileIndex] = tileIndex;
                        sizeU++;
                        tileIndex = sector*3+2;
                        upExpansions[tileIndex] = tileIndex;
                        sizeU++;
                        tileIndex = 13;
                        sector = 3;
                        upExpansions[tileIndex] = tileIndex;
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
                    else if ( tileBelowIndex == 13) {
                        //MARK: IMPROVE put something here?
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
                    tileIndex = 13; //MARK: UPDATE
                    sector = 3;
                    upExpansions[tileIndex] = tileIndex;
                    sizeU++;
                }
                else {
                    cout << "AHHHHH ERROR!\n";
                }
                int validExpansions[size];
                int sizeV = 0;

                for (int z = 0; z < size; z++) {
                    if ((rightExpansions[z] == upExpansions[z]) && (rightExpansions[z] != -1)) {
                        validExpansions[sizeV] = rightExpansions[z];
                        sizeV++;
                    }
                }
                if ((sizeV) == 0) {
                    tileIndex = 0;
                    sector = 0;
                    cout << "\n******** no match found on line " << index << " spot " << j << " ********** -- Tilebelow " << tileBelowIndex << "\n";
                }
                else {
                    int rng2 = randi(0, (sizeV-1));
                    
                    tileIndex = validExpansions[rng2];
                    sector = tileIndex/3;
                }
            }

            terrainList[index]->gfxIndex[j] = tileIndex;
            //terrainList[index]->content[j] = game->forest[tileIndex];
            terrainList[index]->content[j] = game->levelTextures[game->currentLevel-1][tileIndex];
            terrainList[index]->pos[j] = vmake( (tileW/2 + (j*tileW)),(terrainList[index-1]->pos[j].y+tileH));
        }
    }
}

//===============================================================
//terrain removeLine()
bool terrain::removeLine(int lineIndex, gEngine *game) {
    bool retval = false;
    
    delete terrainList[lineIndex];
    terrainList[lineIndex] = nullptr;
    
    for (int i = lineIndex; i < (numLines-1); i++) {
        terrainList[i] = terrainList[i+1];
    }
    terrainList[numLines-1] = nullptr;
    generateLine(game);
    
    return(retval);
}

//===============================================================
//terrain moveTerrain()
void terrain::moveTerrain(gEngine *game) {
    for (int i = 0; i < numLines; i++) {
        if (terrainList[i] != nullptr) {
            for (int j = 0; j < tilesPerLine; j++) {
                //DEBUG uncomment after finished
                terrainList[i]->pos[j].y -= G_CAMERA_SPEED;
                if ((terrainList[i]->pos[j].y + tileH/2) < 0.f ) {
                    removeLine(i, game);
                    i--;
                    j = tilesPerLine;
                }
            }
        }
    }
    moveClouds();
}

//===============================================================
//terrain moveClouds()
void terrain::moveClouds(void) {
    for (int i = 0; i < MAX_CLOUDS; i++) {
        if (cloudList[i] != nullptr) {
            if (cloudList[i]->isActive) {
                cloudList[i]->pos.y -= G_CAMERA_SPEED*0.6;
                if ((cloudList[i]->pos.y + cloudList[i]->height/2) < 0.f) { //remove cloud
                    numClouds--;
                    cloudList[i]->isActive = false;
                }
            }
        }
    }
}

//===============================================================
//terrain generateClouds()
bool terrain::generateClouds(gEngine *game) {
    if (randchance(MAX_CLOUDS-numClouds)) { //chance to generate clouds based on number of clouds in existance
        TexIDs gfx = (TexIDs)randi((int)T_CLOUD_00,((int)T_CLOUD_00 + 7));
        float w = game->gCore.getTexWidth(gfx)*CLOUD_SIZE_MOD;
        float h = game->gCore.getTexHeight(gfx)*CLOUD_SIZE_MOD;
        vec newPos = vmake(randf(0,G_WIDTH), G_HEIGHT+h);
        for (int i = 0; i < MAX_CLOUDS; i++) {
            if (cloudList[i] == nullptr) {//if you find an empty cloud spot, gen new cloud
                
                cloudList[i] = new cloud(gfx, newPos, w, h);
                numClouds++;
                return(true);
            }
            else if (!cloudList[i]->isActive) { //if there's an inactive cloud, remake it
                cloudList[i]->isActive = true;
                cloudList[i]->width = w;
                cloudList[i]->height = h;
                cloudList[i]->cloudGfx = gfx;
                cloudList[i]->pos = newPos;
                numClouds++;
                return(true);
            }
        }
    }
    return(false);
}








