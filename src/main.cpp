#include "a_conf.h"
#include "Fractals.h"
#include "Planets.h"
#include "Trecia.h"
//#include "Example.h"
#include "safep.hpp"

#include "math/Vector.h"

using namespace std;

int main(int argc, char* argv[])
{
	SetAppPath(*argv);

	SDLGL engine("Trecia uzduotis", 800, 500, false);

//	{
//		Fractals game_fractals;
//		game_fractals.Run(engine);
//	}

//	{
//		Planets game_planets;
//		game_planets.Run(engine);
//	}
	
	{
		Trecia trecia_uzduotis;
		trecia_uzduotis.Run(engine);
	}

	std::cout << "Press any key to exit..." << std::endl;

	getchar();

	return 0;
}