#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)　HW16A194 峯岡
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)　HW16A178　前田
// TODO: 砲台を青い壁に沿って上下に動かす。(C)　HW16A178　前田
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D) Hw16A190 水本浩暉
// TODO: スコアのサイズを大きくする。(E)　HW16A190 水本浩暉
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)　HW16A194 峯岡
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)　HW16A194 峯岡
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)　HW16A221 吉田和成





Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
int     flag=0;


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-315, -150);
    targetRect = Rect(280, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
    
    PlayBGM("bgm_maoudamashii_8bit07.mp3");
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    //雲の移動
    if (cloudPos.x < 310) {
        cloudPos.x += 50 * Time::deltaTime;
    }else{
        cloudPos.x =-550;
    }
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        
        PlaySound("se_maoudamashii_explosion03.mp3");
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 300 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_system20.mp3");
        }
    }

    //砲台の移動
    if(cannonPos.y < -75&&(flag==0||flag==2)){
        flag=0;
    }else if(cannonPos.y>-85&&(flag==0||flag==2)){
        flag=1;
    }else if(cannonPos.y<-145){
        flag=2;
    }
    if (flag==0||flag==2){
        cannonPos.y += 50 * Time::deltaTime;
    }else{
        cannonPos.y -= 50 * Time::deltaTime;
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 20.0f*3);
    DrawText(FormatString("%05d", score), Vector2(-319, 199), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-320, 200), Color::white);
}

