add_library(
    ThreadpoolManager
    ThreadpoolManager.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ThreadpoolManager PRIVATE Threads::Threads)