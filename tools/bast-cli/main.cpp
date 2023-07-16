#include <iostream>

static const char banner[] =
    R"(
        ____     _     ____  _____
        | __ )   / \   / ___||_   _|
        |  _ \  / _ \  \___ \  | |
        | |_) |/ ___ \  ___) | | |
        |____//_/   \_\|____/  |_|
    )";

int main()
{
    std::cout << banner << std::endl;
    return 0;
}