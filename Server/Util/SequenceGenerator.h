#pragma once
#include <atomic>

class SequenceGenerator
{
public:
	SequenceGenerator(uint64_t _maxNum = UINT64_MAX) : m_maxNumber(_maxNum) {}
	uint64_t Generate();
private:
	std::atomic<uint64_t> m_number = 0;
	const uint64_t m_maxNumber = 0;
};