#ifndef __mySketch__mesh__
#define __mySketch__mesh__

#include <ofMain.h>
class mesh{
public:
    
    mesh();
    void setup();
    void update();
    void draw(float x, float y, float z);
    
    void setID(int indentify);
    
    int ID;
    
    //    static const int WIDTH = 512;
    //    static const int HEIGHT = 512;
    //    static const int NUM_PARTICLES = WIDTH * HEIGHT;
    
    //    ofVbo myVbo;
    //    ofVec3f myVerts[NUM_PARTICLES];
    //    ofFloatColor myColor[NUM_PARTICLES];
    
    ofImage image;
    ofMesh myMesh;
    
    vector<ofVec3f> points;
    
};
#endif /* defined(__mySketch__mesh__) */
