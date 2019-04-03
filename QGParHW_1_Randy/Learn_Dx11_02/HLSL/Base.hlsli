struct VertexIn //顶点着色器传入结构体
{
	float3 pos : POSITION; //顶点位置 float3->坐标点描述(x,y,z)
	float4 color : COLOR;//颜色 float4->颜色(RGBA)
};

struct VertexOut //顶点着色器输出结构体
{
	float4 posH : SV_POSITION;//后续着色器不得修改该输出后的 位置值 作为光栅化的最终位置 输出后变为float(x,y,z,d)
	float4 color : COLOR;//颜色 float4->颜色(RGBA)
};