#pragma once

#include "ICollider.h"

/*!
	* @brief	ボックスコライダー。
	*/
class BoxCollider : public ICollider
{
public:

	void Create( const btVector3& size ) {		
		shape = std::make_unique<btBoxShape>(size);
	}
	/*void ReCreate(const Vector3& size){
		shape.release();
		shape = std::make_unique<btBoxShape>(size);
	}*/
	btCollisionShape* GetBody() const override
	{
		return shape.get();
	}
private:
	std::unique_ptr<btBoxShape>		shape;
	Vector3 m_size = Vector3::Zero;
};
