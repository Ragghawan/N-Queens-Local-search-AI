#include<bits/stdc++.h>
using namespace std;

void print(vector<int>);
int cost(vector<int>);
vector<int> randomRestart(int);
bool isGoal(vector<int>);

int main()
{
    // N <= 13
    int N;
    cin>>N;
    vector<int> G = randomRestart(N);
    while (!isGoal(G))
    {
        int n = G.size(), minCost = cost(G);
        bool found = false;
        vector<int> nextState;

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if(G[i] == j)   continue;
                int temp = G[i];
                G[i] = j;
                int c = cost(G); 
                if (c < minCost){
                    found = true;
                    minCost = c;
                    nextState = G;
                }
                G[i] = temp;
            }
        }
        if(found)   G = nextState;
        else    G = randomRestart(G.size());
    }
    cout<<"Result : \n";
    print(G);
}
int cost(vector<int> G){
    int n = G.size(); // G[u] = v; -> u - col, v - row
    int count = 0;
    for(int i = 0;i < n;i++){
        int x1 = G[i], y1 = i;
        for(int j = i+1;j < n;j++){
            int y2 = j, x2 = G[j];
            if(x1 == x2)    count++;
            else if(y1 == y2)    count++;
            else if(x1+y1 == x2+y2)  count++;
            else if(y1-x1 == y2-x2)  count++;
        }
    }
    return count;
}
vector<int> randomRestart(int n){
    vector<int> G(n);
    for(int i = 0;i < n;i++){
        G[i] = rand()%n;
    }
    cout<<"Restarting from a random state : \n";
    print(G);
    return G;
}
bool isGoal(vector<int> G){
    return (cost(G) == 0);
}
void print(vector<int> G){
    int n = G.size();
    vector<vector<int>> board(n,vector<int>(n,-1));
    for(int i = 0;i < n;i++){
        board[G[i]][i] = 1;
    }
    for(int i = 0;i < n;i++){
        cout<<"[ ";
        for(int j = 0;j < n;j++){
            if(board[i][j] == 1){
                printf("Q ",board[i][j]);
            }else{
                printf("_ ");
            }
        }
        cout<<"]"<<endl;
    }
}
