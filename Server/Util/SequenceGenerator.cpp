#include "SequenceGenerator.h"

uint64_t SequenceGenerator::Generate()
{
	return m_number.fetch_add(1, std::memory_order_relaxed) + 1;
}
