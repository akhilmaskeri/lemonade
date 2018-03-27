#include<iostream>
#include<string>

using namespace std;

bool solutionExists;

// utility function
void swap(int *a,int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

/* randomly generate position and
 * swap it with the last element 
 */
void shuffle(int a[],int n){

    int ptr = n; 

    while(ptr>0){

        int x = rand()%ptr;     
        ptr--;
        swap(a[x],a[ptr]);

    }

}

void display(int board[9][9]){

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)
        	if(board[i][j] == 0)
        		 cout<<"- ";
        	else
        		cout<<board[i][j]<<" ";

        cout<<endl;
    }
}

int findUnassigned(int board[9][9],int &r,int &c){

    for(r=0;r<9;r++){
        for(c=0;c<9;c++){

            if(board[r][c]==0) 
                return 1; 
        }
    }
     
    return 0;
}

int isSafe(int board[9][9],int r,int c,int n){
    
    for(int i=0;i<9;i++)
        if(board[r][i]==n)
            return 0;

    for(int i=0;i<9;i++)
        if(board[i][c]==n)
            return 0;

    int box_r = r - (r%3);
    int box_c = c - (c%3);

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[box_r+i][box_c+j]==n)
                return 0;

    return 1;
}



int solve(int board[9][9]){

    int r=0,c=0;

    if(!findUnassigned(board,r,c)){
    	// first solution
    	if(!solutionExists){
    		solutionExists = true;
    		return 0;
    	}
    	// second solution
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

int multipleExists(int board[9][9]){

	solutionExists = false;

	int b[9][9];
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			b[i][j] = board[i][j];
		}
	}

	if(!solve(b) && solutionExists){
		return 0;
	}
	return 1;
	
}


int simpleSolve(int board[9][9]){

    int r=0,c=0;

    if(!findUnassigned(board,r,c)){
        return 1;
    }

    for(int i=1;i<=9;i++){

        if(isSafe(board,r,c,i)){

            board[r][c]=i;
            
            if(simpleSolve(board))
                return 1;

            board[r][c]=0;

        }
    }

    return 0;
}

// generate a complete sudoku gridg
void generate(int board[9][9]){

    srand((unsigned)time(0));

    
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

    simpleSolve(board);

}


int main(int arg,char * argv[]){

    int b[9][9]; memset(b,0,sizeof(b));

    generate(b);

    int i;
    int j;

    int s = 0;

   	if(arg == 2)
	 	s = stoi(argv[1]);

    
    while(s>0){

		i = rand()%9;
    	j = rand()%9;

    	if(b[i][j] == 0)
    		continue;

    	if(multipleExists(b))
    		continue;

    	
    	b[i][j] = 0;
    	s--;
    }

    display(b);

}















