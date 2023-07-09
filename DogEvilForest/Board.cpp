
#include "Board.hpp"
#include <iostream>
//#include "Dog.cpp"
#include "Dog.hpp"
using namespace std;

Board::Board(char diff, bool d){
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}
void Board::InitAll() {
	bool keepPlaying = true;

	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char p;
		cin >> p;
		level = p;
		startx = rand() % size;
		starty = 0;
		endx = rand() % size;
		endy = size-1;

		mydog.x = startx; //How do I make mydog an identifier???
		mydog.y = starty;
		starting_x = startx;
		ending_x=endx;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();

		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}

}


/***********************************************************************/
/* HERE'S WHERE THE CODE GOES!                                         */
/***********************************************************************/

void Board::printBoard() {
	//(8 pts)
	//Instructions for this method:
//	 this method first uses the dog's printDog method to print out info
//	 about the dog, and then it prints out the board as follows:
//	 *
//	 This method prints out hte board such that it looks like a board.  It
//	 prints a blank space for any square (for squares that do not have
//	 food, traps, walls, the dog, and aren't the beginning or the ending.
//   (at first, there will be no food or traps, or even walls or dog, but we
//   will be adding food as 'F' character, traps as 'T' character, walls as
//   '|' or '_' characters, and the dog 'D' character to the board, so you want
//   to print a space for everything that isn't a 'T','F','|','_',or'D'.
//	 Otherwise it prints out the character in the square. Note that I printed a
//	 border around the entire board so it was easier to look at, and, equally,
//	 I placed an -> arro (thats a minus and a greater than sign) in the border
//	 for where the beginning of the game was and where the end of the game was.

//mydog.printDog();  // COMMENT THIS IN WHEN YOU Write your Dog class!!
	for(int a=0; a<22; a++){
		cout << endl;
		for(int b=0; b<22; b++) {
			if(a==0||a==21) {
				cout << '_';
			}
			else if(b==0||b==21){
				if(a==starting_x+1 && b==0){
					cout<<'>';
				}
				else if(a==ending_x+1 && b==21){
					cout<<'<';
				}
				else{
					cout<<'|';
				}
			}
				else if(debug){
					if(board[a-1][b-1]=='+'){
						cout<<' ';
					}
					else{
						cout<<board[a-1][b-1];
					}
				}
				else{
					if(board[a-1][b-1]=='T'||board[a-1][b-1]=='+'){
						cout<<' ';
					}
					else{
						cout<<board[a-1][b-1];
					}
				}
			}
		}
	}



void Board::boardConfig() {
	//(8 pts)
	//Instructions for writing boardConfig:
	/* this method and the moveDog method are probably the longest methods.
	 * This method first puts dummy values in every square (I used '+' - I just didn't want
	 * every square to have gibberish, so I chose a character I wasn't using for any other
	 * purpose and initialized every square to have that value).
	 * I then added my random horizontal and vertical walls.
	 *
	 * Here's how I did it the walls:
	 *
	 * I only placed walls in the odd numbered rows and columns (in other words, row one might
	 * have a row, but then row 2 would not, whereas row three could and row 4 could not.
	 * Same with columns (although you can have flexibility.
	 *
	 * I picked an odd row or column that did not already have a wall in it at all.
	 *
	 * I generated a total of 10 walls.

	 * For each wall, I picked randomly for vertical or horizontal (just rand() % 2 to get either
	 * 0 for vertical, 1 for horizontal.
	 *
	 * I set the easy version to have at most 9 squares in a row or column as a wall, the
	 * medium to have at most 13 squares as walls in a row or column, and the hard version to
	 * have at most 16 squares per row or column.(but you can play with this because sometimes
	 * the hard version was seriously hard!!!
	 *
	 * Let's say I randomly decided to place a wall in row 3.  I then randomly chose 9 squares in
	 * row 3 to be a wall (if it was the easy version, 13 if it was the medium, and 16 if it was
	 * the hard)
	 *
	 * So that's the walls.  Then I added the 'D' to the beginning square nad an 'E' to the end square.
	 *
	 *
	 */
	for(int i=0; i<21; i++){
		for(int j=0; j<21; j++){
			board[i][j]='+';
		}
	}
	int numberofwalls=0;
	int maxwalls;
	if(level=='e'){
		maxwalls=10;
	}
	else if(level=='m'){
		maxwalls=13;
	}
	else if(level=='h'){
		maxwalls=16;
	}
	else{
		maxwalls=13;
	}
	for(int i=0; i<20; i++){
		for(int j=0; j<20; j++){
			if(i%2!=0){ //Adds walls in odd spots (if remainder is not 0 its odd)
				if(numberofwalls<maxwalls){
					if(rand()%2==0){ //Vertical Walls
						int a=rand()%20;
						if(board[i][a]=='+'){
							board[i][a]='|';
							numberofwalls++;
						}
						else{
							a=rand()%20;
							board[i][a]='|';
							numberofwalls++;
						}
					}
					else{ //Horizontal walls
						int a=rand()%20;
						if(board[i][a]=='+'){
							board[i][a]='_';
							numberofwalls++;
						}
						else{
							a=rand()%20;
							board[i][a]='_';
							numberofwalls++;
						}
					}
				}
			}
		}
		numberofwalls=0;
	}
	board[mydog.x][mydog.y]='D'; //places D character for dog
	board[ending_x][size-1]='E';
}


void Board::addFood() {
	//cout<<level<<endl;
	// (5 pts)
	/* Instructions for writing addFood:
	/* this method randomly adds food around the board.  For easy, I added the field size
	 * number of foods randomly around the board.  For medium, I added size-2 foods, and for
	 * hard I added size-4 foods.  The amount of strength the dog gets when they eat (aka
	 * move onto) the food is determined in the moveDog method.
	 */
	int food=0, a, b, i;
	if(level=='e'){
		food=20;
	}
	else if(level=='m'){
		food=15;
	}
	else if(level=='h'){
		food=10;
	}
	else{
		food=15;
	}
	for(i=0; i<food;){
		a=rand()%20;
		b=rand()%20;
		if(board[a][b]=='+'){
			board[a][b]='F'; //Sets food character to F
			i++;
		}
	}
}

void Board::addTraps() {
	// (5 pts)
	//Instructions for addTraps
	/* this method randomly adds traps around the board.  For easy I added size - 6 traps,
	 * for medium, I added size - 8 traps, and for hard I added size - 10 traps.  Note: Traps are
	 * only printed on the board when the game is in debug mode.  The amount of strength each trap
	 * saps from the dog is determined in the moveDog method when the dog moves on a Trap.
	 */
	int trap;
	//cout << level << endl;
	if(level=='e'){
		trap=6;
	}
	else if(level=='m'){
		trap=8;
	}
	else if(level=='h'){
		trap=10;
	}
	else{
		trap=8;
	}
	int a, b, i;
	for(i=0; i<trap;){
		a=rand()%size;
		b=rand()%size;
		if(board[a][b]=='+'){
			board[a][b]='T';
			i++;
		}
	}
}


bool Board::moveDog(char c) {
	// (12 pts)
	//Instructions for moveDog
	/* This is a somewhat long method.
		 * First, it determines the new coordinats of the dog, based on teh direction in which the
		 * dog wants to move (based on what c holds - u is up, d is down, l is left, r is right).
		 *
		 * If the dog is at teh edge of the board, teh dog should not move
		 *
		 * If the dog moves over food, a random number between 2 and 17 is generated, and the
		 * dog's changeStrength method is used to increase the dog's strength by the random amount.
		 *
		 * If the dog moves over the end of the board, the dog's won method is called and false is
		 * returned from this method.
		 *
		 * If the dog moves over a Trap, a random number between 2 and 17 is generated and the dog's
		 * changeStrength method is called with that negative number.  (Note that the changeStrength
		 * method returns a boolean indicating whether the dog's strength has gone to 0 or less, and
		 * thus the dog has died and the game is over. That boolean value is returned from this method).
		 *
		 * If the dog moves over a wall, the method checks to see if the dog has enough strength to
		 * knock down the wall (I made it cost 6 strength points to knock down a wall).  If the dog
		 * has enough strength, the user is asked, "Do you want to knock down that wall?"  If the user
		 * responds "yes", then the wall is knocked down, the dog moves into that square, adn the dog's
		 * strength decreases by 6.  If the answer is "no", the dog loses 1 strength point, just because.
		 *
		 * If the dog moves into a blank square, the dog loses 2 strength points using the changeStrength
		 * method (which, again, will return false if the dog has lost all their strength and died.
		 *
		 * NOTE: I am not concerned with the precise rules here.  If you want to change the range of
		 * random numbers for food, if you are worried about whether you still lose 2 strength points for
		 * moving even though you gained points for moving over food - I'm leaving all that to your preference.
		 * I am concerned that you are using classes, objects, and object methods and accessing object
		 * fields correctly!
		 *
		 */
	/* (12 pts) code for the moveDog method goes here */
		int changex;
		int changey;
		bool buff;
		if( c =='u' || c == 'U'){
			changex=mydog.x-1;
			changey=mydog.y;

			if(board[changex][changey] == ' '){
				// blank space within borders
				board[mydog.x][mydog.y]=' ';
				board[changex][changey]='D';
				mydog.x=changex;
				buff=mydog.Strength_Change(-2);
			}
			else if(board[changex][changey]=='F'){
				board[mydog.x][mydog.y]=' ';
				int food = rand()%16+2;
				mydog.x=changex;
				board[mydog.x][mydog.y]='D';
				cout<<"You Ate Food!!!"<<endl;
				buff=mydog.Strength_Change(food);
			}
			else if(board[changex][changey]=='T'){
				board[mydog.x][mydog.y]=' ';
				int trap= rand()%16+2;
				mydog.x=changex;
				board[mydog.x][mydog.y]='D';
				cout<<"Its A Trap!!!"<<endl;
				buff=mydog.Strength_Change(trap*-1);
				//if(buff){
				//}
			}
			else if( board[changex][changey]=='|' || board[changex][changey] =='_'){
				// walls
				if(mydog.strength>7 ){
					cout << "Do you want to break wall? (Yes or No)" << endl;
					string answer = "no";
					cin>>answer;
					if (answer == "yes" || answer == "Yes") {
						board[mydog.x][mydog.y]=' ';
						mydog.x=changex;
						board[mydog.x][mydog.y]='D';
						buff=mydog.Strength_Change(-6);

					}

					else {
						buff=mydog.Strength_Change(-2);
					}
				}
			}
			else if(board[changex][changey]=='E'){
				board[mydog.x][mydog.y]=' ';
				mydog.x=changex;
				board[mydog.x][mydog.y]='D';
				mydog.won();
				return false;
			}
			//else if(changex<0){
				//cout<<"border"<<endl;

			//}
			else {
				board[mydog.x][mydog.y]=' ';
							board[changex][changey]='D';
							mydog.x=changex;
							buff=mydog.Strength_Change(-2);
			}

	}
		if( c=='d' || c== 'D'){ //down
			changex=mydog.x+1;
			changey=mydog.y;

			if(board[changex][changey] == ' '){
				// blank space within borders
				board[mydog.x][mydog.y]=' ';
				board[changex][changey]='D';
				mydog.x=changex;
				buff=mydog.Strength_Change(-2);
			}
			else if(board[changex][changey]=='F'){
				// Food
				board[mydog.x][mydog.y]=' ';
				int food = rand()%16+2;
				mydog.x=changex;
				board[mydog.x][mydog.y]='D';
				cout<<"You Ate Food!!!"<<endl;
				buff=mydog.Strength_Change(food);
			}
			else if(board[changex][changey]=='T'){
				board[mydog.x][mydog.y]=' ';
				int trap= rand()%16+2;
				mydog.x=changex;
				board[mydog.x][mydog.y]='D';
				cout<<"Its A Trap!!!"<<endl;
				buff=mydog.Strength_Change(trap*-1);
				if(buff){
				}
			}
			else if( board[changex][changey]=='|' || board[changex][changey] =='_'){
				// walls
				if(mydog.strength>7 ){
					cout << "Do you want to break wall? (Yes or No)" << endl;
					string answer;
					cin>>answer;
					if (answer == "yes" || answer == "Yes") {
						board[mydog.x][mydog.y]=' ';
						mydog.x=changex;
						board[mydog.x][mydog.y]='D';
						buff=mydog.Strength_Change(-6);

					}
					else {
						buff=mydog.Strength_Change(-1);
					}
				}
			}
			else if(board[changex][changey]=='E'){
				board[mydog.x][mydog.y]=' ';
				mydog.x=changex;
				board[mydog.x][mydog.y]='D';
				mydog.won();
				return false;
			}
			//else if(changey<=0){
				//cout<<"left Border"<<endl;
			//}
			else{
				board[mydog.x][mydog.y]=' ';
							board[changex][changey]='D';
							mydog.x=changex;
							buff=mydog.Strength_Change(-2);
			}
		}
		if( c=='r' || c== 'R'){
			changex=mydog.x;
			changey=mydog.y+1;

			if(board[changex][changey] == ' '){
				// blank space within borders
				board[mydog.x][mydog.y]=' ';
				board[changex][changey]='D';
				mydog.y=changey;
				buff=mydog.Strength_Change(-2);
			}
			else if(board[changex][changey]=='F'){
				// Food
				board[mydog.x][mydog.y]=' ';
				int food = rand()%16+2;
				mydog.y=changey;
				board[mydog.x][mydog.y]='D';
				cout<<"You Ate Food!!!"<<endl;
				buff=mydog.Strength_Change(food);
			}
			else if(board[changex][changey]=='T'){
				//Trap
				board[mydog.x][mydog.y]=' ';
				int trap= rand()%16+2;
				mydog.y=changey;
				board[mydog.x][mydog.y]='D';
				cout<<"Its A Trap!!!"<<endl;
				buff=mydog.Strength_Change(trap*-1);
				if(buff){
				}
			}
			else if( board[changex][changey]=='|' || board[changex][changey] =='_'){
				// walls
				if(mydog.strength>7 ){
					cout << "Do you want to break wall? (Yes or No)" << endl;
					string answer;
					cin>>answer;
					if (answer == "yes" || answer == "Yes") {
						board[mydog.x][mydog.y]=' ';
						mydog.y=changey;
						board[mydog.x][mydog.y]='D';
						buff=mydog.Strength_Change(-6);

					}
					else {
						buff=mydog.Strength_Change(-1);
					}
				}
			}
			else if(board[changex][changey]=='E'){
				board[mydog.x][mydog.y]=' ';
				mydog.y=changey;
				board[mydog.x][mydog.y]='D';
				mydog.won();
				return false;
			}
			else{
				board[mydog.x][mydog.y]=' ';
							board[changex][changey]='D';
							mydog.y=changey;
							buff=mydog.Strength_Change(-2);
			}
	}
		if( c=='l' || c== 'L'){
			changex=mydog.x;
			changey=mydog.y-1;

			if(board[changex][changey] == ' '){
				// blank space within borders
				board[mydog.x][mydog.y]=' ';
				board[changex][changey]='D';
				mydog.y=changey;
				buff=mydog.Strength_Change(-2);
			}
			else if(board[changex][changey]=='F'){
				// Food
				board[mydog.x][mydog.y]=' ';
				int food = rand()%16+2;
				mydog.y=changey;
				board[mydog.x][mydog.y]='D';
				cout<<"You Ate Food!!!"<<endl;
				buff=mydog.Strength_Change(food);
			}
			else if(board[changex][changey]=='T'){
				//Trap
				board[mydog.x][mydog.y]=' ';
				int trap= rand()%16+2;
				mydog.y=changey;
				board[mydog.x][mydog.y]='D';
				cout<<"Its A Trap!!!"<<endl;
				buff=mydog.Strength_Change(trap*-1);
				if(buff){
				}
			}
			else if( board[changex][changey]=='|' || board[changex][changey] =='_'){
				// walls
				if(mydog.strength>7 ){
					cout << "Do you want to break wall? (Yes or No)" << endl;
					string answer;
					cin>>answer;
					if (answer == "yes" || answer == "Yes") {
						board[mydog.x][mydog.y]=' ';
						mydog.y=changey;
						board[mydog.x][mydog.y]='D';
						buff=mydog.Strength_Change(-6);

					}else {
						buff=mydog.Strength_Change(-1);
					}
				}
			}
			else if(board[changex][changey]=='E'){
				board[mydog.x][mydog.y]=' ';
				mydog.y=changey;
				board[mydog.x][mydog.y]='D';
				mydog.won();
				return false;
			}
			else{
				board[mydog.x][mydog.y]=' ';
							board[changex][changey]='D';
							mydog.y=changey;
							buff=mydog.Strength_Change(-2);
			}
	}
		return buff;
}

void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}


}


