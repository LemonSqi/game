/*****************************************************************************
** File Name:        Snake
** Author:           SiQi_Wang
** Date:             2016/08/15
** Version:          6.1
** Description:      Snake game
******************************************************************************
**                         Important Edit History                            *
** --------------------------------------------------------------------------*
** DATE           NAME             DESCRIPTION                               *
** 2016/08/15    SiQi_Wang             Create                                *
******************************************************************************/

/*---------------------------------------------------------------------------*
**                         Include Files                                     *
**-------------------------------------------------------------------- ------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "FunctionDefintion.h"
#include"conio.h"

//#include<assert.h>
//#define _WIN32_WINNT 0x0500 // for GetConsoleFontSize(), XP and up
//#pragma comment(lib, "winmm.lib")

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


/******************************************************************************
**                              Main Function                                 *
** ---------------------------------------------------------------------------*
** This function is programming entrance which is able to easily make you know*
** the run process of program.                                                *
*******************************************************************************/

int main (void)
{
    uchar level=0,flag,nofood=1,pause=0,choose=9;
    uint score=0;
    uint j = 0;
    uint k=0;
    uint k2=0;
    uint flag2=1;
    uint flag3=1;
    uint flag4=1;
    uint Numfood=0;
    uint Numfood2=0;

    struct SNAKE snake = {5,{0,0},R}; //赋与初值,初始化变量

    //fixConsoleSize(WIDTH*2,HEIGHT*1);//设置窗口大小
    setCursorVisible(FALSE);//设置光标宽度为零，不显示光标
    setConsoleTitle(" My Snake Game QQ :472224310 Author :SiQi_Wang");//设置窗口标题
    SetConsoleFont = (PROCSETCONSOLEFONT)GetProcAddress(GetModuleHandle("kernel32"),"SetConsoleFont");
    SetConsoleFont(GetStdHandle (STD_OUTPUT_HANDLE),12);
    //	SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE),30);
    //	PlaySound("C:\\Users\\王思琦\\Desktop\\yyy.wav",NULL,SND_ASYNC|SND_FILENAME);
    //HMODULE hKernel32 = GetModuleHandle("kernel32");
    // GetConsoleFontInfo = (PROCGETCONSOLEFONTINFO)GetProcAddress(hKernel32,"GetConsoleFontInfo");
    //GetConsoleFontSize = (PROCGETCONSOLEFONTSIZE)GetProcAddress(hKernel32,"GetConsoleFontSize");
    //GetNumberOfConsoleFonts = (PROCGETNUMBEROFCONSOLEFONTS)GetProcAddress(hKernel32,"GetNumberOfConsoleFonts");
    //GetCurrentConsoleFont = (PROCGETCURRENTCONSOLEFONT)GetProcAddress(hKernel32,"GetCurrentConsoleFont");

Play:

    flag=Menu();//首先显示菜单
    //  Menu();
    if (!flag)//如果返回零，退出游戏
        return 0;

    /*-----------------------------------------------------------------------------
    利用switch控制Model选择，以此实现不同的模式切换
    Classical or Pass Model :    Model=0,1,2,3,4
    -----------------------------------------------------------------------------*/
    switch(model)
    {
    /*===========================================================================*/
    case 0:
        system("cls");//清屏以显示游戏界面
        Wall_Start();//暂停3秒启动游戏
        system("cls");//再清屏
        InitSnake(&snake);//初始化蛇
        nofood = InitFood0(&snake);//初始化食物

        DrawSnake(&snake);//画出蛇
        switch(pass)
        {
        case 0:
            DrawWall_0();
            break;//画出第0关围墙
        case 1:
            DrawWall_1();
            break;//画出第1关围墙
        case 2:
            DrawWall_2();
            break;//画出第2关围墙
        case 3:
            DrawWall_3();
            break;//画出第3关围墙
        case 4:
            DrawWall_4();
            break;//画出第4关围墙
        case 5:
            DrawWall_5();
            break;//画出第5关围墙
        }
        DrawFood();//画出食物
        Sleep(500);
        do
        {
            if(pause)
            {
                //如果暂停
                ShowPause();//显示暂停界面
                pause = 0;//当从暂停界面退出时，pause赋为0，表示没有暂停
                system("cls");//将暂停界面清屏

                switch(pass)
                {
                case 0:
                    DrawWall_0();
                    break;//画出第0关围墙
                case 1:
                    DrawWall_1();
                    break;//画出第1关围墙
                case 2:
                    DrawWall_2();
                    break;//画出第2关围墙
                case 3:
                    DrawWall_3();
                    break;//画出第3关围墙
                case 4:
                    DrawWall_4();
                    break;//画出第4关围墙
                case 5:
                    DrawWall_5();
                    break;//画出第5关围墙
                }
                DrawSnake(&snake);//画出蛇
                DrawFood();//画出食物
            }
            if (nofood)
            {
                // had eaten food如果吃到了食物
                nofood = InitFood0(&snake);//重新初始化食物
                score=score+(50+2*(diff-1)+10*(pass-1));//加分
                DrawFood();//再画出食物
            }
            if(level<=18)//calculate level如果不大于12级
                level=diff+(snake.length-5)/10;//计算等级
            setTextColor(GREY);//设置文本颜色
            gotoTextPos(0,HEIGHT-1);//光标定位，并输出分数
            printf(" score:%u",score);
            gotoTextPos(WIDTH,HEIGHT-1);//光标定位，并输出等级
            printf("level:%u",level);
            setTextColor(TEAL);
            gotoTextPos(1,HEIGHT-2);//光标定位，并输出分数
            printf("        Press ESC to return to the first interface");

            Sleep(CALTIME(level));//snake's vilocity,暂停一段时间，这里是蛇的运动速度
            if (jkHasKey())
            {
                //扫描是否有按键按下
                switch(jkGetKey())
                {
                //如果有，看是什么键
                case JK_UP://上方向键时
                    if(snake.direction != D)//如果蛇不向下运动，蛇运动方向为上
                        snake.direction = U;
                    break;
                case JK_DOWN:
                    if(snake.direction!=U)//同上
                        snake.direction = D;
                    break;
                case JK_LEFT:
                    if(snake.direction!=R)
                        snake.direction = L;
                    break;
                case JK_RIGHT:
                    if(snake.direction!= L)
                        snake.direction = R;
                    break;
                case JK_ESC:
                    score = 0;;
                    goto Play;
                    break;
                case JK_ENTER:
                    pause = 1;//按回车表示暂停
                default: ;//其它按键忽略
                }
            }
            nofood= MoveSnake(&snake);//移动蛇，并返回是否吃到食物或游戏结束
        }
        while(OVER!=nofood);
        pass=0;
        diff=1;
        switch(ShowOver(&score,&model_pass,&model_challenge_pass,&model_Tunnel_pass))
        {
        case 'Y':
            goto Play;
            break;
        case 'y':
            goto Play;
            break;
        default:
            ;
        }
        break;

        /*===========================================================================*/

    case 1:
        system("cls");//清屏以显示游戏界面
        Wall_Start();//暂停3秒启动游戏
        do
        {
            system("cls");//清屏以显示游戏界面
            InitSnake(&snake);//初始化蛇
            nofood = InitFood1(&snake);//初始化食物

            switch(model_pass)
            {
            case 0:
                DrawWall_0();
                break;//画出第0关围墙
            case 1:
                DrawWall_1();
                break;//画出第1关围墙
            case 2:
                DrawWall_2();
                break;//画出第2关围墙
            case 3:
                DrawWall_3();
                break;//画出第3关围墙
            case 4:
                DrawWall_4();
                break;//画出第4关围墙
            case 5:
                DrawWall_5();
                break;//画出第5关围墙
            }
            DrawSnake(&snake);//画出蛇
            DrawFood();//画出食物
            Sleep(500);

            do
            {

                if(pause)
                {
                    //如果暂停
                    ShowPause();//显示暂停界面
                    pause = 0;//当从暂停界面退出时，pause赋为0，表示没有暂停
                    system("cls");//将暂停界面清屏

                    switch(model_pass)
                    {
                    case 0:
                        DrawWall_0();
                        break;//画出第0关围墙
                    case 1:
                        DrawWall_1();
                        break;//画出第1关围墙
                    case 2:
                        DrawWall_2();
                        break;//画出第2关围墙
                    case 3:
                        DrawWall_3();
                        break;//画出第3关围墙
                    case 4:
                        DrawWall_4();
                        break;//画出第4关围墙
                    case 5:
                        DrawWall_5();
                        break;//画出第5关围墙
                    }

                    DrawSnake(&snake);//画出蛇
                    DrawFood();//画出食物
                }
                if (nofood)
                {
                    k++;
                    Numfood++;
                    // had eaten food如果吃到了食物
                    nofood = InitFood1(&snake);//重新初始化食物
                    DrawFood();//再画出食物
                }

                if(k==8)
                    model_pass++;

                if(k==8)
                    break;

                setTextColor(GREY);//设置文本颜色
                gotoTextPos(0,HEIGHT-1);//光标定位，并输出关卡数
                printf(" Pass Level:%u",model_pass+1);
                gotoTextPos(WIDTH,HEIGHT-1);//光标定位，并输出等级
                printf("Numfood:%u",Numfood);
                setTextColor(TEAL);
                gotoTextPos(1,HEIGHT-2);
                printf("        Press ESC to return to the first interface");

                Sleep(CALTIME(speed));//snake's vilocity,暂停一段时间，这里是蛇的运动速度


                if (jkHasKey())
                {
                    //扫描是否有按键按下
                    switch(jkGetKey())
                    {
                    //如果有，看是什么键
                    case JK_UP://上方向键时
                        if(snake.direction != D)//如果蛇不向下运动，蛇运动方向为上
                            snake.direction = U;
                        break;
                    case JK_DOWN:
                        if(snake.direction!=U)//同上
                            snake.direction = D;
                        break;
                    case JK_LEFT:
                        if(snake.direction!=R)
                            snake.direction = L;
                        break;
                    case JK_RIGHT:
                        if(snake.direction!= L)
                            snake.direction = R;
                        break;
                    case JK_ESC:
                        model_pass = 0;
                        Numfood=0;
                        speed=1;
                        k=0;
                        goto Play;
                        break;
                    case JK_ENTER:
                        pause = 1;//按回车表示暂停
                    default: ;//其它按键忽略
                    }
                }
                nofood= MoveSnake(&snake);//移动蛇，并返回是否吃到食物或游戏结束

            }
            while(OVER!=nofood);

            if(k!=8)
            {
                k=0;
                Numfood=0;
                speed=1;
                switch(ShowOver(&score,&model_pass,&model_challenge_pass,&model_Tunnel_pass))
                {
                case 'Y':
                    goto Play;
                    break;
                case 'y':
                    goto Play;
                    break;
                default:
                    ;
                }
                flag2=0; //修复退出BUG
            }
            k=0;
            if(flag2==0)
                break;
        }
        while(model_pass<6);
        model_pass=0;
        speed=1;
        Numfood=0;
        model=0;
        if(flag2==1)
            switch(ShowWin(&model_pass,&model_challenge_pass,&model_Tunnel_pass))
            {
            case 'Y':
                goto Play;
                break;
            case 'y':
                goto Play;
                break;
            default:
                ;
            }
        flag2=1;
        break;

        /*===========================================================================*/

    case 2:
        system("cls");//清屏以显示游戏界面
        Wall_Start();//暂停3秒启动游戏
        system("cls");//再清屏
        InitSnake(&snake);//初始化蛇
        nofood = InitFood2(&snake);//初始化食物

        DrawSnake(&snake);//画出蛇
        switch(pass)
        {
        case 0:
            DrawWall_0();
            break;//画出第0关围墙
        case 1:
            DrawWall_1();
            break;//画出第1关围墙
        case 2:
            DrawWall_2();
            break;//画出第2关围墙
        case 3:
            DrawWall_3();
            break;//画出第3关围墙
        case 4:
            DrawWall_4();
            break;//画出第4关围墙
        case 5:
            DrawWall_5();
            break;//画出第5关围墙
        }
        DrawFood();//画出食物
        Sleep(500);
        do
        {
            if(pause)
            {
                //如果暂停
                ShowPause();//显示暂停界面
                pause = 0;//当从暂停界面退出时，pause赋为0，表示没有暂停
                system("cls");//将暂停界面清屏

                switch(pass)
                {
                case 0:
                    DrawWall_0();
                    break;//画出第0关围墙
                case 1:
                    DrawWall_1();
                    break;//画出第1关围墙
                case 2:
                    DrawWall_2();
                    break;//画出第2关围墙
                case 3:
                    DrawWall_3();
                    break;//画出第3关围墙
                case 4:
                    DrawWall_4();
                    break;//画出第4关围墙
                case 5:
                    DrawWall_5();
                    break;//画出第5关围墙
                }
                DrawSnake(&snake);//画出蛇
                DrawFood();//画出食物
            }
            if (nofood)
            {
                // had eaten food如果吃到了食物
                nofood = InitFood2(&snake);//重新初始化食物
                score=score+(50+2*(diff-1)+10*(pass-1));//加分
                DrawFood();//再画出食物
            }
            if(level<=18)//calculate level如果不大于12级
                level=diff+(snake.length-5)/10;//计算等级
            setTextColor(GREY);//设置文本颜色
            gotoTextPos(0,HEIGHT-1);//光标定位，并输出分数
            printf(" score:%u",score);
            gotoTextPos(WIDTH,HEIGHT-1);//光标定位，并输出等级
            printf("level:%u",level);
            setTextColor(TEAL);
            gotoTextPos(1,HEIGHT-2);//光标定位，并输出分数
            printf("        Press ESC to return to the first interface");

            Sleep(CALTIME(level));//snake's vilocity,暂停一段时间，这里是蛇的运动速度
            if (jkHasKey())
            {
                //扫描是否有按键按下
                switch(jkGetKey())
                {
                //如果有，看是什么键
                case JK_UP://上方向键时
                    if(snake.direction != D)//如果蛇不向下运动，蛇运动方向为上
                        snake.direction = U;
                    break;
                case JK_DOWN:
                    if(snake.direction!=U)//同上
                        snake.direction = D;
                    break;
                case JK_LEFT:
                    if(snake.direction!=R)
                        snake.direction = L;
                    break;
                case JK_RIGHT:
                    if(snake.direction!= L)
                        snake.direction = R;
                    break;
                case JK_ESC:
                    score = 0;;
                    goto Play;
                    break;
                case JK_ENTER:
                    pause = 1;//按回车表示暂停
                default: ;//其它按键忽略
                }
            }
            nofood= MoveSnake2(&snake);//移动蛇，并返回是否吃到食物或游戏结束
        }
        while(OVER!=nofood);
        pass=0;
        diff=1;
        model=0;
        switch(ShowOver(&score,&model_pass,&model_challenge_pass,&model_Tunnel_pass))
        {
        case 'Y':
            goto Play;
            break;
        case 'y':
            goto Play;
            break;
        default:
            ;
        }
        break;

        /*===========================================================================*/

    case 3:
        system("cls");//清屏以显示游戏界面
        Wall_Start();//暂停3秒启动游戏
        system("cls");//清屏以显示游戏界面
        InitSnake(&snake);//初始化蛇
        DrawWall_challenge();//画围墙
        do
        {
            nofood = InitFood_Challenge(&snake);//初始化食物
            DrawSnake(&snake);//画出蛇
            DrawWall_challenge();
            DrawFood();//画出食物
            do
            {

                if(pause)
                {
                    //如果暂停
                    ShowPause();//显示暂停界面
                    pause = 0;//当从暂停界面退出时，pause赋为0，表示没有暂停
                    system("cls");//将暂停界面清屏
                    DrawWall_challenge();//画围墙
                    DrawSnake(&snake);//画出蛇
                    DrawFood();//画出食物
                }
                if (nofood)
                {
                    k2++;
                    Numfood2++;
                    // had eaten food如果吃到了食物
                    nofood = InitFood_Challenge(&snake);//重新初始化食物
                    DrawFood();//再画出食物
                }

                if(k2==5)
                    model_challenge_pass++;

                if(k2==5)
                    break;

                setTextColor(GREY);//设置文本颜色
                gotoTextPos(0,HEIGHT-1);//光标定位，并输出关卡数
                printf(" Pass Level:%u",model_challenge_pass+1);
                gotoTextPos(WIDTH,HEIGHT-1);//光标定位，并输出等级
                printf("Numfood:%u",Numfood2);
                setTextColor(TEAL);
                gotoTextPos(1,HEIGHT-2);
                printf("        Press ESC to return to the first interface");

                Sleep(CALTIME(speed));//snake's vilocity,暂停一段时间，这里是蛇的运动速度


                if (jkHasKey())
                {
                    //扫描是否有按键按下
                    switch(jkGetKey())
                    {
                    //如果有，看是什么键
                    case JK_UP://上方向键时
                        if(snake.direction != D)//如果蛇不向下运动，蛇运动方向为上
                            snake.direction = U;
                        break;
                    case JK_DOWN:
                        if(snake.direction!=U)//同上
                            snake.direction = D;
                        break;
                    case JK_LEFT:
                        if(snake.direction!=R)
                            snake.direction = L;
                        break;
                    case JK_RIGHT:
                        if(snake.direction!= L)
                            snake.direction = R;
                        break;
                    case JK_ESC:
                        model_challenge_pass = 0;
                        k2=0;
                        flag3=1;
                        speed=1;
                        Numfood2=0;
                        goto Play;
                        break;
                    case JK_ENTER:
                        pause = 1;//按回车表示暂停
                    default: ;//其它按键忽略
                    }
                }
                nofood= MoveSnake(&snake);//移动蛇，并返回是否吃到食物或游戏结束

            }
            while(OVER!=nofood);

            if(k2!=5)
            {
                k2=0;
                speed=1;
                switch(ShowOver(&score,&model_pass,&model_challenge_pass,&model_Tunnel_pass))
                {
                case 'Y':
                    goto Play;
                    break;
                case 'y':
                    goto Play;
                    break;
                default:
                    ;
                }
                flag3=0; //修复退出BUG
            }
            system("cls");
            k2=0;
            if(flag3==0)
                break;
        }
        while(model_challenge_pass<6);


        if(flag3==1)
            switch(ShowWin(&model_pass,&model_challenge_pass,&model_Tunnel_pass))
            {
            case 'Y':
                goto Play;
                break;
            case 'y':
                goto Play;
                break;
            default:
                ;
            }
        speed=1;
        Numfood2=0;
        model=0;
        flag3=1;
        model_challenge_pass=0;
        break;

        /*===========================================================================*/

    case 4:
        system("cls");//清屏以显示游戏界面
        Wall_Start();//暂停3秒启动游戏
        system("cls");//再清屏
        InitSnakeTunnel(&snake);//初始化蛇
        //   nofood = InitFood2(&snake);//初始化食物
        DrawTunnel();

        do
        {

            DrawSnakeTunnel(&snake);//画出蛇
            DrawTunnel();
            do
            {

                if(pause)
                {
                    //如果暂停
                    ShowPause();//显示暂停界面
                    pause = 0;//当从暂停界面退出时，pause赋为0，表示没有暂停
                    system("cls");//将暂停界面清屏

                    DrawTunnel();
                    DrawSnakeTunnel(&snake);//画出蛇

                }

                /*---------------------------------------------------------------------- **
                /*                 Tunnel Model Console Group                            **
                **  This condition is to control the Snake's cross Tunnel to change with **
                **  the Snake's moving.                                                  **
                **  case 1: (snake.body[0].x==0) && (snake.direction==L) ->              **
                **  case 2: (snake.body[0].x==31) && (snake.direction==R) ->              **
                **  case 3: (snake.body[0].y==0) && (snake.direction==U) ->              **
                **  case 4: (snake.body[0].x==21) && (snake.direction==D) ->              **
                **-----------------------------------------------------------------------*/

                //---------------------------------case 1----------------------------------//
                if((snake.body[0].x==0) && (snake.direction==L) )
                {
                    model_Tunnel_pass++;
                    gotoTextPos((snake.body[4].x)*2,snake.body[4].y);//光标定位到原来蛇尾位置
                    printf("　");//将它擦除
                    snake.body[0].x=31;
                    for(j=1; j<5; j++)
                        snake.body[j].x=j-1;

                }

                if((snake.body[0].x==31) && (snake.direction==L))
                {
                    gotoTextPos((snake.body[4].x)*2,snake.body[4].y);//光标定位到原来蛇尾位置
                    printf("　");//将它擦除

                    snake.body[0].x=30;
                    snake.body[1].x=31;
                    snake.body[2].x=0;
                    snake.body[3].x=1;
                    snake.body[4].x=2;
                    //	delayMS(1000);
                    break;
                }


                //---------------------------------case 2----------------------------------//
                if((snake.body[0].x==31) && (snake.direction==R) )
                {
                    model_Tunnel_pass++;
                    gotoTextPos((snake.body[4].x)*2,snake.body[4].y);//光标定位到原来蛇尾位置
                    printf("　");//将它擦除
                    snake.body[0].x=0;
                    for(j=1; j<5; j++)
                        snake.body[j].x=32-j;

                }

                if((snake.body[0].x==0) && (snake.direction==R))
                {
                    gotoTextPos((snake.body[4].x)*2,snake.body[4].y);//光标定位到原来蛇尾位置
                    printf("　");//将它擦除

                    snake.body[0].x=1;
                    snake.body[1].x=0;
                    snake.body[2].x=31;
                    snake.body[3].x=30;
                    snake.body[4].x=29;
                    //	delayMS(1000);
                    break;
                }


                //---------------------------------case 3----------------------------------//
                if((snake.body[0].y==0) && (snake.direction==U))
                {
                    model_Tunnel_pass++;
                    gotoTextPos((snake.body[4].x)*2,snake.body[4].y);//光标定位到原来蛇尾位置
                    printf("　");//将它擦除
                    snake.body[0].y=21;
                    for(j=1; j<5; j++)
                        snake.body[j].y=j-1;

                }

                if((snake.body[0].y==21) && (snake.direction==U))
                {
                    gotoTextPos((snake.body[4].x)*2,snake.body[4].y);//光标定位到原来蛇尾位置
                    printf("　");//将它擦除

                    snake.body[0].y=20;
                    snake.body[1].y=21;
                    snake.body[2].y=0;
                    snake.body[3].y=1;
                    snake.body[4].y=2;
                    //	delayMS(1000);
                    break;
                }

                //---------------------------------case 4----------------------------------//
                if((snake.body[0].y==21) && (snake.direction==D))
                {
                    model_Tunnel_pass++;
                    gotoTextPos((snake.body[4].x)*2,snake.body[4].y);//光标定位到原来蛇尾位置
                    printf("　");//将它擦除
                    snake.body[0].y=0;
                    for(j=1; j<5; j++)
                        snake.body[j].y=22-j;

                }

                if((snake.body[0].y==0) && (snake.direction==D))
                {
                    gotoTextPos((snake.body[4].x)*2,snake.body[4].y);//光标定位到原来蛇尾位置
                    printf("　");//将它擦除

                    snake.body[0].y=1;
                    snake.body[1].y=0;
                    snake.body[2].y=21;
                    snake.body[3].y=20;
                    snake.body[4].y=19;
                    //	delayMS(1000);
                    break;
                }

                //---------------------------------CONDITION--------------------------------//

                setTextColor(GREY);//设置文本颜色
                gotoTextPos(0,HEIGHT-1);//光标定位，并输出关卡数
                printf(" Tunnel Level:%u",model_Tunnel_pass+1);

                setTextColor(TEAL);
                gotoTextPos(1,HEIGHT-2);//光标定位，并输出分数
                printf("        Press ESC to return to the first interface");

                Sleep(CALTIME(speed));//snake's vilocity,暂停一段时间，这里是蛇的运动速度
                if (jkHasKey())
                {
                    //扫描是否有按键按下
                    switch(jkGetKey())
                    {
                    //如果有，看是什么键
                    case JK_UP://上方向键时
                        if(snake.direction != D)//如果蛇不向下运动，蛇运动方向为上
                            snake.direction = U;
                        break;
                    case JK_DOWN:
                        if(snake.direction!=U)//同上
                            snake.direction = D;
                        break;
                    case JK_LEFT:
                        if(snake.direction!=R)
                            snake.direction = L;
                        break;
                    case JK_RIGHT:
                        if(snake.direction!= L)
                            snake.direction = R;
                        break;
                    case JK_ESC:
                        model_Tunnel_pass = 0;
                        speed=1;
                        flag4=1;
                        goto Play;
                        break;
                    case JK_ENTER:
                        pause = 1;//按回车表示暂停
                    default: ;//其它按键忽略
                    }
                }
                nofood= MoveSnakeTunnel(&snake);//移动蛇，并返回是否吃到食物或游戏结束
            }
            while(OVER!=nofood);

            if(!(((snake.body[0].x==30) && (snake.direction==L)) || ((snake.body[0].x==1) && (snake.direction==R)) \
                    || ((snake.body[0].y==20) && (snake.direction==U)) || ((snake.body[0].y==1) && (snake.direction==D)) ))
            {
                speed=1;
                switch(ShowOver(&score,&model_pass,&model_challenge_pass,&model_Tunnel_pass))
                {
                case 'Y':
                    goto Play;
                    break;
                case 'y':
                    goto Play;
                    break;
                default:
                    ;
                }
                flag4=0;
                //修复退出BUG
            }
            system("cls");

            //
            if(flag4==0)
                break;
        }
        while(model_Tunnel_pass<6);

        if(flag4==1)
        {
            speed=1;
            switch(ShowWin(&model_pass,&model_challenge_pass,&model_Tunnel_pass))
            {
            case 'Y':
                goto Play;
                break;
            case 'y':
                goto Play;
                break;
            default:
                ;
            }
            speed=1;
            model=0;
            flag4=1;
            model_Tunnel_pass=0;
            break;

        }    //switch 模式选择

        return 0;
    }
}
