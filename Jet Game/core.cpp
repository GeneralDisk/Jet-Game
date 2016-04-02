//
//  core.cpp
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/19/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//

#include "core.h"
//#include <cstdio>

byte core::databuffer[2048 * 2048 * 4];

//===============================================================
//core()
core::core(void) {
    
    for (int i = 0; strcmp(textureList[i].name,""); i++) {
        loadBmp(textureList[i].name, textureList[i].wrap);
    }//load all textures
    
    for (int i = 0; strcmp(waveList[i].name,""); i++) {
        loadWave(waveList[i].name);
    }//load all wave files

}

//===============================================================
//~core()
core::~core(void) {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (gTextures[i].inUse) {
            unloadBmp(i);
        }
    }//unload all textures
    
    for (int i = 0; i < MAX_SOUNDS; i++) {
        if (gWaves[i].inUse) {
            unloadWave(i);
  //          alDeleteSources(<#ALsizei n#>, <#const ALuint *sources#>)
//            alDeleteBuffers(<#ALsizei n#>, <#const ALuint *buffers#>)
        }
    }//unload all waves
}

//===============================================================
//randf()
float core::randf(float lower_bound, float upper_bound) {
    float diff, rng;
    diff = upper_bound - lower_bound;
    rng = rand() % (int)(diff*10000) + (int)(lower_bound*10000);
    rng = ((float)rng)/10000;
    return(rng);
}

//=============================================================== GRAPHICS BINDINGS ===============================================================//
//===============================================================
//loadBmp()
GLuint core::loadBmp(const char filename[], bool wrap) {
    
    BMPFileHeader fheader;
    //char path[100];
    //getcwd(path, 100);
    //std::cout << "PATH: " << path << std::endl;
    FILE *file = fopen(filename, "rb");
    if (!file) {
        std::cout << "Error: file '" << filename << "' not found.\n";
        return(0);
    } //open the file
    
    if (fread(fheader.header, 1, 54, file) != 54) {
        std::cout << "Error: Not BMP file.\n";
        return(0);
    }
    
    if ( fheader.header[0]!='B' || fheader.header[1]!='M' ) {
        std::cout << "Error: File incorrectly formated.\n";
        return(0);
    } //.bmp files always begin with 'BM'
    
    fheader.offset = *(int*)&(fheader.header[0x0A]);
    fheader.imageSize = *(int*)&(fheader.header[0x22]);
    fheader.width = *(int*)&(fheader.header[0x12]);
    fheader.height = *(int*)&(fheader.header[0x16]);
    //fheader.offset = *(int*)&(fheader.header[0xA]);
    //std::cout << fheader.dataPos << "  IS: " << fheader.imageSize << "  W: " << fheader.width << "  H: " << fheader.height << std::endl;
    //std::cout << "OFFSET: " << fheader.offset << std::endl;
    //std::cout << "OFFSET: " << fheader.dataPos << std::endl;
    
    if (fheader.height > 100000) {
        //std::cout << "Error: Bad height: " << fheader.height << std::endl;
        fheader.height = abs((int)fheader.height); //code fixes the bad val problem, i don't really know why...
        //std::cout << "Error: Bad height: " << fheader.height << std::endl;
        
    }
    if (fheader.width > 100000) {
        //std::cout << "Error: Bad width: " << fheader.width << std::endl;
        fheader.width = abs((int)fheader.width);
    }
    //std::cout << "I.S.: " << fheader.imageSize << std::endl;
    if (fheader.offset == 0) {
        std::cout << "Offset data error.\n";
        fheader.offset = 54; //this should generally be the default
    }
    if (fheader.imageSize == 0)
        fheader.imageSize = fheader.height * fheader.width * 3;

    
    
    fseek(file, fheader.offset, 0); //set file pointer to the beginning of the bmp data

    fread(databuffer, 1, fheader.imageSize*2, file); //read img file
    fclose(file);
    
    //openGL texture configuration
    GLuint texId;
    glGenTextures(1, &texId); //create an openGL tex
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, texId);
    
    // Give the image to OpenGL
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
    
    
    dword swidth = squared(fheader.width);
    dword sheight = squared(fheader.height);
    
    //std::cout << "W: " << swidth << "  H: " << sheight << std::endl;
    
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, swidth, sheight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, NULL);
//    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width_pow2, height_pow2, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, NULL);
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, fheader.width, fheader.height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, databuffer);
    
    
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (gTextures[i].inUse == false) {
            //std::cout << "AT: " << i << std::endl;
            gTextures[i].inUse = true;
            gTextures[i].h = fheader.height/((float)sheight);
            gTextures[i].w = fheader.width/((float)swidth);
            gTextures[i].pixh = fheader.height;
            gTextures[i].pixw = fheader.width;
            gTextures[i].tex = texId;
            //std::cout << texId <<std::endl;
            return(texId);
        }
    }
    return(0);
}

//===============================================================
//unloadBmp()
void core::unloadBmp(int texIndex) {
    glDeleteTextures( 1, &gTextures[texIndex].tex );
    gTextures[texIndex].inUse = false;
}

//===============================================================
//RenderCenteredSprite()
void core::RenderCenteredSprite(vec pos, vec size, int texIndex, rgba color, bool additive, bool flip, bool hasShadow, bool reverse) {
    if (texIndex < MAX_TEXTURES && texIndex >= 0) {
        
        if (hasShadow) {
            rgba black(0.f,0.f,0.f,0.5f);
            RenderCenteredSprite(vmake(pos.x+(SHADOW_OFFSET), pos.y-SHADOW_OFFSET), vscale(size, SHADOW_SIZE_MOD), texIndex, black, additive, flip);
        }
        
        glColor4f(color.r, color.g, color.b, color.a);

        if (additive)
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        else
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        
        vec p0 = vsub(pos, vscale(size, .5f));
        vec p1 = vadd(pos, vscale(size, .5f));
        
        //std::cout << "p1: " << p1.x << " " << p1.y << "\np0: " << p0.x << " " << p0.y << "\n\n";
        //std::cout << "texIndex: " << texIndex << std::endl;
        
        glBindTexture( GL_TEXTURE_2D, gTextures[texIndex].tex );
        glBegin( GL_QUADS );
        if (flip) {
            glTexCoord2d(0.0, 0.0);
            glVertex2f(p0.x, p0.y);
            glTexCoord2d(gTextures[texIndex].w, 0.0);
            glVertex2f(p1.x, p0.y);
            glTexCoord2d(gTextures[texIndex].w, gTextures[texIndex].h);
            glVertex2f(p1.x, p1.y);
            glTexCoord2d(0.0, gTextures[texIndex].h);
            glVertex2f(p0.x, p1.y);
        }
        else if (reverse) {
            glTexCoord2d(0.0, 0.0);
            glVertex2f(p1.x, p1.y);
            glTexCoord2d(gTextures[texIndex].w, 0.0);
            glVertex2f(p0.x, p1.y);
            glTexCoord2d(gTextures[texIndex].w, gTextures[texIndex].h);
            glVertex2f(p0.x, p0.y);
            glTexCoord2d(0.0, gTextures[texIndex].h);
            glVertex2f(p1.x, p0.y);
 
        }
        else {
            glTexCoord2d(0.0, 0.0);
            glVertex2f(p0.x, p1.y);
            glTexCoord2d(gTextures[texIndex].w, 0.0);
            glVertex2f(p1.x, p1.y);
            glTexCoord2d(gTextures[texIndex].w, gTextures[texIndex].h);
            glVertex2f(p1.x, p0.y);
            glTexCoord2d(0.0, gTextures[texIndex].h);
            glVertex2f(p0.x, p0.y);
        }
        glEnd();
        
    }
    else
        std::cout << "ERROR: Bad texIndex val: " << texIndex << std::endl;
    
}

//===============================================================
//RenderCenteredString()
vec core::RenderCenteredString(const char string[], vec pos, float fontSize, rgba color, bool additive) {
    int numRows = size_of(fontRef);
    int sizeRow = strlen(fontRef[0]);
    float w, h;
    float sizeMod = fontSize;
    w = gTextures[T_SIZER_KROMASKY].pixw*sizeMod;
    h = gTextures[T_SIZER_KROMASKY].pixh*sizeMod;
 //   std::cout << "string: " << string << " at ";
//    std::cout << "pos: "; vprint(pos);
    
    int sizeOfString = strlen(string);
    int extra = 0;
    int start = 0;
    vec newPos;
    bool wrap = false;
    wrapText:;
    if (sizeOfString*w >= G_WIDTH) {
        //std::cout << "need to wrap string " << string << "\n";
        extra = sizeOfString - (int)(G_WIDTH/(w));
        //std::cout << "SIZE: " << sizeOfString << " but can only fit size: " << (int)(G_WIDTH/(w)) << " -- " << extra <<std::endl;
        sizeOfString = (int)(G_WIDTH/(w));
        wrap = true;
    }
    
    for (int i = 0; i < sizeOfString; i++) {
        for (int j = 0; j < numRows; j++) {
            for (int k = 0; k < sizeRow; k++) {
                if (string[i+start] == fontRef[j][k]) {
                    //j is the row number, k is the line number
                    if (sizeOfString%2 == 0) { //even # of chars in string
                        if (i >= sizeOfString/2) { //if you're on the section of the string to the right of the pos
                            newPos = vmake((pos.x + w/2 + (i-sizeOfString/2)*w),pos.y);
                        }
                        else { // if you're on the section of the string to the left of pos
                            newPos = vmake((pos.x - w/2 - (sizeOfString/2-(i+1))*w),pos.y);
                        }
                    }
                    else { //odd # of chars in string
                        if (i >= sizeOfString/2) {
                            newPos = vmake((pos.x + w*(i-sizeOfString/2)),pos.y);
                        }
                        else {
                            newPos = vmake((pos.x - w*(sizeOfString/2-i)),pos.y);
                        }
                    }
                    
                    //Render the texture
                    glColor4f(color.r, color.g, color.b, color.a);
                    
                    if (additive)
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                    else
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    
                    vec size = vmake(w,h); //pretty sure size here is related to the texture size of the rendered oobject
                    vec p0 = vsub(newPos, vscale(size, .5f));
                    vec p1 = vadd(newPos, vscale(size, .5f));
                    
                    glBindTexture( GL_TEXTURE_2D, gTextures[T_KROMASKY].tex );
                    glBegin( GL_QUADS );

                    float Nwidth, Nheight, Nx, Ny, Nx0, Ny0;
                    //NOTE** true equation calls for you to multiply below values by parent textures w and h values
                    Nwidth = (float)gTextures[T_SIZER_KROMASKY].pixw/(float)gTextures[T_KROMASKY].pixw; //normalized
                    Nheight = (float)gTextures[T_SIZER_KROMASKY].pixh/(float)gTextures[T_KROMASKY].pixh; //normalized
                    
                    Nx = Nwidth*k;
                    Nx0 = Nx + Nwidth;
                    Ny = Nheight*j;
                    Ny0 = Ny+Nheight;
                    
                    //NOTE: problem here is we're using pix values when we really need be using the NORMALIZED values
                    // lower left corner
                    glTexCoord2d(Nx, Ny0); //this tells gl where to look IN THE TEXTURE
                    //glTexCoord2d(0.f, gTextures[T_KROMASKY].h);
                    glVertex2f(p0.x, p0.y);
                    
                    //lower right corner
                    glTexCoord2d(Nx0, Ny0);
                    //glTexCoord2d(gTextures[T_KROMASKY].w, gTextures[T_KROMASKY].h);
                    glVertex2f(p1.x, p0.y);
                    
                    //upper right corner
                    glTexCoord2d(Nx0, Ny);
                    //glTexCoord2d(gTextures[T_KROMASKY].w, 0.f);
                    glVertex2f(p1.x, p1.y);
                    
                    //upper left corner
                    glTexCoord2d(Nx, Ny);
                    //glTexCoord2d(0.f, 0.f);
                    glVertex2f(p0.x, p1.y);
                   
                    glEnd();
                    goto next;
                }
            }
        }
    next:;
    }
    
    if (wrap) {
        wrap = false;
        start += sizeOfString;
        sizeOfString = extra;
        pos.y -= h*1.5;
        goto wrapText;
    }
    return(pos); // returns the position vector of the last rendered string
}
//=============================================================== AUDIO BINDINGS ===============================================================//
//===============================================================
//loadWave()
ALuint core::loadWave(const char filename[]) {
    ALuint retval = -1;
    //std::cout << "File: " << filename << std::endl;
    
    FILE *file = fopen(filename, "rb");
    if (!file) {
        std::cout << "Error: file '" << filename << "' not found.\n";
        return(retval);
    } //open the file
    
    char type[4];
    dword size, chunksize, sampleRate, avgBytesPerSec, dataSize;
    short formatType, channels, bytesPerSample, bitsPerSample;
    
    
    //check that the file type is, in fact, an acceptable .wav file
    fread(type, sizeof(char), 4, file); //read the first four char sized bytes into 'type'
    if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F') {
        std::cout << "Error: file type not 'RIFF'\n";
        return(retval);
    }
    
    fread(&size, sizeof(dword), 1, file); // read in the size of the file
    fread(type, sizeof(char), 4, file); //read next four chars of the file
    if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E') {
        std::cout << "Error: file type not 'WAVE'\n";
        return(retval);
    }

    fread(type, sizeof(char), 4, file); //read next four chars of the file
    if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ') {
        std::cout << "Error: format ID header not found\n";
        return(retval);
    }
    
    
    
    fread(&chunksize, sizeof(dword), 1, file);
    fread(&formatType, sizeof(short), 1, file);
    fread(&channels, sizeof(short), 1, file);
    fread(&sampleRate, sizeof(dword), 1, file);
    fread(&avgBytesPerSec, sizeof(dword), 1, file);
    fread(&bytesPerSample, sizeof(short), 1, file);
    fread(&bitsPerSample, sizeof(short), 1, file);
    
    fread(type, sizeof(char), 4, file); //read next four chars of the file, you should be at the 'data' ID at this point
    if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a') {
        std::cout << "Error: data ID header not found -- " << filename << "\n";
        return(retval);
    }
    
    fread(&dataSize, sizeof(dword), 1, file); //read in the data size chunk
    
    //now we should be at the start of the actual file data
    unsigned char *buffer = new unsigned char [dataSize]; //dynamically allocate a buffer the size of the audio file's main data
    fread(buffer, sizeof(byte), dataSize, file); //read the whole file, store data in buffer
    
    ALuint source;
    ALuint buf;
    ALuint freq = sampleRate;
    ALuint format = 0;
    
    alGenBuffers(1, &buf); //create an al buffer
    alGenSources(1, &source); //create an al source
    
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
    
    //load the data into the AL buffer
    alBufferData(buf, format, buffer, dataSize, freq);
    
    //set relative positions and velocities of the source & listener
    ALfloat SourcePos[] = {0.0, 0.0, 0.0};
    ALfloat SourceVel[] = {0.0, 0.0, 0.0};
    ALfloat ListenerPos[] = {0.0, 0.0, 0.0};
    ALfloat ListenerVel[] = {0.0, 0.0, 0.0};
    ALfloat ListenerOri[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    
    alListenerfv(AL_POSITION, ListenerPos);
    alListenerfv(AL_VELOCITY, ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
    
    alSourcei(source, AL_BUFFER, buf);
    alSourcef(source, AL_PITCH, 1.0f); //pitch control
    alSourcef(source, AL_GAIN, 1.f); //volume control
    alSourcefv(source, AL_POSITION, SourcePos);
    alSourcefv(source, AL_VELOCITY, SourceVel);
    
    for (int i = 0; i < MAX_SOUNDS; i++) {
        if (gWaves[i].inUse == false) {
            gWaves[i].inUse = true;
            //gWaves[i].isActive = false;
            gWaves[i].source = source;
            gWaves[i].buffer = buf;
            return(source);
            //gWaves[i].name = filename;
        }
    }
    alSourcePlay(source);
    return(retval);
}

//===============================================================
//unloadWave()
void core::unloadWave(int wavIndex) {
    alDeleteSources(1, &gWaves[wavIndex].source);
    alDeleteBuffers(1, &gWaves[wavIndex].buffer);
    gWaves[wavIndex].inUse = false;
}

//===============================================================
//playSound()
void core::playSound(int soundIndex, float volume, bool Loop) {
    if (soundIndex < MAX_SOUNDS) {
        if (gWaves[soundIndex].inUse) {
            //std::cout << "Playing Sound: " << soundIndex << std::endl;
            alSourcef(gWaves[soundIndex].source, AL_GAIN, volume); //volume control
            if (Loop) {
                alSourcei(gWaves[soundIndex].source, AL_LOOPING, AL_TRUE); //set sound to repeat
            }
            else
                alSourcei(gWaves[soundIndex].source, AL_LOOPING, AL_FALSE); //set sound to NOT repeat
            
            gWaves[soundIndex].isActive = true;
            alSourcePlay(gWaves[soundIndex].source); //play sound
        }
        else {
            std::cout << "Error: requested soundIndex is not loaded/inUse\n";
        }
    }
    else {
        std::cout << "Error: requested soundIndex is out of range\n";
    }
}

//===============================================================
//stopSound()
void core::stopSound(int soundIndex) {
    if (soundIndex < MAX_SOUNDS) {
        if (gWaves[soundIndex].inUse && gWaves[soundIndex].isActive) {
            alSourceStop(gWaves[soundIndex].source); //stop sound
            gWaves[soundIndex].isActive = false;
        }
        else {
            std::cout << "Error: requested soundIndex is not loaded/Active\n";
        }
    }
    else {
        std::cout << "Error: requested soundIndex is out of range\n";
    }
}

//===============================================================
//stopAllSounds()
void core::stopAllSounds(void) {
    for (int i = 0; i < MAX_SOUNDS; i++) {
        if (gWaves[i].inUse) {
            alSourceStop(gWaves[i].source);
            gWaves[i].isActive = false;
        }
    }
}

//===============================================================
//pauseAllSounds()
void core::pauseAllSounds(bool resume) {
    for (int i = 0; i < MAX_SOUNDS; i++) {
        if (gWaves[i].inUse && gWaves[i].isActive) {
            if (i == W_DOOM1 || i == W_SSJ3 || i == W_BIGBLUE_SS || i == W_STAT_BRIEFING) {
            if (resume) {
                alSourcePlay(gWaves[i].source);
            }
            else
                alSourcePause(gWaves[i].source);
            }
        }
    }
}


