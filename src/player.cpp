#include <player.h>
#include <GameRunner.h>
#include <sword.h>

char* textureFilepath = "../../common/sprites/GungeonRipoffBase.png";
char* textureBack = ".. / .. / common / sprites / GungeonRipoffBaseBack.png";
static const vec3 UP = vec3(0, 1, 0);
Sword* heldSword;

Player::Player() : Entity(glm::vec2(0, 0), textureFilepath)
{
	front = LoadTexture(textureFilepath);
	back = LoadTexture(textureBack);
	hasSword = true;
	health = 10;
	speed = 5.0f;

	Position = glm::vec2(0, 0);
	SetPlayer(this);

	heldSword = new Sword("../../common/sprites/Sword1.png");

}


void Player::Update()
{
	float frameDelta = GetFrameDeltaTime();
	
	std::list<Entity*>* entities = GetEntityList();

	glm::vec2 dir = normalizeDir(GetPlayerMoveDir());

	vec2 nextPos = Position + dir * frameDelta * speed;

	CollisionBox hitBox = CollisionBox(1, 1, &nextPos);

	bool collided = false;
	std::list<Entity*>::iterator it;
	for (it = entities->begin(); it != entities->end(); ++it)
	{
		if (checkCollision(hitBox, (*it)->GetHitBox())) {
			collided = true;
			break;
		}
	}

	//Collision disabled for now
	//if(!collided)
	Position = nextPos;

	SetView(lookAt(vec3(Position.x, Position.y, 10), vec3(Position.x, Position.y, 0), UP));
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

float Player::GetPlayerWalkSpeed(void)
{
	return speed;
}

void Player::Attack(void* null)
{
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
}

Sword* Player::GetSword()
{
	return heldSword;
}