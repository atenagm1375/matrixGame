// Ashena Gorgan Mohammadi, 610394128
/* Q : Sort a matrix of order n with an empty square by moving the
 * empty square.
 * INPUT : integer n as order of matrix which is 4 or less and the
 * matrix.(* represents the empty square)
 * OUTPUT : no if it was not possible to solve the puzzle or the string
 * containg D(down), U(up), R(right) and L(left), each meaning to move
 * the empty square to the other direction(i.e. L means that * must move
 * right).
 * */
// The idea of solving the task is based on BFS algorithm.
#include <iostream>
#include <queue>
#include <map>
#include <cstdlib>

using namespace std;

typedef pair<int **, pair<int, int> > myPair; // a matrix of int and a pair of integers
                                                //showing the location of *

void findSquare(int **); // the base of bfs
myPair *convertToPair(int **); // change matrix to pair
string convertToString(int **); // change the matrix to a symbolic string no matter what it is
void setNext(pair<myPair *, string> *, queue<pair<myPair *, string> > *); // set children of each pair
                                                        // and put them in queue
bool isAnswer(int **); // check if the answer is met or not
bool mapIsTrue(myPair *); // check the correction of map

int n; // order of matrix
int **input; // the input matrix
map<string, bool> myMap; // the map with a string key and a boolean value

int main() {
    cout << "Enter the order of the square which is either 3 or 4:" << endl;
    cin >> n;
    input = new int *[n];
    for(int i = 0; i < n; i++)
        input[i] = new int[n];
    cout << "Enter the index of square(* representing empty):" << endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            char a;
            cin >> a;
            if(a != '*')
                input[i][j] = a - '0';
            else
                input[i][j] = -1;
        }
    findSquare(input);
    cout << "no" << endl;
    return 0;
}

void findSquare(int **A)
{
    queue<pair<myPair *, string> > record;
    string aid = "";
    pair<myPair *, string> p(convertToPair(A), aid);
    record.push(p);
    myMap[convertToString(A)] = true;
    while(record.size() > 0){
        pair<myPair *, string> a = record.front();
        record.pop();
        setNext(&a, &record);
        if(isAnswer(a.first->first)){
            cout << a.second << endl;
            exit(0);
        }
    }
}

myPair *convertToPair(int **A)
{
    pair<int, int> p(0, 0);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(A[i][j] == -1){
                p.first = i;
                p.second = j;
                break;
            }
    return new myPair(A, p);
}

string convertToString(int **A)
{
    string str;
    for(int i = 0;i < n;i ++)
        for(int j = 0;j < n;j ++)
            str += (char)(A[i][j] + 20);
    return str;
}

void setNext(pair<myPair *, string> *P, queue<pair<myPair *, string> > *Q)
{
    int x = P->first->second.first;
    int y = P->first->second.second;
    if(x > 0){ // move down
        int ** answer = new int *[n];
        for(int i = 0; i < n; i++)
            answer[i] = new int [n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                answer[i][j] = P->first->first[i][j];
        int aid = answer[x - 1][y];
        answer[x - 1][y] = answer[x][y];
        answer[x][y] = aid;
        pair<int, int> p(x - 1, y);
        string str = P->second;
        str += "D";
        myPair *a = new myPair(answer, p);
        pair<myPair *, string> q(a, str);
        if(mapIsTrue(a))
            Q->push(q);
    }

    if(x < n - 1){ // move up
        int ** answer = new int *[n];
        for(int i = 0; i < n; i++)
            answer[i] = new int [n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                answer[i][j] = P->first->first[i][j];
        int aid = answer[x + 1][y];
        answer[x + 1][y] = answer[x][y];
        answer[x][y] = aid;
        pair<int, int> p(x + 1, y);
        string str = P->second;
        str += "U";
        myPair *a = new myPair(answer, p);
        pair<myPair *, string> q(a, str);
        if(mapIsTrue(a))
            Q->push(q);
    }

    if(y > 0){ // move right
        int ** answer = new int *[n];
        for(int i = 0; i < n; i++)
            answer[i] = new int [n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                answer[i][j] = P->first->first[i][j];
        int aid = answer[x][y - 1];
        answer[x][y - 1] = answer[x][y];
        answer[x][y] = aid;
        pair<int, int> p(x, y - 1);
        string str = P->second;
        str += "R";
        myPair *a = new myPair(answer, p);
        pair<myPair *, string> q(a, str);
        if(mapIsTrue(a))
            Q->push(q);
    }

    if(y < n - 1){ // move left
        int ** answer = new int *[n];
        for(int i = 0; i < n; i++)
            answer[i] = new int [n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                answer[i][j] = P->first->first[i][j];
        int aid = answer[x][y + 1];
        answer[x][y + 1] = answer[x][y];
        answer[x][y] = aid;
        pair<int, int> p(x, y + 1);
        string str = P->second;
        str += "L";
        myPair *a = new myPair(answer, p);
        pair<myPair *, string> q(a, str);
        if(mapIsTrue(a))
            Q->push(q);
    }
}

bool isAnswer(int **A)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(!(i == n - 1 && j == n - 1) && A[i][j] != (i * n + j + 1))
                return false;
    return true;
}

bool mapIsTrue(myPair *p)
{
    string str = convertToString(p->first);
    if(!myMap[str]){
        myMap[str]  =true;
        return true;
    }
    return false;
}git
