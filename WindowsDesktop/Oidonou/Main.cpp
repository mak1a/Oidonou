﻿
# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
#include "Result.hpp"

void Main() {
    /// <summary>
    /// ウィンドウの閉じるボタンを押したときだけ終了する場合はコメントを外す
    /// </summary>
    //System::SetTerminationTriggers(UserAction::CloseButtonClicked);

    /// <summary>
    /// タイトルを設定
    /// </summary>
    Window::SetTitle(U"追い土嚢");

    /// <summary>
    /// 背景色を設定
    /// </summary>
    Scene::SetBackground(Palette::White);

    /// <summary>
    /// ウィンドウサイズを変更
    /// </summary>
    Window::Resize(1280, 720);

    /// <summary>
    /// 使用するフォントアセットを登録
    /// </summary>
    FontAsset::Register(U"Title", 120, Resource(U"example/font/AnnyantRoman/AnnyantRoman.ttf"));
    FontAsset::Register(U"Menu", 30, Typeface::Regular);
    FontAsset::Register(U"Score", 36, Typeface::Bold);
    FontAsset::Register(U"CountDown", 72, Typeface::Bold);
    FontAsset::Register(U"GameTime", 40, Typeface::Light);
    FontAsset::Register(U"Result", 50, Typeface::Bold);
    FontAsset::Register(U"ResultMonku", 100, Typeface::Bold);

    /// <summary>
    /// フォントプリロード
    /// </summary>
    PreloadAscii(FontAsset(U"Title"));
    PreloadAscii(FontAsset(U"Menu"));
    PreloadAscii(FontAsset(U"Score"));
    PreloadAscii(FontAsset(U"CountDown"));
    PreloadAscii(FontAsset(U"GameTime"));
    PreloadAscii(FontAsset(U"Result"));
    Preload(FontAsset(U"ResultMonku"), U"夜は土のう無かったのに何であるんですか！？！？え！？何で土のう置いてないの？？？");

    /// <summary>
    /// 使用するテクスチャアセットを登録
    /// </summary>
    TextureAsset::Register(U"Schoolkun", Resource(U"textures/daigaku_toudai.png"));
    TextureAsset::Register(U"ManSchool", Resource(U"textures/walking2_man.png"));
    TextureAsset::Register(U"WomanSchool", Resource(U"textures/walking5_woman.png"));
    TextureAsset::Register(U"Donou", Resource(U"textures/donou.png"));
    TextureAsset::Register(U"River", Resource(U"textures/kawa.png"));
    TextureAsset::Register(U"ManIkari", Resource(U"textures/walking2_man_ikari.png"));
    TextureAsset::Register(U"WomanIkari", Resource(U"textures/walking5_woman_ikari.png"));

    /// <summary>
    /// シーンと遷移時の色を設定
    /// </summary>
    MyApp manager;
    manager
        .add<Title>(State::Title)
        .add<Game>(State::Game)
        .add<Result>(State::Result)
        .setFadeColor(ColorF(1.0));

    /// <summary>
    /// ゲームシーンから開始する場合はコメントを外す
    /// </summary>
    //manager.init(State::Result);

    while (System::Update()) {
        if (!manager.update()) {
            break;
        }
    }
}
