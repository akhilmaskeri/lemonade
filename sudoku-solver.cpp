#include<iostream>

using namespace std;

// @idea https://www.geeksforgeeks.org/sudoku-solver

// utility function
void display(int board[9][9]){

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }
}

// returns the r and c of unassigned cell
int findUnassigned(int board[9][9],int &r,int &c){

    for(r=0;r<9;r++){
        for(c=0;c<9;c++){

            // if there is cell that hasn't 
            // been assigned 
            if(board[r][c]==0) 
                return 1; 
        }
    }
    
    // all cells have been assigned 
    // solved 
    return 0;
}

// checks if n can be assigned to r & c
int isSafe(int board[9][9],int r,int c,int n){
    
    // if found in same row
    for(int i=0;i<9;i++)
        if(board[r][i]==n)
            return 0;

    // if found in same column
    for(int i=0;i<9;i++)
        if(board[i][c]==n)
            return 0;

    // box_x and box_y
    int box_r = r - (r%3);
    int box_c = c - (c%3);

    // if found in box
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[box_r+i][box_c+j]==n)
                return 0;

    return 1;
}

// recursive function for solving
int solve(int board[9][9]){

    int r=0,c=0;

    // if no unsigned cells
    if(!findUnassigned(board,r,c))
        return 1;

    // try all the numbers
    for(int i=1;i<=9;i++){

        if(isSafe(board,r,c,i)){

            // assign on safe
            board[r][c]=i;
            
            // on solved 
            if(solve(board))
                return 1;

            // unassign on fail
            board[r][c]=0;

        }
    }

    // trigger back tracking
    return 0;
}


int main(){

    int board[9][9];
    int r=0,c=0;

    // get the input for file
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            cin>>board[i][j];

    if(solve(board)){
        display(board);
    }
    else{
        cout<<"cannot be solved!!"<<endl;
    }

    return 0;
}
