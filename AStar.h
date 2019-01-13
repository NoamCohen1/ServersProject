//
// Created by gal on 1/13/19.
//

#ifndef SERVERSPROJECT_ASTAR_H
#define SERVERSPROJECT_ASTAR_H

#include <queue>
#include "Searcher.h"
#include "State.h"
#include "MyClientHandler.h"
#include<bits/stdc++.h>

using namespace std;

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int>> pPair;

// A structure to hold the neccesary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

template<class T>
class AStar : public Searcher<T> {
public:
    /* A Function to find the shortest path between a given source cell to
     * a destination cell according to A* Search Algorithm */
    virtual string search(Searchable<T> *searchable) {
        string result = "";
        vector<pPair> matrix = searchable->getPairsVector();
        Pair src = (searchable->getInitialPair()).second;
        Pair dest = (searchable->getGoalPair()).second;
        int row = returnRow(matrix) + 1;
        int col = returnCol(matrix) + 1;
        double grid[row][col];
        for (int k = 0; k < row; ++k) {
            for (int r = 0; r < col; ++r) {
                grid[k][r] = matrix[(k * col) + r].first;
            }
        }

        //void aStarSearch(int grid[][COL], Pair src, Pair dest)

        // Either the source or the destination is blocked
        if ((searchable->getInitialState()->getCost() == (-1)) ||
            (searchable->getGoalState()->getCost() == (-1))) {
            result = "-1";
            return result;
        }

        // If the destination cell is the same as source cell
        if (searchable->getInitialState()->equals(searchable->getGoalState())) {
            return result;
        }

        // Create a closed list and initialise it to false which means
        // that no cell has been included yet
        // This closed list is implemented as a boolean 2D array
        bool closedList[row][col];
        memset(closedList, false, sizeof(closedList));

        // Declare a 2D array of structure to hold the details
        //of that cell
        //cell cellDetails[row][col];
        cell cellDetails[row][col];
        //vector<cell> allCells;


        int i, j;

        for (i = 0; i < row; ++i) {
            for (j = 0; j < col; ++j) {
                cellDetails[i][j].f = FLT_MAX;
                cellDetails[i][j].g = FLT_MAX;
                cellDetails[i][j].h = FLT_MAX;
                cellDetails[i][j].parent_i = -1;
                cellDetails[i][j].parent_j = -1;
            }
        }

        // Initialising the parameters of the starting node
        i = src.first;
        j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j;

        /*
         Create an open list having information as-
         <f, <i, j>>
         where f = g + h,
         and i, j are the row and column index of that cell
         Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
         This open list is implenented as a set of pair of pair.*/
        set<pPair> openList;

        // Put the starting cell on the open list and set its
        // 'f' as 0
        openList.insert(make_pair(0.0, make_pair(i, j)));

        // We set this boolean value as false as initially
        // the destination is not reached.
        bool foundDest = false;

        while (!openList.empty()) {
            pPair p = *openList.begin();

            // Remove this vertex from the open list
            openList.erase(openList.begin());

            // Add this vertex to the closed list
            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            // To store the 'g', 'h' and 'f' of the 8 successors
            double gNew, hNew, fNew;

            //----------- 1st Successor (North) ------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j, row, col) == true) {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i - 1, j, dest) == true) {
                    // Set the Parent of the destination cell
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                    return tracePath((cell *) cellDetails, dest, col);
                }
                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (closedList[i - 1][j] == false && ((grid[i - 1][j]) != -1)) {
                    gNew = cellDetails[i][j].g + grid[i - 1][j];
                    hNew = calculateHValue(i - 1, j, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i - 1][j].f == FLT_MAX ||
                        cellDetails[i - 1][j].f > fNew) {
                        openList.insert(make_pair(fNew, make_pair(i - 1, j)));

                        // Update the details of this cell
                        cellDetails[i - 1][j].f = fNew;
                        cellDetails[i - 1][j].g = gNew;
                        cellDetails[i - 1][j].h = hNew;
                        cellDetails[i - 1][j].parent_i = i;
                        cellDetails[i - 1][j].parent_j = j;
                    }
                }
            }

            //----------- 2nd Successor (South) ------------

            // Only process this cell if this is a valid one
            if (isValid(i + 1, j, row, col) == true) {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i + 1, j, dest) == true) {
                    // Set the Parent of the destination cell
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                    return tracePath((cell *) cellDetails, dest, col);
                }
                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (closedList[i + 1][j] == false && ((grid[i + 1][j]) != -1)) {
                    gNew = cellDetails[i][j].g + grid[i + 1][j];
                    hNew = calculateHValue(i + 1, j, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i + 1][j].f == FLT_MAX ||
                        cellDetails[i + 1][j].f > fNew) {
                        openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                        // Update the details of this cell
                        cellDetails[i + 1][j].f = fNew;
                        cellDetails[i + 1][j].g = gNew;
                        cellDetails[i + 1][j].h = hNew;
                        cellDetails[i + 1][j].parent_i = i;
                        cellDetails[i + 1][j].parent_j = j;
                    }
                }
            }

            //----------- 3rd Successor (East) ------------

            // Only process this cell if this is a valid one
            if (isValid(i, j + 1, row, col) == true) {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i, j + 1, dest) == true) {
                    // Set the Parent of the destination cell
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                    return tracePath((cell *) cellDetails, dest, col);
                }

                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (closedList[i][j + 1] == false && ((grid[i][j + 1]) != -1)) {
                    gNew = cellDetails[i][j].g + grid[i][j + 1];
                    hNew = calculateHValue(i, j + 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i][j + 1].f == FLT_MAX ||
                        cellDetails[i][j + 1].f > fNew) {
                        openList.insert(make_pair(fNew, make_pair(i, j + 1)));

                        // Update the details of this cell
                        cellDetails[i][j + 1].f = fNew;
                        cellDetails[i][j + 1].g = gNew;
                        cellDetails[i][j + 1].h = hNew;
                        cellDetails[i][j + 1].parent_i = i;
                        cellDetails[i][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 4th Successor (West) ------------

            // Only process this cell if this is a valid one
            if (isValid(i, j - 1, row, col) == true) {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i, j - 1, dest) == true) {
                    // Set the Parent of the destination cell
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                    return tracePath((cell *) cellDetails, dest, col);
                }

                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (closedList[i][j - 1] == false && ((grid[i][j - 1]) != -1)) {
                    gNew = cellDetails[i][j].g + grid[i][j - 1];
                    hNew = calculateHValue(i, j - 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i][j - 1].f == FLT_MAX ||
                        cellDetails[i][j - 1].f > fNew) {
                        openList.insert(make_pair(fNew, make_pair(i, j - 1)));

                        // Update the details of this cell
                        cellDetails[i][j - 1].f = fNew;
                        cellDetails[i][j - 1].g = gNew;
                        cellDetails[i][j - 1].h = hNew;
                        cellDetails[i][j - 1].parent_i = i;
                        cellDetails[i][j - 1].parent_j = j;
                    }
                }
            }
        }

        // When the destination cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destiantion cell. This may happen when the
        // there is no way to destination cell (due to blockages)
//        if (foundDest == false)
        return "-1";
    }

    int returnRow(vector<pPair> matrix) {
        int maxRow = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            if ((matrix[i].second).first > maxRow) {
                maxRow = (matrix[i].second).first;
            }
        }
        return maxRow;
    }

    int returnCol(vector<pPair> matrix) {
        int maxCol = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            if ((matrix[i].second).second > maxCol) {
                maxCol = (matrix[i].second).second;
            }
        }
        return maxCol;
    }

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
    bool isValid(int row, int col, int maxRow, int maxCol) {
        // Returns true if row number and column number
        // is in range
        return (row >= 0) && (row < maxRow) &&
               (col >= 0) && (col < maxCol);
    }

// A Utility Function to check whether destination cell has
// been reached or not
    bool isDestination(int row, int col, Pair dest) {
        if (row == dest.first && col == dest.second)
            return (true);
        else
            return (false);
    }

// A Utility Function to calculate the 'h' heuristics.
    double calculateHValue(int row, int col, Pair dest) {
        // Return using the distance formula of manhattan
        return (double) (abs(row - dest.first) + abs(col - dest.second));
    }

// A Utility Function to trace the path from the source
// to destination
    string tracePath(cell *cellDetails, Pair dest, int col) {
        //printf("\nThe Path is ");
        int i = dest.first;
        int j = dest.second;
        stack<Pair> Path;
        while (!(((*(cellDetails + (i * col) + j)).parent_i == i) &&
                 ((*(cellDetails + (i * col) + j)).parent_j == j))) {
            Path.push(make_pair(i, j));
            int temp_row = (*(cellDetails + (i * col) + j)).parent_i;
            int temp_col = (*(cellDetails + (i * col) + j)).parent_j;
            i = temp_row;
            j = temp_col;
        }

        Path.push(make_pair(i, j));
        return getPath(Path);
    }

    bool stateIsInVisited(State<T> *state, vector<State<T> *> visited) {
        for (State<T> *s : visited) {
            if (state->equals(s)) {
                return true;
            }
        }
        return false;
    }

    string getPath(stack<Pair> Path) {
        string path = "";
        int size = Path.size();
        for (int i = 0; i < (size - 1); ++i) {
            pair<int, int> p1 = Path.top();
            Path.pop();
            pair<int, int> p2 = Path.top();
            int i1 = p1.first;
            int j1 = p1.second;
            int i2 = p2.first;
            int j2 = p2.second;
            if ((i1 == i2) && (j1 == (j2 - 1))) {
                path += "R";
            } else if ((i1 == i2) && (j1 == (j2 + 1))) {
                path += "L";
            } else if ((i1 == (i2 - 1)) && (j1 == j2)) {
                path += "D";
            } else if ((i1 == (i2 + 1)) && (j1 == j2)) {
                path += "U";
            }
        }

        return path;
    }
};


#endif //SERVERSPROJECT_ASTAR_H
