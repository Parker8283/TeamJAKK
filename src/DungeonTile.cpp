//Class to model a (default 32x32p) tile in a map
//@author Cody Keilitz
//Last modified Oct 30 2019

#include <DungeonTile.h>
#include <glm/glm.hpp>
#include <Graphics.h>

using namespace glm;

static const mat2 rot = {
  -1,  0,
  0, -1
};

DungeonTile::DungeonTile(bool p, float x, float y) {
    passable = p;
    worldX = x;
    worldY = y;
}

void DungeonTile::Draw(void) {
    glUseProgram(GetShader());

    mat4 M = translate(mat4(1), vec3(this->worldX, this->worldY, 0));
    mat4 MVP = GetProjection() * GetView() * M;

	MVP = scale(MVP, vec3(2.0f, 2.0f, 1.0f));

    glBindVertexArray(GetTileVAO());
    
    if (this->isPassable())
        glBindTexture(GL_TEXTURE_2D, GetFloorTextureID());
    else
        glBindTexture(GL_TEXTURE_2D, GetWallTextureID());

    glUniform1i(glGetUniformLocation(GetShader(), "tex"), 0);
    glUniformMatrix2fv(glGetUniformLocation(GetShader(), "uvRot"), 1, GL_FALSE, &rot[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(GetShader(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(GetTileVAO());
    glUseProgram(GetShader());
}

void DungeonTile::setPassable(bool p) {
    passable = p;
}

void DungeonTile::setWorldCoordCenter(float x, float y) {
    worldX = x;
    worldY = y;
}

bool DungeonTile::isPassable() {
    return passable;
}

bool DungeonTile::moveOnEvent() {
    return false;
}

inline float DungeonTile::getWorldX() {
    return worldX;
}

inline float DungeonTile::getWorldY() {
    return worldY;
}

