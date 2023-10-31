struct VertexShaderOutput {
	float32_t4 position : SV_POSITION;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
};

struct Material {
	float32_t4 color;
	int32_t enableLightning;
	float32_t4x4 uvTransform;
};

struct TransformationMatrix {
	float32_t4x4 WVP;
	float32_t4x4 World;
};

struct PixelShaderOutput {
	float32_t4 color : SV_TARGET0;
};

struct VertexShaderInput {
	float32_t4 position : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
};

struct DirectionalLight {
	float32_t4 color;
	float32_t3 direction;
	float intensity;
};