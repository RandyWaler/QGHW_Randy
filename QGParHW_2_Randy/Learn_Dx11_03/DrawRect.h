#pragma once
class DrawRect
{
private:
	int nowState = 0;//当前阶段值
	int nowPointNum = 0;//当前需要呈现的顶点数量
public:

//初始化
	DrawRect();
	~DrawRect();
//更新
	void rectUpdate(float dt);
//Get
	int getPointNum();
};

