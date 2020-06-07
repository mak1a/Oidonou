
# pragma once
# include "Common.hpp"

/// <summary>
/// �^�C�g���N���X
/// </summary>
class Title : public MyApp::Scene {
private:

    Rect m_startButton;
    Transition m_startTransition;

    Rect m_exitButton;
    Transition m_exitTransition;

public:

    Title(const InitData& init);

    void update() override;

    void draw() const override;
};
