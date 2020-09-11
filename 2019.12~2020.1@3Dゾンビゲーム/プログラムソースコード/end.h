#pragma once
enum UICONTROL2
{
	gamestart2,
	gameend2,
};
class end:public CScene
{
public:
	end();
	~end();
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	std::unique_ptr<CPolygon> pbackground;
	STRINGDRAW GameStart;
	STRINGDRAW GameOut;
	float gamestartBlend;
	int ControlUINum2;
};

