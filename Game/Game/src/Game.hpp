
# pragma once
# include "Common.hpp"

/// <summary>
/// 人間クラス（怒ってるか判定）
/// Triangleを継承してるのは
/// 人間の目線を三角形で表現するため
/// </summary>
class Human : public Triangle {
private:
	/// <summary>
	/// 精神状態
	/// </summary>
	enum class State {
		None,
		Angry
	};

	/// <summary>
	/// 現在の精神状態
	/// </summary>
	State m_state = State::None;

	/// <summary>
	/// y軸の方向
	/// </summary>
	const double moveYDir = Random (-1.f, 1.f);

public:
	explicit Human (const Vec2& initPos) noexcept;

	/// <summary>
	/// 怒ってるか判定
	/// </summary>
	/// <returns>現在の精神状態がAngryか</returns>
	[[nodiscard]] bool isAngry () const noexcept {
		return m_state == State::Angry;
	}

	constexpr double getYDir () const noexcept {
		return moveYDir;
	}

	/// <summary>
	/// 精神状態を怒りにする
	/// </summary>
	void changeStateAngry () noexcept {
		m_state = State::Angry;
	}
};

// ゲームシーン
class Game : public MyApp::Scene {
private:
	/// <summary>
	/// スタートのカウントを数えるタイマー
	/// </summary>
	Stopwatch m_countDown;
	/// <summary>
	/// ゲームがスタートしてからのタイマー
	/// </summary>
	Stopwatch m_gameTimer;
	/// <summary>
	/// 男を作り出すタイミング
	/// </summary>
	Stopwatch m_createMan;
	/// <summary>
	/// 女を作り出すタイミング
	/// </summary>
	Stopwatch m_createWoman;

	/// <summary>
	/// 作り出した男を格納しておく
	/// </summary>
	Array<Human> m_men;
	/// <summary>
	/// 作り出した女を格納しておく
	/// </summary>
	Array<Human> m_women;

	/// <summary>
	/// 土嚢の当たり判定や、
	/// そもそも土嚢を持ってるかの情報を持ってる
	/// </summary>
	Optional<RectF> m_donou;

	/// <summary>
	/// 土嚢を作り出す場所
	/// </summary>
	RectF m_chargeDonou;
	/// <summary>
	/// 持ってる土嚢を置く場所
	/// </summary>
	RectF m_putDonou;
	/// <summary>
	/// 置いた土嚢が学校の入り口に近いと点数が上がるシステムなため、
	/// 学校の玄関の位置の情報が必要
	/// </summary>
	Vec2 m_scoreSphere = Vec2 (1140.f, 530.f);

	/// <summary>
	/// 置いた土嚢の位置を格納しておく
	/// </summary>
	Array<Vec2> m_putDonous;

	/// <summary>
	/// ゲームの終了時間
	/// </summary>
	static constexpr int32 gameTimeMillisec = 20 * 1000;

	/// <summary>
	/// 現在のスコア
	/// </summary>
	int32 m_score = 0;

	[[nodiscard]] bool onCountDown () const noexcept {
		return m_countDown.isRunning () && m_countDown < 4000ms;
	}
	[[nodiscard]] bool onGame () const noexcept {
		return m_gameTimer.isRunning ();
	}
public:

	Game (const InitData& init);

	void update () override;

	void draw () const override;
};
