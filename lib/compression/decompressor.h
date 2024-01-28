#pragma once

#include <boost/beast/core/flat_buffer.hpp>
#include <memory>

namespace bast {
namespace compression {

using buffer = boost::beast::flat_buffer;

class decompressor
{
public:
    virtual ~decompressor() = default;

    /**
     * decompress data
     * @param input_buffer
     * @param out_buffer
     */
    virtual void decompress(const buffer &input_buffer, buffer &out_buffer) = 0;
};

using decompressor_ptr = std::unique_ptr<decompressor>;

} // namespace compression
} // namespace bast