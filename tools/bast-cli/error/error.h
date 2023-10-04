#pragma once

#include "error_types.h"

namespace bast {
namespace cli {

enum class error
{
    /**
     * the operation completed successfully.
     */
    success = 0,

    /***
     * input args is empty
     */
    no_args = 1,

    /**
     * not found command
     */
    not_found_cmd = 2,
};

enum class condition
{
    fatal = 1
};

} // namespace cli
} // namespace bast

#include "impl/error.h"