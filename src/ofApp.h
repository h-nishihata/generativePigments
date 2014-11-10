#pragma once

#include "ofMain.h"
#include "mesh.h"
#define num 1
#define kNumTestNodes 4
#define kNumCameras 2

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int camToView;
    int camToConfigure;
    int lookatIndex[kNumCameras];
    
    ofNode testNodes[kNumTestNodes];
    ofCamera cam[kNumCameras];
    ofLight light;
    
    mesh m[num];
    
};