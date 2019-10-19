
# include "Game.hpp"

Human::Human(const Vec2 &initPos)
    : Triangle(initPos, initPos.movedBy(-450, 50), initPos.movedBy(-450, -50)) {}


Game::Game(const InitData& init)
	: IScene(init)
    , m_chargeDonou(Arg::center(50.f, Scene::CenterF().movedBy(0, 120).y), Vec2(200.f, 500.f))
    , m_putDonou(Arg::center(1230.f, Scene::CenterF().movedBy(0, 120).y), Vec2(300.f, 500.f)) {
        m_countDown.start();
         
}

void Game::update() {
    // ゲームスタートの処理
    if (!onGame() && m_countDown >= 3000ms) {
        m_gameTimer.start();
        m_createMan.start();
        m_createWoman.start();
        m_countDown.reset();
    }
    // ゲームを開始してない場合、早期リターン
    if (!onGame()) {
        return;
    }
    
    // 人間の生成
    if (m_createMan >= 800ms) {
        m_createMan.restart();
        Vec2 initPos(1000.f, Scene::CenterF().y + Random(-100.f, 200.f));
        m_men.emplace_back(initPos);
    }
    if (m_createWoman >= 1000ms) {
        m_createWoman.restart();
        Vec2 initPos(1000.f, Scene::CenterF().y + Random(-100.f, 200.f));
        m_women.emplace_back(initPos);
    }
    for (auto &man : m_men) {
        man.moveBy(-5.f, man.getYDir());
    }
    for (auto &woman : m_women) {
        woman.moveBy(-5.f, woman.getYDir());
    }
    
    // 土嚢の動き
    if (!m_donou.has_value()) {
        if (m_chargeDonou.leftClicked()) {
            m_donou.emplace(Arg::center(Cursor::PosF()), 100, 200);
        }
        
        return;
    }
    
    m_donou.value().setCenter(Cursor::PosF());
    
    for (auto &man : m_men) {
        if (man.intersects(m_donou.value())) {
            man.changeStateAngry();
        }
    }
    for (auto &woman : m_women) {
        if (woman.intersects(m_donou.value())) {
            woman.changeStateAngry();
        }
    }
    
    if (m_putDonou.leftClicked()) {
        m_putDonous.emplace_back(Cursor::PosF());
        
        int32 score = m_scoreSphere.distanceFrom(Cursor::PosF()) * 50;
        m_donou.reset();
    }
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
    
    m_putDonou.draw(ColorF(Palette::Yellow, 0.5f));
    TextureAsset(U"Schoolkun").resized(400.f, 300.f).drawAt(m_putDonou.center().movedBy(-100.f, -100.f));
    
    m_chargeDonou.draw(ColorF(Palette::Red, 0.5f));
    
    for (auto &donouPos : m_putDonous) {
        TextureAsset(U"Donou").resized(50, 100).drawAt(donouPos);
    }
    
    for (auto &man : m_men) {
        man.draw(ColorF(Palette::Red, 0.5f));
        if (!man.isAngry()) {
            TextureAsset(U"ManSchool").resized(100, 200).drawAt(man.p0);
        }
        else {
            TextureAsset(U"ManIkari").resized(100, 200).drawAt(man.p0);
        }
    }
    for (auto &woman : m_women) {
        woman.draw(ColorF(Palette::Red, 0.5f));
        if (!woman.isAngry()) {
            TextureAsset(U"WomanSchool").resized(100, 200).drawAt(woman.p0);
        }
        else {
            TextureAsset(U"WomanIkari").resized(100, 200).drawAt(woman.p0);
        }
    }
    
    if (m_donou.has_value()) {
        TextureAsset(U"Donou").resized(m_donou.value().size).drawAt(m_donou.value().center());
    }
}
