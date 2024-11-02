#include <Novice.h>

const char kWindowTitle[] = "LC1C_07_コイズミリョウ_タイトル";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// プレイヤーの向き
enum playerDirection {
	LEFT,
	RIGHT
};

// 構造体

// ベクトル
typedef struct Vector2 {
	float x;
	float y;
} Vector2;

// プレイヤー
typedef struct Player {
	Vector2 worldPos;
	Vector2 move;
	float radius;
	float speed;
	int jumpCount;
	float jump;
	int isJump;
	float doubleJump;
	int isDoubleJump;
	int hp;
	int isHit;
	int hitTimer;
} Player;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ========================
	// 変数の宣言と初期化
	// ========================

	// 自機の変数
	Player player{};
	player.worldPos.x = 80.0f;
	player.worldPos.y = 536.0f;
	player.speed = 8.0f;
	player.radius = 36.0f;
	player.jumpCount = 0;
	player.jump = 0.0f;
	player.isJump = false;
	player.doubleJump = 0.0f;
	player.isDoubleJump = false;
	player.hp = 5;
	player.isHit = false;
	player.hitTimer = 120;

	int playerDirection = RIGHT;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// 自機の移動処理

		if (keys[DIK_A]) {
			playerDirection = LEFT;
			if (player.worldPos.x > 0.0f + 128.0f / 2.0f) {
				player.worldPos.x -= player.speed;
			}
			else {
				if (player.worldPos.x > 0.0f + 128.0f / 2.0f) {
					player.worldPos.x -= player.speed;
				}
			}
		}

		if (keys[DIK_D]) {
			playerDirection = RIGHT;
			if (player.worldPos.x <= 6272.0f + 128.0f / 2.0f) {
				player.worldPos.x += player.speed;
			}
			else {
				if (player.worldPos.x <= 6272.0f + 128.0f / 2.0f) {
					player.worldPos.x += player.speed;
				}
			}
		}

		// スペース押した瞬間にジャンプする
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && player.worldPos.y == 536.0f) {
			player.jump = -12.0f;
			player.worldPos.y += player.jump;
			player.isJump = true;
			player.jumpCount += 1;
		}


		// ジャンプ中の動作(落下)
		if (player.isJump) {
			player.jump += 0.5f;
			player.worldPos.y += player.jump;
			if (player.worldPos.y >= 536.0f) {
				player.worldPos.y = 536.0f;
				player.isJump = false;
				player.isDoubleJump = false;
			}
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(0, 572, kWindowWidth, kWindowHeight, 0.0f, WHITE, kFillModeSolid);

		// 自機の描画
		if (playerDirection == RIGHT) {
			Novice::DrawBox(static_cast<int>(player.worldPos.x - 128.0f / 2.0f),
				static_cast<int>(player.worldPos.y), static_cast<int>(player.radius), static_cast<int>(player.radius), 0.0f, RED, kFillModeSolid);
		}

		if (playerDirection == LEFT) {
			Novice::DrawBox(static_cast<int>(player.worldPos.x - 128.0f / 2.0f),
				static_cast<int>(player.worldPos.y), static_cast<int>(player.radius), static_cast<int>(player.radius), 0.0f, RED, kFillModeSolid);
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
