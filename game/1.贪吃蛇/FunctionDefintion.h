/**--------------------------------------------------------------------------*
**                         FUNCTION DEFINITION                              *
**--------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*
Name:		    Menu
Discribe:		menu interface
Return:		diff , QUIT
**--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
**                         Include Files                                     *
**-------------------------------------------------------------------- ------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include"conio.h"
#include "pcc32.h"

/**--------------------------------------------------------------------------*
**                         Macro Definition                                 *
**--------------------------------------------------------------------------*/
#define uchar unsigned char
#define uint unsigned int

#define SNAKE_MIN_LEN 5
#define SNAKE_MAX_LEN 600
#define WIDTH 32
#define HEIGHT 24
#define S_TIME 350

#define QUIT 0
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#define OVER 2

#define CALTIME(x) (S_TIME-(x)*22)

#ifndef FUNCTIONDEFINTION_H_INCLUDED
#define FUNCTIONDEFINTION_H_INCLUDED

/**-------------------------------------------------------------------------*
**                         Type And Struct                                  *
**--------------------------------------------------------------------------*/
enum SNAKE_DIR
{
    U,
    D,
    L,
    R
};//snake direction

struct COORDINATE
{
    uchar x;
    uchar y;
};

struct SNAKE
{
    uchar length;
    struct COORDINATE body[SNAKE_MAX_LEN];
    enum SNAKE_DIR direction;
};

/**--------------------------------------------------------------------------*
**                         EXTERNAL DECLARE                                 *
**--------------------------------------------------------------------------*/
struct CONSOLE_FONT
{
    DWORD index;
    COORD dim;
};

typedef BOOL (WINAPI *PROCSETCONSOLEFONT)(HANDLE, DWORD);

PROCSETCONSOLEFONT SetConsoleFont;

/**--------------------------------------------------------------------------*
**                         STATIC DEFINITION                                *
**--------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*
**                         GLOBAL DEFINITION                                *
**--------------------------------------------------------------------------*/
struct COORDINATE food;
struct COORDINATE Cursor[300];
uchar pass=0;
uint model_pass=0;
uchar diff=1;
uchar model=0;
uchar speed=1;
uint model_challenge_pass=0;
uint model_Tunnel_pass=0;
uint NumC=0;

/*---------------------------------------------------------------------------*/
/*                          LOCAL FUNCTION DECLARE                           */
/*---------------------------------------------------------------------------*/
uchar   Menu();//display menu
uchar   SetDifficulty(uchar *diff);//set Speed
uchar   SetLevel(uchar *pass);//set Pass Level
uchar   SetPassModel(uchar *diff);//set Pass Model
uchar   SetCrossModel(uchar *diff);//set Cross Model
uchar   SetCrossModel2(uchar *pass);//set Cross Model
uchar   SetChallengeModel(uchar *diff);//set Challenge Model
uchar   SetTunnelModel(uchar *diff);//set Tunnel Model
uchar   Instruction();//GAME INSTRUCTION
uchar   InitFood0 (struct SNAKE *snake);
uchar   InitFood1 (struct SNAKE *snake);
uchar   InitFood2 (struct SNAKE *snake);
uchar   InitFood_Challenge (struct SNAKE *snake);
uchar   InSnake (struct SNAKE *snake, uchar x, uchar y);
uchar   MoveSnake(struct SNAKE *snake);
uchar   MoveSnake2(struct SNAKE *snake);
uchar   MoveSnakeTunnel(struct SNAKE *snake);
uchar   IsOver0(struct SNAKE *snake, uchar x, uchar y);
uchar   IsOver1(struct SNAKE *snake, uchar x, uchar y);
uchar   IsOver2(struct SNAKE *snake, uchar x, uchar y);
uchar   IsOver3(struct SNAKE *snake, uchar x, uchar y);
uchar   IsOver4(struct SNAKE *snake, uchar x, uchar y);
uchar   IsOverTunnel(uchar x, uchar y);
uchar   ShowOver(uint *score,uint *model_pass,uint *model_challenge_pass,uint *model_Tunnel_pass);
uchar   ShowWin(uint *model_pass,uint *model_challenge_pass,uint *model_Tunnel_pass);
void	DrawWall_0();
void	DrawWall_1();
void	DrawWall_2();
void	DrawWall_3();
void	DrawWall_4();
void	DrawWall_5();
void    DrawWall_challenge();
void    DrawTunnel();
void    Wall_Start();
void	DrawSnake(struct SNAKE *snake);
void    DrawSnakeTunnel(struct SNAKE *snake);
void	DrawFood();
void    ShowPause ();//show pause interface
void    InitSnake(struct SNAKE *snake);//init snake's length
void    InitSnakeTunnel(struct SNAKE *snake);

/**------------------------------------------------------------------------**/
/**------------------------------------------------------------------------**/
uchar Menu()//�����ǲ˵�ѡ��Ľ���
{
    uchar choose = 6, ischoose = 1;
    uchar i;
    //display menu interface
    system("cls");//clear screen��������
    printf("\n");
    setTextColor(WHITE);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��         ___________My Snake Game____________         ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                             ����     ��\n");
    printf("   ��         Classical Model(Easy)             ��    ��   ��\n");
    printf("   ��         Pass Model��Barrier��            ��    ��    ��\n");
    printf("   ��         Cross Model��No Wall��           ��          ��\n");
    printf("   ��         Challenge Model��Hard��            ��        ��\n");
    printf("   ��         Tunnel Model��Transfer��             ��      ��\n");
    printf("   ��         Quit Game ((�s�n�t)b)       ����  ��  ��     ��\n");
    printf("   ��         Chinese Instruction        ��   �� ����      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��         Warning:Please select English input method.  ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(25,3);
    printf("My Snake Game\n");
    setTextColor(YELLOW);
    gotoTextPos(50,5);
    printf("����\n");
    gotoTextPos(48,6);
    printf("��    ��\n");
    gotoTextPos(47,7);
    printf("��    ��\n");
    gotoTextPos(47,8);
    printf("��\n");
    gotoTextPos(49,9);
    printf("��\n");
    gotoTextPos(51,10);
    printf("��\n");
    gotoTextPos(42,11);
    printf("����  ��  ��\n");
    gotoTextPos(41,12);
    printf("��   �� ����\n");
    setTextColor(RED_ORANGE);
    gotoTextPos(13,15);
    printf(" Warning:Please select English input method.\n");
    gotoTextPos(13,17);
    setTextColor(MEDIUM_BLUE);
    printf(" Please press UP or DOWN to choose Menu.\n");
    gotoTextPos(13,18);
    printf(" Press Enter to Confirm.");
    setTextColor(LIGHT_PURPLE);
    gotoTextPos(13,19);
    printf(" Author:SiQi_Wang  2016/08/15\n");
    setTextColor(DARK_GREEN);
    gotoTextPos(29,20);
    printf("                Version:  6.1\n");
    setTextColor(TEAL);
    gotoTextPos(14,6);
    printf("Classical Model(Easy)\n");
    gotoTextPos(14,7);
    printf("Pass Model��Barrier��\n");
    gotoTextPos(14,8);
    printf("Cross Model��No Wall��\n");
    gotoTextPos(14,9);
    printf("Challenge Model��Hard��\n");
    gotoTextPos(14,10);
    printf("Tunnel Model��Transfer��\n");
    gotoTextPos(14,11);
    printf("Quit Game ((�s�n�t)b)\n");
    gotoTextPos(14,12);
    printf("Chinese Instruction\n");



    setTextColor(YELLOW);
    do
    {
        for(i=6; i<=12; i++)
        {
            gotoTextPos(10,i);//����Ƶ�(2,i)��
            if(i==choose)
                printf("��");//������ʾ����ѡ�������
            else
                printf(" ");
        }
        //get keydown
        switch(jkGetKey())
        {
        //��ȡ���̰����������ֻ��ͨ��ɨ�����ȡ
        case JK_UP:
            if (choose>6)
                choose --;
            break;
        case JK_DOWN:
            if (choose<12)
                choose ++;
            break;
        case JK_ENTER:
            ischoose = 0;
            break;
        default:
            ;
        }
    }
    while (ischoose);
    switch (choose)
    {
    case 6:
        SetDifficulty(&diff);
        break;
    case 7:
        SetPassModel(&speed);
        break;
    case 8:
        SetCrossModel(&diff);
        break;
    case 9:
        SetChallengeModel(&speed);
        break;
    case 10:
        SetTunnelModel(&speed);
        break;
    case 11:
        return QUIT;
        break;
    case 12:
        Instruction();
        break;
    }
}


/**--------------------------------------------------------------------------*
Name:		    SetDifficulty
Discribe:		choose difficulty interface
Return:		    0
**--------------------------------------------------------------------------*/
uchar SetDifficulty(uchar *diff)//��ʾѡ���ѶȵĽ���
{
    model=0;
    //	assert (NULL != diff);
    system("cls");//to show set difficulty level interface
    printf("\n");
    setTextColor(WHITE);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��         ___________My Snake Game____________         ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                             ����     ��\n");
    printf("   ��         Instruction:This interface        ��    ��   ��\n");
    printf("   ��         supply player to set Snake       ��    ��    ��\n");
    printf("   ��         moving speed which is from       ��          ��\n");
    printf("   ��         1 to 15 which make different       ��        ��\n");
    printf("   ��         difficulty.                          ��      ��\n");
    printf("   ��                                     ����  ��  ��     ��\n");
    printf("   ��                                    ��   �� ����      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(25,3);
    printf("My Snake Game\n");
    setTextColor(YELLOW);
    gotoTextPos(50,5);
    printf("����\n");
    gotoTextPos(48,6);
    printf("��    ��\n");
    gotoTextPos(47,7);
    printf("��    ��\n");
    gotoTextPos(47,8);
    printf("��\n");
    gotoTextPos(49,9);
    printf("��\n");
    gotoTextPos(51,10);
    printf("��\n");
    gotoTextPos(42,11);
    printf("����  ��  ��\n");
    gotoTextPos(41,12);
    printf("��   �� ����\n");
    setTextColor(WHITE);
    gotoTextPos(10,HEIGHT/2+1); //��14��
    setTextColor(DARK_GREEN);
    printf("                        ��\n\n");//��ʾ������
    gotoTextPos(34,15);
    printf("��\n");//��ʾ������
    setTextColor(RED_ORANGE);
    gotoTextPos(14,17);
    printf("Please press UP or DOWN to choose speed level\n");
    gotoTextPos(14,19);
    printf("Press Enter to Confirm");
    gotoTextPos(14,18);
    printf("Press ESC to return the last interface");
    setTextColor(DARK_GREEN);
    gotoTextPos(29,20);
    printf("                Version:  6.1\n");
    setTextColor(TEAL);
    gotoTextPos(14,6);
    printf("Instruction:This interface\n");
    gotoTextPos(14,7);
    printf("supply player to set Snake\n");
    gotoTextPos(14,8);
    printf("moving speed which is from\n");
    gotoTextPos(14,9);
    printf("1 to 15 which make different\n");
    gotoTextPos(14,10);
    printf("difficulty.\n");


    while (1)
    {
        gotoTextPos(14,HEIGHT/2+2);
        setTextColor(LIGHT_PURPLE);
        printf("Speed level:");
        setTextColor(YELLOW);
        printf("        %2d",*diff);

        switch(jkGetKey())
        {
        //��ȡ������Ϣ��ѡ���Ѷ�
        case JK_UP:
            if (*diff == 1)
            {
                (*diff) =15;
                break;
            }
            if (*diff > 1)
                (*diff) --;
            break;
        case JK_DOWN:
            if (*diff == 15)
            {
                (*diff) =1;
                break;
            }
            if (*diff < 15)
                (*diff) ++;
            break;
        case JK_ESC:
            return Menu();
            break;
        case JK_ENTER:
            return SetLevel(&pass);
        default:
            ;
        }
    }
}


/**--------------------------------------------------------------------------*
Name:		    SetLevel
Discribe:		choose pass interface
Return:		    0
**--------------------------------------------------------------------------*/
uchar SetLevel(uchar *pass)//��ʾѡ���ѶȵĽ���
{
    model=0;
    //	assert (NULL != diff);
    system("cls");//to show set difficulty level interface
    //	gotoTextPos(10,HEIGHT/2-3); //9
    printf("\n");
    setTextColor(WHITE);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��         ___________My Snake Game____________         ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                             ����     ��\n");
    printf("   ��         Instruction:This interface        ��    ��   ��\n");
    printf("   ��         supply player to set game        ��    ��    ��\n");
    printf("   ��         pass which is from 0 to 5        ��          ��\n");
    printf("   ��         which make different level.        ��        ��\n");
    printf("   ��                                              ��      ��\n");
    printf("   ��                                     ����  ��  ��     ��\n");
    printf("   ��                                    ��   �� ����      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(25,3);
    printf("My Snake Game\n");
    setTextColor(YELLOW);
    gotoTextPos(50,5);
    printf("����\n");
    gotoTextPos(48,6);
    printf("��    ��\n");
    gotoTextPos(47,7);
    printf("��    ��\n");
    gotoTextPos(47,8);
    printf("��\n");
    gotoTextPos(49,9);
    printf("��\n");
    gotoTextPos(51,10);
    printf("��\n");
    gotoTextPos(42,11);
    printf("����  ��  ��\n");
    gotoTextPos(41,12);
    printf("��   �� ����\n");
    setTextColor(WHITE);
    gotoTextPos(10,HEIGHT/2+1); //��14��
    setTextColor(DARK_GREEN);
    printf("                      ��\n\n");//��ʾ������
    gotoTextPos(32,15);
    printf("��\n");//��ʾ������
    setTextColor(RED_ORANGE);
    gotoTextPos(14,17);
    printf("Please press UP or DOWN to choose speed level\n");
    gotoTextPos(14,19);
    printf("Press Enter to Confirm");
    gotoTextPos(14,18);
    printf("Press ESC to return the last interface");
    setTextColor(DARK_GREEN);
    gotoTextPos(29,20);
    printf("                Version:  6.1\n");
    setTextColor(TEAL);
    gotoTextPos(14,6);
    printf("Instruction:This interface\n");
    gotoTextPos(14,7);
    printf("supply player to set game\n");
    gotoTextPos(14,8);
    printf("pass which is from 0 to 5\n");
    gotoTextPos(14,9);
    printf("which make different level.\n");

    while (1)
    {
        gotoTextPos(14,HEIGHT/2+2);
        setTextColor(LIGHT_PURPLE);
        printf("Pass level:");
        setTextColor(YELLOW);
        printf("       %2d",*pass);

        switch(jkGetKey())
        {
        //��ȡ������Ϣ��ѡ���Ѷ�
        case JK_UP:
            if (*pass == 0)
            {
                (*pass) = 5 ;
                break;
            }
            if (*pass > 0)
                (*pass) --;
            break;
        case JK_DOWN:
            if (*pass == 5)
            {
                (*pass) = 0;
                break;
            }
            if (*pass < 5)
                (*pass) ++;
            break;
        case JK_ESC:
            return SetDifficulty(&diff);
            break;
        case JK_ENTER:
            return 1;
        default:
            ;
        }
    }
}


/**--------------------------------------------------------------------------*
Name:		    SetPassModel
Discribe:		choose PassModel interface
Return:		    0
**--------------------------------------------------------------------------*/
uchar SetPassModel(uchar *speed)//��ʾѡ���ѶȵĽ���
{
    //	assert (NULL != diff);
    system("cls");//to show set difficulty level interface
    //	gotoTextPos(10,HEIGHT/2-3); //9
    model=1;
    printf("\n");
    setTextColor(WHITE);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��         ___________My Snake Game____________         ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                             ����     ��\n");
    printf("   ��         Instruction:This model allows     ��    ��   ��\n");
    printf("   ��         player to play Snake Game in     ��    ��    ��\n");
    printf("   ��         different level in an orderly    ��          ��\n");
    printf("   ��         manner that Snake's Speed is       ��        ��\n");
    printf("   ��         able to set from 1 to 12 level.      ��      ��\n");
    printf("   ��                                     ����  ��  ��     ��\n");
    printf("   ��                                    ��   �� ����      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(25,3);
    printf("My Snake Game\n");
    setTextColor(YELLOW);
    gotoTextPos(50,5);
    printf("����\n");
    gotoTextPos(48,6);
    printf("��    ��\n");
    gotoTextPos(47,7);
    printf("��    ��\n");
    gotoTextPos(47,8);
    printf("��\n");
    gotoTextPos(49,9);
    printf("��\n");
    gotoTextPos(51,10);
    printf("��\n");
    gotoTextPos(42,11);
    printf("����  ��  ��\n");
    gotoTextPos(41,12);
    printf("��   �� ����\n");
    setTextColor(WHITE);
    gotoTextPos(10,HEIGHT/2+1); //��14��
    setTextColor(DARK_GREEN);
    printf("                        ��\n\n");//��ʾ������
    gotoTextPos(34,15);
    printf("��\n");//��ʾ������
    setTextColor(RED_ORANGE);
    gotoTextPos(14,17);
    printf("Please press UP or DOWN to choose speed level\n");
    gotoTextPos(14,19);
    printf("Press Enter to Confirm");
    gotoTextPos(14,18);
    printf("Press ESC to return the last interface");
    setTextColor(DARK_GREEN);
    gotoTextPos(29,20);
    printf("                Version:  6.1\n");
    setTextColor(TEAL);
    gotoTextPos(14,6);
    printf("Instruction:This model allows\n");
    gotoTextPos(14,7);
    printf("player to play Snake Game in\n");
    gotoTextPos(14,8);
    printf("different level in an orderly\n");
    gotoTextPos(14,9);
    printf("manner that Snake's Speed is\n");
    gotoTextPos(14,10);
    printf("able to set from 1 to 12 level.\n");
    model=1;

    while (1)
    {
        gotoTextPos(14,HEIGHT/2+2);
        setTextColor(LIGHT_PURPLE);
        printf("Difficulty Speed:");
        setTextColor(YELLOW);
        printf("   %2d",*speed);

        switch(jkGetKey())
        {
        //��ȡ������Ϣ��ѡ���Ѷ�
        case JK_UP:
            if (*speed == 1)
            {
                (*speed) = 12;
                break;
            }
            if (*speed > 1)
                (*speed) --;
            break;
        case JK_DOWN:
            if (*speed == 12)
            {
                (*speed) = 1;
                break;
            }
            if (*speed < 12)
                (*speed) ++;
            break;
        case JK_ESC:
            model=0;
            speed=1;
            return Menu();
            break;
        case JK_ENTER:
            return 1;
            break;
        default:
            ;
        }
    }
}


/**--------------------------------------------------------------------------*
Name:		    SetCrossModel
Discribe:		choose CrossModel interface
Return:		    0
**--------------------------------------------------------------------------*/
uchar SetCrossModel(uchar *diff)//��ʾѡ���ѶȵĽ���
{
    //	assert (NULL != diff);
    system("cls");//to show set difficulty level interface
    model=2;
    printf("\n");
    setTextColor(WHITE);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��         ___________My Snake Game____________         ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                             ����     ��\n");
    printf("   ��         Instruction:This model allows     ��    ��   ��\n");
    printf("   ��         player to play Snake Game in     ��    ��    ��\n");
    printf("   ��         different level that Snake's     ��          ��\n");
    printf("   ��         Speed is able to set from 1 to     ��        ��\n");
    printf("   ��         15 level.                            ��      ��\n");
    printf("   ��                                     ����  ��  ��     ��\n");
    printf("   ��                                    ��   �� ����      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(25,3);
    printf("My Snake Game\n");
    setTextColor(YELLOW);
    gotoTextPos(50,5);
    printf("����\n");
    gotoTextPos(48,6);
    printf("��    ��\n");
    gotoTextPos(47,7);
    printf("��    ��\n");
    gotoTextPos(47,8);
    printf("��\n");
    gotoTextPos(49,9);
    printf("��\n");
    gotoTextPos(51,10);
    printf("��\n");
    gotoTextPos(42,11);
    printf("����  ��  ��\n");
    gotoTextPos(41,12);
    printf("��   �� ����\n");
    setTextColor(WHITE);
    gotoTextPos(10,HEIGHT/2+1); //��14��
    setTextColor(DARK_GREEN);
    printf("                        ��\n\n");//��ʾ������
    gotoTextPos(34,15);
    printf("��\n");//��ʾ������
    setTextColor(RED_ORANGE);
    gotoTextPos(14,17);
    printf("Please press UP or DOWN to choose speed level\n");
    gotoTextPos(14,19);
    printf("Press Enter to Confirm");
    gotoTextPos(14,18);
    printf("Press ESC to return the last interface");
    setTextColor(DARK_GREEN);
    gotoTextPos(29,20);
    printf("                Version:  6.1\n");
    setTextColor(TEAL);
    gotoTextPos(14,6);
    printf("Instruction:This model allows\n");
    gotoTextPos(14,7);
    printf("player to play Snake Game in\n");
    gotoTextPos(14,8);
    printf("different level that Snake's\n");
    gotoTextPos(14,9);
    printf("Speed is able to set from 1 to\n");
    gotoTextPos(14,10);
    printf("15 level.\n");
    model=2;

    while (1)
    {
        gotoTextPos(14,HEIGHT/2+2);
        setTextColor(LIGHT_PURPLE);
        printf("Difficulty Speed:");
        setTextColor(YELLOW);
        printf("   %2d",*diff);

        switch(jkGetKey())
        {
        //��ȡ������Ϣ��ѡ���Ѷ�
        case JK_UP:
            if (*diff == 1)
            {
                (*diff) = 15;
                break;
            }
            if (*diff > 1)
                (*diff) --;
            break;
        case JK_DOWN:
            if (*diff == 15)
            {
                (*diff) = 1;
                break;
            }
            if (*diff < 15)
                (*diff) ++;
            break;
        case JK_ESC:
            model=0;
            diff=1;
            return Menu();
            break;
        case JK_ENTER:
            return SetCrossModel2(&pass);
            break;
        default:
            ;
        }
    }
}


/**--------------------------------------------------------------------------*
Name:		    SetCrossModel2
Discribe:		choose pass interface
Return:		    0
**--------------------------------------------------------------------------*/
uchar SetCrossModel2(uchar *pass)//��ʾѡ���ѶȵĽ���
{
    model=2;
    //	assert (NULL != diff);
    system("cls");//to show set difficulty level interface
    printf("\n");
    setTextColor(WHITE);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��         ___________My Snake Game____________         ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                             ����     ��\n");
    printf("   ��         Instruction:This model allows     ��    ��   ��\n");
    printf("   ��         player to play Snake Game in     ��    ��    ��\n");
    printf("   ��         different level that Snake's     ��          ��\n");
    printf("   ��         Speed is able to set from 1 to     ��        ��\n");
    printf("   ��         15 level.                            ��      ��\n");
    printf("   ��                                     ����  ��  ��     ��\n");
    printf("   ��                                    ��   �� ����      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(25,3);
    printf("My Snake Game\n");
    setTextColor(YELLOW);
    gotoTextPos(50,5);
    printf("����\n");
    gotoTextPos(48,6);
    printf("��    ��\n");
    gotoTextPos(47,7);
    printf("��    ��\n");
    gotoTextPos(47,8);
    printf("��\n");
    gotoTextPos(49,9);
    printf("��\n");
    gotoTextPos(51,10);
    printf("��\n");
    gotoTextPos(42,11);
    printf("����  ��  ��\n");
    gotoTextPos(41,12);
    printf("��   �� ����\n");
    setTextColor(WHITE);
    gotoTextPos(10,HEIGHT/2+1); //��14��
    setTextColor(DARK_GREEN);
    printf("                      ��\n\n");//��ʾ������
    gotoTextPos(32,15);
    printf("��\n");//��ʾ������
    setTextColor(RED_ORANGE);
    gotoTextPos(14,17);
    printf("Please press UP or DOWN to choose speed level\n");
    gotoTextPos(14,19);
    printf("Press Enter to Confirm");
    gotoTextPos(14,18);
    printf("Press ESC to return the last interface");
    setTextColor(DARK_GREEN);
    gotoTextPos(29,20);
    printf("                Version:  6.1\n");
    setTextColor(TEAL);
    gotoTextPos(14,6);
    printf("Instruction:This model allows\n");
    gotoTextPos(14,7);
    printf("player to play Snake Game in\n");
    gotoTextPos(14,8);
    printf("different level that Snake's\n");
    gotoTextPos(14,9);
    printf("Speed is able to set from 1 to\n");
    gotoTextPos(14,10);
    printf("15 level.\n");

    while (1)
    {
        gotoTextPos(14,HEIGHT/2+2);
        setTextColor(LIGHT_PURPLE);
        printf("Pass level:");
        setTextColor(YELLOW);
        printf("       %2d",*pass);

        switch(jkGetKey())
        {
        //��ȡ������Ϣ��ѡ���Ѷ�
        case JK_UP:
            if (*pass == 0)
            {
                (*pass) = 5 ;
                break;
            }
            if (*pass > 0)
                (*pass) --;
            break;
        case JK_DOWN:
            if (*pass == 5)
            {
                (*pass) = 0;
                break;
            }
            if (*pass < 5)
                (*pass) ++;
            break;
        case JK_ESC:
            return SetCrossModel(&diff);
            break;
        case JK_ENTER:
            return 1;
        default:
            ;
        }
    }
}



/**--------------------------------------------------------------------------*
Name:		    SetChallengeModel
Discribe:		choose ChallengeModel interface
Return:		    0
**--------------------------------------------------------------------------*/
uchar SetChallengeModel(uchar *speed)//��ʾѡ���ѶȵĽ���
{
    //	assert (NULL != diff);
    system("cls");//to show set difficulty level interface
    //	gotoTextPos(10,HEIGHT/2-3); //9
    model=3;
    printf("\n");
    setTextColor(WHITE);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��         ___________My Snake Game____________         ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                             ����     ��\n");
    printf("   ��         Instruction:This model allows     ��    ��   ��\n");
    printf("   ��         player to play Snake Game in     ��    ��    ��\n");
    printf("   ��         different level in an orderly    ��          ��\n");
    printf("   ��         manner that Snake's Speed is       ��        ��\n");
    printf("   ��         able to set from 1 to 12 level.      ��      ��\n");
    printf("   ��                                     ����  ��  ��     ��\n");
    printf("   ��                                    ��   �� ����      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(25,3);
    printf("My Snake Game\n");
    setTextColor(YELLOW);
    gotoTextPos(50,5);
    printf("����\n");
    gotoTextPos(48,6);
    printf("��    ��\n");
    gotoTextPos(47,7);
    printf("��    ��\n");
    gotoTextPos(47,8);
    printf("��\n");
    gotoTextPos(49,9);
    printf("��\n");
    gotoTextPos(51,10);
    printf("��\n");
    gotoTextPos(42,11);
    printf("����  ��  ��\n");
    gotoTextPos(41,12);
    printf("��   �� ����\n");
    setTextColor(WHITE);
    gotoTextPos(10,HEIGHT/2+1); //��14��
    setTextColor(DARK_GREEN);
    printf("                        ��\n\n");//��ʾ������
    gotoTextPos(34,15);
    printf("��\n");//��ʾ������
    setTextColor(RED_ORANGE);
    gotoTextPos(14,17);
    printf("Please press UP or DOWN to choose speed level\n");
    gotoTextPos(14,19);
    printf("Press Enter to Confirm");
    gotoTextPos(14,18);
    printf("Press ESC to return the last interface");
    setTextColor(DARK_GREEN);
    gotoTextPos(29,20);
    printf("                Version:  6.1\n");
    setTextColor(TEAL);
    gotoTextPos(14,6);
    printf("Instruction:This model allows\n");
    gotoTextPos(14,7);
    printf("player to play Snake Game in\n");
    gotoTextPos(14,8);
    printf("different level in an orderly\n");
    gotoTextPos(14,9);
    printf("manner that Snake's Speed is\n");
    gotoTextPos(14,10);
    printf("able to set from 1 to 12 level.\n");

    while (1)
    {
        gotoTextPos(14,HEIGHT/2+2);
        setTextColor(LIGHT_PURPLE);
        printf("Difficulty Speed:");
        setTextColor(YELLOW);
        printf("   %2d",*speed);

        switch(jkGetKey())
        {
        //��ȡ������Ϣ��ѡ���Ѷ�
        case JK_UP:
            if (*speed == 1)
            {
                (*speed) = 12;
                break;
            }
            if (*speed > 1)
                (*speed) --;
            break;
        case JK_DOWN:
            if (*speed == 12)
            {
                (*speed) = 1;
                break;
            }
            if (*speed < 12)
                (*speed) ++;
            break;
        case JK_ESC:
            model=0;
            speed=1;
            return Menu();
            break;
        case JK_ENTER:
            return 1;
            break;
        default:
            ;
        }
    }
}


/**--------------------------------------------------------------------------*
Name:		    SetTunnelModel
Discribe:		choose ChallengeModel interface
Return:		    0
**--------------------------------------------------------------------------*/
uchar SetTunnelModel(uchar *speed)//��ʾѡ���ѶȵĽ���
{
    //	assert (NULL != diff);
    system("cls");//to show set difficulty level interface
    //	gotoTextPos(10,HEIGHT/2-3); //9
    model=4;
    printf("\n");
    setTextColor(WHITE);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��         ___________My Snake Game____________         ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                             ����     ��\n");
    printf("   ��         Instruction:This model allows     ��    ��   ��\n");
    printf("   ��         player to play Snake Game in     ��    ��    ��\n");
    printf("   ��         different level in an orderly    ��          ��\n");
    printf("   ��         manner that Snake's Speed is       ��        ��\n");
    printf("   ��         able to set from 1 to 12 level.      ��      ��\n");
    printf("   ��                                     ����  ��  ��     ��\n");
    printf("   ��                                    ��   �� ����      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(25,3);
    printf("My Snake Game\n");
    setTextColor(YELLOW);
    gotoTextPos(50,5);
    printf("����\n");
    gotoTextPos(48,6);
    printf("��    ��\n");
    gotoTextPos(47,7);
    printf("��    ��\n");
    gotoTextPos(47,8);
    printf("��\n");
    gotoTextPos(49,9);
    printf("��\n");
    gotoTextPos(51,10);
    printf("��\n");
    gotoTextPos(42,11);
    printf("����  ��  ��\n");
    gotoTextPos(41,12);
    printf("��   �� ����\n");
    setTextColor(WHITE);
    gotoTextPos(10,HEIGHT/2+1); //��14��
    setTextColor(DARK_GREEN);
    printf("                        ��\n\n");//��ʾ������
    gotoTextPos(34,15);
    printf("��\n");//��ʾ������
    setTextColor(RED_ORANGE);
    gotoTextPos(14,17);
    printf("Please press UP or DOWN to choose speed level\n");
    gotoTextPos(14,19);
    printf("Press Enter to Confirm");
    gotoTextPos(14,18);
    printf("Press ESC to return the last interface");
    setTextColor(DARK_GREEN);
    gotoTextPos(29,20);
    printf("                Version:  6.1\n");
    setTextColor(TEAL);
    gotoTextPos(14,6);
    printf("Instruction:This model allows\n");
    gotoTextPos(14,7);
    printf("player to play Snake Game in\n");
    gotoTextPos(14,8);
    printf("different level in an orderly\n");
    gotoTextPos(14,9);
    printf("manner that Snake's Speed is\n");
    gotoTextPos(14,10);
    printf("able to set from 1 to 12 level.\n");

    while (1)
    {
        gotoTextPos(14,HEIGHT/2+2);
        setTextColor(LIGHT_PURPLE);
        printf("Difficulty Speed:");
        setTextColor(YELLOW);
        printf("   %2d",*speed);

        switch(jkGetKey())
        {
        //��ȡ������Ϣ��ѡ���Ѷ�
        case JK_UP:
            if (*speed == 1)
            {
                (*speed) = 12;
                break;
            }
            if (*speed > 1)
                (*speed) --;
            break;
        case JK_DOWN:
            if (*speed == 12)
            {
                (*speed) = 1;
                break;
            }
            if (*speed < 12)
                (*speed) ++;
            break;
        case JK_ESC:
            model=0;
            speed=1;
            return Menu();
            break;
        case JK_ENTER:
            return 1;
            break;
        default:
            ;
        }
    }
}


/**--------------------------------------------------------------------------*
Name:		    Instruction
Discribe:		Chinese Game Instruction
Return:		    0
**--------------------------------------------------------------------------*/
uchar Instruction()//��ʾѡ���ѶȵĽ���
{
    //	assert (NULL != diff);
    system("cls");//to show set difficulty level interface
    printf("\n");
    setTextColor(GREY);

    printf("   ����������������������������������������������������������\n");
    printf("   ��                                                      ��\n");
    printf("   ��               _________��Ϸ˵��_________             ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ��                                                      ��\n");
    printf("   ����������������������������������������������������������\n");

    setTextColor(LIGHT_GREEN);
    gotoTextPos(29,3);
    printf("��Ϸ˵��\n");
    setTextColor(TEAL);
    gotoTextPos(14,5);
    printf("��Ϸ��������5��ģʽ,ÿ��ģʽ���и���\n");
    gotoTextPos(14,6);
    printf("���ص�Ϳ����ԣ������㲻ͬ��ҵ�����\n");

    gotoTextPos(13,7);
    setTextColor(RED_ORANGE);
    printf("��        ��\n");
    gotoTextPos(15,7);
    setTextColor(YELLOW);
    printf("����ģʽ\n");
    setTextColor(LIGHT_PURPLE);
    gotoTextPos(25,7);
    printf("��ԭ֭ԭζ��ԭ����̰���ߡ�\n");


    gotoTextPos(13,8);
    setTextColor(RED_ORANGE);
    printf("��        ��\n");
    gotoTextPos(15,8);
    setTextColor(YELLOW);
    printf("����ģʽ\n");
    setTextColor(LIGHT_PURPLE);
    gotoTextPos(25,8);
    printf("��6������ؿ����Ե�8��ʳ��\n");
    gotoTextPos(14,9);
    printf("������һ�أ�����48��ʳ��ͨ�ء�\n");

    gotoTextPos(13,10);
    setTextColor(RED_ORANGE);
    printf("��        ��\n");
    gotoTextPos(15,10);
    setTextColor(YELLOW);
    printf("��Խģʽ\n");
    setTextColor(LIGHT_PURPLE);
    gotoTextPos(25,10);
    printf("��û����Χǽ�ڣ������ɴ���\n");

    gotoTextPos(13,11);
    setTextColor(RED_ORANGE);
    printf("��        ��\n");
    gotoTextPos(15,11);
    setTextColor(YELLOW);
    printf("��սģʽ\n");
    setTextColor(LIGHT_PURPLE);
    gotoTextPos(25,11);
    printf("��ÿ�Ե�5��ʳ��ǽ�ڻ��Զ���\n");
    gotoTextPos(14,12);
    printf("Сһ�㣬����30��ʳ��ͨ�ء�\n");

    gotoTextPos(13,13);
    setTextColor(RED_ORANGE);
    printf("��        ��\n");
    gotoTextPos(15,13);
    setTextColor(YELLOW);
    printf("���ģʽ\n");
    setTextColor(LIGHT_PURPLE);
    gotoTextPos(25,13);
    printf("��û��ʳ�û��ʱ�����ƣ�\n");
    gotoTextPos(14,14);
    printf("�е�ֻ���޾�����ˮ����\n");

    gotoTextPos(14,15);
    setTextColor(MEDIUM_BLUE);
    printf("��\n");
    gotoTextPos(14,15);
    printf("����˵��\n");
    setTextColor(RED_ORANGE);
    gotoTextPos(23,15);
    printf("����Ϸ�У�����ʱ�̰���ESC����\n");
    gotoTextPos(14,16);
    printf("���������棬����Enter��ͣ��Ϸ��������\n");
    gotoTextPos(14,17);
    printf("������ģʽ���ٶȡ��ؿ�ѡ���Լ��ߵ��ƶ�\n");
    gotoTextPos(14,18);
    printf("��������Ϸ�������棬����Y/y or N/n��\n");
    gotoTextPos(14,19);
    printf("�л�������Enterȷ����ɲ���ָ�\n");



    while (1)
    {
        switch(jkGetKey())
        {
        case JK_ESC:
            return Menu();
            break;
        case JK_ENTER:
            return Menu();
            break;
        default:
            ;
        }
    }
}


/**--------------------------------------------------------------------------*
Name:		    InitSnake
Discribe:		Initialize length, coordinate and direction;
Return:		    NuLL
**--------------------------------------------------------------------------*/
void InitSnake(struct SNAKE *snake)//��ʼ���ߵ�λ�ó��ȷ���
{
    uchar i = 0;
    //	assert (NULL!=snake);
    snake->length = SNAKE_MIN_LEN;//��ʼ������
    snake->direction = R;//��ʼ������
    for (; i<SNAKE_MIN_LEN; i++)
    {
        //��ʼ�����������
        snake->body[i].x=SNAKE_MIN_LEN-i;
        snake->body[i].y=5;
    }
}



/**--------------------------------------------------------------------------*
Name:		    InitSnakeTunnel
Discribe:		Initialize length, coordinate and direction;
Return:		    NuLL
**--------------------------------------------------------------------------*/
void InitSnakeTunnel(struct SNAKE *snake)//��ʼ���ߵ�λ�ó��ȷ���
{
    uchar i = 0;
    //	assert (NULL!=snake);
    snake->length = SNAKE_MIN_LEN;//��ʼ������
    snake->direction = R;//��ʼ������
    for (; i<SNAKE_MIN_LEN; i++)
    {
        //��ʼ�����������
        snake->body[i].x=SNAKE_MIN_LEN-i;
        snake->body[i].y=5;
    }
}


/**--------------------------------------------------------------------------*
Name:		    InSnake
Discribe:		if in the snake
Return:		TRUE,FALSE
**--------------------------------------------------------------------------*/
uchar InSnake(struct SNAKE *snake, uchar x, uchar y)//�ж�ĳһ���Ƿ���������
{
    uchar i;
    for(i=0; i<snake->length; i++)
    {
        //���ĳһ��������ĳһ������ͬ��������1
        if((x==snake->body[i].x) && (y==snake->body[i].y))
            return 1;
    }
    return 0;
}


/**--------------------------------------------------------------------------*
Name:		InitFood0
Discribe:	make food
Return:		0
**--------------------------------------------------------------------------*/
uchar InitFood0 (struct SNAKE *snake)//��ʼ��ʳ��
{
    uchar x=0,y=0;
    srand((unsigned)time(NULL));//��ʼ���������
    switch(pass)
    {
    case 0:
        do
        {
            //��������������ʳ���������ص�������������
            food.x = rand()%(WIDTH-2)+1;
            food.y = rand()%(HEIGHT-4)+1;
        }
        while(InSnake(snake,food.x,food.y));

    case 1:
        //��������������ʳ���������ص�������������
        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((15==x)&&(6==y))||((15==x)&&(7==y))||((14==x)&&(7==y))||((13==x)&&(8==y))\
                    ||((14==x)&&(8==y))||((15==x)&&(8==y))||((15==x)&&(9==y))||((15==x)&&(10==y))\
                    ||((15==x)&&(11==y))||((15==x)&&(12==y))||((15==x)&&(13==y))||((13==x)&&(14==y))\
                    ||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 2:
        //��������������ʳ���������ص�������������

        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((13==x)&&(11==y))||((13==x)&&(12==y))||((13==x)&&(13==y))\
                    ||((13==x)&&(14==y))||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 3:
        //��������������ʳ���������ص�������������
        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 4:
        //��������������ʳ���������ص�������������

        while(1)
        {
            //	srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((17==x)&&(6==y))||((13==x)&&(7==y))||((17==x)&&(7==y))\
                    ||((13==x)&&(8==y))||((17==x)&&(8==y))||((13==x)&&(9==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 5:
        //��������������ʳ���������ص�������������

        while(1)
        {
            //	srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((13==x)&&(7==y))||((13==x)&&(8==y))||((13==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    }
    return 0;//��ʼ���ɹ��󷵻�
}


/**--------------------------------------------------------------------------*
Name:		InitFood1
Discribe:	make food
Return:		0
**--------------------------------------------------------------------------*/
uchar InitFood1 (struct SNAKE *snake)//��ʼ��ʳ��
{
    uchar x=0,y=0;
    srand((unsigned)time(NULL));//��ʼ���������
    switch(model_pass)
    {
    case 0:
        do
        {
            //��������������ʳ���������ص�������������
            food.x = rand()%(WIDTH-2)+1;
            food.y = rand()%(HEIGHT-4)+1;
        }
        while(InSnake(snake,food.x,food.y));
    case 1:
        //	do{
        //��������������ʳ���������ص�������������
        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((15==x)&&(6==y))||((15==x)&&(7==y))||((14==x)&&(7==y))||((13==x)&&(8==y))\
                    ||((14==x)&&(8==y))||((15==x)&&(8==y))||((15==x)&&(9==y))||((15==x)&&(10==y))\
                    ||((15==x)&&(11==y))||((15==x)&&(12==y))||((15==x)&&(13==y))||((13==x)&&(14==y))\
                    ||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;
        //		}while(InSnake(snake,food.x,food.y));

    case 2:
        //	do{
        //��������������ʳ���������ص�������������

        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((13==x)&&(11==y))||((13==x)&&(12==y))||((13==x)&&(13==y))\
                    ||((13==x)&&(14==y))||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;
        //	}while(InSnake(snake,food.x,food.y));

    case 3:
        //	do{
        //��������������ʳ���������ص�������������

        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;
        //	}while(InSnake(snake,food.x,food.y));

    case 4:
        //	do{
        //��������������ʳ���������ص�������������

        while(1)
        {
            //	srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((17==x)&&(6==y))||((13==x)&&(7==y))||((17==x)&&(7==y))\
                    ||((13==x)&&(8==y))||((17==x)&&(8==y))||((13==x)&&(9==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;
        //	}while(InSnake(snake,food.x,food.y));

    case 5:
        //	do{
        //��������������ʳ���������ص�������������

        while(1)
        {
            //	srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((13==x)&&(7==y))||((13==x)&&(8==y))||((13==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;
        //	}while(InSnake(snake,food.x,food.y));

    }
    return 0;//��ʼ���ɹ��󷵻�
}


/**--------------------------------------------------------------------------*
Name:		InitFood2
Discribe:	make food
Return:		0
**--------------------------------------------------------------------------*/
uchar InitFood2 (struct SNAKE *snake)//��ʼ��ʳ��
{
    uchar x=0,y=0;
    srand((unsigned)time(NULL));//��ʼ���������
    switch(pass)
    {
    case 0:
        do
        {
            //��������������ʳ���������ص�������������
            food.x = rand()%(WIDTH-2)+1;
            food.y = rand()%(HEIGHT-4)+1;
        }
        while(InSnake(snake,food.x,food.y));

    case 1:
        //��������������ʳ���������ص�������������
        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(InSnake(snake, x, y)\
                    ||((15==x)&&(6==y))||((15==x)&&(7==y))||((14==x)&&(7==y))||((13==x)&&(8==y))\
                    ||((14==x)&&(8==y))||((15==x)&&(8==y))||((15==x)&&(9==y))||((15==x)&&(10==y))\
                    ||((15==x)&&(11==y))||((15==x)&&(12==y))||((15==x)&&(13==y))||((13==x)&&(14==y))\
                    ||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 2:
        //��������������ʳ���������ص�������������

        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((13==x)&&(11==y))||((13==x)&&(12==y))||((13==x)&&(13==y))\
                    ||((13==x)&&(14==y))||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 3:
        //��������������ʳ���������ص�������������
        while(1)
        {
            //		srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 4:
        //��������������ʳ���������ص�������������

        while(1)
        {
            //	srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((17==x)&&(6==y))||((13==x)&&(7==y))||((17==x)&&(7==y))\
                    ||((13==x)&&(8==y))||((17==x)&&(8==y))||((13==x)&&(9==y))||((17==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 5:
        //��������������ʳ���������ص�������������

        while(1)
        {
            //	srand((unsigned)time(NULL));//��ʼ���������
            x = rand()%(WIDTH-2)+1;
            y = rand()%(HEIGHT-4)+1;
            if(InSnake(snake, x, y)\
                    ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                    ||((17==x)&&(6==y))||((13==x)&&(7==y))||((13==x)&&(8==y))||((13==x)&&(9==y))\
                    ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                    ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                    ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    }
    return 0;//��ʼ���ɹ��󷵻�
}



/**--------------------------------------------------------------------------*
Name:		InitFood_Challenge
Discribe:	make food
Return:		0
**--------------------------------------------------------------------------*/
uchar InitFood_Challenge (struct SNAKE *snake)//��ʼ��ʳ��
{
    uchar x=0,y=0;
    srand((unsigned)time(NULL));//��ʼ���������
    switch(model_challenge_pass)
    {
    case 0:
        //��������������ʳ���������ص�������������
        while(1)
        {
            x = rand()%30;
            y = rand()%20;
            if(0==x || 1==x || 0==y || 1==y || InSnake(snake, x, y))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 1:
        //��������������ʳ���������ص�������������
        while(1)
        {
            x = rand()%29;
            y = rand()%19;
            if(0==x || 1==x || 2==x || 0==y || 1==y || 2==y || InSnake(snake, x, y))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 2:
        //��������������ʳ���������ص�������������
        while(1)
        {
            x = rand()%28;
            y = rand()%18;
            if(0==x || 1==x || 2==x || 3==x || 0==y || 1==y || 2==y || 3==y || InSnake(snake, x, y))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 3:
        //��������������ʳ���������ص�������������
        while(1)
        {
            x = rand()%27;
            y = rand()%17;
            if(0==x || 1==x || 2==x || 3==x || 4==x || 0==y || 1==y || 2==y || 3==y || 4==y || InSnake(snake, x, y))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 4:
        //��������������ʳ���������ص�������������
        while(1)
        {
            x = rand()%26;
            y = rand()%16;
            if(0==x || 1==x || 2==x || 3==x || 4==x || 5==x || 0==y || 1==y || 2==y || 3==y || 4==y || 5==y || InSnake(snake, x, y))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    case 5:
        //��������������ʳ���������ص�������������
        while(1)
        {
            x = rand()%25;
            y = rand()%15;
            if(0==x || 1==x || 2==x || 3==x || 4==x || 5==x || 6==x || 0==y || 1==y || 2==y || 3==y || 4==y || 5==y || 6==y || InSnake(snake, x, y))
                continue;
            else
                break;
        }
        food.x = x;
        food.y = y;

    }
    return 0;//��ʼ���ɹ��󷵻�
}


/**--------------------------------------------------------------------------*
Name:		     ShowPause
Discribe:		 Enter Pause
Return:		     Null
**--------------------------------------------------------------------------*/
void ShowPause()//��ʾ��ͣ�Ľ���
{
    int key;

    system("cls");
    setTextColor(RED_ORANGE);
    gotoTextPos(0,HEIGHT/2-6);
    printf("     * * * *        *       *       *  * * * *  * * * * *\n");
    printf("     *       *     * *      *       * *         *        \n");
    printf("     *       *    *   *     *       * *         *        \n");
    printf("     * * * *     * * * *    *       *  * * * *  * * * * *\n");
    printf("     *          *       *   *       *         * *        \n");
    printf("     *         *         *   *     *          * *        \n");
    printf("     *        *           *   * * *    * * * *  * * * * *\n");
    setTextColor(WHITE);
    printf("\n\n                Please press ENTER to continue.");
    while(key=jkGetKey())
    {
        //ֻ�����»س���ʱ�˳�ѭ��������Ϸ
        if(key==JK_ENTER)
            break;
    }
}

/**--------------------------------------------------------------------------*
Name:		MoveSnake
Discribe:
Return:		nofood
**--------------------------------------------------------------------------*/
uchar MoveSnake(struct SNAKE *snake)
{
    //	assert(NULL!=snake);
    uchar i=0;
    uchar nofood=0;
    uchar x=snake->body[0].x;
    uchar y=snake->body[0].y;//��ͷ����
    uchar lx=snake->body[snake->length-1].x;
    uchar ly=snake->body[snake->length-1].y;//��β����
    switch (snake->direction)
    {
    case U:
        y-=1;
        break;
    case D:
        y+=1;
        break;//����������ϣ�y����-1������+1
    case L:
        x -=1;
        break;
    case R:
        x+=1;
        break;
    default:
        ;
    }
    if ((x==food.x) && ( y==food.y))
    {
        //�ж��Ƿ�Ե�ʳ��
        snake->length++;//�Ե�ʳ����ȼ�һ
        nofood = TRUE;//û��ʳ��
    }
    for(i=snake->length-1; i>0; i--)
    {
        //��ͷ���µĲ����ƶ�
        snake->body[i]=snake->body[i-1];
    }
    switch(model)
    {
    case 0:
        if(IsOver0(snake, x, y))//�Ƶ�������������򷵻�OVER
            return OVER;
        break;
    case 1:
        if(IsOver1(snake, x, y))//�Ƶ�������������򷵻�OVER
            return OVER;
        break;
    case 3:
        if(IsOver3(snake, x, y))//�Ƶ�������������򷵻�OVER
            return OVER;
        break;
    }

    if(!nofood)
    {
        //���û�гԵ�ʳ���ԭ����β����
        gotoTextPos(lx*2,ly);//��궨λ��ԭ����βλ��
        printf("��");//��������
    }
    snake->body[0].x=x,snake->body[0].y=y;
    DrawSnake(snake);//�����µ���
    return nofood;//�����Ƿ���ʳ�����Ϸ����
}


/**--------------------------------------------------------------------------*
Name:		MoveSnake2
Discribe:
Return:		nofood
**--------------------------------------------------------------------------*/
uchar MoveSnake2(struct SNAKE *snake)
{
    //	assert(NULL!=snake);
    uchar i=0;
    uchar nofood=0;
    uchar x=snake->body[0].x;
    uchar y=snake->body[0].y;//��ͷ����
    uchar lx=snake->body[snake->length-1].x;
    uchar ly=snake->body[snake->length-1].y;//��β����
    switch (snake->direction)
    {
    case U:
        if(y==0)
        {
            y=21;
            break;
        }
        y-=1;
        break;
    case D:
        if(y==21)
        {
            y=0;
            break;
        }
        y+=1;
        break;//����������ϣ�y����-1������+1
    case L:
        if(x==0)
        {
            x=31;
            break;
        }
        x -=1;
        break;
    case R:
        if(x==31)
        {
            x=0;
            break;
        }
        x+=1;
        break;
    default:
        ;
    }
    if ((x==food.x) && ( y==food.y))
    {
        //�ж��Ƿ�Ե�ʳ��
        snake->length++;//�Ե�ʳ����ȼ�һ
        nofood = TRUE;//û��ʳ��
    }
    for(i=snake->length-1; i>0; i--)
    {
        //��ͷ���µĲ����ƶ�
        snake->body[i]=snake->body[i-1];
    }
    if(IsOver2(snake, x, y))//�Ƶ�������������򷵻�OVER
        return OVER;
    if(!nofood)
    {
        //���û�гԵ�ʳ���ԭ����β����
        gotoTextPos(lx*2,ly);//��궨λ��ԭ����βλ��
        printf("��");//��������
    }
    snake->body[0].x=x,snake->body[0].y=y;
    DrawSnake(snake);//�����µ���
    return nofood;//�����Ƿ���ʳ�����Ϸ����
}



/**--------------------------------------------------------------------------*
Name:		MoveSnakeTunnel
Discribe:
Return:		nofood
**--------------------------------------------------------------------------*/
uchar MoveSnakeTunnel(struct SNAKE *snake)
{
    //	assert(NULL!=snake);
    uchar i=0;
    uchar nofood=0;
    uchar x=snake->body[0].x;
    uchar y=snake->body[0].y;//��ͷ����
    uchar lx=snake->body[snake->length-1].x;
    uchar ly=snake->body[snake->length-1].y;//��β����
    switch (snake->direction)
    {
    case U:
        if(y==0)
        {
            y=21;
            break;
        }
        y-=1;
        break;
    case D:
        if(y==21)
        {
            y=0;
            break;
        }
        y+=1;
        break;//����������ϣ�y����-1������+1
    case L:
        if(x==0)
        {
            x=31;
            break;
        }
        x -=1;
        break;
    case R:
        if(x==31)
        {
            x=0;
            break;
        }
        x+=1;
        break;
    default:
        ;
    }

    for(i=snake->length-1; i>0; i--)
    {
        //��ͷ���µĲ����ƶ�
        snake->body[i]=snake->body[i-1];
    }
    if(IsOver4(snake, x, y))//�Ƶ�������������򷵻�OVER
        return OVER;
    if(!nofood)
    {
        //���û�гԵ�ʳ���ԭ����β����
        gotoTextPos(lx*2,ly);//��궨λ��ԭ����βλ��
        printf("��");//��������
    }
    snake->body[0].x=x,snake->body[0].y=y;
    DrawSnake(snake);//�����µ���
    return nofood;//�����Ƿ���ʳ�����Ϸ����
}


/**--------------------------------------------------------------------------*
Name:		DrawWall
Discribe:
Return:
**--------------------------------------------------------------------------*/
void DrawWall_0()//��������ǽ
{
    uchar x=0,y=0;
    setTextColor(RED_ORANGE);//����ǽ����ɫ
    gotoTextPos(0,0);

    if(model!=2)
    {
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        gotoTextPos(0,HEIGHT-3);
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        for(y=1; y<HEIGHT-3; y++)
        {
            gotoTextPos(0,y);
            printf("��");
            gotoTextPos((WIDTH-1)*2,y);
            printf("��");
        }
    }
}

void DrawWall_1()//��������ǽ
{

    uchar x=0,y=0;

    gotoTextPos(0,0);
    setTextColor(LIGHT_PURPLE);
    printf("\n\n\n\n\n\n");
    printf("                              ��                        \n");
    printf("                            ����                        \n");
    printf("                          ������                        \n");
    printf("                              ��                        \n");
    printf("                              ��                        \n");
    printf("                              ��                        \n");
    printf("                              ��                        \n");
    printf("                              ��                        \n");
    printf("                          ����������                    \n");

    setTextColor(RED_ORANGE);//����ǽ����ɫ
    gotoTextPos(0,0);

    if(model!=2)
    {
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        gotoTextPos(0,HEIGHT-3);
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        for(y=1; y<HEIGHT-3; y++)
        {
            gotoTextPos(0,y);
            printf("��");
            gotoTextPos((WIDTH-1)*2,y);
            printf("��");
        }
    }
}

void DrawWall_2()//��������ǽ
{
    uchar x=0,y=0;

    gotoTextPos(0,0);
    setTextColor(LIGHT_PURPLE);
    printf("\n\n\n\n\n\n");
    printf("                          ����������                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                          ����������                    \n");
    printf("                          ��                            \n");
    printf("                          ��                            \n");
    printf("                          ��                            \n");
    printf("                          ����������                    \n");

    setTextColor(RED_ORANGE);//����ǽ����ɫ
    gotoTextPos(0,0);

    if(model!=2)
    {
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        gotoTextPos(0,HEIGHT-3);
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        for(y=1; y<HEIGHT-3; y++)
        {
            gotoTextPos(0,y);
            printf("��");
            gotoTextPos((WIDTH-1)*2,y);
            printf("��");
        }
    }


}

void DrawWall_3()//��������ǽ
{
    uchar x=0,y=0;
    gotoTextPos(0,0);
    setTextColor(LIGHT_PURPLE);
    printf("\n\n\n\n\n\n");
    printf("                          ����������                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                          ����������                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                          ����������                    \n");

    setTextColor(RED_ORANGE);//����ǽ����ɫ
    gotoTextPos(0,0);

    if(model!=2)
    {
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        gotoTextPos(0,HEIGHT-3);
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        for(y=1; y<HEIGHT-3; y++)
        {
            gotoTextPos(0,y);
            printf("��");
            gotoTextPos((WIDTH-1)*2,y);
            printf("��");
        }
    }
}

void DrawWall_4()//��������ǽ
{
    uchar x=0,y=0;
    gotoTextPos(0,0);
    setTextColor(LIGHT_PURPLE);
    printf("\n\n\n\n\n\n");
    printf("                          ��      ��                    \n");
    printf("                          ��      ��                    \n");
    printf("                          ��      ��                    \n");
    printf("                          ��      ��                    \n");
    printf("                          ����������                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");

    setTextColor(RED_ORANGE);//����ǽ����ɫ
    gotoTextPos(0,0);

    if(model!=2)
    {
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        gotoTextPos(0,HEIGHT-3);
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        for(y=1; y<HEIGHT-3; y++)
        {
            gotoTextPos(0,y);
            printf("��");
            gotoTextPos((WIDTH-1)*2,y);
            printf("��");
        }
    }
}

void DrawWall_5()//��������ǽ
{
    uchar x=0,y=0;
    gotoTextPos(0,0);
    setTextColor(LIGHT_PURPLE);
    printf("\n\n\n\n\n\n");
    printf("                          ����������                    \n");
    printf("                          ��                            \n");
    printf("                          ��                            \n");
    printf("                          ��                            \n");
    printf("                          ����������                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                          ����������                    \n");

    setTextColor(RED_ORANGE);//����ǽ����ɫ
    gotoTextPos(0,0);

    if(model!=2)
    {
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        gotoTextPos(0,HEIGHT-3);
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        for(y=1; y<HEIGHT-3; y++)
        {
            gotoTextPos(0,y);
            printf("��");
            gotoTextPos((WIDTH-1)*2,y);
            printf("��");
        }
    }
}


/**--------------------------------------------------------------------------*
Name:		DrawWall_challenge
Discribe:
Return:
**--------------------------------------------------------------------------*/


void DrawWall_challenge()//��������ǽ
{
    uchar x=0,y=0;
    switch(model_challenge_pass)
    {

    case 0:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        gotoTextPos(0,0);
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        gotoTextPos(0,HEIGHT-3);
        for(x=0; x<WIDTH; x++)
        {
            printf("��");
        }
        for(y=1; y<HEIGHT-3; y++)
        {
            gotoTextPos(0,y);
            printf("��");
            gotoTextPos((WIDTH-1)*2,y);
            printf("��");
        }
        break;

    case 1:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        gotoTextPos(2,1);
        for(x=1; x<WIDTH-1; x++)
        {
            printf("��");
        }
        gotoTextPos(2,HEIGHT-4);
        for(x=1; x<WIDTH-1; x++)
        {
            printf("��");
        }
        for(y=2; y<HEIGHT-4; y++)
        {
            gotoTextPos(2,y);
            printf("��");
            gotoTextPos((WIDTH-2)*2,y);
            printf("��");
        }
        break;

    case 2:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        gotoTextPos(4,2);
        for(x=2; x<WIDTH-2; x++)
        {
            printf("��");
        }
        gotoTextPos(4,HEIGHT-5);
        for(x=2; x<WIDTH-2; x++)
        {
            printf("��");
        }
        for(y=3; y<HEIGHT-5; y++)
        {
            gotoTextPos(4,y);
            printf("��");
            gotoTextPos((WIDTH-3)*2,y);
            printf("��");
        }

        break;

    case 3:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        gotoTextPos(6,3);
        for(x=3; x<WIDTH-3; x++)
        {
            printf("��");
        }
        gotoTextPos(6,HEIGHT-6);
        for(x=3; x<WIDTH-3; x++)
        {
            printf("��");
        }
        for(y=4; y<HEIGHT-6; y++)
        {
            gotoTextPos(6,y);
            printf("��");
            gotoTextPos((WIDTH-4)*2,y);
            printf("��");
        }

        break;

    case 4:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        gotoTextPos(8,4);
        for(x=4; x<WIDTH-4; x++)
        {
            printf("��");
        }
        gotoTextPos(8,HEIGHT-7);
        for(x=4; x<WIDTH-4; x++)
        {
            printf("��");
        }
        for(y=5; y<HEIGHT-7; y++)
        {
            gotoTextPos(8,y);
            printf("��");
            gotoTextPos((WIDTH-5)*2,y);
            printf("��");
        }

        break;

    case 5:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        gotoTextPos(10,5);
        for(x=5; x<WIDTH-5; x++)
        {
            printf("��");
        }
        gotoTextPos(10,HEIGHT-8);
        for(x=5; x<WIDTH-5; x++)
        {
            printf("��");
        }
        for(y=6; y<HEIGHT-8; y++)
        {
            gotoTextPos(10,y);
            printf("��");
            gotoTextPos((WIDTH-6)*2,y);
            printf("��");
        }

        break;

    default:
        ;
    }
}


/**--------------------------------------------------------------------------*
Name:		DrawTunnel
Discribe:
Return:
**--------------------------------------------------------------------------*/

void DrawTunnel()//��������ǽ
{
    uchar x=0,y=0;
    uint C_flag=0;
    switch(model_Tunnel_pass)
    {

    case 0:
        setTextColor(RED_ORANGE);//����ǽ����ɫ

        //-------------------------------------------
        gotoTextPos(0,2);         //  --
        for(x=0; x<17; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=2; y<16; y++)       //   |
        {
            gotoTextPos(32,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(16,15);         //  --
        for(x=8; x<17; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=15; y<18; y++)       //   |
        {
            gotoTextPos(16,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(16,17);         //  --
        for(x=8; x<19; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<18; y++)       //   |
        {
            gotoTextPos(36,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(36,1);         //  --
        for(x=18; x<29; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<17; y++)       //   |
        {
            gotoTextPos(56,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(56,16);         //  --
        for(x=28; x<32; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        //-------------------------------------------
        gotoTextPos(0,8);
        for(x=0; x<11; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=8; y<11; y++)       //   |
        {
            gotoTextPos(20,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(6,10);
        for(x=3; x<11; x++)       //    -
        {
            printf("��");
        }

        for(y=10; y<22; y++)       //   |
        {
            gotoTextPos(6,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(6,21);
        for(x=3; x<23; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<22; y++)       //   |
        {
            gotoTextPos(44,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(44,5);
        for(x=22; x<25; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<21; y++)       //   |
        {
            gotoTextPos(48,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(48,20);
        for(x=24; x<32; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }
        break;

    case 1:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        //-------------------------------------------
        gotoTextPos(0,16);         //  --
        for(x=0; x<6; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=14; y<17; y++)       //   |
        {
            gotoTextPos(10,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(2,14);         //  --
        for(x=1; x<6; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<15; y++)       //   |
        {
            gotoTextPos(2,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(2,1);         //  --
        for(x=1; x<16; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<17; y++)       //   |
        {
            gotoTextPos(30,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(30,16);         //  --
        for(x=15; x<27; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=14; y<17; y++)       //   |
        {
            gotoTextPos(52,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(34,14);         //  --
        for(x=17; x<27; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=4; y<15; y++)       //   |
        {
            gotoTextPos(34,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(34,4);         //  --
        for(x=17; x<27; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=0; y<5; y++)       //   |
        {
            gotoTextPos(52,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        //-------------------------------------------
        gotoTextPos(0,20);
        for(x=0; x<10; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=10; y<21; y++)       //   |
        {
            gotoTextPos(18,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(10,10);
        for(x=5; x<10; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<11; y++)       //   |
        {
            gotoTextPos(10,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(10,5);
        for(x=5; x<12; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<21; y++)       //   |
        {
            gotoTextPos(22,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(22,20);
        for(x=11; x<31; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=10; y<21; y++)       //   |
        {
            gotoTextPos(60,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(42,10);
        for(x=21; x<31; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=8; y<11; y++)       //   |
        {
            gotoTextPos(42,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(42,8);
        for(x=21; x<31; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=0; y<9; y++)       //   |
        {
            gotoTextPos(60,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        break;

    case 2:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        //-------------------------------------------
        for(y=16; y<22; y++)       //   |
        {
            gotoTextPos(52,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(48,16);         //  --
        for(x=24; x<27; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=16; y<21; y++)       //   |
        {
            gotoTextPos(48,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(28,20);         //  --
        for(x=14; x<25; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=16; y<21; y++)       //   |
        {
            gotoTextPos(28,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(24,16);         //  --
        for(x=12; x<15; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=16; y<21; y++)       //   |
        {
            gotoTextPos(24,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(2,20);         //  --
        for(x=1; x<13; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=12; y<21; y++)       //   |
        {
            gotoTextPos(2,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(2,12);         //  --
        for(x=1; x<5; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=8; y<13; y++)       //   |
        {
            gotoTextPos(8,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(8,8);         //  --
        for(x=4; x<27; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<9; y++)       //   |
        {
            gotoTextPos(52,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<9; y++)       //   |
        {
            gotoTextPos(36,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<9; y++)       //   |
        {
            gotoTextPos(20,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(0,5);         //  --
        for(x=0; x<11; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        //-------------------------------------------
        for(y=1; y<22; y++)       //   |
        {
            gotoTextPos(60,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(40,12);
        for(x=20; x<31; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=12; y<17; y++)       //   |
        {
            gotoTextPos(40,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(36,16);
        for(x=18; x<21; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=12; y<17; y++)       //   |
        {
            gotoTextPos(36,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(16,12);
        for(x=8; x<19; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=12; y<17; y++)       //   |
        {
            gotoTextPos(16,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(10,16);
        for(x=5; x<9; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(0,1);
        for(x=0; x<31; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<5; y++)       //   |
        {
            gotoTextPos(28,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<5; y++)       //   |
        {
            gotoTextPos(44,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        break;

    case 3:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        //-------------------------------------------
        gotoTextPos(48,5);         //  --
        for(x=24; x<32; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<22; y++)       //   |
        {
            gotoTextPos(62,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(48,15);         //  --
        for(x=24; x<32; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(34,21);         //  --
        for(x=17; x<32; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=14; y<22; y++)       //   |
        {
            gotoTextPos(34,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(30,14);         //  --
        for(x=15; x<18; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=14; y<21; y++)       //   |
        {
            gotoTextPos(30,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(0,20);         //  --
        for(x=0; x<16; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=14; y<21; y++)       //   |
        {
            gotoTextPos(18,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(12,14);         //  --
        for(x=6; x<10; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=4; y<21; y++)       //   |
        {
            gotoTextPos(0,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(0,4);         //  --
        for(x=0; x<7; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=4; y<9; y++)       //   |
        {
            gotoTextPos(12,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(12,6);         //  --
        for(x=6; x<18; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=4; y<7; y++)       //   |
        {
            gotoTextPos(24,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        //-------------------------------------------
        gotoTextPos(0,1);
        for(x=0; x<32; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<4; y++)       //   |
        {
            gotoTextPos(18,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<4; y++)       //   |
        {
            gotoTextPos(32,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<10; y++)       //   |
        {
            gotoTextPos(40,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(18,9);
        for(x=9; x<28; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=9; y<12; y++)       //   |
        {
            gotoTextPos(54,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(6,11);
        for(x=3; x<28; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=7; y<18; y++)       //   |
        {
            gotoTextPos(6,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(6,17);
        for(x=3; x<7; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=11; y<19; y++)       //   |
        {
            gotoTextPos(40,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(40,18);
        for(x=20; x<29; x++)       //    -
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=11; y<18; y++)       //   |
        {
            gotoTextPos(24,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        break;

    case 4:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        //-------------------------------------------
        gotoTextPos(50,1);         //  --
        for(x=25; x<32; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(8,0);         //  --
        for(x=4; x<26; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<10; y++)       //   |
        {
            gotoTextPos(8,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=0; y<13; y++)       //   |
        {
            gotoTextPos(2,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(4,12);         //  --
        for(x=2; x<14; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=3; y<12; y++)       //   |
        {
            gotoTextPos(14,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<10; y++)       //   |
        {
            gotoTextPos(20,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(22,3);         //  --
        for(x=11; x<13; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(0,14);         //  --
        for(x=0; x<14; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=6; y<14; y++)       //   |
        {
            gotoTextPos(26,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(30,3);         //  --
        for(x=15; x<23; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=4; y<10; y++)       //   |
        {
            gotoTextPos(30,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(26,6);         //  --
        for(x=13; x<16; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(32,9);         //  --
        for(x=16; x<22; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(36,6);         //  --
        for(x=18; x<26; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=7; y<18; y++)       //   |
        {
            gotoTextPos(48,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=2; y<12; y++)       //   |
        {
            gotoTextPos(50,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(52,10);         //  --
        for(x=26; x<29; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(56,5);         //  --
        for(x=28; x<32; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(56,6);         //  --
        for(x=28; x<32; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=7; y<21; y++)       //   |
        {
            gotoTextPos(62,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(54,14);         //  --
        for(x=27; x<31; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(32,12);         //  --
        for(x=16; x<24; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=13; y<17; y++)       //   |
        {
            gotoTextPos(44,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(44,17);         //  --
        for(x=22; x<29; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=13; y<17; y++)       //   |
        {
            gotoTextPos(46,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=15; y<20; y++)       //   |
        {
            gotoTextPos(0,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=13; y<17; y++)       //   |
        {
            gotoTextPos(32,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(6,17);         //  --
        for(x=3; x<17; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=15; y<20; y++)       //   |
        {
            gotoTextPos(38,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(0,20);         //  --
        for(x=0; x<31; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        break;

    case 5:
        setTextColor(RED_ORANGE);//����ǽ����ɫ
        //-------------------------------------------
        for(y=15; y<22; y++)       //   |
        {
            gotoTextPos(2,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=18; y<22; y++)       //   |
        {
            gotoTextPos(8,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(10,21);         //  --
        for(x=5; x<32; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(20,19);         //  --
        for(x=10; x<15; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(26,20);         //  --
        for(x=13; x<15; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(4,15);         //  --
        for(x=2; x<8; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(14,16);         //  --
        for(x=7; x<18; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=17; y<19; y++)       //   |
        {
            gotoTextPos(14,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=17; y<19; y++)       //   |
        {
            gotoTextPos(14,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(34,19);         //  --
        for(x=17; x<30; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<21; y++)       //   |
        {
            gotoTextPos(62,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=11; y<19; y++)       //   |
        {
            gotoTextPos(34,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=16; y<19; y++)       //   |
        {
            gotoTextPos(50,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=16; y<19; y++)       //   |
        {
            gotoTextPos(58,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=15; y<18; y++)       //   |
        {
            gotoTextPos(38,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=15; y<18; y++)       //   |
        {
            gotoTextPos(46,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=15; y<18; y++)       //   |
        {
            gotoTextPos(54,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(40,17);         //  --
        for(x=20; x<23; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(46,14);         //  --
        for(x=23; x<31; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(36,13);         //  --
        for(x=18; x<21; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=13; y<16; y++)       //   |
        {
            gotoTextPos(42,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(42,12);         //  --
        for(x=21; x<30; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=3; y<12; y++)       //   |
        {
            gotoTextPos(58,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(46,3);         //  --
        for(x=23; x<29; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<11; y++)       //   |
        {
            gotoTextPos(54,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=9; y<12; y++)       //   |
        {
            gotoTextPos(50,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(36,11);         //  --
        for(x=18; x<20; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(38,10);         //  --
        for(x=19; x<24; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(46,9);         //  --
        for(x=23; x<25; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(6,1);         //  --
        for(x=3; x<31; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=0; y<2; y++)       //   |
        {
            gotoTextPos(6,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=0; y<5; y++)       //   |
        {
            gotoTextPos(2,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=2; y<6; y++)       //   |
        {
            gotoTextPos(42,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=7; y<9; y++)       //   |
        {
            gotoTextPos(42,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(44,5);         //  --
        for(x=22; x<27; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(44,7);         //  --
        for(x=22; x<27; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(34,8);         //  --
        for(x=17; x<21; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(26,9);         //  --
        for(x=13; x<18; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(20,12);         //  --
        for(x=10; x<14; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(18,14);         //  --
        for(x=9; x<16; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(2,13);         //  --
        for(x=1; x<6; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(10,10);         //  --
        for(x=5; x<12; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(6,8);         //  --
        for(x=3; x<10; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(2,6);         //  --
        for(x=1; x<8; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(14,2);         //  --
        for(x=7; x<10; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(14,3);         //  --
        for(x=7; x<10; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(14,4);         //  --
        for(x=7; x<10; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(4,3);         //  --
        for(x=2; x<5; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(4,4);         //  --
        for(x=2; x<6; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(22,5);         //  --
        for(x=11; x<20; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(34,3);         //  --
        for(x=17; x<20; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(34,4);         //  --
        for(x=17; x<20; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(22,6);         //  --
        for(x=11; x<14; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        gotoTextPos(22,7);         //  --
        for(x=11; x<14; x++)
        {
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=7; y<13; y++)       //   |
        {
            gotoTextPos(2,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=9; y<12; y++)       //   |
        {
            gotoTextPos(6,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=11; y<13; y++)       //   |
        {
            gotoTextPos(10,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=12; y<15; y++)       //   |
        {
            gotoTextPos(14,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=11; y<13; y++)       //   |
        {
            gotoTextPos(16,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=12; y<14; y++)       //   |
        {
            gotoTextPos(20,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=4; y<6; y++)       //   |
        {
            gotoTextPos(10,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=5; y<8; y++)       //   |
        {
            gotoTextPos(18,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=8; y<10; y++)       //   |
        {
            gotoTextPos(22,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=10; y<12; y++)       //   |
        {
            gotoTextPos(26,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=7; y<14; y++)       //   |
        {
            gotoTextPos(30,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=3; y<5; y++)       //   |
        {
            gotoTextPos(22,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=2; y<4; y++)       //   |
        {
            gotoTextPos(26,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=1; y<3; y++)       //   |
        {
            gotoTextPos(30,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        for(y=4; y<6; y++)       //   |
        {
            gotoTextPos(30,y);
            printf("��");
            Cursor[C_flag].x=getCursorX();
            Cursor[C_flag].y=getCursorY();
            C_flag++;
        }

        break;

    default:
        ;
    }
    NumC=C_flag;
}


/**--------------------------------------------------------------------------*
Name:		Wall_Start
Discribe:	Start Game Pause interface
Return:
**--------------------------------------------------------------------------*/

void Wall_Start()//��������ǽ
{

    gotoTextPos(0,0);
    setTextColor(YELLOW);
    printf("\n\n\n\n\n\n");
    printf("                          ����������                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                          ����������                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                          ����������                    \n");
    gotoTextPos(0,0);
    Sleep(800);
    printf("\n\n\n\n\n\n");
    printf("                          ����������                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                                  ��                    \n");
    printf("                          ����������                    \n");
    printf("                          ��                            \n");
    printf("                          ��                            \n");
    printf("                          ��                            \n");
    printf("                          ����������                    \n");
    gotoTextPos(0,0);
    Sleep(800);
    printf("\n\n\n\n\n\n");
    printf("                              ��                        \n");
    printf("                            ����                        \n");
    printf("                          ������                        \n");
    printf("                              ��                        \n");
    printf("                              ��                        \n");
    printf("                              ��                        \n");
    printf("                              ��                        \n");
    printf("                              ��                        \n");
    printf("                          ����������                    \n");
    gotoTextPos(0,0);
    Sleep(800);

}



/**--------------------------------------------------------------------------*
Name:		DrawSnake
Discribe:		draw snake body
Return:
**--------------------------------------------------------------------------*/
void DrawSnake(struct SNAKE *snake)//������ ��ȫ��
{
    uchar i;

    setTextColor(MEDIUM_BLUE);//�����ߵ���ɫ
    gotoTextPos(snake->body[0].x*2,snake->body[0].y);
    printf("��");
    setTextColor(YELLOW);
    for(i=1; i<snake->length; i++)
    {
        gotoTextPos(snake->body[i].x*2,snake->body[i].y);
        printf("��");
    }
}




/**--------------------------------------------------------------------------*
Name:		DrawSnakeTunnel
Discribe:		draw snake body
Return:
**--------------------------------------------------------------------------*/
void DrawSnakeTunnel(struct SNAKE *snake)//������ ��ȫ��
{
    uchar i;

    setTextColor(MEDIUM_BLUE);//�����ߵ���ɫ
    gotoTextPos(snake->body[0].x*2,snake->body[0].y);
    printf("��");
    setTextColor(YELLOW);
    for(i=1; i<snake->length; i++)
    {
        gotoTextPos(snake->body[i].x*2,snake->body[i].y);
        printf("��");
    }
}


/**--------------------------------------------------------------------------*
Name:		DrawFood
Discribe:
Return:		Null
**--------------------------------------------------------------------------*/
void DrawFood()//����ʳ��
{
    setTextColor(LIGHT_GREEN);
    gotoTextPos(food.x*2,food.y);
    printf("��");
}

/**--------------------------------------------------------------------------*
Name:		IsOver0
Discribe:
Return:
**--------------------------------------------------------------------------*/
uchar IsOver0(struct SNAKE *snake, uchar x, uchar y)
{
    //�ж��Ƿ�ײ��ǽ��Ե��Լ�
    // 	assert(NULL!=snake);
    switch(pass)
    {
    case 0:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y))
            return 1;
        else return 0;
    case 1:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((15==x)&&(6==y))||((15==x)&&(7==y))||((14==x)&&(7==y))||((13==x)&&(8==y))\
                ||((14==x)&&(8==y))||((15==x)&&(8==y))||((15==x)&&(9==y))||((15==x)&&(10==y))\
                ||((15==x)&&(11==y))||((15==x)&&(12==y))||((15==x)&&(13==y))||((13==x)&&(14==y))\
                ||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 2:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((13==x)&&(11==y))||((13==x)&&(12==y))||((13==x)&&(13==y))\
                ||((13==x)&&(14==y))||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 3:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
            return 1;
        else return 0;
    case 4:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((17==x)&&(6==y))||((13==x)&&(7==y))||((17==x)&&(7==y))\
                ||((13==x)&&(8==y))||((17==x)&&(8==y))||((13==x)&&(9==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 5:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((13==x)&&(7==y))||((13==x)&&(8==y))||((13==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
            return 1;
        else return 0;

    }
}


/**--------------------------------------------------------------------------*
Name:		IsOver1
Discribe:
Return:
**--------------------------------------------------------------------------*/
uchar IsOver1(struct SNAKE *snake, uchar x, uchar y)
{
    //�ж��Ƿ�ײ��ǽ��Ե��Լ�
    // 	assert(NULL!=snake);
    switch(model_pass)
    {
    case 0:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y))
            return 1;
        else return 0;
    case 1:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((15==x)&&(6==y))||((15==x)&&(7==y))||((14==x)&&(7==y))||((13==x)&&(8==y))\
                ||((14==x)&&(8==y))||((15==x)&&(8==y))||((15==x)&&(9==y))||((15==x)&&(10==y))\
                ||((15==x)&&(11==y))||((15==x)&&(12==y))||((15==x)&&(13==y))||((13==x)&&(14==y))\
                ||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 2:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((13==x)&&(11==y))||((13==x)&&(12==y))||((13==x)&&(13==y))\
                ||((13==x)&&(14==y))||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 3:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
            return 1;
        else return 0;
    case 4:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((17==x)&&(6==y))||((13==x)&&(7==y))||((17==x)&&(7==y))\
                ||((13==x)&&(8==y))||((17==x)&&(8==y))||((13==x)&&(9==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 5:
        if(0==x ||WIDTH-1==x|| 0==y || HEIGHT-3==y||InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((13==x)&&(7==y))||((13==x)&&(8==y))||((13==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
            return 1;
        else return 0;

    }
}


/**--------------------------------------------------------------------------*
Name:		IsOver2
Discribe:
Return:
**--------------------------------------------------------------------------*/
uchar IsOver2(struct SNAKE *snake, uchar x, uchar y)
{
    //�ж��Ƿ�ײ��ǽ��Ե��Լ�
    // 	assert(NULL!=snake);
    switch(pass)
    {
    case 0:
        if(InSnake(snake, x, y))
            return 1;
        else return 0;
    case 1:
        if(InSnake(snake, x, y)\
                ||((15==x)&&(6==y))||((15==x)&&(7==y))||((14==x)&&(7==y))||((13==x)&&(8==y))\
                ||((14==x)&&(8==y))||((15==x)&&(8==y))||((15==x)&&(9==y))||((15==x)&&(10==y))\
                ||((15==x)&&(11==y))||((15==x)&&(12==y))||((15==x)&&(13==y))||((13==x)&&(14==y))\
                ||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 2:
        if(InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((13==x)&&(11==y))||((13==x)&&(12==y))||((13==x)&&(13==y))\
                ||((13==x)&&(14==y))||((14==x)&&(14==y))||((15==x)&&(14==y))||((16==x)&&(14==y))||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 3:
        if(InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((17==x)&&(7==y))||((17==x)&&(8==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
            return 1;
        else return 0;
    case 4:
        if(InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((17==x)&&(6==y))||((13==x)&&(7==y))||((17==x)&&(7==y))\
                ||((13==x)&&(8==y))||((17==x)&&(8==y))||((13==x)&&(9==y))||((17==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y)))
            return 1;
        else return 0;
    case 5:
        if(InSnake(snake, x, y)\
                ||((13==x)&&(6==y))||((14==x)&&(6==y))||((15==x)&&(6==y))||((16==x)&&(6==y))\
                ||((17==x)&&(6==y))||((13==x)&&(7==y))||((13==x)&&(8==y))||((13==x)&&(9==y))\
                ||((17==x)&&(10==y))||((16==x)&&(10==y))||((15==x)&&(10==y))||((14==x)&&(10==y))\
                ||((13==x)&&(10==y))||((17==x)&&(11==y))||((17==x)&&(12==y))||((17==x)&&(13==y))\
                ||((17==x)&&(14==y))||((16==x)&&(14==y))||((15==x)&&(14==y))||((14==x)&&(14==y))||((13==x)&&(14==y)))
            return 1;
        else return 0;

    }
}


/**--------------------------------------------------------------------------*
Name:		IsOver3
Discribe:
Return:
**--------------------------------------------------------------------------*/
uchar IsOver3(struct SNAKE *snake, uchar x, uchar y)
{
    //�ж��Ƿ�ײ��ǽ��Ե��Լ�
    // 	assert(NULL!=snake);
    switch(model_challenge_pass)
    {
    case 0:
        if(0==x || 31==x || 0==y || 21==y || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 1:
        if(1==x || 30==x || 1==y || 20==y || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 2:
        if(2==x || 29==x || 2==y || 19==y || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 3:
        if(3==x || 28==x || 3==y || 18==y || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 4:
        if(4==x || 27==x || 4==y || 17==y || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 5:
        if(5==x || 26==x || 5==y || 16==y || InSnake(snake, x, y))
            return 1;
        else return 0;

    }
}


/**--------------------------------------------------------------------------*
Name:		IsOver4
Discribe:
Return:
**--------------------------------------------------------------------------*/
uchar IsOver4(struct SNAKE *snake, uchar x, uchar y)
{
    //�ж��Ƿ�ײ��ǽ��Ե��Լ�
    // 	assert(NULL!=snake);
    switch(model_Tunnel_pass)
    {
    case 0:
        if(IsOverTunnel(x,y) || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 1:
        if(IsOverTunnel(x,y) || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 2:
        if(IsOverTunnel(x,y) || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 3:
        if(IsOverTunnel(x,y) || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 4:
        if(IsOverTunnel(x,y) || InSnake(snake, x, y))
            return 1;
        else return 0;
    case 5:
        if(IsOverTunnel(x,y) || InSnake(snake, x, y))
            return 1;
        else return 0;

    }
}


/**--------------------------------------------------------------------------*
Name:		    IsOverTunnel
Discribe:		if in the Tunnel
Return:		TRUE,FALSE
**--------------------------------------------------------------------------*/
uchar IsOverTunnel(uchar x, uchar y)//�ж�ĳһ���Ƿ���������
{
    uchar i;
    for(i=0; i<NumC; i++)
    {
        //���ĳһ��������ĳһ������ͬ��������1
        if((x==(Cursor[i].x/2)) && (y==Cursor[i].y))
            return 1;
    }
    return 0;
}


/**--------------------------------------------------------------------------*
Name:		ShowOver
Discribe:	over interface
Return:		key
**--------------------------------------------------------------------------*/
uchar ShowOver(uint *score,uint *model_pass,uint *model_challenge_pass,uint *model_Tunnel_pass)//��ʾ�����Ľ���
{

    uchar key;
    system("cls");
    setTextColor(MEDIUM_BLUE);
    gotoTextPos(0,HEIGHT/2-10);
    printf("    * *         *       *       *   * * * *               \n");
    printf("  *            * *      **     **   *                     \n");
    printf("  * * * *     *   *     * *   * *   * * * *               \n");
    printf("  *  * *     * * * *    *  * *  *   *                     \n");
    printf("   **  *    *       *   *   *   *   * * * *               \n");
    setTextColor(LIGHT_GREEN);
    gotoTextPos(16,HEIGHT/2-2);
    printf("           - - �� �� ϧ ��");
    setTextColor(WHITE);
    gotoTextPos(16,HEIGHT/2-1);
    printf("________________________________");
    setTextColor(YELLOW);
    gotoTextPos(16,HEIGHT/2+1);
    switch(model)
    {
    case 1:
        printf("          Your Pass: %u",*model_pass);
        break;
    case 0:
        printf("          Your Score: %u",*score);
        break;
    case 2:
        printf("          Your Score: %u",*score);
        break;
    case 3:
        printf("          Your Pass: %u",*model_challenge_pass);
        break;
    case 4:
        printf("          Your Pass: %u",*model_Tunnel_pass);
        break;
    default:
        ;
    }
    setTextColor(RED);
    gotoTextPos(20,HEIGHT/2+5);
    printf("    * *     *       *   * * * *    * * *         \n");
    gotoTextPos(20,HEIGHT/2+6);
    printf("  *     *    *     *    *          *    *                 \n");
    gotoTextPos(20,HEIGHT/2+7);
    printf("  *     *     *   *     * * * *    * * *                \n");
    gotoTextPos(20,HEIGHT/2+8);
    printf("  *     *      * *      *          *  *            \n");
    gotoTextPos(20,HEIGHT/2+9);
    printf("    * *         *       * * * *    *    *            \n");
    Sleep(2000);//�ȴ�2��
    setTextColor(TEAL);

    do
    {
        //ѯ���Ƿ�����
        gotoTextPos(12,HEIGHT/2-2);
        setTextColor(RED_ORANGE);
        printf("     Press Y/N or y/n + Enter to confirm");
        setTextColor(LIGHT_GREEN);
        gotoTextPos(16,HEIGHT/2-3);
        printf("      ����������?(Y/N) �� ��    ");
        do
        {

            gotoTextPos(41,HEIGHT/2-3);
            key=getche();
            /*
            if('Y'!=key &&'y'!=key && 'N'!=key &&'n'!=key){
            gotoTextPos(21,HEIGHT/2-4);
            setTextColor(RED_ORANGE);
            printf("Please input right order!");}
            */
        }
        while('Y'!=key &&'y'!=key && 'N'!=key &&'n'!=key);
        gotoTextPos(21,HEIGHT/2-4);
        printf("                                ");
        setTextColor(LIGHT_GREEN);
    }
    while('\r'!=getch());
    if ('Y' == key||'y'==key)//����ǣ�����������ʸ���ҳ
        system ("start http://user.qzone.qq.com/472224310/main");

    do
    {
        //ѯ���Ƿ�����
        gotoTextPos(12,HEIGHT/2-2);
        setTextColor(RED_ORANGE);
        printf("     Press Y/N or y/n + Enter to confirm");
        setTextColor(LIGHT_GREEN);
        gotoTextPos(16,HEIGHT/2-3);
        printf("        ����������?(Y/N) �� ��    ");
        do
        {

            gotoTextPos(43,HEIGHT/2-3);
            key=getche();
            /*
            if('Y'!=key &&'y'!=key && 'N'!=key &&'n'!=key){
            gotoTextPos(21,HEIGHT/2-4);
            setTextColor(RED_ORANGE);
            printf("Please input right order!");}
            */
        }
        while('Y'!=key &&'y'!=key && 'N'!=key &&'n'!=key);
        gotoTextPos(21,HEIGHT/2-4);
        printf("                                 ");
        setTextColor(LIGHT_GREEN);
    }
    while('\r'!=getch());

    *score=0;
    *model_pass=0;
    *model_challenge_pass=0;
    *model_Tunnel_pass=0;
    model=0;
    return key;
}


/**--------------------------------------------------------------------------*
Name:		ShowWin
Discribe:	win interface
Return:		key
**--------------------------------------------------------------------------*/
uchar ShowWin(uint *model_pass,uint *model_challenge_pass,uint *model_Tunnel_pass)//��ʾ�����Ľ���
{
    uchar key;
    system("cls");
    setTextColor(MEDIUM_BLUE);
    gotoTextPos(0,HEIGHT/2-11);
    printf("    * *         *       *       *   * * * *               \n");
    printf("  *            * *      **     **   *                     \n");
    printf("  * * * *     *   *     * *   * *   * * * *               \n");
    printf("  *  * *     * * * *    *  * *  *   *                     \n");
    printf("   **  *    *       *   *   *   *   * * * *               \n");
    setTextColor(LIGHT_GREEN);
    gotoTextPos(16,HEIGHT/2-1);
    printf("   b(������)d��ϲ������ʤ�� ��");
    setTextColor(WHITE);
    gotoTextPos(16,HEIGHT/2);
    printf("________________________________");
    setTextColor(YELLOW);
    gotoTextPos(16,HEIGHT/2+1);
    switch(model)
    {
    case 1:
        printf("          Your Pass: %u",*model_pass);
        break;
    case 3:
        printf("          Your Pass: %u",*model_challenge_pass);
        break;
    case 4:
        printf("          Your Pass: %u",*model_Tunnel_pass);
        break;
    }
    setTextColor(RED);
    gotoTextPos(20,HEIGHT/2+5);
    printf("  *       *       *    * * *     **    *                \n");
    gotoTextPos(20,HEIGHT/2+6);
    printf("   *     * *     *       *       * *   *                \n");
    gotoTextPos(20,HEIGHT/2+7);
    printf("    *   *   *   *        *       *  *  *                \n");
    gotoTextPos(20,HEIGHT/2+8);
    printf("     * *     * *         *       *   * *                \n");
    gotoTextPos(20,HEIGHT/2+9);
    printf("      *       *        * * *     *    **                \n");
    Sleep(2000);//�ȴ�2��
    setTextColor(TEAL);

    do
    {
        //ѯ���Ƿ�����
        gotoTextPos(12,HEIGHT/2-2);
        setTextColor(RED_ORANGE);
        printf("     Press Y/N or y/n + Enter to confirm");
        setTextColor(LIGHT_GREEN);
        gotoTextPos(16,HEIGHT/2-1);
        printf("                                ");
        gotoTextPos(16,HEIGHT/2);
        printf("                                 ");
        gotoTextPos(16,HEIGHT/2-3);
        printf("      ����������?(Y/N) �� ��    ");

        do
        {
            gotoTextPos(41,HEIGHT/2-3);
            key=getche();
            /*
            if('Y'!=key &&'y'!=key && 'N'!=key &&'n'!=key){
            gotoTextPos(21,HEIGHT/2-4);
            setTextColor(RED_ORANGE);
            printf("Please input right order!");}
            */
        }
        while('Y'!=key &&'y'!=key && 'N'!=key &&'n'!=key);
        gotoTextPos(21,HEIGHT/2-4);
        printf("                                ");
        setTextColor(LIGHT_GREEN);
    }
    while('\r'!=getch());
    if ('Y' == key||'y'==key)//����ǣ�����������ʸ���ҳ
        system ("start http://user.qzone.qq.com/472224310/main");

    do
    {
        //ѯ���Ƿ�����
        gotoTextPos(12,HEIGHT/2-2);
        setTextColor(RED_ORANGE);
        printf("     Press Y/N or y/n + Enter to confirm");
        setTextColor(LIGHT_GREEN);
        gotoTextPos(16,HEIGHT/2-3);
        printf("        ����������?(Y/N) �� ��    ");

        do
        {
            gotoTextPos(43,HEIGHT/2-3);
            key=getche();
            /*
            if('Y'!=key &&'y'!=key && 'N'!=key &&'n'!=key){
            gotoTextPos(21,HEIGHT/2-4);
            setTextColor(RED_ORANGE);
            printf("Please input right order!");}
            */
        }
        while('Y'!=key &&'y'!=key && 'N'!=key &&'n'!=key);
        gotoTextPos(21,HEIGHT/2-4);
        printf("                                 ");
        setTextColor(LIGHT_GREEN);
    }
    while('\r'!=getch());

    *model_pass=0;
    *model_challenge_pass=0;
    *model_Tunnel_pass=0;
    model=0;
    return key;
}


#endif // FUNCTIONDEFINTION_H_INCLUDED
