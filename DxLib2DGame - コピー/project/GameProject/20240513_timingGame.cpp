#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
//定数
#define SCREEN_X 800
#define SCREEN_Y 600
#define CIRCLE_POS_X 400
#define CIRCLE_POS_Y 300
#define CIRCLE_RADIUS_START 10
#define CIRCLE_RADIUS_MAX 200

//変数
typedef struct circle
{
    int posX;
    int posY;
    int radius;
    double area;
}circle;

//ゲームフラグ
bool enterPressedLastFrame = false;     //エンターキーが押されたかどうかのフラグ
bool gameStartFlag = false;             //ゲーム開始フラグ
bool circleGenerationFlag = true;       //円の生成フラグ
bool gameEndFlag = true;                //ゲーム終了フラグ

//ゲームカウント
int enterPressCount;
//構造体を変数にする
circle Circle;
//円の最大面積
double circleAreaMax = M_PI * CIRCLE_RADIUS_MAX * CIRCLE_RADIUS_MAX;

//メイン関数
int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)//Windowsのメインで動かす
{
    //---------------------------//
    // 基本設定
    //---------------------------//
    ChangeWindowMode(TRUE);//Windowsの画面をアクティブにする
    DxLib_Init();//DxLibの初期化
    SetMainWindowText("タイミングゲーム");
    SetDrawScreen(DX_SCREEN_BACK);//画面の背景は黒
    SetGraphMode(SCREEN_X, SCREEN_Y, 32);//画面の大きさ

    //DxLibの初期化処理
    if (DxLib_Init() == -1)
    {
        //エラーが起きたら直ちに終了
        return -1;
    }
    //色指定
    int CircleColor = GetColor(128, 128, 128);
    //円の大きさを指定
    Circle.posX = CIRCLE_POS_X;
    Circle.posY = CIRCLE_POS_Y;
    Circle.radius = CIRCLE_RADIUS_START;

    //---------------------------//
    // ゲームループ
    //---------------------------//

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ClearDrawScreen() == 0)
    {

        //画面の初期化
        ClearDrawScreen();
        if (CheckHitKey(KEY_INPUT_RETURN) && !enterPressedLastFrame)
        {
            gameStartFlag = !gameStartFlag;
        }
        enterPressedLastFrame = CheckHitKey(KEY_INPUT_ESCAPE);
        //円の変化をつける
        if (gameStartFlag)
        {
            //大きくする
            if (CheckHitKey(KEY_INPUT_UP))
            {
                Circle.radius +=1;
            }
            if (Circle.radius >= CIRCLE_RADIUS_MAX)
            {
                circleGenerationFlag = false;
            }
            //小さくする
            if (CheckHitKey(KEY_INPUT_DOWN))
            {
                Circle.radius -= 1;
            }
            if (Circle.radius <= CIRCLE_RADIUS_START)
            {
                circleGenerationFlag = false;
            }
        }
        //円の描画
        DrawCircle(Circle.posX, Circle.posY, Circle.radius, CircleColor,TRUE);


        //裏画面の内容を表画面に反映させる
        ScreenFlip();
        WaitTimer(1000 / 60);


    }

    //Dxlib終了処理
    DxLib_End();

    return 0;
}