#include <enemy.h>
#include <System.h>
#include <Graphics.h>

Enemy::BehaviorState currentState;
//Projectile* shot;

Enemy::Enemy(char* c) : Entity(c) 
{

}

void Enemy::Init(glm::vec2 iPos)
{
	Entity::Init(iPos);
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
		printf("Shoot her!\n");

		shot = new Projectile(ROOT_DIR"/common/sprites/FireballnoOutline.png");
		
		shot->Init(Position + glm::vec2((size.x * 0.5), 0), target);

		SetState(BehaviorState::Seek);
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
	return currentState;
}

void Enemy::SetState(BehaviorState s)
{
	currentState = s;
}