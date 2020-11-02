#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

class Log {
	public:
		static void info(string message = "") {
			cout << message << endl;
		}
};

class Dice {
	public:
		int roll(int il_sc) {
			int result = (rand() % il_sc) + 1;

			ostringstream ss;
			ss << "Dice roll: " << result;
			Log::info(ss.str());

			return result;
		}
};

class Pawn {
	public:
		int position;
		string name;

		Pawn() {}

		Pawn(string name) {
			this->name = name;
			this->position = 0;

			Log::info(name + " joined the game.");
		}
};

class Board {
private:
    int maxPosition,max_tura,max_sciany;

	public:
        short warunek=0;
		vector<Pawn> pawns;
		Dice dice;
		Pawn winner;
		int turnsCounter;


		Board() {
			this->turnsCounter = 0;
		}

		void performTurn() {
			this->turnsCounter++;
                if(this->turnsCounter<=max_tura){
                    ostringstream ss;
                    ss << "Turn " << this->turnsCounter;
                    Log::info();
                    Log::info(ss.str());

                    for(int i = 0; i < this->pawns.size(); i++) {
                        int rollResult = this->dice.roll(max_sciany);
                        Pawn &pawn = this->pawns.at(i);
                        pawn.position += rollResult;

                        ostringstream ss;
                        ss << pawn.name << " new position: " << pawn.position;
                        Log::info(ss.str());

                    if(pawn.position >= this->maxPosition) {
					this->winner = pawn;
					throw "Winner was called!";
                        }
                    }
                    this->warunek++;
                }
                else {
                        this->warunek=0;
                        throw "Winner was called!";
                     }



		}

		void ustaw_dane(int max_pos,int max_tur,int max_scian){

            this->maxPosition=max_pos;
            this->max_tura=max_tur;
            this->max_sciany=max_scian;

		}
};

int main() {
	srand(time(NULL));
	int liczba_graczy,max_scian,max_pol,max_tur;
	string nazwy_graczy;

	Board board = Board();
	board.dice = Dice();

    while(liczba_graczy<=2 || liczba_graczy>=11){
        cout<<"ilu ma byc graczy?"<<endl;
        cin>>liczba_graczy;
    }
    for(short i=0; i<=liczba_graczy-1;i++){
        cout<<"podaj nazwe "<<i+1<<" gracza:"<<endl;
        cin>>nazwy_graczy;
        board.pawns.push_back(Pawn(nazwy_graczy));
    }
    cout<<"podaj ilosc scian kostki"<<endl;
    cin>>max_scian;
    cout<<"podaj maks liczbe pol"<<endl;
    cin>>max_pol;
    cout<<"podaj maks liczbe turn"<<endl;
    cin>>max_tur;

    board.ustaw_dane(max_pol, max_tur, max_scian);

	try {
		while(true) {
			board.performTurn();
		}
	} catch(const char* exception) {
		Log::info();
            if(board.warunek>=1){Log::info(board.winner.name + " won");
            }
                else cout<<"koniec gry nikt nie wygral"<<endl;
        }

	return 0;
}



