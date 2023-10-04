//
// Created by blackkaiser on 10/4/23.
//

#include "help.h"

#include <fmt/format.h>

namespace bast {
namespace cli {

help_command::help_command(command_runner_ptr runner)
    : command("help", "get help on commands"), runner_(runner)
{
}

help_command::~help_command()
{
}

error_code help_command::execute(std::span<std::string> args)
{
    if (args.empty())
        return error::no_help_args;

    auto name = args.front();
    auto command = runner_->find(name);
    if (!command)
        return error::not_found_cmd;
    std::cout << fmt::format("{}-{}-{}", runner_->name(), command->name(), command->description());
    std::cout << std::endl;
    auto usage = command->usage();
    if (!usage.empty())
    {
        std::cout << fmt::format("usage: {}-{} {}", runner_->name(), command->name(), usage);
        std::cout << std::endl;
    }
    return error::success;
}

} // namespace cli
} // namespace bast
