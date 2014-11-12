#include "mesh.h"

//const int mesh::WIDTH;
//const int mesh::HEIGHT;
//const int mesh::NUM_PARTICLES;
int colX, colY;

//--------------------------------------------------------------
mesh::mesh(){
    
}

//--------------------------------------------------------------
void mesh::setID(int identify){
    
    ID = identify;
    
}

//--------------------------------------------------------------
void mesh::setup(){
    
    ofSetFrameRate(60);
    
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
    
    ofColor c = image.getColor(image.width/2, image.height/2);
    current.x = abs(c.r);
    current.y = abs(c.g) * -1.0;
    current.z = abs(c.b) * ID*10.0;
    
    //    cout << "x : " << current.x << endl;
    //    cout << "y : " << current.y << endl;
    //    cout << "z : " << current.z << endl;
}

//--------------------------------------------------------------
void mesh::update(){
    
    previous = current;
    
    if(flagX == false){
        if (current.x <= -500) {
            flagX = true;
        }else{
            if (abs(currentCol.r) < abs(currentCol.g) && abs(currentCol.r) < abs(currentCol.b)) {
                current.x = floor(current.x *= .8);
            }else{
                current.x -= (int)(currentCol.r/10.0);
            }
        }
    }else if(flagX == true){
        if (current.x >= 500) {
            flagX = false;
        }else{
            if (abs(currentCol.r) < abs(currentCol.g) && abs(currentCol.r) < abs(currentCol.b)) {
                current.x = floor(current.x *= .8);
            }else{
                current.x += (int)(currentCol.r/10.0);
            }
        }
    }
    
    
    
    if(flagY == false){
        if (current.y <= -500) {
            flagY = true;
        }else{
            if (abs(currentCol.g) < abs(currentCol.r) && abs(currentCol.g) < abs(currentCol.b)) {
                current.y = floor(current.y *= .8);
            }else{
                current.y -= (int)(currentCol.g/10.0);
            }
        }
    }else if(flagY == true){
        if (current.y >= 500) {
            flagY = false;
        }else{
            if (abs(currentCol.g) < abs(currentCol.r) && abs(currentCol.g) < abs(currentCol.b)) {
                current.y = floor(current.y *= .8);
            }else{
                current.y += (int)(currentCol.g/10.0);
            }
        }
    }
    
    
    
    if(flagZ == false){
        if (current.z <= -500) {
            flagZ = true;
        }else{
            if (abs(currentCol.b) < abs(currentCol.r) && abs(currentCol.b) < abs(currentCol.g)) {
                current.z = floor(current.z *= .95);
            }else{
                current.z -= (int)(currentCol.b);
            }
        }
    }else if(flagZ == true){
        if (current.z >= 500) {
            flagZ = false;
        }else{
            if (abs(currentCol.b) < abs(currentCol.r) && abs(currentCol.b) < abs(currentCol.g)) {
                current.z = floor(current.z *= .95);
            }else{
                current.z += (int)(currentCol.b);
            }
        }
    }
    


    points.push_back(current);
    
    //    while(points.size() > 1000) {
    //        points.pop_front();
    //    }
    
    /*
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
    
    //    cout << current << endl;
    
}

//--------------------------------------------------------------
void mesh::draw(float x, float y, float z){
    
    previousCol = currentCol;
    
    if (colY < image.height) {
        if (colX < image.width) {
            currentCol = image.getColor(colX, colY);
            colX++;
        }else{
            colX = 0;
            colY ++;
        }
    }else{
        colX = colY = 0;
    }
    
    
    if (abs(currentCol.r-previousCol.r) > 10) {
        currentCol.r = (currentCol.r + previousCol.r)/4.0;
    }
    if (abs(currentCol.g-previousCol.g) > 10) {
        currentCol.g = (currentCol.g + previousCol.g)/4.0;
    }
    if (abs(currentCol.b-previousCol.b) > 10) {
        currentCol.b = (currentCol.b + previousCol.b)/4.0;
    }
    
    ofSetColor(currentCol);
    
    ofMesh myMesh_;
    myMesh_.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    myMesh_.clear();
    
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
    
   
    //    ofPushMatrix();
    glTranslatef(x, y, z);
    ofRotateX(180);
    
    //    myVbo.draw(GL_POINTS, 0, NUM_PARTICLES);
    myMesh.draw();
    
    //    ofPopMatrix();
    
}




