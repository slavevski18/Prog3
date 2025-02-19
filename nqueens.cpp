#include <iostream>
#include <vector>
using namespace std;

// Функција да провери дали две кралици се напаѓаат
bool canQueensAttack(pair<int, int> queenA, pair<int, int> queenB) 
{
    return (queenA.first == queenB.first || queenA.second == queenB.second || abs(queenA.first - queenB.first) == abs(queenA.second - queenB.second));
}

// Функција за валидација ако не се напаѓаат кралици меѓусебно во тековната конфигурација
bool isValidQueenPlacement(vector<pair<int, int>>& queenPositions) 
{
    for (int i = 0; i < queenPositions.size(); i++) 
    {
        for (int j = i + 1; j < queenPositions.size(); j++) 
        {
            if (canQueensAttack(queenPositions[i], queenPositions[j])) 
            {
                return false;
            }
        }
    }
    return true;
}

// Рекурзивна функција
void solveNQueens(int boardSize, vector<pair<int, int>>& currentPlacement, vector<vector<pair<int, int>>>& solutions) 
{
    if (currentPlacement.size() == boardSize) 
    {
        if (isValidQueenPlacement(currentPlacement)) 
        {
            solutions.push_back(currentPlacement);
        }
        return;
    }
    for (int row = 0; row < boardSize; row++) 
    {
        for (int col = 0; col < boardSize; col++) 
        {
            currentPlacement.push_back({row, col});
            solveNQueens(boardSize, currentPlacement, solutions);
            currentPlacement.pop_back();
        }
    }
}

int main() {
    int boardSize;
    cin >> boardSize;

    vector<vector<pair<int, int>>> solutions;
    vector<pair<int, int>> currentPlacement;

    solveNQueens(boardSize, currentPlacement, solutions);

    int solutionCount = 0;
    for (auto& solution : solutions) 
    {
        cout << ++solutionCount << '\n';
        for (auto& position : solution) 
        {
            cout << "(" << position.first << ", " << position.second << ") ";
        }
        cout << '\n';
    }

    cout << solutionCount;
    return 0;
}
