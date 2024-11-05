#include <Novice.h>

const char kWindowTitle[] = "TD1_2";
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

// ボス
typedef struct Boss {
	Vector2 pos;
	//float speed;
	float radius;
	int isAlive;
	//int phase;
	int hp;
}Boss;

typedef struct Slash {
	Vector2 pos;
	float radius;
	int isSlash;
	float speed;
	int slashLeft;
	int slashRight;
}Slash;

// ボスの向き
enum BossDirection {
	PLAYER_LEFT,
	PLAYER_RIGHT
};

// ボスの段階
enum Phase {
	PHASE1,
	PHASE2,
	PHASE3
};

void SpawnSlash(Boss& boss, Slash& slash, BossDirection direction) {
	slash.isSlash = true;
	slash.pos.y = boss.pos.y;

	if (direction == PLAYER_LEFT) {
		slash.pos.x = boss.pos.x - 80.0f;
		slash.slashLeft = true;
	}
	else if (direction == PLAYER_RIGHT) {
		slash.pos.x = boss.pos.x + 80.0f;
		slash.slashRight = true;
	}
}

/// <summary>
/// 横振りの攻撃関数
/// </summary>
/// <param name="boss">ボスの構造体</param>
/// <param name="player">プレイヤーの構造体</param>
void SlashMove(Slash& slash) {
	// 横振り攻撃の処理
	if (slash.isSlash) {
		if (slash.slashLeft) {
			slash.pos.x -= slash.speed;
		}
		else if (slash.slashRight) {
			slash.pos.x += slash.speed;
		}

		if (slash.pos.x < 0.0f || slash.pos.x > 1280.0f) {
			slash.isSlash = false;
			slash.slashLeft = false;
			slash.slashRight = false;
		}
	}
}

/// <summary>
/// 縦振りの関数
/// </summary>
/// <param name="boss">ボスの構造体</param>
/// <param name="player">プレイヤーの構造体</param>
/*void Attack_Vertical_Swing(Boss& boss, Player& player) {
	// 縦振り攻撃の処理
}

/// <summary>
/// 剣の召喚攻撃関数
/// </summary>
/// <param name="boss">ボスの構造体</param>
/// <param name="player">プレイヤーの構造体</param>
void Attack_Sword_Summon(Boss& boss, Player& player) {

}

/// <summary>
/// ボスのメインループ関数
/// </summary>
/// <param name="boss">ボスの構造体</param>
/// <param name="player">プレイヤーの構造体</param>
void Boss_AI(Boss& boss, Player& player) {
	Phase cuurentPhase = PHASE1;
	switch (cuurentPhase)
	{
	case PHASE1:
		if (boss.hp > 70) {


		}

		break;

	case PHASE2:

		break;

	case PHASE3:

		break;
	}
}*/

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

	// ボスの変数
	Boss boss{};
	boss.pos.x = 700.0f;
	boss.pos.y = 500.0f;
	boss.radius = 72.0f;
	boss.isAlive = true;
	boss.hp = 100;

	BossDirection bossDirection = PLAYER_LEFT;

	Slash slash{};
	slash.pos.x = 0.0f;
	slash.pos.y = 0.0f;
	slash.radius = 60.0f;
	slash.speed = 8.0f;
	slash.isSlash = false;

	int frameCount = 0;

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

		frameCount++;

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


		if (boss.isAlive) {
			if (boss.pos.x < player.worldPos.x) {
				bossDirection = PLAYER_RIGHT;
			}

			if (boss.pos.x > player.worldPos.x) {
				bossDirection = PLAYER_LEFT;
			}
		}


		if (frameCount == 300) {
			SpawnSlash(boss, slash, bossDirection);
		}

		SlashMove(slash);

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
				static_cast<int>(player.worldPos.y), 
				static_cast<int>(player.radius), 
				static_cast<int>(player.radius), 
				0.0f, RED, kFillModeSolid);
		}

		if (playerDirection == LEFT) {
			Novice::DrawBox(static_cast<int>(player.worldPos.x - 128.0f / 2.0f),
				static_cast<int>(player.worldPos.y), 
				static_cast<int>(player.radius), 
				static_cast<int>(player.radius), 
				0.0f, RED, kFillModeSolid);
		}

		if (boss.isAlive) {
			if (bossDirection == PLAYER_LEFT) {
				Novice::DrawEllipse(static_cast<int>(boss.pos.x),
					static_cast<int>(boss.pos.y),
					static_cast<int>(boss.radius),
					static_cast<int>(boss.radius),
					0.0f, BLACK, kFillModeSolid);
			}

			if (bossDirection == PLAYER_RIGHT) {
				Novice::DrawEllipse(static_cast<int>(boss.pos.x),
					static_cast<int>(boss.pos.y),
					static_cast<int>(boss.radius),
					static_cast<int>(boss.radius),
					0.0f, BLACK, kFillModeSolid);
			}
		}

		if (slash.isSlash) {
			Novice::DrawEllipse(static_cast<int>(slash.pos.x),
				static_cast<int>(slash.pos.y),
				static_cast<int>(slash.radius - 50.0f),
				static_cast<int>(slash.radius),
				0.0f, WHITE, kFillModeSolid);
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
