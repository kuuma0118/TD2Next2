#include "HorizontalBlur.hlsli"

struct PixelShaderOutput
{
    float4 color : SV_TARGET0; //通常
    float4 highIntensity : SV_TARGET1; //高輝度
};

struct Blur
{
    int32_t textureWidth;
    int32_t textureHeight;
    float4 bkWeight[2];
};

Texture2D<float32_t4> gTexture : register(t0);
Texture2D<float32_t4> gHighIntensityTexture : register(t1);
SamplerState gSampler : register(s0);

ConstantBuffer<Blur> gBlur : register(b0);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    output.color = float4(0, 0, 0, 0);
    output.highIntensity = float4(0, 0, 0, 0);
    float4 color = gTexture.Sample(gSampler, input.texcoord);
    float w = gBlur.textureWidth;
    float h = gBlur.textureHeight;
    float dx = 1.0f / w;
    float dy = 1.0f / h;

    output.color += gBlur.bkWeight[0] * color;
    output.color += gBlur.bkWeight[0][1] * gTexture.Sample(gSampler, input.texcoord + float2(dx * 1, 0));
    output.color += gBlur.bkWeight[0][1] * gTexture.Sample(gSampler, input.texcoord + float2(-dx * 1, 0));
    output.color += gBlur.bkWeight[0][2] * gTexture.Sample(gSampler, input.texcoord + float2(dx * 2, 0));
    output.color += gBlur.bkWeight[0][2] * gTexture.Sample(gSampler, input.texcoord + float2(-dx * 2, 0));
    output.color += gBlur.bkWeight[0][3] * gTexture.Sample(gSampler, input.texcoord + float2(dx * 3, 0));
    output.color += gBlur.bkWeight[0][3] * gTexture.Sample(gSampler, input.texcoord + float2(-dx * 3, 0));
    output.color += gBlur.bkWeight[1][0] * gTexture.Sample(gSampler, input.texcoord + float2(dx * 4, 0));
    output.color += gBlur.bkWeight[1][0] * gTexture.Sample(gSampler, input.texcoord + float2(-dx * 4, 0));
    output.color += gBlur.bkWeight[1][1] * gTexture.Sample(gSampler, input.texcoord + float2(dx * 5, 0));
    output.color += gBlur.bkWeight[1][1] * gTexture.Sample(gSampler, input.texcoord + float2(-dx * 5, 0));
    output.color += gBlur.bkWeight[1][2] * gTexture.Sample(gSampler, input.texcoord + float2(dx * 6, 0));
    output.color += gBlur.bkWeight[1][2] * gTexture.Sample(gSampler, input.texcoord + float2(-dx * 6, 0));
    output.color += gBlur.bkWeight[1][3] * gTexture.Sample(gSampler, input.texcoord + float2(dx * 7, 0));
    output.color += gBlur.bkWeight[1][3] * gTexture.Sample(gSampler, input.texcoord + float2(-dx * 7, 0));
    output.color.a = color.a;
    
    output.highIntensity += gBlur.bkWeight[0] * color;
    output.highIntensity += gBlur.bkWeight[0][1] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(dx * 1, 0));
    output.highIntensity += gBlur.bkWeight[0][1] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(-dx * 1, 0));
    output.highIntensity += gBlur.bkWeight[0][2] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(dx * 2, 0));
    output.highIntensity += gBlur.bkWeight[0][2] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(-dx * 2, 0));
    output.highIntensity += gBlur.bkWeight[0][3] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(dx * 3, 0));
    output.highIntensity += gBlur.bkWeight[0][3] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(-dx * 3, 0));
    output.highIntensity += gBlur.bkWeight[1][0] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(dx * 4, 0));
    output.highIntensity += gBlur.bkWeight[1][0] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(-dx * 4, 0));
    output.highIntensity += gBlur.bkWeight[1][1] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(dx * 5, 0));
    output.highIntensity += gBlur.bkWeight[1][1] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(-dx * 5, 0));
    output.highIntensity += gBlur.bkWeight[1][2] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(dx * 6, 0));
    output.highIntensity += gBlur.bkWeight[1][2] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(-dx * 6, 0));
    output.highIntensity += gBlur.bkWeight[1][3] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(dx * 7, 0));
    output.highIntensity += gBlur.bkWeight[1][3] * gHighIntensityTexture.Sample(gSampler, input.texcoord + float2(-dx * 7, 0));
    output.highIntensity.a = color.a;

    return output;
}