
# pragma once
# include "Common.hpp"

/// <summary>
/// �l�ԃN���X�i�{���Ă邩����j
/// Triangle���p�����Ă�̂�
/// �l�Ԃ̖ڐ����O�p�`�ŕ\�����邽��
/// </summary>
class Human : public Triangle {
private:
    /// <summary>
    /// ���_���
    /// </summary>
    enum class State {
        None,
        Angry
    };

    /// <summary>
    /// ���݂̐��_���
    /// </summary>
    State m_state = State::None;

    /// <summary>
    /// y���̕���
    /// </summary>
    const double moveYDir = Random(-1.f, 1.f);

public:
    explicit Human(const Vec2& initPos) noexcept;

    /// <summary>
    /// �{���Ă邩����
    /// </summary>
    /// <returns>���݂̐��_��Ԃ�Angry��</returns>
    [[nodiscard]] bool isAngry() const noexcept {
        return m_state == State::Angry;
    }

    constexpr double getYDir() const noexcept {
        return moveYDir;
    }

    /// <summary>
    /// ���_��Ԃ�{��ɂ���
    /// </summary>
    void changeStateAngry() noexcept {
        m_state = State::Angry;
    }
};

// �Q�[���V�[��
class Game : public MyApp::Scene {
private:
    /// <summary>
    /// �X�^�[�g�̃J�E���g�𐔂���^�C�}�[
    /// </summary>
    Stopwatch m_countDown;
    /// <summary>
    /// �Q�[�����X�^�[�g���Ă���̃^�C�}�[
    /// </summary>
    Stopwatch m_gameTimer;
    /// <summary>
    /// �j�����o���^�C�~���O
    /// </summary>
    Stopwatch m_createMan;
    /// <summary>
    /// �������o���^�C�~���O
    /// </summary>
    Stopwatch m_createWoman;

    /// <summary>
    /// ���o�����j���i�[���Ă���
    /// </summary>
    Array<Human> m_men;
    /// <summary>
    /// ���o���������i�[���Ă���
    /// </summary>
    Array<Human> m_women;

    /// <summary>
    /// �y�X�̓����蔻���A
    /// ���������y�X�������Ă邩�̏��������Ă�
    /// </summary>
    Optional<RectF> m_donou;

    /// <summary>
    /// �y�X�����o���ꏊ
    /// </summary>
    RectF m_chargeDonou;
    /// <summary>
    /// �����Ă�y�X��u���ꏊ
    /// </summary>
    RectF m_putDonou;
    /// <summary>
    /// �u�����y�X���w�Z�̓�����ɋ߂��Ɠ_�����オ��V�X�e���Ȃ��߁A
    /// �w�Z�̌��ւ̈ʒu�̏�񂪕K�v
    /// </summary>
    Vec2 m_scoreSphere = Vec2(1140.f, 530.f);

    /// <summary>
    /// �u�����y�X�̈ʒu���i�[���Ă���
    /// </summary>
    Array<Vec2> m_putDonous;

    /// <summary>
    /// �Q�[���̏I������
    /// </summary>
    static constexpr int32 gameTimeMillisec = 20 * 1000;

    /// <summary>
    /// ���݂̃X�R�A
    /// </summary>
    int32 m_score = 0;

    [[nodiscard]] bool onCountDown() const noexcept {
        return m_countDown.isRunning() && m_countDown < 4000ms;
    }
    [[nodiscard]] bool onGame() const noexcept {
        return m_gameTimer.isRunning();
    }
public:

    Game(const InitData& init);

    void update() override;

    void draw() const override;
};
