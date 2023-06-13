#pragma once

#include "core/core.h"

#include "Scene.h"
#include "SceneLayer.h"

class ImGuiOverlay : public core::Layer
{
public:
	ImGuiOverlay(Scene& scene, SceneLayer& sceneLayer);

private:
	// Inherited via Layer
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(core::Timestep ts);

	void OnRender();

	void AddSpherePopup();
	void AddPlanePopup();
	void AddTorusPopup();
	void AddPointLightPopup();

	void SubmitNewObject(const std::string& label, std::unique_ptr<ISceneObject>&& object);

	class TransformEdit
	{
	public:
		void operator()(const char* label, glm::mat4* resultMatrix);

	private:
		glm::mat4 BuildTransformMatrix() const;

		glm::vec3 m_translate{ 0.0f };
		glm::vec3 m_scale{ 1.0f };
		glm::vec3 m_rotateAxis{ 1.0f, 0.0f, 0.0f };
		float m_rotateAngle = 0.0f;
	};

	class SceneObjectNode
	{
	public:
		SceneObjectNode(
			const std::string& title,
			int objectIndex,
			glm::vec3 color,
			glm::mat4 transform
		);

		/*
		Returns 'true' if node should be removed afterwards.
		*/
		bool OnRender();

		inline static ImGuiOverlay* s_overlay;

	private:
		void HandleColorChange(bool submit);
		void HandleTransformChange(bool submit);

		TransformEdit m_transformEdit;
		glm::vec3 m_color, m_cachedColor;
		glm::mat4 m_transform, m_cachedTransform;
		std::string m_title;
		int m_objectIndex;
	};

	Scene& m_scene;
	SceneLayer& m_sceneLayer;

	std::vector<SceneObjectNode> m_sceneObjectNodes;
};
