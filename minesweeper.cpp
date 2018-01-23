#include<iostream>
#include<cstdio>
#include<ctime>

#define size 8

using namespace std;

int m[size+2][size+2];                   // the seeded matrix
int a[size+2][size+2];                   // open or closed check matrix
int bombs = 10;                          // number of bomb shells

void seed(){

    // make all the cells 0 
    for(int i=0;i<=size;i++)
        for(int j=0;j<=size;j++){
            m[i][j]=0;
            a[i][j]=0;
        }

    srand((unsigned)time(0));

    for(int i=0;i<bombs;i++){

        int r,c;
        r = 1+rand()%size;
        c = 1+rand()%size;
        
        if(m[r][c]!=0){i--;continue;}
        m[r][c]=-1;                           // place the bomb

        // add 1 to the surrounding cells 
        for(int i=r-1;i<=r+1;i++){      
            for(int j = c-1;j<=c+1;j++){      
                if(m[i][j]>=0)
                    m[i][j]+=1;
            }
        }
    }
}

// utility function prints each cell
// []        - printed for unopened cells
// <space>   - printed for opened empty cells
// <num>     - number is displayed if cell contains number
int display(){

    int count=0;

    for(int i=1;i<=size;i++){

        for(int j=1;j<=size;j++){

            if(a[i][j]==1){                         // if the cell is open then print

                if(m[i][j]==0)                      // cell is empty -> print space
                    cout<<" "<<'\t';
                else
                    cout<<m[i][j]<<'\t';            // cell contains tile -> print 
                
            }
            else{
                count++;
                cout<<"[]"<<'\t';                   // else print the unopened tile
            }

        }
        cout<<endl;
    }

    return count;
}

void zero(int r,int c){

    // if r and c are invalid  -> return
    if(r==-1)return; if(c==-1)return;
    if(c>size)return;if(r>size)return;


    if(a[r][c]==1)return;             //has already been open return

    a[r][c]=1;                        // open the valid cell

    if(m[r][c]!=0) return;            //if not empty return


    // if empty recursively open surrounding cells
    
    zero(r-1,c-1);     zero(r-1,c);      zero(r-1,c+1);

    zero(r,c-1);       /* m[r][c] */     zero(r,c+1);

    zero(r+1,c-1);     zero(r+1,c);      zero(r+1,c+1);
 
}

// returns status based on opened cell
int open(int r,int c){


    if(m[r][c]==-1) return 0;        // cell has bomb in it -> game over
    else{
        if(m[r][c]>0){               // cell is not empty and contains a tile
            a[r][c]=1;
        }
        else{
            zero(r,c);               // cell is empty
        }
        return 1;                    // return true for successful operation
    }
    
}

int main(){

    seed();
    int r,c;
    int closed = size*size;                  // total closed cells

    do{
   
        closed = display();                 // get number of closed cells
        cout<<"------------------------------------------------------------"<<endl;

        if(closed == bombs){                // win condition
            cout<<"you win!!"<<endl;
            return 0;
        }
 
        cout<<size<<" x "<<size<<" row column : ";
        cin>>r>>c;
    
    }while(open(r,c)); 

    cout<<"game over!"<<endl;

}
