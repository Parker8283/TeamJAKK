#include <behaviors.h>

Behavior::Behavior()
{
	cursor = 0;
	fireCursor = 0;
	moveTargets.push_back(vec2(0, 0));

	fireTargets.push_back(vec2(0, 0));
}

Behavior::Behavior(Behavior::AIType type, float radius)
{
	cursor = 0;
	fireCursor = 0;
	switch (type)
	{
	case Behavior::AIType::Cardinal:
		moveTargets.push_back(vec2(-radius, 0));
		moveTargets.push_back(vec2(0, radius));
		moveTargets.push_back(vec2(radius, 0));
		moveTargets.push_back(vec2(0, -radius));

		fireTargets.push_back(vec2(1, 0));
		fireTargets.push_back(vec2(0, -1));
		fireTargets.push_back(vec2(-1, 0));
		fireTargets.push_back(vec2(0, 1));
		break;
	case Behavior::AIType::Simple:
		moveTargets.push_back(vec2(0, 0));

		fireTargets.push_back(vec2(0, 0));
		break;
	case Behavior::AIType::Circle:
		for (float angle = 0; angle < 2 * 3.14159265; angle += .1)
		{
			moveTargets.push_back(vec2(radius * cos(angle), radius * sin(angle)));
		}
		fireTargets.push_back(vec2(0, 0));
		break;
	case Behavior::AIType::Lead:
		moveTargets.push_back(vec2(0, 0));

		fireTargets.push_back(vec2(0, 0));

		leadShots = true;
		break;
	default:
		break;
	}

}

vec2 Behavior::GetMoveTarget(vec2 pos)
{
	vec2 currentTar = moveTargets.at(cursor);
	vec2 playerPos = vec2(GetPlayerPos().x, GetPlayerPos().y);
	if (abs(pos.x - (currentTar.x + playerPos.x)) < .1 && abs(pos.y - (currentTar.y + playerPos.y)) < .1)
	{
		cursor++;
		fireCursor++;
		if (cursor >= moveTargets.size()) cursor = 0;
		if (fireCursor >= fireTargets.size()) fireCursor = 0;
	}
	return moveTargets.at(cursor) + playerPos;
}

vec2 Behavior::GetFireTarget()
{
	if (leadShots) 
	{
		//printf("%f %f\n", GetPlayerMoveDir().x, GetPlayerMoveDir().y);
		return fireTargets.at(fireCursor) + vec2(GetPlayerPos()) + 
			vec2(GetPlayerMoveDir().x * GetPlayerWalkSpeed() * 1.5, GetPlayerMoveDir().y * GetPlayerWalkSpeed() * 1.5) ;
	}
	return fireTargets.at(fireCursor) + vec2(GetPlayerPos());
}