#include <cstdlib>

import fwd.log;


int main(int argc, char* argv[])
{
    fwd::log::error("this is a message from {}", "forward log");

    return EXIT_SUCCESS;
}
