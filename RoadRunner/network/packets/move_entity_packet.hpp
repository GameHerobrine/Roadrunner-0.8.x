#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
	namespace network {
		namespace packets {
			class MoveEntityPacket {
			public:
				static const uint8_t packet_id;

				bool deserialize_body(RakNet::BitStream *stream);

				void serialize_body(RakNet::BitStream *stream);
			};
		}
	}
}
