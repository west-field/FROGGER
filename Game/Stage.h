#pragma once
#include <vector>

enum class LayerType
{
	Background,//0:�w�i
	Enemy,//1:�G
	Event,//2:�C�x���g
};

//�}�b�v�̍L���~���C���[���Ȃ̂ŁA2�̃x�N�^�[�����q�ɂ��Ă���
using MapData_t = std::vector<std::vector<unsigned char>>;

/// <summary>
/// �X�e�[�W�����Ǘ�����N���X
/// </summary>
class Stage
{

public:
	Stage();
	virtual ~Stage();

	/// <summary>
	/// �w�b�_�[��ǂݍ���
	/// </summary>
	/// <param name="filePath">�ǂݍ��ރt�@�C����</param>
	void Load(const wchar_t* filePath);

	/// <summary>
	/// �}�b�v�f�[�^�̎Q�Ƃ�Ԃ�
	/// </summary>
	/// <returns>�}�b�v�f�[�^</returns>
	const MapData_t& GetMapData()const;

	/// <summary>
	/// �}�b�v��ID���擾����֐�
	/// </summary>
	/// <param name="layerId">���C���[</param>
	/// <param name="chipX">�`�b�v�̏ꏊ��</param>
	/// <param name="chipY">�`�b�v�̏ꏊ�c</param>
	/// <returns>�}�b�v��ID</returns>
	const int GetChipId(int layerId,int chipX,int chipY)const;

	/// <summary>
	/// �}�b�v�̃T�C�Y����肷��
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	void GetMapSize(int& width, int& height);

private:
	MapData_t mapData_;
	int mapWidth_;
	int mapHeight_;
	/// <summary>
	/// �f�[�^�̓��e��XY�]�u����
	/// </summary>
	/// <param name="layerId">���C���[ID</param>
	void TransposeMapData(int layerId);
};

