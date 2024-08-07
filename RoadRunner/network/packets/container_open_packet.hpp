#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
	namespace network {
		namespace packets {
			class ContainerOpenPacket {
			public:
				static const uint8_t packet_id;

				uint8_t window_id;
				uint8_t type;
				uint8_t slot;
				int32_t x;
				int32_t y;
				int32_t z;

				bool deserialize_body(RakNet::BitStream *stream);

				void serialize_body(RakNet::BitStream *stream);
			};
		}
	}
}
