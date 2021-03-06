﻿#include "Result.hpp"

Result::Result(const InitData& init)
    : IScene(init) {
    /// <summary>
    /// 風船を30個作る
    /// </summary>
    for (auto i : step(30)) {
        m_balloons.emplace_back(Texture(CreateBalloon(12 * i)), Duration(Random(0.8, 1.5))
            , Vec2(Random(0, Scene::Size().x), 750), Random(1.0, 4.0));
    }
}

void Result::update() {
    if ((MouseL | KeyEscape).down()) {
        changeScene(State::Title);
        return;
    }

    for (auto& balloon : m_balloons) {
        balloon.Move();
    }
}

void Result::draw() const {
    /// <summary>
    /// 背景の描画
    /// </summary>
    TextureAsset(U"River").resized(1400, 830).drawAt(Scene::CenterF());
    TextureAsset(U"Schoolkun").resized(400.f, 300.f).drawAt(Vec2(1230.f, Scene::CenterF().movedBy(0, 120).y).movedBy(-100.f, -100.f));

    /// <summary>
    /// 飛ばしてる風船の描画
    /// </summary>
    for (auto& balloon : m_balloons) {
        balloon.drawBalloon();
    }

    const double resultHeight = FontAsset(U"Result")(U"スコア：", getData().score).region().h;

    FontAsset(U"Result")(U"スコア").draw(Scene::CenterF().x - 100, Scene::Height() * 0.4 - resultHeight / 2, Palette::Black);
    FontAsset(U"Result")(U":", getData().score).draw(Scene::CenterF().x + 200, Scene::Height() * 0.4 - resultHeight / 2, Palette::Black);

    /// <summary>
    /// スコアに応じて文字を変更
    /// </summary>
    if (getData().score <= 0) {
        FontAsset(U"ResultMonku")(U"え！？何で土のう").draw(Scene::CenterF().x - 450, Scene::Height() * 0.3 + resultHeight * 1.5, Palette::Red);
        FontAsset(U"ResultMonku")(U"置いてないの？？？").draw(Scene::CenterF().x - 450, Scene::Height() * 0.3 + resultHeight * 3.5, Palette::Red);
        return;
    }

    FontAsset(U"ResultMonku")(U"夜は土のう無かったのに").draw(Scene::CenterF().x - 550, Scene::Height() * 0.3 + resultHeight * 1.5, Palette::Red);
    FontAsset(U"ResultMonku")(U"何であるんですか！？！？").draw(Scene::CenterF().x - 450, Scene::Height() * 0.3 + resultHeight * 3.5, Palette::Red);
}
