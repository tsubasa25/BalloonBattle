/*!
 * @brief	�X�t�B�A�R���C�_�[�B
 */

#pragma once

#include "ICollider.h"
#include <memory>
#include <bulletPhysics/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.h>

class CSphereCollider : public ICollider
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="radius"></param>
	/// <param name="height"></param>
	void Init(float radius)
	{
		m_shape = std::make_unique<btSphereShape>(radius);
		m_radius = radius;
	}
	////////////////kinoto
	void ReInit(float radius)
	{
		//m_shape(new btSphereShape(m_radius));
		m_shape.release();
		m_shape = std::make_unique<btSphereShape>(radius);
		//m_radius = radius;
		/*std::unique_ptr<btSphereShape>shape = std::make_unique<btSphereShape>(m_radius);
		m_shape.swap(shape);*/
	}

	/// <summary>
	/// BulletPhysics�̃R���W�����`����擾�B
	/// </summary>
	/// <returns></returns>
	btCollisionShape* GetBody() const override
	{
		return m_shape.get();
	}
	/// <summary>
	/// ���a���擾�B
	/// </summary>
	/// <returns></returns>
	float GetRadius() const
	{
		return m_radius;
	}
	
private:
	std::unique_ptr<btSphereShape>	m_shape;
	float m_radius = 0.0f;	
};
