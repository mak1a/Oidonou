
# pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

/// <summary>
/// シーンの名前
/// </summary>
enum class State {
    Title,

    Game,

    Result
};

/// <summary>
/// ゲームデータ
/// </summary>
struct GameData {
    /// <summary>
    /// スコア
    /// </summary>
    int32 score = 0;
};


/// <summary>
/// 自作関数
/// </summary>
namespace {
    /// <summary>
    /// フォントのプリロード
    /// </summary>
    /// <param name="font">フォント</param>
    /// <param name="text">プリロードしたい文字列</param>
    void Preload(const Font& font, const String& text) {
        font(text.uniqued()).draw(0, 0, ColorF(0.0, 0.0));
    }

    /// <summary>
    /// 全てのアスキーコードをプリロードしておく
    /// </summary>
    /// <param name="font">フォント</param>
    void PreloadAscii(const Font& font) {
        String s;

        for (auto asciiNum = 33; asciiNum <= 126; ++asciiNum) {
            s.push_back(static_cast<char32>(asciiNum));
        }
        s.push_back(U'\n');

        font(s).draw(0.0, 0.0, Color(0, 0));
    }

    /// <summary>
    /// 風船をHSVを指定したもので返す
    /// </summary>
    /// <param name="hue">色相</param>
    /// <returns>風船のImage</returns>
    Image CreateBalloon(double hue) {
        Image image(Emoji::CreateImage(U"🎈"));
        for (auto& pixel : image) {
            HSV hsv = pixel;

            hsv.h = hue;

            pixel = hsv;
        }

        return image;
    }

    /// <summary>
    /// 風船を指定した色で返す
    /// v0.4.2では動くことを確認
    /// </summary>
    /// <param name="color">風船の表面の色</param>
    /// <returns>風船のImage</returns>
    Image CreateBalloon(const Color& color) {
        Image image(Emoji::CreateImage(U"🎈"));

        for (auto& pixel : image) {
            HSV hsv = pixel;

            if (hsv.s == 0) {
                continue;
            }

            hsv = color;

            pixel = hsv;
        }
        return image;
    }
}

/// <summary>
/// シーン管理クラス
/// </summary>
using MyApp = SceneManager<State, GameData>;
