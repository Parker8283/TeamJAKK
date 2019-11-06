#include <projectile.h>
#include <math.h>
#include <GameMath.h>
#include <glm/glm.hpp>
#include <System.h>
#include <GameRunner.h>

#define PI 3.14159265

Projectile::Projectile(const char* file) : Entity(glm::vec2(0), file)
{

}

Projectile::~Projectile()
{

}

void Projectile::Init(glm::vec2 iPos, glm::vec2 target)
{
	direction.y = (float)target.y - iPos.y;
	direction.x = (float)target.x - iPos.x;

	size = glm::vec2(0.4f, 0.4f);

	speed = 2;

	direction = normalizeDir(direction);

	rotation = (double)atan2(direction.y , direction.x);
	rotation = (rotation >= 0 ? rotation : (2 * PI + rotation));
	//printf("radians: %f, deg: %f", rotation, rotation * 180 / PI);

	//AddEntity(this);
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
