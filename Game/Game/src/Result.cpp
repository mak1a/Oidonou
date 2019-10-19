//
//  Result.cpp
//  Game
//
//  Created by 山口隼矢 on 2019/10/20.
//

#include "Result.hpp"

Result::Result(const InitData &init)
    : IScene(init) {}

void Result::update() {
    if ((MouseL | KeyEscape).down()) {
        changeScene(State::Title);
    }
}

void Result::draw() const {
    TextureAsset(U"River").resized(1400, 830).drawAt(Scene::CenterF());
    
    TextureAsset(U"Schoolkun").resized(400.f, 300.f).drawAt(Vec2(1230.f, Scene::CenterF().movedBy(0, 120).y).movedBy(-100.f, -100.f));
    
    const double resultHeight = FontAsset(U"Result")(U"スコア：", getData().highScore).region().h;
    
    FontAsset(U"Result")(U"スコア").draw(Scene::CenterF().x - 100, Scene::Height() * 0.4 - resultHeight / 2, Palette::Black);
    FontAsset(U"Result")(U":", getData().highScore).draw(Scene::CenterF().x + 200, Scene::Height() * 0.4 - resultHeight / 2, Palette::Black);
}
