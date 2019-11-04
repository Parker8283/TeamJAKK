#include <sword.h>

static float radius = 1.5f;

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
		glm::vec3 temp = swordMath();
		rotation = temp.z;
		rotation += glm::radians(45.0f);
		rotation *= -1;

		printf("%f %f \n", temp.x, temp.y);
		Position = vec3(temp.x, temp.y, 0) * radius + GetPlayerPos();
		//Position = GetPlayerPos();
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