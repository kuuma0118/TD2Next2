#include "PostProcess.hlsli"

Texture2D<float32_t> gLinearDepthTexture : register(t0);
Texture2D<float32_t4> gTexture : register(t1);
Texture2D<float32_t4> gHighIntensityTexture : register(t2);
Texture2D<float32_t4> gBlurTexture : register(t3);
Texture2D<float32_t4> gHighIntensityBlurTexture : register(t4);
Texture2D<float32_t4> gShrinkBlurTexture : register(t5);
Texture2D<float32_t4> gHighIntensityShrinkBlurTexture : register(t6);
SamplerState gSampler : register(s0);

ConstantBuffer<Bloom> gBloomParameter : register(b0);
ConstantBuffer<Fog> gFogParameter : register(b1);
ConstantBuffer<DoF> gDofParameter : register(b2);
ConstantBuffer<LensDistortion> gLensDistortionParameter : register(b3);
ConstantBuffer<Vignette> gVignetteParameter : register(b4);

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    //深度テクスチャ
    float32_t depthColor = gLinearDepthTexture.Sample(gSampler, input.texcoord);
	//通常テクスチャ
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
	//高輝度テクスチャ
    float32_t4 highIntensityColor = gHighIntensityTexture.Sample(gSampler, input.texcoord);
    //通常ぼかしテクスチャ
    float32_t4 blurColor = gBlurTexture.Sample(gSampler, input.texcoord);
	//高輝度ぼかしテクスチャ
    float32_t4 highIntensityBlurColor = gHighIntensityBlurTexture.Sample(gSampler, input.texcoord);
    //縮小ぼかしテクスチャ
    float32_t4 shrinkBlurColor = gShrinkBlurTexture.Sample(gSampler, input.texcoord);
	//高輝度縮小ぼかしテクスチャ
    float32_t4 highIntensityShrinkBlurColor = gHighIntensityShrinkBlurTexture.Sample(gSampler, input.texcoord);

    
	//レンズディストーション
    if (gLensDistortionParameter.enable == true)
    {
        const float2 uvNormalized = input.texcoord * 2 - 1;
        const float distortionMagnitude = abs(uvNormalized.x * uvNormalized.y);
        const float smoothDistortionMagnitude = pow(distortionMagnitude, gLensDistortionParameter.tightness);
		//const float smoothDistortionMagnitude = 1 - sqrt(1 - pow(distortionMagnitude, gLensDistortionParameter.tightness));
		//const float smoothDistortionMagnitude = pow(sin(1.57079632679f * distortionMagnitude), gLensDistortionParameter.tightness);
        float2 uvDistorted = input.texcoord + uvNormalized * smoothDistortionMagnitude * gLensDistortionParameter.strength;
        if (uvDistorted[0] < 0 || uvDistorted[0] > 1 || uvDistorted[1] < 0 || uvDistorted[1] > 1)
        {
            depthColor = 0.0f;
            textureColor = 0.0f;
            highIntensityColor = 0.0f;
            blurColor = 0.0f;
            highIntensityBlurColor = 0.0f;
            shrinkBlurColor = 0.0f;
            highIntensityShrinkBlurColor = 0.0f;
        }
        else
        {
            depthColor = gLinearDepthTexture.Sample(gSampler, uvDistorted);
            textureColor = gTexture.Sample(gSampler, uvDistorted);
            highIntensityColor = gHighIntensityTexture.Sample(gSampler, uvDistorted);
            blurColor = gBlurTexture.Sample(gSampler, uvDistorted);
            highIntensityBlurColor = gHighIntensityBlurTexture.Sample(gSampler, uvDistorted);
            shrinkBlurColor = gShrinkBlurTexture.Sample(gSampler, uvDistorted);
            highIntensityShrinkBlurColor = gHighIntensityShrinkBlurTexture.Sample(gSampler, uvDistorted);
        }
    }
    

    //Fog
    if (gFogParameter.enable == true)
    {
        float fogWeight = 0.0f;
        fogWeight += gFogParameter.scale * max(0.0f, 1.0f - exp(-gFogParameter.attenuationRate * depthColor));
        const float3 gbColor = textureColor.rgb;
        const float3 gbBlurColor = blurColor.rgb;
        const float3 gbShrinkBlurColor = shrinkBlurColor.rgb;
        const float3 fogColor = 0.8f;
        textureColor.rgb = lerp(gbColor, fogColor, fogWeight);
        blurColor.rgb = lerp(gbBlurColor, fogColor, fogWeight);
        shrinkBlurColor.rgb = lerp(gbShrinkBlurColor, fogColor, fogWeight);
    }
    
    
    //被写界深度
    if (gDofParameter.enable == true)
    {
        float d = 0.0f;
		//if (depthColor > 0.0f && depthColor < 0.5f) {
		//	d = 2 * depthColor;
		//}
		//else if (depthColor > 0.5f && depthColor < 1.0f) {
		//	d = 2 * (1 - depthColor);
		//}
        if (depthColor > 0.0f && depthColor < 0.25f)
        {
            d = 4 * depthColor;
        }
        else if (depthColor > 0.25f && depthColor < 0.75f)
        {
            d = 1.0f;
        }
        else if (depthColor > 0.75f && depthColor < 1.0f)
        {
            d = 4 * (1 - depthColor);
        }
        float coef = 1.0 - d;
        float blur1Coef = coef * d;
        float blur2Coef = coef * coef;
        float4 color = textureColor;
        float4 blur1Color = blurColor;
        float4 blur2Color = shrinkBlurColor;
        textureColor = color * d + blur1Color * blur1Coef + blur2Color * blur2Coef;
    }
    

	//Bloom
    if (gBloomParameter.enable == true)
    {
        float4 color = textureColor;
        textureColor = color + highIntensityColor + highIntensityBlurColor + highIntensityShrinkBlurColor;
    }


	//ビネット
    if (gVignetteParameter.enable)
    {
        float2 uv = input.texcoord;
        uv = gVignetteParameter.intensity * uv - gVignetteParameter.intensity / 2;
        textureColor *= 1.0 - dot(uv, uv);
    }

    output.color = textureColor;
    
    return output;
}