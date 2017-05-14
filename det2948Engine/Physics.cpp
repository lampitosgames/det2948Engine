#include "Physics.h"
#include "Engine.h"
#include "GameObject.h"

//SPHERE VS SPHERE
Manifold Physics::Collide(SphereCollider* A, SphereCollider* B) {
	Manifold m;
	//Sphere collision
	vec3 p1 = A->pos();
	vec3 p2 = B->pos();
	float r1 = A->radius * A->maxScale();
	float r2 = B->radius * B->maxScale();
	//Translation vector pointing from collider A to collider B
	vec3 t = p2 - p1;
	if (dot(t, t) > (r1 + r2)*(r1 + r2)) {
		//Exit early, non-intersecting
		m.norm = vec3();
		return m;
	}
	m.A = A;
	m.B = B;

	float d = length(t);
	
	//Check if spheres are directly on top of each other
	if (d == 0.0f) {
		m.penetration = r1;
		m.norm = vec3(0.0f, 1.0f, 0.0f);
		m.pos = p1;
	//Valid collision
	} else {
		//Cumulative radii minus the distance of collision.
		m.penetration = r1 + r2 - d;
		//Collision normal
		m.norm = t/d;
		//Collision position (adding scaled collision normal to position of sphere one.  This is on the edge of sphere 1 in the direction of the collision)
		m.pos = p1 + (m.norm * r1);
	}
	return m;
}

//AABB VS AABB
Manifold Physics::Collide(AABBCollider* A, AABBCollider* B) {
	Manifold m;
	m.A = A;
	m.B = B;
	vec3 p1 = A->pos();
	vec3 p2 = B->pos();
	vec3 scale1 = A->scale();
	vec3 scale2 = B->scale();

	//Center to corner vectors
	vec3 ctcA = A->corner1 - p1;
	vec3 ctcB = B->corner1 - p2;
	//Scaled ctc vectors
	vec3 eA = vec3(abs(ctcA.x * scale1.x), abs(ctcA.y * scale1.y), abs(ctcA.z * scale1.z));
	vec3 eB = vec3(abs(ctcB.x * scale2.x), abs(ctcB.y * scale2.y), abs(ctcB.z * scale2.z));

	//Vector from A to B
	vec3 t = p2 - p1;

	/*
	If the components overlap on the axis, the boxes are colliding on it
	
	components - _________eA.x     ______________eB.x
	axis       - ________________________________t.x
	
	If collision is true on all 3 axes, the boxes are colliding
	*/
	//Check x axis
	if (abs(t.x) < eA.x + eB.x) {
		//Overlap is calculated by adding the components together and then subtracting the box offset (which will always be less if collision is true)
		float xOverlap = eA.x + eB.x - abs(t.x);
		//Check y axis
		if (abs(t.y) < eA.y + eB.y) {
			float yOverlap = eA.y + eB.y - abs(t.y);
			//Check z axis (if true, collision is happening)
			if (abs(t.z) < eA.z + eB.z) {
				float zOverlap = eA.z + eB.z - abs(t.z);
				//Find the largest overlap
				//Is x smaller than both?
				if (xOverlap < yOverlap && xOverlap < zOverlap) {
					m.penetration = xOverlap;
					if (t.x < 0) {
						m.norm = vec3(-1.0f, 0.0f, 0.0f);
					} else {
						m.norm = vec3(1.0f, 0.0f, 0.0f);
					}
					return m;
				//Either y or z is smallest
				} else if (yOverlap < zOverlap) {
					m.penetration = yOverlap;
					if (t.y < 0) {
						m.norm = vec3(0.0f, -1.0f, 0.0f);
					} else {
						m.norm = vec3(0.0f, 1.0f, 0.0f);
					}
					return m;
				//zOverlap is the smallest
				} else {
					m.penetration = zOverlap;
					if (t.z < 0) {
						m.norm = vec3(0.0f, 0.0f, -1.0f);
					} else {
						m.norm = vec3(0.0f, 0.0f, 1.0f);
					}
					return m;
				}
			}
		}
	}
	//If any axis check proves negative (no overlap), there is no overlap
	m.norm = vec3();
	return m;
}

//AABB VS SPHERE
Manifold Physics::Collide(AABBCollider* A, SphereCollider* B) {
	Manifold m;
	m.A = A;
	m.B = B;
	//Center positions
	vec3 cA = A->pos();
	vec3 cB = B->pos();
	//Scale of the AABB
	vec3 scale1 = A->scale();
	//Radius of the sphere
	float r2 = B->radius * B->maxScale();

	//Center to corner vector
	vec3 ctcA = A->corner1 - cA;
	vec3 eA = vec3(ctcA.x * scale1.x, ctcA.y * scale1.y, ctcA.z * scale1.z);

	//Translation vector from A to B
	vec3 D = cB - cA;

	float nearestX = max(cA.x, min(cB.x, cA.x + (A->halfX * scale1.x)));
	float nearestY = max(cA.y, min(cB.y, cA.y + (A->halfY * scale1.y)));
	float nearestZ = max(cA.z, min(cB.z, cA.z + (A->halfZ * scale1.z)));

	//Get nearest point
	vec3 p = vec3(nearestX, nearestY, nearestZ);
	//Get vector from center of circle to the point on the rectangle
	vec3 Dp = cB - p;

	//If the magnitude of Dp is larger than the circle's radius, then no collision
	if (dot(Dp, Dp) > r2 * r2) {
		m.norm = vec3();
		return m;
	} else {
		m.norm = normalize(Dp);
		if (dot(D, p - cA) < dot(p - cA, p - cA)) {
			m.norm *= -1.0f;
		}
		m.penetration = r2 - length(Dp);
		return m;
	}

}

Physics::Physics() {
}

Physics::~Physics() {
	for (int i = 0; i < colCount; i++) {
		delete colliders[i];
	}
}

bool Physics::Start() {
	return true;
}

void Physics::Update(float dt) {
	colliders;
	for (int i = 0; i < transCount; i++) {
		if (transforms[i].GetGameObject()->isActive) {
			transforms[i].Update(dt);
		}
	}
	for (int i = 0; i < rbCount; i++) {
		if (rigidBodies[i].GetGameObject()->isActive) {
			rigidBodies[i].ApplyGravity(gravity);
			rigidBodies[i].ApplyDrag(airDensity);
			rigidBodies[i].Update(dt);
		}
	}
	//Resolve collisions
	for (int i = 0; i < colCount; i++) {
		colliders[i]->Update(dt);
		for (int k = i; k < colCount; k++) {
			if (k == i) { continue; }
			Manifold m = Collide(colliders[i], colliders[k]);
			if (length(m.norm) < 1.0f) { continue; }

			//Get both rigid bodies
			RigidBody* rb1 = m.A->GetRigidBody();
			RigidBody* rb2 = m.B->GetRigidBody();

			//Get relative velocity
			vec3 rv = rb2->vel - rb1->vel;
			//Get rv along collision normal
			float vAlongNorm = dot(rv, m.norm);
			//If the velocities will already separate objects, do nothing
			if (vAlongNorm > 0.0f) { continue; }
			//Use whichever restitution is smaller
			float e = max(rb1->restitution, rb2->restitution);
			//Impulse
			float j = -(1.0f + e) * vAlongNorm;
			j /= rb1->invMass() + rb2->invMass();
			vec3 impulse = j * m.norm;
			//Apply impulse
			rb1->vel -= rb1->invMass() * impulse;
			rb2->vel += rb2->invMass() * impulse;

			//Positional correction (to account for slight floating point numbers.  This is how we avoid 'sinking').
			//Just decrease penetration depth by 20% before the next velocity update
			float percent = 0.2;
			vec3 correction = m.penetration / (rb1->invMass() + rb2->invMass()) * percent * m.norm;
			m.A->GetTransform()->location -= rb1->invMass() * correction;
			m.B->GetTransform()->location += rb2->invMass() * correction;
		}
	}
}

Handle Physics::Add(int indexPointer, pType type) {
	return Engine::OF.Add(indexPointer, type);
}

Manifold Physics::Collide(Collider* A, Collider* B) {
	if (A->GetRigidBody()->mass == 0 && B->GetRigidBody()->mass == 0) {
		Manifold m;
		m.norm = vec3();
		return m;
	}

	//Both colliders are sphere colliders
	if (A->type == colType::SPHERE_COL && B->type == colType::SPHERE_COL) {
		return Collide((SphereCollider*)A, (SphereCollider*)B);
	//Both colliders are AABB colliders
	} else if (A->type == colType::AABB_COL && B->type == colType::AABB_COL) {
		return Collide((AABBCollider*)A, (AABBCollider*)B);
	//Collider 'A' is an AABB collider and collider 'B' is a sphere collider
	} else if (A->type == colType::AABB_COL && B->type == colType::SPHERE_COL) {
		return Collide((AABBCollider*)A, (SphereCollider*)B);
	//Collider 'A' is a sphere collider and collider 'B' is an AABB collider
	} else if (A->type == colType::SPHERE_COL && B->type == colType::AABB_COL) {
		return Collide((AABBCollider*)B, (SphereCollider*)A);

	//Collision types are not properly handled
	} else {
		Manifold m;
		m.norm = vec3();
		return m;
	}
}

template<typename T>
inline T Physics::Get(Handle h) {
	return Engine::OF.Get<T>(h);
}

/*

COMPONENTS

*/
Handle Physics::CreateTransform(vec3 inLoc, vec3 inRot, vec3 inScl) {
	transforms.push_back(Transform(inLoc, inRot, inScl));
	transCount += 1;
	Handle transformHandle = Add(transCount - 1, pType::TRANSFORM);
	transforms[transCount - 1].handle = transformHandle;
	transforms[transCount - 1].index = transCount - 1;
	transforms[transCount - 1].Start();
	return transformHandle;
}

Handle Physics::CreateRigidBody(float mass, vec3 vel, float restitution) {
	rigidBodies.push_back(RigidBody(mass, vel, restitution));
	rbCount += 1;
	Handle rigidBodyHandle = Add(rbCount - 1, pType::RIGID_BODY);
	rigidBodies[rbCount - 1].handle = rigidBodyHandle;
	rigidBodies[rbCount - 1].index = rbCount - 1;
	rigidBodies[rbCount - 1].Start();
	return rigidBodyHandle;
}

Handle Physics::CreateSphereCollider(float radius) {
	SphereCollider* col = new SphereCollider(radius);
	colliders.push_back(col);
	colCount += 1;
	Handle sphereColliderHandle = Add(colCount - 1, pType::COLLIDER);
	col->handle = sphereColliderHandle;
	col->index = colCount - 1;
	col->Start();
	return sphereColliderHandle;
}

Handle Physics::CreateAABBCollider(vec3 center, vec3 corner1, vec3 corner2) {
	//This is a wrapper function
	return CreateAABBCollider(center, abs(corner1.x - corner2.x), abs(corner1.y - corner2.y), abs(corner1.z - corner2.z));
}

Handle Physics::CreateAABBCollider(vec3 center, float xSize, float ySize, float zSize) {
	AABBCollider* col = new AABBCollider(center, xSize, ySize, zSize);
	colliders.push_back(col);
	colCount += 1;
	Handle aabbColliderHandle = Add(colCount - 1, pType::COLLIDER);
	col->handle = aabbColliderHandle;
	col->index = colCount - 1;
	col->Start();
	return aabbColliderHandle;
}
