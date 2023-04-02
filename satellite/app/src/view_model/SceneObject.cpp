#include "view_model/SceneObject.h"

SceneObject::SceneObject()
	: m_transformMat(1.0f)
{
}

void SceneObject::SetRemoveCallback(const RemoveCallback& deleter)
{
	m_removeCallback = deleter;
}

void SceneObject::Draw(int width, int height)
{
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_model", m_transformMat);
	DoDraw(width, height);
}

void SceneObject::RemoveSelf()
{
	m_removeCallback(this);
}

void SceneObject::Transform(const glm::mat4& mat)
{
	m_transformMat = mat;
}
