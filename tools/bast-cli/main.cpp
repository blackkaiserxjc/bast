
#include <iostream>
#include <memory>

#include <command/runner.h>
#include <command/version.h>

using namespace bast::cli;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return EXIT_FAILURE;
    }
    auto runner = std::make_unique<command_runner>("bast-cli");
    runner->add(make_command<version_command>());
    int exitCode = runner->run(argc, argv);
    return exitCode != 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}