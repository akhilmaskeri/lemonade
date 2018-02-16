#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

// class for keeping track of valid
// moves and other utility functions
class board{

    private:
        int b[3][3];

    public:
        // initialize with null on all cells
        board(){
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    b[i][j]=0;
        }

        // utility functions

        // getter
        int get(int i,int j){
            return b[i][j];
        }
        int isEmpty(int r,int c){
            if(b[r][c]==0)
                return 1;
            return 0;
        }

        // copy from other instant  
        void setBoard(board br){               
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    b[i][j]=br.get(i,j);

        }

        // status check
        int finished(){

            // principle diagonal
            if(b[0][0]==b[1][1] && b[0][0]==b[2][2] && b[0][0]!=0)              
                return b[0][0];

            // non-principle diagonal
            if(b[0][2]==b[1][1] && b[0][2]==b[2][0] && b[0][2]!=0)              
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

            // column wise
            for(i=0;i<3;i++){                                                   
                for(j=0;j<2;j++)
                    if(b[j][i]!=b[j+1][i] || b[j][i]==0)
                        break;
                if(j==2){
                    return b[j][i];
                }
            }
           
            return 0;
        }

        // move
        void play(int r,int c,int p){

            if(p){                              // user is playing 
                b[r][c]=1;
            }
            else{                               // computer is playing
                b[r][c]=-1;
            }
            
        }

        // utility display
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

        // score for minmax
        int getScore(){
            return finished()*10;
        }



};

// class to abstract bot
class computer{

    private:
        int player;

    public:
        computer(int p){
            player = p;
        }

        int number(){
            return player;
        }

        int minmax(board b,int *r,int *c,int depth){

            // only for depth <= 2
            if(depth>2)return 0;

            if(b.finished()){
                return b.getScore();
            }

            depth+=1;

            int scores[9];
            int moves[9][2];
            int count=0;

            // toggle player < -1 or 1 >
            computer max((player*-1)+1);

            // board instant for testing
            board test;

            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    
                    if(b.isEmpty(i,j)){
                        
                        // copy current board
                        test.setBoard(b);  

                        // play at i j with emulating a player
                        test.play(i,j,player);

                        // save scores
                        scores[count]=max.minmax(test,r,c,depth);

                        moves[count][0]=i;
                        moves[count][1]=j;

                        count++;

                    }
                }
            }

            int maxscore = 0;
            int minscore = 0;

            int zeros=1;

            // get max / min / ties from the simulated board
            for(int i=0;i<count;i++){

                if(i<=count-1 && scores[i]!=scores[i+1] && scores[i]==0)
                    zeros=0;

                if(scores[i]>scores[maxscore])
                    maxscore=i;
                if(scores[i]<scores[minscore])
                    minscore=i;
            }

            // in case of more than one move
            // end up with same score randomly
            // select the move
            if(zeros){

                int z = 0;
                if(count)
                    z=rand()%count;
                *r = moves[z][0];
                *c = moves[z][1];
                return 0;
                
            }

            // select the best move
            if(player==1){

                *r = moves[maxscore][0];
                *c = moves[maxscore][1];
                return scores[maxscore];
            }

            *r = moves[minscore][0];
            *c = moves[minscore][1];

            return scores[minscore];

        }

};


int main(){

    int player;
    int r,c,i;
    int depth=0;

    //initialize the board
    board b;
    computer cheryl(1);                             // bot always plays o

    srand((unsigned)time(0));
    
    // randomly choose the first player
    player = rand()%2;                              
    cout<<"first player : "<<player<<endl;


    for(i=0;i<9 && !b.finished() ;i++){
    
        if((player+i)%2){                           // computer 

            cheryl.minmax(b,&r,&c,0);

            b.play(r,c,1);
            cout<<"bot > "<<r<<" "<<c<<endl;

        }
        else{                                       // user
            b.display();

            do{
                cout<<"r:c > ";
                cin>>r>>c;

            }while(r>=3 && c>=3 &&  !b.isEmpty(r,c));
            
            b.play(r,c,0);

        }
    }

    b.display();

    // if game ends before all moves
    if(i!=9){

        if(((b.finished()*-1)+1)/2)
            cout<<"you win"<<endl;
        else
            cout<<"bot wins"<<endl;
    }
    else
        cout<<"match draw"<<endl;

    return 0;
}
/*
int test(){

    int player;
    int r,c,i;
    int depth=0;

    board b;
    b.play(1,0,0); 
    b.play(1,1,0);


    computer cheryl(1);                             // cheryl always plays o

    cheryl.minmax(b,&r,&c,0);
    b.play(r,c,1);
    b.display();
    cout<<b.getScore()<<endl;

    cout<<r<<" "<<c<<endl;

    return 0;
}
*/
