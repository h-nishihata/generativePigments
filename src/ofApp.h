#pragma once

#include "ofMain.h"
#include "vbo.h"

#include "ofxOsc.h"

#define num 1
#define kNumTestNodes 4
#define kNumCameras 2
#define kNumLights 2

#define HOST "192.168.11.29"
#define PORT 8000

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void drawFboTest();
    
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
    int lookatIndex[kNumCameras];
    
    ofFbo buffer;
    
    ofNode testNodes[kNumTestNodes];
    ofCamera cam[kNumCameras];
    ofLight light[kNumLights];
    
    vbo v[num];
    
    ofVbo particles;
    vector<ofVec3f>points;
    vector<ofVec3f>speeds;
    ofVec3f agent;
    
    ofxOscSender sender;
    
//    float xAxis = ofGetElapsedTimef();
//    float zAxis = ofGetElapsedTimef();
    
};