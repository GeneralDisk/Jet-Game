//
//  base.h
//  Jet Game
//
//  Created by Maris Kapualani Kali on 1/18/16.
//  Copyright © 2016 Maris Kapualani Kali. All rights reserved.
//

#ifndef base_h
#define base_h
#include <math.h>
#include <iostream>
//typedefs
typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;
typedef int sword;
typedef unsigned int uint;

//macros
#define size_of(a) (sizeof(a)/sizeof(a[0]))

//structs
struct ivec { int x, y; };
struct vec { float x, y; };
struct box {float x1, x2, y1, y2;
    inline void print(void) {std::cout << "x1: " << x1 << ", x2: " << x2 << ", y1: " << y1 << ", y2: " << y2 << std::endl; }
    box(float ix1, float ix2, float iy1, float iy2) : x1(ix1), x2(ix2), y1(iy1), y2(iy2) {}
    box() : x1(0.f), x2(0.f), y1(0.f), y2(0.f) {}
};

//functions
inline void vprint(vec r) { std::cout << "(" << r.x << "," << r.y << ")\n"; }
inline vec vmake(float x, float y) {vec r2; r2.x = x; r2.y = y; return(r2); }
inline vec vadd(vec v1, vec v2) {return(vmake(v1.x + v2.x, v1.y + v2.y));}
inline vec vsub(vec v1, vec v2) {return(vmake(v1.x - v2.x, v1.y - v2.y));}
inline vec vscale(vec v, float f) {return(vmake((v.x) * f, (v.y) * f));}
inline float vlen2(vec v) {return(v.x * v.x + v.y * v.y);}
inline float vlen(vec v) {return((float)sqrt(vlen2(v)));}
inline float vdot(vec v1, vec v2) {return(v1.x * v2.x + v1.y * v2.y);}
inline vec vunit(float angle) {return(vmake((float)cos(angle), (float)sin(angle)));}
inline vec  vunit (vec v) {return(vscale(v, 1.f/vlen(v))); }
inline void vcollide (vec &v1, vec &v2) {v1.x = (v1.x + v2.x*2)/2; v1.y = (v1.y + v2.y*2)/2; v2.x = (v2.x + v1.x*2)/2; v2.y = (v2.y + v1.y*2)/2;}  //NOTE: This physics model assumes masses are equal
inline float vdistance(vec v1, vec v2) { return(sqrt( (v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y))); }

inline box bmake(float ix1, float ix2, float iy1, float iy2) {box r2(ix1, ix2, iy1, iy2); return(r2); }


inline float randf(float lower_bound, float upper_bound) {
    float diff, rng;
    diff = upper_bound - lower_bound;
    /**
    if (diff == 0) {
        return(upper_bound);
    }**/
    rng = rand() % (int)(diff*10000) + (int)(lower_bound*10000);
    rng = ((float)rng)/10000;
    return(rng);
    
}
inline float randi(int lower_bound, int upper_bound) {int diff; diff = upper_bound - lower_bound + 1; return(rand()%diff + lower_bound); }
inline bool randchance(int percent_chance) { int rng = rand() % 100; return(percent_chance > rng); }



#endif /* base_h */
