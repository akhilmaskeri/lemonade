#include<iostream>
#include<ctime>
#include<cstdio>

#define len 4
using namespace std;

// initializing the board
int m[len][len]={{0,0,0,0},
                 {0,0,0,0},
                 {0,0,0,0},
                 {0,0,0,0}};

// push right
void right(){
    
    for(int r=0;r<len;r++){
        
        //initializing final cell last
        int to = len-1;    
        for(int c=len-2;c>=0;c--){

            // skip if current cell is empty
            if(m[r][c]==0)continue;
            else{
                
                // assign current cell value
                // if final cell is empty
                if(m[r][to]==0){
                    m[r][to]=m[r][c];
                    m[r][c]=0;
                    continue;
                }

                // double if final cell has 
                // same number
                if(m[r][to]==m[r][c]){
                    m[r][to]*=2;
                    m[r][c]=0;
                    to-=1;
                    continue;
                }
                else{
                    // move to left element
                    if(m[r][to-1]==0){
                        m[r][to-1]=m[r][c];
                        m[r][c]=0;
                        to-=1;
                    }
                    else{
                        to-=1; 
                    }
                }
            }

        }                 // for <c>
    }                     // for <r>

}                         // right

//push left
void left(){

    for(int r=0;r<len;r++){

        // initializing final cell as first
        int to = 0;
        for(int c=1;c<len;c++){
        
            // skip if current cell is empty
            if(m[r][c]==0)continue;
            else{

                // assign current cell value
                // if final cell is empty
                if(m[r][to]==0){
                   m[r][to]=m[r][c];    
                   m[r][c]=0;
                   continue;
                }

                // double if final cell has 
                // same number
                if(m[r][to]==m[r][c]){
                    m[r][to]*=2;
                    m[r][c]=0;
                    to+=1;
                    continue;
                }
                else{
                    // move to right element
                    if(m[r][to+1]==0){
                        m[r][to+1]=m[r][c];   
                        m[r][c]=0;
                        to+=1;
                    }
                    else{
                        to+=1;
                    }
                }
            }

        }               // for <c>
    }                   // for <r>

}                       // left

//push up
void up(){

    for(int c=0;c<len;c++){

        // initializing final cell as first <in column>
        int to = 0;
        for(int r=1;r<len;r++){
        
            // skip on current cell is 0
            if(m[r][c]==0)continue;
            else{
                // assign current cell value
                // if final cell is empty
                if(m[to][c]==0){
                   m[to][c]=m[r][c];    
                   m[r][c]=0;
                   continue;
                }

                // double if cell has
                // same number
                if(m[to][c]==m[r][c]){
                    m[to][c]*=2;
                    m[r][c]=0;
                    to+=1;
                    continue;
                }
                else{
                    // move to below element
                    if(m[to+1][c]==0){
                        m[to+1][c]=m[r][c];   
                        m[r][c]=0;
                        to+=1;
                    }
                    else{
                        to+=1;
                    }
                }
            }

        }           //for <r>
    }               //for <c>

}                   //up

//push down
void down(){

    for(int c=0;c<len;c++){

        // initializing final cell 
        // as last in column
        int to = len-1;
        for(int r=len-2;r>=0;r--){
        
            // skip on current cell is 0
            if(m[r][c]==0)continue;
            else{
                // assign current cell value
                // if final cell is empty
                if(m[to][c]==0){
                   m[to][c]=m[r][c];    
                   m[r][c]=0;
                   continue;
                }

                // double if cell has
                // same number
                if(m[to][c]==m[r][c]){
                    m[to][c]*=2;
                    m[r][c]=0;
                    to-=1;
                    continue;
                }
                else{
                    // move to above element 
                    if(m[to-1][c]==0){
                        m[to-1][c]=m[r][c];   
                        m[r][c]=0;
                        to-=1;
                    }
                    else{
                        to-=1;
                    }
                }
            }

        }           // for <u>
    }               // for <c>

}                   // down

// utility function
void display(){

    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++)
            cout<<m[i][j]<<" ";
        cout<<endl;
    }
    cout<<"----------------"<<endl;
}


// generate a random number
// insert into the matrix
int seed(){

    // skew matrix
    int skew[len*len][3];
    int free=0;

    // assigning the skew
    // for empty cells
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++)
            if(m[i][j]==0){
                skew[++free][0]=i;
                skew[free][1]=j;
            }
    }    
    
    // if no free spaces
    // game over
    if(free==0)return 0;

    free++;

    // at random space with random number
    int space = rand()%free;
    int element = ((rand()%2)+1);

    int r = skew[space][0],c=skew[space][1];
    m[r][c]=element;

    // status success
    return 1;

}

int main(){

    srand((unsigned)time(0));

    char opt;

    while(seed()){
        
        //board in the begging
        display(); 
    
        cin>>opt;

        switch(opt){
            case 'l':left();  break;
            case 'r':right(); break;
            case 'u':up();    break;
            case 'd':down();  break;
            case 'q':         return 0;
            default :
                     cout<<"----------------"<<endl;
                     cout<<"invalid option"<<endl;
                     cout<<"u - up"<<endl
                         <<"d - down"<<endl
                         <<"l - left"<<endl
                         <<"r - right"<<endl
                         <<"----------------"<<endl;
                     continue;
        }
    }
    
    //end of game
    cout<<"game over!!"<<endl;


}

