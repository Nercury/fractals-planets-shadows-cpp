#include "Example.h"

Example::Example(void) // this is constructor (when class is created)
{
	// initialize any class variables here
	rotation = 0.0;
}

Example::~Example(void) // this is destructor (when class is destroyed)
{
	// delete/destroy any initialized variables
}

/*
New window is created. This is the place to do any OpenGL initialization.
*/
bool Example::OnInitWindow(SDLGL* engine)
{
	/* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	return true; // return true if initialization was successfull
}

/*
Window is resized. This is called first time the window is created, and any
time the window is re-created.

This is good place to do OpenGL initializations which depends on how big window
is. Also, after window is resized, all textures are usually lost, so they need
to be loaded again.
*/
void Example::OnResizeWindow(SDLGL* engine)
{
    glMatrixMode( GL_PROJECTION ); // we want 3D!
    gluPerspective( 60.0f, this->ratio, 1.0f, 800.0f ); // don't worry too much about this function
    glMatrixMode( GL_MODELVIEW ); // and also this
}

/*
This is place to put the code which renders things on screen.
*/
void Example::OnRender(SDLGL* engine, boost::posix_time::time_duration delta)
{
	glLoadIdentity(); // load default coordinates (matrix)

	// Clear the redering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// remember that y axis is upwards by default (but that can be changed)
	// so x is left to right, y is up to down, and z points to us from monitor

	// move things 4 units in z axis (away from us, so that we can see them)
	glTranslatef(0, 0, -4);

	// rotate: angle, x axis, y axis, z axis
	rotation += 5; // increase rotation by 5 degrees
	if (rotation > 360) // if rotation is more than 360 degrees, reduce it by 360 degrees
		rotation -= 360;
	// we put z axis = 1 to indicate that we are rotating around z
	glRotatef(rotation, 0, 0, 1); // use rotation to rotate everything in scene

    glBegin( GL_QUADS ); // Draw A Quad      
		glColor3f(   0.1f,  0.1f,  0.3f ); // set color for first two points
		glVertex2i(  1,  0 ); // Top Right Of The Quad 
		glVertex2i(  0,  0 ); // Top Left Of The Quad

		glColor3f(   0.0f,  0.0f,  0.2f ); // set another color for second two points
		glVertex2i(  0,  1 ); // Bottom Left Of The Quad  
		glVertex2i(  1, 1 ); // Bottom Right Of The Quad 
    glEnd(); // Done Drawing The Quad  

	SDL_GL_SwapWindow(engine->surface); // special thing that need to be done to put results on screen
}

/*
This is called when window is destroyed.
Delete any resources which were initialized in OnInitWindow.
*/
void Example::OnExitWindow(SDLGL* engine)
{

}

/*
This is called when user presses keys.
*/
void Example::OnKeyDown(SDLGL* engine, SDL_Event* ev)
{
	if (ev->key.keysym.sym == SDLK_ESCAPE) // if key is Escape
	{
		engine->Close(); // signal that window needs to be closed
	}
}