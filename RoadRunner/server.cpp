#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <PacketPriority.h>
#include <RakNetTypes.h>
#include <network/packets/chat_packet.hpp>
#include <network/packets/update_block_packet.hpp>
#include <server.hpp>
#include "world/perlin.hpp"
#include "block/block.hpp"
#include <chrono>
#include <thread>


using RoadRunner::block::Block;
using RoadRunner::Server;
using RoadRunner::network::packets::ChatPacket;using RoadRunner::network::packets::UpdateBlockPacket;

void Server::post_to_chat(std::string message) {
    ChatPacket msg;
    msg.message = message.c_str();
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(msg.packet_id);
    msg.serialize_body(&send_stream);
    std::map<const RakNet::RakNetGUID, RoadRunner::Player *>::iterator it = this->players.begin();
    while (it != this->players.end()) {
        this->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
        ++it;
    }
}

void Server::send_block_data(int32_t x, int32_t y, int32_t z, uint8_t blockid, uint8_t meta) {
    UpdateBlockPacket pk;
    pk.x = x;
    pk.y = y & 0xff;
    pk.z = z;
    pk.block = blockid;
    pk.meta = meta;

    //TODO some broadcast packet method?
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(pk.packet_id);
    pk.serialize_body(&send_stream);

    std::map<const RakNet::RakNetGUID, RoadRunner::Player *>::iterator it = this->players.begin();
    while (it != this->players.end()) {
        this->peer->Send(&send_stream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
        ++it;
    }

}

unsigned long long int getTimeMS() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Server* Server::INSTANCE;

Server::Server(uint16_t port, uint32_t max_clients) {
    Server::INSTANCE = this;

    Block::initBlocks();

    this->entity_id = 1;
    this->peer = RakNet::RakPeerInterface::GetInstance();
    this->is_running = true;
	this->world = new RoadRunner::world::World(0); //TODO seed and othet stuff
	
	//TODO better gen, move out of here
    printf("Generating the world\n");
	for(int index = 0; index < 256; ++index){
		RoadRunner::world::Perlin perlin;
		int chunkX = this->world->chunks[index]->x; //TODO nullptr checks?
		int chunkZ = this->world->chunks[index]->z;
		RoadRunner::world::Chunk* chunk = this->world->chunks[index];
		for (int32_t x = 0; x < 16; ++x) {
            for (int32_t z = 0; z < 16; ++z) {
				int32_t y = (int32_t)perlin.perlin(((chunkZ << 4) + z), ((chunkX << 4) + x), 10.0 * (float)world->seed, 1, 1, 1, 0.2, 2) + 62;
				
				int32_t start_point = y;
                while (y >= 0) {
                    if (y < 1 && y >= 0) {
                        chunk->set_block_id(x, y, z, 7);
                    } else if (y < start_point && y > start_point - 4) {
                        if (y > 60) {
                            chunk->set_block_id(x, y, z, 3);
                        } else {
                            chunk->set_block_id(x, y, z, 13);
                        }
                    } else if (y == start_point) {
                        if (y > 61) {
                        	chunk->set_block_id(x, y, z, 2);
                        } else {
							chunk->set_block_id(x, y, z, 13);
                        }
                    } else {
                        chunk->set_block_id(x, y, z, 1);
                    }
                    --y;
                }
                for (int32_t i = 0; i < 63; ++i) {
                    if (chunk->get_block_id(x, i, z) == 0) {
                        chunk->set_block_id(x, i, z, 9);
                    }
                }
				
			}
		}
	}
	
    EntityIDGenerator idGen;

    RakNet::Packet *packet;

    printf("Starting the server on port %d...\n", port);
    
    RakNet::SocketDescriptor sd(port, 0);
    RakNet::StartupResult result = peer->Startup(max_clients, &sd, 1);
    switch (result) {
        case RakNet::RAKNET_STARTED:
            printf("Started successfully\n");
            break;
        case RakNet::SOCKET_PORT_ALREADY_IN_USE:
            printf("Failed: The port is already in use.\n");
            goto forceend;
        default:
            printf("Failed: %d\n", result);
            goto forceend;
    }
   

    peer->SetMaximumIncomingConnections(max_clients);
	double nextUpdate = 0.0;
    
    while (this->is_running) {
        RakNet::RakString data = "MCCPP;MINECON;Test";
        RakNet::BitStream stream;
        data.Serialize(&stream);
        peer->SetOfflinePingResponse((const char *)stream.GetData(), stream.GetNumberOfBytesUsed());
	unsigned long long int timeMS = getTimeMS();
	if(nextUpdate > timeMS){
        unsigned long long int skip = (nextUpdate - timeMS);
		//printf("skipping %f\n", skip/1000);
		//usleep((int)skip);
        std::this_thread::sleep_for(std::chrono::milliseconds(skip));
	}
	nextUpdate = timeMS+50;
        packet = peer->Receive();
        if (!packet) continue;
	
        if (packet->bitSize != 0) {
            RakNet::BitStream receive_stream(packet->data, BITS_TO_BYTES(packet->bitSize), false);

            uint8_t packet_id;
            receive_stream.Read<uint8_t>(packet_id);

            switch (packet_id) {
            case ID_NEW_INCOMING_CONNECTION:
                printf("A new connection is incoming.\n");
                if (this->players.count(packet->guid) == 0) {
                    RoadRunner::Player *player = new RoadRunner::Player(this, &idGen);
                    player->guid = packet->guid;
                    if (this->reuseable_entity_ids.size()) {
                        player->entity_id = this->reuseable_entity_ids.back();
                        this->reuseable_entity_ids.pop_back();
                    } else {
                        player->entity_id = this->entity_id++;
                    }
                    this->players[packet->guid] = player;
                }
                break;
            case ID_NO_FREE_INCOMING_CONNECTIONS:
                printf("The server is full.\n");
                break;
            case ID_DISCONNECTION_NOTIFICATION:
            case ID_CONNECTION_LOST:
                printf("A client lost the connection.\n");
                if (this->players.count(packet->guid) != 0) {
                    delete this->players[packet->guid];
                    this->players.erase(packet->guid);
                }
                break;
            default:
                if (this->players.count(packet->guid) != 0) {
                    this->players[packet->guid]->handle_packet(packet_id, &receive_stream);
                }
                break;
            }
        }
        peer->DeallocatePacket(packet);
    }

    forceend:
    RakNet::RakPeerInterface::DestroyInstance(peer);
	delete this->world;
}
