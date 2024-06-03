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
#define RESULT_STRING_X 15
#define RESULT_STRING_Y 15

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
bool gameEndFlag = false;               //ゲーム終了フラグ
bool enterPressAllowed = true;          //エンターキーを押されているかを許可するフラグ

//ゲームカウント
int enterPressCount;
//構造体を変数にする
circle Circle;
//円の最大面積
double circleAreaMax = M_PI * CIRCLE_RADIUS_MAX * CIRCLE_RADIUS_MAX;
//円の面積割合
double circlePorpotoin = 0.0f;

//フレームカウント
double frameCount = 0;
//デルタ時間
int prevCount, nowCout;



//メイン関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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
    int resultColor = GetColor(255, 255, 255);
    //円の大きさを指定
    Circle.posX = CIRCLE_POS_X;
    Circle.posY = CIRCLE_POS_Y;
    Circle.radius = CIRCLE_RADIUS_START;
    //フレームカウント初期化
    nowCout = prevCount = GetNowCount();

    //---------------------------//
    // ゲームループ
    //---------------------------//

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ClearDrawScreen() == 0)
    {
        //時間を獲得
        nowCout = GetNowCount();
        //デルタタイム
        double deltaTime = (nowCout - prevCount) / 1000.0f;

        //フレームカウントに追加
        frameCount += deltaTime;

        //画面の初期化
        ClearDrawScreen();

        //エンターキーを押してゲームをスタート

        if (enterPressAllowed && CheckHitKey(KEY_INPUT_RETURN) && !enterPressedLastFrame)
        {
            enterPressCount++;
            if (enterPressCount % 2 == 1)
            {
                //ゲームの開始
                gameStartFlag = true;
                gameEndFlag = false;
            }
            else
            {
                //ゲームの終了フラグ
                gameEndFlag = true;
                gameStartFlag = false;
                enterPressAllowed = false;
            }
        }
        //エンターキーが押されたかを記憶させる
        enterPressedLastFrame = CheckHitKey(KEY_INPUT_RETURN);
        //終了フラグがfalseであれば
        if (!gameEndFlag)
        {
            //円の変化をつける
            if (gameStartFlag)
            {
                if (frameCount >= 1.0f / 60.f)
                {
                    frameCount = 0;
                    //大きくする
                    if (circleGenerationFlag)
                    {
                        //半径を5ずつ増やす
                        Circle.radius += 5;
                        //半径が最大値になったときフラグを変換
                        if (Circle.radius >= CIRCLE_RADIUS_MAX)
                        {
                            circleGenerationFlag = false;
                        }
                    }
                    //半径を5ずつ減らす
                    else
                    {
                        Circle.radius -= 5;
                        //半径が最小値になったらフラグを変換
                        if (Circle.radius <= CIRCLE_RADIUS_START)
                        {
                            circleGenerationFlag = true;
                        }

                    }

                }
            }
        }
        else
        {
            //リザルトを出力
            Circle.area = M_PI * (double)Circle.radius * (double)Circle.radius;
            //面積の割合計算
            circlePorpotoin = Circle.area / circleAreaMax * 100;
            //画面に描画
            SetFontSize(30);
            DrawFormatString(RESULT_STRING_X, RESULT_STRING_Y, resultColor, "円の割合は%.1f%%です", circlePorpotoin);

        }


        //円の描画
        DrawCircle(Circle.posX, Circle.posY, Circle.radius, CircleColor);


        //裏画面の内容を表画面に反映させる
        ScreenFlip();
        //処理したフレームの時間
        prevCount = nowCout;


    }

    //Dxlib終了処理
    DxLib_End();

    return 0;
}