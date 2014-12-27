#ifndef _OF_VBO_
#define _OF_VBO_

#include "ofMain.h"

extern int xAxis;
extern int yAxis;
extern int zAxis;
extern int timer;

class vbo{
public:

    void setup();
    void update();
    void draw(float x, float y, float z);
    
    void setID(int indentify);
    void reset();
    
    int ID;
    static int sum;
    
    static const int WIDTH = 512;
    static const int HEIGHT = 512;
    static const int NUM_PARTICLES = WIDTH * HEIGHT;

    unsigned char * pixels;
    
    ofImage image;
    
    ofVbo myVbo;
    ofVec3f myVerts[NUM_PARTICLES];
    ofFloatColor myColor[NUM_PARTICLES];
    
};
#endif
