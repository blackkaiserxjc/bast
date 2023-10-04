
#include "runner.h"

#include <boost/assert.hpp>
#include <boost/scope_exit.hpp>
#include <fmt/format.h>
#include <ranges>
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

Respository command_runner::get() const
{
    return respository_;
}

std::string command_runner::name() const
{
    return name_;
}

int command_runner::run(std::vector<std::string> &args)
{
    auto ec = run_impl(args);
    if (ec == error::no_args)
    {
        show_usage();
    }
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

void command_runner::show_usage()
{
    std::cout << fmt::format("usage:{}", name_);
    std::cout << std::endl;
    std::cout << "       <command> [<args>]" << std::endl;
    std::cout << std::endl;
    std::cout << "Available commands are:" << std::endl;
    for (auto command : respository_ | std::views::values)
    {
        auto name = command->name();
        auto usage = command->usage();
        auto description = command->description();
        std::cout << fmt::format("\n  {:1s} {:2s}\n     {:3s}", name, usage, description) << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << fmt::format("See {} help <command>' for more information on a specific command.", name_);
}
} // namespace cli
} // namespace bast