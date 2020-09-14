#include "DxLib.h"

#define GAME_WIDTH			640
#define GAME_HEIGHT			480
#define GAME_COLOR			32

#define GAME_WINDOW_BAR		0
#define GAME_WINDOW_NAME	"Dxlib_Movie"

#define MOVIE_PATH			".\\MOVIE\\GB.mp4"

int handle = -1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));
	SetAlwaysRunFlag(TRUE);

	if (DxLib_Init() == -1) { return -1; }

	handle = LoadGraph(MOVIE_PATH);

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		if (GetMovieStateToGraph(handle) == 0)
		{
			SeekMovieToGraph(handle, 0);
			PlayMovieToGraph(handle);

			ChangeMovieVolumeToGraph(127, handle);
		}

		DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, handle, FALSE);
		//DrawGraph(0, 0, handle, FALSE);

		DrawString(0, 0, "動画を再生しています・・・", GetColor(255, 255, 255));
		DrawString(0, 20, "フグの動画", GetColor(255, 255, 255));

		ScreenFlip();
	}

	DxLib_End();

	DeleteGraph(handle);

	return 0;
}
