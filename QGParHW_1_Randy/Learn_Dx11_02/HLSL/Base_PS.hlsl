#include "Base.hlsli"
// ������ɫ��
float4 PS(VertexOut pIn) : SV_Target//�������ɫֵ����ֱ�ӱ��浽��ȾĿ����ͼ�ĺ󱸻�������Ӧλ��
{
	return pIn.color;
}