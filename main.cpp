#include <iostream>

#include "raylib.h"

void Init();
void Gameloop();
void Update();
void Draw();
void Shutdown();

const int MAX_WIDTH = 1024;
const int MAX_HEIGHT = 720;
const int MAX_FPS = 60;

struct PLAYER
{
	int Games_Played;
	int Balls_Popped;
	int Red_Balls_Popped;
	int Green_Balls_Popped;
	int Blue_Balls_Popped;
	int Yellow_Balls_Popped;
	long Score;
};

struct BALL
{
	float X_Pos, Y_Pos;
	float X_Vel, Y_Vel;
	Vector2 Pos, Vel;
	bool Popped;
	bool Visible;
	int Points;
	int Timer_Countdown; //how long before the ball re-appears
	Color col;
	int Radius;
	Rectangle Rect;
};

const int MAX_PARTICLES = 30;

struct PARTICLE
{
	Vector2 Position;
	Color col;
	float alpha;
	float size;
	float rotation;
	bool Active;
};

enum GAME_SCREEN
{
	LOGO,
	TITLE,
	GAME,
	STATS
};

bool Paused = false;

PLAYER Player;

BALL Red_Ball, Green_Ball, Blue_Ball, Yellow_Ball;

GAME_SCREEN GameScreen = LOGO;

PARTICLE Particle;

Texture2D LogoTex, TitleTex;

int mx = 0;
int my = 0;

int main(int argc, char* argv[])
{
	Init();

	Gameloop();

	Shutdown();

	return 0;
}

void Init()
{
	InitWindow(MAX_WIDTH, MAX_HEIGHT, "Ball Shooter Deluxe! - ICY VIKING GAMES");

	SetTargetFPS(MAX_FPS);

	LogoTex = LoadTexture("Images/Logo.png");
	TitleTex = LoadTexture("Images/BallTitle.png");

	Player.Balls_Popped = 0;
	Player.Blue_Balls_Popped = 0;
	Player.Green_Balls_Popped = 0;
	Player.Red_Balls_Popped = 0;
	Player.Yellow_Balls_Popped = 0;
	Player.Games_Played = 0;
	Player.Score = 0;

	SetRandomSeed(25);

	Red_Ball.X_Pos = (float)GetRandomValue(1, MAX_WIDTH);
	Red_Ball.Y_Pos = (float)GetRandomValue(1,MAX_HEIGHT);
	Red_Ball.X_Vel = 10.0f;
	Red_Ball.Y_Vel = 10.0f;
	Red_Ball.Pos.x = Red_Ball.X_Pos;
	Red_Ball.Pos.y = Red_Ball.Y_Pos;
	Red_Ball.Vel.x = Red_Ball.X_Vel;
	Red_Ball.Vel.y = Red_Ball.Y_Vel;
	Red_Ball.Radius = 20;
	Red_Ball.Timer_Countdown = 200;
	Red_Ball.Points = 20;
	Red_Ball.Popped = false;
	Red_Ball.Visible = true;

	Green_Ball.X_Pos = (float)GetRandomValue(1, MAX_WIDTH);
	Green_Ball.Y_Pos = (float)GetRandomValue(1, MAX_HEIGHT);
	Green_Ball.X_Vel = 8.0f;
	Green_Ball.Y_Vel = 8.0f;
	Green_Ball.Pos.x = Green_Ball.X_Pos;
	Green_Ball.Pos.y = Green_Ball.Y_Pos;
	Green_Ball.Vel.x = Green_Ball.X_Vel;
	Green_Ball.Vel.y = Green_Ball.Y_Vel;
	Green_Ball.Radius = 20;
	Green_Ball.Timer_Countdown = 200;
	Green_Ball.Points = 15;
	Green_Ball.Popped = false;
	Green_Ball.Visible = true;

	Blue_Ball.X_Pos = (float)GetRandomValue(1, MAX_WIDTH);
	Blue_Ball.Y_Pos = (float)GetRandomValue(1, MAX_HEIGHT);
	Blue_Ball.X_Vel = 6.0f;
	Blue_Ball.Y_Vel = 6.0f;
	Blue_Ball.Pos.x = Blue_Ball.X_Pos;
	Blue_Ball.Pos.y = Blue_Ball.Y_Pos;
	Blue_Ball.Vel.x = Blue_Ball.X_Vel;
	Blue_Ball.Vel.y = Blue_Ball.Y_Vel;
	Blue_Ball.Radius = 20;
	Blue_Ball.Timer_Countdown = 200;
	Blue_Ball.Points = 10;
	Blue_Ball.Popped = false;
	Blue_Ball.Visible = true;

	Yellow_Ball.X_Pos = (float)GetRandomValue(1, MAX_WIDTH);
	Yellow_Ball.Y_Pos = (float)GetRandomValue(1, MAX_HEIGHT);
	Yellow_Ball.X_Vel = 4.0f;
	Yellow_Ball.Y_Vel = 4.0f;
	Yellow_Ball.Pos.x = Yellow_Ball.X_Pos;
	Yellow_Ball.Pos.y = Yellow_Ball.Y_Pos;
	Yellow_Ball.Vel.x = Yellow_Ball.X_Vel;
	Yellow_Ball.Vel.y = Yellow_Ball.Y_Vel;
	Yellow_Ball.Radius = 20;
	Yellow_Ball.Timer_Countdown = 200;
	Yellow_Ball.Points = 5;
	Yellow_Ball.Popped = false;
	Yellow_Ball.Visible = true;
}

void Gameloop()
{
	while (!WindowShouldClose())
	{
		Update();

		Draw();
	}
}

void Update()
{
	switch (GameScreen)
	{
	case LOGO:
		if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			GameScreen = TITLE;
		}
		break;

	case TITLE:
		if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			GameScreen = GAME;
		}
		break;

	case GAME:
		if (IsKeyPressed(KEY_P)) Paused = !Paused;

		if (!Paused)
		{
			Vector2 MousePos = GetMousePosition();
			mx = (int)MousePos.x;
			my = (int)MousePos.y;

			Red_Ball.Pos.x += Red_Ball.Vel.x;
			Red_Ball.Pos.y += Red_Ball.Vel.y;

			Green_Ball.Pos.x += Green_Ball.Vel.x;
			Green_Ball.Pos.y += Green_Ball.Vel.y;

			Blue_Ball.Pos.x += Blue_Ball.Vel.x;
			Blue_Ball.Pos.y += Blue_Ball.Vel.y;

			Yellow_Ball.Pos.x += Yellow_Ball.Vel.x;
			Yellow_Ball.Pos.y += Yellow_Ball.Vel.y;

			if ((Red_Ball.Pos.x >= (GetScreenWidth() - Red_Ball.Radius)) || (Red_Ball.Pos.x <= Red_Ball.Radius)) Red_Ball.Vel.x *= -1;
			if ((Red_Ball.Pos.y >= (GetScreenHeight() - Red_Ball.Radius)) || (Red_Ball.Pos.y <= Red_Ball.Radius)) Red_Ball.Vel.y *= -1;

			if((Green_Ball.Pos.x >= (GetScreenWidth() - Green_Ball.Radius)) || (Green_Ball.Pos.x <= Green_Ball.Radius)) Green_Ball.Vel.x *= -1;
			if((Green_Ball.Pos.y >= (GetScreenHeight() - Green_Ball.Radius)) || (Green_Ball.Pos.y <= Green_Ball.Radius)) Green_Ball.Vel.y *= -1;

			if ((Blue_Ball.Pos.x >= (GetScreenWidth() - Blue_Ball.Radius)) || (Blue_Ball.Pos.x <= Blue_Ball.Radius)) Blue_Ball.Vel.x *= -1;
			if ((Blue_Ball.Pos.y >= (GetScreenHeight() - Blue_Ball.Radius)) || (Blue_Ball.Pos.y <= Blue_Ball.Radius)) Blue_Ball.Vel.y *= -1;

			if ((Yellow_Ball.Pos.x >= (GetScreenWidth() - Yellow_Ball.Radius)) || (Yellow_Ball.Pos.x <= Yellow_Ball.Radius)) Yellow_Ball.Vel.x *= -1;
			if ((Yellow_Ball.Pos.y >= (GetScreenHeight() - Yellow_Ball.Radius)) || (Yellow_Ball.Pos.y <= Yellow_Ball.Radius)) Yellow_Ball.Vel.y *= -1;

			if (CheckCollisionCircles(Red_Ball.Pos, (float)Red_Ball.Radius, Green_Ball.Pos, (float)Green_Ball.Radius))
			{
				Red_Ball.Vel.x *= -1;
				Red_Ball.Vel.y *= -1;
				Green_Ball.Vel.x *= -1;
				Green_Ball.Vel.y *= -1;
			}

			if (CheckCollisionCircles(Red_Ball.Pos, (float)Red_Ball.Radius, Blue_Ball.Pos, (float)Blue_Ball.Radius))
			{
				Red_Ball.Vel.x *= -1;
				Red_Ball.Vel.y *= -1;
				Blue_Ball.Vel.x *= -1;
				Blue_Ball.Vel.y *= -1;
			}

			if (CheckCollisionCircles(Green_Ball.Pos, (float)Green_Ball.Radius, Blue_Ball.Pos, (float)Blue_Ball.Radius))
			{
				Green_Ball.Vel.x *= -1;
				Green_Ball.Vel.y *= -1;
				Blue_Ball.Vel.x *= -1;
				Blue_Ball.Vel.y *= -1;
			}

			if (CheckCollisionCircles(Red_Ball.Pos, (float)Red_Ball.Radius, Yellow_Ball.Pos, (float)Yellow_Ball.Radius))
			{
				Red_Ball.Vel.x *= -1;
				Red_Ball.Vel.y *= -1;
				Yellow_Ball.Vel.x *= -1;
				Yellow_Ball.Vel.y *= -1;
			}

			if (CheckCollisionCircles(Green_Ball.Pos, (float)Green_Ball.Radius, Yellow_Ball.Pos, (float)Yellow_Ball.Radius))
			{
				Green_Ball.Vel.x *= -1;
				Green_Ball.Vel.y *= -1;
				Yellow_Ball.Vel.x *= -1;
				Yellow_Ball.Vel.y *= -1;
			}

			if (CheckCollisionCircles(Blue_Ball.Pos, (float)Blue_Ball.Radius, Yellow_Ball.Pos, (float)Yellow_Ball.Radius))
			{
				Blue_Ball.Vel.x *= -1;
				Blue_Ball.Vel.y *= -1;
				Yellow_Ball.Vel.x *= -1;
				Yellow_Ball.Vel.y *= -1;
			}

			
			if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && abs(MousePos.x - Yellow_Ball.Pos.x) <= Yellow_Ball.Radius && abs(MousePos.y - Yellow_Ball.Pos.y) <= Yellow_Ball.Radius)
			{
				Yellow_Ball.Popped = true;
				Player.Score += Yellow_Ball.Points;
				Player.Balls_Popped++;
				Player.Yellow_Balls_Popped++;
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && abs(MousePos.x - Red_Ball.Pos.x) <= Red_Ball.Radius && abs(MousePos.y - Red_Ball.Pos.y) <= Red_Ball.Radius)
			{
				Red_Ball.Popped = true;
				Player.Score += Red_Ball.Points;
				Player.Balls_Popped++;
				Player.Red_Balls_Popped++;
			}

			if (Red_Ball.Popped == true)
			{
				Red_Ball.Vel.x = 0;
				Red_Ball.Vel.y = 0;
				Red_Ball.X_Pos = 0;
				Red_Ball.Y_Pos = 0;
				Red_Ball.Timer_Countdown--;

				if (Red_Ball.Timer_Countdown == 0)
				{
					Red_Ball.Popped = false;
					Red_Ball.Vel.x += 10.0f;
					Red_Ball.Vel.y += 10.0f;
					Red_Ball.Pos.x = (float)GetRandomValue(1, MAX_WIDTH);
					Red_Ball.Pos.y = (float)GetRandomValue(1, MAX_HEIGHT);
					Red_Ball.Timer_Countdown = 200;
				}
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && abs(MousePos.x - Green_Ball.Pos.x) <= Green_Ball.Radius && abs(MousePos.y - Green_Ball.Pos.y) < Green_Ball.Radius)
			{
				Green_Ball.Popped = true;
				Player.Score += Green_Ball.Points;
				Player.Balls_Popped++;
				Player.Green_Balls_Popped++;
			}

			if (Green_Ball.Popped == true)
			{
				Green_Ball.Vel.x = 0;
				Green_Ball.Vel.y = 0;
				Green_Ball.X_Pos = 0;
				Green_Ball.Y_Pos = 0;
				Green_Ball.Timer_Countdown--;

				if (Green_Ball.Timer_Countdown == 0)
				{
					Green_Ball.Popped = false;
					Green_Ball.Vel.x += 8.0f;
					Green_Ball.Vel.y += 8.0f;
					Green_Ball.Pos.x = (float)GetRandomValue(1, MAX_WIDTH);
					Green_Ball.Pos.y = (float)GetRandomValue(1, MAX_HEIGHT);
					Green_Ball.Timer_Countdown = 200;
				}
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && abs(MousePos.x - Blue_Ball.Pos.x) <= Blue_Ball.Radius && abs(MousePos.y - Blue_Ball.Pos.y) < Blue_Ball.Radius)
			{
				Blue_Ball.Popped = true;
				Player.Score += Blue_Ball.Points;
				Player.Balls_Popped++;
				Player.Blue_Balls_Popped++;
			}

			if (Blue_Ball.Popped == true)
			{
				Blue_Ball.Vel.x = 0;
				Blue_Ball.Vel.y = 0;
				Blue_Ball.X_Pos = 0;
				Blue_Ball.Y_Pos = 0;
				Blue_Ball.Timer_Countdown--;

				if (Blue_Ball.Timer_Countdown == 0)
				{
					Blue_Ball.Popped = false;
					Blue_Ball.Vel.x += 6.0f;
					Blue_Ball.Vel.y += 6.0f;
					Blue_Ball.Pos.x = (float)GetRandomValue(1, MAX_WIDTH);
					Blue_Ball.Pos.y = (float)GetRandomValue(1, MAX_HEIGHT);
					Blue_Ball.Timer_Countdown = 200;
				}
			}

			if (Yellow_Ball.Popped == true)
			{
				Yellow_Ball.Vel.x = 0;
				Yellow_Ball.Vel.y = 0;
				Yellow_Ball.X_Pos = 0;
				Yellow_Ball.Y_Pos = 0;
				Yellow_Ball.Timer_Countdown--;

				if (Yellow_Ball.Timer_Countdown == 0)
				{
					Yellow_Ball.Popped = false;
					Yellow_Ball.Vel.x += 4.0f;
					Yellow_Ball.Vel.y += 4.0f;
					Yellow_Ball.Pos.x = (float)GetRandomValue(1, MAX_WIDTH);
					Yellow_Ball.Pos.y = (float)GetRandomValue(1, MAX_HEIGHT);
					Yellow_Ball.Timer_Countdown = 200;
				}
			}

			if (IsKeyPressed(KEY_S))
			{
				GameScreen = STATS;
			}
		}

	case STATS:
		if (IsKeyPressed(KEY_Z))
		{
			GameScreen = GAME;
		}
		break;
		break;
	}
}

void Draw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	switch (GameScreen)
	{
	case LOGO:
		DrawTexture(LogoTex, 100, 100 , WHITE);
		break;

	case TITLE:
		DrawTexture(TitleTex, 100 , 100 , WHITE);
		break;

	case GAME:
		DrawText(TextFormat("SCORE: %i", Player.Score),1, 1, 20, YELLOW);
		DrawText(TextFormat("POPPED: %i", Player.Balls_Popped), 1, 20, 20, YELLOW);

		//For debugging purposes
		//DrawText(TextFormat("MX: %i", mx), 1,40,20,YELLOW);
		//DrawText(TextFormat("MY: %i", my), 1, 60, 20, YELLOW);

		if (Red_Ball.Popped == false)
		{
			DrawCircleV(Red_Ball.Pos, (float)Red_Ball.Radius, RED);
		}
		else
		{


		}

		if (Green_Ball.Popped == false)
		{
			DrawCircleV(Green_Ball.Pos, (float)Green_Ball.Radius, GREEN);
		}
		else
		{

		}

		if (Blue_Ball.Popped == false)
		{
			DrawCircleV(Blue_Ball.Pos, (float)Blue_Ball.Radius, BLUE);
		}
		else
		{

		}

		if (Yellow_Ball.Popped == false)
		{
			DrawCircleV(Yellow_Ball.Pos, (float)Yellow_Ball.Radius, YELLOW);
		}
		else
		{

		}
		break;

	case STATS:
		DrawText(TextFormat("SCORE: %i", Player.Score), 1, 1, 20, YELLOW);
		DrawText(TextFormat("POPPED: %i", Player.Balls_Popped), 1, 20, 20, YELLOW);
		DrawText(TextFormat("RED POPPED: %i", Player.Red_Balls_Popped), 1, 40,20, YELLOW);
		DrawText(TextFormat("GREEN POPPED: %i", Player.Green_Balls_Popped), 1, 60, 20, YELLOW);
		DrawText(TextFormat("BLUE POPPED: %i", Player.Blue_Balls_Popped), 1, 80, 20, YELLOW);
		DrawText(TextFormat("YELLOW POPPED: %i", Player.Yellow_Balls_Popped), 1, 100, 20, YELLOW);

		DrawText("PRESS Z TO RETURN TO GAME!", MAX_WIDTH / 2 - 200, MAX_HEIGHT / 2, 20, YELLOW);
		break;
	}

	EndDrawing();
}

void Shutdown()
{
	UnloadTexture(LogoTex);
	UnloadTexture(TitleTex);

	CloseWindow();
}
