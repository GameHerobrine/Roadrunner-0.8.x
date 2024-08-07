#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
	namespace network {
		namespace packets {
			class SetEntityLinkPacket {
			public:
				static const uint8_t packet_id;

				int32_t from;
				int32_t to;
				int32_t type;

				bool deserialize_body(RakNet::BitStream *stream);

				void serialize_body(RakNet::BitStream *stream);
			};
		}
	}
}
