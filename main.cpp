#include "network.h"

int main()
{

    Network n;

    n.import_network("test_network.txt");

    n.display_all();

    n.display_router("a");

    return 0;
}
