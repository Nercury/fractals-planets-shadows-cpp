#pragma once

#include "a_win.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"

#include <SDL2/SDL.h>
//#define NO_SDL_GLEXT
//#include <SDL_opengl.h>

static bool shading_enabled = false;

#ifdef __WIN32__
  #define uglGetProcAddress(x) wglGetProcAddress(x)
  #define WIN32_OR_X11
  void setupExtensions();
#else
# ifdef __APPLE__
	  #include <OpenGL/glu.h>
	  #include <OpenGL/glext.h>
	  void setupExtensions()
	  { shading_enabled = true; }; // OS X already has these extensions
# else
	  #include <GL/glx.h>
	  #include <GL/glxext.h>
	  #define uglGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)(x))
	  #define WIN32_OR_X11
	  void setupExtensions();
# endif
#endif

#ifdef WIN32_OR_X11
	void glGenFramebuffersEXT(GLsizei, GLuint *);
	void glBindFramebufferEXT (GLenum, GLuint);
	void glFramebufferTexture2DEXT (GLenum, GLenum, GLenum, GLuint, GLint);
	GLenum glCheckFramebufferStatusEXT (GLenum);

	void glGetShaderiv(GLuint, GLenum, GLint *);
	void glGetProgramiv(GLuint, GLenum, GLint *);
	void glActiveTextureARB (GLenum);
	void glMultiTexCoord2fARB (GLenum, GLfloat, GLfloat);
	GLhandleARB glCreateProgramObjectARB (void);
	void glDeleteObjectARB (GLhandleARB);
	GLhandleARB glCreateShaderObjectARB(GLenum);
	void glShaderSourceARB (GLhandleARB, GLsizei, const GLcharARB* *, const GLint *);
	void glCompileShaderARB (GLhandleARB);
	void glGetObjectParameterfvARB (GLhandleARB, GLenum, GLfloat *);
	void glGetObjectParameterivARB (GLhandleARB, GLenum, GLint *);
	void glAttachObjectARB (GLhandleARB, GLhandleARB);
	void glGetInfoLogARB (GLhandleARB object, GLsizei maxLenght, GLsizei * length, GLcharARB * infoLog);
	void glLinkProgramARB (GLhandleARB);
	void  glUseProgramObjectARB (GLhandleARB);
	GLint glGetUniformLocationARB (GLhandleARB, const GLcharARB *);
	GLint glGetAttribLocationARB (GLhandleARB, const GLcharARB *);
	void glUniform1fARB (GLint, GLfloat);
	void glUniform2fARB (GLint, GLfloat, GLfloat);
	void glUniform3fARB (GLint, GLfloat, GLfloat, GLfloat);
	void glUniform4fARB (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
	void glUniform1iARB (GLint, GLint);
	void glUniform2iARB (GLint, GLint, GLint);
	void glUniform3iARB (GLint, GLint, GLint, GLint);
	void glUniform4iARB (GLint, GLint, GLint, GLint, GLint);
	void glUniform1fvARB (GLint, GLsizei, const GLfloat *);
	void glUniform2fvARB (GLint, GLsizei, const GLfloat *);
	void glUniform3fvARB (GLint, GLsizei, const GLfloat *);
	void glUniform4fvARB (GLint, GLsizei, const GLfloat *);
	void glUniform1ivARB (GLint, GLsizei, const GLint *);
	void glUniform2ivARB (GLint, GLsizei, const GLint *);
	void glUniform3ivARB (GLint, GLsizei, const GLint *);
	void glUniform4ivARB (GLint, GLsizei, const GLint *);
	void glUniformMatrix2fvARB (GLint, GLsizei, GLboolean, const GLfloat *);
	void glUniformMatrix3fvARB (GLint, GLsizei, GLboolean, const GLfloat *);
	void glUniformMatrix4fvARB (GLint, GLsizei, GLboolean, const GLfloat *);
#endif

#include <string>
#include "b_bind.h"
#include "b_time.h"
#include "L.h"

void wPushMatrix();
void wPopMatrix();
void wScalef(GLfloat a, GLfloat b, GLfloat c);
void wTranslatef(GLfloat x, GLfloat y, GLfloat z);
void wRotatef(GLfloat a, GLfloat x, GLfloat y, GLfloat z);
void wMultMatrixf(const GLfloat *m);

class SDLGL
{
private:
	Uint32 sdl_flags;

	GLint width;
	GLint height;
	bool fullscreen;
	bool is_running;

	std::string title;
	boost::posix_time::ptime last_time;
public:
	SDL_Window *surface;

	SDLGL(std::string title, int width, int height, bool fullscreen);

	boost::function<bool (SDLGL*)> InitFunction;
	boost::function<void (SDLGL*)> ResizeFunction;
	boost::function<void (SDLGL*,boost::posix_time::time_duration)> RenderFunction;
	boost::function<void (SDLGL*)> ExitFunction;
	boost::function<void (SDLGL*,SDL_Event*)> KeyUpFunction;
	boost::function<void (SDLGL*,SDL_Event*)> KeyDownFunction;
	boost::function<void (SDLGL*,SDL_Event*)> MouseUpFunction;
	boost::function<void (SDLGL*,SDL_Event*)> MouseWheelFunction;
	boost::function<void (SDLGL*,SDL_Event*)> MouseDownFunction;
	boost::function<void (SDLGL*,SDL_Event*)> MouseMoveFunction;

	void Run();
	inline void Close() { this->is_running = false; };

	inline GLint GetWidth() { return this->width; };
	inline GLint GetHeight() { return this->height; };

	virtual ~SDLGL(void);
};

Uint32 getpixel(SDL_Surface *surface, int x, int y);

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

inline void GLRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	glTranslatef(x, y, 0);
    glBegin( GL_QUADS );                 // Draw A Quad      
		glVertex2f(  w ,  0); // Top Right Of The Quad 
		glVertex2f(  0,  0 ); // Top Left Of The Quad
		glVertex2f(  0,  h ); // Bottom Left Of The Quad  
		glVertex2f(  w, h ); // Bottom Right Of The Quad 
    glEnd();                            // Done Drawing The Quad  
}
