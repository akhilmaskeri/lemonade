#include<iostream>

using namespace std;

class Board{
    
    private:
        // board implemented as int
        int b[5][7];

    public:
        // default constructor 
        // initialize with only 0s
        Board(){
            memset(b,0,sizeof(b));
        }
       
        // copy constructor
        Board(Board &b){

            for(int i=0;i<5;i++)
                for(int j=0;j<7;j++)
                    this->b[i][j] = b.get(i,j);
        }

        int get(int i,int j){
            return b[i][j];
        }

        bool play(bool player,int column){

            int i=0;
            // start from the last row
            // check if the cell is empty

            for(i=5-1;i>=0;i--){
                if(b[i][column]==0){
                    b[i][column] = (player)?1:-1;
                    return true;
                }
            }

            return false;
        }

        // utility function
        bool equals(int a,int b,int c,int d){

            if(a==b && a==c && a==d)
                return true;

            return false;

        }

        // check for 4 continuous boxes
        int gameOver(){
        
            // horizontally
            for(int i=0;i<5;i++)
                for(int j=0;j<4;j++)
                    if(b[i][j] && equals(b[i][j],b[i][j+1],b[i][j+2],b[i][j+3]))
                        return b[i][j];

            // vertically
            for(int j=0;j<7;j++)
                for(int i=0;i<2;i++)
                    if(b[i][j] && equals(b[i][j],b[i+1][j],b[i+2][j],b[i+3][j]))
                        return b[i][j];
        
            // left to right
            for(int i=0;i<2;i++)
                for(int j=0;j<4;j++)
                    if(b[i][j] && equals(b[i][j],b[i+1][j+1],b[i+2][j+2],b[i+3][j+3]))
                        return b[i][j];
            
          // right to left
          for(int i=0;i<2;i++)
              for(int j=3;j<7;j++)
                  if(b[i][i] && equals(b[i][j],b[i+1][j-1],b[i+2][j-2],b[i+3][j-3]))
                      return b[i][j];
         
            return 0;

        } 

        int getScore(){

            return gameOver()*10;
        }

        void display(){
        
            for(int i=0;i<35;i++)
                cout<<'-';
            cout<<endl<<endl;

            for(int i=0;i<5;i++){
                for(int j=0;j<7;j++){
                
                    if(b[i][j]==0)
                        cout<<"[ ]"<<" ";
                    if(b[i][j]==1)
                        cout<<" P "<<" ";
                    if(b[i][j]==-1)
                        cout<<" B "<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        
        }

};

// class to abstract bot
class Bot{

    private:
        // to keep track of player
        // during minmax recursion
        bool player;

    public:
        Bot(bool p){
            player = p;
        }

        bool getPlayer(){
            return player;
        }
    
        int minmax(Board b,int *column,int depth){
        
            // setting depth 
            if(depth>3) return 0;
            
            // on every recursion increase the depth
            depth++;

            // return score on receiving completed board
            if(b.gameOver()){
                return b.getScore();
            }

            // max number of moves are 5
            int scores[7];
            int moves[7];
            int count=0;

            // bot to play optimized move
            // representing the opponent
            Bot max(!player);

            for(int j=0;j<7;j++){
            
                // instantiate board for test
                Board test(b);

                // try column j
                while(!test.play(player,j)){
                    j++;
                }
            
                scores[count] = max.minmax(test,column,depth);

                moves[count] = j;
                count++;
            
            }

            int maxscore = 0;
            int minscore = 0;

            // flag to check if all the input
            // gives same out put
            bool zeros = true;

            // get max / min / ties from the simulated board
            for(int i=0;i<count;i++){
                
                if(i<count && scores[i]!=scores[i+1] )
                    zeros=false;
            
                if(scores[i]>scores[maxscore])
                    maxscore=i;

                if(scores[i]<scores[minscore])
                    minscore=i;
            
            }

            if(zeros){

                *column =rand()%7;
                
            }

            if(player){
                *column = moves[maxscore];
                return scores[maxscore];
            }

            *column = moves[minscore];
            return scores[minscore];
        
        }

};

int main(){

    // initialize the board
    int player;

    srand((unsigned)time(0));

    int column;

    Board b;
    Bot bot(1);

    for(int i=0;i<35 && !b.gameOver(); i++){
    
        if((player+i)%2){
            
            bot.minmax(b,&column,0);

            b.play(true,column);

        }
        else{
            
            b.display();

            do{
            
                cout<<"column : ";
                cin>>column;

            }while(!b.play(false,column));


        }
    
    }

    b.display();


}

