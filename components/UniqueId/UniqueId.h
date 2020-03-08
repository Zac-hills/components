#include <queue>
#include <mutex>

class UniqueID {
public:
	UniqueID();
	~UniqueID();

	unsigned int get();
	void release(unsigned int);
private:
	std::queue<unsigned int> IDS;
	unsigned int counter = 0;
	std::mutex mutex;
};