#include"Common.hpp"


/// <summary>
/// 風船クラス
/// Tw○tterの誕生日の時みたいに飛ばす
/// </summary>
class Balloon {
private:
	/// <summary>
	/// 風船のテクスチャ
	/// 色は別の関数で変更する
	/// </summary>
	Texture m_texture;
	/// <summary>
	/// 左右に動くが、周期的に動くのでその周期
	/// </summary>
	Duration m_cycleMove;
	/// <summary>
	/// 風船が上に行く速さ
	/// </summary>
	double m_speed;
	/// <summary>
	/// 風船の位置
	/// </summary>
	Vec2 m_position;
public:
	/// <summary>
	/// デフォルトコンストラクタを禁止する
	/// </summary>
	Balloon () = delete;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture_">風船のテクスチャ</param>
	/// <param name="cycle_">左右に動く際の周期</param>
	/// <param name="pos_">初期位置</param>
	/// <param name="speed_">上昇の速さ</param>
	/// <returns></returns>
	Balloon (const Texture& texture_, Duration cycle_, const Vec2& pos_, const double speed_) noexcept
		: m_texture (texture_)
		, m_cycleMove (cycle_)
		, m_position (pos_)
		, m_speed (speed_) {}

	/// <summary>
	/// 風船を動かす
	/// </summary>
	/// <returns></returns>
	void Move () noexcept {
		m_position.y -= m_speed;
	}

	/// <summary>
	/// 風船の描画
	/// 風船の持つところに土嚢が付いてる
	/// 左右を周期的に動かしてる
	/// </summary>
	void drawBalloon () const {
		m_texture.draw (m_position.x + 20 * Periodic::Triangle0_1 (m_cycleMove), m_position.y);
		TextureAsset (U"Donou").resized (100, 100).draw (
			m_position.x + 20 * Periodic::Triangle0_1 (m_cycleMove) - 50
			, m_position.y + 100
		);
	}
};

/// <summary>
/// リザルトクラス
/// </summary>
class Result : public MyApp::Scene {
private:
	/// <summary>
	/// 風船を格納する
	/// </summary>
	Array<Balloon> m_balloons;
public:

	Result (const InitData& init);

	void update () override;

	void draw () const override;
};
