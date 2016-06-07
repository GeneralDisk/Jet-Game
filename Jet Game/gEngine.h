//
//  gEngine.h
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/18/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//

#ifndef gEngine_h
#define gEngine_h
#include "stdafx.h"
#include "base.h"
#include "sys.h"
#include "core.h"

#define MAX_ENTITIES 256
#define MAX_ANIMATIONS 50


//forward class declarations
class gEngine;

static int ZERO = 0;

//===============================================================
//MARK: Menu structs

enum MenuType { M_NULL, M_MAIN_MENU, M_LEVEL_SELECT, M_OPTIONS, M_HELP_INFO, M_PAUSE, M_QUESTION };

class MenuItem {
public:
    MenuItem(void) { str = nullptr; sizeStr = 0; sizeMod = 1.f;}
    MenuItem(const char STR[]) { sizeStr = (int)strlen(STR); char *newStr = new char[sizeStr]; str = new char[sizeStr]; delete newStr; for (int i=0;i<sizeStr;i++) { str[i] = STR[i]; } sizeMod = 1.f; isChosen = false; }
    ~MenuItem(void) { if (sizeStr > 0) {delete str; str = nullptr; sizeStr = 0;}}
    void setStr(const char STR[]) {if (sizeStr > 0) {delete str; str = nullptr; sizeStr = 0;} sizeStr = (int)strlen(STR); str = new char[(int)sizeStr]; strcpy(str, STR);}
    void setAtr(const char STR[], float SizeMod = 1.f, bool ISChosen = false, bool NOTButton = false) { setStr(STR); sizeMod = SizeMod; isChosen = ISChosen; notButton = NOTButton; }

    char* str;
    int sizeStr;
    vec pos;
    float sizeMod;
    bool isChosen, notButton;
};

class Menu {
public:
    Menu(void) {listSize = 0; items = nullptr; }
    Menu(int size) { listSize = size; items = new MenuItem[size]; }
    ~Menu(void) {if (listSize > 0 && items != nullptr) {delete[] items; items =nullptr; listSize = 0;} };
    
    vec positionOfTop;
    int listSize;
    MenuItem *items;
};

//===============================================================
//MARK: Terrain System
class cloud {
public:
    cloud(TexIDs gfx, vec Pos, float w, float h) {cloudGfx = gfx; pos = Pos; width = w; height = w; isActive = true; }
    bool isActive;
    float width, height;
    TexIDs cloudGfx;
    vec pos;
   // cloud(TexIDs gfx, vec Pos) : cloudGfx(gfx), pos(Pos), isActive(true) {}

    
};

class line {
public:
    line(int Size = 1) {size = Size; content = new TexIDs[size]; pos = new vec[size]; gfxIndex = new int[size]; }
    ~line(void) { delete[] gfxIndex; delete[] pos; delete[] content; }
    int size;
    
    int* gfxIndex; // contains corresponding indexs of the gfx used for each id
    vec* pos; //contains positions of corresponding content IDs
    TexIDs* content;
};

class terrain {
public:
    terrain(gEngine *game);
    ~terrain(void);
    void initializeMap(gEngine *game);
    void clearMap(void);
    void generateLine(gEngine *game);
    bool removeLine(int lineIndex, gEngine *game);
    void moveTerrain(gEngine *game);
    void moveClouds(void);
    bool generateClouds(gEngine *game);
    
    
    int numLines;
    int tilesPerLine;
    int numClouds;
    float tileW, tileH;
    
    line **terrainList;
    cloud **cloudList;
};

//===============================================================
//MARK: Entity System
enum EType {E_NULL, E_PLAYERSHIP, E_JET, E_JET_2, E_RED_JET, E_RED_BLOB, E_BLADE, E_BOSS, E_POWERUP, E_HEALTHUP, E_PLAYER_WEAPON, E_ENEMY_WEAPON, E_ENEMY_LASER };
enum ESubType {EST_NULL, EST_PRIMARY_WEP, EST_SECONDARY_WEP, EST_TERTIARY_WEP};
enum EState {ES_ALIVE, ES_EXPLODING, ES_DESTROYED};
enum Direction {D_NULL, D_LEFT, D_STRAIGHT, D_RIGHT};

class entity {
public:
    EType type;
    ESubType subType;
    EState state;
    rgba RGBA;
    bool isActive;
    bool flipGfx;
    bool reverseGfx;
    bool isRendered;
    bool isAnimated;
    vec pos;
    vec vel;
    int width;
    int height;
    int Id;
    float inertia;
    int numGfx;
    TexIDs curGfx;
    TexIDs gfxSet[20];
    
    //virtual overloaded submethods
    virtual void updatePos(void);
    virtual void reverseXVel(void) {vel.x = (vel.x * -1);}
    virtual void reverseYVel(void) {vel.y = (vel.y * -1);}
    virtual int getDropscale(void) { return(0); }
    virtual int& getScore(void) {ZERO = 0; return(ZERO); }
    virtual TexIDs getGfx(int index) {return(curGfx);}
    virtual float& getHp(void) {float x = 10.f; return(x);}
    virtual float& getDirTimer(void) {float x = 0.f; return(x); }
    virtual float& getReloadTimer(int primaryOrSecondary = 0) {float x = 0.f; return(x); }
    virtual float& getHitTimer(void) {float x = 0.f; return(x); }
    virtual TexIDs& getCurWeapon(int primaryOrSecondary = 0) {TexIDs placeholder = T_SINGLE_SHOT; return(placeholder); }
    virtual Direction& getCurDirection(void) {Direction x = D_NULL; return(x); }
    virtual void fireWeapons(gEngine *game) {}
    virtual void animation(void) {}
    virtual bool expAnimation(float dyingTimer) { return(false); }
    
    
};

class player : public entity {
    public:
        char* name;
        float hp;
        float hitTimer;
        float reloadTimer;
        float secondaryReloadTimer;
        float tertiaryReloadTimer;
        float explosionTimer;
        int curScore;
        int numOmegaWeapon;
        int expTexAmount;
        TexIDs expGfxSet[20];
        TexIDs currentWeapon;
        TexIDs currentSecondaryWeapon;
        TexIDs currentTertiaryWeapon;
        //TexIDs gfxSet[5];
    
        int& getScore(void) { return(curScore); }
        TexIDs getGfx(int index) { return(gfxSet[index]);}
        float& getHp(void) { return(hp); }
        float& getReloadTimer(int primaryOrSecondary) { if (primaryOrSecondary == 0) { return(reloadTimer); } else if (primaryOrSecondary == 1) { return(secondaryReloadTimer); } else { return(tertiaryReloadTimer); } }
        float& getHitTimer(void) { return(hitTimer); }
        TexIDs& getCurWeapon(int primaryOrSecondary) { if (primaryOrSecondary == 0) {return(currentWeapon); } else if (primaryOrSecondary == 1) { return(currentSecondaryWeapon); } else { return(currentTertiaryWeapon); }}
    
        void fireWeapons(gEngine *game);
        void fireOmegaBomb(gEngine *game);
        bool deathCheck(void); //function checks whether or not the player is dead
        bool expAnimation(float dyingTimer); //function handles player explosion, implementation in gEngine.cpp

};

class enemy : public entity {
    public:
        float hp;
        Direction direction;
        float directionTimer;
        float animationTimer;
        float hitTimer;
        float reloadTimer;
        float secondaryReloadTimer;
        float tertiaryReloadTimer;
        float explosionTimer;
        int scoreVal;
        int dropscale;
        int expTexAmount;
        TexIDs expGfxSet[20];
        TexIDs getGfx(int index) { return(gfxSet[index]);}
        TexIDs currentWeapon;
        TexIDs currentSecondaryWeapon;
        TexIDs currentTertiaryWeapon;
        //TexIDs gfxSet[5];
    
        //overloaded virtual functions
        void reverseXVel(void) {vel.x = (vel.x * -1); if (vel.x < 0) {direction = D_LEFT;} else if (vel.x > 0) {direction = D_RIGHT;}}
        int getDropscale(void) { return(dropscale); }
        int& getScore(void) { return(scoreVal); }
        float& getDirTimer(void) { return(directionTimer); }
        float& getHp(void) { return(hp); }
    
        float& getReloadTimer(int primaryOrSecondary) { if (primaryOrSecondary == 0) { return(reloadTimer); } else if (primaryOrSecondary == 1) { return(secondaryReloadTimer); } else { return(tertiaryReloadTimer); } }
        float& getHitTimer(void) { return(hitTimer); }
        TexIDs& getCurWeapon(int primaryOrSecondary) { if (primaryOrSecondary == 0) {return(currentWeapon); } else if (primaryOrSecondary == 1) { return(currentSecondaryWeapon); } else { return(currentTertiaryWeapon); }}
        Direction& getCurDirection(void) { return(direction); }
    
        void fireWeapons(gEngine *game);
        void animation(void);
        bool expAnimation(float dyingTimer); //function handles the explosion, implementation in gEngine.cpp

};

class bossSegment : public entity {
    friend class gEngine;
    public:
        float hp;
        Direction direction;
        float hitTimer;
        float reloadTimer;
        float secondaryReloadTimer;
        float explosionTimer;
        //TexIDs gfxSet[10];
        TexIDs currentWeapon;
        int expTexAmount;
        TexIDs expGfxSet[20];
    
    
        //overloaded virtual functions
        void reverseXVel(void) {vel.x = (vel.x * -1); if (vel.x < 0) {direction = D_LEFT;} else if (vel.x > 0) {direction = D_RIGHT;}}
        float& getHp(void) { return(hp); }
        float& getReloadTimer(int primaryOrSecondary) { if (primaryOrSecondary == 0) { return(reloadTimer); } else { return(secondaryReloadTimer); } }
        float& getHitTimer(void) { return(hitTimer); }
        TexIDs& getCurWeapon(int primaryOrSecondary) { return(currentWeapon); }
        Direction& getCurDirection(void) { return(direction); }
    
        bool expAnimation(float dyingTimer); //function handles the explosion, implementation in gEngine.cpp
    
};

class weapon : public entity {
    public:
        float damage;
        float reloadInterval;
        float animation_timer;
        int numGFXanimations;
        void animation(void); //function handles weapon animations if they exist
    
    
};

class laser : public weapon {
    public:
        entity* parent; //lasers must be tied to a parent entity
    
        void updatePos(void);
    
};

class item : public entity {
    public:
        float hpIncrease;
        float animation_timer;
        int numGFXanimations;
        TexIDs wepUpgrade;
        //TexIDs gfxSet[5];
    
        float& getHp(void) { return(hpIncrease); }
        TexIDs& getCurWeapon(int primaryOrSecondary) { return(wepUpgrade); }
        void animation(void);  //function handles item animations, implemented on next page
};

class boss {
    public:
        float healthpool;
        float maxHealth;
        float omegaChamberCycleTime;
        float omegaWepTimer;
        float omegaWepChargeTime;
        float omegaWepFireTime;
        int scoreVal;
        int width;
        int height;
        EState state;
        int numOfSegments;
        entity **segments;
        //vec *segPositions; //these positions will be relative to the center position, which will be vmake(0,0)
        vec endIntroPosition;
        vec position;
        vec velocity;
        box posBoundaries;
    
        //boss timers
        float introTimer;
        float explosionTimer;
    
        //boss methods
        void intro(void); //function that controls the boss's introduction behavior (intro to the screen)
        void fireControl(gEngine *game); //controls the boss's weapons fire || also good example of friendship

        void updatePos(void); //function to update the boss's position based on it's velocity
        void updateSegVel(void); //function to update the segment's velocities to be the boss's velocity
        bool death(void); //function controls what happens when the boss dies, returns true upon end of death animation
    
};

//===============================================================
//MARK: Animation System -- for making animations separate from entities

enum AType {A_NULL, A_BLACK_FULL_TRANSITION, A_BLACK_FADE_IN, A_WHITE_FADE_IN, A_HALO, A_EXP_REG, A_EXP_NUKE, A_BLUE_LAZER_CHARGE, A_BLUE_LAZER};
enum ASubType {AS_FADE, AS_CYCLING, AS_STROBE_SIZE, AS_EXPAND_SIZE};
class animation {
public:
    AType type;
    ASubType subtype;
    rgba RGBA;
    entity *parent; //each animation will have to have a paretn entity it's tied too
    bool isActive;
    bool multiSegments;
    bool flipGfx;
    float sizeMod;
    float aniTimer;
    float aniLength;
    vec pos;
    vec vel;
    int iniWidth;
    int iniHeight;
    int width;
    int height;
    int numGfx;
    int numOfRepeats;
    TexIDs curGfx;
    TexIDs gfxSet[20];
    
    //methods
    void updatePos(void);
    void fade(void);
    void cycleGfx(void);
    void strobeSize(void);
    void expandSize(void);
    
};

struct playerStats {
    float playerHP;
    TexIDs weapons[3];
    float armorRating;
    TexIDs* shipType;
    int score;
};


//===============================================================
//MARK: Game Engine
enum gState { GS_PLAYING, GS_MAIN_MENU, GS_STATSCREEN, GS_PAUSE, GS_DYING, GS_BOSSFIGHT, GS_VICTORY, GS_EXIT };
enum location { L_TOP, L_BOTTOM, L_LEFT, L_RIGHT };

class gEngine {
    public:
        //friend declarations
        friend entity;
        friend enemy;
        friend player;
        friend boss;
        friend terrain;
        //main game engine methods, these need to be public
        gEngine(void);
        ~gEngine(void);
        void render(void);
        void show(void);
        void pump(void);
        void processInput(void);
        gState runLogic(void);
        void sleep(int ms);
    protected:
        //submethods ================== ==================
        void renderMenu(Menu *menu);
        void renderScore(int levelScore, int overallScore);
        void generateTerrain(int level);
        int createEntity(EType eType, vec position, vec velocity, int w, int h, float inertia, TexIDs curGFX, TexIDs GFXset[20], bool flipGFX = 0, bool reverseGFX = 0);
        int createAnimation(AType aType, entity *parentE, vec position, vec velocity, float animationLen, float sizeModifier = 1.f, int numRepeats = 0, bool flipGFX = 0);
        void moveAniToFront(int index);
        void stopAllAnimations(void); //stops all currently active animations
        void generateLevelEnemies(void);
        void generateEnemy(EType etype, float chanceToSpawn, location spawnLOC);
        boss* generateBoss(int level);
        void spawnItem(vec pos, int dropscale);
        void resetGame(void);
    
        //DEBUGING functions
        void spawnEnemy(void);
        void printEntityInfo(void);
    
        //Menus ================== ==================
        Menu* currentMenu;
    
        Menu *mainMenu;
        Menu *levelSelectMenu;
        Menu *optionsMenu;
        Menu *helpInfoMenu;
        Menu *pauseMenu;
        Menu *questionMenu; // the are you sure? menu
        int curSelectedMenuIndex;
        int curMenuSize;
        MenuType curMenu;
        MenuType prevMenu;
    
        //prev input boolians
        bool prevleft;
        bool prevright;
        bool prevup;
        bool prevdown;
        bool prevspace;
        bool prevleftBracket;
        bool prevrightBracket;
        bool prevpressP;
        bool prevpressQ;
        bool prevpressX;
        bool prevpressE;
        bool prevpressW;
        bool prevpressA;
        bool prevpressS;
        bool prevpressD;
        bool preventer;
    
    
        //ENDTEST
    
    
        //interior variables ================== ==================
        gState game_state;
        playerStats player_stats;
        bool victory;
        bool isBossSpawned;
        bool prevPress;
        int currentLevel;
        float masterVolume;
        float musicVolume;
        float sfxVolume;
        float main_timer;
        float dying_timer;
        float key_timer;
        float menu_switchBKG_timer;
        core gCore; //graphics and audio OPEN GL & OPEN AL interfaces
        float gCameraPos;
        entity *entityList[MAX_ENTITIES]; //game entity carrier
        animation *animationList[MAX_ANIMATIONS];
        boss *levelBoss;
        terrain *gameTerrain;
    
        //player statistic counters ================== ==================
        int enemiesSpawned;
        int enemiesKilled;
        int shotsFired;
        int shotsHit;
        float hpGained;
        float hpLost;
    
        //Texture Packs ================== ==================
        //ship packs ***
        //player ships
        TexIDs beigeShip[5] = {T_BSHIP_LL, T_BSHIP_L, T_BSHIP_C, T_BSHIP_R, T_BSHIP_RR};
        TexIDs silverShip[5] = {T_SSHIP_LL, T_SSHIP_L, T_SSHIP_C, T_SSHIP_R, T_SSHIP_RR}; //slim
        TexIDs silverShip2[5] = {T_SSHIP2_LL, T_SSHIP2_L, T_SSHIP2_C, T_SSHIP2_R, T_SSHIP2_RR}; //bulky
        TexIDs silverShip3[5] = {T_SSHIP3_LL, T_SSHIP3_L, T_SSHIP3_C, T_SSHIP3_R, T_SSHIP3_RR}; //midrange
        TexIDs carrotShip[5] = {T_CSHIP_LL, T_CSHIP_L, T_CSHIP_C, T_CSHIP_R, T_CSHIP_RR}; //player ship
    
        TexIDs greenShip[5] = {T_GSHIP_LL, T_GSHIP_L, T_GSHIP_C, T_GSHIP_R, T_GSHIP_RR};
        TexIDs greenShip2[5] = {T_GSHIP2_LL, T_GSHIP2_L, T_GSHIP2_C, T_GSHIP2_R, T_GSHIP2_RR};
        TexIDs redShip[5] = {T_RSHIP_LL, T_RSHIP_L, T_RSHIP_C, T_RSHIP_R, T_RSHIP_RR};
        TexIDs redBlob[4] = {T_RBLOB_00, T_RBLOB_01, T_RBLOB_02, T_RBLOB_03};
        TexIDs blade[4] = {T_BLADE_00, T_BLADE_01, T_BLADE_02, T_BLADE_03};
    
        //boss packs ***
        TexIDs boss1body[6] = {T_BOSS_BLC, T_BOSS_BMC, T_BOSS_BRC, T_BOSS_BLD, T_BOSS_BMD, T_BOSS_BRD};
        TexIDs boss1charge[8] = {T_BOSS_C0, T_BOSS_C1, T_BOSS_C2, T_BOSS_C3, T_BOSS_C4, T_BOSS_C5, T_BOSS_C6, T_BOSS_C7};
    
        //weapon packs ***
        TexIDs blueLaser[3] = {T_BLUE_LASER_BASE, T_BLUE_LASER_SHAFT, T_BLUE_LASER_TIP};
    
        //item packs ***
        TexIDs hpBlob[4] = {T_HP_BLOB1, T_HP_BLOB2, T_HP_BLOB3, T_HP_BLOB4};
    
        //explosion packs ***
        TexIDs nukeEXP[17] = {T_EXP_NUKE_01, T_EXP_NUKE_02, T_EXP_NUKE_03, T_EXP_NUKE_04, T_EXP_NUKE_05, T_EXP_NUKE_06, T_EXP_NUKE_07, T_EXP_NUKE_08, T_EXP_NUKE_09, T_EXP_NUKE_10, T_EXP_NUKE_11, T_EXP_NUKE_12, T_EXP_NUKE_13, T_EXP_NUKE_14, T_EXP_NUKE_15, T_EXP_NUKE_16, T_EXP_NUKE_17};
    
        TexIDs regEXP[13] = {T_EXP_REG_01, T_EXP_REG_02, T_EXP_REG_03, T_EXP_REG_04, T_EXP_REG_05, T_EXP_REG_06, T_EXP_REG_07, T_EXP_REG_08, T_EXP_REG_09, T_EXP_REG_10, T_EXP_REG_11, T_EXP_REG_12, T_EXP_REG_13};
    
    
        //Level tile packs
        //forest
        TexIDs forest[14] = {T_FOREST_TL, T_FOREST_TM, T_FOREST_TR, T_FOREST_ML, T_FOREST_MM, T_FOREST_MR, T_FOREST_BL, T_FOREST_BM, T_FOREST_BR, T_FOREST_ETL, T_FOREST_EBL, T_FOREST_ETR, T_FOREST_EBR, T_FOREST_EM};
    
        //ocean
        TexIDs ocean[14] = {T_OCEAN_TL, T_OCEAN_TM, T_OCEAN_TR, T_OCEAN_ML, T_OCEAN_MM, T_OCEAN_MR, T_OCEAN_BL, T_OCEAN_BM, T_OCEAN_BR, T_OCEAN_ETL, T_OCEAN_EBL, T_OCEAN_ETR, T_OCEAN_EBR, T_OCEAN_EM};
    
        //grass
    TexIDs grass[14] = {T_GRASS_TL, T_GRASS_TM, T_GRASS_TR, T_GRASS_ML, T_GRASS_MM, T_GRASS_MR, T_GRASS_BL, T_GRASS_BM, T_GRASS_BR, T_GRASS_ETL, T_GRASS_EBL, T_GRASS_ETR, T_GRASS_EBR, T_GRASS_EM};
    
    //rockyP
    TexIDs rockyP[14] = {T_ROCKYP_TL, T_ROCKYP_TM, T_ROCKYP_TR, T_ROCKYP_ML, T_ROCKYP_MM, T_ROCKYP_MR, T_ROCKYP_BL, T_ROCKYP_BM, T_ROCKYP_BR, T_ROCKYP_ETL, T_ROCKYP_EBL, T_ROCKYP_ETR, T_ROCKYP_EBR, T_ROCKYP_EM};
    
    //metal
    TexIDs metal[14] = {T_METAL_TL, T_METAL_TM, T_METAL_TR, T_METAL_ML, T_METAL_MM, T_METAL_MR, T_METAL_BL, T_METAL_BM, T_METAL_BR, T_METAL_ETL, T_METAL_EBL, T_METAL_ETR, T_METAL_EBR, T_METAL_EM};
    
    //industrial
    TexIDs industrial[14] = {T_INDUSTRIAL_TL, T_INDUSTRIAL_TM, T_INDUSTRIAL_TR, T_INDUSTRIAL_ML, T_INDUSTRIAL_MM, T_INDUSTRIAL_MR, T_INDUSTRIAL_BL, T_INDUSTRIAL_BM, T_INDUSTRIAL_BR, T_INDUSTRIAL_ETL, T_INDUSTRIAL_EBL, T_INDUSTRIAL_ETR, T_INDUSTRIAL_EBR, T_INDUSTRIAL_EM};
    
    //lava
    TexIDs lava[14] = {T_LAVA_TL, T_LAVA_TM, T_LAVA_TR, T_LAVA_ML, T_LAVA_MM, T_LAVA_MR, T_LAVA_BL, T_LAVA_BM, T_LAVA_BR, T_LAVA_ETL, T_LAVA_EBL, T_LAVA_ETR, T_LAVA_EBR, T_LAVA_EM};
    
    
    
        TexIDs *levelTextures[7] = {grass, forest, ocean, rockyP, metal, industrial, lava}; //master leveltexturepack carrier


    
};

//===============================================================




#endif /* gEngine_h */
