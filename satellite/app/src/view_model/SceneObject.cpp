#include "view_model/SceneObject.h"

SceneObject::SceneObject()
	: m_transformMat(1.0f)
{
}

void SceneObject::SetDeleter(const ObjectDeleter& deleter)
{
	m_deleter = deleter;
}

void SceneObject::Draw(int width, int height)
{
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_model", m_transformMat);
	DoDraw(width, height);
}

void SceneObject::DestroySelf()
{
	m_deleter(this);
}

void SceneObject::Transform(const glm::mat4& mat)
{
	m_transformMat = mat;
}