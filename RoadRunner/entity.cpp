#include <entity.hpp>
#include <server.hpp>

using RoadRunner::Entity;
int Entity::entityCounter = 0;
Entity::Entity(RoadRunner::Server* server){
	this->server = server;
	this->entity_id = Entity::entityCounter++;
	this->server->addEntity(this);
}
