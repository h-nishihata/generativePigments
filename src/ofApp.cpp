#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

// cameras
    camToView = 0;
    camToConfigure = 1;
    
    cam[0].setPosition(40, -40, -500);
    cam[1].setPosition(0, 700, -500);
    lookatIndex[1] = kNumTestNodes-1;


// lights
    light[0].setPosition(1000, 50, 0);
    light[1].setPosition(0, 500, 0);
    
    testNodes[0].setOrientation(ofVec3f(30,0,40));
    testNodes[1].setOrientation(ofVec3f(40,0,30));
    
    for (int s=0; s<kNumLights; s++) {
        light[s].enable();
        light[s].setSpotlight();
        light[s].lookAt(testNodes[lookatIndex[s]]);
        
        light[s].setAmbientColor(ofColor(218, 165, 32, 255));
        light[s].setDiffuseColor(ofColor(100, 100, 100));
        light[s].setSpecularColor(ofColor(155, 100, 100));
    }


//  objects
    for (int s=0; s<num; s++) {
        m[s].setID(s);
        m[s].setup();
    }
   
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int s=0; s<num; s++) {
        m[s].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

//    ofBackgroundGradient(ofColor(0, 0, 0),  ofColor(85, 78, 68),OF_GRADIENT_LINEAR);
    ofBackground(0);
    
    
    for (int i=0; i<kNumCameras; i++) {
        if (lookatIndex[i] >= 0) {
            cam[i].lookAt(testNodes[lookatIndex[i]]);
        }
    }
    
    cam[camToView].begin();
    
    //    ofDrawGrid(500, 10, false, false, true, false);
        ofRotateY(ofGetElapsedTimef()*2.0);
    
    for (int s=0; s<num; s++) {
        m[s].draw(0, 0, s*500);
    }
    
    cam[camToView].end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case '0':
            camToView = 0;
            break;
            
        case '1':
            camToView = 1;
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
