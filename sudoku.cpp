#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

class cell{

    public:
        int value;
        bool has_value;

        int *row_candidates;
        int *column_candidates;
        int *sqare_candidates;

};

class board{

    private:
        int size;
        int unset_cells;
        cell cells[10][10];

        int rows[10];
        int columns[10];
        int sqares[10];

        int square(int r,int c){

            int subdimension=sqrt(size);
            if(r<1 && r>size && c<1 && c>size) return -1;                           // failed

            return (((r-1)/subdimension)*subdimension)+((c-1)/subdimension);
        }

        void use(int c[],int num){
            c[num]=1;
        }

        void restore(int c[],int num){
            c[num]=0;
        }

    public:

        // init board 
        board(int s){
            size = s;
            unset_cells = size*size;

            for(int i=1;i<=size;i++){
                
                //                                                               initializing the candidates
                for(int j=1;j<=size;j++){
                    rows[j]=columns[j]=sqares[j]=0;
                }

                for(int j=1;j<=size;j++){
                       cells[i][j].has_value=false; 
                       cells[i][j].value = 0;
                       cells[i][j].row_candidates = rows+i;                     // address of the rows
                       cells[i][j].column_candidates = columns+i;               // address of the columns
                       cells[i][j].sqare_candidates  = sqares + square(i,j);
                }
            }

        }

        void set(int r,int c,int val){
        
            unset_cells-=1;
            cells[r][c].has_value=true;

            cells[r][c].value=val;
            
            use(cells[r][c].row_candidates,val);
            use(cells[r][c].column_candidates,val);
            use(cells[r][c].sqare_candidates,val);
        
        }

        void unset(int r,int c,int val){
        
            unset_cells+=1;        
            cells[r][c].has_value=false;
            cells[r][c].value = 0;

            restore(cells[r][c].row_candidates,val);
            restore(cells[r][c].column_candidates,val);
            restore(cells[r][c].sqare_candidates,val);
        
        }

        bool isSet(int r,int c){
            return cells[r][c].has_value;
        }

        void display(){
            
            for(int i=1;i<=size;i++){
                for(int j=1;j<=size;j++){
                    cout<<cells[i][j].value<<" ";
                } 
                cout<<endl;
            }
        
        }

        int following(int n){
            return ((n-size+1)%(size+1)+1);
        }

        int next(int *r,int *c){

            if((*r) == size && (*c) ==size)return 0;

            *c = following(*c);

            if(*c == 1)
                *r = following(*r);

            return 1;
        }

        int find_common(int r[],int c[],int s[],int atleast){
            
            for(int i=atleast;i<=size;i++){
                
                if(!r[i] && !c[i] && !s[i]) return i;
            
            }
            return -1;
        
        }

        int solve(int r,int c){
        
            int pre,val;
        
            if(unset_cells == 0){
                display();
                return 1;
            }

            while(isSet(r,c) && next(&r,&c));

            if(isSet(r,c))return 1;

            pre =1;

            while(1){
            
                val = find_common(cells[r][c].row_candidates,cells[r][c].column_candidates,cells[r][c].sqare_candidates,pre); 

                if(val == -1)break;

                set(r,c,val);
                if(solve(r,c))return 1;

                unset(r,c,val);
                pre=val+1;
            
            }
            return 0;
        }

};


int main(int cn,char * arg[]){

    char input;
    board b(9);

    int r=1,c=1;

    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
        
            cin>>input;
            cout<<input;

            if((isdigit(input) && input!='0') || input=='.'){
                if(c!='.')
                    b.set(r,c,input-'0');
                if(!b.next(&r,&c))
                    break;
            }
            
        }    
    }

    b.solve(1,9);
        
}
