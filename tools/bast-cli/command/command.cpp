#include "command.h"

namespace bast {
namespace cli {

command::command(std::string_view name, std::string_view description)
    : name_(name), description_(description)
{
}

std::string command::name() const
{
    return this->name_;
}

std::string command::description() const
{
    return this->description_;
}

std::string command::usage() const
{
    return "";
}

error_code command::execute(std::span<std::string> args)
{
    return error::success;
}

} // namespace cli
} // namespace bast