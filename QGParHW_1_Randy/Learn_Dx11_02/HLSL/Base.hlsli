struct VertexIn //������ɫ������ṹ��
{
	float3 pos : POSITION; //����λ�� float3->���������(x,y,z)
	float4 color : COLOR;//��ɫ float4->��ɫ(RGBA)
};

struct VertexOut //������ɫ������ṹ��
{
	float4 posH : SV_POSITION;//������ɫ�������޸ĸ������� λ��ֵ ��Ϊ��դ��������λ�� ������Ϊfloat(x,y,z,d)
	float4 color : COLOR;//��ɫ float4->��ɫ(RGBA)
};