#include <base/base64.h>
#include <base/detail/base64.h>

namespace bast {
namespace base {

std::string base64_encode(std::uint8_t const *data, std::size_t len)
{
    std::string dest;
    dest.resize(detail::base64::encoded_size(len));
    dest.resize(detail::base64::encode(&dest[0], data, len));
    return dest;
}

std::string base64_encode(std::string_view data)
{
    return base64_encode(reinterpret_cast<std::uint8_t const *>(data.data()), data.size());
}

std::string base64_decode(std::string_view data)
{
    std::string dest;
    dest.resize(detail::base64::decoded_size(data.size()));
    auto const result = detail::base64::decode(&dest[0], data.data(), data.size());
    dest.resize(result.first);
    return dest;
}
} // namespace base
} // namespace bast