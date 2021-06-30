#include "stdafx.h"
#include "ExEngine.h"
#include "RigidBody.h"


void RigidBody::Init(RigidBodyInitData& m_initData)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(m_initData.pos.x, m_initData.pos.y, m_initData.pos.z));
	transform.setRotation(btQuaternion(m_initData.rot.x, m_initData.rot.y, m_initData.rot.z, m_initData.rot.w));

	m_myMotionState = std::make_unique<btDefaultMotionState>();
	m_myMotionState->setWorldTransform(transform);
	btVector3 btLocalInteria;
	btLocalInteria.setX(m_initData.localInteria.x);
	btLocalInteria.setY(m_initData.localInteria.y);
	btLocalInteria.setZ(m_initData.localInteria.z);
	
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(m_initData.mass, m_myMotionState.get(), m_initData.collider->GetBody(), btLocalInteria);
	m_rigidBody = std::make_unique<btRigidBody>(btRbInfo);
	
	PhysicsWorld::GetInstance()->AddRigidBody(*this);
}
void RigidBody::ReInit(RigidBodyInitData& m_initData)
{
	if (m_rigidBody) {
		PhysicsWorld::GetInstance()->RemoveRigidBody(*this);
	}
	PhysicsWorld::GetInstance()->RemoveRigidBody(*this);
	btTransform transform;
	transform.setIdentity();	
	transform.setOrigin(btVector3(m_initData.pos.x, m_initData.pos.y, m_initData.pos.z));
	transform.setRotation(btQuaternion(m_initData.rot.x, m_initData.rot.y, m_initData.rot.z, m_initData.rot.w));
	
	m_myMotionState->setWorldTransform(transform);
	btVector3 btLocalInteria;
	btLocalInteria.setX(m_initData.localInteria.x);
	btLocalInteria.setY(m_initData.localInteria.y);
	btLocalInteria.setZ(m_initData.localInteria.z);

	btRigidBody::btRigidBodyConstructionInfo btRbInfo(m_initData.mass, m_myMotionState.get(), m_initData.collider->GetBody(), btLocalInteria);
	//std::unique_ptr<btRigidBody>rigidBody = std::make_unique<btRigidBody>(btRbInfo);
	/*m_rigidBody.swap(rigidBody);
	m_rigidBody.reset(new btRigidBody(btRbInfo));*/
	//m_rigidBody.release();
	m_rigidBody = std::make_unique<btRigidBody>(btRbInfo);
	PhysicsWorld::GetInstance()->AddRigidBody(*this);
}
RigidBody::~RigidBody()
{
	if (m_rigidBody) {
		PhysicsWorld::GetInstance()->RemoveRigidBody(*this);
	}
}