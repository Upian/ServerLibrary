#pragma once
#include  <type_traits>
namespace IOCP
{
	class PacketBuf;

	template<typename T>
	concept DerivedFromPacketBuf = std::is_base_of_v<IOCP::PacketBuf, T>;
}