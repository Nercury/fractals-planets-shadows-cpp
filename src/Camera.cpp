#include "Camera.h"

#include <iostream>
#include <cmath>

using namespace std;

Camera::Camera()
{
	maxPitchRate = 0.1f;
	maxHeadingRate = 0.1f;
	headingRadians = 0.0f;
	pitchRadians = 0.0f;
	maxForwardVelocity = 5.0f;
	forwardVelocity = 0.0f;
}

Camera::~Camera()
{

}

void Camera::Pan(Vector3f direction)
{
	position = GetPanPosition(direction);
}

Vector3f Camera::GetPanPosition(Vector3f direction)
{
	Quaternionf q = qHeading * qPitch;
	Matrix4f m;
	q.to4x4Matrix(&m);
	return position + direction.transform(m);
}

Vector3f Camera::GetPanChange(Vector3f direction)
{
	Quaternionf q = qHeading * qPitch;
	Matrix4f m;
	q.to4x4Matrix(&m);
	return direction.transform(m);
}

void Camera::Walk(Vector3f direction)
{
	Matrix4f m;
	qHeading.to4x4Matrix(&m);
	position += direction.transform(m);
}

Vector3f Camera::GetWalkPosition(Vector3f direction)
{
	Matrix4f m;
	qHeading.to4x4Matrix(&m);
	return position + direction.transform(m);
}

Vector3f Camera::GetWalkChange(Vector3f direction)
{
	Matrix4f m;
	qHeading.to4x4Matrix(&m);
	return direction.transform(m);
}

static float sqr(float a)
{
	return a*a;
}

// Offset pIn by pOffset into pOut
static void VectorOffset (Vector3f & pIn, Vector3f & pOffset, Vector3f & pOut)
{
   pOut.x = pIn.x - pOffset.x;
   pOut.y = pIn.y - pOffset.y;
   pOut.z = pIn.z - pOffset.z;
}

// Compute the cross product a X b into pOut
static void VectorGetNormal (Vector3f & a, Vector3f & b, Vector3f & pOut)
{
   pOut.x = a.y * b.z - a.z * b.y;
   pOut.y = a.z * b.x - a.x * b.z;
   pOut.z = a.x * b.y - a.y * b.x;
}

// Normalize pIn vector into pOut
static bool VectorNormalize (Vector3f & pIn, Vector3f & pOut)
{
   float len = (float)(sqrt(sqr(pIn.x) + sqr(pIn.y) + sqr(pIn.z)));
   if (len)
   {
      pOut.x = pIn.x / len;
      pOut.y = pIn.y / len;
      pOut.z = pIn.z / len;
      return true;
   }
   return false;
}

// Compute p1,p2,p3 face normal into pOut
static bool ComputeFaceNormal (Vector3f & p1, Vector3f & p2, Vector3f & p3, Vector3f & pOut)
{
   // Uses p2 as a new origin for p1,p3
   Vector3f a;
   VectorOffset(p3, p2, a);
   Vector3f b;
   VectorOffset(p1, p2, b);
   // Compute the cross product a X b to get the face normal
   Vector3f pn;
   VectorGetNormal(a, b, pn);
   // Return a normalized vector
   return VectorNormalize(pn, pOut);
}

static bool TestIntersectionPlane(const Vector3f & surfaceNormal, const Vector3f & surfacePosition, const Vector3f & position,const Vector3f & direction, float & lamda, Vector3f & pNormal)
{
	float DotProduct = direction * surfaceNormal;			// Dot Product Between Plane Normal And Ray Direction
	double l2;

	// Determine If Ray Parallel To Plane
	if ((DotProduct<ZERO)&&(DotProduct>-ZERO))
		return false;

	l2=(surfaceNormal * (surfacePosition-position))/DotProduct;	// Find Distance To Collision Point

	if (l2<-ZERO)							// Test If Collision Behind Start
		return false;

	pNormal=surfaceNormal;
	lamda=l2;
	return true;
}

float DistanceToPlane(const Vector3f & point, const Vector3f & planePoint, const Vector3f & planeNormal)
{
	float dot = (point - planePoint) * planeNormal;
	if ((dot<ZERO)&&(dot>-ZERO))
		return 1000000; // bet koks didelis skaicius
	return dot;
}

bool Camera::TestPointInsideBox(const Vector3f & boxCenter, const Vector3f & boxHalfSize, Quaternionf & rot, const Vector3f & point, const Vector3f & change,
	Vector3f & responseDirection, Vector3f & surfaceNormal)
{
	Vector3f localPoint = point - boxCenter;
	Vector3f nextPos = point + change;
	Vector3f directionNormal = change.normalized();

	//RenderArrow(localPoint, directionNormal, 50, Vector3f(1,0,0));

	Matrix4f m;
	rot.to4x4Matrix(&m);

	Vector3f topLeftFront = Vector3f(boxHalfSize.x, boxHalfSize.y, -boxHalfSize.z).transform(m);
	Vector3f topLeftBack = Vector3f(boxHalfSize.x, boxHalfSize.y, boxHalfSize.z).transform(m);
	Vector3f topRightFront = Vector3f(-boxHalfSize.x, boxHalfSize.y, -boxHalfSize.z).transform(m);
	Vector3f topRightBack = Vector3f(-boxHalfSize.x, boxHalfSize.y, boxHalfSize.z).transform(m);
	Vector3f bottomLeftFront = Vector3f(boxHalfSize.x, -boxHalfSize.y, -boxHalfSize.z).transform(m);
	Vector3f bottomLeftBack = Vector3f(boxHalfSize.x, -boxHalfSize.y, boxHalfSize.z).transform(m);
	Vector3f bottomRightFront = Vector3f(-boxHalfSize.x, -boxHalfSize.y, -boxHalfSize.z).transform(m);
	Vector3f bottomRightBack = Vector3f(-boxHalfSize.x, -boxHalfSize.y, boxHalfSize.z).transform(m);

	Vector3f leftNormal = bottomLeftFront - bottomRightFront;
	leftNormal.normalize();
	//RenderArrow(bottomLeftFront, leftNormal, 50, Vector3f(1,0,0));

	Vector3f rightNormal = bottomRightFront - bottomLeftFront;
	rightNormal.normalize();
	//RenderArrow(bottomRightFront, rightNormal, 50, Vector3f(1,0,0));

	Vector3f frontNormal = bottomLeftFront - bottomLeftBack;
	frontNormal.normalize();
	//RenderArrow(bottomLeftFront, frontNormal, 50, Vector3f(1,0,0));

	Vector3f backNormal = bottomLeftBack - bottomLeftFront;
	backNormal.normalize();
	//RenderArrow(bottomLeftBack, backNormal, 50, Vector3f(1,0,0));

	Vector3f topNormal = topLeftFront - bottomLeftFront;
	topNormal.normalize();
	//RenderArrow(topLeftFront, topNormal, 50, Vector3f(1,0,0));

	Vector3f bottomNormal = bottomLeftFront - topLeftFront;
	bottomNormal.normalize();
	//RenderArrow(bottomLeftFront, bottomNormal, 50, Vector3f(1,0,0));

	float dLeft = DistanceToPlane(localPoint, bottomLeftFront, leftNormal);
	float dRight = DistanceToPlane(localPoint, bottomRightFront, rightNormal);
	float dFront = DistanceToPlane(localPoint, bottomLeftFront, frontNormal);
	float dBack = DistanceToPlane(localPoint, bottomLeftBack, backNormal);
	float dTop = DistanceToPlane(localPoint, topLeftFront, topNormal);
	float dBottom = DistanceToPlane(localPoint, bottomLeftFront, bottomNormal);

	if (true
		&& dLeft < 0 
		&& dRight < 0 
		&& dFront < 0 
		&& dBack < 0 
		&& dTop < 0 
		&& dBottom < 0)
	{
		//cout<< "------ InBox" << endl;

		Vector3f nearestPlaneNormal;
		Vector3f nearestPlanePoint;

		float distance = -1000000;
		if (dLeft > distance)
		{
			distance = dLeft;
			nearestPlaneNormal = leftNormal;
			nearestPlanePoint = bottomLeftFront;
		}
		if (dRight > distance)
		{
			distance = dRight;
			nearestPlaneNormal = rightNormal;
			nearestPlanePoint = bottomRightFront;
		} 
		if (dFront > distance)
		{
			distance = dFront;
			nearestPlaneNormal = frontNormal;
			nearestPlanePoint = bottomLeftFront;
		} 
		if (dBack > distance)
		{
			distance = dBack;
			nearestPlaneNormal = backNormal;
			nearestPlanePoint = bottomLeftBack;
		} 
		if (dTop > distance)
		{
			distance = dTop;
			nearestPlaneNormal = topNormal;
			nearestPlanePoint = topLeftFront;
		} 
		if (dBottom > distance)
		{
			distance = dBottom;
			nearestPlaneNormal = bottomNormal;
			nearestPlanePoint = bottomLeftFront;
		} 
		if (distance < 1000000 + ZERO && distance > 1000000 - ZERO) return false;

		//cout << "nearestPlaneNormal: x:" << nearestPlaneNormal.x << " y:"<< nearestPlaneNormal.y << " z:" << nearestPlaneNormal.z << endl;
		//cout << "change: x:" << change.x << " y:"<< change.y << " z:" << change.z << endl;
		surfaceNormal = nearestPlaneNormal;
		responseDirection = (change || nearestPlaneNormal).normalized() * change.length();
		if (distance < -change.length())
		{
			responseDirection += nearestPlaneNormal * ((-distance) - change.length());
		}
		float responseDot = nearestPlaneNormal * change;
		if (responseDot < -ZERO && responseDot > ZERO)
		{
			responseDirection -= (nearestPlaneNormal * responseDot * 2) * 0.002f; // keep position a bit away to avoid entering into geometry
		}
		//cout << "response: x:" << responseDirection.x << " y:"<< responseDirection.y << " z:" << responseDirection.z << endl;
		return true;
	}
	else
	{
		return false;
	}
}

bool Camera::TestSphereBox(const Vector3f & boxCenter, const Vector3f & boxHalfSize, Quaternionf & boxRotation,
	const Vector3f & spherePos, const float sphereRadius, const Vector3f & sphereVelocity,
	Vector3f & responseDirection, Vector3f & surfaceNormal, 
	float & distance)
{
	auto nextSpherePos = spherePos + sphereVelocity;
	if ((nextSpherePos - boxCenter).length() > sphereRadius + boxHalfSize.length())
	{
		return false;
	}
	else
	{
		//cout<< "--- InSphere" << endl;
		Vector3f biggerSize(boxHalfSize.x + sphereRadius, boxHalfSize.y + sphereRadius, boxHalfSize.z + sphereRadius);
		if (TestPointInsideBox(boxCenter, biggerSize, boxRotation, nextSpherePos, sphereVelocity, responseDirection, surfaceNormal))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

float angleBetween(Vector3f v1,Vector3f v2) { 
	float d = v1.normalized() * v2.normalized();
    return (float)acos(d);
} 

void Camera::RenderArrow(const Vector3f& P, const Vector3f& D, float length, const Vector3f color)
{
	glDisable(GL_LIGHTING);
	glUseProgramObjectARB(0);

	glPushMatrix();
	glTranslatef(P.x, P.y, P.z);
	glScalef(length, length, length);

	glColor3f(color.x, color.y, color.z);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glPopMatrix();

	glEnable(GL_LIGHTING);
}

Vector3f Camera::GetCorrectPosition()
{
	auto correctCameraPosition = Vector3f(position.x, position.y, -position.z) - Vector3f(0, 200.0f, 0);
	return correctCameraPosition;
}

Vector3f Camera::GetCameraDirection(Vector3f nextPosition)
{
	auto cameraDirection = (nextPosition - position);
	return Vector3f(nextPosition.x, nextPosition.y, -nextPosition.z);
}

void Camera::Move(Vector3f direction, vector<p<TmpCollisionObj>> collisionObjects)
{
	Vector3f fixedDirection;
	bool hadcollision = false;
	float radius = 90.0f;
	auto cameraDirection = Vector3f(direction.x, direction.y, -direction.z);
	auto correctCameraPosition = GetCorrectPosition();
	vector<pair<Vector3f, Vector3f>> collisions; // response direction, normal
	Vector3f responseDirection, surfaceNormal;
	float distance;
	for (auto it = collisionObjects.begin(); it != collisionObjects.end(); ++it)
	{
		if (TestSphereBox(it->o()->position, it->o()->size / 2, it->o()->rotation, correctCameraPosition,
			radius, cameraDirection, responseDirection, surfaceNormal, distance))
		{
			hadcollision = true;
			collisions.push_back(pair<Vector3f, Vector3f>(Vector3f(responseDirection.x, responseDirection.y, responseDirection.z), surfaceNormal));
		}
	}
	if (hadcollision)
	{
		//cout << "had collisions" << endl;
		Vector3f sum;
		Vector3f normalSum;
		int number = 0;
		for (auto it = collisions.begin(); it != collisions.end(); ++it)
		{
			if (number > 0)
			{
				sum += it->first;
				normalSum += it->second;
			}
			else
			{
				sum = it->first;
				normalSum = it->second;
			}
			number++;
		}
		if (number == 1)
		{
			if (!isnan(sum.x) && !isnan(sum.y) && !isnan(sum.z))
			{
				position += Vector3f(sum.x, sum.y, -sum.z);
			}
		}
		else
		{
			normalSum.normalize();
			auto result = (sum / (float)number) || normalSum;
			cout << "sum: x:" << sum.x << " y:"<< sum.y << " z:" << sum.z << endl;
			cout << "normal sum: x:" << normalSum.x << " y:"<< normalSum.y << " z:" << normalSum.z << endl;
			cout << "mutual direction: x:" << result.x << " y:"<< result.y << " z:" << result.z << endl;
			if (result.length() < 3000.0f)
			{				
				position += Vector3f(result.x, result.y, -result.z);
			}
		}
	}
	else
	{
		/*Matrix4f m;
		(qHeading * qPitch).to4x4Matrix(&m);*/
		position += Vector3f(direction.x, direction.y, direction.z);
	}
}



void Camera::WalkWithCollision(Vector3f direction, vector<p<TmpCollisionObj>> collisionObjects)
{
	Vector3f fixedDirection;
	bool hadcollision = false;
	float radius = 90.0f;
	auto cameraDirection = GetCameraDirection(GetWalkPosition(direction));
	auto correctCameraPosition = GetCorrectPosition();
	vector<pair<Vector3f, Vector3f>> collisions; // response direction, normal
	Vector3f responseDirection, surfaceNormal;
	float distance;
	for (auto it = collisionObjects.begin(); it != collisionObjects.end(); ++it)
	{
		if (TestSphereBox(it->o()->position, it->o()->size / 2, it->o()->rotation, correctCameraPosition,
			radius, cameraDirection, responseDirection, surfaceNormal, distance))
		{
			hadcollision = true;
			collisions.push_back(pair<Vector3f, Vector3f>(Vector3f(responseDirection.x, responseDirection.y, responseDirection.z), surfaceNormal));
		}
	}
	if (hadcollision)
	{
		Vector3f sum;
		Vector3f normalSum;
		int number = 0;
		for (auto it = collisions.begin(); it != collisions.end(); ++it)
		{
			if (number > 0)
			{
				sum += it->first;
				normalSum += it->second;
			}
			else
			{
				sum = it->first;
				normalSum = it->second;
			}
			number++;
		}
		if (number == 1)
		{
			position += Vector3f(sum.x, sum.y, -sum.z);
		}
		else
		{
			normalSum.normalize();
			auto result = (sum / (float)number) || normalSum;
			//cout << "sum: x:" << sum.x << " y:"<< sum.y << " z:" << sum.z << endl;
			//cout << "normal sum: x:" << normalSum.x << " y:"<< normalSum.y << " z:" << normalSum.z << endl;
			//cout << "mutual direction: x:" << result.x << " y:"<< result.y << " z:" << result.z << endl;
			position += Vector3f(result.x, result.y, -result.z);
		}
	}
	else
	{
		Matrix4f m;
		qHeading.to4x4Matrix(&m);
		position += direction.transform(m);
	}
}

void Camera::GetLookAtMatrix(Vector3f position, Vector3f target, Matrix4f & m)
{
	Vector3f distance = (target - position);
	auto pitchRadians = tan(target.y / (Vector2f(distance.x, distance.z).length()));

	auto pitch = Quaternionf(Vector3f(1.0f, 0.0f, 0.0f), pitchRadians);
	auto direction = Vector3f(position.x, 0, position.z) - Vector3f(target.x, 0, target.z);
	auto angle = angleBetween(Vector3f(0.0f, 0.0f, 1.0f), direction);
	if (direction.x > 0)
		angle = -angle;

	auto heading = Quaternionf(Vector3f(0.0f, 1.0f, 0.0f), angle);

	Quaternionf rotation = pitch * heading;

	rotation.to4x4Matrix(&m);
}

void Camera::ApplyLookAt(Vector3f position, Vector3f target)
{
	Vector3f distance = (target - position);
	auto pitchRadians = tan(target.y / (Vector2f(distance.x, distance.z).length()));

	auto pitch = Quaternionf(Vector3f(1.0f, 0.0f, 0.0f), pitchRadians);
	auto direction = Vector3f(position.x, 0, position.z) - Vector3f(target.x, 0, target.z);
	auto angle = angleBetween(Vector3f(0.0f, 0.0f, 1.0f), direction);
	if (direction.x > 0)
		angle = -angle;

	auto heading = Quaternionf(Vector3f(0.0f, 1.0f, 0.0f), angle);

	Quaternionf rotation = pitch * heading;
	Matrix4f m;

	rotation.to4x4Matrix(&m);
	glMultMatrixf(m.element);
	glTranslatef(-position.x, -position.y, -position.z);
}

void Camera::GetMatrix(Matrix4f & m)
{
	qPitch = Quaternionf(Vector3f(1.0f, 0.0f, 0.0f), pitchRadians);
	qHeading = Quaternionf(Vector3f(0.0f, 1.0f, 0.0f), headingRadians);
	
	// Combine the pitch and heading rotations and store the results in q
	Quaternionf q = qPitch * qHeading;
	q.to4x4Matrix(&m);
}

void Camera::Apply()
{
	/* VEIKIA! tik up yra ne Z o Y */

	Matrix4f m;
	GetMatrix(m);

	glMultMatrixf(m.element);
	
	// Create a matrix from the pitch Quaternion and get the j vector 
	// for our direction.
	/*qPitch.to4x4Matrix(&m);
	directionVector.y = m.element[9]; // m[2][1]

	// Combine the heading and pitch rotations and make a matrix to get
	// the i and j vectors for our direction.
	q = qHeading * qPitch;
	q.to4x4Matrix(&m);
	directionVector.x = m.element[8]; // m[2][0]
	directionVector.z = m.element[10]; // m[2][2]

	// Scale the direction by our speed.
	directionVector *= forwardVelocity;

	// Increment our position by the vector
	position += directionVector;*/

	// Translate to our new position.
	glTranslatef(-position.x, -position.y, position.z);
}

void Camera::SetPitch(float radians)
{
	pitchRadians = radians;
	if(pitchRadians > 2*PI)
	{
		pitchRadians -= 2*PI;
	}
	else if(pitchRadians < -2*PI)
	{
		pitchRadians += 2*PI;
	}
	//cout << "pitch: " << pitchRadians << endl;
}

void Camera::ChangePitch(float radians)
{
	if(fabs(radians) < fabs(maxPitchRate))
	{
		// Our pitch is less than the max pitch rate that we 
		// defined so lets increment it.
		pitchRadians += radians;
	}
	else
	{
		// Our pitch is greater than the max pitch rate that
		// we defined so we can only increment our pitch by the 
		// maximum allowed value.
		if(radians < 0)
		{
			// We are pitching down so decrement
			pitchRadians -= maxPitchRate;
		}
		else
		{
			// We are pitching up so increment
			pitchRadians += maxPitchRate;
		}
	}

	while (pitchRadians > 2*PI)
	{
		pitchRadians -= 2*PI;
	}
	while(pitchRadians < -2*PI)
	{
		pitchRadians += 2*PI;
	}
	//cout << "pitch: " << pitchRadians << endl;
}

void Camera::SetHeading(float radians)
{
	headingRadians = radians;
	if(headingRadians > 2*PI)
	{
		headingRadians -= 2*PI;
	}
	else if(headingRadians < -2*PI)
	{
		headingRadians += 2*PI;
	}
	//cout << "heading: " << headingRadians << endl;
}

void Camera::ChangeHeading(float radians)
{
	if(fabs(radians) < fabs(maxHeadingRate))
	{
		// Our Heading is less than the max heading rate that we 
		// defined so lets increment it but first we must check
		// to see if we are inverted so that our heading will not
		// become inverted.
		if(pitchRadians > PI/2 && pitchRadians < PI/2*3 || (pitchRadians < -PI/2 && pitchRadians > -PI/2*3))
		{
			headingRadians -= radians;
		}
		else
		{
			headingRadians += radians;
		}
	}
	else
	{
		// Our heading is greater than the max heading rate that
		// we defined so we can only increment our heading by the 
		// maximum allowed value.
		if(radians < 0)
		{
			// Check to see if we are upside down.
			if((pitchRadians > PI/2 && pitchRadians < PI/2*3) || (pitchRadians < -PI/2 && pitchRadians > -PI/2*3))
			{
				// Ok we would normally decrement here but since we are upside
				// down then we need to increment our heading
				headingRadians += maxHeadingRate;
			}
			else
			{
				// We are not upside down so decrement as usual
				headingRadians -= maxHeadingRate;
			}
		}
		else
		{
			// Check to see if we are upside down.
			if(pitchRadians > PI/2 && pitchRadians < PI/2*3 || (pitchRadians < -PI/2 && pitchRadians > -PI/2*3))
			{
				// Ok we would normally increment here but since we are upside
				// down then we need to decrement our heading.
				headingRadians -= maxHeadingRate;
			}
			else
			{
				// We are not upside down so increment as usual.
				headingRadians += maxHeadingRate;
			}
		}
	}
	
	while(headingRadians > 2*PI)
	{
		headingRadians -= 2*PI;
	}
	while(headingRadians < -2*PI)
	{
		headingRadians += 2*PI;
	}
	//cout << "heading: " << headingRadians << endl;
}

/*void Camera::SetVelocity(float vel)
{
	forwardVelocity = vel;
	if (forwardVelocity < -maxForwardVelocity)
		forwardVelocity = -maxForwardVelocity;
	else if (forwardVelocity > maxForwardVelocity)
		forwardVelocity = maxForwardVelocity;
	cout << "velocity: " << forwardVelocity << endl;
}

void Camera::ChangeVelocity(float vel)
{
	if(fabs(vel) < fabs(maxForwardVelocity))
	{
		// Our velocity is less than the max velocity increment that we 
		// defined so lets increment it.
		forwardVelocity += vel;
	}
	else
	{
		// Our velocity is greater than the max velocity increment that
		// we defined so we can only increment our velocity by the 
		// maximum allowed value.
		if(vel < 0)
		{
			// We are slowing down so decrement
			forwardVelocity -= -maxForwardVelocity;
		}
		else
		{
			// We are speeding up so increment
			forwardVelocity += maxForwardVelocity;
		}
	}
	cout << "velocity: " << forwardVelocity << endl;
}*/