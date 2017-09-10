#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class board{

    private:
        int b[3][3];

    public:
        board(){
            
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    b[i][j]=0;
        }

        //--------------------------------------
        int get(int i,int j){
            return b[i][j];
        }

        int getScore(){
            int score = finished()*10;
            return score;
        }

        int isEmpty(int r,int c){
            if(b[r][c]==0)
                return 1;
            return 0;
        }

        void setBoard(board br){                // copy the board
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    b[i][j]=br.get(i,j);

        }

        int finished(){

            if(b[0][0]==b[1][1] && b[0][0]==b[2][2] && b[0][0]!=0)              // principle diagonal
                return b[0][0];

            if(b[0][2]==b[1][1] && b[0][2]==b[2][0] && b[0][2]!=0)              // non-principle diagonal
                return b[0][2];


            int i,j;
                                                                                // row wise
            for(i=0;i<3;i++){
                for(j=0;j<2;j++)
                    if(b[i][j]!=b[i][j+1] || b[i][j]==0)
                        break;
                if(j==2){
                    return b[i][j];
                }
            }

            for(i=0;i<3;i++){
                for(j=0;j<2;j++)
                    if(b[j][i]!=b[j+1][i] || b[j][i]==0)
                        break;
                if(j==2){
                    return b[i][j];
                }
            
            }
           
            // nobody won
            return 0;
        }
        //--------------------------------------------

        void play(int r,int c,int p){

            if(p){                              // user is playing 
                b[r][c]=1;
            }
            else{                               // computer is playing
                b[r][c]=-1;
            }
            
        }

        //--------------------------------------------
        void display(){

            for(int i=0;i<20;i++)
                cout<<"-";
            cout<<endl;
            
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(!b[i][j])
                        cout<<" "<<" ";
                    if(b[i][j]==1)
                        cout<<"o"<<" ";
                    if(b[i][j]==-1)
                        cout<<"x"<<" ";
                }
                cout<<endl;
            }
            
            for(int i=0;i<20;i++)
                cout<<"-";
            cout<<endl;
        }

};

class minmax{

    public:
        int flipflop(board b,int *r,int *c,int depth){

            if(b.finished())
                return b.finished();

            depth++;

            board possible[9];
            int count=0;
            int move[9][2];

            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                
                    if(b.isEmpty(i,j)){
                        possible[count].setBoard(b);
                        possible[count].play(i,j,1);
                    } 
                
                }
            }
        
        }

};

int main(){

    int player;
    int r,c,i;

    board b;

    srand((unsigned)time(0));

    player = rand()%2;                          // randomly choose the first player
    cout<<"first player : "<<player<<endl;


    for(i=0;i<9 && !b.finished() ;i++){
    
        if((player+i)%2){                       // computer playes

            do{
                r = rand()%3;
                c = rand()%3;
            }while(!b.isEmpty(r,c));

            // do the minmax instead of random

            b.play(r,c,1);

        }
        else{                                 // user playes
            b.display();

            do{
                cout<<"r:c > ";
                cin>>r>>c;
            }while(r>=3 && c>=3 &&  !b.isEmpty(r,c));
            
            b.play(r,c,0);

        }
    }

    b.display();
    if(i!=9)
        cout<<((b.finished()*-1)+1)/2<<" wins"<<endl;
    else
        cout<<"match draw"<<endl;

}
