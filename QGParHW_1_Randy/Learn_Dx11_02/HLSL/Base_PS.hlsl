#include "Base.hlsli"
// 像素着色器
float4 PS(VertexOut pIn) : SV_Target//输出的颜色值将会直接保存到渲染目标视图的后备缓冲区对应位置
{
	return pIn.color;
}