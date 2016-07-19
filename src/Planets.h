#pragma once

#include "GameBase.h"
#include "TextureManager.h"
#include "safep.hpp"
#include "glst/GLST_Text.h"

class Planets :
	public GameBase
{
private:
	GLUquadricObj * quadratic;

	TextureManager * textures;

	GLuint earthTexture;
	GLuint sunTexture;
	GLuint moonTexture;

	GLST_Text * infotext;
	GLST_Text * yeartimetext;
	GLST_Text * daytimetext;
	GLST_Text * speedtext;
	GLST_Text * biinfotext;

	bool binarySystem;

	double binaryMass1;
	double binaryMass2;
	double binaryDistance1;
	double binaryDistance2;
	double binaryRadius1;
	double binaryRadius2;

	// laiko mastelis
	double timeScale;

	double earthDayRotation;
	double earthYearRotation;
	double moonRotation;
	double sunRotation;

	bool drawAxis;

	void PutUnlitSphere(GLuint texture, GLfloat radius, GLint detail, GLfloat r, GLfloat g, GLfloat b);
	void PutUntexturedSphere(GLfloat radius, GLint detail, GLfloat r, GLfloat g, GLfloat b);
	void PutSphere(GLuint texture, GLfloat radius, GLint detail);
	void DrawSatellite();
protected:
	virtual bool OnInitWindow(SDLGL* engine);
	virtual void OnResizeWindow(SDLGL* engine);
	virtual void OnRender(SDLGL* engine, boost::posix_time::time_duration delta);
	virtual void OnExitWindow(SDLGL* engine);
	virtual void OnKeyDown(SDLGL* engine, SDL_Event* ev);
public:
	Planets(void);
	virtual ~Planets(void);
};
