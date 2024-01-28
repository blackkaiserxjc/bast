#include "basic.h"

namespace bast {
namespace compression {
namespace gzip {

basic_zip::basic_zip(uint64_t chunk_size, std::function<void(z_stream *)> zstream_deleter)
    : chunk_size_{chunk_size}, chunk_char_ptr_(new unsigned char[chunk_size]), zstream_ptr_(new z_stream(), zstream_deleter)
{
}

uint64_t basic_zip::checksum()
{
    return zstream_ptr_->adler;
}

void basic_zip::update_output(buffer &out_buffer)
{
    const uint64_t n_output = chunk_size_ - zstream_ptr_->avail_out;
    if (n_output == 0)
        return;

    zstream_ptr_->avail_out = chunk_size_;
    zstream_ptr_->next_out = chunk_char_ptr_.get();
}

} // namespace gzip
} // namespace compression
} // namespace bast