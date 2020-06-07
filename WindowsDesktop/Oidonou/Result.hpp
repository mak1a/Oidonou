#include"Common.hpp"


/// <summary>
/// ���D�N���X
/// Tw��tter�̒a�����̎��݂����ɔ�΂�
/// </summary>
class Balloon {
private:
    /// <summary>
    /// ���D�̃e�N�X�`��
    /// �F�͕ʂ̊֐��ŕύX����
    /// </summary>
    Texture m_texture;
    /// <summary>
    /// ���E�ɓ������A�����I�ɓ����̂ł��̎���
    /// </summary>
    Duration m_cycleMove;
    /// <summary>
    /// ���D����ɍs������
    /// </summary>
    double m_speed;
    /// <summary>
    /// ���D�̈ʒu
    /// </summary>
    Vec2 m_position;
public:
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^���֎~����
    /// </summary>
    Balloon() = delete;

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="texture_">���D�̃e�N�X�`��</param>
    /// <param name="cycle_">���E�ɓ����ۂ̎���</param>
    /// <param name="pos_">�����ʒu</param>
    /// <param name="speed_">�㏸�̑���</param>
    /// <returns></returns>
    Balloon(const Texture& texture_, Duration cycle_, const Vec2& pos_, const double speed_) noexcept
        : m_texture(texture_)
        , m_cycleMove(cycle_)
        , m_position(pos_)
        , m_speed(speed_) {}

    /// <summary>
    /// ���D�𓮂���
    /// </summary>
    /// <returns></returns>
    void Move() noexcept {
        m_position.y -= m_speed;
    }

    /// <summary>
    /// ���D�̕`��
    /// ���D�̎��Ƃ���ɓy�X���t���Ă�
    /// ���E�������I�ɓ������Ă�
    /// </summary>
    void drawBalloon() const {
        m_texture.draw(m_position.x + 20 * Periodic::Triangle0_1(m_cycleMove), m_position.y);
        TextureAsset(U"Donou").resized(100, 100).draw(
            m_position.x + 20 * Periodic::Triangle0_1(m_cycleMove) - 50
            , m_position.y + 100
        );
    }
};

/// <summary>
/// ���U���g�N���X
/// </summary>
class Result : public MyApp::Scene {
private:
    /// <summary>
    /// ���D���i�[����
    /// </summary>
    Array<Balloon> m_balloons;
public:

    Result(const InitData& init);

    void update() override;

    void draw() const override;
};
