#pragma once

#include "command.h"
#include "runner.h"

namespace bast {
namespace cli {

class help_command : public command
{
public:
    help_command(command_runner_ptr runner);
    ~help_command();

    error_code execute(std::span<std::string> args) override;

private:
    command_runner_ptr runner_;
};

} // namespace cli
} // namespace bast