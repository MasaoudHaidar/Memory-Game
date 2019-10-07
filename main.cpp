#include <iostream>
#include <math.h>
#include <time.h>
#include <algorithm>

unsigned int n,s1,s2;
unsigned int a[100][100];
unsigned int md;
unsigned int vis[10000];
unsigned int rev[10000];
unsigned int s;
unsigned int u;

//Our random number generator:
unsigned int random_number(){
    //The function rand() gives the same numbers for every game, so we're using the value of the time to help generate random numbers
    return ((rand()%md)*(time(nullptr)%md))%md;
}


void out(){
    char o[100][100]; //We will use o to store the desired output
    std::string f[5];        //We will use f to show our cards
    f[0]="-----";
    f[1]="|   |";
    f[2]="|   |";
    f[3]="|   |";
    f[4]="-----";
    for (int w=0,j=0;w<n*n;w++,j++){ //w counts the cards , i counts the rows , j counts the columns
        int i=w/n;
        std::string k;  //This will store the number on the card as a string
        k="rev";
        if (rev[w]){}                                            //Revealed cards
        else if (w<10) {k[0]='0';k[1]='0';k[2]=w+'0';}           //One digit numbers (00x)
        else if (w<100) {k[0]='0';k[1]=w/10+'0';k[2]=w%10+'0';}  //Two digit numbers (0xy)
        else {k[0]=w/100+'0';k[1]=(w/10)%10+'0';k[2]=w%10+'0';}  //Three digit numbers (xyz)

        //Storing f and k into o:
        for (int x=i*5;x<i*5+5;x++)
        {
            if (x!=2+i*5) for (int y=j*5;y<j*5+5;y++)  o[x][y]=f[x-5*i][y-5*j];
            else {
                o[x][j*5]='|';
                o[x][j*5+1]=k[0];
                o[x][j*5+2]=k[1];
                o[x][j*5+3]=k[2];
                o[x][j*5+4]='|';

            }
        }

        if (j==n-1) j=-1; //restart j when you reach the end of the row
    }

    //Output o:
    for (int i=0;i<n*5;i++)
    {
        for (int j=0;j<n*5;j++) std::cout<<o[i][j];
        std::cout<<std::endl;
        if (i%5==0 && i)std::cout<<std::endl; //Leave a line between different rows of cards
    }

}
int main()
{
    std::cout<<"Enter number of rows and columns (This has to be an even number, we recommend 4, maximum is 30):";
    std::cin>>n;
    if (n==0){
        std::cout<<"Challenge yourself more"<<std::endl;
        return 0;
    }

    if (n%2!=0) n=(n/2)*2; //n has to be even or else there will be a card that doesn't have a match
    n=std::min(n,(unsigned int)30);           //The maximum size of the game
    md=n*n/2;              // 0 to md-1 are the numbers behind the cards

    //Choosing the random numbers behind the cards: ( We need two cards of each number )
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int x=random_number();    //We need a random number between 0 and md-1
            while (vis[x]>=2){  //If we already have two cards of that number we need to change it
                x=random_number();
            }
            vis[x]++;
            a[i][j]=x;
        }
    }

    while (s<n*n){
    out(); //This outputs the flipped cards

    std::cout<<"Enter two cards to reveal:"<<std::endl;
    int x,y;
    std::cin>>x>>y;
    if (x<0 || x+1>n*n || y<0 || y+1>n*n){
        std::cout<<"numbers not valid"<<std::endl;
        continue;
    }
    if (x==y) {
        std::cout<<"Choose different numbers"<<std::endl;
        u++;
        continue;
    }
    if (a[x/n][x%n]==a[y/n][y%n]){
        std::cout<<"Matched"<<std::endl;
        s+=2;                  //This is the total number of matched cards
        // Tag the cards as revealed:
        rev[x]=1;
        rev[y]=1;
    }
    else {
        std::cout<<"Wrong"<<std::endl<<"Card "<<x<<" is "<<a[x/n][x%n]<<std::endl;
        std::cout<<"Card "<<y<<" is "<<a[y/n][y%n]<<std::endl;
    }
    u++;  //This counts the total numbers of turns taken
    }
    std::cout<<"You win"<<std::endl<<"The game took you "<<u<<" turns"<<std::endl;
    if (u>md) std::cout<<"Can you solve it faster?"<<std::endl;
    else std::cout<<"Wow, no one will solve it faster, Congrats!!"<<std::endl;
    return 0;
}
