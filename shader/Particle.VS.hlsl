#include "Particle.hlsli"

struct ParticleForGPU
{
    float32_t4x4 world;
    float32_t4 color;
};

struct ViewProjection
{
    float32_t4x4 view;
    float32_t4x4 projection;
};

StructuredBuffer<ParticleForGPU> gParticle : register(t0);
ConstantBuffer<ViewProjection> gViewProjection : register(b1);

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
};

VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    output.position = mul(input.position, mul(gParticle[instanceId].world, mul(gViewProjection.view, gViewProjection.projection)));
    output.texcoord = input.texcoord;
    output.normal = normalize(mul(input.normal, (float32_t3x3) gParticle[instanceId].world));
    output.color = gParticle[instanceId].color;

    return output;
}