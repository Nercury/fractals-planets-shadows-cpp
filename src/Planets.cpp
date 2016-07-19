#include "Planets.h"

#include <sstream>

using namespace std;

GLfloat LightAmbient[]=  { 0.6f, 0.6f, 0.6f, 1.0f };	// Ambient Light Values
GLfloat LightDiffuse[]=	 { 1.1f, 1.1f, 1.1f, 1.0f };	// Diffuse Light Values
GLfloat LightPosition[]= { 0.0f, 0.0f, -8.0f, 1.0f };	// Light Position

Planets::Planets(void)
{
	timeScale = 32768;
	earthDayRotation = 0.0;
	earthYearRotation = 0.7;
	moonRotation = 0.0;
	sunRotation = 0.5;

	binaryMass1 = 80;
	binaryMass2 = 180;
	binaryDistance1 = 1.3;
	binaryDistance2 = 0.8;
	binaryRadius1 = 0.2;
	binaryRadius2 = 0.9;

	binarySystem = false;
	drawAxis = false;

	textures = new TextureManager();
	textures->MapFileTexture(earthTexture, FullPathTo("textures\\earth.jpg"));
	textures->MapFileTexture(sunTexture, FullPathTo("textures\\sun.jpg"));
	textures->MapFileTexture(moonTexture, FullPathTo("textures\\moon.jpg"));
}

Planets::~Planets(void)
{
	delete textures;
	textures = NULL;
}

string tostr(double value)
{
	ostringstream ss;
	ss << value;
	return ss.str();
}

double d_abs(double value)
{
	if (value >=0)
		return value;
	else return -value;
}

bool Planets::OnInitWindow(SDLGL* engine)
{
	if (TTF_Init() < 0)
	{
		l("TTF library initialization failed: ", TTF_GetError(), L_FAILURE);
		return false;
	}

	infotext = new GLST_Text(FullPathTo("fonts\\FreeMonoBold.ttf"), 12, GLST_Top_Left);
	yeartimetext = new GLST_Text(FullPathTo("fonts\\FreeMonoBold.ttf"), 12, GLST_Top_Left);
	daytimetext = new GLST_Text(FullPathTo("fonts\\FreeMonoBold.ttf"), 12, GLST_Top_Left);
	speedtext = new GLST_Text(FullPathTo("fonts\\FreeMonoBold.ttf"), 12, GLST_Top_Left);
	biinfotext = new GLST_Text(FullPathTo("fonts\\FreeMonoBold.ttf"), 12, GLST_Top_Left);
	speedtext->SetText("Speed x " + tostr(timeScale));

	infotext->SetColor(1,1,0);
	infotext->SetText("Use Up/Down to change speed, B to toggle binary system, and X to toggle axis lines for spheres.");

    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	quadratic = gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )

	return true;
}

void Planets::OnResizeWindow(SDLGL* engine)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

	/* Depth buffer setup */
    glClearDepth( 1.0f );

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);			// Position The Light
	glEnable(GL_LIGHT1);							// Enable Light One

	glEnable(GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL );

	glDisable(GL_BLEND);

	textures->WindowResize();
	GLST_Refresh();
}

void Planets::PutUntexturedSphere(GLfloat radius, GLint detail, GLfloat r, GLfloat g, GLfloat b)
{
	glDisable(GL_LIGHTING);
	//axis
	if (drawAxis)
	{
		glColor3f(1,0,0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0,-radius*2,0);	glVertex3f(0,radius*2,0);
		glEnd();
	}
	glEnable(GL_LIGHTING);

	glDisable(GL_TEXTURE_2D);
	glColor3f( r, g, b );

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluSphere(quadratic, radius, detail, detail);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void Planets::PutUnlitSphere(GLuint texture, GLfloat radius, GLint detail, GLfloat r, GLfloat g, GLfloat b)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glDisable(GL_LIGHTING);
	//axis
	if (drawAxis)
	{
		glColor3f(1,0,0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0,-radius*2,0);	glVertex3f(0,radius*2,0);
		glEnd();
	}
	glColor3f( r, g, b );

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluSphere(quadratic, radius, detail, detail);
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
}

void Planets::PutSphere(GLuint texture, GLfloat radius, GLint detail)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	//axis
	if (drawAxis)
	{
		glDisable(GL_LIGHTING);
		glColor3f(1,0,0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0,-radius*2,0);	glVertex3f(0,radius*2,0);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluSphere(quadratic, radius, detail, detail);
	glPopMatrix();
}

double sq(double val)
{
	return val * val;
}

void DrawSatellitePlate()
{
	glBegin(GL_QUAD_STRIP);
	glVertex3f(0.0f, -0.05f, -0.03f);
	glVertex3f(0.0f, -0.05f, 0.03f);
	glVertex3f(0.0f, 0.05f, -0.03f);
	glVertex3f(0.0f, 0.05f, 0.03f);
	glEnd();
}

void Planets::DrawSatellite()
{
	PutUntexturedSphere(0.02f, 16, 1, 1, 1);
    glTranslatef( 0.0, 0.0, -0.06f );
	gluCylinder(quadratic, 0.005, 0.005, 0.12, 5, 5);

	glTranslatef( 0.0, 0.0, -0.03f );

	glPushMatrix();
	glRotatef( 30, 0, 0, 1 );
	DrawSatellitePlate();
	glRotatef( 180, 0, 0, 1 );
	glTranslatef( -0.001f, 0.0, 0.0 );
	DrawSatellitePlate();
	glPopMatrix();

	glTranslatef( 0.0, 0.0, 0.18f );

	glPushMatrix();
	glRotatef( -30.0, 0, 0, 1 );
	DrawSatellitePlate();
	glRotatef( -180, 0, 0, 1 );
	glTranslatef( 0.001f, 0.0, 0.0 );
	DrawSatellitePlate();
	glPopMatrix();
}

void Planets::OnRender(SDLGL* engine, boost::posix_time::time_duration delta)
{
	double PI = 3.1415926535897932384626433;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	textures->SceneStart();
	GLST_SetSceneStart();

	glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective( 60.0f, this->ratio, 1.0f, 800.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

	// Clear the redering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// delta.total_milliseconds() = laikas milisekundemis nuo praejusio kadro
	double hoursPassed = delta.total_milliseconds() * timeScale / 1000.0 / 3600.0;
	double deltaDay = hoursPassed / 24.0;
	double deltaYear = deltaDay / 365.25;
	double deltaMoon = deltaDay / 29.0;
	double deltaSun = deltaDay / 14.0;

	earthDayRotation += deltaDay;
	earthYearRotation += deltaYear;
	moonRotation += deltaMoon;
	sunRotation += deltaSun;

	if (earthDayRotation > 1)
		earthDayRotation -= (int)earthDayRotation;
	if (earthYearRotation > 1)
		earthYearRotation -= (int)earthYearRotation;
	if (moonRotation > 1)
		moonRotation -= (int)moonRotation;
	if (sunRotation > 1)
		sunRotation -= (int)sunRotation;

	ostringstream ss1;
	ss1 << "Day of year: " << earthYearRotation * 365.25;
	yeartimetext->SetText(ss1.str()); // SetText isveda teksta i ekrana
	
	ostringstream ss2;
	double tiksliValanda = earthDayRotation * 24.0;
	int valanda = (int)tiksliValanda;
	double tiksliMinute = (tiksliValanda - valanda) * 60.0;
	int minute = (int)tiksliMinute;
	int sekunde = (int)((tiksliMinute - minute) * 60.0);
	ss2 << "Time of day: " << valanda / 10 << valanda % 10 << ":" << minute / 10 << minute % 10 << ":" << sekunde / 10 << sekunde %10;
	daytimetext->SetText(ss2.str());

	// Clear the current matrix (Modelview)
	glLoadIdentity();

	// Back off eight units to be able to view from the origin.
    glTranslatef ( 0.0, 0.0, -8.0 );

	//glTranslatef( 0.0, 2.0, 0.0 );

	//glRotatef( 15.0, 0.0, 0.0, 1.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );

    glPushMatrix();						// Save matrix state
	if (binarySystem)
	{
		glRotatef( 360.0f * sunRotation, 0, 1, 0);
		double excentricity = 0.2;
		double systemMass = binaryMass1 + binaryMass2;
		double a = binaryDistance1 + binaryDistance2;
		double a1 = binaryMass2 / systemMass * a;
		double a2 = binaryMass1 / systemMass * a;
		double sunRot1 = sunRotation;
		if (sunRot1 > 0.5)
		{
			sunRot1 = -(sunRot1 - 1.0);
		}
		sunRot1 = (sunRot1 / 0.5) * (PI);
		/*double sunRot2 = sunRotation - 0.5;
		if (sunRot2 < 0)
			sunRot2 += 1.0;
		sunRot2 = (sunRot2 / 0.5) */
		double r1 = a1 * (1 - sq(excentricity)) / (1 + excentricity * cos(sunRot1));
		double r2 = a2 * (1 - sq(excentricity)) / (1 + excentricity * cos(sunRot1));
		biinfotext->SetText("Binary rotation: " + tostr(sunRot1));
		glPushMatrix();
		glTranslatef(r1, 0, 0);
		PutUnlitSphere(sunTexture, binaryRadius1, 32, 1.0f, 0.4f, 0.1f);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-r2, 0, 0);
		PutUnlitSphere(sunTexture, binaryRadius2, 32, 1.0f, 1.0f, 0.3f);
		glPopMatrix();
	}
	else
	{
		glRotatef( 360.0*sunRotation, 0, 1, 0);
		biinfotext->SetText("Sun rotation: " + tostr(sunRotation));
		PutUnlitSphere(sunTexture, 1.0, 32, 1.0, 1.0, 0.5);
	}
    glPopMatrix();						// Restore matrix state

    // Draw the Earth
	// First position it around the sun
	//		Use DayOfYear to determine its position
    glRotatef( 360.0 * earthYearRotation, 0.0, 1.0, 0.0 );
    glTranslatef( 4.0, 0.0, 0.0 );

    glPushMatrix();						// Save matrix state
	// Second, rotate the earth on its axis.
	//		Use HourOfDay to determine its rotation.
	glRotatef( 360.0*(1.0 - earthYearRotation), 0,1, 0);
	glRotatef( 23.5, 0, 0, 1);
	glRotatef( 360.0 * earthDayRotation, 0.0, 1.0, 0.0 );
	PutSphere(earthTexture, 0.4f, 32);

	// palydovas
    glTranslatef( 0.6f, 0.0f, 0.0f );
	DrawSatellite();

    glPopMatrix();						// Restore matrix state

	glPushMatrix();
	// Draw the moon.
	//	Use DayOfYear to control its rotation around the earth
	glRotatef( 360.0 * moonRotation, 0.0, 1.0f, 0.0 );
    glTranslatef( 1.3f, 0.0, 0.0 );

	PutSphere(moonTexture, 0.15f, 32);

	glRotatef( 360.0*(1.0 - earthDayRotation), 0, 1, 0);
	//glRotatef( 360.0*(1.0 - sunRotation), 0, 0, 1);
    glTranslatef( 0.3f, 0.0f, 0.0f );
	glScalef(0.5,0.5,0.5);
	DrawSatellite();

	glPopMatrix();

	glRotatef( 360.0*(1.0 - earthDayRotation), 0, 1, 0);
	//glRotatef( 360.0*(1.0 - sunRotation), 0, 0, 1);
    glTranslatef( 0.6f, 0.0f, 0.0f );
	glScalef(0.5,0.5,0.5);
	DrawSatellite();

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	GLint top = 5;
	infotext->Render(5,top);
	top += (GLint)infotext->Height() + 2;
	yeartimetext->Render(5,top);
	top += (GLint)yeartimetext->Height() + 2;
	daytimetext->Render(5,top);
	top += (GLint)daytimetext->Height() + 2;
	speedtext->Render(5,top);
	top += (GLint)speedtext->Height() + 2;
	biinfotext->Render(5,top);
	glDisable(GL_BLEND);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	SDL_GL_SwapBuffers();
}

void Planets::OnExitWindow(SDLGL* engine)
{
	gluDeleteQuadric(quadratic);

	delete infotext;
	delete yeartimetext;
	delete daytimetext;
	delete speedtext;
	delete biinfotext;

	TTF_Quit();
}

void Planets::OnKeyDown(SDLGL* engine, SDL_Event* ev)
{
	switch ( ev->key.keysym.sym )
	{
		case SDLK_ESCAPE:
			if (engine != NULL)
			{
				engine->Close();
			}
			break;
		case SDLK_UP:
			timeScale *= 2.0;			// Double the animation time step
				speedtext->SetText("Speed x " + tostr(timeScale));

			break;
		case SDLK_DOWN:
			timeScale /= 2.0;			// Double the animation time step
				speedtext->SetText("Speed x " + tostr(timeScale));

			break;
		case SDLK_x:
			drawAxis = !drawAxis;
			break;
		case SDLK_b:
			binarySystem = !binarySystem;
			break;
		default:
			break;
	}
}
