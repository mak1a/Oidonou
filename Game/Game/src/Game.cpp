
# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene(init)
    , m_man(Scene::CenterF(), 100, 200)
    , m_woman(Scene::CenterF(), 100, 200)
    , m_Donou(Scene::CenterF(), 100, 200){
    m_countDown.start();
}

void Game::update() {
    m_Donou.setCenter(Cursor::PosF());
}

void Game::draw() const {
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
    
    return;
    
    TextureAsset(U"River").resized(1400, 830).drawAt(Scene::CenterF());
    
    TextureAsset(U"ManSchool").resized(m_man.size).drawAt(m_man.center());
    TextureAsset(U"WomanSchool").resized(m_woman.size).drawAt(m_woman.center());
    TextureAsset(U"Donou").resized(m_Donou.size).drawAt(m_Donou.center());
}
