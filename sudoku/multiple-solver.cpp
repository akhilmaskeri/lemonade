#include<iostream>
#include "stack.cpp"

using namespace std;

stack s;


void solveAll(int b[9][9]){

    int board[9][9];

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            board[i][j] = b[i][j];

    _solve(board);
    
}


int solve(int board[9][9]){

    int r=0,c=0;

    if(!findUnassigned(board,r,c)){
        if(s.getCount()<1){
            s.push(board);
            return 0;
        }
        return 1;
    }

    for(int i=1;i<=9;i++){

        if(isSafe(board,r,c,i)){

            board[r][c]=i;
            
            if(solve(board))
                return 1;

            board[r][c]=0;

        }
    }

    return 0;
}

int mulitpleExists(int b[9][9]){

    int board[9][9];

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            board[i][j]=b[i][j];

     solve(board);

     if(s.getCount()==0 || s.getCount()>1)
     	return 0;

     return 1;
}

/*
int main(){

    int board[9][9];

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            cin>>board[i][j];

    cout<<mulitpleExists(board)<<endl;

}
*/
