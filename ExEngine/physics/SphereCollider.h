/*!
 * @brief	スフィアコライダー。
 */

#pragma once

#include "ICollider.h"
#include <memory>
#include <bulletPhysics/src/BulletCollision/CollisionDispatch/SphereTriangleDetector.h>

class CSphereCollider : public ICollider
{
public:
	/// <summary>
	/// 初期化
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
	/// BulletPhysicsのコリジョン形状を取得。
	/// </summary>
	/// <returns></returns>
	btCollisionShape* GetBody() const override
	{
		return m_shape.get();
	}
	/// <summary>
	/// 半径を取得。
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
