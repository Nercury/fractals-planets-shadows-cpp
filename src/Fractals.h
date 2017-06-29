#pragma once

#include <math.h>
#include "GameBase.h"

typedef double DoublePoint[2];  
typedef double ElasticItem[4]; 

class Fractals : public GameBase
{
private:
	int depth;

	ElasticItem elastic[30];

	int drift_index;

	void DrawBackground(GLsizei width, GLsizei height);
	void DrawFractals(GLsizei width, GLsizei height);

	void FractalTest1(GLsizei width, GLsizei height, int depth);
	void InitTest1();
	void FractalUzduotis15(GLsizei width, GLsizei height, int depth);

	void ElChange(int start, int max);
	double ElGet(int index);
protected:
	virtual bool OnInitWindow(SDLGL* engine) override ;
	virtual void OnResizeWindow(SDLGL* engine) override ;
	virtual void OnRender(SDLGL* engine, boost::posix_time::time_duration delta) override ;
	virtual void OnExitWindow(SDLGL* engine) override ;
	virtual void OnKeyDown(SDLGL* engine, SDL_Event* ev) override ;
public:
	Fractals(void);
	virtual ~Fractals(void) override ;
};
