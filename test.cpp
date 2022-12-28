#include "RCU.h"
#include <memory.h>

int main (int argc, char **argv) {
    std::shared_ptr<RCU::ThreadpoolManager> t = std::make_shared<RCU::ThreadpoolManager>();
    t->QueueJob([]{std::cout << "Running" << std::endl;});
    t->QueueJob([]{std::cout << "Running" << std::endl;});
    t->QueueJob([]{std::cout << "Running" << std::endl;});
    t->QueueJob([]{std::cout << "Running" << std::endl;});
    t->Start();
    t->Stop();
}