#include "ofApp.h"

int xAxis;
int yAxis;
int zAxis;
bool xFlag, yFlag, zFlag;
int timer;

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(24);
    ofSetVerticalSync(true);
    ofBackground(255);
    ofEnableDepthTest();
    

    buffer.allocate(1024, 900, GL_RGBA);
    buffer.begin();
        ofClear(255, 255, 255, 0);
    buffer.end();
    
    
// nodes
    testNodes[0].setOrientation(ofVec3f(0,0,0));
    testNodes[1].setOrientation(ofVec3f(1000,0,1200));
    
    
// cameras
    camToView = 0;
    cam[0].setPosition(posX_00, posY_00, posZ_00);
    cam[1].setPosition(posX_01, posY_01, posZ_01);
    lookatIndex[1] = kNumTestNodes-1;
    
    
//  lights
    light[0].setPosition(0, 50, 0);
    light[1].setPosition(1000, 50, 1200);
    
    for (int s=0; s<kNumLights; s++) {
        light[s].enable();
        light[s].setSpotlight();
        light[s].lookAt(testNodes[lookatIndex[s]]);
        
        light[s].setAmbientColor(ofColor(r, g, b, 255));
        light[s].setDiffuseColor(ofColor(r+13, g+24, b+12));
        light[s].setSpecularColor(ofColor(255, 255, 255));
    }

    
//  objects
    for (int s=0; s<num; s++) {
        v[s].setID(s);
        v[s].setup();
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofEnableAlphaBlending();
    
//  cameras
    if (xFlag == false) {
        posX_00 -= xAxis;
        posX_01 -= xAxis;
        if (cam[0].getX() < -1000 || cam[1].getX() < -1000) {
            xFlag = true;
            switch (camToView) {
                case 0:
                    camToView = 1;
                    break;
                case 1:
                    camToView = 0;
                    break;
            }
        }
    }else if (xFlag == true) {
        posX_00 += xAxis;
        posX_01 += xAxis;
        if (cam[0].getX() > 1000 || cam[1].getX() > 1000) {
            xFlag = false;
            switch (camToView) {
                case 0:
                    camToView = 1;
                    break;
                case 1:
                    camToView = 0;
                    break;
            }
        }
    }


    if (yFlag == false) {
        posY_00 -= yAxis;
        posY_01 -= yAxis;
        if (cam[0].getY() < -100 || cam[1].getY() < -100) {
            yFlag = true;
            switch (camToView) {
                case 0:
                    camToView = 1;
                    break;
                case 1:
                    camToView = 0;
                    break;
            }
        }
    }else if (yFlag == true) {
        posY_00 += yAxis;
        posY_01 += yAxis;
        if (cam[0].getY() > 1000 || cam[1].getY() > 1000) {
            yFlag = false;
            switch (camToView) {
                case 0:
                    camToView = 1;
                    break;
                case 1:
                    camToView = 0;
                    break;
            }
        }
    }
    
    
    if (zFlag == false) {
        posZ_00 -= zAxis;
        posZ_01 -= zAxis;
        if (cam[0].getZ() < -1000 || cam[1].getZ() < -1000) {
            zFlag = true;
            switch (camToView) {
                case 0:
                    camToView = 1;
                    break;
                case 1:
                    camToView = 0;
                    break;
            }
        }
    }else if (zFlag == true) {
        posZ_00 += zAxis;
        posZ_01 += zAxis;
        if (cam[0].getZ() > 1000 || cam[1].getZ() > 1000) {
            zFlag = false;
            switch (camToView) {
                case 0:
                    camToView = 1;
                    break;
                case 1:
                    camToView = 0;
                    break;
            }
        }
    }

    
    if (camToView == 0) {
        if (cam[0].getX() == -100 || cam[0].getX() == 100){
            clearBuffer = true;
            if (clearBuffer) {
                bufferClearTime = 50;
            }
        }

    }else if (camToView == 1) {
        if (cam[1].getX() == -100 || cam[1].getX() == 100){
            clearBuffer = true;
            if (clearBuffer) {
                bufferClearTime = 30;
            }
        }
    }

    cam[0].setPosition(posX_00, posY_00, posZ_00);
    cam[1].setPosition(posX_01, posY_01, posZ_01);
    
    
// lighting
    if (rFlag == false) {
        r -=0.1;
        if (r <= 10) {
            rFlag = true;
        }
    }else if (rFlag == true) {
        if (g > 80 && b < 80) {
            r +=0.1;
        }
        if (r >= 255) {
            rFlag = false;
        }
    }
    
    if (gFlag == false) {
        g -=0.1;
        if (g <= 10) {
            gFlag = true;
        }
    }else if (gFlag == true) {
        g +=0.1;
        if (g >= 255) {
            gFlag = false;
        }
    }
    
    if (bFlag == false) {
        b -=0.1;
        if (b <= 10) {
            bFlag = true;
        }
    }else if (bFlag == true) {
        if (r < 80 && g > 80) {
            b +=0.1;
        }
        if (b >= 190) {
            bFlag = false;
        }
    }
    
    for (int s=0; s<kNumLights; s++) {
        light[s].setAmbientColor(ofColor(r, g, b, 255));
        light[s].setDiffuseColor(ofColor(r+13, g+24, b+12));
        light[s].setSpecularColor(ofColor(255, 255, 255));
    }

    
//  objects
    for (int s=0; s<num; s++) {
        v[s].update();
    }
    
    
// particles
    if(points.size() < 500000) {
            points.push_back(ofVec3f(ofRandom(-2000,2000),ofRandom(-10,200),ofRandom(-2000,2000)));
            speeds.push_back(ofVec3f(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1)));
    }
    
    //    float t = (2 + ofGetElapsedTimef()) * .1;
    //    agent.x = ofSignedNoise(t, 0, 0);
    //    agent.y = ofSignedNoise(0, t, 0);
    //    agent.z = ofSignedNoise(0, 0, t);
    //    agent *= 400;
    
    for (unsigned int i=0; i<points.size(); i++) {
        speeds[i].y += ofRandom(-.04, .04);
        points[i]   += speeds[i];
//      speeds[i]   *= 0.98;
        
//        ofVec3f vec = agent - points[i];
//        if(vec.length() < 1000) {
//            vec.normalize();
//            speeds[i] -= vec*100;
//        }
        
        if(points[i].x > 2000)    points[i].x = -2000;
        if(points[i].x < -2000)   points[i].x = 2000;
        if(points[i].y > 200)     points[i].y = -10;
        if(points[i].y < -10)     points[i].y = 200;
        if(points[i].z > 2000)    points[i].z = -2000;
        if(points[i].z < -2000)   points[i].z = 2000;
    }

    
    buffer.begin();
        drawFboTest();
    buffer.end();
    
}

//--------------------------------------------------------------
void ofApp::drawFboTest(){
    
    ofEnableAlphaBlending();
    
    
    if (clearBuffer == true && bufferClearTime > 0) {
        bufferClearTime--;
        if (bufferClearTime <= 0){
            clearBuffer = false;
        }
    }
    
    
    if (ofGetKeyPressed('c') || clearBuffer == true){
        ofClear(255,255,255,0);
    }
    
    for (int i=0; i<kNumCameras; i++) {
        if (lookatIndex[i] >= 0) {
            cam[i].lookAt(testNodes[lookatIndex[i]]);
        }
    }
    
    
    cam[camToView].begin();
    
    ofRotateX(180);

// objects
        v[0].draw(0, 0, 0);
        v[1].draw(1000, 0, 1200);


// particles
    ofSetColor(255);
    particles.setVertexData(&points[0], (int)points.size(), GL_DYNAMIC_DRAW);
    particles.draw(GL_POINTS, 0, (int)points.size());

    cam[camToView].end();
    
//    ofSetColor(0);
//    ofRect(400, 0, 100, ofGetHeight());
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofHideCursor();
    ofSetColor(255);
    buffer.draw(208,0/*,ofGetWidth(), ofGetHeight()*/);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
