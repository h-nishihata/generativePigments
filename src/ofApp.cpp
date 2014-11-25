#include "ofApp.h"

//int initX;
//int initY;
bool xFlag, zFlag;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    ofBackground(0);
    ofEnableDepthTest();

    buffer.allocate(1440, 900, GL_RGBA);
    buffer.begin();
        ofClear(255, 255, 255, 0);
    buffer.end();
    
    sender.setup(HOST, PORT);
    
    
    // nodes
    testNodes[0].setOrientation(ofVec3f(30,0,40));
    testNodes[1].setOrientation(ofVec3f(40,0,30));
    
    
    // cameras
    camToView = 0;
    
    cam[0].setPosition(40, -40, -800);
    cam[1].setPosition(0, 700, -500);
    lookatIndex[1] = kNumTestNodes-1;
    
    // lights
    light[0].setPosition(1000, 50, 0);
    light[1].setPosition(0, 500, 0);
    
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
        v[s].setID(s);
        v[s].setup();
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
//    ofVec3f initPos;
    ofEnableAlphaBlending();
    
    ofRotateY(180);
    ofTranslate(-500, -500, 0);
    

//    if (zFlag == false) {
//        if (zAxis < 0.0) {
//            zAxis *= -1;
//            zFlag = true;
//        }
//    }else if (zFlag == true) {
//        if (zAxis > 2.4) {
//            zAxis *= -1;
//            zFlag = false;
//        }
//    }
    
//    cam[0].move(0, 0, zAxis);
//    cout << zAxis << endl;
    
    
//    if (initY < 512) {
//        if (initX < 512) {
//            initPos = v[0].pix;
//            initX++;
//        }else{
//            initX = 0;
//            initY ++;
//        }
//    }else{
//        initX = initY = 0;
//    }
    
//    int temp = 0;
//    if (temp < v[0].NUM_PARTICLES) {
//        initPos = v[0].myVerts[160];
//        temp++;
//    }
    
    
    // particles
    if(points.size() < 500000) {
//        for (int s=0; s<30; s++) {
            points.push_back(ofVec3f(500,500,0));
            speeds.push_back(ofVec3f(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1)));
//        }
    }

    for (unsigned int i=0; i<points.size(); i++) {
        
        speeds[i].y += 0.02;
        points[i]   += speeds[i];
        speeds[i]   *= 0.98;
        
        ofVec3f mouseVec = ofVec3f(ofGetMouseX(),ofGetMouseY(),ofGetMouseX()+ofGetMouseY()) - points[i];
        if(mouseVec.length() < 1000) {
            mouseVec.normalize();
            speeds[i] -= mouseVec;
        }
        
        float t = (2 + ofGetElapsedTimef()) * .1;
        agent.x = ofSignedNoise(t, 0, 0);
        agent.y = ofSignedNoise(0, t, 0);
        agent.z = ofSignedNoise(0, 0, t);
        agent *= 400;

        
//        if(points[i].x > ofGetWidth())    points[i].x = ofRandom(10000);
//        if(points[i].x < 0)               points[i].x = ofRandom(10000);;
//        if(points[i].y > ofGetHeight())   points[i].y = ofRandom(10000);;
//        if(points[i].y < 0)               points[i].y = ofRandom(10000);;
        
    }
    
    buffer.begin();
        drawFboTest();
    buffer.end();
    
}

//--------------------------------------------------------------
void ofApp::drawFboTest(){
    
    ofEnableAlphaBlending();
    if (ofGetKeyPressed('c')) {
        ofClear(255,255,255, 0);
    }
    
    ofTranslate(720, 0);
    
    for (int i=0; i<kNumCameras; i++) {
        if (lookatIndex[i] >= 0) {
            cam[i].lookAt(testNodes[lookatIndex[i]]);
        }
    }
    cam[camToView].begin();
    
            ofHideCursor();
//            ofRotateY(ofGetElapsedTimef());
    
            // objects
            for (int s=0; s<num; s++) {
                v[s].draw(0, 0, s*500);
            }
    
            ofRotateY(180);
            ofTranslate(-500, -500, 0);
    
    
            // particles
            ofSetColor(255);
            particles.setVertexData(&points[0], (int)points.size(), GL_DYNAMIC_DRAW);
            particles.draw(GL_POINTS, 0, (int)points.size());

//            ofSetColor(255);
//            ofCircle(agent,10);
    
    cam[camToView].end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 255, 255);
    buffer.draw(0,0);
    
    if (ofGetKeyPressed()) {
        ofxOscMessage m;
        m.setAddress("/key");
        m.addFloatArg(80);
        sender.sendMessage(m);
    }else{
        ofxOscMessage m;
        m.setAddress("/key");
        m.addFloatArg(0);
        sender.sendMessage(m);
    }
    
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
