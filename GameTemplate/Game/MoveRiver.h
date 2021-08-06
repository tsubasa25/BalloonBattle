#pragma once
namespace nsBalloon {
	class MoveRiver :public IGameObject
	{
		bool Start()override;
		void Update()override;
		void Render(RenderContext& rc, Camera* camera);
	private:
		struct RiverData
		{
			float textureSize;//テクスチャのサイズ(正方形を想定しているのでfloat。)
			float scrollingValue = 0;//スクロール量
		};
		Model m_riverModel;	//空のモデル、2画面用に2つ用意する。
		RiverData m_riverData;		//シェーダーに渡される空のデータ
	};

}