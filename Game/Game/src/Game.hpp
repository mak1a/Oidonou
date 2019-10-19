
# pragma once
# include "Common.hpp"

// ゲームシーン
class Game : public MyApp::Scene {
private:
    Stopwatch m_countDown;
    Stopwatch m_gameTimer;
    Stopwatch m_createMan;
    Stopwatch m_createWoman;
    
    Array<Triangle> m_men;
    Array<Triangle> m_women;
    std::optional<RectF> m_donou;
    
    RectF m_chargeDonou;
    RectF m_putDonou;
    
    bool onCountDown() const {
        return m_countDown.isRunning() && m_countDown < 4000ms;
    }
    bool onGame() const {
        return m_gameTimer.isRunning();
    }
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
