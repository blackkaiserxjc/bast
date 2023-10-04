#pragma once

#include <list>
#include <memory>
#include <string>

#include "command.h"

namespace bast {
namespace cli {

using Respository = std::unordered_map<std::string, command_ptr>;

class command_runner
{
public:
    command_runner(const std::string &name);

    command_runner(const command_runner &) = delete;
    command_runner &operator=(const command_runner &) = delete;

    ~command_runner() = default;

public:
    /**
     * add command
     * @param cmd
     */
    void add(command_ptr command);

    /**
     * find command
     * @param name
     * @return command
     */
    command_ptr find(const std::string &name) const;

    /**
     * get command list
     * @return command list
     */
    Respository get() const;

    /**
     * get name
     * @return name
     */
    std::string name() const;

    /**
     * run the appropriate
     * @param args input args
     * @return status code
     */
    int run(std::vector<std::string> &args);

    /*
     * run with command options
     * @param argc input arg count
     * @param argv input args
     * @return status code
     */
    int run(int argc, const char *const *argv);

protected:
    error_code run_impl(std::vector<std::string> &args);

    void before_run(command_ptr command);
    void after_run(command_ptr command);
    void show_usage();

    // parse command line options
    std::vector<std::string> parse(int argc, const char *const *argv);

private:
    std::string name_;
    Respository respository_;
};

using command_runner_ptr = std::shared_ptr<command_runner>;

} // namespace cli
} // namespace bast