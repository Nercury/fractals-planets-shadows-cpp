#pragma once

#include "GameBase.h"
#include "TextureManager.h"
#include "Surface.h"
#include "Shader.h"
#include "PolyObject.h"
#include "TmpCollisionObj.h"
#include "WrlModel.h"
#include "Sphere.h"
#include "Light.h"
#include "Camera.h"
#include "TrMenu.h"
#include "safep.hpp"
#include "gui/Gui.h"
#include "glst/GLST_Text.h"
#include "gui/Window.h"

enum CamMode
{
	camWalk,
	camFly,
	camExamine,
};

class Trecia :
	public GameBase
{
private:
	// Hold id of the framebuffer for light POV rendering
	GLuint fboId;

	// Z values will be rendered to this texture when using fboId framebuffer
	GLuint depthTextureId0;
	GLuint depthTextureId1;
	GLuint depthTextureId2;
	GLuint depthTextureId3;
	GLuint depthTextureId4;
	GLuint depthTextureId5;

	Gui ui;

	p<ShaderManager> shaders;
	p<TextureManager> textures;

	Surface floor;
	Surface ceiling;
	Surface wleft;
	Surface wright;
	Surface wfront;
	Surface wback;

	//Sphere globe;

	p<Shader> sh_n_light_textured;
	p<Shader> sh_shiny_no_texture;

	Light light0;
	Light light1;
	Light light2;

	Camera camera;

	bool leftDown;
	bool rightDown;
	bool middleDown;

	bool btnW;
	bool btnS;
	bool btnA;
	bool btnD;

	bool ctrl;

	float movementSpeed;

	CamMode cameraMode;
	float examineDistance;

	p<GLST_Text> txtInfo;

	p<MWindow> menu;
	bool menuVisible;
	p<Windowless> menuItemCamera;


	p<PolyObject> polyObject;

	p<WrlModel> wrlModel;
	Vector3f wrlModelPosChange;

	void ChangeCamera();
	void ChangeShadows();
	void ToggleCollisions();

	//void GenerateShadowFBO();
	void InitShadowTexture(GLuint * depthTextureId);
	void InitFramebuffer(GLuint *fboId);
	void TransformToTexture(GLenum texture);
	void RenderShadowTexture(GLuint & textureId, Vector3f & position, Vector3f & target);
	void SetTextureMatrix(void);
	double modelView[16];
	double projection[16];
	int32_t shadowMapWidth;
	int32_t shadowMapHeight;

	bool collisionsVisible;
	std::vector<p<TmpCollisionObj>> collisionObjects;
	p<TmpCollisionObj> wrlCollision;
	p<TmpCollisionObj> polyCollision;
	p<TmpCollisionObj> colFloor;
	p<TmpCollisionObj> colCeiling;
	p<TmpCollisionObj> colLeft;
	p<TmpCollisionObj> colRight;
	p<TmpCollisionObj> colFront;
	p<TmpCollisionObj> colBack;
	p<TmpCollisionObj> staticCollision;
	p<TmpCollisionObj> staticCollision2;

	p<TmpCollisionObj> colRamp;

	int fov;

	bool ortho;

	float orthoScale;
	Vector3f orthoTranslate;

	bool shadows;
	virtual void Update(boost::posix_time::time_duration delta);
protected:
	virtual bool OnInitWindow(SDLGL* engine) override ;
	virtual void OnResizeWindow(SDLGL* engine) override ;
	virtual void OnRender(SDLGL* engine, boost::posix_time::time_duration delta) override ;
	virtual void OnExitWindow(SDLGL* engine) override ;
	virtual void OnKeyUp(SDLGL* engine, SDL_Event* ev) override ;
	virtual void OnKeyDown(SDLGL* engine, SDL_Event* ev) override ;
	virtual void OnMouseWheel(SDLGL* engine, SDL_Event* ev) override ;
	virtual void OnMouseUp(SDLGL* engine, SDL_Event* ev) override ;
	virtual void OnMouseDown(SDLGL* engine, SDL_Event* ev) override ;
	virtual void OnMouseMove(SDLGL* engine, SDL_Event* ev) override ;
public:
	Trecia(void);
	virtual ~Trecia(void) override ;
};
