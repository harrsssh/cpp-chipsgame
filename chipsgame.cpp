#include<bits/stdc++.h>
using namespace std;
const int MAX_CHIPS = 100;
const float MAX_TURN = .5;

struct player
{
    string name;
    int numwins;
};


string findplayersname(player playername[],bool);
void getusernames(player playername[]);
int askmove(bool, int, player playername[]);
void addwins(player playernames[], bool);

int main(int argc, char const *argv[])
{
    char playagain;
    
    do{
    bool player1turn = true;
    bool gameover = false;

    int movecount = 0;
    int chipsinpile = 0;
    int chipstaken = 0;
    int maxperturn = 0;
    player playername[2];

    ofstream outfile;
    outfile.open("winners.txt", ios::app);
    

    srand(time(0));
    getusernames(playername);

    chipsinpile = rand()%MAX_CHIPS + 1;
    cout << "this room will start with " << chipsinpile << " chips in the pile.\n" << endl;
    gameover = false;
    movecount = 0;
    
    while(gameover == false)
    {
    chipsinpile = chipsinpile - askmove(player1turn, chipsinpile, playername);
    cout << "\nThere are " << chipsinpile << " left in the pile..\n" << endl;
    
    if(chipsinpile == 0){
        gameover = true;
        cout << "Congratulations " << findplayersname(playername, player1turn) << " you won!\n";
        outfile << findplayersname(playername,player1turn) << " won the game in " << movecount << " moves\n";
        cout << "do you want to play again...(y/n)\n";
        cin >> playagain;
        playagain = toupper(playagain);
        addwins(playername, player1turn);
        cout << playername[0].name << " had " << playername[0].numwins << " total wins this round.\n";
        cout << playername[1].name << " had " << playername[1].numwins << " total wins this round.\n";
        outfile.close();
    }
    
    else
    {
        player1turn = !player1turn;
        movecount++;
    }
    }
    }while(playagain == 'Y');
    
    return 0;
}

string findplayersname(player playername[], bool playerturn){
    if(playerturn == true){
        return playername[0].name;
    }
    
    else 
        return playername[1].name;
}

void getusernames(player playername[]){
    cout << "Player1, please enter your name: " << endl;
    cin >> playername[0].name;
    cout << "Player2, please enter your name: " << endl;
    cout << "if you wish to play against computer please enter 'AI'\n";
    cin >> playername[1].name;
    playername[0].numwins = 0;
    playername[1].numwins = 0;
}

int askmove(bool player1turn, int chipsinpile, player playername[]){
    int chipstaken;
    int maxperturn = MAX_TURN*chipsinpile;

    do{
        cout << findplayersname(playername, player1turn) << "'s turn!\n";
        cout << "How many chips would you like?\n";
        cout <<"you can take upto ";

        if(maxperturn == 0){
            cout << "1\n";
        }
        else{
            cout << maxperturn << endl;
        }
        if(findplayersname(playername,player1turn) == "AI"){
            
            if(maxperturn == 0){
            chipstaken = 1;
            cout << "AI took 1\n";
            }
            
            else{
            chipstaken = rand()%maxperturn + 1;
            cout << "AI took " << chipstaken << endl;
            }
        }
        
        else{
            cin >> chipstaken;
        }
    } while((chipstaken > maxperturn) && (chipsinpile > 1));
    return chipstaken;
}

void addwins(player playername[],bool player1turn)
{
    if(player1turn){
        playername[0].numwins++;
    }
    
    else{
        playername[1].numwins++;
    }
}
