//2020 �˰��� �⸻ ������Ʈ - 12��
//2016316016 �պ��
//2016314015 ���翬
//3. 8*8 �׸��� �ٵ�

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

#define UP  72         // ���� �̵� (����Ű�� �̵�)
#define DOWN 80         // �Ʒ��� �̵� (����Ű�� �̵�)
#define LEFT 75         // ���� �̵� (����Ű�� �̵�)
#define RIGHT 77      // ������ �̵� (����Ű�� �̵�)
#define ENTER 32      // �ٵϵ� ���� (����)
#define RETURN 8        // �ٵϵ� ������ (�齺���̽�)

#define CLEAR 0         // �迭 �ʱ�ȭ
#define NONE 0
#define MAPSIZE 8      // �ٵ��� ũ�� ���� (8*8)
#define START 1
#define END 0
#define NO 0
#define player1 1      // ����� 1
#define player2 2      // ����� 2
#define PLAY 1         // �ٵ� ������ ��
#define OK 1
#define YES 1
#define TRUE 1
#define FALSE 0
#define OK_COUNT 4

int map[MAPSIZE][MAPSIZE];                  // ��¿� Map
int checkHouse[MAPSIZE][MAPSIZE];           // ���� ��ġ�� �������� ���� �ִ��� �Ǵ��ϱ� ���� Map
int x, y = 3;
int displayX = 0, displayLineY = 10, displayY = 12;   // Ŀ�� ���
char mapGrid[] = "������������������";            // �ٵ��� �׸���

int countReset1 = 0;                     // for player 1) ���� ���� ���� ġ�� �� ����� ���� count ��
int countReset2 = 0;                     // for player 2) ���� ���� ���� ġ�� �� ����� ���� count ��
int count_return = 0;                     //�� ������ ������ Ȯ���ϴ� ����
int totalCount = 0;                      // ���ݱ��� ���� �ٵϵ��� ����

int STARTFLAG = 0;                        // �ٵ� �� ã�� loop �ݺ� ����
int ret_count1 = 0;                       // player1 �� �� ������
int ret_count2 = 0;                       // player2 �� �� ������
int play_count = 0;


void ClearStones();                     // �ٵϵ� �迭 �ʱ�ȭ �Լ�
void ClearMap();                        // �ٵ��� �ʱ�ȭ �Լ�

void InputSelect(int player);                  // ���� �� �ٵϵ� ����
void ShowCheckerBoard();                        // �ٵ��� ��Ȳ ��� �Լ�
void ShowCursorPos(int x, int y);                  // �ٵ��� �迭�� ���̴� ���� ��ġ�� Ŀ���� ���� �ִ� �Լ�

int DeleteCheck();                           // ���� �ٵϵ� ������ ���� �ִ��� ���θ� count�� ���� Ȯ���ϴ� �Լ�
int DecisionFlag(int x, int y);               // ���� ��ġ�� ��ȿ���� �Ǵ��� �� ���
void RemoveStone(int x, int y, int player_number);   // �ٵϵ��� �������� ó��
void CheckMyStonePos(int x, int y, int player_number);   // �ٵϵ��� ���� ��� ���� ��ġ�� ���� ���� �����ϴ� ��ġ���� Ȯ��
int CheckPlayerHousePos(int x, int y, int player_number);   // ���� �δ� ��ġ�� ���� ������ Ȯ��
int FindHouse(int x, int y, int player_number);
int Find(int player_number);
int GameStatus();                           // ���� ���� ���¸� Ȯ��, ������ ��� ���������� �Ǵ�


void ClearStones() {               // �ٵϵ� �� �迭 �ʱ�ȭ �Լ�

    int i, j;

    for (i = 0; i < MAPSIZE; i++) {
        for (j = 0; j < MAPSIZE; j++) {
            checkHouse[i][j] = CLEAR;      // checkHouse �ʱ�ȭ
        }
    }
}

void ClearMap() {      // �ٵ��� �ʱ�ȭ �Լ�

    int x, y;

    for (y = 0; y < MAPSIZE; y++) {
        for (x = 0; x < MAPSIZE; x++) {
            map[y][x] = CLEAR;
        }
    }
}

int DecisionFlag(int x, int y) {
    if (x < 0 || x >= MAPSIZE || y < 0 || y >= MAPSIZE)   // ���� ��ġ�� ��� ����� Flag �Ǵ�
        return TRUE;

    if (checkHouse[y][x] == OK)               // checkHouse�� 1�� ���
        return TRUE;

    return FALSE;
}

int DeleteCheck(int count) {
    return count == OK_COUNT;
}

int CheckPlayerHousePos(int x, int y, int player_number) { // ���� �δ� ���� ������ ������ ���θ� �� ���� �Ǵ�

    int result;
    int count;

    if (x < 0 || x >= MAPSIZE || y < 0 || y >= MAPSIZE)    // ���� ��ġ�� ��� ���� ������ �� ��

        return OK;

    if (map[y][x] == player_number)            // �̹� �ڽ��� ���� ��ġ�� �������� �� ��
        return OK;

    if (map[y][x] == NONE)                     // �ٵϵ��� ���� ���� �������� �ϴ� ���
        return NO;

    count = 0;
    result = NO;
    checkHouse[y][x] = OK;

    if (DecisionFlag(x, y - 1) == FALSE) {     // y - 1�� ���� ���� �ִ°�

        if (CheckPlayerHousePos(x, y - 1, player_number)) {   // � �÷��̾��� ���� �׿� �ִ��� Ȯ�� --> ���

            count = count + 1;

        }
    }
    else { count = count + 1; }

    if (DecisionFlag(x - 1, y) == FALSE) {          // x - 1�� ���� ���� �ִ°�

        if (CheckPlayerHousePos(x - 1, y, player_number)) {     // � �÷��̾��� ���� �׿� �ִ��� Ȯ�� --> ���
            count = count + 1;
        }
    }
    else { count = count + 1; }

    if (DecisionFlag(x + 1, y) == FALSE) {

        if (CheckPlayerHousePos(x + 1, y, player_number)) { count = count + 1; }
    }
    else { count = count + 1; }

    if (DecisionFlag(x, y + 1) == FALSE) {
        if (CheckPlayerHousePos(x, y + 1, player_number)) { count = count + 1; }
    }
    else { count = count + 1; }

    if (count == OK_COUNT) {            // ���� ��ġ�� ���� �ѷ� �׿����� or ���� �Ǵ� ��� �Ǵ�
        result = OK;
    }

    return result;

}

int FindHouse(int x, int y, int player_number) {

    int result;
    int count;

    // ���� ��ġ�� ��� ���� ������ �� ��
    if (x < 0 || x >= MAPSIZE || y < 0 || y >= MAPSIZE)  return OK;

    if (map[y][x] == player_number)  return OK;          // �̹� �ڽ��� ���� ��ġ�� �������� �� ��

    count = 0;
    result = NO;
    checkHouse[y][x] = OK;

    if (DecisionFlag(x, y - 1) == FALSE) {           // y - 1�� ���� ���� �ִ°�
        if (CheckPlayerHousePos(x, y - 1, player_number)) {      // � �÷��̾��� ���� �׿� �ִ��� Ȯ�� --> ���
            count = count + 1;
        }
    }
    else { count = count + 1; }

    if (DecisionFlag(x - 1, y) == FALSE) {           // x - 1�� ���� ���� �ִ°�

        if (CheckPlayerHousePos(x - 1, y, player_number)) {      // � �÷��̾��� ���� �׿� �ִ��� Ȯ�� --> ���
            count = count + 1;
        }
    }
    else { count = count + 1; }

    if (DecisionFlag(x + 1, y) == FALSE) {

        if (CheckPlayerHousePos(x + 1, y, player_number)) { count = count + 1; }
    }
    else { count = count + 1; }

    if (DecisionFlag(x, y + 1) == FALSE) {

        if (CheckPlayerHousePos(x, y + 1, player_number)) { count = count + 1; }
    }
    else { count = count + 1; }

    if (count == OK_COUNT) {           // ���� ��ġ�� ���� �ѷ� �׿��ְų�, ���� �Ǵ� ��� �Ǵ�
        result = OK;
    }
    return result;
}

void RemoveStone(int x, int y, int player_number) // ���� ���� ������ ���� ���� ���� �� --> ��ͷ� ����
{
    if (x < 0 || x >= MAPSIZE || y < 0 || y >= MAPSIZE) return;

    if (map[y][x] == player_number) return;

    if (map[y][x] == NONE) return;

    map[y][x] = CLEAR;

    if (player_number == player1) countReset2++;

    if (player_number == player2) countReset1++;

    if (x + 1 < MAPSIZE) RemoveStone(x + 1, y, player_number);

    if (x - 1 >= 0) RemoveStone(x - 1, y, player_number);

    if (y + 1 < MAPSIZE) RemoveStone(x, y + 1, player_number);

    if (y - 1 >= 0) RemoveStone(x, y - 1, player_number);
}

void InputSelect(int player) {            // ���� �ٵ��� �ΰ� �ִ� �÷��̾��� ��ǥ �̵�
    char check;
    int player_number;
    int loop = START;

    if (player == player1) { player_number = player2; }
    else { player_number = player1; }

    while (loop != END) {

        check = _getch();

        switch (check) {

        case UP:      // ���� �̵�

            y = y - 1;
            if (y < 0) y = y + 1;
            ShowCursorPos(x, y);
            break;

        case DOWN:      // �Ʒ��� �̵�

            y = y + 1;
            if (y >= MAPSIZE) y = y - 1;
            ShowCursorPos(x, y);
            break;

        case RIGHT:      // ������ �̵�

            x = x + 1;
            if (x >= MAPSIZE) x = x - 1;
            ShowCursorPos(x, y);
            break;

        case LEFT:      // ���� �̵�

            x = x - 1;
            if (x < 0) x = x + 1;
            ShowCursorPos(x, y);
            break;

        case RETURN:   // �� ������

            if (player_number == player1) {

                if (ret_count1 >= 2)
                    break;
                ret_count1++;
            }
            else if (player_number == player2) {
                if (ret_count2 >= 2)
                    break;
                ret_count2++;
            }

            ShowCursorPos(displayX, displayY);

            map[y][x] = CLEAR;
            play_count--;
            ShowCheckerBoard();

            if (player_number == player1) {
                printf("\n\n\n\n\n\n��(�浹) �÷��̾ �� �����Դϴ�.");
            }
            else {
                printf("\n\n\n\n\n\n��(�鵹) �÷��̾ �� �����Դϴ�.");
            }

            ShowCursorPos(x, y);
            InputSelect(player_number);

            if (player_number == player1)
                player_number = player2;
            else
                player_number = player1;

            ShowCheckerBoard();


            if (player == player1) {

                ShowCursorPos(displayX, displayY);
                printf("\n\n\n\n\n\n��(�浹) �÷��̾ �� �����Դϴ�.");

            }
            else {

                ShowCursorPos(displayX, displayY);
                printf("\n\n\n\n\n\n��(�鵹) �÷��̾ �� �����Դϴ�.");

            }

            GameStatus();
            ShowCursorPos(x, y);
            InputSelect(player_number);
            loop = END;

        case ENTER:      // �ٵϵ��� ������ ��

            if (play_count == 0 && !(y == 0 || y == 7 || x == 0 || x == 7) && player == player1) {  // �����ڸ����� ���� �� �ְ� ó��
                STARTFLAG = 1;
                loop = END;
                break;
            }

            if (map[y][x] != NONE) break;

            map[y][x] = player;

            CheckMyStonePos(x, y, player);
            ClearStones();

            if (CheckPlayerHousePos(x, y, player_number) == YES) // �ش� ��ġ�� ���� ������ ���, �� �� ������ YES ��� --> �ξ��� ���� ��ȿȭ
                map[y][x] = CLEAR;
            else
                loop = END;

            play_count++;
        }
    }
}

// �ٵϵ��� �������� ��� �� �ٵϵ��� ���� ���� ��� �����ϰ� ���� ���� ��츦 ����ؼ� �˻��ϱ� ���� ����� �˰���
void CheckMyStonePos(int x, int y, int player_number) {

    ClearStones();      // �ξ��� �ٵ��� �ʱ�ȭ
    if (CheckPlayerHousePos(x + 1, y, player_number) == YES) RemoveStone(x + 1, y, player_number);

    ClearStones();
    if (CheckPlayerHousePos(x - 1, y, player_number) == YES) RemoveStone(x - 1, y, player_number);

    ClearStones();
    if (CheckPlayerHousePos(x, y + 1, player_number) == YES) RemoveStone(x, y + 1, player_number);

    ClearStones();
    if (CheckPlayerHousePos(x, y - 1, player_number) == YES) RemoveStone(x, y - 1, player_number);
}


int GameStatus() {      // ���� ������ ���� ���¸� �˷��ִ� �Լ�

    int i, j;
    int player1_do = 0;
    int player2_do = 0;
    totalCount = 0;   // ���� �� �� ����

    for (i = 0; i < MAPSIZE; i++)
        for (j = 0; j < MAPSIZE; j++)
            if (map[i][j] != CLEAR)
                totalCount++;      // �� ������ ���� ���� 1�� ����

    ShowCursorPos(displayX, displayY + 3);

    printf("\n\n\n\n\n�ٵϵ��� �� �� ����: %d\n1�� �÷��̾� : %d\n2�� �÷��̾� : %d\n\n���� ���� Ƚ��(�ִ� 2ȸ���� �����մϴ�)\n1�� �÷��̾� : %d\n2�� �÷��̾� : %d\n", totalCount, countReset1, countReset2, ret_count1, ret_count2);  // ���� �� ����, �÷��̾�1�� �� ��, �÷��̾�2�� �� �� ���

    // 2���� �� ������ ��
    if (ret_count1 >= 2)
        printf("��(�浹)�� �� �̻� ���� �� �����ϴ�.\n");
    if (ret_count2 >= 2)
        printf("��(�鵹)�� �� �̻� ���� �� �����ϴ�.\n");

    if ((totalCount + countReset1 + countReset2) == MAPSIZE * MAPSIZE) {
        player1_do = Find(player1);
        player2_do = Find(player2);

        ShowCursorPos(displayX, displayY);

        if (countReset1 < countReset2)
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n�����մϴ�! \n��(�鵹)�� �¸��Ͽ����ϴ�!!\n");
        else if (countReset1 > countReset2)
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n�����մϴ�! \n��(�浹)�� �¸��Ͽ����ϴ�!!\n");
        else
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n���ºγ׿�!\n");

        printf("1�� �÷��̾��� �� ���� : %d | 2�� �÷��̾��� �� ���� %d \n", player1_do + 2, player2_do);
        return 1;
    }
    return 0;

}

void ShowCheckerBoard() {                  // ȭ�� ���

    int x, y, n;
    char calculate[3];
    system("cls");


    for (y = 0; y < MAPSIZE; y++) {
        for (x = 0; x < MAPSIZE; x++) {
            if (map[y][x] == player1) {     // �÷��̾�1 - �浹
                printf("��");
            }
            else if (map[y][x] == player2) {// �÷��̾�2 - �鵹
                printf("��");
            }
            else if (map[y][x] == NONE) { // �ٵ��� ���
                n = (x + 5) / 6 + (y + 5) / 6 * 3;
                calculate[0] = mapGrid[n * 2];
                calculate[1] = mapGrid[n * 2 + 1];
                calculate[2] = 0;               // �ٵ����� 8x8 �� ����� ���� ��� ����

                printf("%s ", calculate);         // �ٵ��� ���
            }
        }
        printf("\n");
    }

    ShowCursorPos(displayX, displayLineY);
    printf("�ٵ��� �����մϴ�!\n");
    printf("Ű������ ����Ű�� ��ġ �̵��� �����մϴ�.\n\n");
    printf("*********** ��� ��� ***********\n�ٵϵ� ���� : spacebar Ű�� �Է����ּ���!\n�� ������ : backspace Ű�� �Է����ּ���!\n");
}

int Find(int player_number) {

    int i, j;
    int temp = 0;
    int count = 0;

    for (i = 0; i < MAPSIZE; i++) {
        for (j = 0; j < MAPSIZE; j++) {
            if (map[i][j] == 0) {
                temp = StoneFind(i, j, player_number);
                count += temp;
            }
        }
    }

    return count;
}

int StoneFind(int x, int y, int player_number)
{
    int player_domain_count = 0;

    if (FindHouse(x + 1, y, player_number) == YES) {
        ClearStones();

        if (FindHouse(x - 1, y, player_number) == YES) {
            ClearStones();

            if (FindHouse(x, y + 1, player_number) == YES) {
                ClearStones();

                if (FindHouse(x, y - 1, player_number) == YES) {
                    player_domain_count++;
                }
            }
        }
    }
    return player_domain_count;
}

void ShowCursorPos(int x, int y) {
    COORD Pos = { x * 2 , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void main() {

    int player = player1, GamePlayFlag = PLAY;
    char replayGo;
    ClearMap();
    ClearStones();
    ShowCheckerBoard();

   
    while (GamePlayFlag != END) {

        ShowCursorPos(displayX, displayY);

        if (STARTFLAG == 1) {
            printf("\n\n\n\nù ���� �����ڸ����� ���� �� �ֽ��ϴ�.");
            STARTFLAG = 0;
            player = player1;
        }

        ShowCursorPos(displayX, displayY);

        if (player == player1) {
            printf("\n\n\n\n\n\n��(�浹) �÷��̾ �� �����Դϴ�.");
        }
        else {
            printf("\n\n\n\n\n\n��(�鵹) �÷��̾ �� �����Դϴ�.");
        }


        ShowCursorPos(x, y);
        InputSelect(player);
        ShowCheckerBoard();

        if (player == player1) {
            player = player2;
        }
        else {
            player = player1;
        }

        if (GameStatus() == OK) {
            GamePlayFlag = END;
        }
    }
}