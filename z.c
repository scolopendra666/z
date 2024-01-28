#include <stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define PADDLE_SIZE 3

int ballX, ballY;
int paddle1, paddle2;
int directionX, directionY;
int player1Score, player2Score;

void initializeGame() {
    ballX = FIELD_WIDTH / 20 - 2;
    ballY = 12;
    paddle1 = 11;
    paddle2 = 11;
    directionX = 1;
    directionY = 0;
    player1Score = 0;
    player2Score = 0;
}
void newRound(){
	paddle1 = 11;
            paddle2 = 11;
            directionX = -directionX;
        directionY = -directionY;
}

void drawField() {
    printf("\033[H\033[J");

    // Draw field
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
        	if (i == 0 || i == FIELD_HEIGHT-1){
        		printf("-");
        	}

            else if (j == 0 || j == FIELD_WIDTH-1) {
                // Draw side borders
                printf("|");
            } else if (i >= paddle1 && i < paddle1 + PADDLE_SIZE && j == 1) {
                // Draw paddle1
                printf("#");
            } else if (i >= paddle2 && i < paddle2 + PADDLE_SIZE && j == FIELD_WIDTH - 2) {
                // Draw paddle2
                printf("#");
            } else if (i == ballY && j == ballX) {
                // Draw ball
                printf("o");
            } else if (j == FIELD_WIDTH / 2) {
                // Draw center #
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("\n");

    // Draw scores
    printf("Player 1: %d\tPlayer 2: %d\n", player1Score, player2Score);
}

void moveBall() {
    ballX += directionX;
    ballY += directionY;

    // Check collision with paddles
    if ((ballX == 2 && ballY >= paddle1 && ballY < paddle1 + PADDLE_SIZE) ||
        (ballX == FIELD_WIDTH - 3 && ballY >= paddle2 && ballY < paddle2 + PADDLE_SIZE)) {
        directionX = -directionX;  // Reverse direction on paddle collision
    }

    // Check if the ball goes out of bounds
    if (ballX == 0 || ((ballY == 0 || ballY == FIELD_HEIGHT-1) && ballX <40)) {
            player2Score++;
            newRound();
            ballX = FIELD_WIDTH / 20-2;
            
        ballY = FIELD_HEIGHT / 2;
        
        }
    if (ballX == FIELD_WIDTH-1 || ((ballY == 0 || ballY == FIELD_HEIGHT-1) && ballX > 40)){
            player1Score++;
        newRound();  
        ballX = FIELD_WIDTH- 3;
        ballY = FIELD_HEIGHT / 2;
        
        }
    }



void movePaddle(int *paddle, char keyUp, char keyDown) {
    char key = getchar();
    if (key == '\n') {
        key = getchar();
    }

    if (key == keyUp && *paddle > 1) {
        (*paddle)--;
    } else if (key == keyDown && *paddle < FIELD_HEIGHT - PADDLE_SIZE - 1) {
        (*paddle)++;
    }
}

void game() {
    initializeGame();

    while (player1Score < 21 && player2Score < 21) {
        drawField();
        movePaddle(&paddle1, 'a', 'z');
        movePaddle(&paddle2, 'k', 'm');
        moveBall();

        
    }

    // Print the winner
    if (player1Score == 21) {
        printf("Player 1 wins!\n");
    } else {
        printf("Player 2 wins!\n");
    }
}

int main() {
    game();
    return 0;
}
