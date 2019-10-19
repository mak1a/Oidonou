
# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene(init)
    , m_chargeDonou(Arg::center(50.f, Scene::CenterF().movedBy(0, 120).y), Vec2(200.f, 500.f)){
        m_countDown.start();
        
        m_donous.emplace(Scene::CenterF(), 100, 200);
        
        // 女性と男性のロード
        Vec2 initPos(1400.f, Scene::CenterF().y + Random(-100.f, 200.f));
        for (auto i : step(15)) {
            m_women.emplace_back(initPos, initPos.movedBy(-100, 50), initPos.movedBy(-100, -50));
            m_men.emplace_back(initPos, initPos.movedBy(-100, 50), initPos.movedBy(-100, -50));
        }
}

void Game::update() {
    // ゲームスタートの処理
    if (!onGame() && m_countDown >= 3000ms) {
        m_gameTimer.start();
        m_countDown.reset();
    }
    // ゲームを開始してない場合、早期リターン
    if (!onGame()) {
        return;
    }
    
    m_donous.value().setCenter(Cursor::PosF());
}

void Game::draw() const {
    // カウントダウン中の場合
    if (onCountDown()) {
        const int32 timeMillisec = Max((3999 - m_countDown.ms()), 0);
        const int32 countDown = timeMillisec / 1000;
        const double e = EaseIn(Easing::Expo, (timeMillisec % 1000) / 1000.0);
        
        if (countDown > 0)
        {
            Transformer2D t(Mat3x2::Scale(1.0 + e * 2, Scene::Center()));
            FontAsset(U"CountDown")(countDown).drawAt(Scene::Center(), Palette::Black);
        }
        else
        {
            Transformer2D t(Mat3x2::Scale(1.0 + (1.0 - e) * 2, Scene::Center()));
            FontAsset(U"CountDown")(U"START").drawAt(Scene::Center(), Palette::Black);
        }
    }
    
    // ゲーム中じゃない場合、早期リターン
    if (!onGame()) {
        return;
    }
    
    TextureAsset(U"River").resized(1400, 830).drawAt(Scene::CenterF());
    
    m_chargeDonou.draw(ColorF(Palette::Red, 0.5f));
    
    for (auto &man : m_men) {
        man.draw(Palette::Black);
    }
    //TextureAsset(U"ManSchool").resized(m_man.size).drawAt(m_man.center());
    //TextureAsset(U"WomanSchool").resized(m_woman.size).drawAt(m_woman.center());
    //TextureAsset(U"Donou").resized(m_Donou.value().size).drawAt(m_Donou.value().center());
}
