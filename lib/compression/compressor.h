#pragma one

#include <boost/beast/core/flat_buffer.hpp>
#include <memory>

namespace bast {
namespace compression {

using buffer = boost::beast::flat_buffer;

enum class state
{
    flush,
    finish
};

/**
 * compress interface
 */
class compressor
{
public:
    virtual ~compressor() = default;

    /**
     * compress data buffer
     * @param buffer
     * @param state
     */
    virtual void compress(buffer &buffer, state state) = 0;
};

using compressor_ptr = std::unique_ptr<compressor>;

} // namespace compression
} // namespace bast