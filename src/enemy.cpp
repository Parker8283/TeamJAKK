#include <enemy.h>
#include <System.h>
#include <Graphics.h>
#include <GameRunner.h>
#include <string.h>

#include <cstdlib>
#include <ctime>


Enemy::Enemy(glm::vec2 pos, const char* c, Behavior::AIType mood) : Entity(pos, c)
{
	SetState(BehaviorState::Seek);
	timer = 0;
	speed = 1;
	behavior = new Behavior(mood, 4);
	score = 100;
	srand(time(NULL));
	health = 2;
}

Enemy::Enemy(glm::vec2 pos, Archetype arch) : Entity(pos, arch.enemyTexture)
{
	health = 2;
	score = 100; //Remove Later
	timer =  (static_cast <float>(rand()) / static_cast <float> (RAND_MAX)) * arch.shotFrequency;
	this->speed = arch.moveSpeed;
	behavior = new Behavior(arch.behavior, (float)arch.radius);
	strncpy(weaponFile, arch.shotTexture, strlen(arch.shotTexture) + 1);
	doesShoot = arch.doesShoot;
	shotSpeed = arch.shotSpeed;
	shotFrequency = arch.shotFrequency;
	damage = arch.damage;
	size = arch.size;
	shotSize = arch.shotSize;
	score = arch.score;

	SetState(BehaviorState::Seek);

	AddEnemy(this);
}

bool Enemy::Update(void)
{
	bool collided = false;
	int randX = 0, randY = 0;

	glm::vec2 nextPos;

	std::list<Entity*>* entities = GetEntityList();

	switch (GetState())
	{
	case BehaviorState::Seek:
		timer += GetFrameDeltaTime();
		//printf("%f \n", GetFrameDeltaTime());
		if (doesShoot && timer > shotFrequency)
		{
			//printf("in if\n");
			timer = 0;
			SetState(BehaviorState::Fire);
		}

		moveTarget = behavior->GetMoveTarget(Position);
		if (moveTarget.x == 3.14159265 && moveTarget.y == 3.14159265) {
			SetState(BehaviorState::Flee);
			return 0;
		}

		moveDir = moveTarget - Position;
		moveDir = normalizeDir(moveDir);

		nextPos = Position + moveDir * GetFrameDeltaTime() * speed;
		if (CheckWalls(nextPos)) {
			glm::vec2 nextX = glm::vec2(nextPos.x, Position.y);
			glm::vec2 nextY = glm::vec2(Position.x, nextPos.y);
			if (CheckWalls(nextX) && !CheckWalls(nextY)) {
				Position = nextY;
			} else if (CheckWalls(nextY) && !CheckWalls(nextX)) {
				Position = nextX;
			}
		} else {
			glm::vec2 oldPos = nextPos;
			nextPos = CheckEntity(nextPos, GetPlayer());
			if (oldPos != nextPos) {
				GetPlayer()->DamagePlayer(damage);
			}
			nextPos = CheckEntities(nextPos, GetEnemyList());
			Position = nextPos;
		}

	if (moveDir.x < 0 && !flipped) {
		size.x = size.x * -1;
		flipped = true;
	} else {
		size.x = abs(size.x);
		flipped = false;
	}
	break;
case BehaviorState::Fire:
	//printf("Shoot her!\n");
	target = behavior->GetFireTarget();

	shot = new Projectile(weaponFile, Position + glm::vec2((size.x * 0.5), 0), target, damage, shotSize);

	//shot->Init(Position + glm::vec2((size.x * 0.5), 0), target);

	this->SetState(BehaviorState::Seek);
	break;
case BehaviorState::Flee:
	randX = (rand() % 12) - 6;
	randY = (rand() % 12) - 6;
	if (quadrant(vec2(randX, randY)) == quadrant(GetPlayerPos())) {
		randX = -randX;
	}
	moveTarget = vec2(GetPlayerPos()) + vec2(randX, randY);
	SetState(BehaviorState::Fleeing);
	break;
case BehaviorState::Fleeing:
	timer += GetFrameDeltaTime();
	if (timer > 4)
	{
		timer = 0;
		SetState(BehaviorState::Seek);
	}
	if (abs(Position.x - moveTarget.x) < .1 && abs(Position.y - moveTarget.y) < .1) {
		timer = 0;
		SetState(BehaviorState::Seek);
	}

	moveDir = moveTarget - Position;
	moveDir = normalizeDir(moveDir);
	nextPos = Position + moveDir * GetFrameDeltaTime() * speed;

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
		glm::vec2 oldPos = nextPos;
		nextPos = CheckEntity(nextPos, GetPlayer());
		if (oldPos != nextPos) {
			GetPlayer()->DamagePlayer(damage);
		}
		Position = nextPos;
	}
	
	if (moveDir.x < 0 && !flipped) {
		size.x = size.x * -1;
		flipped = true;
	}
	else if (moveDir.x < 0) {

	}
	else {
		size.x = abs(size.x);
		flipped = false;
	}
	break;
default:
	SetState(BehaviorState::Seek);
	break;
}

if (checkCollision(hitBox, GetPlayer()->GetSword()->GetHitBox()) && GetPlayer()->GetSword()->GetState() == Sword::State::Fly) {
	GetPlayer()->GetSword()->UpdateState(Sword::State::Ground);
	return this->TakeDamage(GetPlayer()->GetSword()->damage);
}

std::list<Entity*>::iterator it;
for (it = entities->begin(); it != entities->end(); ++it)
{
	if (checkCollision(hitBox, (*it)->GetHitBox()) && this != *it) {
		collided = true;
		break;
	}
}

if (!collided)
	Position = nextPos;

hitBox.Draw();
return false;
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

void Enemy::Die()
{
	RemoveEnemy(this);
	IncrementEnemiesKilled();
	GetPlayer()->AddScore(score);
}

bool Enemy::TakeDamage(int takenDam) {
	health -= takenDam;
	if (health <= 0) {
		this->Die();
		return true;
	}

	return false;
}
