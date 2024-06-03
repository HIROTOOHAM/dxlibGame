#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>


//定数
#define SCREEN_X 800
#define SCREEN_Y 600
#define CIRCLE_POS_X 400
#define CIRCLE_POS_Y 300
#define CIRCLE_RADIUS 10
#define CIRCLE_RADIUS_MAX 100

//変数
typedef struct circle
{
    int posX;
    int posY;
    int radius;
}circle;

//ゲームプラグ
bool enterPressedLastFrame = false;//エンターキーが押されたかどうかのフラグ
bool gameStartFlag = false;//ゲーム開始フラグ
bool circleGenerationFlag = true;//円の生成フラグ
bool gameEndFlag = true;//ゲーム終了フラグ

//ゲームカウント
int enterPressCount;
//構造体を変数にする
circle circle1;
//円の最大面積
double circleAreaMax = M_PI * CIRCLE_RADIUS_MAX * CIRCLE_RADIUS_MAX;

//メイン関数
int Winmain(HINSTANCE, HINSTANCE, LPSTR, int)//WIndowsのメインで動かす
{
    //基本設定
    ChangeWindowMode(TRUE);//Windowsの画面をアクティブにする
    DxLib_Init();//DxLibの初期化
    SetMainWindowText("タイミングゲーム");
    SetDrawScreen(DX_SCREEN_BACK);//画面の背景は黒
    SetGraphMode(800, 600, 32);//画面の大きさ

    //Dxlibの初期化処理
    if (DxLib_Init() == -1)
    {
        //エラーが起きたら終了

        return -1;
    }
    //色の指定
    int circleColor = GetColor(128, 128, 128);
    //円の描画
    circle1.posX = CIRCLE_POS_X;
    circle1.posY = CIRCLE_POS_Y;
    circle1.radius = CIRCLE_RADIUS;

    //ゲームループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();

        DrawCircle(circle1.posX, circle1.posY, circle1.radius, GetColor(0, 0, 255), TRUE);
        if (CheckHitKey(KEY_INPUT_UP))
        {
            circle1.radius += 1;
        }


    }
    //DxLib終了処理
    DxLib_End();

    return 0;
}