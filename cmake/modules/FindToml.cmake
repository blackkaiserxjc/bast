# - Find CppToml
# Find the CppToml library
#
# TOML_INCLUDE_DIR, where to find toml headers
# TOML_FOUND, If false, do not try to use toml

find_path(TOML_INCLUE_DIR NAMES cpptoml.h)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    TOML 
    REQUIRED_VARS TOML_INCLUE_DIR
)
mark_as_advanced(TOML_INCLUDE_DIR)

if (TOML_NOT_FOUND AND NOT(TARGTE toml::toml))
    add_library(toml INTERFACE)
    set_target_properties(toml PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${TOML_INCLUDE_DIR}"
        INTERFACE_COMPILE_FEATURES cxx_std_11
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    )
    add_library(toml::toml ALIAS toml)
endif()