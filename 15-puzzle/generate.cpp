#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stack>

using namespace std;

//utility functions
void swap(int *a,int *b){

	int t = *a;
	*a = *b;
	*b = t;

}

void display(int b[4][4]){

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++) 
        	if(b[i][j]==0)
        		cout<<" _ ";
        	else
        		if (b[i][j]<10)
        			cout<<" "<<b[i][j]<<" ";
            	else
            		cout<<b[i][j]<<" ";
        cout<<endl;
    }

}

bool valid(int zr,int zc,int m){

	switch(m){

		case 0: // up
				if(zr == 0 )
					return 0;
				break;
		case 1:  // down
				if(zr == 3 )
					return 0;
				break;
		case 2:  //left
				if(zc == 0 )
					return 0;
				break;
		case 3: // right
				if(zc == 3 )
					return 0;
				break;
	}

	return 1;
}


void makeMove(int b[4][4],int* r,int* c,int m){


	switch(m){

		case 0: //up
				swap(b[*r][*c],b[(*r)-1][*c]);
				*r = (*r) -1;
				break;
		case 1: //down
				swap(b[*r][*c],b[(*r)+1][*c]);
				*r = (*r) +1;
				break;
		case 2: //left
				swap(b[*r][*c],b[*r][(*c)-1]);
				*c = (*c)-1;
				break;
		case 3: //right
				swap(b[*r][*c],b[*r][(*c)+1]);
				*c = (*c)+1;
				break;
	}

}

int main(){

    int board[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};

    stack <int> st;

	srand(time(NULL));
    
	int move,remainingMoves = 20;

	int zr=3,zc=3;


	while(remainingMoves){

		move = rand()%4;

		if(move == 0  &&  st.size() > 0 && st.top() == 1)continue;
		if(move == 1  &&  st.size() > 0 && st.top() == 0)continue;
		if(move == 2  &&  st.size() > 0 && st.top() == 3)continue;
		if(move == 3  &&  st.size() > 0 && st.top() == 2)continue;

		if(!valid(zr,zc,move))continue;
	
		st.push(move);		
		makeMove(board,&zr,&zc,move);

		remainingMoves--;

	}

	cout<<"-----------"<<endl<<endl;
	display(board);
	cout<<endl;
	cout<<"-----------"<<endl;

}