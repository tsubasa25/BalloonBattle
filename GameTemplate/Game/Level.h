#pragma once
#include "tklFile.h"
#include "MapChipRender.h"


	class Level
	{
	private:
		/**
		 * @brief ボーンを作成してm_boneに格納する
		*/
		void BuildBone();
	public:
		~Level();

		/**
		 * @brief レベルの初期化
		 * @param levelFilePath レベルのファイルパス(.tkl)
		 * @param hookFunc フック関数
		 * @return
		*/
		bool Init(const char* levelFilePath, std::function<bool(LevelObjectData& objectData)> hookFunc);
	private:
		tklFile m_tklFile;								//読み込んだtklファイルのデータ
		typedef std::unique_ptr<Bone> CBone;			//ボーンのユニークポインタ
		std::vector<CBone> m_bone;						//ボーンのユニークポインタの可変長配列
		std::unique_ptr<Matrix[]> m_boneMatrixs;		//行列のユニークポインタ
		bool m_isInited = false;						//初期化が完了したか?
		std::list<MapChipRender*> m_mapChipRenderPtrs;	//レベルに存在するマップチップのリスト
	};

