#pragma once

#include "sdlgl.h"
#include "math/Quaternion.h"
#include "math/Vector.h"
#include "math/Matrix.h"
#include "math/Plane.h"

#include <vector>

#include "TmpCollisionObj.h"

class Camera
{
private:
	float maxPitchRate;
	float maxHeadingRate;
	float headingRadians;
	float pitchRadians;
	float maxForwardVelocity;
	float forwardVelocity;
	Quaternionf qHeading;
	Quaternionf qPitch;
	Vector3f directionVector;

	void RenderArrow(const Vector3f& P, const Vector3f& D, float length, const Vector3f color);
public:
	Vector3f position;
	bool TestPointInsideBox(const Vector3f & boxCenter, const Vector3f & boxHalfSize, Quaternionf & rot, 
		const Vector3f & point, const Vector3f & change, Vector3f & responseDirection, Vector3f & surfaceNormal);
	bool TestSphereBox(const Vector3f & boxCenter, const Vector3f & boxHalfSize, Quaternionf & boxRotation,
		const Vector3f & spherePos, const float sphereRadius, const Vector3f & sphereVelocity,
		Vector3f & responseDirection, Vector3f & surfaceNormal, 
		float & distance);	
	void Pan(Vector3f direction);
	Vector3f GetCameraDirection(Vector3f nextPosition);
	Vector3f GetCorrectPosition();
	Vector3f GetPanPosition(Vector3f direction);
	Vector3f GetPanChange(Vector3f direction);
	void Walk(Vector3f direction);
	Vector3f GetWalkPosition(Vector3f direction);
	Vector3f GetWalkChange(Vector3f direction);
	void Move(Vector3f direction, std::vector<p<TmpCollisionObj>> collisionObjects);
	void WalkWithCollision(Vector3f direction, std::vector<p<TmpCollisionObj>> collisionObjects);
	//void SetVelocity(float vel); // nera reikalo cia sito laikyt
	void SetHeading(float radians);
	void SetPitch(float radians);
	//void ChangeVelocity(float vel);
	void ChangeHeading(float radians);
	void ChangePitch(float radians);
	float Heading() { return headingRadians; };
	float Pitch() { return pitchRadians; };
	void Apply(void);
	void GetMatrix(Matrix4f & m);
	void GetLookAtMatrix(Vector3f position, Vector3f target, Matrix4f & m);
	void ApplyLookAt(Vector3f position, Vector3f target);
	Camera();
	virtual ~Camera();
};