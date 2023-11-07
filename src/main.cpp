#include "ofMain.h"
#include "ofApp.h" 
#include <X11/Xlib.h>

//========================================================================
int main(int argc, char** argv){

	int width = 500, height = 500, nParticles = 24000;
	float angle, distance, speed, diff, decay;
	bool fullscreen = false, screensaver = false;

	std::stringstream additionalInfo;

	ofApp *app = new ofApp();


    if(argc == 1) {
        std::cout << "Using default settings: width = 500, height= 500, nParticles = 24000 \nCall with --help for extra information" << std::endl;
    }
    if(argc > 1) {
        for(int i = 1; i < argc; ++i) {
            if(std::string(argv[i]).compare("--help") == 0) {
                std::cout << "\t\t------Slime Mold GPU Simulation------" << std::endl; 
                std::cout << "\t\t  ----Made by Frederick Loeffel----" << std::endl << std::endl;
                std::cout << "usage: ./SlimeMold [option]" << std::endl;
                std::cout << "Options and arguments:" << std::endl;
                std::cout << "-w width\t : width of the window and field in pixel" << std::endl;
                std::cout << "-h height\t : height of the window and field in pixel" << std::endl;
                std::cout << "-n nParticles\t : number of particles in the simulation" << std::endl;
                std::cout << "--sense-distance distance\t : distance of the sense ray" << std::endl;
                std::cout << "--sense-angle angle\t : angle between sense rays" << std::endl;
                std::cout << "--speed speed\t : distance per move of particle (too high and skips pixels)" << std::endl;
                std::cout << "--fullscreen\t : Enables fullscreen mode" << std::endl;
                exit(0);
            }
            if(std::string(argv[i-1]).compare("-w") == 0) {
                width = atoi(argv[i]);
            }
            if(std::string(argv[i-1]).compare("-h") == 0) {
                height = atoi(argv[i]);
            }
            if(std::string(argv[i-1]).compare("-n") == 0) {
                nParticles = atoi(argv[i]);
				app->setNumParticles(nParticles);
            }
			if(std::string(argv[i-1]).compare("--sense-distance") == 0) {
                distance = atof(argv[i]);
				app->setSenseDistance(distance);
				additionalInfo << ", sense-distance = " << distance;
            }
			if(std::string(argv[i-1]).compare("--sense-angle") == 0) {
                angle = atof(argv[i]);
				app->setSenseAngle(angle);
				additionalInfo << ", sense-angle = " << angle;
            }
			if(std::string(argv[i-1]).compare("--speed") == 0) {
                speed = atof(argv[i]);
				app->setSpeed(speed);
				additionalInfo << ", speed = " << speed;
            }
			if(std::string(argv[i-1]).compare("--diffusion") == 0) {
                diff = atof(argv[i]);
				app->setDiffusion(diff);
				additionalInfo << ", diffusion = " << diff;
            }
			if(std::string(argv[i-1]).compare("--decay") == 0) {
                decay = atof(argv[i]);
				app->setDecay(decay);
				additionalInfo << ", decay = " << decay;
            }
			if(std::string(argv[i]).compare("--fullscreen") == 0) {
                fullscreen = true;
				additionalInfo << ", fullscreen = True";
            }
        }
        std::cout << "Using: width = " << width << ", height = " << height << ", nParticles = " << nParticles << additionalInfo.str() << std::endl;
    }

	ofGLFWWindowSettings settings;
	settings.setSize(width,height);
	settings.windowMode = fullscreen ? OF_FULLSCREEN : OF_WINDOW;
	if(!fullscreen && !screensaver)
		settings.resizable = false;
    auto window = ofCreateWindow(settings);

	
	ofRunApp(app);

}
