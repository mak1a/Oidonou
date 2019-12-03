//
//  Result.hpp
//  Game
//
//  Created by 山口隼矢 on 2019/10/20.
//

#include"Common.hpp"


class Balloon {
private:
	Texture m_texture;
	Duration m_cycleMove;
	double m_speed;
	Vec2 m_position;
public:
	Balloon() = delete;
	Balloon(const Texture& texture_, Duration cycle_, const Vec2& pos_, const double speed_) noexcept
		: m_texture(texture_)
		, m_cycleMove(cycle_)
		, m_position(pos_)
		, m_speed(speed_) {}
	
	void Move() noexcept {
		m_position.y -= m_speed;
	}

	void drawBalloon() const {
		m_texture.draw(m_position.x + 20 * Periodic::Triangle0_1(m_cycleMove), m_position.y);
		TextureAsset (U"Donou").resized (100, 100).draw (
			m_position.x + 20 * Periodic::Triangle0_1 (m_cycleMove) - 50
			, m_position.y + 100
		);
	}
};

class Result : public MyApp::Scene {
private:
	Array<Balloon> m_balloons;
public:

	Result (const InitData& init);

	void update () override;

	void draw () const override;
};
