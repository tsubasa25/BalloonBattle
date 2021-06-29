/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#pragma once

#include "ICollider.h"


class CCapsuleCollider : public ICollider
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="radius"></param>
	/// <param name="height"></param>
	void Init(float radius)
	{
		m_shape = std::make_unique<btCapsuleShape>(radius, radius);
		m_radius = radius;
		m_height = radius;
	}
	////////////////kinoto
	void ReInit(float radius)
	{		
		m_shape.release();
		m_shape = std::make_unique<btCapsuleShape>(radius, radius);
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
	/// <summary>
	/// �������擾�B
	/// </summary>
	/// <returns></returns>
	float GetHeight() const
	{
		return m_height;
	}
private:
	std::unique_ptr<btCapsuleShape>	m_shape;
	float m_radius = 0.0f;
	float m_height = 0.0f;
};
