#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    int width = ofGetWidth();
    int height = ofGetHeight(); 


    float* field = new float[width*height];
    float* pX = new float[nParticles];
    float* pY = new float[nParticles];
    float* pH = new float[nParticles];


    int amountSettings = 7;
    float settings[amountSettings];
    
    for(int i = 0; i < width*height; ++i)
        field[i] = 0.0f; 

    for(int i = 0; i < nParticles; ++i) {
        pX[i] = rand() % width;
        pY[i] = rand() % height;
        pH[i] = rand() % 360;
    }



    settings[0] = sense_angle;
    settings[1] = sense_distance;
    settings[2] = (float) width;
    settings[3] = (float) height;
    settings[4] = speed;
    settings[5] = diffusion;
    settings[6] = decay;
    

    Field.allocate(width*height*sizeof(float),field,GL_STATIC_DRAW);
    FieldTemp.allocate(width*height*sizeof(float),field,GL_STATIC_DRAW);
    ParticleX.allocate(nParticles*sizeof(float),pX,GL_STATIC_DRAW);
    ParticleY.allocate(nParticles*sizeof(float),pY,GL_STATIC_DRAW);
    ParticleHeading.allocate(nParticles*sizeof(float),pH,GL_STATIC_DRAW);
    Settings.allocate(amountSettings*sizeof(float),settings,GL_STATIC_DRAW);

    Field.bindBase(GL_SHADER_STORAGE_BUFFER,0);
    FieldTemp.bindBase(GL_SHADER_STORAGE_BUFFER,1);
    ParticleX.bindBase(GL_SHADER_STORAGE_BUFFER,2);
    ParticleY.bindBase(GL_SHADER_STORAGE_BUFFER,3);
    ParticleHeading.bindBase(GL_SHADER_STORAGE_BUFFER,4);
    Settings.bindBase(GL_SHADER_STORAGE_BUFFER,5);

    particleShader.setupShaderFromFile(GL_COMPUTE_SHADER,"../../src/shaders/particleshader.cs");
    particleShader.linkProgram();  

    fieldShader.setupShaderFromFile(GL_COMPUTE_SHADER,"../../src/shaders/fieldshader.cs");
    fieldShader.linkProgram();  
    
    texture.allocate(width,height,GL_RGBA8);
    texture.bindAsImage(6,GL_WRITE_ONLY);

    delete[] field;
    delete[] pX;
    delete[] pY;
    delete[] pH;

}

//--------------------------------------------------------------
void ofApp::update(){
    int width = ofGetWidth();
    int height = ofGetHeight(); 

    if(pressed) {

    }

    particleShader.begin();
    particleShader.dispatchCompute(nParticles/1024,1,1);
    particleShader.end();

    fieldShader.begin();
    fieldShader.dispatchCompute(width/20,height/20,1);
    fieldShader.end();

    static int c=1;
    c = 1-c;
    Field.bindBase(GL_SHADER_STORAGE_BUFFER, 0+c);
    FieldTemp.bindBase(GL_SHADER_STORAGE_BUFFER, 0+1-c);

    std::stringstream strm;
	strm << "FPS: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
}



//--------------------------------------------------------------
void ofApp::draw(){
    texture.draw(0,0); 
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(button == 0) {
        mouseX = x;
        mouseY = y;
        pressed = true;
    }

}


/*
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
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
*/