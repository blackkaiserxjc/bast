
#include <iostream>
#include <memory>

#include <command/help.h>
#include <command/runner.h>
#include <command/version.h>

using namespace bast::cli;

int main(int argc, char *argv[])
{
    auto runner = std::make_shared<command_runner>("bast-cli");
    runner->add(make_command<help_command>(runner));
    runner->add(make_command<version_command>());
    int ec = runner->run(argc, argv);
    return ec != 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}