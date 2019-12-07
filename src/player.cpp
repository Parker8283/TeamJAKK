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
	invincTimer = 0;
}


bool Player::Update()
{
	Entity::Update();
	float frameDelta = GetFrameDeltaTime();
	invincTimer += frameDelta;
	
	std::list<Entity*>* entities = GetEntityList();

	glm::vec2 dir = normalizeDir(GetPlayerMoveDir());

	float frameSpeed = speed;
	if (!hasSword) frameSpeed = frameSpeed + 2;
	vec2 nextPos = Position + dir * frameDelta * frameSpeed;

	bool collided = false;
	std::list<Entity*>::iterator it;
	for (it = entities->begin(); it != entities->end(); ++it)
	{
		if (checkCollision(hitBox, (*it)->GetHitBox()) && this != *it) {
			if (*it == this->heldSword)
				this->heldSword->UpdateState(Sword::State::Held);

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

	//Collision for player
	if(!collided)
		Position = nextPos;

	SetView(lookAt(vec3(Position.x, Position.y, 10), vec3(Position.x, Position.y, 0), UP));

	hitBox.Draw();
	return false;
}

void Player::AddScore(uint s) {
	score += s;
}

void Player::DamagePlayer(int damage) {
	if (invincTimer > .75f) {
		curHealth -= damage;
		invincTimer = 0;
	}
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
		GetSoundEngine()->play2D("../../audio/woosh.wav", GL_FALSE);
	}
}

Sword* Player::GetSword()
{
	return heldSword;
}
