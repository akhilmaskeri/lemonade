#include<iostream>

using namespace std;

// @idea https://www.geeksforgeeks.org/program-sudoku-generator/

// utility function
void swap(int *a,int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

// utility function
void display(int board[9][9]){

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)
            if(board[i][j]==0)
                cout<<"-"<<" ";
            else
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

// shuffle the given array
void shuffle(int a[],int n){

    int ptr = n; 

    while(ptr>0){

        // randomly generate position
        int x = rand()%ptr;     
        // swap it with the last element
        ptr--;
        swap(a[x],a[ptr]);

    }

}

// generate a complete sudoku grid
void generate(int board[9][9]){
    
    // candidates
    int c[]={1,2,3,4,5,6,7,8,9};
    int box_r,box_c;
    int n=9,k;

    // for box starting at 0 , 0
    shuffle(c,n);
    k=0;

    box_r=box_c=0;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[box_r+i][box_c+j] = c[k++];
        }
    }

    // for box starting at 3 , 3    
    shuffle(c,n);
    k=0;

    box_r=box_c=3;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[box_r+i][box_c+j] = c[k++];
        }
    }

    // for box starting at 6 , 6
    shuffle(c,n);
    k=0;

    box_r=box_c=6;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[box_r+i][box_c+j] = c[k++];
        }
    }

    // solve for remaining positions
    if(solve(board)){
        display(board);
    }

}

int main(){

    // seed numbers
    srand((unsigned)time(0));

    int board[9][9]={0};

    generate(board);

    return 0;
}

