#include <sword.h>

static float radius = 1.5f;

Sword::State currentState;


Sword::Sword(const char* file) : Projectile(file, GetPlayerPos(), vec2(0), 1, size)
{
	Position = GetPlayerPos();
	Width    = .8f;
	Height   = .8f;
	size     = glm::vec2(Width, Height);

	speed    = 3;

	currentState = State::Held;
	damage = 1;

	currentSword = this;
}

void Sword::Init()
{
	UpdateState(State::Held);
}

void Sword::Update(void)
{
	float frameDelta = GetFrameDeltaTime();

	switch (GetState())
	{
	case Sword::State::Fly:
		Position += direction * frameDelta * speed;
		rotation += (0.5f * 180.0f / 3.14159265f) * frameDelta;

		
		/**for (it = entities->begin(); it != entities->end(); ++it)
		{
			if (dynamic_cast<Enemy*>(*it) &&  checkCollision(hitBox, (*it)->GetHitBox())) {
				printf("hi\n");
				Enemy* e = dynamic_cast<Enemy*>(*it);
				e->TakeDamage(damage);
				break;
			}
		}*/

		if (abs(Position.x) > 50 || abs(Position.y) > 50)
		{
			UpdateState(State::Held);
		}
		break;
	case Sword::State::Ground:
		break;
	case Sword::State::Held:
		// insert code here to set the rotation and position of the sword based on cursor
		glm::vec3 temp = swordMath();
		rotation = temp.z;
		rotation += glm::radians(45.0f);
		rotation *= -1;

		//printf("%f %f \n", temp.x, temp.y);
		Position = vec3(temp.x, temp.y, 0) * radius + GetPlayerPos();
		//Position = GetPlayerPos();
		//printf("deg: %f\n", glm::degrees(rotation));
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

void Throw(void* null)
{
	
	double xpos, ypos;
	glfwGetCursorPos(GetWindow(), &xpos, &ypos);
	double ndcX = (xpos - (1920 / 2)) / (1920 / 2);
	double ndcY = (ypos - (1080 / 2)) / (1080 / 2);
	vec2 ndc = normalizeDir(vec2(ndcX, -ndcY));
	
	float angle = atan2(ndc.y, ndc.x);
	angle = (angle >= 0 ? angle : (2 * 3.14159265 + angle));
	angle = (angle * 180) / 3.14159265;
	
	currentSword->direction = ndc;
	currentSword->rotation = angle;
	currentSword->UpdateState(Sword::State::Fly);
}