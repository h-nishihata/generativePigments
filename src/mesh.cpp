#include "mesh.h"

//const int mesh::WIDTH;
//const int mesh::HEIGHT;
//const int mesh::NUM_PARTICLES;

//--------------------------------------------------------------
mesh::mesh(){
    
}

//--------------------------------------------------------------
void mesh::setID(int identify){
    
    ID = identify;
    
}

//--------------------------------------------------------------
void mesh::setup(){
    
    char str[20];
    sprintf(str, "test_%02d.png", ID);
    image.loadImage(str);

    //    image.resize(image.getWidth()/5, image.getHeight()/5);
    
    /*
     unsigned char * pixels = image.getPixels();
     int skip = 4;
     
     for (int i=0; i<WIDTH; i+=skip) {
     for (int j=0; j<HEIGHT; j+=skip) {
     
     float r = (float)pixels[j * WIDTH*3 + i * 3] / 256.0;
     float g = (float)pixels[j * WIDTH*3 + i * 3+1] / 256.0;
     float b = (float)pixels[j * WIDTH*3 + i * 3+2] / 256.0;
     float brightness = (r+g+b) / 3.0f;
     //            ofColor cur = img.getColor(i, j);
     //            if (cur.a > 0) {
     
     //                float z = (cur.r + cur.g + cur.b)/3;
     //                float z = ofMap(cur.a, 0, 255, -300, 300);
     //                cur.a = 255;
     
     myVerts[j * WIDTH + i] = ofVec3f(i - WIDTH/2, j - HEIGHT/2, brightness * 256.0);
     myColor[j * WIDTH + i] = ofFloatColor(r,g,b,0.8);
     
     //            }
     
     }
     }
     
     myVbo.setVertexData(myVerts, NUM_PARTICLES, GL_DYNAMIC_DRAW);
     myVbo.setColorData(myColor, NUM_PARTICLES, GL_DYNAMIC_DRAW);
     
     ofEnableDepthTest();
     glEnable(GL_POINT_SMOOTH);
     
     */
    
    ofSetVerticalSync(true);
    myMesh.setMode(OF_PRIMITIVE_LINES);
    
    float intensityThreshold = 100.0;
    int w = image.getWidth();
    int h = image.getHeight();
    
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity <= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(x, y, z);
                myMesh.addVertex(pos);
                myMesh.addColor(c);
                
//                offsets.push_back(ofVec3f(ofRandom(100000),ofRandom(100000),ofRandom(100000)));
            }
        }
    }
    
    float connectionDistance = 20;
    int numVerts = myMesh.getNumVertices();
    int skip = 10;
    for (int a=0; a<numVerts; a+=skip) {
        ofVec3f verta = myMesh.getVertex(a);
        for (int b=a+1; b<numVerts; b+=skip) {
            ofVec3f vertb = myMesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                myMesh.addIndex(a);
                myMesh.addIndex(b);
            }
        }
    }
    
    
    glPointSize(3.0);
    
    //    for (int n=0; n<num; n++) {
    //        for (int m = this[n].ID + 1; m<num; m++) {
    //
    //            float dx = this[m].centx-this[n].centx;
    //            float dy = this[m].centy-this[n].centy;
    //            float d = sqrt(dx*dx + dy*dy);
    //
    //            if (d < this[m].radius + this[n].radius) {
    //                if (d > abs(this[m].radius - this[n].radius)) {
    //                    ofSetLineWidth(2);
    //                    ofSetColor(this[m].r, this[m].g, this[m].b, this[m].a);
    //                    ofSetLineWidth(ofRandom(1,5));
    //                    ofLine(this[m].centx, this[m].centy, this[n].centx, this[n].centy);
    //
    //                }
    //            }
    //
    //        }
    //    }
    
}

//--------------------------------------------------------------
void mesh::update(){
    
    ofVec3f mousePoint(ofGetMouseX(), ofGetMouseY(), ofGetMouseX()+ofGetMouseY());
    points.push_back(mousePoint);
    
    /*
    int numVerts = myMesh.getNumVertices();
    for (int i=0; i<numVerts; i++) {
        ofVec3f vert = myMesh.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = 5.0;
        float displacementScale = 0.75;
        ofVec3f timeOffsets = offsets[i];
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
        myMesh.setVertex(i, vert);
    }
 */
}

//--------------------------------------------------------------
void mesh::draw(float x, float y, float z){

    ofSetColor(255);
    ofMesh myMesh_;
    myMesh_.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for(unsigned int i = 0; i < points.size(); i++){
        
        ofVec3f thisPoint = points[i];
        ofVec3f nextPoint = points[i+1];
        
        ofVec3f direction = (nextPoint - thisPoint);
        
        float distance = direction.length();
        ofVec3f unitDirection = direction.normalized();
        
        ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
        ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
        
        float thickness = ofMap(distance, 0, 60, 20, 2, true);
        
        
        
        ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
        ofVec3f rightPoint = thisPoint+toTheRight*thickness;
        
        myMesh_.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
        myMesh_.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
    }
    
    myMesh_.draw();

    //    easyCam.begin();
    
    //    ofPushMatrix();
    glTranslatef(x, y, z);
    ofRotateX(180);
    
    //    myVbo.draw(GL_POINTS, 0, NUM_PARTICLES);
    
    myMesh.draw();
    
    //    ofPopMatrix();
    //    easyCam.end();

}




