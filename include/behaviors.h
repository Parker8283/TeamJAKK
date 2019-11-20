#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include <Graphics.h>
#include <Controller.h>
#include <vector>

using namespace glm;

class Behavior {
public:
	enum class AIType {
		Cardinal, Simple, Circle, Lead
	};
	std::vector<vec2> moveTargets;
	std::vector<vec2> fireTargets;
	int cursor;
	int fireCursor;
	bool leadShots = false;
	bool clockwise = true;
	AIType ai;

	Behavior();
	Behavior(AIType, float);
	Behavior(AIType, float, float);
	vec2 GetMoveTarget(vec2);
	vec2 GetFireTarget();
};

#endif