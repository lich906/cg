#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/type_ptr.hpp>

#include "ImGuiOverlay.h"
#include "Sphere.h"
#include <Plane.h>
#include <Torus.h>

ImGuiOverlay::ImGuiOverlay(Scene& scene, SceneLayer& sceneLayer)
	: Layer("ImGui Overlay")
	, m_scene(scene)
	, m_sceneLayer(sceneLayer)
{
	ImGuiOverlay::SceneObjectNode::s_overlay = this;
}

void ImGuiOverlay::OnAttach()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	core::Application& app = core::Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void ImGuiOverlay::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiOverlay::OnUpdate(core::Timestep)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	OnRender();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiOverlay::OnRender()
{
	if (ImGui::Begin("Main Menu", NULL, ImGuiWindowFlags_MenuBar))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Add object"))
			{
				if (ImGui::Button("Plane      "))
					ImGui::OpenPopup("AddPlanePopup");
				if (ImGui::Button("Sphere     "))
					ImGui::OpenPopup("AddSpherePopup");
				if (ImGui::Button("Torus      "))
					ImGui::OpenPopup("AddTorusPopup");

				AddSpherePopup();
				AddPlanePopup();
				AddTorusPopup();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Add light source"))
			{
				if (ImGui::Button("Point light"))
					ImGui::OpenPopup("AddPointLightPopup");

				AddPointLightPopup();

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (ImGui::CollapsingHeader("Scene"))
		{
			for (size_t i = 0; i < m_sceneObjectNodes.size(); i++)
			{
				if (m_sceneObjectNodes[i].OnRender())
					m_sceneObjectNodes.erase(m_sceneObjectNodes.begin() + i);
			}
		}

		ImGui::End();
	}
}

void ImGuiOverlay::AddSpherePopup()
{
	static glm::vec3 color;
	static glm::mat4 transform(1.0f);
	static TransformEdit transformEdit;

	if (ImGui::BeginPopup("AddSpherePopup"))
	{
		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		transformEdit("Transform", &transform);

		if (ImGui::Button("Add"))
		{
			auto sphere = std::make_unique<Sphere>();
			sphere->SetMaterial(Material(color));
			sphere->SetTransform(transform);
			SubmitNewObject("Sphere", std::move(sphere), transformEdit);
		}

		ImGui::EndPopup();
	}
}

void ImGuiOverlay::AddPlanePopup()
{
	static glm::vec3 color;
	static glm::mat4 transform(1.0f);
	static glm::vec3 normal;
	static TransformEdit transformEdit;

	if (ImGui::BeginPopup("AddPlanePopup"))
	{
		ImGui::SliderFloat3("Normal", glm::value_ptr(normal), -1.0f, 1.0f, "%.2f");
		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		transformEdit("Transform", &transform);

		if (ImGui::Button("Add"))
		{
			auto plane = std::make_unique<Plane>(glm::normalize(normal));
			plane->SetMaterial(Material(color));
			plane->SetTransform(transform);
			SubmitNewObject("Plane", std::move(plane), transformEdit);
		}

		ImGui::EndPopup();
	}
}

void ImGuiOverlay::AddTorusPopup()
{
	static float r, R;
	static glm::vec3 color;
	static glm::mat4 transform(1.0f);
	static TransformEdit transformEdit;
	
	if (ImGui::BeginPopup("AddTorusPopup"))
	{
		ImGui::SliderFloat("Tube radius", &r, 0.01f, 100.0f);
		ImGui::SliderFloat("Torus radius", &R, 0.01f, 100.0f);
		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		transformEdit("Transform", &transform);

		if (ImGui::Button("Add"))
		{
			auto torus = std::make_unique<Torus>(R, r);
			torus->SetMaterial(Material(color));
			torus->SetTransform(transform);
			SubmitNewObject("Torus", std::move(torus), transformEdit);
		}

		ImGui::EndPopup();
	}
}

void ImGuiOverlay::AddPointLightPopup()
{
	static float intensity;
	static glm::vec3 color, position;

	if (ImGui::BeginPopup("AddPointLightPopup"))
	{
		ImGui::DragFloat("Intensity", &intensity, 0.01f, 0.01f, 10.0f);
		ImGui::ColorEdit3("Light color", glm::value_ptr(color));
		ImGui::DragFloat3("Position", glm::value_ptr(position), 0.01f, -10000.0f, 10000.0f, "%.2f");

		if (ImGui::Button("Add"))
		{
			PointLight light;
			light.Intensity = intensity;
			light.LightColor = color;
			light.Position = position;
			m_scene.AddPointLight(light);
			m_sceneLayer.ForceNextRender();
		}

		ImGui::EndPopup();
	}
}

void ImGuiOverlay::SubmitNewObject(const std::string& label, std::unique_ptr<ISceneObject>&& object, const TransformEdit& transformEdit)
{
	glm::mat4 transform = object->GetTransform();
	glm::vec3 color = object->GetMaterial().Color;
	int index = m_scene.AddObject(std::move(object));
	m_sceneLayer.ForceNextRender();
	m_sceneObjectNodes.push_back(SceneObjectNode(
		"[" + std::to_string(index) + "]" + label,
		index, color, transform, transformEdit));
}

ImGuiOverlay::SceneObjectNode::SceneObjectNode(
	const std::string& title,
	int objectIndex,
	glm::vec3 color,
	glm::mat4 transform,
	const TransformEdit& transformEdit
)
	: m_title(title)
	, m_objectIndex(objectIndex)
	, m_object(&s_overlay->m_scene.GetObject(objectIndex))
	, m_transformEdit(transformEdit)
{
	m_color = m_object->GetMaterial().Color;
	m_transform = m_object->GetTransform();
}

bool ImGuiOverlay::SceneObjectNode::OnRender()
{
	if (ImGui::TreeNode(m_title.c_str()))
	{
		ImGui::ColorEdit3("Color", glm::value_ptr(m_color));
		m_transformEdit("Transform", &m_transform);

		if (m_color != m_object->GetMaterial().Color || m_transform != m_object->GetTransform())
		{
			bool submit = ImGui::Button("Submit");
			ImGui::SameLine();
			HandleColorChange(submit);
			HandleTransformChange(submit);
		}

		if (ImGui::Button("Remove"))
		{
			s_overlay->m_scene.RemoveObject(m_objectIndex);
			s_overlay->m_sceneLayer.ForceNextRender();
			return true;
		}

		ImGui::TreePop();
	}

	return false;
}

void ImGuiOverlay::SceneObjectNode::HandleColorChange(bool submit)
{
	if ((m_color != m_object->GetMaterial().Color) && submit)
	{
		s_overlay->m_scene.GetObject(m_objectIndex).SetMaterial(Material(m_color));
		s_overlay->m_sceneLayer.ForceNextRender();
	}
}

void ImGuiOverlay::SceneObjectNode::HandleTransformChange(bool submit)
{
	if ((m_transform != m_object->GetTransform()) && submit)
	{
		s_overlay->m_scene.GetObject(m_objectIndex).SetTransform(m_transform);
		s_overlay->m_sceneLayer.ForceNextRender();
	}
}

ImGuiOverlay::TransformEdit::TransformEdit(const glm::vec3& translate, const glm::vec3& scale, const glm::vec3& rotateAxis, float rotateAngle)
	: m_translate(translate)
	, m_scale(scale)
	, m_rotateAxis(rotateAxis)
	, m_rotateAngle(rotateAngle)
{
}

void ImGuiOverlay::TransformEdit::operator()(const char* label, glm::mat4* resultMatrix)
{
	if (ImGui::TreeNode(label))
	{
		if (ImGui::DragFloat3("Translate", glm::value_ptr(m_translate), 0.01f, -10000.0f, 10000.0f, "%.2f"))
			*resultMatrix = BuildTransformMatrix();
		if (ImGui::DragFloat3("Scale", glm::value_ptr(m_scale), 0.01f, -10000.0f, 10000.0f, "%.2f"))
			*resultMatrix = BuildTransformMatrix();
		if (ImGui::DragFloat3("Rotate Axis", glm::value_ptr(m_rotateAxis), 0.01f, -1.0f, 1.0f, "%.2f"))
			*resultMatrix = BuildTransformMatrix();
		if (ImGui::DragFloat("Rotate Angle", &m_rotateAngle, 0.1f, 0.0f, 360.0f, "%.1f"))
			*resultMatrix = BuildTransformMatrix();

		ImGui::TreePop();
	}
}

glm::mat4 ImGuiOverlay::TransformEdit::BuildTransformMatrix() const
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_translate);
	transform = glm::rotate(transform, glm::radians(m_rotateAngle), glm::normalize(m_rotateAxis));
	transform = glm::scale(transform, m_scale);
	return transform;
}
