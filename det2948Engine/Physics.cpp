#include "Physics.h"
#include "Engine.h"
#include "GameObject.h"

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
		for (int k = i; k < colCount; k++) {
			if (k == i) { continue; }
			Manifold m = Collide(&colliders[i], &colliders[k]);
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
			float e = min(rb1->restitution, rb2->restitution);
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

//Manifold Physics::Collide(Collider* A, Collider* B) {
//	if (A->type == colType::SPHERE_COL && B->type == colType::SPHERE_COL) {
//		return Collide((SphereCollider*) A, (SphereCollider*) B);
//	} else {
//		Manifold m;
//		m.norm = vec3();
//		return m;
//	}
//}

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
	//SphereCollider* col = &SphereCollider(radius);
	colliders.push_back(SphereCollider(radius));
	colCount += 1;
	Handle sphereColliderHandle = Add(colCount - 1, pType::COLLIDER);
	colliders[colCount - 1].handle = sphereColliderHandle;
	colliders[colCount - 1].index = rbCount - 1;
	colliders[colCount - 1].Start();
	return sphereColliderHandle;
}
