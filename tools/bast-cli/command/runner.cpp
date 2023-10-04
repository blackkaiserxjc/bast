
#include "runner.h"

#include <boost/assert.hpp>
#include <boost/scope_exit.hpp>
#include <regex>
#include <span>

namespace bast {
namespace cli {

command_runner::command_runner(const std::string &name)
    : name_(name)
{
}

void command_runner::add(command_ptr command)
{
    BOOST_ASSERT(command != nullptr);
    auto name = command->name();
    if (!respository_.contains(name))
    {
        respository_.emplace(command->name(), command);
    }
}

command_ptr command_runner::find(const std::string &name) const
{
    auto iter = respository_.find(name);
    return iter != respository_.end() ? iter->second : nullptr;
}

int command_runner::run(std::vector<std::string> &args)
{
    auto ec = run_impl(args);
    return ec.value() > 0 ? ec.value() : 0;
}

int command_runner::run(int argc, const char *const *argv)
{
    auto args = parse(argc, argv);
    return run(args);
}

error_code command_runner::run_impl(std::vector<std::string> &args)
{
    if (args.empty())
        return error::no_args;

    auto cmd_name = args[0];
    auto cmd_args = std::span{std::begin(args) + 1, std::end(args)};
    auto cmd = find(cmd_name);
    if (!cmd)
        return error::not_found_cmd;

    before_run(cmd);
    BOOST_SCOPE_EXIT_ALL(&)
    {
        after_run(cmd);
    };
    return cmd->execute(cmd_args);
}

std::vector<std::string> command_runner::parse(int argc, const char *const *argv)
{
    std::vector<std::string> args;
    for (auto index = 1; index < argc; index++)
    {
        args.emplace_back(argv[index]);
    }
    if (args.size() > 0)
    {
        auto &arg = args[0];
        if (arg == "-h" || arg == "--help")
        {
            arg = "help";
        }
        else if (arg == "-v" || arg == "--version")
        {
            arg = "version";
        }
    }
    return args;
}

void command_runner::before_run(command_ptr command)
{
}

void command_runner::after_run(command_ptr command)
{
}

} // namespace cli
} // namespace bast