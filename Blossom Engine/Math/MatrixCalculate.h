#pragma once

#include <math.h>
#include "Matrix4x4.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include <stdint.h>

#include "../Blossom Engine/utility/MaterialData.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Transform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

struct VertexData {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};

struct Material {
	Vector4 color;
	int32_t enableLightning;
	float padding[3];
	Matrix4x4 uvTransform;
};

struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
};

struct DirectionalLight {
	Vector4 color;
	Vector3 direction;
	float intensity;
};

//struct MaterialData {
//	std::string textureFilePath;
//};

struct ModelData {
	std::vector<VertexData> verticles;
	MaterialData material;
};

Matrix4x4 MakeRotateXMatrix(float theta);
Matrix4x4 MakeRotateYMatrix(float theta);
Matrix4x4 MakeRotateZMatrix(float theta);

Matrix4x4 MakeRotateMatrix(const Vector3& radian);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Vector3 Normalize(const Vector3& v);

float Length(const Vector3& v);

float Dot(const Vector3& v1, const Vector3& v2);

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

Vector3 V3Add(const Vector3& pos, const Vector3& vector);

Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Inverse(const Matrix4x4& m);

Matrix4x4 Transpose(const Matrix4x4& m);

Matrix4x4 MakeIdentity4x4();

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

float cot(float theta);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);