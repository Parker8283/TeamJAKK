#include <sword.h>

Sword::State currentState;

Sword::Sword(char* file) : Projectile(file)
{
	Position = GetPlayerPos();
	Width = .8f;
	Height = .8f;
	size = glm::vec2(Width, Height);

	speed = 2;
}

void Sword::Init()
{
	Entity::Init(Position);
	UpdateState(State::Held);
}

void Sword::Update(void)
{
	switch (GetState())
	{
	case State::Fly:
		break;
	case State::Ground:
		break;
	case State::Held:
		// insert code here to set the rotation and position of the sword based on cursor

		rotation = swordMath();
		rotation += glm::radians(-135.0f);
		rotation *= -1;
		Position = GetPlayerPos();
		Position.x += .1 * sin(rotation);
		Position.y += .1 * cos(rotation);
		//printf("deg: %f\n", glm::degrees(rotation));

		break;
	default:
		break;
	}
}

Sword::State Sword::GetState()
{
	return currentState;
}

void Sword::UpdateState(State s)
{
	currentState = s;
}