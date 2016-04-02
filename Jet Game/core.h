//  basic core module for implementing graphics and sound control
//  core.h
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/19/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//

#ifndef core_h
#define core_h
#include "stdafx.h"

#include "base.h"
#include "sys.h"

//#define G_WIDTH 1000

#define MAX_TEXTURES 256
#define MAX_SOUNDS 50
#define SHADOW_OFFSET 60.f
#define SHADOW_SIZE_MOD 0.75f

struct rgba {
    float r, g, b, a;
    void setVal(float rr,float gg, float bb, float aa) { r = rr, g = gg, b = bb, a = aa; }
    rgba(float rr,float gg, float bb, float aa) : r(rr), g(gg), b(bb), a(aa) {}
    rgba() : r(0), g(0), b(0), a(0) {}
};

enum WavIDs {
    // *** Soundtracks ***
    W_DOOM1, W_BIGBLUE_SS, W_SSJ3, W_STAT_BRIEFING,
    
    // *** SFX ***
    
    //*** SFX ***
    //indicator sounds**
    W_IND_FAILURE, W_IND_BOSS, W_IND_VICTORY,
    
    //explosions**
    W_EXPLOSION_1,
    
    //weapon Impacts
    W_IMPACT_1,
    
    //weapon fire
    W_LASER_SHOT, W_POWERUP
    
};

enum TexIDs {
    //background textures **
    T_BKG, T_WHITE,
    
    //Fonts **
    //Kromasky
    T_KROMASKY, T_SIZER_KROMASKY,
    
    //info textures **
    T_HP_BAR, T_LEVEL_BAR, T_BOSS_HP_BAR, T_OMEGA_BOMB_INDI,
    
    //player ship textures **
    T_BSHIP_C, T_BSHIP_L, T_BSHIP_LL, T_BSHIP_R, T_BSHIP_RR,
    
    //enemy ship textures **
    //green ship
    T_GSHIP_C, T_GSHIP_L, T_GSHIP_LL, T_GSHIP_R, T_GSHIP_RR,
    
    //green jet 2
    T_GSHIP2_C, T_GSHIP2_L, T_GSHIP2_LL, T_GSHIP2_R, T_GSHIP2_RR,
    
    //red jet
    T_RSHIP_C, T_RSHIP_L, T_RSHIP_LL, T_RSHIP_R, T_RSHIP_RR,
    
    //red spinning blob
    T_RBLOB_00, T_RBLOB_01, T_RBLOB_02, T_RBLOB_03,
    
    //spinning blades
    T_BLADE_00, T_BLADE_01, T_BLADE_02, T_BLADE_03,
    
    //Boss Textures **
    T_BOSS_BLC, T_BOSS_BMC, T_BOSS_BRC, T_BOSS_BLD, T_BOSS_BMD, T_BOSS_BRD, T_BOSS_C0, T_BOSS_C1, T_BOSS_C2, T_BOSS_C3, T_BOSS_C4, T_BOSS_C5, T_BOSS_C6, T_BOSS_C7,
    
    //ship weapons **
    //primary weapons
    T_SINGLE_SHOT, T_DOUBLE_SHOT, T_TRIPLE_SHOT, T_QUAD_SHOT,
    
    //Tertiary weapons
    T_SIDEWAYS_ML_SINGLE_SHOT, T_SIDEWAYS_MR_SINGLE_SHOT,
    
    //laser weapons
    T_BLUE_LASER_BASE, T_BLUE_LASER_SHAFT, T_BLUE_LASER_TIP,
    
    //secondary weapons
    T_ROCKET1, T_ROCKET2,
    
    //enemy weapons
    T_BLOB_SHOT,
    
    //ship_items **
    //hp blob
    T_HP_BLOB1, T_HP_BLOB2, T_HP_BLOB3, T_HP_BLOB4,
    
    //Omega Bomb
    T_UPG_OMEGA_BOMB, T_HALO,
    
    //weapon upgrades
    T_UPG_DOUBLE_SHOT, T_UPG_TRIPLE_SHOT, T_UPG_SINGLE_ROCKET, T_UPG_SINGLE_SIDEWAYS_SHOT_M,
    
    //explosions **
    //nuke
    T_EXP_NUKE_01, T_EXP_NUKE_02, T_EXP_NUKE_03, T_EXP_NUKE_04, T_EXP_NUKE_05, T_EXP_NUKE_06, T_EXP_NUKE_07, T_EXP_NUKE_08, T_EXP_NUKE_09, T_EXP_NUKE_10, T_EXP_NUKE_11, T_EXP_NUKE_12, T_EXP_NUKE_13, T_EXP_NUKE_14, T_EXP_NUKE_15, T_EXP_NUKE_16, T_EXP_NUKE_17,
    
    //regular exp
    T_EXP_REG_01, T_EXP_REG_02, T_EXP_REG_03, T_EXP_REG_04, T_EXP_REG_05, T_EXP_REG_06, T_EXP_REG_07, T_EXP_REG_08, T_EXP_REG_09, T_EXP_REG_10, T_EXP_REG_11, T_EXP_REG_12, T_EXP_REG_13,
    
    //clouds**
    T_CLOUD_00, T_CLOUD_01, T_CLOUD_02, T_CLOUD_03, T_CLOUD_04, T_CLOUD_05, T_CLOUD_06, T_CLOUD_07, T_CLOUD_08,
    
    //LEVEL TILES **
    //forest
    T_FOREST_TL, T_FOREST_TM, T_FOREST_TR, T_FOREST_ML, T_FOREST_MM, T_FOREST_MR, T_FOREST_BL, T_FOREST_BM, T_FOREST_BR, T_FOREST_ETL, T_FOREST_EBL, T_FOREST_ETR, T_FOREST_EBR, T_FOREST_EM,
    
    //ocean
    T_OCEAN_TL, T_OCEAN_TM, T_OCEAN_TR, T_OCEAN_ML, T_OCEAN_MM, T_OCEAN_MR, T_OCEAN_BL, T_OCEAN_BM, T_OCEAN_BR, T_OCEAN_ETL, T_OCEAN_EBL, T_OCEAN_ETR, T_OCEAN_EBR, T_OCEAN_EM,
    
    //GRASS
    T_GRASS_TL, T_GRASS_TM, T_GRASS_TR, T_GRASS_ML, T_GRASS_MM, T_GRASS_MR, T_GRASS_BL, T_GRASS_BM, T_GRASS_BR, T_GRASS_ETL, T_GRASS_EBL, T_GRASS_ETR, T_GRASS_EBR, T_GRASS_EM,
    
    //METAL
    T_METAL_TL, T_METAL_TM, T_METAL_TR, T_METAL_ML, T_METAL_MM, T_METAL_MR, T_METAL_BL, T_METAL_BM, T_METAL_BR, T_METAL_ETL, T_METAL_EBL, T_METAL_ETR, T_METAL_EBR, T_METAL_EM,
    
    //INDUSTRIAL
    T_INDUSTRIAL_TL, T_INDUSTRIAL_TM, T_INDUSTRIAL_TR, T_INDUSTRIAL_ML, T_INDUSTRIAL_MM, T_INDUSTRIAL_MR, T_INDUSTRIAL_BL, T_INDUSTRIAL_BM, T_INDUSTRIAL_BR, T_INDUSTRIAL_ETL, T_INDUSTRIAL_EBL, T_INDUSTRIAL_ETR, T_INDUSTRIAL_EBR, T_INDUSTRIAL_EM,
    
    //ROCKYP
    T_ROCKYP_TL, T_ROCKYP_TM, T_ROCKYP_TR, T_ROCKYP_ML, T_ROCKYP_MM, T_ROCKYP_MR, T_ROCKYP_BL, T_ROCKYP_BM, T_ROCKYP_BR, T_ROCKYP_ETL, T_ROCKYP_EBL, T_ROCKYP_ETR, T_ROCKYP_EBR, T_ROCKYP_EM,
    
    //LAVA
    T_LAVA_TL, T_LAVA_TM, T_LAVA_TR, T_LAVA_ML, T_LAVA_MM, T_LAVA_MR, T_LAVA_BL, T_LAVA_BM, T_LAVA_BR, T_LAVA_ETL, T_LAVA_EBL, T_LAVA_ETR, T_LAVA_EBR, T_LAVA_EM
    
};



//main core module
class core {
    public:
        //basic rng functions, i wrote these
        core(void);
        ~core(void);
        float randf(float lower_bound, float upper_bound);
        inline float randi(int lower_bound, int upper_bound) {int diff; diff = upper_bound - lower_bound + 1; return(rand()%diff + lower_bound); }
        inline bool randchance(int percent_chance) { int rng = rand() % 100; return(percent_chance > rng); }
    
        //glfw openGL bindings
        GLuint loadBmp(const char filename[], bool wrap);
        GLuint loadBmp_jonbho(const char filename[], bool wrap); //jonbho's loadBmp method
        void unloadBmp(int texIndex);
        inline GLuint GetBmpOpenGLTex(int texIndex) { return(gTextures[texIndex].tex); }
        void RenderCenteredSprite(vec pos, vec size, int texix, rgba color, bool additive, bool flip, bool hasShadow = false, bool reverse = false);
        vec RenderCenteredString(const char string[], vec pos, float fontSize, rgba color, bool additive);
    
        //openAL bindings
    
        ALuint loadWave(const char filename[]);
        void unloadWave(int wavIndex);
        void playSound(int soundIndex, float volume = 1.f, bool Loop = false);
        void stopSound(int soundIndex);
        void stopAllSounds(void);
        void pauseAllSounds(bool resume = false);
    
        //submethods
        float getTexWidth(TexIDs tex) { return(gTextures[tex].pixw); }
        float getTexHeight(TexIDs tex) { return(gTextures[tex].pixh); }
    
    protected:
    
        #define READ_LE_WORD(a)  (a[0] + a[1]*0x100)
        #define READ_LE_DWORD(a) (a[0] + a[1]*0x100 + a[2]*0x10000 + a[3]*0x1000000)
        static byte databuffer[2048 * 2048 * 4];
        //byte *databuffer;
        
        inline dword squared(dword v) { v--; v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16; v++; return v; } //next power of 2
    
        struct BMPFileHeader
        {
            
            byte header[54]; // Each BMP file begins by a 54-bytes header
            dword offset;     // Position in the file where the actual data begins
            dword width, height;
            dword imageSize;   // = width*height*3
        };
    
        //fontReferenceer
        char fontRef[8][9] = {
            {" !   %-'"},
            {"   +, ./"},
            {"01234567"},
            {"89:;   ?"},
            {" abcdefg"},
            {"hijklmno"},
            {"pqrstuvw"},
            {"xyz     "}
        };
    
    
        //Audio structs
        struct Wave {
            char name[150];
            ALuint source;
            ALuint buffer;
        };
        struct wave : Wave {
            bool inUse;
            bool isActive;
        } gWaves[MAX_SOUNDS] = {};
    
        Wave waveList[MAX_SOUNDS] = {
            //*** soundtracks ***
            {"data/Audio/soundtracks/doom1.wav"},
            {"data/Audio/soundtracks/bigBlueSS.wav"},
            {"data/Audio/soundtracks/SSJ3.wav"},
            {"data/Audio/sfx/stat_briefingScreenLoop.wav"},
            
            //*** SFX ***
            //indicator sounds**
            {"data/Audio/sfx/failure.wav"},
            {"data/Audio/sfx/bossWarning.wav"},
            {"data/Audio/sfx/victoryIndicator.wav"},
            
            //explosions**
            {"data/Audio/sfx/explosion1.wav"},
            
            //weapon Impacts
            {"data/Audio/sfx/impact1.wav"},
            
            //weapon fire
            {"data/Audio/sfx/laserShot.wav"},
            {"data/Audio/sfx/powerup.wav"}
            
            
        };
    
        //textrue structs
        struct Texture {
            char name[150];
            bool wrap;
            GLuint tex;
        };
        struct texture : Texture {
            bool inUse;
            float w, h;
            int pixw, pixh;
        } gTextures[MAX_TEXTURES] = {};
    
        Texture textureList[MAX_TEXTURES] = {
            //background textures **
            {"data/Textures/bkg0.bmp", false, 0},
            {"data/Textures/white.bmp", false, 0},
            
            //Fonts **
            //kromasky
            {"data/Textures/Fonts/Kromasky.bmp", false, 0},
            {"data/Textures/Fonts/sizerKromasky.bmp", false, 0},
            
            //info textures **
            {"data/Textures/Info/hpBar.bmp", false, 0},
            {"data/Textures/Info/levelBar.bmp", false, 0},
            {"data/Textures/Enemies/Boss/bossHpBar.bmp", false, 0},
            {"data/Textures/Info/omegaBombInd.bmp", false, 0},
            
            //Player Ship Textures **
            {"data/Textures/PlayerShipModels/BshipC.bmp", false, 0},
            {"data/Textures/PlayerShipModels/BshipL.bmp", false, 0},
            {"data/Textures/PlayerShipModels/BshipLL.bmp", false, 0},
            {"data/Textures/PlayerShipModels/BshipR.bmp", false, 0},
            {"data/Textures/PlayerShipModels/BshipRR.bmp", false, 0},
            
            //Enemy Ship Textures **
            //green jet
            {"data/Textures/Enemies/GshipC.bmp", false, 0},
            {"data/Textures/Enemies/GshipL.bmp", false, 0},
            {"data/Textures/Enemies/GshipLL.bmp", false, 0},
            {"data/Textures/Enemies/GshipR.bmp", false, 0},
            {"data/Textures/Enemies/GshipRR.bmp", false, 0},
            //green jet 2
            {"data/Textures/Enemies/Gship2C.bmp", false, 0},
            {"data/Textures/Enemies/Gship2L.bmp", false, 0},
            {"data/Textures/Enemies/Gship2LL.bmp", false, 0},
            {"data/Textures/Enemies/Gship2R.bmp", false, 0},
            {"data/Textures/Enemies/Gship2RR.bmp", false, 0},
            
            //red jet
            {"data/Textures/Enemies/RshipC.bmp", false, 0},
            {"data/Textures/Enemies/RshipL.bmp", false, 0},
            {"data/Textures/Enemies/RshipLL.bmp", false, 0},
            {"data/Textures/Enemies/RshipR.bmp", false, 0},
            {"data/Textures/Enemies/RshipRR.bmp", false, 0},
            
            //red spinning blob
            {"data/Textures/Enemies/RBlob00.bmp", false, 0},
            {"data/Textures/Enemies/RBlob01.bmp", false, 0},
            {"data/Textures/Enemies/RBlob02.bmp", false, 0},
            {"data/Textures/Enemies/RBlob03.bmp", false, 0},
            
            //spinning blades
            {"data/Textures/Enemies/Blade00.bmp", false, 0},
            {"data/Textures/Enemies/Blade01.bmp", false, 0},
            {"data/Textures/Enemies/Blade02.bmp", false, 0},
            {"data/Textures/Enemies/Blade03.bmp", false, 0},
            
            //Boss Textures **
            {"data/Textures/Enemies/Boss/L1/bodyLeftComp.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/bodyMidComp.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/bodyRightComp.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/bodyLeftDmg.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/bodyMidDmg.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/bodyRightDmg.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/charge00.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/charge01.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/charge02.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/charge03.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/charge04.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/charge05.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/charge06.bmp", false, 0},
            {"data/Textures/Enemies/Boss/L1/charge07.bmp", false, 0},
            
            //ship weapons **
            //Primary Weapons
            {"data/Textures/Weapons/singleShotBlaster.bmp", false, 0},
            {"data/Textures/Weapons/doubleShotBlaster.bmp", false, 0},
            {"data/Textures/Weapons/tripleShotBlaster.bmp", false, 0},
            {"data/Textures/Weapons/quadShotBlaster.bmp", false, 0},
            
            //Tertiary Weapons
            {"data/Textures/Weapons/sidewaysML_SingleShot.bmp", false, 0},
            {"data/Textures/Weapons/sidewaysMR_SingleShot.bmp", false, 0},
            
            //Laser Weapons
            {"data/Textures/Weapons/blueLaser00.bmp", false, 0},
            {"data/Textures/Weapons/blueLaser01.bmp", false, 0},
            {"data/Textures/Weapons/blueLaser02.bmp", false, 0},
            
            //Secondary Weapons
            {"data/Textures/Weapons/rocket1.bmp", false, 0},
            {"data/Textures/Weapons/rocket2.bmp", false, 0},
            
            
            //Enemy Weapons
            {"data/Textures/Weapons/singleShotBlob.bmp", false, 0},
            
            
            
            
            //ship items **
            //hp blob
            {"data/Textures/items/HPblobs/hp1.bmp", false, 0},
            {"data/Textures/items/HPblobs/hp2.bmp", false, 0},
            {"data/Textures/items/HPblobs/hp3.bmp", false, 0},
            {"data/Textures/items/HPblobs/hp4.bmp", false, 0},
            
            //omega bomb
            {"data/Textures/items/omegaBomb.bmp", false, 0},
            {"data/Textures/Weapons/halo.bmp", false, 0},
            
            //weapon upgrades
            {"data/Textures/items/WeaponUpgrades/doubleBlasterUPG.bmp", false, 0},
            {"data/Textures/items/WeaponUpgrades/tripleBlasterUPG.bmp", false, 0},
            {"data/Textures/items/WeaponUpgrades/singleRocketUPG.bmp", false, 0},
            {"data/Textures/items/WeaponUpgrades/SingleSidewaysMBlasterUPG.bmp", false, 0},
            
            //explosions **
            //nuke explosion
            {"data/Textures/Explosions/exp1/exp01.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp02.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp03.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp04.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp05.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp06.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp07.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp08.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp09.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp10.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp11.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp12.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp13.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp14.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp15.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp16.bmp", false, 0},
            {"data/Textures/Explosions/exp1/exp17.bmp", false, 0},
            
            //regular exp
            {"data/Textures/Explosions/exp2/exp01.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp02.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp03.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp04.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp05.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp06.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp07.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp08.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp09.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp10.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp11.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp12.bmp", false, 0},
            {"data/Textures/Explosions/exp2/exp13.bmp", false, 0},
            
            //CLOUDS**
            {"data/Textures/clouds/cloud00.bmp", false, 0},
            {"data/Textures/clouds/cloud01.bmp", false, 0},
            {"data/Textures/clouds/cloud02.bmp", false, 0},
            {"data/Textures/clouds/cloud03.bmp", false, 0},
            {"data/Textures/clouds/cloud04.bmp", false, 0},
            {"data/Textures/clouds/cloud05.bmp", false, 0},
            {"data/Textures/clouds/cloud06.bmp", false, 0},
            {"data/Textures/clouds/cloud07.bmp", false, 0},
            {"data/Textures/clouds/cloud08.bmp", false, 0},
            
            
            //LEVEL BACKGROUNDS **
            //forest
            {"data/Textures/levelTiles/Forest/TL.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/TM.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/TR.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/ML.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/MM.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/MR.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/BL.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/BM.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/BR.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/ETL.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/EBL.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/ETR.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/ER.bmp", false, 0},
            {"data/Textures/levelTiles/Forest/EM.bmp", false, 0},
            
            //ocean
            {"data/Textures/levelTiles/Ocean/TL.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/TM.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/TR.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/ML.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/MM.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/MR.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/BL.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/BM.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/BR.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/ETL.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/EBL.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/ETR.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/EBR.bmp", false, 0},
            {"data/Textures/levelTiles/Ocean/EM.bmp", false, 0},
            
            //grass
            {"data/Textures/levelTiles/Grass/TL.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/TM.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/TR.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/ML.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/MM.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/MR.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/BL.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/BM.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/BR.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/ETL.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/EBL.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/ETR.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/EBR.bmp", false, 0},
            {"data/Textures/levelTiles/Grass/EM.bmp", false, 0},
            
            //Metal
            {"data/Textures/levelTiles/Metal/TL.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/TM.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/TR.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/ML.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/MM.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/MR.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/BL.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/BM.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/BR.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/ETL.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/EBL.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/ETR.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/EBR.bmp", false, 0},
            {"data/Textures/levelTiles/Metal/EM.bmp", false, 0},
            
            //Industrial
            {"data/Textures/levelTiles/Industrial/TL.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/TM.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/TR.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/ML.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/MM.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/MR.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/BL.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/BM.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/BR.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/ETL.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/EBL.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/ETR.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/EBR.bmp", false, 0},
            {"data/Textures/levelTiles/Industrial/EM.bmp", false, 0},
            
            //RockyP
            {"data/Textures/levelTiles/RockyP/TL.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/TM.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/TR.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/ML.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/MM.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/MR.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/BL.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/BM.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/BR.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/ETL.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/EBL.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/ETR.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/EBR.bmp", false, 0},
            {"data/Textures/levelTiles/RockyP/EM.bmp", false, 0},
            
            //Lava
            {"data/Textures/levelTiles/Lava/TL.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/TM.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/TR.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/ML.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/MM.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/MR.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/BL.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/BM.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/BR.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/ETL.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/EBL.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/ETR.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/EBR.bmp", false, 0},
            {"data/Textures/levelTiles/Lava/EM.bmp", false, 0}
            
            
        };
    
};




#endif /* core_h */
