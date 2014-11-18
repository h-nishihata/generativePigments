#ifndef __mySketch__mesh__
#define __mySketch__mesh__

#include "ofMain.h"
class mesh{
public:
    
    mesh();
    void setup();
    void update();
    void draw(float x, float y, float z);
    
    void setID(int indentify);
    void reset();
    
    int ID;
    
    static const int WIDTH = 512;
    static const int HEIGHT = 512;
    static const int NUM_PARTICLES = WIDTH * HEIGHT;

    ofImage image;
    
    ofVbo myVbo;
    ofVec3f myVerts[NUM_PARTICLES];
    ofFloatColor myColor[NUM_PARTICLES];
    
    //    ofVboMesh object;
    //    ofVboMesh stroke;
    
    //    vector<ofVec3f> points;
    //    vector<ofColor> colors;
    //    vector<ofVec3f> indices;
        
    //    ofVec3f previous, current;
    
    //    ofColor previousCol;
    //    ofColor currentCol;
    
    //    bool flagX;
    //    bool flagY;
    //    bool flagZ;
    
    //    int waiting;
    
};
#endif /* defined(__mySketch__mesh__) */
