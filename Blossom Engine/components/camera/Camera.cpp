#include "Camera.h"
#include "../Blossom Engine/WinApp/WinApp.h"
#include "../ImGui/ImGuiManager.h"
#include "../Blossom Engine/Math/Matrix4x4.h"
//#include "../camera/DebugCamera.h"
#include "DebugCamera.h"

Camera* Camera::GetInstance() {
	static Camera instance;

	return &instance;
}

void Camera::Initialize() {
	worldTransform_ = {
	{1.0f,1.0f,1.0f},
	{0.0f,0.0f,0.0f},
	{0.0f,0.0f,0.0f}
	};
	cameraTransform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,-10.0f}
	};
}

void Camera::SettingCamera() {
	worldMatrix_ = MakeAffineMatrix(worldTransform_.scale, worldTransform_.rotate, worldTransform_.translate);
	/*cameraMatrix_ = MakeAffineMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	viewMatrix_ = Inverse(cameraMatrix_);*/
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, (float)WinApp::kClientWidth / (float)WinApp::kClientHeight, 0.1f, 100.0f);
	worldViewProjectionMatrix_ = Multiply(worldMatrix_, Multiply(DebugCamera::GetInstance()->GetViewMatrix(), projectionMatrix_));
	transformationMatrixData_ = &worldViewProjectionMatrix_;
}

void Camera::DrawDebugParameter() {
	ImGui::Text("Camera");
	ImGui::SliderFloat3("Camera.Translate", &cameraTransform_.translate.x, -10, 10);
	ImGui::DragFloat3("Camera.Rotate", &cameraTransform_.rotate.x,0.01f ,-6.28f, 6.28f);
}