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

    for(uint i = 0; i < nParticles; ++i) {
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
    texture.allocate(width,height,GL_RGBA8);
    MousePos.allocate(sizeof(int) * 5,NULL,GL_STATIC_DRAW);


    Field.bindBase(GL_SHADER_STORAGE_BUFFER,0);
    FieldTemp.bindBase(GL_SHADER_STORAGE_BUFFER,1);
    ParticleX.bindBase(GL_SHADER_STORAGE_BUFFER,2);
    ParticleY.bindBase(GL_SHADER_STORAGE_BUFFER,3);
    ParticleHeading.bindBase(GL_SHADER_STORAGE_BUFFER,4);
    Settings.bindBase(GL_SHADER_STORAGE_BUFFER,5);
    texture.bindAsImage(6,GL_WRITE_ONLY);
    MousePos.bindBase(GL_SHADER_STORAGE_BUFFER,7);


    particleShader.setupShaderFromFile(GL_COMPUTE_SHADER,"../../src/shaders/particleshader.cs");
    particleShader.linkProgram();  

    interactionShader.setupShaderFromFile(GL_COMPUTE_SHADER,"../../src/shaders/interactionshader.cs");
    interactionShader.linkProgram();

    fieldShader.setupShaderFromFile(GL_COMPUTE_SHADER,"../../src/shaders/fieldshader.cs");
    fieldShader.linkProgram();  
    

    delete[] field;
    delete[] pX;
    delete[] pY;
    delete[] pH;

}

//--------------------------------------------------------------
void ofApp::update(){
    int width = ofGetWidth();
    int height = ofGetHeight(); 

    if(pressed < 60) {
        pressed++;

        MousePos.updateData(sizeof(int)*5,mouse);
        MousePos.bindBase(GL_SHADER_STORAGE_BUFFER,7);

        interactionShader.begin();
        interactionShader.dispatchCompute(width/20,height/20,1);
        interactionShader.end();
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
        mouse[0] = x;
        mouse[1] = y;
        mouse[3] = button;
        pressed = 0;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    mouse[0] = x;
    mouse[1] = y;
    mouse[3] = button;
    pressed = 55;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP) {
        mouse[4] += 10;
        std::cout << "Radius = " << mouse[4] << std::endl;
    }
    else if(key == OF_KEY_DOWN) {
        mouse[4] -= 10;
        std::cout << "Radius = " << mouse[4] << std::endl;
    }
    else if(key == OF_KEY_RIGHT) {
        mouse[2] += 10;
        std::cout << "Amount = " << mouse[2] << std::endl;
    }
    else if(key == OF_KEY_LEFT) {
        mouse[2] -= 10;
        std::cout << "Amount = " << mouse[2] << std::endl;
    }
    
    
    
}


/*


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