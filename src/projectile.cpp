#include <projectile.h>
#include <math.h>
#include <GameMath.h>
#include <glm/glm.hpp>
#include <System.h>
#include <GameRunner.h>

#define PI 3.14159265

Projectile::Projectile(const char* file, glm::vec2 iPos, glm::vec2 target, float damage, glm::vec2 size) : Entity(iPos, file)
{
	this->damage = damage;
	Position = iPos;
	direction.y = (float)target.y - iPos.y;
	direction.x = (float)target.x - iPos.x;


	this->size = size;

	speed = 7;

	direction = normalizeDir(direction);

	rotation = (double)atan2(direction.y, direction.x);
	rotation = (rotation >= 0 ? rotation : (2 * PI + rotation));

	HitEnemy = false;
}

Projectile::~Projectile()
{

}

void Projectile::Update()
{
	//printf("Projectile update run\n");
	float frameDelta = GetFrameDeltaTime();
	Position += direction * frameDelta * speed;
	if (abs(Position.x) > 50 || abs(Position.y) > 50)
	{
		RemoveEntity(this);
		delete this;
	}
	
}
