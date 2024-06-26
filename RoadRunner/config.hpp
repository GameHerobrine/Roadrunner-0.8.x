#pragma once

#include <cstdint>
#include <string>

// Meta
#define MAX_CLIENTS 10
#define SERVER_PORT 19132

// World
// The seed of the world
extern int SEED;
extern std::string SEEDPROP;
// The spawn position of the player
constexpr float SPAWN_X = 128.f;
constexpr float SPAWN_Y = 128.f;
constexpr float SPAWN_Z = 128.f;
// Game mode
extern bool IS_CREATIVE;

// Movement
// The largest number of blocks the player can move at once before being pulled back
constexpr float MAX_DIST = 5.0;
// If the player is blocked from going past the world border. 
#define WORLD_BORDER false

// I will think later where to put this
constexpr int32_t PROTOCOL = 14;