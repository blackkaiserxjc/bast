#pragma once

#include <boost/beast/core.hpp>
#include <functional>
#include <memory>

#include <zlib.h>

namespace bast {
namespace compression {
namespace gzip {

using buffer = boost::beast::flat_buffer;

class basic_zip
{
public:
    basic_zip(uint64_t chunk_size, std::function<void(z_stream *)> zstream_deleter);

    uint64_t checksum();

protected:
    void update_output(buffer &out_buffer);

    const uint64_t chunk_size_;
    bool initialized_{false};

    const std::unique_ptr<unsigned char[]> chunk_char_ptr_;
    const std::unique_ptr<z_stream, std::function<void(z_stream *)>> zstream_ptr_;
};

} // namespace gzip
} // namespace compression
} // namespace bast