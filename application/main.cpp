#include "argparse.h"
#include <string>


auto parse_args(int argc, char const * const argv[])
{
    auto parser = argparse::ArgumentParser();
    parser.add_argument("data").help("data to send");
    parser.add_argument("--access-token").help("access token");
    return parser.parse_args(argc, argv);
}

auto send(std::string const & data, std::string const & token)
{
    (void) data;
    (void) token;
}

auto main(int argc, char * argv[]) -> int
{
    auto const args = parse_args(argc, argv);
    auto const data = args.get_value("data");
    auto const token = args.get_value("access_token");
    send(data, token);

    return 0;
}
