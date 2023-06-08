#include "Stage.h"
#include <DxLib.h>
#include <string>
#include <cassert>

Stage::Stage():mapWidth_(0), mapHeight_(0)
{
}

Stage::~Stage()
{
}

void Stage::Load(const wchar_t* filePath)
{
	//FMF�w�b�_�[�iPlatinum�̃h�L�������g�ɏ����Ă���j
	struct Header
	{
		int8_t id[4];			//�@�t�@�C�����ʎq(FMF_)�@4�o�C�g
		uint32_t size;			//�@�w�b�_���̂������f�[�^�T�C�Y�@4�o�C�g
		uint32_t mapWidth;		//�@�}�b�v�̉����@4�o�C�g
		uint32_t mapHeight;		//�@�}�b�v�̏c���@4�o�C�g
		uint8_t chipWidth;		//�@�p�[�c(�Z��1��)�̉����@1�o�C�g
		uint8_t chipHeight;		//�@�p�[�c(�Z��1��)�̏c���@1�o�C�g
		uint8_t layerCount;		//�@���C���[���@1�o�C�g
		uint8_t bitCount;		//�@1�Z��������̃r�b�g��(��8�Ńo�C�g��)�@1�o�C�g
	};//20�o�C�g
	Header header;
	int handle = FileRead_open(filePath);
	FileRead_read(&header, sizeof(header), handle);
	
	std::string strId;
	strId.resize(4);
	std::copy_n(header.id, 4, strId.begin());
	if (strId != "FMF_")
	{
		//���[�h���s
		assert(0);
	}
	
	mapWidth_ = header.mapWidth;
	mapHeight_ = header.mapHeight;
	int layerCount = header.layerCount;
	//���C���[1������̃T�C�Y���v�Z����
	//�}�b�v�̕��~�}�b�v�̍����~�i�}�b�v�������̃o�C�g��
	int layerDataSize = header.mapWidth * header.mapHeight * (header.bitCount / 8);

	mapData_.resize(layerCount);//  resize�f�[�^��傫�������菬����������
	for (auto& layer : mapData_)
	{
		layer.resize(layerDataSize);
		FileRead_read(layer.data(), layerDataSize, handle);
	}

	FileRead_close(handle);

	//���s���������������̂��߂ɁA�f�[�^�����H
	for (int layerIdx = 0; layerIdx < layerCount; layerIdx++)
	{
		TransposeMapData(layerIdx);
	}
}

const MapData_t& Stage::GetMapData() const
{
	return mapData_;
}

const int Stage::GetChipId(int layerId, int chipX, int chipY) const
{
	assert(chipX < mapWidth_);
	assert(chipY < mapHeight_);
	auto index = chipY + mapHeight_ * chipX;
	return mapData_[layerId][index];
}

void Stage::GetMapSize(int& width, int& height)
{
	width = mapWidth_;
	height = mapHeight_;
}

void Stage::TransposeMapData(int layerId)
{
	auto temp = mapData_[layerId];//��������R�s�[���Ă����@�R�s�[�����ɓ]�u���悤�Ƃ���ƌ��̃f�[�^��������
	for (int Y = 0; Y < mapHeight_; Y++)
	{
		for (int X = 0; X < mapWidth_; X++)
		{
			//�ʏ��XY�w��̏ꍇ	Y*mapWidth_+X�Ƃ������ɂȂ�B�@����ɁA��200�c15�͈ێ�����K�v������B
			//�c�ɕ��ׂĂ��������@0�ׂ̗͈�i���ɂ�����
			int idxSrc = Y * mapWidth_ + X;//Source Index���ƂɂȂ�f�[�^
			int idxDst = Y + mapHeight_ * X;//Destination Index�R�s�[����f�[�^�̏ꏊ

			mapData_[layerId][idxDst] = temp[idxSrc];
		}
	}
}
