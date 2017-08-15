#include<iostream>
#include<ctime>
#include<cstdio>

#define len 4
using namespace std;

int m[len][len]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

void right(){
    
    for(int r=0;r<len;r++){
        int to = len-1;    
        for(int c=len-2;c>=0;c--){
            if(m[r][c]==0)continue;
            else{
                if(m[r][to]==0){
                    m[r][to]=m[r][c];
                    m[r][c]=0;
                    continue;
                }
                if(m[r][to]==m[r][c]){
                    m[r][to]*=2;
                    m[r][c]=0;
                    to-=1;
                    continue;
                }
                else{
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
        }
    }
}
void left(){
    for(int r=0;r<len;r++){
        int to = 0;
        for(int c=1;c<len;c++){
        
            if(m[r][c]==0)continue;
            else{
                if(m[r][to]==0){
                   m[r][to]=m[r][c];    
                   m[r][c]=0;
                   continue;
                }
                if(m[r][to]==m[r][c]){
                    m[r][to]*=2;
                    m[r][c]=0;
                    to+=1;
                    continue;
                }
                else{
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
        }
    }
}

void up(){

    for(int c=0;c<len;c++){
        int to = 0;
        for(int r=1;r<len;r++){
        
            if(m[r][c]==0)continue;
            else{
                if(m[to][c]==0){
                   m[to][c]=m[r][c];    
                   m[r][c]=0;
                   continue;
                }
                if(m[to][c]==m[r][c]){
                    m[to][c]*=2;
                    m[r][c]=0;
                    to+=1;
                    continue;
                }
                else{
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
        }
    } 
}
void down(){

    for(int c=0;c<len;c++){
        int to = len-1;
        for(int r=len-2;r>=0;r--){
        
            if(m[r][c]==0)continue;
            else{
                if(m[to][c]==0){
                   m[to][c]=m[r][c];    
                   m[r][c]=0;
                   continue;
                }
                if(m[to][c]==m[r][c]){
                    m[to][c]*=2;
                    m[r][c]=0;
                    to-=1;
                    continue;
                }
                else{
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
        }
    } 
}

void display(){

    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++)
            cout<<m[i][j]<<" ";
        cout<<endl;
    }
    cout<<"----------------"<<endl;
}

int seed(){

    int skew[len*len][3];
    int z=0;

    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++)
            if(m[i][j]==0){
                skew[++z][0]=i;
                skew[z][1]=j;
            }
    }    

    if(z==0)return 0;

    ++z;

    int space = rand()%z;
    int element = ((rand()%2)+1);

    int r = skew[space][0],c=skew[space][1];
    m[r][c]=element;

    return 1;

}

int main(){

    srand((unsigned)time(0));
    seed();
    char opt;

    while(true){

        display(); 
    
        cin>>opt;
        switch(opt){
            case 'l':left();break;
            case 'r':right();break;
            case 'u':up();break;
            case 'd':down();break;
            case 'q': return 0;
            default:
                    cout<<"----------------"<<endl;
                    cout<<"invalid option"<<endl;
                    cout<<"u - up"<<endl
                        <<"d - down"<<endl
                        <<"l - left"<<endl
                        <<"r - right"<<endl
                        <<"----------------"<<endl;
                    continue;
        }
        seed();
    }
    


}

