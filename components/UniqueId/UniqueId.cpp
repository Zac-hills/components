#include "UniqueId.h"

UniqueID::UniqueID()
{
}

UniqueID::~UniqueID()
{
}

unsigned int UniqueID::get()
{
	std::lock_guard<std::mutex> lock(mutex);
	if (!IDS.empty())
	{
		unsigned int result = IDS.front();
		IDS.pop();
		return result;
	}

	return counter++;
}

void UniqueID::release(unsigned int ID)
{
	std::lock_guard<std::mutex> lock(mutex);
	IDS.push(ID);
}
