#include "MultiPass.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0; //通常
    float4 highIntensity : SV_TARGET1; //高輝度
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    output.color = textureColor;
    
    //高輝度を取得
    float y = output.color.r * 0.299 + output.color.g * 0.587 + output.color.b * 0.114;
    if (y > 0.99)
    {
        output.highIntensity = y;
    }
    else
    {
        output.highIntensity = 0.0f;
    }
    
    return output;
}