#pragma once

#include "ofMain.h"
#include "ofConstants.h"




class ofApp : public ofBaseApp{
	private:
		float sense_angle = 20.0f;
		float sense_distance = 20.0f;
		uint nParticles = 24000;
		float speed = 0.5f;
		float diffusion = (1.0f/9.0f);
		float decay = 0.85f;
		int pressed = 60;
		int mouse[5];

		ofBufferObject Field, FieldTemp, ParticleX, ParticleY, ParticleHeading, Settings, MousePos;
		ofTexture texture;
 		ofShader particleShader, fieldShader, interactionShader;

	public:
		void setNumParticles(uint num) {
			nParticles = num;
		}
		void setSenseAngle(float angle) {
			if(angle >= 360)
				angle -= 360;
			if(angle < 0)
				angle += 360;
			sense_angle = angle;
		}

		void setSenseDistance(float distance) {
			sense_distance = distance;
		}

		void setSpeed(float speed_) {
			speed = speed_;
		} 

		void setDiffusion(float diff) {
			diffusion = diff;
		}

		void setDecay(float dec) {
			decay = dec;
		}

		void setup();
		void update();
		void draw();


		void mousePressed(int x, int y, int button);

		void keyPressed(int key);

		/*
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		*/
		
};
