#include <iostream>
#include "MySerialServer.h"
#include "State.h"
#include <queue>
#include "Point.h"
#include "BestFirstSearch.h"
#include "MyClientHandler.h"
#include "FileCacheManager.h"
#include "SolverSearcher.h"
#include "BFS.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
//    MySerialServer* mySerialServer = new MySerialServer();
//    Solver<string, string>* solver = new StringReverser();
//    FileCacheManager* fileCacheManager = new FileCacheManager();
//    ClientHandler* clientHandler = new MyTestClientHandler(solver, fileCacheManager);
//    mySerialServer->open(5400, clientHandler);
    //string g = "as";
    //string f = "jk";
    //fileCacheManager->writeInfo(g, f);
//    class Comp {
//    public:
//        bool operator () (State<Point>* left, State<Point>* right) {
//            return (left->getCost()) > (right->getCost());
//        }
//    };
//
//    priority_queue<State<Point>*, vector<State<Point>*>,Comp> p;
//
//    int one = 1;
//    int two = 2;
//    int eight = 8;
//    int three = 3;
//    int seven = 7;
//    int five = 5;
//    int ten = 10;
//
//
//    p.push(new State<Point>(new Point(2, 3), 3));
//    p.push(new State<Point>(new Point(7,0), 2));
//    p.push(new State<Point>(new Point(1,5), 2));
//    p.push(new State<Point>(new Point(10,8), 5));
//    cout << p.top()->getCost() << endl;
//    p.pop();
//    cout << p.top()->getCost() << endl;
//    p.pop();
//    cout << p.top()->getCost() << endl;
//    p.pop();
//    cout << p.top()->getCost() << endl;
//    p.pop();
//    State<Point>* initial = new State<Point>(Point(0, 0), 3);
//    State<Point>* goal = new State<Point>(Point(2, 2), 6);
//
//    vector<State<Point> *> searchable;
//    searchable.push_back(initial);
//    searchable.push_back(new State<Point>(Point(0, 1), 2));
//    searchable.push_back(new State<Point>(Point(0, 2), -1));
//    searchable.push_back(new State<Point>(Point(1, 0), 1));
//    searchable.push_back(new State<Point>(Point(1, 1), -1));
//    searchable.push_back(new State<Point>(Point(1, 2), 5));
//    searchable.push_back(new State<Point>(Point(2, 0), 100));
//    searchable.push_back(new State<Point>(Point(2, 1), 4));
//    searchable.push_back(goal);
//
//
//    Searchable<Point>* m = new Matrix(searchable, initial, goal);
//    BestFirstSearch<Point> * b = new BestFirstSearch<Point>;
//    string x = b->search(m);
//    cout << x << endl;

    State<Point>* initial = new State<Point>(Point(0, 0), 3);
    State<Point>* goal = new State<Point>(Point(2, 2), 6);

    vector<State<Point> *> searchable;
    searchable.push_back(initial);
    searchable.push_back(new State<Point>(Point(0, 1), 2));
    searchable.push_back(new State<Point>(Point(0, 2), 2));
    searchable.push_back(new State<Point>(Point(1, 0), 1));
    searchable.push_back(new State<Point>(Point(1, 1), 7));
    searchable.push_back(new State<Point>(Point(1, 2), 5));
    searchable.push_back(new State<Point>(Point(2, 0), 100));
    searchable.push_back(new State<Point>(Point(2, 1), 4));
    searchable.push_back(goal);

    Searchable<Point>* m = new Matrix(searchable, initial, goal);
    BFS<Point> * b = new BFS<Point>;
    string x = b->search(m);
    cout << x << endl;

//    MySerialServer* d = new MySerialServer();
//    Solver<Searchable<Point>*, string>* solver = new SolverSearcher(new BestFirstSearch<Point>());
//    CacheManager* cacheManager = new FileCacheManager();
//    ClientHandler* ds = new MyClientHandler(solver, cacheManager);
//    d->open(5400,ds);
//    while (true) {}
    return 0;
}