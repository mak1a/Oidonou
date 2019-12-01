//
//  Result.hpp
//  Game
//
//  Created by 山口隼矢 on 2019/10/20.
//

#include"Common.hpp"

class Result : public MyApp::Scene {
private:
	Array<Texture> m_balloons;
	Array<Duration> m_balloonsPos;
	Array<double> m_posXs;
	Array<Vec2> m_posYs;
public:

	Result (const InitData& init);

	void update () override;

	void draw () const override;
};
