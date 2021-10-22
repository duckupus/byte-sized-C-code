#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char board[3][3]={
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};

char init_board[3][3]={
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};

void p_board()	{
	printf("%c|%c|%c", board[0][0], board[0][1], board[0][2]);
	printf("\n=====\n");
	printf("%c|%c|%c", board[1][0], board[1][1], board[1][2]);
	printf("\n=====\n");
	printf("%c|%c|%c\n", board[2][0], board[2][1], board[2][2]);
}

int change_board(int one, int two, char change) {
	//first checks to ensure that it isn't already used
	if(board[one][two] != init_board[one][two])
		return 1;
	board[one][two]=change;
	return 0;
}

char check() {
	int i, q, nc=0;
	char ret;
	//checks all horizontal lines
	for(i=0; i < 3; i++) {
		if(board[i][0]==board[i][1] && board[i][0]==board[i][2]) {
			ret=board[i][0];
			return ret;
		}
	}
	//checks all vertical lines
	for(i=0; i < 3; i++) {
		if(board[0][i]==board[1][i] && board[0][i]==board[2][i]) {
			ret=board[0][i];
			return ret;
		}
	}
	//diagonal number 1 "\"
	if(board[0][0]==board[1][1] && board[0][0]==board[2][2]) {
		ret=board[0][0];
		return ret;
	}
	//diagonal number 2 "/"
	if(board[0][2]==board[1][1] && board[0][2]==board[2][0]) {
		ret=board[0][2];
		return ret;
	}
	//check if board is full
	for(i=0; i < 3; i++) {
		for(q=0; q < 3; q++) {
			if(board[i][q] == init_board[i][q]) {
				nc++;
			}
		}
	}
	if(nc==0)
		return 'f';
	return '0';
}

void bot(char bott) {
	int num, i=0, same;
	//tries to randomise output
	num=(rand() % 9 + 1);
	num--;
	while(num > 3) {
		num -= 3;
		i++;
	}
	same=change_board(i, num, bott);
	if(same==1)
		bot(bott);
	return;
}

int main()	{
	srand(time(0));
	char player='0', opponent;
	int ip=0, i, same;
	char w_condition='0';
	system("clear");
	while( player != 'X' && player != 'O') {
		printf("please select X or O\n");
		printf("X/O> ");
		player=getchar();
	}
	//init opponent according to what player has chosen
	if(player=='X')
		opponent='O';
	else
		opponent='X';
	while(w_condition == '0') {
		i=0;
		p_board();
		printf("choose a number from 1-9\n");
		scanf("%d", &ip);
		//checks if input is valid
		if(ip < 10 && ip > 0) {
			ip--;
			while(ip > 3) {
				ip -= 3;
				++i;
			}
		}
		else
			continue;
		same=change_board(i, ip, player);
		w_condition=check();
		if(w_condition != '0') 
			break;
		if(same==1)
			continue;
		bot(opponent);
		w_condition=check();
	}
	if(w_condition==player) {
		p_board();
		printf("You win!\n");
		return 0;
	}else if(w_condition==opponent) {
		p_board();
		printf("GG! try harder next time!\n");
		return 1000;
	}else if(w_condition=='f') {
		p_board();
		printf("Game has ended with a draw\n");
		return  0;
	}
	return 0;
}
