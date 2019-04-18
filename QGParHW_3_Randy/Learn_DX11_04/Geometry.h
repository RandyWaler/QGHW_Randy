//***************************************************************************************
// Geometry.h by X_Jun(MKXJun) (C) 2018-2019 All Rights Reserved.
// Licensed under the MIT License.
//
// 生成常见的几何体网格模型
// Generate common geometry meshes.
//***************************************************************************************

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>
#include <string>
#include <map>
#include "Vertex.h"

class Geometry
{
public:
	// 网格数据
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	struct MeshData
	{
		std::vector<VertexType> vertexVec;	// 顶点数组
		std::vector<IndexType> indexVec;	// 索引数组

		MeshData()
		{
			// 需检验索引类型合法性
			static_assert(sizeof(IndexType) == 2 || sizeof(IndexType) == 4, "The size of IndexType must be 2 bytes or 4 bytes!");
			static_assert(std::is_unsigned<IndexType>::value, "IndexType must be unsigned integer!");
		}
	};




	// 创建立方体网格数据
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> CreateBox(float width = 2.0f, float height = 2.0f, float depth = 2.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// 创建一个覆盖NDC屏幕的面
	template<class VertexType = VertexPosTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> Create2DShow(float centerX = 0.0f, float centerY = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });


private:
	struct VertexData
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT4 tangent;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 tex;
	};

	template<class VertexType>
	static void InsertVertexElement(VertexType& vertexDst, const VertexData& vertexSrc);

private:
	static const std::map<std::string, std::pair<size_t, size_t>> semanticSizeMap;
};






//
// 几何体方法的实现
//

// 根据目标顶点类型选择性将数据插入
template<class VertexType>
inline void Geometry::InsertVertexElement(VertexType& vertexDst, const VertexData& vertexSrc)
{
	static std::string semanticName;
	for (size_t i = 0; i < ARRAYSIZE(VertexType::inputLayout); i++)
	{
		semanticName = VertexType::inputLayout[i].SemanticName;
		const auto& range = Geometry::semanticSizeMap.at(semanticName);
		memcpy_s(reinterpret_cast<char*>(&vertexDst) + VertexType::inputLayout[i].AlignedByteOffset,
			range.second - range.first,
			reinterpret_cast<const char*>(&vertexSrc) + range.first,
			range.second - range.first);
	}
}



template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::CreateBox(float width, float height, float depth, const DirectX::XMFLOAT4 & color)
{
	using namespace DirectX;

	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(24);


	VertexData vertexDataArr[24];
	float w2 = width / 2, h2 = height / 2, d2 = depth / 2;


	// 顶面
	vertexDataArr[0].pos = XMFLOAT3(-w2, h2, -d2);
	vertexDataArr[1].pos = XMFLOAT3(-w2, h2, d2);
	vertexDataArr[2].pos = XMFLOAT3(w2, h2, d2);
	vertexDataArr[3].pos = XMFLOAT3(w2, h2, -d2);
	// 底面
	vertexDataArr[4].pos = XMFLOAT3(w2, -h2, -d2);
	vertexDataArr[5].pos = XMFLOAT3(w2, -h2, d2);
	vertexDataArr[6].pos = XMFLOAT3(-w2, -h2, d2);
	vertexDataArr[7].pos = XMFLOAT3(-w2, -h2, -d2);
	// 左面
	vertexDataArr[8].pos = XMFLOAT3(-w2, -h2, d2);
	vertexDataArr[9].pos = XMFLOAT3(-w2, h2, d2);
	vertexDataArr[10].pos = XMFLOAT3(-w2, h2, -d2);
	vertexDataArr[11].pos = XMFLOAT3(-w2, -h2, -d2);
	// 右面
	vertexDataArr[12].pos = XMFLOAT3(w2, -h2, -d2);
	vertexDataArr[13].pos = XMFLOAT3(w2, h2, -d2);
	vertexDataArr[14].pos = XMFLOAT3(w2, h2, d2);
	vertexDataArr[15].pos = XMFLOAT3(w2, -h2, d2);
	// 前面
	vertexDataArr[16].pos = XMFLOAT3(w2, -h2, d2);
	vertexDataArr[17].pos = XMFLOAT3(w2, h2, d2);
	vertexDataArr[18].pos = XMFLOAT3(-w2, h2, d2);
	vertexDataArr[19].pos = XMFLOAT3(-w2, -h2, d2);
	// 后面
	vertexDataArr[20].pos = XMFLOAT3(-w2, -h2, -d2);
	vertexDataArr[21].pos = XMFLOAT3(-w2, h2, -d2);
	vertexDataArr[22].pos = XMFLOAT3(w2, h2, -d2);
	vertexDataArr[23].pos = XMFLOAT3(w2, -h2, -d2);

	for (int i = 0; i < 4; ++i)
	{
		vertexDataArr[i].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);		// 顶面
		vertexDataArr[i].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexDataArr[i].color = color;

		vertexDataArr[i + 4].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);	// 底面
		vertexDataArr[i + 4].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
		vertexDataArr[i + 4].color = color;

		vertexDataArr[i + 8].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);	// 左面
		vertexDataArr[i + 8].tangent = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
		vertexDataArr[i + 8].color = color;

		vertexDataArr[i + 12].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);	// 右面
		vertexDataArr[i + 12].tangent = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexDataArr[i + 12].color = color;

		vertexDataArr[i + 16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);	// 前面
		vertexDataArr[i + 16].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
		vertexDataArr[i + 16].color = color;

		vertexDataArr[i + 20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f); // 后面
		vertexDataArr[i + 20].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexDataArr[i + 20].color = color;
	}

	for (int i = 0; i < 6; ++i)
	{
		vertexDataArr[i * 4].tex = XMFLOAT2(0.0f, 1.0f);
		vertexDataArr[i * 4 + 1].tex = XMFLOAT2(0.0f, 0.0f);
		vertexDataArr[i * 4 + 2].tex = XMFLOAT2(1.0f, 0.0f);
		vertexDataArr[i * 4 + 3].tex = XMFLOAT2(1.0f, 1.0f);
	}

	for (int i = 0; i < 24; ++i)
	{
		InsertVertexElement(meshData.vertexVec[i], vertexDataArr[i]);
	}

	meshData.indexVec = {
		0, 1, 2, 2, 3, 0,		// 顶面
		4, 5, 6, 6, 7, 4,		// 底面
		8, 9, 10, 10, 11, 8,	// 左面
		12, 13, 14, 14, 15, 12,	// 右面
		16, 17, 18, 18, 19, 16, // 背面
		20, 21, 22, 22, 23, 20	// 正面
	};

	return meshData;
}
template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::Create2DShow(float centerX, float centerY, float scaleX, float scaleY, const DirectX::XMFLOAT4 & color)
{
	using namespace DirectX;

	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(4);

	VertexData vertexData;
	IndexType vIndex = 0;

	vertexData = { XMFLOAT3(centerX - scaleX, centerY - scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 1.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX - scaleX, centerY + scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 0.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX + scaleX, centerY + scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(1.0f, 0.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX + scaleX, centerY - scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(1.0f, 1.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	meshData.indexVec = { 0, 1, 2, 2, 3, 0 };
	return meshData;
}



#endif
