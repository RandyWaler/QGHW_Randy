#include "Basic.hlsli"


// 像素着色器(3D)
float4 PS(VertexPosHWNormalTex pIn) : SV_Target
{
	//float4 finalTexPoint = mul(float4(pIn.Tex.x, pIn.Tex.y,1.0f ,1.0f), g_Rotate);

    //float4 texColor = g_Tex.Sample(g_SamLinear, float2(finalTexPoint.x, finalTexPoint.y));
    //float4 texColor2 = g_TexB.Sample(g_SamLinear, float2(finalTexPoint.x, finalTexPoint.y));

	float4 texColor = g_Tex.Sample(g_SamLinear, pIn.Tex);
	float4 texColor2 = g_TexB.Sample(g_SamLinear, pIn.Tex);

    return float4(texColor.x*texColor2.x,texColor.y*texColor2.y,texColor.z*texColor2.z,texColor.w*texColor2.w);
}
// 像素着色器(3D)
//float4 PS(VertexPosHTex pIn) : SV_Target
//{
//	//float4 finalTexPoint = mul(float4(pIn.Tex.x, pIn.Tex.y,1.0f ,1.0f), g_Rotate);
//
//	//float4 texColor = g_Tex.Sample(g_SamLinear, float2(finalTexPoint.x, finalTexPoint.y));
//	//float4 texColor2 = g_TexB.Sample(g_SamLinear, float2(finalTexPoint.x, finalTexPoint.y));
//
//	float4 texColor = g_Tex.Sample(g_SamLinear, pIn.Tex);
//	float4 texColor2 = g_TexB.Sample(g_SamLinear, pIn.Tex);
//
//	return texColor2;
//}