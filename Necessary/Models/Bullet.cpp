#include "Bullet.h"
#include <iostream>
#include <cmath>
#define PI 3.14159265358979323846f
Microsoft::WRL::ComPtr<ID3D12Resource> Bullet::CreateBufferResource(const Microsoft::WRL::ComPtr<ID3D12Device>& device, size_t sizeInBytes) {
	HRESULT hr;
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC vertexResourceDesc{};

	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = sizeInBytes;

	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;

	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;

	hr = device.Get()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexResource));
	assert(SUCCEEDED(hr));

	return vertexResource;
}

void Bullet::CreateVertexResource() {
	vertexResource_ = CreateBufferResource(DirectXCommon::GetInstance()->GetDevice(), sizeof(VertexData) * modelData_.verticles.size()).Get();
}

void Bullet::CreateVertexBufferView() {

	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();

	vertexBufferView_.SizeInBytes = sizeof(VertexData) * UINT(modelData_.verticles.size());

	vertexBufferView_.StrideInBytes = sizeof(VertexData);
}

void Bullet::CreateMaterialResource() {
	materialResource_ = CreateBufferResource(DirectXCommon::GetInstance()->GetDevice(), sizeof(Material)).Get();

	materialData_ = nullptr;

	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
}

void Bullet::CreateWvpResource() {

	transformationMatrixResource_ = CreateBufferResource(DirectXCommon::GetInstance()->GetDevice(), sizeof(TransformationMatrix)).Get();

	transformationMatrixResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixData_));

	transformationMatrixData_->WVP = MakeIdentity4x4();
}

void Bullet::Initialize() {

	modelData_ = ObjManager::GetInstance()->GetObjModelData()[bullet];

	CreateVertexResource();

	CreateMaterialResource();

	CreateWvpResource();

	CreateVertexBufferView();

	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
	std::memcpy(vertexData_, modelData_.verticles.data(), sizeof(VertexData) * modelData_.verticles.size());

	transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	speed = 0.05f;
	angle = 90.0f;
	rotationAngle = 0.0f;
	rotateAmount = 0.0f;
	uvTransform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	materialData_->enableLightning = false;

	materialData_->uvTransform = MakeIdentity4x4();
}

void Bullet::Update() {
	trueangle = angle * (PI / 180.0f);
	float vx = speed * cos(trueangle);
	float vy = speed * sin(trueangle);
	transform.translate.x += vx;
	transform.translate.y += vy;
}

void Bullet::Draw() {
	uvTransformMatrix_ = MakeScaleMatrix(uvTransform_.scale);
	uvTransformMatrix_ = Multiply(uvTransformMatrix_, MakeRotateZMatrix(uvTransform_.rotate.z));
	uvTransformMatrix_ = Multiply(uvTransformMatrix_, MakeTranslateMatrix(uvTransform_.translate));
	materialData_->uvTransform = uvTransformMatrix_;

	//transform_.rotate.y += 0.006f;
	transformationMatrixData_->World = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);

	transformationMatrixData_->WVP = Multiply(transformationMatrixData_->World, *Camera::GetInstance()->GetTransformationMatrixData());
	transformationMatrixData_->World = MakeIdentity4x4();

	materialData_->color = { 1.0f,1.0f,1.0f,1.0f };

	DirectXCommon::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);

	DirectXCommon::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootDescriptorTable(2, TextureManager::GetInstance()->GetTextureSrvHandleGPU()[textureNum]);

	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResource_.Get()->GetGPUVirtualAddress());

	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(3, Light::GetInstance()->GetDirectionalLightResource()->GetGPUVirtualAddress());

	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_.Get()->GetGPUVirtualAddress());
	DirectXCommon::GetInstance()->GetCommandList()->DrawInstanced(UINT(modelData_.verticles.size()), 1, 0, 0);
}
