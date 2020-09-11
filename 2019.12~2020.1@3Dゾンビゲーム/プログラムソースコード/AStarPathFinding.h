#pragma once
#define Rows 99
#define Cows 99
#define ZlineDaijia 10
#define XlineDaijia 14
#define ab    100


struct MyPoint
{
	int row;
	int cow;
	int f;
	int g;
	int h;
	void Setf() { f = g + h; }
};
//Fuzheditu;
struct pathNode
{
	int val;
	bool iswark;//
	XMFLOAT3 jinD;
	XMFLOAT3 YuanD;
	XMFLOAT3 Center;

};
struct  PathUpdateMap
{
	int val;
};
//tree de jiedian leixain
struct treeNode
{
	MyPoint						Pos;//  now node pos
	treeNode*					pParent; // father node
	std::vector<treeNode*>	child; // ï€ë∂Å@child node

	treeNode()
	{
		memset(this, 0, sizeof(treeNode));
	}

};
enum direct { p_up, p_down, p_left, p_right, p_lup, p_ldown, p_rup, p_rdown };
enum rundirect { Zhiline, XieLine, Zhiline1 };
struct MyDirect
{
	MyPoint							Pos;
	XMFLOAT3						dire;
};

class AStarPathFinding
{
public:
	AStarPathFinding();
	~AStarPathFinding();
	void Init();
	void Init( SBOX sbox);
	void Init(pathNode pathmap[Rows][Cows]);
	void Update();
	void UpdateX();
	void UPdateObject(XMFLOAT3& Pos,   bool& stopmove, bool& Again, float Speed);
	void FindPath(XMFLOAT3 StartPos,XMFLOAT3 EndPos);
	void Move(XMFLOAT3 &Pos, float dt);
	void Move(XMFLOAT3 &Pos, float dt, XMVECTOR& Dir,float& outblendtimer,float& outDeg,float Speed,bool& pathoff, XMVECTOR nowfacedir);
	void Draw();
	void Uinit();
private:
	int initMap[Rows][Cows];
	MyPoint		beginPos;
	MyPoint		enPos;
	pathNode	pathMap[Rows][Cows];
	pathNode	InitMap[Rows][Cows];
	MyPoint      UpdateMap;

	treeNode*   pTemp = NULL; // dang qian shu jie idan 
	std::vector<treeNode* > buffer;//// create Vecter for ï€ë∂Å@ï]âøÇ≥ÇÍÇΩPos
	bool isfindEnd;
public:
	bool canwalk(MyPoint pos, pathNode pathmap[Rows][Cows]);
	int GetH(MyPoint pos, MyPoint endpos);
	void NowPosInMap(XMFLOAT2 bePos);
	void SetbeginPos(XMFLOAT2 bePos);
	void SetTargetPos(XMFLOAT2 endPos);
	void RestMapForWalls(pathNode pathmap[Rows][Cows],std::vector<MyPoint> UpMap);
	void RestMapForwall();
	bool* GetisfindEnd() { return&isfindEnd; }
	MyPoint GetbeginPos() { return beginPos; }
	MyPoint GetendPos() { return enPos; }
	MyPoint GetUpdateMapPos() { return UpdateMap; }
	void SetfindEnd(bool xx) { isfindEnd = xx; }
private:
	bool Box(XMFLOAT2 cPoint, XMFLOAT2 p1, XMFLOAT2 p3);
	bool PathPrinting(treeNode* pNode);
	std::vector<XMFLOAT3> MesPos;
	std::vector<MyDirect> VPath;
	std::vector<MyDirect> VPath2;
	std::vector<XMFLOAT3> PathDir;
	std::vector<XMFLOAT3> PathPos;
	
	int PathCount;
	bool FindPathDir;
	void GetPathDir();
	bool endPrintpath;
public:
	
	std::vector<MyDirect>  GetVPath();
	bool GetenDprint() { return endPrintpath; }
	void SetStartNode();
	void PathReset();
	void VPathClear() { VPath2.clear(); }
	void RestIsfindpath() { isfindEnd = true; }
	pathNode& GetPathMap() { return pathMap[Rows][Cows]; }

	XMVECTOR NowMoveDir()
	{
		return  XMLoadFloat3(&PathDir[PathCount]);
	}
	int GetPathDirSize() { return PathDir.size()-1; }
	bool GetFindPathDir() { return FindPathDir; }
};

