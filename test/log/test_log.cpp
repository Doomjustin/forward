#include <fwd/Log.h>

#include <cstdlib>


int main(int argc, char* argv[])
{
    fwd::log::error("this is a message from {}", "forward log");

    return EXIT_SUCCESS;
}
