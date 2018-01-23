#include<iostream>
#include<ncurses.h>
using namespace std;

int main(){

    char opt;
    int number=0;

    // probably ask for range 
    cout<<"guess a number from 0 to 31"<<endl;

    for(int k=0;k<5;k++){
    
        for(int i=1;i<32;i++){
        
            for(int j=0;j<4 && i<32;i++)
                if(i&(1<<k)){
                    cout<<i<<" ";
                    j++;
                }

            cout<<endl;
        }

        cout<<"do you find your number in the list ? "<<endl;
        cout<<"y/n : ";

        cin>>opt;

        if(opt=='y' || opt=='Y' || opt=='n' || opt== 'N'){

            if(opt=='y' || opt=='Y')
                number+=(1<<k);
        }
        else{
            
            cout<<"aborting game due to unknown input "<<endl;
            return 0;

        }


    }

    cout<<"the number you thought of was "<<number<<endl;

}
