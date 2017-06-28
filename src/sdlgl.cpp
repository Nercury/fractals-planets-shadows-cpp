#include "sdlgl.h"

using namespace std;

#ifdef WIN32_OR_X11
  /* gl extensions */
	PFNGLGENFRAMEBUFFERSEXTPROC oglGenFramebuffersEXT;
	PFNGLBINDFRAMEBUFFEREXTPROC oglBindFramebufferEXT;
	PFNGLFRAMEBUFFERTEXTURE2DEXTPROC oglFramebufferTexture2DEXT;
	PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC oglCheckFramebufferStatusEXT;

  /* Shading language prototypes. */
  PFNGLGETSHADERIVPROC oglGetShaderiv;
  PFNGLGETPROGRAMIVPROC oglGetProgramiv;
  PFNGLACTIVETEXTUREARBPROC           oglActiveTextureARB;
  PFNGLMULTITEXCOORD2FARBPROC         oglMultiTexCoord2fARB;
  PFNGLCREATEPROGRAMOBJECTARBPROC     oglCreateProgramObjectARB;
  PFNGLDELETEOBJECTARBPROC            oglDeleteObjectARB;
  PFNGLCREATESHADEROBJECTARBPROC      oglCreateShaderObjectARB;
  PFNGLSHADERSOURCEARBPROC            oglShaderSourceARB;
  PFNGLCOMPILESHADERARBPROC           oglCompileShaderARB;
  PFNGLGETOBJECTPARAMETERFVARBPROC    oglGetObjectParameterfvARB;
  PFNGLGETOBJECTPARAMETERIVARBPROC    oglGetObjectParameterivARB;
  PFNGLATTACHOBJECTARBPROC            oglAttachObjectARB;
  PFNGLGETINFOLOGARBPROC              oglGetInfoLogARB;
  PFNGLLINKPROGRAMARBPROC             oglLinkProgramARB;
  PFNGLUSEPROGRAMOBJECTARBPROC        oglUseProgramObjectARB;
  PFNGLGETUNIFORMLOCATIONARBPROC      oglGetUniformLocationARB;
  PFNGLGETATTRIBLOCATIONARBPROC       oglGetAttribLocationARB;
  PFNGLUNIFORM1FARBPROC oglUniform1fARB;
  PFNGLUNIFORM2FARBPROC oglUniform2fARB;
  PFNGLUNIFORM3FARBPROC oglUniform3fARB;
  PFNGLUNIFORM4FARBPROC oglUniform4fARB;
  PFNGLUNIFORM1IARBPROC	oglUniform1iARB;
  PFNGLUNIFORM2IARBPROC	oglUniform2iARB;
  PFNGLUNIFORM3IARBPROC	oglUniform3iARB;
  PFNGLUNIFORM4IARBPROC	oglUniform4iARB;
  PFNGLUNIFORM1FVARBPROC oglUniform1fvARB;
  PFNGLUNIFORM2FVARBPROC oglUniform2fvARB;
  PFNGLUNIFORM3FVARBPROC oglUniform3fvARB;
  PFNGLUNIFORM4FVARBPROC oglUniform4fvARB;
  PFNGLUNIFORM1IVARBPROC oglUniform1ivARB;
  PFNGLUNIFORM2IVARBPROC oglUniform2ivARB;
  PFNGLUNIFORM3IVARBPROC oglUniform3ivARB;
  PFNGLUNIFORM4IVARBPROC oglUniform4ivARB;
  PFNGLUNIFORMMATRIX2FVARBPROC oglUniformMatrix2fvARB;
  PFNGLUNIFORMMATRIX3FVARBPROC oglUniformMatrix3fvARB;
  PFNGLUNIFORMMATRIX4FVARBPROC oglUniformMatrix4fvARB;

/* framebuffer extensions */

void glGenFramebuffersEXT(GLsizei n, GLuint *framebuffers)
{
	if (oglGenFramebuffersEXT != NULL)
		(*oglGenFramebuffersEXT)(n, framebuffers);
}

void glBindFramebufferEXT (GLenum target, GLuint framebuffer)
{
	if (oglBindFramebufferEXT != NULL)
		(*oglBindFramebufferEXT)(target, framebuffer);
}

void glFramebufferTexture2DEXT (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	if (oglFramebufferTexture2DEXT != NULL)
		(*oglFramebufferTexture2DEXT)(target, attachment, textarget, texture, level);
}

GLenum glCheckFramebufferStatusEXT (GLenum target)
{
	if (oglCheckFramebufferStatusEXT != NULL)
		return (*oglCheckFramebufferStatusEXT)(target);
	else
		return GL_FRAMEBUFFER_UNSUPPORTED_EXT;
}

/* shader extensions */

void glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
{
	(*oglGetShaderiv)(shader, pname, params);
}

void glGetProgramiv(GLuint shader, GLenum pname, GLint *params)
{
	(*oglGetProgramiv)(shader, pname, params);
}

void glActiveTextureARB (GLenum value)
{
	(*oglActiveTextureARB)(value);
}

void glMultiTexCoord2fARB (GLenum value, GLfloat a, GLfloat b)
{
	(*oglMultiTexCoord2fARB)(value, a, b);
}

GLhandleARB glCreateProgramObjectARB ()
{
	return (*oglCreateProgramObjectARB)();
}

void glDeleteObjectARB (GLhandleARB value)
{
	(*oglDeleteObjectARB)(value);
}

GLhandleARB glCreateShaderObjectARB(GLenum value)
{
	return (*oglCreateShaderObjectARB)(value);
}

void glShaderSourceARB (GLhandleARB handle, GLsizei size, const GLcharARB* * src, const GLint * length)
{
	(*oglShaderSourceARB)(handle, size, src, length);
}

void glCompileShaderARB (GLhandleARB handle)
{
	(*oglCompileShaderARB)(handle);
}

void glGetObjectParameterfvARB (GLhandleARB handle, GLenum value, GLfloat * a)
{
	(*oglGetObjectParameterfvARB)(handle, value, a);
}

void glGetObjectParameterivARB (GLhandleARB handle, GLenum value, GLint * a)
{
	(*oglGetObjectParameterivARB)(handle, value, a);
}

void glAttachObjectARB (GLhandleARB handle, GLhandleARB handle2)
{
	(*oglAttachObjectARB)(handle, handle2);
}

void glGetInfoLogARB (GLhandleARB object, GLsizei maxLenght, GLsizei * length, GLcharARB * infoLog)
{
	(*oglGetInfoLogARB)(object, maxLenght, length, infoLog);
}

void glLinkProgramARB (GLhandleARB handle)
{
	(*oglLinkProgramARB)(handle);
}

void  glUseProgramObjectARB (GLhandleARB handle)
{
	(*oglUseProgramObjectARB)(handle);
}

GLint glGetUniformLocationARB (GLhandleARB handle, const GLcharARB * value)
{
	return (*oglGetUniformLocationARB)(handle, value);
}

GLint glGetAttribLocationARB (GLhandleARB handle, const GLcharARB * value)
{
	return (*oglGetAttribLocationARB)(handle, value);
}

void glUniform1fARB (GLint location, GLfloat v0)
{
	return (*oglUniform1fARB)(location, v0);
}

void glUniform2fARB (GLint location, GLfloat v0, GLfloat v1)
{
	return (*oglUniform2fARB)(location,v0,v1);
}

void glUniform3fARB (GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	return (*oglUniform3fARB)(location,v0,v1,v2);
}

void glUniform4fARB (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	return (*oglUniform4fARB)(location,v0,v1,v2,v3);
}

void glUniform1iARB (GLint location, GLint v0)
{
	return (*oglUniform1iARB)(location, v0);
}

void glUniform2iARB (GLint location, GLint v0, GLint v1)
{
	return (*oglUniform2iARB)(location, v0, v1);
}

void glUniform3iARB (GLint location, GLint v0, GLint v1, GLint v2)
{
	return (*oglUniform3iARB)(location, v0, v1, v2);
}

void glUniform4iARB (GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	return (*oglUniform4iARB)(location, v0, v1, v2, v3);
}

void glUniform1fvARB (GLint location, GLsizei count, const GLfloat *value)
{
	return (*oglUniform1fvARB)(location, count, value);
}

void glUniform2fvARB (GLint location, GLsizei count, const GLfloat *value)
{
	return (*oglUniform2fvARB)(location, count, value);
}

void glUniform3fvARB (GLint location, GLsizei count, const GLfloat *value)
{
	return (*oglUniform3fvARB)(location, count, value);
}

void glUniform4fvARB (GLint location, GLsizei count, const GLfloat *value)
{
	return (*oglUniform4fvARB)(location, count, value);
}

void glUniform1ivARB (GLint location, GLsizei count, const GLint *value)
{
	return (*oglUniform1ivARB)(location, count, value);
}

void glUniform2ivARB (GLint location, GLsizei count, const GLint *value)
{
	return (*oglUniform2ivARB)(location, count, value);
}

void glUniform3ivARB (GLint location, GLsizei count, const GLint *value)
{
	return (*oglUniform3ivARB)(location, count, value);
}

void glUniform4ivARB (GLint location, GLsizei count, const GLint *value)
{
	return (*oglUniform4ivARB)(location, count, value);
}

void glUniformMatrix2fvARB (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	return (*oglUniformMatrix2fvARB)(location, count, transpose, value);
}

void glUniformMatrix3fvARB (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	return (*oglUniformMatrix3fvARB)(location, count, transpose, value);
}

void glUniformMatrix4fvARB (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	return (*oglUniformMatrix4fvARB)(location, count, transpose, value);
}


#endif

int fromTexture = 2;
int toTexture = 7;

void wPushMatrix()
{
	glMatrixMode(GL_TEXTURE);
	for (int i = fromTexture; i <= toTexture; i++)
	{
		glActiveTextureARB(GL_TEXTURE0 + i);
		glPushMatrix();
	}
	glActiveTextureARB(GL_TEXTURE0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}

void wPopMatrix()
{
	glMatrixMode(GL_TEXTURE);
	for (int i = fromTexture; i <= toTexture; i++)
	{
		glActiveTextureARB(GL_TEXTURE0 + i);
		glPopMatrix();
	}
	glActiveTextureARB(GL_TEXTURE0);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void wTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_TEXTURE);
	for (int i = fromTexture; i <= toTexture; i++)
	{
		glActiveTextureARB(GL_TEXTURE0 + i);
		glTranslatef(x, y, z);
	}
	glActiveTextureARB(GL_TEXTURE0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(x, y, z);
}

void wRotatef(GLfloat a, GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_TEXTURE);
	for (int i = fromTexture; i <= toTexture; i++)
	{
		glActiveTextureARB(GL_TEXTURE0 + i);
		glRotatef(a, x, y, z);
	}
	glActiveTextureARB(GL_TEXTURE0);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(a, x, y, z);
}

void wScalef(GLfloat a, GLfloat b, GLfloat c)
{
	glMatrixMode(GL_TEXTURE);
	for (int i = fromTexture; i <= toTexture; i++)
	{
		glActiveTextureARB(GL_TEXTURE0 + i);
		glScalef(a, b, c);
	}
	glActiveTextureARB(GL_TEXTURE0);
	glMatrixMode(GL_MODELVIEW);
	glScalef(a, b, c);
}

void wMultMatrixf(const GLfloat *m)
{
	glMatrixMode(GL_TEXTURE);
	for (int i = fromTexture; i <= toTexture; i++)
	{
		glActiveTextureARB(GL_TEXTURE0 + i);
		glMultMatrixf(m);
	}
	glActiveTextureARB(GL_TEXTURE0);
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(m);
}

#ifdef WIN32_OR_X11

#include <cstring>

static bool findString(char* in, char* list)
{
  int thisLength = strlen(in);
  while (*list != 0)
  {
    int length = strcspn(list," ");

    if( thisLength == length )
      if (!strncmp(in,list,length))
        return true;

    list += length + 1;
  }
  return false;
}

void setupExtensions()
{
	char * glversionstr = (char*)glGetString(GL_VERSION);
	if (glversionstr != NULL)
	{
		cout << "OpenGL " << glversionstr << endl;
	}
	else
	{
		cout << "Invalid rendering context" << endl;
		shading_enabled = false;
		return;
	}
  char* extensionList = (char*)glGetString(GL_EXTENSIONS);

  bool hasAbrObj = findString("GL_ARB_shader_objects",extensionList);
  if (hasAbrObj)
	  cout << "Shader Objects avalable." << endl;
  else
  	cout << "Shader Objects UNSUPPORTED." << endl;
  bool hasSL = findString("GL_ARB_shading_language_100",extensionList);
  if (hasSL)
	  cout << "Shading Language compiler available." << endl;
  else
  	cout << "Shading Language compiler IS NOT AVAILABLE, sorry." << endl;
  bool hasVS = findString("GL_ARB_vertex_shader",extensionList);
  if (hasVS)
	  cout << "Vertex Shader available." << endl;
  else
  	cout << "Vertex Shader IS UNSUPPORTED." << endl;
  bool hasPS = findString("GL_ARB_fragment_shader",extensionList);
  if (hasPS)
	  cout << "Pixel Shader available." << endl;
  else
  	cout << "Pixel Shader IS UNSUPPORTED." << endl;

  	oglGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)
	  uglGetProcAddress("glGenFramebuffersEXT");
  	oglBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)
	  uglGetProcAddress("glBindFramebufferEXT");
	oglFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)
	  uglGetProcAddress("glFramebufferTexture2DEXT");
	oglCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)
	  uglGetProcAddress("glCheckFramebufferStatusEXT");

if (false
	|| oglGenFramebuffersEXT == NULL
	|| oglBindFramebufferEXT == NULL
	|| oglFramebufferTexture2DEXT == NULL
	|| oglCheckFramebufferStatusEXT == NULL)
	cout << "Warning! Framebuffer extensions not available. No shadows, sorry :(" << endl;

  if( hasAbrObj && hasSL && hasVS && hasPS )
  {
 	oglGetShaderiv = (PFNGLGETSHADERIVPROC)
	  uglGetProcAddress("glGetShaderiv");
	if (oglGetShaderiv == NULL)
		cout << "UNAVAILABLE: glGetShaderiv" << endl;
 	oglGetProgramiv = (PFNGLGETPROGRAMIVPROC)
	  uglGetProcAddress("glGetProgramiv");
	if (oglGetProgramiv == NULL)
		cout << "UNAVAILABLE: glGetProgramiv" << endl;
	oglActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)
      uglGetProcAddress("glActiveTextureARB");
	if (oglActiveTextureARB == NULL)
		cout << "UNAVAILABLE: glActiveTextureARB" << endl;
    oglMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)
      uglGetProcAddress("glMultiTexCoord2fARB");
	if (oglMultiTexCoord2fARB == NULL)
		cout << "UNAVAILABLE: glMultiTexCoord2fARB" << endl;
    oglCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)
      uglGetProcAddress("glCreateProgramObjectARB");
	if (oglCreateProgramObjectARB == NULL)
		cout << "UNAVAILABLE: glCreateProgramObjectARB" << endl;
    oglDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)
      uglGetProcAddress("glDeleteObjectARB");
	if (oglDeleteObjectARB == NULL)
		cout << "UNAVAILABLE: glDeleteObjectARB" << endl;
    oglCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)
     uglGetProcAddress("glCreateShaderObjectARB");
	if (oglCreateShaderObjectARB == NULL)
		cout << "UNAVAILABLE: glCreateShaderObjectARB" << endl;
    oglShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)
      uglGetProcAddress("glShaderSourceARB");
	if (oglShaderSourceARB == NULL)
		cout << "UNAVAILABLE: glShaderSourceARB" << endl;
    oglCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)
      uglGetProcAddress("glCompileShaderARB");
	if (oglCompileShaderARB == NULL)
		cout << "UNAVAILABLE: glCompileShaderARB" << endl;
    oglGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC)
      uglGetProcAddress("glGetObjectParameterfvARB");
	if (oglGetObjectParameterfvARB == NULL)
		cout << "UNAVAILABLE: glGetObjectParameterfvARB" << endl;
    oglGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)
      uglGetProcAddress("glGetObjectParameterivARB");
	if (oglGetObjectParameterivARB == NULL)
		cout << "UNAVAILABLE: glGetObjectParameterivARB" << endl;
    oglAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)
      uglGetProcAddress("glAttachObjectARB");
	if (oglAttachObjectARB == NULL)
		cout << "UNAVAILABLE: glAttachObjectARB" << endl;
    oglGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)
      uglGetProcAddress("glGetInfoLogARB");
	if (oglGetInfoLogARB == NULL)
		cout << "UNAVAILABLE: glGetInfoLogARB" << endl;
    oglLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)
      uglGetProcAddress("glLinkProgramARB");
	if (oglLinkProgramARB == NULL)
		cout << "UNAVAILABLE: glLinkProgramARB" << endl;
    oglUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)
      uglGetProcAddress("glUseProgramObjectARB");
	if (oglUseProgramObjectARB == NULL)
		cout << "UNAVAILABLE: glUseProgramObjectARB" << endl;
    oglGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)
      uglGetProcAddress("glGetUniformLocationARB");
	if (oglGetUniformLocationARB == NULL)
		cout << "UNAVAILABLE: glGetUniformLocationARB" << endl;
    oglGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC)
      uglGetProcAddress("glGetAttribLocationARB");
	if (oglGetAttribLocationARB == NULL)
		cout << "UNAVAILABLE: glGetAttribLocationARB" << endl;

    oglUniform1fARB = (PFNGLUNIFORM1FARBPROC)
      uglGetProcAddress("glUniform1fARB");
	if (oglUniform1fARB == NULL)
		cout << "UNAVAILABLE: glUniform1fARB" << endl;
    oglUniform2fARB = (PFNGLUNIFORM2FARBPROC)
      uglGetProcAddress("glUniform2fARB");
	if (oglUniform2fARB == NULL)
		cout << "UNAVAILABLE: glUniform2fARB" << endl;
	oglUniform3fARB = (PFNGLUNIFORM3FARBPROC)
      uglGetProcAddress("glUniform3fARB");
	if (oglUniform3fARB == NULL)
		cout << "UNAVAILABLE: glUniform3fARB" << endl;
	oglUniform4fARB = (PFNGLUNIFORM4FARBPROC)
      uglGetProcAddress("glUniform4fARB");
	if (oglUniform4fARB == NULL)
		cout << "UNAVAILABLE: glUniform4fARB" << endl;
	oglUniform1iARB = (PFNGLUNIFORM1IARBPROC)
      uglGetProcAddress("glUniform1iARB");
	if (oglUniform1iARB == NULL)
		cout << "UNAVAILABLE: glUniform1iARB" << endl;
	oglUniform2iARB = (PFNGLUNIFORM2IARBPROC)
      uglGetProcAddress("glUniform2iARB");
	if (oglUniform2iARB == NULL)
		cout << "UNAVAILABLE: glUniform2iARB" << endl;
	oglUniform3iARB = (PFNGLUNIFORM3IARBPROC)
      uglGetProcAddress("glUniform3iARB");
	if (oglUniform3iARB == NULL)
		cout << "UNAVAILABLE: glUniform3iARB" << endl;
	oglUniform4iARB = (PFNGLUNIFORM4IARBPROC)
      uglGetProcAddress("glUniform4iARB");
	if (oglUniform4iARB == NULL)
		cout << "UNAVAILABLE: glUniform4iARB" << endl;
	oglUniform1fvARB = (PFNGLUNIFORM1FVARBPROC)
      uglGetProcAddress("glUniform1fvARB");
	if (oglUniform1fvARB == NULL)
		cout << "UNAVAILABLE: glUniform1fvARB" << endl;
	oglUniform2fvARB = (PFNGLUNIFORM2FVARBPROC)
      uglGetProcAddress("glUniform2fvARB");
	if (oglUniform2fvARB == NULL)
		cout << "UNAVAILABLE: glUniform2fvARB" << endl;
	oglUniform3fvARB = (PFNGLUNIFORM3FVARBPROC)
      uglGetProcAddress("glUniform3fvARB");
	if (oglUniform3fvARB == NULL)
		cout << "UNAVAILABLE: glUniform3fvARB" << endl;
	oglUniform4fvARB = (PFNGLUNIFORM4FVARBPROC)
      uglGetProcAddress("glUniform4fvARB");
	if (oglUniform4fvARB == NULL)
		cout << "UNAVAILABLE: glUniform4fvARB" << endl;
	oglUniform1ivARB = (PFNGLUNIFORM1IVARBPROC)
      uglGetProcAddress("glUniform1ivARB");
	if (oglUniform1ivARB == NULL)
		cout << "UNAVAILABLE: glUniform1ivARB" << endl;
	oglUniform2ivARB = (PFNGLUNIFORM2IVARBPROC)
      uglGetProcAddress("glUniform2ivARB");
	if (oglUniform2ivARB == NULL)
		cout << "UNAVAILABLE: glUniform2ivARB" << endl;
	oglUniform3ivARB = (PFNGLUNIFORM3IVARBPROC)
      uglGetProcAddress("glUniform3ivARB");
	if (oglUniform3ivARB == NULL)
		cout << "UNAVAILABLE: glUniform3ivARB" << endl;
	oglUniform4ivARB = (PFNGLUNIFORM4IVARBPROC)
      uglGetProcAddress("glUniform4ivARB");
	if (oglUniform4ivARB == NULL)
		cout << "UNAVAILABLE: glUniform4ivARB" << endl;
	oglUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC)
      uglGetProcAddress("glUniformMatrix2fvARB");
	if (oglUniformMatrix2fvARB == NULL)
		cout << "UNAVAILABLE: glUniformMatrix2fvARB" << endl;
	oglUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC)
      uglGetProcAddress("glUniformMatrix3fvARB");
	if (oglUniformMatrix3fvARB == NULL)
		cout << "UNAVAILABLE: glUniformMatrix3fvARB" << endl;
	oglUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC)
      uglGetProcAddress("glUniformMatrix4fvARB");
	if (oglUniformMatrix4fvARB == NULL)
		cout << "UNAVAILABLE: glUniformMatrix4fvARB" << endl;

    if( false
     || oglGetShaderiv == NULL
     || oglGetProgramiv == NULL
     || oglActiveTextureARB == NULL
     || oglMultiTexCoord2fARB == NULL
     || oglCreateProgramObjectARB == NULL
     || oglDeleteObjectARB == NULL
     || oglCreateShaderObjectARB == NULL
     || oglShaderSourceARB == NULL
     || oglCompileShaderARB == NULL
     || oglGetObjectParameterfvARB == NULL
     || oglGetObjectParameterivARB == NULL
     || oglAttachObjectARB == NULL
     || oglGetInfoLogARB == NULL
     || oglLinkProgramARB == NULL
     || oglUseProgramObjectARB == NULL
     || oglGetUniformLocationARB == NULL
     || oglGetAttribLocationARB == NULL
     || oglUniform1fARB == NULL
     || oglUniform2fARB == NULL
     || oglUniform3fARB == NULL
     || oglUniform4fARB == NULL
     || oglUniform1iARB == NULL
     || oglUniform2iARB == NULL
     || oglUniform3iARB == NULL
     || oglUniform4iARB == NULL
     || oglUniform1fvARB == NULL
     || oglUniform2fvARB == NULL
     || oglUniform3fvARB == NULL
     || oglUniform4fvARB == NULL
     || oglUniform1ivARB == NULL
     || oglUniform2ivARB == NULL
     || oglUniform3ivARB == NULL
     || oglUniform4ivARB == NULL
     || oglUniformMatrix2fvARB == NULL
     || oglUniformMatrix3fvARB == NULL
     || oglUniformMatrix4fvARB == NULL
      )
      shading_enabled = false;
    else shading_enabled = true;
  } else
    shading_enabled = false;
}

#endif

#define SCREEN_BPP 16

SDLGL::SDLGL(std::string title, GLint width, GLint height, bool fullscreen)
{
	this->width = width;
	this->height = height;
	this->fullscreen = fullscreen;
	this->title = title;
}

SDLGL::~SDLGL(void)
{
}

int sdl_instances = 0;

bool SDLInit()
{
	if (sdl_instances == 0)
	{
		/* initialize SDL */
		if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		{
			cout << "Failed to initialize SDL: " << SDL_GetError() << endl;
			return false;
		} else {
			//SDL_EnableUNICODE(true); /* TODO: Unicode in SDL2 */
			cout << "SDL initialized." << endl;
		}
	}
	sdl_instances++;
	return true;
}

void SDLClose()
{
	if (sdl_instances == 1)
	{
		SDL_Quit();
	}
	sdl_instances--;
}

void SDLGL::Run()
{
	if (this->InitFunction)
	{
		if (SDLInit())
		{
			bool ok = true;

			cout << "Client thread started." << endl;

				/* Flags to pass to SDL_SetVideoMode */
			Uint32 videoFlags;
			/* main loop variable */
			bool done = false;
			/* used to collect events */
			SDL_Event sdl_event;
			/* whether or not the window is active */
			bool isActive = true;

			if (ok) {
				/* initialize SDL */
				if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) // | SDL_INIT_AUDIO
				{
					cout << "Video initialization failed: " << SDL_GetError() << endl;
					ok = false;
				}
			}

			if (ok)
			{
				/* Sets up OpenGL double buffering */
				SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

				/* get a SDL surface */
				this->surface = SDL_CreateWindow(title.c_str(),
												 SDL_WINDOWPOS_UNDEFINED,
												 SDL_WINDOWPOS_UNDEFINED,
												 this->width, this->height,
                                                 SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );

                SDL_SetWindowMinimumSize(this->surface, 320, 200);
                SDL_SetWindowMaximumSize(this->surface, 100000, 100000);
                SDL_SetWindowSize(this->surface, 800, 600);

                SDL_GLContext context = SDL_GL_CreateContext(this->surface);


				/* Verify there is a surface */
				if ( !this->surface )
				{
					cout << "Video mode set failed: " << SDL_GetError( ) << endl;
					ok = false;
				}
			}

			if (ok) {

				cout << "Initializing shaders..." << endl;
				setupExtensions();
				if (shading_enabled)
					cout << "Shaders ready." << endl;
				else {
					cout << "Failed to initialize shaders." << endl;
					ok = false;
				}
			}

			if (ok) {
				last_time = boost::posix_time::microsec_clock::local_time();

                auto sdlWindowID = SDL_GetWindowID(surface);

				this->is_running = true;

				l("GL initialization ok; run game initialization...", L_SYSTEM_INFO);
				
				/* initialize OpenGL */
				if (this->InitFunction(this))
				{
					l("Initialized. Running resize...", L_SYSTEM_INFO);
					/* resize the initial window */
					if (this->ResizeFunction)
						this->ResizeFunction(this);
					l("Resized. Running loop...", L_SYSTEM_INFO);
					/* wait for events */
					while ( !done )
					{
						/* handle the events in the queue */
						while ( SDL_PollEvent( &sdl_event ) )
						{
							switch( sdl_event.type )
							{
                            case SDL_WINDOWEVENT: {
                                if (sdlWindowID == sdl_event.window.windowID) {
                                    switch (sdl_event.window.event) {
                                        case SDL_WINDOWEVENT_FOCUS_LOST: {
                                            /* Something's happend with our focus
                                             * If we lost focus or we are iconified, we
                                             * shouldn't draw the screen
                                             */
                                            isActive = false;

                                            break;
                                        }
                                        case SDL_WINDOWEVENT_FOCUS_GAINED: {
                                            isActive = true;
                                            break;
                                        }
                                        case SDL_WINDOWEVENT_RESIZED: {
                                            l("Window resized.", L_SYSTEM_INFO);
                                            /* handle resize event */
                                            this->width = sdl_event.window.data1;
                                            this->height = sdl_event.window.data2;

//                                        l("Change video mode after resize...", L_SYSTEM_INFO);
//                                        SDL_SetWindowSize( surface, we.data1,
//                                                                     we.data2 );
//                                        if ( !surface )
//                                        {
//                                            cout << "Could not get a surface after resize: " << SDL_GetError() << endl;
//                                            this->Close();
//                                        }
                                            l("Running game resize...", L_SYSTEM_INFO);
                                            if (this->ResizeFunction)
                                                this->ResizeFunction(this);
                                            l("Resize ok.", L_SYSTEM_INFO);
                                            break;
                                        }
                                        case SDL_WINDOWEVENT_CLOSE: {
                                            this->Close();
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
							case SDL_MOUSEBUTTONDOWN:
								if (MouseDownFunction)
								{
									MouseDownFunction(this,&sdl_event);
								}
								break;
							case SDL_MOUSEBUTTONUP:
								if (MouseUpFunction)
								{
									MouseUpFunction(this,&sdl_event);
								}
								break;
							case SDL_MOUSEMOTION:
								if (MouseMoveFunction)
								{
									MouseMoveFunction(this,&sdl_event);
								}
								break;
                            case SDL_MOUSEWHEEL:
                                if (MouseWheelFunction)
                                {
                                    MouseWheelFunction(this,&sdl_event);
                                }
                                break;
							case SDL_KEYDOWN:
								if (KeyDownFunction)
								{
									KeyDownFunction(this,&sdl_event);
								}
								break;
							case SDL_KEYUP:
								if (KeyUpFunction)
								{
									KeyUpFunction(this,&sdl_event);
								}
								break;
							case SDL_QUIT:
								l("Quit signal received, halting.", L_SYSTEM_INFO);
								/* handle quit requests */
								done = true;
								break;
							default:
								break;
							}
						}

						if (!this->is_running)
							done = true;
						/* draw the scene */
						if ( !done )
						{
							if ( this->RenderFunction )
							{
								boost::posix_time::ptime ctime = boost::posix_time::microsec_clock::local_time();
								this->RenderFunction(this, ctime - last_time);
								last_time = ctime;
							}
						}

					}

					l("Executing exit function...", L_SYSTEM_INFO);
					if (this->ExitFunction)
						this->ExitFunction(this);
					l("Exit done.", L_SYSTEM_INFO);
				}
			}
			this->is_running = false;
			
			l("Closing SDL...", L_SYSTEM_INFO);
			SDLClose();
		}
	}
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}
