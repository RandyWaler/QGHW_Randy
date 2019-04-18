#include "Basic.hlsli"

// 顶点着色器(3D)
VertexPosHWNormalTex VS(VertexPosNormalTex vIn) 
{
	VertexPosHWNormalTex vOut;
	matrix viewProj = mul(g_View, g_Proj);
	float4 posW = mul(float4(vIn.PosL, 1.0f), g_World);

	vOut.PosH = mul(posW, viewProj);
	vOut.PosW = posW.xyz;
	vOut.NormalW = mul(vIn.NormalL, (float3x3) g_WorldInvTranspose);

	float4 finalTex = mul(float4(vIn.Tex.x, vIn.Tex.y,1.0f,1.0f),g_Rotate);
	vOut.Tex = float2(finalTex.x,finalTex.y);
	//vOut.Tex = vIn.Tex;
	return vOut;
}
//// 顶点着色器(3D)
//VertexPosHTex VS(VertexPosTex vIn)
//{
//	VertexPosHTex vOut;
//	vOut.PosH = mul(float4(vIn.PosL, 1.0f), g_World);  // mul 才是矩阵乘法, 运算符*要求操作对象为
//	vOut.PosH = mul(vOut.PosH, g_View);               // 行列数相等的两个矩阵，结果为
//	vOut.PosH = mul(vOut.PosH, g_Proj);               // Cij = Aij * Bij
//
//	float4 finalTex = mul(float4(vIn.Tex.x, vIn.Tex.y, 1.0f,1.0f), g_Rotate);
//	//vOut.Tex = float2(finalTex.x, finalTex.y);
//	vOut.Tex = vIn.Tex;
//	return vOut;
//}