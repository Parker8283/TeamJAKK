#include <behaviors.h>
#include <cstdlib>
#include <ctime>
#include <GameRunner.h>

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

		cursor = rand() % 4;
		if (cursor < 2) clockwise = false;
		break;
	case Behavior::AIType::Simple:
		moveTargets.push_back(vec2(0, 0));

		fireTargets.push_back(vec2(0, 0));
		break;
	case Behavior::AIType::Circle:
		for (float angle = 0; angle < 2 * 3.14159265; angle += 0.1f)
		{
			moveTargets.push_back(vec2(radius * cos(angle), radius * sin(angle)));
		}
		fireTargets.push_back(vec2(0, 0));
		cursor = rand() % 24;
		if (cursor < 12) clockwise = false;
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
	vec2 playerPos = vec2(GetPlayer()->GetPosition().x, GetPlayer()->GetPosition().y);
	if (abs(pos.x - (currentTar.x + playerPos.x)) < .1 && abs(pos.y - (currentTar.y + playerPos.y)) < .1)
	{
		if (clockwise) cursor++;
		else cursor--;
		fireCursor++;
		if (cursor >= moveTargets.size()) cursor = 0;
		if (cursor < 0) cursor = (int)moveTargets.size();
		if (fireCursor >= fireTargets.size()) fireCursor = 0;
	}
	return moveTargets.at(cursor) + playerPos;
}

vec2 Behavior::GetFireTarget()
{
	printf("here\n");
	if (leadShots) 
	{
		//printf("%f %f\n", GetPlayerMoveDir().x, GetPlayerMoveDir().y);
		float speed = GetPlayer()->GetPlayerWalkSpeed();
		float moveX = static_cast <float>( GetPlayerMoveDir().x);
		float moveY = static_cast <float>( GetPlayerMoveDir().y);
		return fireTargets.at(fireCursor) + vec2(GetPlayer()->GetPosition()) + vec2(moveX * speed * 1.5, moveY * speed * 1.5);
	}
	return fireTargets.at(fireCursor) + vec2(GetPlayer()->GetPosition());
}