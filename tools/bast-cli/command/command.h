#pragma once

#include <error/error.h>

#include <span>
#include <string>

namespace bast {
namespace cli {

class command
{
public:
    /**
     * constructor
     * @param name
     * @param description
     */
    command(std::string_view name, std::string_view description);

    /**
     * nocopy able
     */
    command(command &) = delete;
    command &operator=(command &) = delete;

    virtual ~command() = default;

    /**
     * Returns the name of the command.
     * @return the command's name
     */
    [[nodiscard]] virtual std::string name() const;

    /**
     * Returns a description of the command.
     * @return the command's description
     */
    [[nodiscard]] virtual std::string description() const;

    /**
     * Returns usage help for the command
     * @return the command's usage help
     */
    [[nodiscard]] virtual std::string usage() const;

    /**
     * execute the command.
     * @param params
     * @return the outcome of the command
     */
    virtual error_code execute(std::span<std::string> args);

private:
    std::string name_;
    std::string description_;
};

using command_ptr = std::shared_ptr<command>;

template <typename T, typename... Args>
auto make_command(Args &&...args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

} // namespace cli
} // namespace bast
