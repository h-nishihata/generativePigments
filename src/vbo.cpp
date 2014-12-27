#include "vbo.h"

const int vbo::WIDTH;
const int vbo::HEIGHT;
const int vbo::NUM_PARTICLES;
int vbo::sum;
int x,y;

//--------------------------------------------------------------
void vbo::setID(int identify){
    
    ID = identify;
    sum++;  //  最初　sum = ２
    
}

//--------------------------------------------------------------
void vbo::reset(){
    
    sum++;
    x = y = 0;
    char str[20];
    if (sum <= 6) {
        sprintf(str, "test_%02d.jpg", sum);
        image.loadImage(str);
    }else{
        sum = 2;
        sprintf(str, "test_%02d.jpg", ID);
        image.loadImage(str);
    }

    
    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(1.0);
    
    pixels = image.getPixels();
    int i,j;
    int skip = 1;
    
    for (i=0; i<WIDTH; i+=skip) {
        for (j=0; j<HEIGHT; j+=skip) {
            
            float r = (float)pixels[j * WIDTH*3 + i * 3] / 256.0;
            float invertR = r+(2*(0.5-r));
            
            float g = (float)pixels[j * WIDTH*3 + i * 3+1] / 256.0;
            float invertG = g+(2*(0.5-g));
            
            float b = (float)pixels[j * WIDTH*3 + i * 3+2] / 256.0;
            float invertB = b+(2*(0.5-b));
            
            float brightness = (invertR+invertG+invertB) / 3.0f;
            if (pixels[j * WIDTH*3 + i * 3] < 170 || pixels[j * WIDTH*3 + i * 3+2] > 100) {
                myVerts[j * WIDTH + i] = ofVec3f(i - WIDTH/2, j - HEIGHT/2, brightness * 256.0);
                myColor[j * WIDTH + i] = ofFloatColor(invertR,invertG,invertB, 1.0);
            }
        }
    }
    
    myVbo.setVertexData(myVerts, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    myVbo.setColorData(myColor, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    
}

//--------------------------------------------------------------
void vbo::setup(){

    x = y = 0;
    char str[20];
    sprintf(str, "test_%02d.jpg", ID);
    image.loadImage(str);
    
    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(1.0);
    
    pixels = image.getPixels();
    int i,j;
    int skip = 1;
    
    for (i=0; i<WIDTH; i+=skip) {
        for (j=0; j<HEIGHT; j+=skip) {
            
            float r = (float)pixels[j * WIDTH*3 + i * 3] / 256.0;
            float invertR = r+(2*(0.5-r));
            
            float g = (float)pixels[j * WIDTH*3 + i * 3+1] / 256.0;
            float invertG = g+(2*(0.5-g));
            
            float b = (float)pixels[j * WIDTH*3 + i * 3+2] / 256.0;
            float invertB = b+(2*(0.5-b));
            
            float brightness = (invertR+invertG+invertB) / 3.0f;
            if (pixels[j * WIDTH*3 + i * 3] < 170 || pixels[j * WIDTH*3 + i * 3+2] > 100) {
                myVerts[j * WIDTH + i] = ofVec3f(i - WIDTH/2, j - HEIGHT/2, brightness * 256.0);
                myColor[j * WIDTH + i] = ofFloatColor(invertR,invertG,invertB, 1.0);
            }
        }
    }
    
    myVbo.setVertexData(myVerts, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    myVbo.setColorData(myColor, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    
}

//--------------------------------------------------------------
void vbo::update(){
    
        if (y < HEIGHT) {
            if(x < WIDTH) {
                xAxis = pixels[y*WIDTH*3+x*3]/80;
                yAxis = pixels[y*WIDTH*3+x*3+1]/80;
                zAxis = pixels[y*WIDTH*3+x*3+2]/80;
                x++;
            }else{
                x = 0;
                y++;
            }
        }else{
            y = 0;
        }

    if (timer < 10000) {
        timer++;
    }else{
        timer = 0;
        reset();
//        cout << "reloading images..." << endl;
    }
    
}

//--------------------------------------------------------------
void vbo::draw(float x, float y, float z){
    
    glTranslatef(x, y, z);
    myVbo.draw(GL_POINTS, 0, NUM_PARTICLES);
    
}
