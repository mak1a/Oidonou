
# pragma once
# include "Common.hpp"

// 人間クラス（怒ってるか判定）
class Human : public Triangle {
private:
    enum class State {
        None,
        Angry
    };
    
    State m_state = State::None;
    
    const double moveYDir = Random(-1.f, 1.f);
    
public:
    explicit Human(const Vec2 &initPos);
    
    bool isAngry() const {
        return m_state == State::Angry;
    }
    
    constexpr double getYDir() const {
        return moveYDir;
    }
    
    void changeStateAngry() {
        m_state = State::Angry;
    }
};

// ゲームシーン
class Game : public MyApp::Scene {
private:
    Stopwatch m_countDown;
    Stopwatch m_gameTimer;
    Stopwatch m_createMan;
    Stopwatch m_createWoman;
    
    Array<Human> m_men;
    Array<Human> m_women;
    std::optional<RectF> m_donou;
    
    RectF m_chargeDonou;
    RectF m_putDonou;
    Vec2 m_scoreSphere = Vec2(1140.f, 530.f);
    
    Array<Vec2> m_putDonous;
    
    const int32 gameTimeMillisec = 12 * 1000;
    
    int32 m_score = 0;
    
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
