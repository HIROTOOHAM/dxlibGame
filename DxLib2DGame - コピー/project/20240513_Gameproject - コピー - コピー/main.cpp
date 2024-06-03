#include "DxLib.h"//Dxライブラリーをインクルード(読み込み)

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)//Windowsのメインで動かす
{

    //基本設計
    ChangeWindowMode(TRUE);//Windowsの画面をアクティブにする
    DxLib_Init();//DxLibの初期化
    SetDrawScreen(DX_SCREEN_BACK);//画面の背景は黒
    SetGraphMode(800, 600, 32);//画面の大きさ

    //Dxlibの初期化処理
    if (DxLib_Init() == -1)
    {
        //エラーが起きたら直ちに終了

        return -1;
    }
    //円の初期位置
    int circleX = 320;
    int circleY = 240;

    //ゲームループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();

        DrawCircle(circleX, circleY, 30, GetColor(0, 0, 255), TRUE);

        circleX += 2;
        circleY += 2;


        ScreenFlip();
    }

    DrawPixel(320, 240, GetColor(255, 0, 0));

    DxLib_End();

    return 0;
}
        
