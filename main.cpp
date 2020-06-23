#include <bits/stdc++.h>
using namespace std;
const char human = 'X';
const char human2='O';
const char ai = 'O';

enum Player { HUMAN, AI };

struct Move {
	int x;
	int y;
};
class MainGame{
    int fc=0;
    char board[3][3];
public:
    MainGame(){
		for (int i=0;i<3;i++) {
			for(int j=0;j<3;j++) {
				board[i][j]='_';
			}
		}
    }
    void print(){
        cout<<"\t"<<0<<"\t"<<1<<"\t"<<2<<endl;
        for(int i=0;i<3;i++){
            cout<<i<<"\t";
            for(int j=0;j<3;j++){
                cout<<board[i][j]<<"\t";
            }
            cout<<endl<<endl;
        }
        cout<<"------------------"<<endl;
    }

    pair<string,string> players(){
        string p1;
        string p2;
        pair<string,string> p;
        int choice;
        cout<<"Choose Mode :\n"<<"1)PVP\n"<<"2)PVE"<<endl;
        cin>>choice;
        if(choice==1){
            cout<<"What's your name player1 ? : "<<endl;
            cin>>p1;
            cout<<"What's your name player2 ? : "<<endl;
            cin>>p2;
        }
        else{
            cout<<"What's your name player ? : "<<endl;
            cin>>p1;
            p2="BOT";
        }
        p.first=p1;
        p.second=p2;
        return(p);
    }

    bool winningCombinations(Player player){
	char playerChar;
	if(player == HUMAN) playerChar = human;
	else playerChar = ai;

	for(int i = 0; i < 3; i++) {
		if(board[i][0] == playerChar && board[i][1] == playerChar&& board[i][2] == playerChar)
			return true;

		if(board[0][i] == playerChar && board[1][i] == playerChar
			&& board[2][i] == playerChar)
			return true;
	}

	if (board[0][0] == playerChar && board[1][1] == playerChar
		&& board[2][2] == playerChar) {
		return true;
	} else if (board[0][2] == playerChar && board[1][1] == playerChar
		&& board[2][0] == playerChar) {
		return true;
	}

	return false;
}


    bool gameOver(){
        if(winningCombinations(HUMAN)) return true;
        else if(winningCombinations(AI))return true;
        bool emptySpace=false;
        for(int i = 0; i < 3; i++) {
            if(board[i][0] == '_' || board[i][1] == '_' || board[i][2] == '_')
                emptySpace = true;
        }
        return !emptySpace;
        }

    int score(){
        if(winningCombinations(HUMAN))
            return(10);
        else if(winningCombinations(AI))
            return(-10);
        else return(0);
    }

    int maxSearch(char AIboard[3][3]){
        if(gameOver())return score();
        Move bestMove;
        int bestMoveScore=-1000;
        	for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(AIboard[i][j]=='_'){
                        AIboard[i][j]='X';
                        int tempMoveScore= minSearch(AIboard);
                        if(tempMoveScore>=bestMoveScore){
                            bestMoveScore=tempMoveScore;
                            bestMove.x=i;
                            bestMove.y=j;
                        }
                        AIboard[i][j]='_';
                    }
                }
            }
            return bestMoveScore;
    }

    int minSearch(char AIboard[3][3]){
        if(gameOver()) return score();
        Move bestMove;
        int bestMoveScore=1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(AIboard[i][j]=='_'){
                    AIboard[i][j]='O';
                    int tempMove=maxSearch(AIboard);
                    if(tempMove<=bestMoveScore){
                        bestMoveScore=tempMove;
                        bestMove.x=i;
                        bestMove.y=j;
                    }
                    AIboard[i][j]='_';
                }
            }
        }
        return bestMoveScore;
    }

    Move minMax(char AIboard[3][3]){
        int bestMoveScore=100;
        Move bestMove;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(AIboard[i][j]=='_'){
                    AIboard[i][j]='O';
                    int tempMoveScore=maxSearch(AIboard);
                    if(tempMoveScore<=bestMoveScore){
                        bestMoveScore=tempMoveScore;
                        bestMove.x=i;
                        bestMove.y=j;
                    }
                    AIboard[i][j]='_';
                }
            }
        }
        return bestMove;
    }

    void play(){
        string name1,name2;
        string mode;
        cout<<"Choose Mode (pvp,pve)"<<endl;
        cin>>mode;
        int turn = 0;
        print();
        if (mode=="pve"){
            cout<<"Player enter your name: "<<endl;
            cin>>name1;
            while(!winningCombinations(HUMAN) && !winningCombinations(AI) && !gameOver()) {
                if(turn % 2 == 0) {
                    getHumanMove();
                    if(winningCombinations(HUMAN)) cout << name1<<" Wins" << endl;
                    turn++;
                    print();
                } else {
                    cout << endl << "Computer Player Move:" << endl;
                    Move AImove = minMax(board);
                    board[AImove.x][AImove.y] = ai;
                    if(winningCombinations(AI)) cout << "BOT Wins" << endl;
                    turn++;
                    print();
                }
            }
        }
        if(mode=="pvp"){
            cout<<"Player 1 enter your name: "<<endl;
            cin>>name1;
            cout<<"Player 2 enter your name: "<<endl;
            cin>>name2;
            int turn = 0;
            print();
            while(!winningCombinations(HUMAN) && !winningCombinations(AI) && !gameOver()) {
                if(turn % 2 == 0) {
                    getHumanMove();
                    if(winningCombinations(HUMAN)) cout <<name1<<" Wins" << endl;
                    turn++;
                    print();
                } else {
                    getHumanMove2();
                    if(winningCombinations(AI)) cout << name2<<" Wins" << endl;
                    turn++;
                    print();
                }
            }
        }
    }
    void getHumanMove() {
	int x, y = -1;
	while(true) {
		cout << "Your Move: ";
		string restofline;
		cin>>x>>y;
		if(board[x][y]=='_')break;
		else cout<<"ERROR try again! "<<endl;

	}
	board[x][y] = human;
}
    void getHumanMove2() {
	int x, y = -1;
	while(true) {
		cout << "Your Move: ";
		string restofline;
		cin>>x>>y;
		if(board[x][y]=='_')break;
		else cout<<"ERROR try again! "<<endl;

	}
	board[x][y] = human2;
}


};


int main()
{
    char pressAnyKeyToExit;
    MainGame xo;
    xo.play();
    cout<<"Press any key to exit: ";
    cin>>pressAnyKeyToExit;
    return 0;
}
