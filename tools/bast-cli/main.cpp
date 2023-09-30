#include <cxxopts.hpp>
#include <iostream>

static const char banner[] =
    R"(
BBBBBBBBBBBBBBBBB               AAA                 SSSSSSSSSSSSSSS TTTTTTTTTTTTTTTTTTTTTTT
B::::::::::::::::B             A:::A              SS:::::::::::::::ST:::::::::::::::::::::T
B::::::BBBBBB:::::B           A:::::A            S:::::SSSSSS::::::ST:::::::::::::::::::::T
BB:::::B     B:::::B         A:::::::A           S:::::S     SSSSSSST:::::TT:::::::TT:::::T
  B::::B     B:::::B        A:::::::::A          S:::::S            TTTTTT  T:::::T  TTTTTT
  B::::B     B:::::B       A:::::A:::::A         S:::::S                    T:::::T
  B::::BBBBBB:::::B       A:::::A A:::::A         S::::SSSS                 T:::::T
  B:::::::::::::BB       A:::::A   A:::::A         SS::::::SSSSS            T:::::T
  B::::BBBBBB:::::B     A:::::A     A:::::A          SSS::::::::SS          T:::::T
  B::::B     B:::::B   A:::::AAAAAAAAA:::::A            SSSSSS::::S         T:::::T
  B::::B     B:::::B  A:::::::::::::::::::::A                S:::::S        T:::::T
  B::::B     B:::::B A:::::AAAAAAAAAAAAA:::::A               S:::::S        T:::::T
BB:::::BBBBBB::::::BA:::::A             A:::::A  SSSSSSS     S:::::S      TT:::::::TT
B:::::::::::::::::BA:::::A               A:::::A S::::::SSSSSS:::::S      T:::::::::T
B::::::::::::::::BA:::::A                 A:::::AS:::::::::::::::SS       T:::::::::T
BBBBBBBBBBBBBBBBBAAAAAAA                   AAAAAAASSSSSSSSSSSSSSS         TTTTTTTTTTT
    )";

int main(int argc, char *argv[])
{
    cxxopts::Options options("bast-cli", "A brief description");
    options.add_options()("b,bar", "Param bar", cxxopts::value<std::string>())("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))("f,foo", "Param foo", cxxopts::value<int>()->default_value("10"))("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    bool debug = result["debug"].as<bool>();
    std::string bar;
    if (result.count("bar"))
    {
        bar = result["bar"].as<std::string>();
    }
    int foo = result["foo"].as<int>();
    std::cout << banner << std::endl;
    return 0;
}