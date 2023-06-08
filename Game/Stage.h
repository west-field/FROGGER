#pragma once
#include <vector>

enum class LayerType
{
	Background,//0:背景
	Enemy,//1:敵
	Event,//2:イベント
};

//マップの広さ×レイヤー数なので、2つのベクターを入れ子にしている
using MapData_t = std::vector<std::vector<unsigned char>>;

/// <summary>
/// ステージ情報を管理するクラス
/// </summary>
class Stage
{

public:
	Stage();
	virtual ~Stage();

	/// <summary>
	/// ヘッダーを読み込む
	/// </summary>
	/// <param name="filePath">読み込むファイル名</param>
	void Load(const wchar_t* filePath);

	/// <summary>
	/// マップデータの参照を返す
	/// </summary>
	/// <returns>マップデータ</returns>
	const MapData_t& GetMapData()const;

	/// <summary>
	/// マップのIDを取得する関数
	/// </summary>
	/// <param name="layerId">レイヤー</param>
	/// <param name="chipX">チップの場所横</param>
	/// <param name="chipY">チップの場所縦</param>
	/// <returns>マップのID</returns>
	const int GetChipId(int layerId,int chipX,int chipY)const;

	/// <summary>
	/// マップのサイズを入手する
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	void GetMapSize(int& width, int& height);

private:
	MapData_t mapData_;
	int mapWidth_;
	int mapHeight_;
	/// <summary>
	/// データの内容をXY転置する
	/// </summary>
	/// <param name="layerId">レイヤーID</param>
	void TransposeMapData(int layerId);
};

