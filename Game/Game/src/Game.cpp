
# include "Game.hpp"

Game::Game(const InitData& init)
	: IScene(init)
, m_man(Scene::CenterF(), 100, 200)
    , m_woman(Scene::CenterF(), 100, 200)
    , m_Donou(Scene::CenterF(), 100, 200){
	
}

void Game::update() {
    m_Donou.setCenter(Cursor::PosF());
}

void Game::draw() const {
    TextureAsset(U"ManSchool").resized(m_man.size).drawAt(m_man.center());
    TextureAsset(U"WomanSchool").resized(m_woman.size).drawAt(m_woman.center());
    TextureAsset(U"Donou").resized(m_Donou.size).drawAt(m_Donou.center());
}
