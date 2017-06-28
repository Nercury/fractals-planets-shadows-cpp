#include "Fractals.h"

double PI = 3.1415926535897932384626433;

Fractals::Fractals(void)
{
	depth = 1;
	InitTest1();
}

Fractals::~Fractals(void)
{
}

bool Fractals::OnInitWindow(SDLGL* engine)
{
	/* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    //glClearDepth( 1.0f );

	//glEnable(GL_DEPTH_TEST);
    //glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    return true;
}

void Fractals::OnResizeWindow(SDLGL* engine)
{
	glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    //gluPerspective( 45.0f, this->ratio, 0.1f, 800.0f );
	glOrtho(0, width, 0, height, 0, 1);
	//gluOrtho2D( 0, width, 0 , height );				// Select Ortho Mode
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
}


void rotate_and_scale(DoublePoint & value, DoublePoint & rot, DoublePoint & scale)
{
	DoublePoint newCoords;
	newCoords[0] = scale[0] * cos(rot[0]) * value[0] - scale[1] * sin(rot[1]) * value[1];
	newCoords[1] = scale[0] * sin(rot[0]) * value[0] + scale[1] * cos(rot[1]) * value[1];
	value[0] = newCoords[0];
	value[1] = newCoords[1];
}

void translate(DoublePoint & value, DoublePoint amount, double fractal_size)
{
	value[0] += amount[0] * fractal_size;
	value[1] += amount[1] * fractal_size;
}

void DrawInverseFractal(DoublePoint * scalem, DoublePoint * rotm, DoublePoint * transm, int size, GLsizei width, GLsizei height, int depth)
{
	double fractal_size;
	if (width < height)
		fractal_size = (double)(width * 0.95);
	else
		fractal_size = (double)(height * 0.95);
	fractal_size /= 2.0;

	glTranslatef((GLfloat)(width / 2.0 - fractal_size), (GLfloat)(height / 2.0 - fractal_size), 0);

    int j, k;
    DoublePoint p ={60.0,80.4};

    for (k = 0; k < depth; k++)
    {
		j = rand() %size;

		rotate_and_scale(p, rotm[j], scalem[j]);
		translate(p, transm[j], fractal_size);

		glBegin(GL_POINTS);
		   glVertex2f((GLfloat)p[0], (GLfloat)p[1]); 
		glEnd();
	}
}

void Fractals::FractalUzduotis15(GLsizei width, GLsizei height, int depth)
{
	int size = 4;

	/*DoublePoint scalem[3]= // scale
	{
		{-0.5,0.5},
		{0.5,0.5},
		{0.5,0.5}
	};
    DoublePoint rotm[3]= // rotate
	{
		{-PI / 2.0,-PI / 2.0},
		{0,0},
		{0,0},
	};
	DoublePoint transm[3]= // translate
	{
		{0,0},
		{0,1},
		{1,1},
	};*/

	DoublePoint scalem[4]= // scale
	{
		{0.5,0.5},
		{0.25,0.25},
		{0.5,0.5},
		{0.5,0.5},
	};
    DoublePoint rotm[4]= // rotate
	{
		{0,0},
		{0,0},
		{PI / 2.0,PI / 2.0},
		{0,0},
	};
	DoublePoint transm[4]= // translate
	{
		{0,1},
		{1.5,1.5},
		{1,0},
		{1,0},
	};

	DrawInverseFractal(scalem, rotm, transm, size, width, height, depth);
}

void ElAsgn(ElasticItem & item, double a1,double a2,double a3,double a4)
{
	item[0] = a1;
	item[1] = a2;
	item[2] = a3;
	item[3] = a4;
}

void Fractals::ElChange(int start, int max)
{
	if (rand() % 8 == 1)
	{
		drift_index++;
		if (drift_index > max)
			drift_index = 0;
	}

	for (int i = start; i <= max; i++)
	{
		double change = elastic[i][1] /* * ((rand() % 8) / 4.0 * 8.0)*/;
		if (i == drift_index)
		{
			change *= 1.5;
		}

		if (elastic[i][0] + change > elastic[i][3] || elastic[i][0] + change < elastic[i][2])
		{
			elastic[i][1] = -elastic[i][1];
		}
		else
		{
			elastic[i][0] += change;
		}
	}
}

void Fractals::InitTest1()
{
	drift_index = 0;

    // scale

	ElAsgn(elastic[0], 4.0, 0.005, 2.0, 7.8);
	ElAsgn(elastic[1], 8.0, 0.006, 2.0, 9.2);
	ElAsgn(elastic[2], 3.0, 0.009, 2.0, 10.0);
	ElAsgn(elastic[9], 3.0, 0.009, 2.0, 8.0);

    // spin

	ElAsgn(elastic[3], 0.32, 0.00101, 0.3, 0.6);
	ElAsgn(elastic[4], 0.4, 0.0008, 0.3, 0.6);
	ElAsgn(elastic[5], 0.6, 0.00075, 0.3, 0.65);
	ElAsgn(elastic[10], 0.5, 0.00071, 0.3, 0.65);

	// rotation

	ElAsgn(elastic[6], 2.0, 0.005, 1.5, 3.0);
	ElAsgn(elastic[7], 2.3, 0.006, 1.5, 3.0);
	ElAsgn(elastic[8], 2.1, 0.009, 1.5, 3.0);
	ElAsgn(elastic[11], 2.2, 0.007, 1.5, 3.0);

	// position

	ElAsgn(elastic[12], 1.0, 0.0007, 0.7, 1.3);
	ElAsgn(elastic[13], 1.0, 0.0006, 0.7, 1.3);
	ElAsgn(elastic[14], 1.0, 0.0005, 0.7, 1.3);
	ElAsgn(elastic[15], 1.0, 0.0008, 0.7, 1.3);
}

double Fractals::ElGet(int index)
{
	return elastic[index][0];
}

void Fractals::FractalTest1(GLsizei width, GLsizei height, int depth)
{
	ElChange(0, 15);
	
	int size = 4;

	DoublePoint scalem[4]= // scale
	{
		{ElGet(3),ElGet(10)},
		{ElGet(4),ElGet(3)},
		{ElGet(5),ElGet(4)},
		{ElGet(10),ElGet(5)},
	};

    DoublePoint rotm[4]= // rotate
	{
		{PI * ElGet(6) / ElGet(0),PI * ElGet(6) / ElGet(0)},
		{PI * ElGet(7) / ElGet(1) * 2.0,PI * ElGet(7) / ElGet(1) * 2.0},
		{PI * ElGet(8) / ElGet(2) * 3.0,PI * ElGet(8) / ElGet(2) * 3.0},
		{PI * ElGet(11) / ElGet(9) * 3.0,PI * ElGet(11) / ElGet(9) * 3.0},
	};
	DoublePoint transm[4]= // translate
	{
		{ElGet(12),ElGet(12)},
		{ElGet(13),ElGet(13)},
		{ElGet(14),ElGet(14)},
		{ElGet(15),ElGet(15)},
	};

	DrawInverseFractal(scalem, rotm, transm, size, width, height, depth);
}

void Fractals::DrawFractals(GLsizei width, GLsizei height)
{
	//this->FractalTest1(width, height, 7000 * depth);
	this->FractalUzduotis15(width, height, 7000 * depth);
}

void Fractals::DrawBackground(GLsizei width, GLsizei height)
{
    glBegin( GL_QUADS );                 // Draw A Quad      
		glColor3f(   0.1f,  0.1f,  0.3f );
		glVertex2i(  width,  0 ); // Top Right Of The Quad 
		glVertex2i(  0,  0 ); // Top Left Of The Quad

		glColor3f(   0.0f,  0.0f,  0.2f ); 
		glVertex2i(  0,  height ); // Bottom Left Of The Quad  
		glVertex2i(  width, height ); // Bottom Right Of The Quad 
    glEnd();                           // Done Drawing The Quad   
}

void Fractals::OnRender(SDLGL* engine, boost::posix_time::time_duration render_delta)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	this->DrawFractals(width, height);

	/* Draw it to the screen */
	SDL_GL_SwapWindow(engine->surface);
}

void Fractals::OnExitWindow(SDLGL* engine)
{
}

void Fractals::OnKeyDown(SDLGL* engine, SDL_Event* ev)
{
	switch ( ev->key.keysym.sym )
	{
		case SDLK_ESCAPE:
			if (engine != NULL)
			{
				engine->Close();
			}
			break;
		case SDLK_SPACE:
			depth++;
			if (depth > 10)
				depth = 1;
			break;
		default:
			break;
	}
}