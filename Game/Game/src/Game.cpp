
# include "Game.hpp"

Human::Human (const Vec2& initPos) noexcept
	: Triangle (initPos, initPos.movedBy (-450, 50), initPos.movedBy (-450, -50)) {}


Game::Game (const InitData& init)
	: IScene (init)
	, m_chargeDonou (Arg::center (50.f, Scene::CenterF ().movedBy (0, 120).y), Vec2 (200.f, 500.f))
	, m_putDonou (Arg::center (1230.f, Scene::CenterF ().movedBy (0, 120).y), Vec2 (300.f, 500.f)) {
	m_countDown.start ();

}

void Game::update () {
	/// <summary>
	/// ゲームスタートの処理
	/// </summary>
	if (!onGame () && m_countDown >= 3000ms) {
		m_gameTimer.start ();
		m_createMan.start ();
		m_createWoman.start ();
		m_countDown.reset ();

		Vec2 initPos (1400.f, Scene::CenterF ().y + Random (-100.f, 200.f));
		m_men.emplace_back (initPos);
		initPos = Vec2 (1400.f, Scene::CenterF ().y + Random (-100.f, 200.f));
		m_women.emplace_back (initPos);
	}
	/// <summary>
	/// ゲームを開始してない場合、早期リターン
	/// </summary>
	if (!onGame ()) {
		return;
	}

	/// <summary>
	/// ゲームが終了した場合、スコアをGameDataに渡し、
	/// シーンをリザルトシーンに移動
	/// </summary>
	if (m_gameTimer.ms () >= gameTimeMillisec) {
		getData ().score = m_score;

		changeScene (State::Result, 2000);
	}

	/// <summary>
	/// 人間の生成
	/// </summary>
	if (m_createMan >= 1600ms) {
		m_createMan.restart ();
		Vec2 initPos (1400.f, Scene::CenterF ().y + Random (-100.f, 200.f));
		m_men.emplace_back (initPos);
	}
	if (m_createWoman >= 2000ms) {
		m_createWoman.restart ();
		Vec2 initPos (1400.f, Scene::CenterF ().y + Random (-100.f, 200.f));
		m_women.emplace_back (initPos);
	}

	/// <summary>
	/// 男の処理
	/// </summary>
	for (auto& man : m_men) {
		man.moveBy (-5.f, man.getYDir ());

		/// <summary>
		/// プレイヤーが土嚢を持ってない場合は早期リターン
		/// </summary>
		if (!m_donou.has_value ()) {
			continue;
		}

		/// <summary>
		/// プレイヤーの土嚢と接触した場合、
		/// スコアが減り、怒り状態になる。
		/// また、土嚢も消える。
		/// </summary>
		if (man.intersects (m_donou.value ())) {
			man.changeStateAngry ();
			m_score -= Random (2500, 5000);
			m_donou.reset ();
		}
	}
	/// <summary>
	/// 女の処理
	/// </summary>
	for (auto& woman : m_women) {
		woman.moveBy (-5.f, woman.getYDir ());

		/// <summary>
		/// プレイヤーが土嚢を持ってない場合は早期リターン
		/// </summary>
		if (!m_donou.has_value ()) {
			continue;
		}

		/// <summary>
		/// プレイヤーの土嚢と接触した場合、
		/// スコアが減り、怒り状態になる。
		/// また、土嚢も消える。
		if (woman.intersects (m_donou.value ())) {
			woman.changeStateAngry ();
			m_score -= Random (2500, 5000);;
			m_donou.reset ();
		}
	}

	/// <summary>
	/// 土嚢を持ってない場合の処理
	/// </summary>
	if (!m_donou.has_value ()) {
		if (m_chargeDonou.leftClicked ()) {
			m_donou.emplace (Arg::center (Cursor::PosF ()), 100, 100);
		}

		return;
	}

	/// <summary>
	/// 土嚢をカーソルの位置に設定する。
	/// ただしズルは許さないため、y座標の最小値最大値を設定している。
	/// </summary>
	m_donou.value ().setCenter (Cursor::PosF ().x, Clamp (Cursor::PosF ().y, 250.0, 650.0));

	/// <summary>
	/// 学校前の四角形の範囲のところをクリックした場合、
	/// 土嚢をクリックした場所に置きスコアを更新する。
	/// </summary>
	if (m_putDonou.leftClicked ()) {
		m_putDonous.emplace_back (Cursor::PosF ());

		int32 score = static_cast<int32>(20000 - m_scoreSphere.distanceFrom (Cursor::PosF ()) * 50);
		m_score += Max (score, 0);
		m_donou.reset ();
	}
}

void Game::draw () const {
	/// <summary>
	/// カウントダウン中の処理
	/// </summary>
	if (onCountDown ()) {
		const int32 timeMillisec = Max ((3999 - m_countDown.ms ()), 0);
		const int32 countDown = timeMillisec / 1000;
		const double e = EaseIn (Easing::Expo, (timeMillisec % 1000) / 1000.0);

		TextureAsset (U"River").resized (1400, 830).drawAt (Scene::CenterF ());

		TextureAsset (U"Schoolkun").resized (400.f, 300.f).drawAt (m_putDonou.center ().movedBy (-100.f, -100.f));

		if (countDown > 0) {
			Transformer2D t (Mat3x2::Scale (1.0 + e * 2, Scene::Center ()));
			FontAsset (U"CountDown")(countDown).drawAt (Scene::Center (), Palette::Black);
		}
		else {
			Transformer2D t (Mat3x2::Scale (1.0 + (1.0 - e) * 2, Scene::Center ()));
			FontAsset (U"CountDown")(U"START").drawAt (Scene::Center (), Palette::Black);
		}
	}

	/// <summary>
	/// ゲーム中じゃない場合、早期リターン
	/// </summary>
	if (!onGame ()) {
		return;
	}

	/// <summary>
	/// 背景の描画
	/// </summary>
	TextureAsset (U"River").resized (1400, 830).drawAt (Scene::CenterF ());
	m_putDonou.draw (ColorF (Palette::Yellow, 0.5f));
	TextureAsset (U"Schoolkun").resized (400.f, 300.f).drawAt (m_putDonou.center ().movedBy (-100.f, -100.f));
	m_chargeDonou.draw (ColorF (Palette::Red, 0.5f));

	/// <summary>
	/// 置いた土嚢の描画処理
	/// </summary>
	for (auto& donouPos : m_putDonous) {
		TextureAsset (U"Donou").resized (50, 100).drawAt (donouPos);
	}

	/// <summary>
	/// 男の描画処理
	/// </summary>
	for (auto& man : m_men) {
		/// <summary>
		/// 精神状態によって描画するテクスチャを変更する
		/// </summary>
		if (!man.isAngry ()) {
			TextureAsset (U"ManSchool").resized (180, 300).drawAt (man.p0.movedBy (0, 85));
		}
		else {
			TextureAsset (U"ManIkari").resized (180, 300).drawAt (man.p0.movedBy (0, 85));
		}
		/// <summary>
		/// 男の目線の描画
		/// 半透明にしてる
		/// </summary>
		man.draw (ColorF (Palette::Red, 0.2f));
	}
	/// <summary>
	/// 女の描画処理
	/// </summary>
	for (auto& woman : m_women) {
		/// <summary>
		/// 精神状態によって描画するテクスチャを変更する
		/// </summary>
		if (!woman.isAngry ()) {
			TextureAsset (U"WomanSchool").resized (180, 300).drawAt (woman.p0.movedBy (0, 85));
		}
		else {
			TextureAsset (U"WomanIkari").resized (180, 300).drawAt (woman.p0.movedBy (0, 85));
		}
		/// <summary>
		/// 女の目線の描画
		/// 半透明にしてる
		/// </summary>
		woman.draw (ColorF (Palette::Red, 0.2f));
	}

	/// <summary>
	/// 土嚢をプレイヤーが持ってる場合の描画処理
	/// </summary>
	if (m_donou.has_value ()) {
		TextureAsset (U"Donou").resized (100, 100).drawAt (m_donou.value ().center ());
	}

	/// <summary>
	/// 残り時間の描画
	/// </summary>
	const int32 timeLeftMillisec = Max (gameTimeMillisec - m_gameTimer.ms (), 0);
	FontAsset (U"GameTime")(U"生徒が来るまで: {:0>2}'{:0>2} 時間"_fmt (timeLeftMillisec / 1000, timeLeftMillisec % 1000 / 10)).draw (60, 60, Palette::Black);

	/// <summary>
	/// スコアの描画
	/// </summary>
	FontAsset (U"GameTime")(U"スコア: {0}"_fmt (m_score)).draw (800, 60, Palette::Black);
}
