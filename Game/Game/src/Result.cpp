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
    
    if (getData().highScore <= 0) {
        FontAsset(U"ResultMonku")(U"え！？何で土のう").draw(Scene::CenterF().x - 450, Scene::Height() * 0.3 + resultHeight * 1.5, Palette::Red);
        FontAsset(U"ResultMonku")(U"置いてないの？？？").draw(Scene::CenterF().x - 450, Scene::Height() * 0.3 + resultHeight * 3.5, Palette::Red);
        return;
    }
    
    FontAsset(U"ResultMonku")(U"夜は土のう無かったのに").draw(Scene::CenterF().x - 550, Scene::Height() * 0.3 + resultHeight * 1.5, Palette::Red);
    FontAsset(U"ResultMonku")(U"何であるんですか！？！？").draw(Scene::CenterF().x - 450, Scene::Height() * 0.3 + resultHeight * 3.5, Palette::Red);
}
