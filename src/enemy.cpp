#include <enemy.h>
#include <System.h>
#include <Graphics.h>

//Projectile* shot;

Enemy::Enemy(glm::vec2 pos, const char* c) : Entity(pos, c)
{
	SetState(BehaviorState::Seek);
	timer = 0;
	moveSpeed = 1;
}

void Enemy::Update(void)
{
	//printf("in enemy update: %f \n   ", GetFrameDeltaTime());
	switch (GetState())
	{
	case BehaviorState::Seek:
		timer += GetFrameDeltaTime();

		target = GetPlayerPos();

		if (timer > 5) 
		{
			timer = 0;
			SetState(BehaviorState::Fire);
		}
		break;
	case BehaviorState::Fire:
		//printf("Shoot her!\n");

		shot = new Projectile("../../common/sprites/FireballNoOutline.png");
		
		shot->Init(Position + glm::vec2((size.x * 0.5), 0), target);

		this->SetState(BehaviorState::Seek);
		break;
	case BehaviorState::Flee:
		break;
	default:
		SetState(BehaviorState::Seek);
		break;
	}
}

void Enemy::Draw(void)
{
	Entity::Draw();
}

Enemy::BehaviorState Enemy::GetState()
{
	return this->behaviorState;
}

void Enemy::SetState(Enemy::BehaviorState s)
{
	this->behaviorState = s;
}
