#include "Point.h"
#include "MyClientHandler.h"
#include "FileCacheManager.h"
#include "SolverSearcher.h"
#include "AStar.h"
#include "MyParallelServer.h"

namespace boot {
    class Main {
    public:
        int main(int argc, char *argv[]) {
            return 0;
        }
    };
}

int main(int argc ,char* argv[]) {
    boot::Main main1;
    main1.main(argc, argv);
    server_side::Server* d = new MyParallelServer();
    Solver<Searchable<Point>*, string>* solver = new SolverSearcher(new AStar<Point>());
    CacheManager* cacheManager = new FileCacheManager();
    ClientHandler* ds = new MyClientHandler(solver, cacheManager);
    d->open(stoi(argv[1]),ds);
    delete (d);
    delete (solver);
    delete (cacheManager);
    delete (ds);
    return 0;
}