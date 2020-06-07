
# include "Game.hpp"

Human::Human(const Vec2& initPos) noexcept
    : Triangle(initPos, initPos.movedBy(-450, 50), initPos.movedBy(-450, -50)) {}


Game::Game(const InitData& init)
    : IScene(init)
    , m_chargeDonou(Arg::center(50.f, Scene::CenterF().movedBy(0, 120).y), Vec2(200.f, 500.f))
    , m_putDonou(Arg::center(1230.f, Scene::CenterF().movedBy(0, 120).y), Vec2(300.f, 500.f)) {
    m_countDown.start();

}

void Game::update() {
    /// <summary>
    /// �Q�[���X�^�[�g�̏���
    /// </summary>
    if (!onGame() && m_countDown >= 3000ms) {
        m_gameTimer.start();
        m_createMan.start();
        m_createWoman.start();
        m_countDown.reset();

        Vec2 initPos(1400.f, Scene::CenterF().y + Random(-100.f, 200.f));
        m_men.emplace_back(initPos);
        initPos = Vec2(1400.f, Scene::CenterF().y + Random(-100.f, 200.f));
        m_women.emplace_back(initPos);
    }
    /// <summary>
    /// �Q�[�����J�n���ĂȂ��ꍇ�A�������^�[��
    /// </summary>
    if (!onGame()) {
        return;
    }

    /// <summary>
    /// �Q�[�����I�������ꍇ�A�X�R�A��GameData�ɓn���A
    /// �V�[�������U���g�V�[���Ɉړ�
    /// </summary>
    if (m_gameTimer.ms() >= gameTimeMillisec) {
        getData().score = m_score;

        changeScene(State::Result, 2000);
    }

    /// <summary>
    /// �l�Ԃ̐���
    /// </summary>
    if (m_createMan >= 1600ms) {
        m_createMan.restart();
        Vec2 initPos(1400.f, Scene::CenterF().y + Random(-100.f, 200.f));
        m_men.emplace_back(initPos);
    }
    if (m_createWoman >= 2000ms) {
        m_createWoman.restart();
        Vec2 initPos(1400.f, Scene::CenterF().y + Random(-100.f, 200.f));
        m_women.emplace_back(initPos);
    }

    /// <summary>
    /// �j�̏���
    /// </summary>
    for (auto& man : m_men) {
        man.moveBy(-5.f, man.getYDir());

        /// <summary>
        /// �v���C���[���y�X�������ĂȂ��ꍇ�͑������^�[��
        /// </summary>
        if (!m_donou.has_value()) {
            continue;
        }

        /// <summary>
        /// �v���C���[�̓y�X�ƐڐG�����ꍇ�A
        /// �X�R�A������A�{���ԂɂȂ�B
        /// �܂��A�y�X��������B
        /// </summary>
        if (man.intersects(m_donou.value())) {
            man.changeStateAngry();
            m_score -= Random(2500, 5000);
            m_donou.reset();
        }
    }
    /// <summary>
    /// ���̏���
    /// </summary>
    for (auto& woman : m_women) {
        woman.moveBy(-5.f, woman.getYDir());

        /// <summary>
        /// �v���C���[���y�X�������ĂȂ��ꍇ�͑������^�[��
        /// </summary>
        if (!m_donou.has_value()) {
            continue;
        }

        /// <summary>
        /// �v���C���[�̓y�X�ƐڐG�����ꍇ�A
        /// �X�R�A������A�{���ԂɂȂ�B
        /// �܂��A�y�X��������B
        if (woman.intersects(m_donou.value())) {
            woman.changeStateAngry();
            m_score -= Random(2500, 5000);;
            m_donou.reset();
        }
    }

    /// <summary>
    /// �y�X�������ĂȂ��ꍇ�̏���
    /// </summary>
    if (!m_donou.has_value()) {
        if (m_chargeDonou.leftClicked()) {
            m_donou.emplace(Arg::center(Cursor::PosF()), 100, 100);
        }

        return;
    }

    /// <summary>
    /// �y�X���J�[�\���̈ʒu�ɐݒ肷��B
    /// �������Y���͋����Ȃ����߁Ay���W�̍ŏ��l�ő�l��ݒ肵�Ă���B
    /// </summary>
    m_donou.value().setCenter(Cursor::PosF().x, Clamp(Cursor::PosF().y, 250.0, 650.0));

    /// <summary>
    /// �w�Z�O�̎l�p�`�͈̔͂̂Ƃ�����N���b�N�����ꍇ�A
    /// �y�X���N���b�N�����ꏊ�ɒu���X�R�A���X�V����B
    /// </summary>
    if (m_putDonou.leftClicked()) {
        m_putDonous.emplace_back(Cursor::PosF());

        int32 score = static_cast<int32>(20000 - m_scoreSphere.distanceFrom(Cursor::PosF()) * 50);
        m_score += Max(score, 0);
        m_donou.reset();
    }
}

void Game::draw() const {
    /// <summary>
    /// �J�E���g�_�E�����̏���
    /// </summary>
    if (onCountDown()) {
        const int32 timeMillisec = Max((3999 - m_countDown.ms()), 0);
        const int32 countDown = timeMillisec / 1000;
        const double e = EaseIn(Easing::Expo, (timeMillisec % 1000) / 1000.0);

        TextureAsset(U"River").resized(1400, 830).drawAt(Scene::CenterF());

        TextureAsset(U"Schoolkun").resized(400.f, 300.f).drawAt(m_putDonou.center().movedBy(-100.f, -100.f));

        if (countDown > 0) {
            Transformer2D t(Mat3x2::Scale(1.0 + e * 2, Scene::Center()));
            FontAsset(U"CountDown")(countDown).drawAt(Scene::Center(), Palette::Black);
        }
        else {
            Transformer2D t(Mat3x2::Scale(1.0 + (1.0 - e) * 2, Scene::Center()));
            FontAsset(U"CountDown")(U"START").drawAt(Scene::Center(), Palette::Black);
        }
    }

    /// <summary>
    /// �Q�[��������Ȃ��ꍇ�A�������^�[��
    /// </summary>
    if (!onGame()) {
        return;
    }

    /// <summary>
    /// �w�i�̕`��
    /// </summary>
    TextureAsset(U"River").resized(1400, 830).drawAt(Scene::CenterF());
    m_putDonou.draw(ColorF(Palette::Yellow, 0.5f));
    TextureAsset(U"Schoolkun").resized(400.f, 300.f).drawAt(m_putDonou.center().movedBy(-100.f, -100.f));
    m_chargeDonou.draw(ColorF(Palette::Red, 0.5f));

    /// <summary>
    /// �u�����y�X�̕`�揈��
    /// </summary>
    for (auto& donouPos : m_putDonous) {
        TextureAsset(U"Donou").resized(50, 100).drawAt(donouPos);
    }

    /// <summary>
    /// �j�̕`�揈��
    /// </summary>
    for (auto& man : m_men) {
        /// <summary>
        /// ���_��Ԃɂ���ĕ`�悷��e�N�X�`����ύX����
        /// </summary>
        if (!man.isAngry()) {
            TextureAsset(U"ManSchool").resized(180, 300).drawAt(man.p0.movedBy(0, 85));
        }
        else {
            TextureAsset(U"ManIkari").resized(180, 300).drawAt(man.p0.movedBy(0, 85));
        }
        /// <summary>
        /// �j�̖ڐ��̕`��
        /// �������ɂ��Ă�
        /// </summary>
        man.draw(ColorF(Palette::Red, 0.2f));
    }
    /// <summary>
    /// ���̕`�揈��
    /// </summary>
    for (auto& woman : m_women) {
        /// <summary>
        /// ���_��Ԃɂ���ĕ`�悷��e�N�X�`����ύX����
        /// </summary>
        if (!woman.isAngry()) {
            TextureAsset(U"WomanSchool").resized(180, 300).drawAt(woman.p0.movedBy(0, 85));
        }
        else {
            TextureAsset(U"WomanIkari").resized(180, 300).drawAt(woman.p0.movedBy(0, 85));
        }
        /// <summary>
        /// ���̖ڐ��̕`��
        /// �������ɂ��Ă�
        /// </summary>
        woman.draw(ColorF(Palette::Red, 0.2f));
    }

    /// <summary>
    /// �y�X���v���C���[�������Ă�ꍇ�̕`�揈��
    /// </summary>
    if (m_donou.has_value()) {
        TextureAsset(U"Donou").resized(100, 100).drawAt(m_donou.value().center());
    }

    /// <summary>
    /// �c�莞�Ԃ̕`��
    /// </summary>
    const int32 timeLeftMillisec = Max(gameTimeMillisec - m_gameTimer.ms(), 0);
    FontAsset(U"GameTime")(U"���k������܂�: {:0>2}'{:0>2} ����"_fmt(timeLeftMillisec / 1000, timeLeftMillisec % 1000 / 10)).draw(60, 60, Palette::Black);

    /// <summary>
    /// �X�R�A�̕`��
    /// </summary>
    FontAsset(U"GameTime")(U"�X�R�A: {0}"_fmt(m_score)).draw(800, 60, Palette::Black);
}
