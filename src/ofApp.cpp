#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    camToView = 0;
    camToConfigure = 1;
    
    cam[0].setPosition(40, 40, -500);
    cam[1].setPosition(80, 500, -200);
    lookatIndex[1] = kNumTestNodes-1;
    
    for (int s=0; s<num; s++) {
        m[s].setID(s);
        m[s].setup();
    }
    
    //    testNodes[1].setOrientation(ofVec3f(40,0,30));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int s=0; s<num; s++) {
        m[s].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor(190, 150, 30),  ofColor(220, 178, 80),OF_GRADIENT_LINEAR);
    
    for (int i=0; i<kNumCameras; i++) {
        if (lookatIndex[i] >= 0) {
            cam[i].lookAt(testNodes[lookatIndex[i]]);
        }
    }
    
    
    cam[camToView].begin();
    
    //    ofDrawGrid(500, 10, false, false, true, false);
    
    ofRotateY(ofGetElapsedTimef()*5.0);
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
