#include <player.h>
#include <GameRunner.h>
#include <sword.h>

static const vec3 UP = vec3(0, 1, 0);

Player::Player() : Entity(glm::vec2(0, 0), "../../common/sprites/GungeonRipoffBase.png")
{
	front = LoadTexture("../../common/sprites/GungeonRipoffBase.png");
	back = LoadTexture("../../common/sprites/GungeonRipoffBaseBack.png");
	hasSword  = true;
	maxHealth = 10;
	curHealth = maxHealth;
	speed = 5.0f;
	Position = glm::vec2(5, 7);
	score = 0;
	
	SetPlayer(this);

	heldSword = new Sword("../../common/sprites/Sword1.png");
	hasSword = true;
}


bool Player::Update()
{
	Entity::Update();
	float frameDelta = GetFrameDeltaTime();
	
	std::list<Entity*>* entities = GetEntityList();

	glm::vec2 dir = normalizeDir(GetPlayerMoveDir());

	vec2 nextPos = Position + dir * frameDelta * speed;

	CollisionBox hitBox = CollisionBox(1, 1, nextPos);

	bool collided = false;
	std::list<Entity*>::iterator it;
	for (it = entities->begin(); it != entities->end(); ++it)
	{
		if (checkCollision(hitBox, (*it)->GetHitBox())) {
			collided = true;
			break;
		}
	}

	if (CheckWalls(nextPos)) {
		glm::vec2 nextX = glm::vec2(nextPos.x, Position.y);
		glm::vec2 nextY = glm::vec2(Position.x, nextPos.y);
		if (CheckWalls(nextX) && !CheckWalls(nextY)) {
			Position = nextY;
		}
		else if (CheckWalls(nextY) && !CheckWalls(nextX)) {
			Position = nextX;
		}
		else {

		}
	}
	else {
		Position = nextPos;
	}

	//Collision disabled for now
	//if(!collided)
	//Position = nextPos;

	SetView(lookAt(vec3(Position.x, Position.y, 10), vec3(Position.x, Position.y, 0), UP));

	return false;
}

void Player::DamagePlayer(int damage) {
	curHealth -= damage;
}

void Player::Draw()
{
	double xPos, yPos;
	glfwGetCursorPos(GetWindow(), &xPos, &yPos);
	yPos = (yPos - (1080 / 2)) / (yPos / 2);
	xPos = (xPos - (1920 / 2)) / (xPos / 2);

	if (yPos < 0) {
		texture = back;
	}
	else {
		texture = front;
	}

	Entity::Draw();
}

glm::vec3 Player::GetPosition()
{
	return glm::vec3(Position, 0);
}

int Player::GetHealth(void) {
	return curHealth;
}

int Player::GetMaxHealth(void) {
	return maxHealth;
}

float Player::GetPlayerWalkSpeed(void)
{
	return speed;
}

void Player::Attack(void* null)
{
	if (hasSword) {
		double xpos, ypos;
		glfwGetCursorPos(GetWindow(), &xpos, &ypos);
		double ndcX = (xpos - (1920 / 2)) / (1920 / 2);
		double ndcY = (ypos - (1080 / 2)) / (1080 / 2);
		vec2 ndc = normalizeDir(vec2(ndcX, -ndcY));

		float angle = atan2(ndc.y, ndc.x);
		angle = (angle >= 0 ? angle : (2.0f * 3.14159265f + angle));
		angle = (angle * 180) / 3.14159265f;

		heldSword->direction = ndc;
		heldSword->rotation = angle;
		heldSword->UpdateState(Sword::State::Fly);
		hasSword = false;
	}
}

Sword* Player::GetSword()
{
	return heldSword;
}
