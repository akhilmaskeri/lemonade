#include<iostream>
#include<cstdio>
#include<ctime>

#define size 6

using namespace std;

int m[size][size];
int color=4;                        // max number of colors

// utility function to know the
// game's status
int check(){

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(m[i][j]!=m[0][0])    // if the current is same at origin
                return 0;
    return 1;
}

// recursively check if surrounding 
// cells are of same number
void make(int from,int to,int i,int j){

    if(i-1 >= 0 && j>=0){           // on valid cell at start
        if(m[i-1][j]==from){        // if are of same number
            m[i-1][j]=to;           // transform to final color
            make(from,to,i-1,j);    // recursively call for its cells
        }
    }

    if(j-1 >=0 && i>=0){            // on valid cell at start
        if(m[i][j-1]==from){
            m[i][j-1]=to;    
            make(from,to,i,j-1);
        }
    }

    if(j+1 < size && i>=0){         // on valid cell at end
        if(m[i][j+1]==from){
            m[i][j+1]=to;
            make(from,to,i,j+1);
        } 
    }
    if(i+1<size && j>=0){           // on valid cell at end
        if(m[i+1][j]==from){
            m[i+1][j]=to;
            make(from,to,i+1,j);
        }
    }

}

// utility function
void display(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++)
            cout<<m[i][j]<<" ";
        cout<<endl;
    }
}

int main(){

    srand((unsigned)time(0));
    
    // initialize with random color
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            m[i][j]=rand()%color;

    display();
    
    int steps = 10; 

    int opt;
    while(steps>0){                     // if you still got moves
        if(check()){                    // and status is 1
            cout<<"you win!"<<endl;
            return 0;                   // end execution
        }

        cout<<"enter your color: ";
        cin >>opt;

        int pre = m[0][0];

        m[0][0]=opt;
        make(pre,opt,0,0);

        display();
        steps--;
    }
    
    cout<<"you lose!"<<endl;
    return 0;
}
