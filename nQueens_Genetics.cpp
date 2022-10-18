#include<bits/stdc++.h>
using namespace std;
#define SIZE 50
#define MUTATION 8 // Out of 100
int p1 = (100-MUTATION)/2, p2 = 100 - MUTATION;
class individual{
    public:
    vector<int> chromosome;
    int fitness;
    int calculateFitness(){
        int n = chromosome.size(); // G[u] = v; -> u - col, v - row
        int count = 0;
        for(int i = 0;i < n;i++){
            int x1 = chromosome[i], y1 = i;
            for(int j = i+1;j < n;j++){
                int y2 = j, x2 = chromosome[j];
                if(x1 == x2)    count++;
                else if(y1 == y2)    count++;
                else if(x1+y1 == x2+y2)  count++;
                else if(y1-x1 == y2-x2)  count++;
            }
        }
        return count;
    }
    individual mate(individual parent2){
        vector<int> progeny(chromosome.size());
        for(int i = 0;i < chromosome.size();i++){
            int p = rand()%100;
            if(p <= p1){
                progeny[i] = chromosome[i];
            }else if(p <= p2){
                progeny[i] = parent2.chromosome[i];
            }else{
                progeny[i] = rand()%chromosome.size();
            }
        }
        individual child;
        child.chromosome = progeny;
        child.fitness = child.calculateFitness();
        return child;
    }
    void printMatrix(){
        int n = chromosome.size();
        vector<vector<int>> board(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++){
            board[chromosome[i]][i] = 1;
        }
        for (int i = 0; i < n; i++){
            cout << "[ ";
            for (int j = 0; j < n; j++){
                if (board[i][j] == 1){
                    printf("Q ", board[i][j]);
                }else{
                    printf("_ ");
                }
            }
            cout << "]" << endl;
        }
    }
    void printVector(){
        cout<<"[";
        for(int i = 0;i < chromosome.size();i++){
            cout<<chromosome[i]<<",";
        }
        cout<<'\b'<<"] ";
    }
};
individual createIndividual(int N){
    vector<int> G(N);
    for(int i = 0;i < N;i++){
        G[i] = rand()%N;
    }
    individual obj;
    obj.chromosome = G;
    obj.fitness = obj.calculateFitness();
    return obj;
}
bool compare(individual a,individual b){
    return a.fitness < b.fitness;
}
int main()
{
    int N;
    cin >> N;
    vector <individual> currGeneration;
    for(int i = 0;i < SIZE;i++){
        currGeneration.push_back(createIndividual(N));
    }
    int generation = 0;
    while(1){
        generation++;
        sort(currGeneration.begin(),currGeneration.end(),compare);
        currGeneration[0].printVector();
        cout<<"Generation : "<<generation<<endl;
        if(currGeneration[0].fitness == 0)  break;
        vector <individual> nextGeneration;
        int p = SIZE/10;
        for(int i = 0;i < p;i++){
            nextGeneration.push_back(currGeneration[i]);
        }
        for(int i = p;i < SIZE;i++){
            p = SIZE/2;
            int parent1 = rand()%p;
            int parent2 = rand()%p;
            while(parent2 == parent1)   parent2 = rand()%p;
            nextGeneration.push_back(currGeneration[parent1].mate(currGeneration[parent2]));
        }
        currGeneration = nextGeneration;
    }
    cout<<"Result : \n";
    currGeneration[0].printMatrix();
    return 0;
}