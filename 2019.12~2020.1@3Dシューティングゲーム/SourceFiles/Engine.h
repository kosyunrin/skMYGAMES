#pragma once
#include <locale>
#include <codecvt> 
#include <iostream>
#include"timer.h"
class Engine
{
public:
	static void timerShow(Timer m_time)
	{
	// 该代码计算每秒帧速，并计算每一帧渲染需要的时间，显示在窗口标题
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	if ((m_time.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::string outs;

		outs = ("OnePieceGame          ");
		char Buf[64];
		char Buf2[64];
		sprintf(Buf, "FPS:  %f"            , fps);
		sprintf(Buf2, "    Frame Time:  %f(ms)", mspf);
		std::string oo;
		oo = outs + Buf+Buf2;


		SetWindowText(GetWindow(), oo.c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
	}
	void fontShow()
	{

	}

private:


};
