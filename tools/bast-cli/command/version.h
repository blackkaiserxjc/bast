
#pragma once

#include "command.h"

namespace bast {
namespace cli {

class version_command : public command
{
public:
    version_command();
    ~version_command();

    error_code execute(std::span<std::string> params) override;
};
} // namespace cli
} // namespace bast