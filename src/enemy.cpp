#include <enemy.h>
#include <System.h>
#include <Graphics.h>
#include <GameRunner.h>

#include <cstdlib>
#include <ctime>


Enemy::Enemy(glm::vec2 pos, const char* c, Behavior::AIType mood) : Entity(pos, c)
{
	SetState(BehaviorState::Seek);
	timer = 0;
	speed = 1;
	behavior = new Behavior(mood, 4);
	srand(time(NULL));
}

Enemy::Enemy(glm::vec2 pos, Archetype arch) : Entity(pos, arch.enemyTexture)
{
	timer =  (static_cast <float>(rand()) / static_cast <float> (RAND_MAX)) * arch.shotFrequency;
	this->speed = arch.moveSpeed;
	behavior = new Behavior(arch.behavior, (float)arch.radius);
	weaponFile = arch.shotTexture;
	doesShoot = arch.doesShoot;
	shotSpeed = arch.shotSpeed;
	shotFrequency = arch.shotFrequency;
	damage = arch.damage;
	size = arch.size;
	shotSize = arch.shotSize;

	SetState(BehaviorState::Seek);
}

void Enemy::Update(void)
{
	int randX =0, randY=0;
	//printf("in enemy update: %f \n   ", GetFrameDeltaTime());

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
		moveDir = moveTarget - Position;
		moveDir = normalizeDir(moveDir);
		Position += moveDir * GetFrameDeltaTime() * speed;
		if (moveDir.x < 0 && !flipped) {
			size.x = size.x * -1;
			flipped = true;
		} else if (moveDir.x < 0) {

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
		Position += moveDir * GetFrameDeltaTime() * speed;
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

	/**if (checkCollision(hitBox, currentSword->hitBox)) {
		TakeDamage(currentSword->damage);
	}*/
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
	delete shot;
	RemoveEntity(this);
	delete this;
}

void Enemy::TakeDamage(int takenDam)
{
	health -= takenDam;
	if (health <= 0) {
		Die();
	}
}