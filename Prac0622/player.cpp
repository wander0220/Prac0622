#include "player.h"
#include "global.h"
Player::Player() {
    playerX = WINDOW_WIDTH / 2 ;
    playerY = WINDOW_HEIGHT * 0.8;

    speed = 1; 
}
void Player::Update() {
    if (inputManager.keyBuffer[VK_LEFT] == 1) {
        playerX -= speed;
    }
    if (inputManager.keyBuffer[VK_RIGHT] == 1) {
        playerX += speed;
    }
    if (inputManager.keyBuffer[VK_UP] == 1) {
        playerY -= speed;
    }
    if (inputManager.keyBuffer[VK_DOWN] == 1) {
        playerY += speed;
    }

    if (playerX  < 0) {
        playerX = 0;
    }
    if (playerX > WINDOW_WIDTH) {
        playerX = WINDOW_WIDTH ;
    }
    if (playerY < 0) {
        playerY = 0;
    }
    if (playerY > WINDOW_HEIGHT) {
        playerY = WINDOW_HEIGHT;
    }

}
void Player::Render() {
    TextureElements* elements = textureManager.GetTexture(200);

    elements->sprite->Begin(D3DXSPRITE_ALPHABLEND);

    RECT rec;
    rec.left = 0;
    rec.top = 0;
    rec.right = 64;
    rec.bottom = 64;

    /*playerX = 100;
    playerY = 100;*/

    D3DXVECTOR3 pos(playerX - 32, playerY - 32, 0);


    elements->sprite->Draw(elements->texture, &rec
        , nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
    elements->sprite->End();
}