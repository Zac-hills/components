#include <string>
#include <functional>

namespace IO
{
struct FileBuffer
{
    unsigned int fileSize;
    std::string buffer;
    std::string fileName;
};

class File
{
public:
    void load(const std::string &fileName, std::function<void(const FileBuffer &)> callback);

private:
};
class JSON
{
public:
private:
};
class CSV
{
public:
private:
};

} // namespace IO
