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
    ofBackground(0);
    ofEnableDepthTest();
    

    buffer.allocate(1920, 1200, GL_RGBA);
    buffer.begin();
        ofClear(255, 255, 255, 0);
    buffer.end();
    
    
// nodes
    testNodes[0].setOrientation(ofVec3f(0,0,0));
    testNodes[1].setOrientation(ofVec3f(1000,0,1200));
    
    
// cameras
    camToView = 0;
    cam[0].setPosition(300, -40, -800);
    cam[1].setPosition(-100, 200, -500);
    lookatIndex[1] = kNumTestNodes-1;
    
    
//     lights
    light[0].setPosition(50, 100, 50);
    light[1].setPosition(1050, 100, 1250);
    
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
        camPosX -= xAxis;
        if (cam[0].getX() < -1000 || cam[1].getX() < -1000) {
            xFlag = true;
            clearBuffer = true;
            bufferClearTime = 100;
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
        camPosX += xAxis;
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
        camPosY -= yAxis;
        if (cam[0].getY() < -100 || cam[1].getY() < -100) {
            yFlag = true;
            clearBuffer = true;
            bufferClearTime = 10;
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
        camPosY += yAxis;
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
        camPosZ -= zAxis;
        if (cam[0].getZ() < -1000 || cam[1].getZ() < -1000) {
            zFlag = true;
            clearBuffer = true;
            bufferClearTime = 50;
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
        camPosZ += zAxis;
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

    cam[0].setPosition(camPosX, camPosY, camPosZ);
    cam[1].setPosition(camPosX, camPosY, camPosZ);
    
    
// lighting
    if (rFlag == false) {
        r -=0.1;
        if (r <= 0) {
            rFlag = true;
        }
    }else if (rFlag == true) {
        r +=0.1;
        if (r >= 198) {
            rFlag = false;
        }
    }
    
    if (gFlag == false) {
        g -=0.1;
        if (g <= 0) {
            gFlag = true;
        }
    }else if (gFlag == true) {
        g +=0.1;
        if (g >= 95) {
            gFlag = false;
        }
    }
    
    if (bFlag == false) {
        b -=0.1;
        if (b <= 0) {
            bFlag = true;
        }
    }else if (bFlag == true) {
        b +=0.1;
        if (b >= 32) {
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
//        speeds[i]   *= 0.98;
        
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
    
    
    if (clearBuffer == true && bufferClearTime >= 0) {
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

    ofHideCursor();
    ofRotateX(180);

// objects
        v[0].draw(0, 0, 0);
        v[1].draw(1000, 0, 1200);


// particles
    ofSetColor(255);
    particles.setVertexData(&points[0], (int)points.size(), GL_DYNAMIC_DRAW);
    particles.draw(GL_POINTS, 0, (int)points.size());

    cam[camToView].end();

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 255, 255);
    buffer.draw(0,0);
    
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
