#include "argparse.h"


int main(int argc, char * argv[])
{
    auto parser = argparse::ArgumentParser();
    parser.add_argument("data").help("data to send");
    parser.add_argument("--access-token").help("access token");
    auto args = parser.parse_args(argc, argv);
    (void) args;
}
