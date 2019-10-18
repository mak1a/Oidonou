
# pragma once
# include "Common.hpp"

// ゲームシーン
class Game : public MyApp::Scene {
private:
    RectF m_man;
    RectF m_woman;
    RectF m_Donou;
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
