//**********************************************************************************
// STEAMiE's Entry Point.
//**********************************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GLViewNewModule.h" //GLView subclass instantiated to drive this simulation
#include <irrKlang.h>
//using namespace irrklang;

/// Saves the in passed params argc and argv in a vector of strings.
std::vector< std::string > saveInputParams( int argc, char** argv );

/**
   This creates a GLView subclass instance and begins the GLView's main loop.
   Each iteration of this loop occurs when a reset request is received. A reset
   request causes the entire GLView to be destroyed (since its exits scope) and
   begin again (simStatus == -1). This loop exits when a request to exit the 
   application is received (simStatus == 0 ).
*/

int main( int argc, char* argv[] )
{
   irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
   std::vector< std::string > args = saveInputParams( argc, argv ); ///< Command line arguments passed via argc and argv, reserved to size of argc
   int simStatus = 0;

   do
   {
      engine->play2D("../mm/sounds/Halo-Theme-Song-Original.mp3", true);
      irrklang::ISound* alarm = engine->play3D("../mm/sounds/star-wars-alarm-sound.mp3", irrklang::vec3df(0,0,0), true, false, true, irrklang::ESM_AUTO_DETECT, true);

      if(alarm) {
	alarm -> setMinDistance(5.0f);
	irrklang::ISoundEffectControl* fx = alarm->getSoundEffectControl();

	if(fx) {
	  fx->enableEchoSoundEffect();
	}
      }
      std::unique_ptr< Aftr::GLViewNewModule > glView( Aftr::GLViewNewModule::New( args ) );
      simStatus = glView->startWorldSimulationLoop(); // Runs until simulation exits or requests a restart (values 0 or -1, respectively)
   }
   while( simStatus != 0 );
   
   engine->drop();
   std::cout << "Exited AfterBurner Engine Normally..." << std::endl;
   return 0;
}

std::vector< std::string > saveInputParams( int argc, char** argv )
{
   std::vector< std::string > args( argc );
   for( int i = 0; i < argc; ++i )
   {
      std::string arg( argv[i] );
      args[i] = arg;
   }
   return args;
}
