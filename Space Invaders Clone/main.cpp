#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameOver = false;
bool bulletHasBeenInstantiated = false;
bool isGoingLeft = true;

int playerXPos, playerYPos, score, bulletXPos, bulletYPos;

int initTimer = 20;
int timerTillWalk = 20;
int initEnemyNumber = 8;

int mapWidth = 20;
int mapHeight = 20; 

int mapLimit = 1;

float enemyXPositions[100];
float enemyYPositions[100];

float enemyYPos[4];

void Setup() {
	int tempIndex = 0;
	int counter = 1;
	int ypos = 2;
	int additioner = 2;

	playerXPos = mapWidth / 2;
	playerYPos = mapHeight - 1;

	enemyXPositions[0] = 6;
	//enemyYPositions[0] = 2;
	enemyYPos[0] = 2;
	//enemyYPositions[0] = 0;
	//enemyYPositions[0] = 2;

	for (int i = 1; i < initEnemyNumber + 1; i++) {
		enemyXPositions[i] = enemyXPositions[tempIndex] + additioner;
		//enemyYPositions[i] = 2;
		enemyYPos[i] = ypos;
		counter++;
		tempIndex++;
		if (counter == 4) {
			ypos++;
			counter = 0;
			tempIndex = 0;
			additioner = 0;
		}
	}
}

void Draw() {

	system("cls");

	for (int i = 0; i < mapWidth + 1; i++) {
		cout << "#";
		//cout << endl;
	}

	cout << endl;

	for (int i = 0; i < mapHeight; i++) {

		for (int j = 0; j < mapWidth; j++) {
			if (j == 0) {
				cout << "#";
			}
			else {
				cout << " ";
			}

			for (int k = 0; k < initEnemyNumber; k++) {
				if (i == enemyYPos[k] && j == enemyXPositions[k]) {
					
					if (k == 0) {
						cout << "W";
					}
					else
					{
						cout << "O";
					}
				}
			}

			if (i == playerYPos && j == playerXPos) {
				cout << "^";
			}

			if (bulletHasBeenInstantiated) {
				if (i == bulletYPos && j == bulletXPos) {
					cout << "!";
				}
			}

			if (j == mapWidth - 1) {
				cout << "#";
				cout << endl;
			
			}
				
		}

	}

	cout << endl;
	cout << "Score: " << score;
}

void Input() {
	while(_kbhit()) {
		switch (_getch())
		{
		case 'a':
			if (playerXPos > 0) {
				playerXPos--;
			}
			break;
		case 'd':
			if (playerXPos < mapWidth - 2) {
				playerXPos++;
			}
			break;
		case'p':
			if (!bulletHasBeenInstantiated) {
								
				bulletXPos = playerXPos;
				bulletYPos = playerYPos - 1;
				bulletHasBeenInstantiated = true;
				
			}
		}
	}
}

void Logic() {
	
	//float additionalXNum = 1;

	//for(int i = 0; i < )
	
	for (int i = 0; i < initEnemyNumber; i++) {
		if (enemyYPos[i] == playerYPos) {
			gameOver = true;
		}
	}


	for (int i = 0; i < initEnemyNumber; i++) {

		bool isLastOne = true;

		for (int j = 0; j < initEnemyNumber; j++) {
			if (isGoingLeft) {
				if (enemyXPositions[j] < enemyXPositions[i] && enemyXPositions[i] < 50) {
					isLastOne = false;
				}
			}
			else {
				if (enemyXPositions[j] > enemyXPositions[i] && enemyXPositions[j] < 50) {
					isLastOne = false;
				}
			}
		}

		if (isLastOne && enemyXPositions[i] == mapLimit) {
			
			isGoingLeft = !isGoingLeft;

			/*
			else {
				isGoingLeft = true;
			}*/

			if (isGoingLeft) {
				mapLimit = 1;
			}
			else {
				mapLimit = mapWidth - 5;
			}
			
			for (int k = 0; k < initEnemyNumber; k++) {
				enemyYPos[k] += 1;
				//isGoingLeft = ;				
			}
		}
	}




	if (bulletHasBeenInstantiated && bulletYPos > 0) {
		bulletYPos--;
	}

	if (bulletYPos <= 0) {
		bulletHasBeenInstantiated = false;
	}

	for (int i = 0; i < initEnemyNumber; i++) {
		if (bulletYPos == enemyYPos[i] && bulletXPos == enemyXPositions[i]) {
			enemyYPos[i] = 50;
			enemyXPositions[i] = 80;
			initTimer -= 3;
			bulletYPos = 0;
			score += 10;
		}
	}

	timerTillWalk--;

	for (int i = 0; i < initEnemyNumber; i++) {
		if (timerTillWalk <= 0) {
			if (isGoingLeft) {
				enemyXPositions[i]--;
			}
			else {
				enemyXPositions[i] ++;
			}
		}
	}

	if (timerTillWalk <= 0) {
		timerTillWalk = initTimer;
	}
}

int main() {

	Setup();

	while(!gameOver) {
		Draw();
		Input();
		Logic();

		//Sleep(50);
	}

	return 0;
}