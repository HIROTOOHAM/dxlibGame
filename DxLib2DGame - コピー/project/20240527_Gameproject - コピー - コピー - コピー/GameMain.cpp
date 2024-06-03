/*
* エントリーポイント＆ゲームループ
*/
#include "GameData.h"
#include "GameFunctuion.h"

//エントリーポイント
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

    //円の大きさを指定
    Circle.posX = CIRCLE_POS_X;
    Circle.posY = CIRCLE_POS_Y;
    Circle.radius = CIRCLE_RADIUS_START;


    //DxLibの初期化処理
    if (DxLib_Init() == -1)
    {
        //エラーが起きたら直ちに終了
        return -1;
    }
    //フレームカウント初期化
    nowCout = prevCount = GetNowCount();
    //---------------------------//
    // ゲームループ
    //---------------------------//

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ClearDrawScreen() == 0)
    {
        //時間を獲得
        nowCout = GetNowCount();
        //デルタタイム生成
        double deltaTime = (nowCout - prevCount) / 1000.0f;
        //フレームカウントを増加
        frameCount += deltaTime;

        //エンターキーを押されたかを記憶させる
        enterPressedLastFrame = CheckHitKey(KEY_INPUT_RETURN);

        //エンターキーを押された回数で変更する
        //0回（スタート画面の表示）
        if (!gameStartFlag && !gameEndFlag)
        {
            //スタート画面関数を呼び出す
            StartScreen(deltaTime);
        }
        //1回から3回（ゲーム画面）
        else if (gameStartFlag && !gameEndFlag)
        {
            //ゲーム画面関数を呼び出す
            GameProcessing(deltaTime);
        }
        //3回以降（リザルト画面）
        else if (gameEndFlag)
        {
            ResultScreen();
        }

        //処理したフレームの時間
        prevCount = nowCout;


    }


    //Dxlib終了処理
    DxLib_End();

    return 0;
}