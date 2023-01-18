#include "argparse.h"


auto parse_args(int argc, char const * const argv[])
{
    auto parser = argparse::ArgumentParser();
    parser.add_argument("data").help("data to send");
    parser.add_argument("--access-token").help("access token");
    return parser.parse_args(argc, argv);
}

auto main(int argc, char * argv[]) -> int
{
    auto const args = parse_args(argc, argv);
    (void) args;

    return 0;
}
