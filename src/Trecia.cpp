#include "Trecia.h"

#include "math/Quaternion.h"
#include "gui/DecoratedWindow.h"
#include "World.h"


using namespace std;

Trecia::Trecia(void)
{
	shaders.put(new ShaderManager());
	textures.put(new TextureManager());

	float floorWidth = 4000; // x
	float floorLength = 1600; // z
	float height = 512;

	shadows = true;

	light0.position = Vector3f(200, height / 2, 1500);
	light0.color = Vector3f(1, 0.5f, .05f);
	light0.index = 0;
	light0.directional = true;
	light0.farDistance = 3000.0f;
	light0.rotation = light0.rotation * Quaternionf(Vector3f(1.7f,1.1f,0.1f), PI / 2).normalize();

	light1.position = Vector3f(2048, height / 2, 512);
	light1.color = Vector3f(0.7f, 0.7f, 0.3f);
	light1.index = 1;
	light1.directional = true;
	light1.cutOff = 30;

	light2.position = Vector3f(3100, height / 2, 512);
	light2.color = Vector3f(0.1f, 0.1f, 1);
	light2.directional = true;
	light2.index = 2;
	light2.rotation = light2.rotation * Quaternionf(Vector3f(1.7f,1.1f,0.1f), PI / 2).normalize();

	floor.texture.put(new Texture(textures, FullPathTo("textures/floor_stone.jpg")));
	floor.size.x = floorWidth;
	floor.size.y = floorLength;
	floor.rotation = Quaternionf(Vector3f(1,0,0), PI / 2 * 3);
	floor.position.z += floorLength;

	ceiling.texture.put(new Texture(textures, FullPathTo("textures/concrete.jpg")));
	ceiling.size.x = floorWidth;
	ceiling.size.y = floorLength;
	ceiling.rotation = Quaternionf(Vector3f(1,0,0), PI / 2);
	ceiling.position.y += height;

	wleft.texture.put(new Texture(textures, FullPathTo("textures/masonry-wall-texture.jpg")));
	wleft.size.x = floorLength;
	wleft.size.y = height;
	wleft.rotation = Quaternionf(Vector3f(0,1,0), -PI / 2);
	wleft.position.x += floorWidth;
	
	wright.texture.put(new Texture(textures, FullPathTo("textures/masonry-wall-texture.jpg")));
	wright.size.x = floorLength;
	wright.size.y = height;
	wright.rotation = Quaternionf(Vector3f(0,1,0), PI / 2);
	wright.position.z += floorLength;

	wfront.texture.put(new Texture(textures, FullPathTo("textures/masonry-wall-texture.jpg")));
	wfront.size.x = floorWidth;
	wfront.size.y = height;

	wback.texture.put(new Texture(textures, FullPathTo("textures/masonry-wall-texture.jpg")));
	wback.size.x = floorWidth;
	wback.size.y = height;
	wback.rotation = Quaternionf(Vector3f(0,1,0), PI);
	wback.position.x += floorWidth;
	wback.position.z += floorLength;

	camera.position.x = 100.0f;
	camera.position.z = -100.0f;
	camera.position.y = height / 2;
	camera.SetHeading(PI/4*3);

	polyObject.put(
		new PolyObject(
			Vector2f(0,1), 
			Vector2f(0,1), 
			[](float & u, float & v, float & x, float & y, float & z)
			{
				x = u*v/(1+u*u+v*v);
				y = v/(1+u*u+v*v);
				z = u/(1+u*u+v*v);
			}, 
			[](float & u, float & v, float & x, float & y, float & z)
			{
				x = v/(1+u*u+v*v);
				y = u/(1+u*u+v*v);
				z = u*v/(1+u*u+v*v);
			}, 
			[](float & u, float & v, float & x, float & y, float & z)
			{
				x = u/(1+u*u+v*v);
				y = u*v/(1+u*u+v*v);
				z = v/(1+u*u+v*v);
			}
		)
	);
	polyObject.o()->texture.put(new Texture(textures, FullPathTo("textures/earth.jpg")));
	polyObject.o()->position = Vector3f(900, 20, 600);
	polyObject.o()->shadowObject = true;

	{
		auto model = new WrlModel();
		Vector3d points[] = {
			Vector3d(-0.768762,-0.189192,-0.311110),Vector3d(-0.722704,-0.352430,0.277614),	Vector3d(-0.644068,0.409263,-0.351955),Vector3d(-0.569545,0.145138,0.600622),
			Vector3d(-0.549940,0.043133,-0.834090),Vector3d(-0.520946,0.615890,0.211526),Vector3d(-0.421491,-0.412116,0.807778),Vector3d(-0.340504,-0.493743,-0.626085),
			Vector3d(-0.265981,-0.757869,0.326492),Vector3d(-0.138746,0.474578,-0.692173),Vector3d(-0.029769,-0.845205,-0.232025),Vector3d(-0.018165,0.047213,0.849128),
			Vector3d(0.048867,-0.083511,-0.861595),Vector3d(0.060471,0.808907,0.219559),Vector3d(0.169448,-0.510876,0.679707),Vector3d(0.296683,0.721571,-0.338958),
			Vector3d(0.371207,0.457445,0.613619),Vector3d(0.551648,-0.652188,-0.223993),Vector3d(0.600247,-0.181435,-0.613088),Vector3d(0.664409,0.731961,0.150976),
			Vector3d(0.674771,-0.445561,0.339489),Vector3d(0.753406,0.316132,-0.290081),Vector3d(0.799464,0.152894,0.298644),
		};
		Vector3d colors[] = {
			Vector3d(0,0,0),Vector3d(0,0,0),Vector3d(0,0,0),Vector3d(0.0,0.72,0.6), Vector3d(0.9,0.7,0.3),  
			Vector3d(0.8,0.8,1.0), Vector3d(0.5,0.0,0.05), Vector3d(0.6,0.2,0.9), Vector3d(0.3,0.2,0.2),  
			Vector3d(0.4,0.4,1), Vector3d(0.4,0.4,0.4), 
		};
		int indexes[] = {
	      20,17,18,21,22,-1,9,15,21,18,12,-1,11,14,20,22,16,-1,8,10,17,20,14,-1,7,12,18,17,10,-1,
	      10,8,1,0,7,-1,16,13,5,3,11,-1,15,9,2,5,13,-1,2,0,1,3,5,-1,6,3,1,-1,6,1,8,-1,6,11,3,-1,6,14,11,-1,14,6,8,-1,19,22,21,-1,
	      19,21,15,-1,19,16,22,-1,19,13,16,-1,13,19,15,-1,4,0,2,-1,4,2,9,-1,4,7,0,-1,4,12,7,-1,12,4,9,-1, 
		};
		int colorIndexes[] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
		model->points = vector<Vector3d>(points, points + sizeof(points) / sizeof(Vector3d));
		model->colors = vector<Vector3d>(colors, colors + sizeof(colors) / sizeof(Vector3d));
		model->indexes = vector<int>(indexes, indexes + sizeof(indexes) / sizeof(int));
		model->colorIndexes = vector<int>(colorIndexes, colorIndexes + sizeof(colorIndexes) / sizeof(int));
		wrlModel.put(model);
	}

	wrlModel.o()->position = Vector3f(500, height / 3 + 20, 1100);
	wrlModel.o()->shadowObject = true;
	wrlModelPosChange = Vector3f(1.0f, 0.0, 0.1f);

	wrlCollision.put(new TmpCollisionObj(Vector3f(250, 300, 250)));
	collisionObjects.push_back(wrlCollision);

	staticCollision.put(new TmpCollisionObj(Vector3f(200, height, 400)));
	collisionObjects.push_back(staticCollision);
	staticCollision.o()->position = Vector3f(200, height + height / 2, 400);
	//staticCollision.o()->rotation = staticCollision.o()->rotation * Quaternionf(Vector3f(0,0,1), PI/5);
	staticCollision.o()->rotation = staticCollision.o()->rotation * Quaternionf(Vector3f(0,1,0), PI/3);

	staticCollision2.put(new TmpCollisionObj(Vector3f(200, height, 400)));
	collisionObjects.push_back(staticCollision2);
	staticCollision2.o()->position = Vector3f(200, height + height / 2, 400);
	//staticCollision2.o()->rotation = staticCollision.o()->rotation * Quaternionf(Vector3f(0,0,1), PI/2/5);
	staticCollision2.o()->rotation = staticCollision.o()->rotation * Quaternionf(Vector3f(0,1,0), -PI/3);

	colRamp.put(new TmpCollisionObj(Vector3f(floorWidth/3, 20, floorLength/2)));
	colRamp.o()->position = Vector3f(floorWidth / 2, height + floorWidth/3 * sin(PI/2/5) / 2, floorLength/2);
	colRamp.o()->rotation = colRamp.o()->rotation * Quaternionf(Vector3f(0,0,1), PI/2/5);
	collisionObjects.push_back(colRamp);

	colFloor.put(new TmpCollisionObj(Vector3f(floorWidth + 40, 20, floorLength + 40)));
	colFloor.o()->position = Vector3f(floorWidth / 2, -10, floorLength / 2);
	colCeiling.put(new TmpCollisionObj(Vector3f(floorWidth + 40, 20, floorLength + 40)));
	colCeiling.o()->position = Vector3f(floorWidth / 2, height+10, floorLength / 2);

	colLeft.put(new TmpCollisionObj(Vector3f(40, height, floorLength + 40)));
	colLeft.o()->position = Vector3f(floorWidth + 20, height / 2, floorLength / 2);
	colRight.put(new TmpCollisionObj(Vector3f(40, height, floorLength + 40)));
	colRight.o()->position = Vector3f(-20, height / 2, floorLength / 2);

	colFront.put(new TmpCollisionObj(Vector3f(floorWidth, height, 40)));
	colFront.o()->position = Vector3f(floorWidth / 2, height / 2, -20);
	colBack.put(new TmpCollisionObj(Vector3f(floorWidth, height, 40)));
	colBack.o()->position = Vector3f(floorWidth / 2, height / 2, floorLength+20);

	collisionObjects.push_back(colFloor);
	collisionObjects.push_back(colCeiling);
	collisionObjects.push_back(colLeft);
	collisionObjects.push_back(colRight);
	collisionObjects.push_back(colFront);
	collisionObjects.push_back(colBack);

	leftDown = false;
	rightDown = false;
	middleDown = false;

	btnW = false;
	btnA = false;
	btnS = false;
	btnD = false;

	ctrl = false;

	cameraMode = camWalk;
	examineDistance = 128.0f;

	movementSpeed = 6.0f;

	menuVisible = false;

	ortho = false;

	orthoScale = 1;
	Vector3f orthoTranslate = Vector3f(0,0,0);

	collisionsVisible = false;


	shadowMapWidth = 512;
	shadowMapHeight = 512;

	fov = 70;
}

Trecia::~Trecia(void)
{
}

void Trecia::InitShadowTexture(GLuint * depthTextureId)
{
	// Try to use a texture depth component
	glGenTextures(1, depthTextureId);
	glBindTexture(GL_TEXTURE_2D, *depthTextureId);

	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Remove artifact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Trecia::InitFramebuffer(GLuint * fboId)
{
	GLenum FBOstatus;

	// create a framebuffer object
	glGenFramebuffersEXT(1, fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, *fboId);

	// Instruct openGL that we won't bind a color texture with the currently binded FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	/*FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");*/

	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

bool Trecia::OnInitWindow(SDLGL* engine)
{
	sh_n_light_textured.put(new Shader(shaders, FullPathTo("shaders/n_light_vs.fx"), FullPathTo("shaders/n_light_ps.fx")));
	sh_shiny_no_texture.put(new Shader(shaders, FullPathTo("shaders/shiny_no_texture_vs.fx"), FullPathTo("shadersf/shiny_no_texture_ps.fx")));

	floor.shader = sh_n_light_textured;
	wleft.shader = sh_n_light_textured;
	wright.shader = sh_n_light_textured;
	wfront.shader = sh_n_light_textured;
	wback.shader = sh_n_light_textured;
	ceiling.shader = sh_n_light_textured;

	polyObject.o()->shader = sh_shiny_no_texture;
	wrlModel.o()->shader = sh_shiny_no_texture;

	txtInfo.put(new GLST_Text(FullPathTo("fonts/FreeMonoBold.ttf"), 12, GLST_Top_Left));
	txtInfo.o()->SetColor(1,1,0);
	txtInfo.o()->SetText("Running. Press M to show menu.");

	{
		auto mnu = new TrMenu();
		mnu->Add(p<Windowless>(new TrMenuItem("Exit", [=](TrMenuItem * item) { 
			if (engine != NULL)
				engine->Close();
		})));
		mnu->Add(new TrMenuItem("Light [1,2,3]", [=](TrMenuItem * item) { 
			light0.directional = !light0.directional;
		}));
		menuItemCamera.put(new TrMenuItem("Camera Mode (Walk) [C]", [=](TrMenuItem * item) { 
			ChangeCamera();
		}));
		mnu->Add(menuItemCamera);
		mnu->Add(p<Windowless>(new TrMenuItem("Shadows [H]", [=](TrMenuItem * item) { 
			ChangeShadows();
		})));
		mnu->Add(p<Windowless>(new TrMenuItem("Colisions [O]", [=](TrMenuItem * item) { 
			ToggleCollisions();
		})));
		mnu->Add(p<Windowless>(new TrMenuItem("FOV (70)", [=](TrMenuItem * item) { 
			fov += 5;
			if (fov > 95)
				fov = 60;
			ostringstream ss;
			ss << "FOV (" << fov << ")";
			item->SetText(ss.str());
		})));
		/*mnu->Add(p<Windowless>(new TrMenuItem("Perspective", [=](TrMenuItem * item) {
			ortho = !ortho;
			if (ortho)
			{
				orthoTranslate = Vector3f(512, 512, 0);
				item->SetText("Ortho");
			}
			else
				item->SetText("Perspective");
		})));*/
		mnu->Add(p<Windowless>(new TrMenuItem("Menu [M]", [=](TrMenuItem * item) { 
			ui.layer()->RemoveWindow(menu);
			menuVisible = false;
		})));
		menu.put(mnu);

		ui.layer()->AddWindow(menu);
		menuVisible = true;
	}

	//ui.layerTop()->AddWindow(p<Window>(new DecoratedWindow()));

    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	return true;
}

void Trecia::OnResizeWindow(SDLGL* engine)
{
	//GenerateShadowFBO();
	InitShadowTexture(&depthTextureId0);
	InitShadowTexture(&depthTextureId1);
	InitShadowTexture(&depthTextureId2);
	InitShadowTexture(&depthTextureId3);
	InitShadowTexture(&depthTextureId4);
	InitShadowTexture(&depthTextureId5);

	InitFramebuffer(&fboId);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

	/* Depth buffer setup */
    glClearDepth( 1.0f );

	glEnable(GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL );
	glEnable(GL_CULL_FACE);

	//glDisable(GL_BLEND);

	textures.o()->WindowResize();
	shaders.o()->WindowResize();
	GLST_Refresh();

	ui.SetSize((int32_t)width, (int32_t)height);

	menu.o()->Resize((int32_t)width, 32);
	menu.o()->Move(0, 0);
}

void setupMatrices(float position_x,float position_y,float position_z,float lookAt_x,float lookAt_y,float lookAt_z)
{
	gluLookAt(position_x,position_y,position_z,lookAt_x,lookAt_y,lookAt_z,0,1,0);
}

void Trecia::TransformToTexture(GLenum texture)
{
	//Save modelview/projection matrice into texture7, also add a biais
	// This is matrix transform every coordinate x,y,z
	// x = x* 0.5 + 0.5 
	// y = y* 0.5 + 0.5 
	// z = z* 0.5 + 0.5 
	// Moving from unit cube [-1,1] to [0,1]  
	const GLdouble bias[16] = {	
		0.5, 0.0, 0.0, 0.0, 
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	};
	
	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(texture);
	
	glLoadIdentity();
	glLoadMatrixd(bias);
	glMultMatrixd (projection);
	glMultMatrixd (modelView);
	
	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void Trecia::RenderShadowTexture(GLuint & textureId, Vector3f & position, Vector3f & target)
{
	//First step: Render from the light POV to a FBO, story depth values only
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboId);	//Rendering offscreen
	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, textureId, 0);

	//Using the fixed pipeline to render to the depthbuffer
	glUseProgramObjectARB(0);
	
	// In the case we render the shadowmap to a higher resolution, the viewport must be modified accordingly.
	glViewport(0,0,shadowMapWidth,shadowMapHeight);
	
	// Clear previous frame values
	glClear(GL_DEPTH_BUFFER_BIT);
	
	//Disable color rendering, we only want to write to the Z-Buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,shadowMapWidth/shadowMapHeight,10,40000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//camera.ApplyLookAt(light0.position, wrlModel.o()->position);
	//setupMatrices(camera.position.x,camera.position.y,camera.position.z,wrlModel.o()->position.x,wrlModel.o()->position.y,wrlModel.o()->position.z);
	setupMatrices(position.x,position.y,position.z,target.x,target.y,target.z);
	
	// Culling switching, rendering only backface, this is done to avoid self-shadowing
	glCullFace(GL_FRONT);
}

void Trecia::Update(boost::posix_time::time_duration delta)
{
	Vector3f cameraChangeTotal;
	if (!ortho)
	{
		if (btnA && !btnD)
		{
			cameraChangeTotal += camera.GetWalkChange(Vector3f(-delta.total_milliseconds() / 10.0f * movementSpeed, 0, 0));
		}
		else if (!btnA && btnD)
		{
			cameraChangeTotal += camera.GetWalkChange(Vector3f(delta.total_milliseconds() / 10.0f * movementSpeed, 0, 0));
		}

		if (cameraMode == camWalk)
		{
			cameraChangeTotal += Vector3f(0,-3.0f,0); // gravity :D
			if (btnW && !btnS)
			{
				cameraChangeTotal += camera.GetWalkChange(Vector3f(0, 0, delta.total_milliseconds() / 10.0f * movementSpeed));
			}
			else if (!btnW && btnS)
			{
				cameraChangeTotal += camera.GetWalkChange(Vector3f(0, 0, -delta.total_milliseconds() / 10.0f * movementSpeed));
			}
		}
		else if (cameraMode == camFly)
		{
			if (btnW && !btnS)
			{
				cameraChangeTotal += camera.GetPanChange(Vector3f(0, 0, delta.total_milliseconds() / 10.0f * movementSpeed));
			}
			else if (!btnW && btnS)
			{
				cameraChangeTotal += camera.GetPanChange(Vector3f(0, 0, -delta.total_milliseconds() / 10.0f * movementSpeed));
			}
		}
		else if (cameraMode == camExamine)
		{
			float change = delta.total_milliseconds() / 10.0f * movementSpeed;
			if (btnW && !btnS)
			{
				cameraChangeTotal += camera.GetWalkChange(Vector3f(0,0,change));
			}
			else if (!btnW && btnS)
			{
				cameraChangeTotal += camera.GetWalkChange(Vector3f(0,0,-change));
			}
		}
	}

	polyObject.o()->rotation = polyObject.o()->rotation * Quaternionf(Vector3f(0,1.0f,0), 0.003f * delta.total_milliseconds()).normalize();
	wrlModel.o()->rotation = wrlModel.o()->rotation * Quaternionf(Vector3f(0,1.0f,0), 0.003f * delta.total_milliseconds()).normalize();
	light1.rotation = light1.rotation * Quaternionf(Vector3f(1.0f,0.0f,0.0f), 0.01f).normalize();
	light2.rotation = light2.rotation * Quaternionf(Vector3f(0.0f,1.0f,0.0f), 0.01f).normalize();

	wrlModel.o()->position += wrlModelPosChange * (float)delta.total_milliseconds() * 0.5f;
	if (wrlModel.o()->position.x > 3500 || wrlModel.o()->position.x < 500)
		wrlModelPosChange = -wrlModelPosChange;

	Vector3f colPosChange = wrlModel.o()->position - wrlCollision.o()->position;
	wrlCollision.o()->position = wrlModel.o()->position;
	wrlCollision.o()->rotation = wrlModel.o()->rotation;

	/*Vector3f responseDirection, surfaceNormal;
	float distance;
	bool colHit = false;
	if (colPosChange.length() > 0)
	{
		if (camera.TestSphereBox(wrlCollision.o()->position, wrlCollision.o()->size / 2, wrlCollision.o()->rotation, camera.GetCorrectPosition(),
				90.0f, camera.GetCameraDirection(camera.GetPanPosition(-colPosChange.normalized())), responseDirection, surfaceNormal, distance))
		{
			cameraChangeTotal += (camera.position-wrlCollision.o()->position).normalized() * wrlCollision.o()->size.length() / 2;
			colHit = true;
		}
	}*/


	if (cameraChangeTotal.length() > ZERO && !ortho)
	{
		camera.Move(cameraChangeTotal, collisionObjects);
	}
}

void Trecia::OnRender(SDLGL* engine, boost::posix_time::time_duration delta)
{
	glDisable(GL_TEXTURE_2D);

	textures.o()->SceneStart();
	GLST_SetSceneStart();

	Update(delta);

	if (shadows)
	{

	// ----------------------------SHADOWS ----------------- 

		sh_n_light_textured.o()->enabled = false;
		sh_shiny_no_texture.o()->enabled = false;

		RenderShadowTexture(depthTextureId0, light0.position, wrlModel.o()->position);
		get_world().o()->RenderShadows(wrlModel.o());
		TransformToTexture(GL_TEXTURE2);

		RenderShadowTexture(depthTextureId1, light0.position, polyObject.o()->position);
		get_world().o()->RenderShadows(polyObject.o());
		TransformToTexture(GL_TEXTURE3);

		RenderShadowTexture(depthTextureId2, light1.position, wrlModel.o()->position);
		get_world().o()->RenderShadows(wrlModel.o());
		TransformToTexture(GL_TEXTURE4);

		RenderShadowTexture(depthTextureId3, light1.position, polyObject.o()->position);
		get_world().o()->RenderShadows(polyObject.o());
		TransformToTexture(GL_TEXTURE5);

		RenderShadowTexture(depthTextureId4, light2.position, wrlModel.o()->position);
		get_world().o()->RenderShadows(wrlModel.o());
		TransformToTexture(GL_TEXTURE6);

		RenderShadowTexture(depthTextureId5, light2.position, polyObject.o()->position);
		get_world().o()->RenderShadows(polyObject.o());
		TransformToTexture(GL_TEXTURE7);
		



		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	// Now rendering from the camera POV, using the FBO to generate shadows
		//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
	}
	// ----------------------------CAMERA ----------------- 	

	if (ortho)
	{
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho(0, width, height, 0, -60000, 60000);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glCullFace(GL_FRONT);
	}
	else
	{
		glViewport( 0, 0, width, height );
	    glMatrixMode( GL_PROJECTION );
	    glLoadIdentity( );
	    gluPerspective( fov, this->ratio, 1.0f, 64000.0f );
	    glMatrixMode( GL_MODELVIEW );
	    glLoadIdentity( );
		glCullFace(GL_BACK);
	}
	
	// Clear the redering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	if (ortho)
	{
		wTranslatef(orthoTranslate.x,orthoTranslate.y,orthoTranslate.z);
		wScalef(orthoScale,orthoScale,orthoScale);
		wRotatef(180, 0, 0, 1);
	}
	else
	{
		camera.Apply();
	}

	sh_n_light_textured.o()->enabled = true;
	sh_shiny_no_texture.o()->enabled = true;
	if (shadows)
	{
		sh_n_light_textured.o()->BindTexture("ShadowMap0", 2, depthTextureId0);
		sh_n_light_textured.o()->BindTexture("ShadowMap1", 3, depthTextureId1);
		sh_n_light_textured.o()->BindTexture("ShadowMap2", 4, depthTextureId2);
		sh_n_light_textured.o()->BindTexture("ShadowMap3", 5, depthTextureId3);
		sh_n_light_textured.o()->BindTexture("ShadowMap4", 6, depthTextureId4);
		sh_n_light_textured.o()->BindTexture("ShadowMap5", 7, depthTextureId5);
	}

	get_world().o()->Render();

	glUseProgramObjectARB(0);

	glDisable(GL_LIGHTING);

	if (cameraMode == camExamine)
	{
		
		glColor3f(1,0,0);
		auto targetPos = camera.GetPanPosition(Vector3f(0,0,examineDistance));
		glTranslatef(targetPos.x, targetPos.y, -targetPos.z);
		glBegin(GL_LINES);
		glVertex3f(-30,0,0);	glVertex3f(30,0,0);
		glVertex3f(0,-30,0);	glVertex3f(0,30,0);
		glVertex3f(0,0,-30);	glVertex3f(0,0,30);
		glEnd();
	}

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glCullFace(GL_BACK);

	// GUI

	glDisable(GL_DEPTH_TEST);

	ui.Render(delta);

	if (!menuVisible)
	{
		glEnable(GL_BLEND);
		GLint top = 5;
		txtInfo.o()->Render(5,top);
		top += ((GLint)txtInfo.o()->Height()) + 2;
		glDisable(GL_BLEND);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	SDL_GL_SwapWindow(engine->surface);
}

void Trecia::OnExitWindow(SDLGL* engine)
{
}

void Trecia::OnKeyUp(SDLGL* engine, SDL_Event* ev)
{
	if (!ui.OnKeyUp(ev))
	{
		switch ( ev->key.keysym.sym )
		{
			case SDLK_LCTRL:
				ctrl = false;
				break;
			case SDLK_w:
				btnW = false;
				break;
			case SDLK_a:
				btnA = false;
				break;
			case SDLK_s:
				btnS = false;
				break;
			case SDLK_d:
				btnD = false;
				break;
			default:
				break;
		}
	}
}

void Trecia::OnKeyDown(SDLGL* engine, SDL_Event* ev)
{
	if (!ui.OnKeyDown(ev))
	{
		switch ( ev->key.keysym.sym )
		{
			case SDLK_ESCAPE:
				if (engine != NULL)
				{
					engine->Close();
				}
				break;
			case SDLK_LCTRL:
				ctrl = true;
				break;
			case SDLK_m:
				menuVisible = !menuVisible;
				if (menuVisible)
					ui.layer()->AddWindow(menu);
				else
					ui.layer()->RemoveWindow(menu);
				break;	
			case SDLK_1:
				light0.directional = !light0.directional;
				break;
			case SDLK_2:
				light1.directional = !light1.directional;
				break;
			case SDLK_3:
				light2.directional = !light2.directional;
				break;
			case SDLK_c:
				ChangeCamera();
				break;	
			case SDLK_h:
				ChangeShadows();
				break;				
			case SDLK_o:
				ToggleCollisions();
				break;				
			case SDLK_w:
				btnW = true;
				break;
			case SDLK_a:
				btnA = true;
				break;
			case SDLK_s:
				btnS = true;
				break;
			case SDLK_d:
				btnD = true;
				break;
			default:
				break;
		}
	}
}

void Trecia::OnMouseUp(SDLGL* engine, SDL_Event* ev)
{
	if (!ui.OnMouseUp(ev))
	{
		if (ev->button.button == SDL_BUTTON_LEFT)
		{
			leftDown = false;
		}
		if (ev->button.button == SDL_BUTTON_RIGHT)
		{
			rightDown = false;
		}
		if (ev->button.button == SDL_BUTTON_MIDDLE)
		{
			middleDown = false;
		}
	}
}

void Trecia::OnMouseWheel(SDLGL *engine, SDL_Event *ev){
    if (ortho)
    {
        if (ev->wheel.y > 0) // mouse wheel up
        {
            orthoScale *= 1.5 * abs(ev->wheel.y);
        }
        if (ev->wheel.y < 0) // mouse wheel down
        {
            orthoScale /= 1.5 * abs(ev->wheel.y);
        }
    }
    else
    {
        if (cameraMode == camExamine)
        {
            float change = 6 * movementSpeed;
            if (ev->wheel.y > 0) // mouse wheel up
            {
                examineDistance -= change * abs(ev->wheel.y);
                camera.Pan(Vector3f(0,0,change));
            }
            if (ev->wheel.y < 0) // mouse wheel down
            {
                examineDistance += change * abs(ev->wheel.y);
                camera.Pan(Vector3f(0,0,-change));
            }
        }
    }
}

void Trecia::OnMouseDown(SDLGL* engine, SDL_Event* ev)
{
	if (!ui.OnMouseDown(ev))
	{
		if (ev->button.button == SDL_BUTTON_LEFT)
		{
			leftDown = true;
		}
		if (ev->button.button == SDL_BUTTON_RIGHT)
		{
			rightDown = true;
		}
		if (ev->button.button == SDL_BUTTON_MIDDLE)
		{
			middleDown = true;
		}
	}
}

void Trecia::OnMouseMove(SDLGL* engine, SDL_Event* ev)
{
	if (!ui.OnMouseMove(ev))
	{
		if (ortho)
		{
			if (leftDown)
			{
				orthoTranslate += Vector3f(ev->motion.xrel / 2.0f * movementSpeed,ev->motion.yrel / 2.0f * movementSpeed, 0);
			}
		}
		else
		{
			if (ctrl)
			{
				if (leftDown)
				{
					light0.position = Vector3f(light0.position.x-ev->motion.xrel / 2.0f * movementSpeed,light0.position.y, light0.position.z + ev->motion.yrel / 2.0f * movementSpeed); 
				}
				else if (middleDown)
				{
					light0.position.y += ev->motion.yrel / 2.0f * movementSpeed; 
				}
				else if (rightDown)
				{
					float headingChange = ev->motion.xrel / (float)200;
					float pitchChange = ev->motion.yrel / (float)200;
					light0.rotation = light0.rotation * Quaternionf(Vector3f(1.0f, 0.0f, 0.0f), pitchChange) * Quaternionf(Vector3f(0.0f, 1.0f, 0.0f), headingChange); 
				}
			}
			else
			{
				if (leftDown || rightDown || middleDown)
				{
					if (leftDown && rightDown)
					{
						if (cameraMode == camFly || cameraMode == camExamine)
							camera.position.y += (ev->motion.yrel / (float)2 * movementSpeed);
					}
					else if (leftDown)
					{
						float headingChange = ev->motion.xrel / (float)200;
						float pitchChange = ev->motion.yrel / (float)200;
						camera.ChangeHeading(headingChange);
						camera.ChangePitch(pitchChange);
						if (cameraMode == camExamine)
						{
							// paskaiciuojam nauja pozicija
							Quaternionf q = Quaternionf(Vector3f(1.0f, 0.0f, 0.0f), pitchChange) * Quaternionf(Vector3f(0.0f, 1.0f, 0.0f), headingChange);
							Matrix4f m; q.to4x4Matrix(&m);
							camera.position += camera.GetPanPosition(Vector3f(0,0,examineDistance)) - camera.GetPanPosition(Vector3f(0,0,examineDistance).transform(m));
						}
					}
					else if (rightDown)
					{
						if (cameraMode == camFly || cameraMode == camExamine)
							camera.Pan(Vector3f(-ev->motion.xrel / 2.0f * movementSpeed, ev->motion.yrel / 2.0f * movementSpeed, 0));
					}
					else if (middleDown)
					{
						wrlModel.o()->position = Vector3f(wrlModel.o()->position.x-ev->motion.xrel / 2.0f * movementSpeed,wrlModel.o()->position.y, wrlModel.o()->position.z + ev->motion.yrel / 2.0f * movementSpeed); 
					}
				}
			}
		}
	}
}

void Trecia::ChangeCamera()
{
	if (cameraMode == camFly)
		cameraMode = camWalk;
	else if (cameraMode == camWalk)
		cameraMode = camExamine;
	else if (cameraMode == camExamine)
		cameraMode = camFly;
	if (cameraMode == camFly)
		dynamic_cast<TrMenuItem*>(menuItemCamera.o())->SetText("Camera Mode (Fly) [C]");
	else if (cameraMode == camWalk)
		dynamic_cast<TrMenuItem*>(menuItemCamera.o())->SetText("Camera Mode (Walk) [C]");
	else if (cameraMode == camExamine)
		dynamic_cast<TrMenuItem*>(menuItemCamera.o())->SetText("Camera Mode (Examine) [C]");
}

void Trecia::ChangeShadows()
{
	shadows = !shadows;
	if (shadows)
	{
		floor.shader = sh_n_light_textured;
		wleft.shader = sh_n_light_textured;
		wright.shader = sh_n_light_textured;
		wfront.shader = sh_n_light_textured;
		wback.shader = sh_n_light_textured;
		ceiling.shader = sh_n_light_textured;
	}
	else
	{
		floor.shader = sh_shiny_no_texture;
		wleft.shader = sh_shiny_no_texture;
		wright.shader = sh_shiny_no_texture;
		wfront.shader = sh_shiny_no_texture;
		wback.shader = sh_shiny_no_texture;
		ceiling.shader = sh_shiny_no_texture;
	}
}

void Trecia::ToggleCollisions()
{
	collisionsVisible = !collisionsVisible;
	for (auto it = collisionObjects.begin(); it != collisionObjects.end(); ++it)
	{
		it->o()->visible = collisionsVisible;
	}
}