#include<iostream>

using namespace std;

void display(int b[5][5]){

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(b[i][j])
                cout<<b[i][j]<<" ";
            else
                cout<<"█ ";
        }
        cout<<endl;
    }
    

}

// first black tile
int getFirstBlack(int b[5][5],int *i,int *j){

    for(*i=0;*i<5;(*i)++){
        for(*j=0;*j<5;(*j)++){
            if(b[*i][*j]==0){
                return 1;
            }
        }
    }

    return 0;

}

int getTotalBlacks(int b[5][5]){

    int white=0;

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(b[i][j]!=0)
                white+=b[i][j];
        }
    }

    return 25 - white;
}

// checks how many same colored tile is connected to it
// to check black n = 0
int connected(int b[5][5],int visited[5][5],int n,int i,int j){
        
    if( i<0 || i>=5  || j<0 || j>=5 ) return 0;
    
    if(visited[i][j]==1 || b[i][j]!= n)return 0;

    visited[i][j]=1;

    return 1 + connected(b,visited,n,i,j+1) + connected(b,visited,n,i+1,j) + connected(b,visited,n,i-1,j) + connected(b,visited,n,i,j-1);

}

int equals(int a,int b,int c,int d){
    
    if(a==b && a==c && a==d)
        return true;

    return false;

}

int hasBox(int b[5][5]){
    
    for(int i=0;i<5-1;i++)
        for(int j=0;j<5-1;j++)
           if(b[i][j] == 0 && equals(b[i][j],b[i][j+1],b[i+1][j],b[i+1][j+1]))
               return true;

    return false;
}

int verifyWhite(int b[5][5],int i,int j){
    
    int n = b[i][j];

    if(n==1) return 1;

    int v[5][5] = {0};


    if(n == connected(b,v,n,i,j))
        return true;

    return false;
}

bool solve(int b[5][5],int white[5][2]){

    int i=0,j=0;

    


    return false;
}

int main(){

    int b[5][5];

    memset(b,0,sizeof(b));

    b[1][1] = 4;
    b[1][2] = 4;
    b[2][2] = 4;
    b[2][3] = 4;

    int v[5][5]={0};
    int i=0,j=0;

    cout<<verifyWhite(b,1,1);
    

}
