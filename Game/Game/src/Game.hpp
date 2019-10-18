
# pragma once
# include "Common.hpp"

// ゲームシーン
class Game : public MyApp::Scene {
private:
    Stopwatch m_countDown;
    Stopwatch m_gameTimer;
    
    RectF m_man;
    RectF m_woman;
    RectF m_Donou;
    
    bool onCountDown() const {
        return m_countDown.isRunning() && m_countDown < 4000ms;
    }
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
