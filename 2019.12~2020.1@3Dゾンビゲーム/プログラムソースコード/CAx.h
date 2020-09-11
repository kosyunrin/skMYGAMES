//#pragma once
////#include <vector>
////using namespace std;
//#define Rows 49
//#define Cows 49
//#define ZlineDaijia 10
//#define XlineDaijia 14
//#define ab    50
//
//struct MyPoint
//{
//	int row;
//	int cow;
//	int f;
//	int g;
//	int h;
//	void Setf() { f = g + h; }
//};
////Fuzheditu;
//struct pathNode
//{
//	int val;
//	bool iswark;//
//	XMFLOAT3 jinD;
//	XMFLOAT3 YuanD;
//	XMFLOAT3 Center;
//	
//};
////tree de jiedian leixain
//struct treeNode
//{
//	MyPoint						Pos;//  now node pos
//	treeNode*					pParent; // father node
//	std::vector<treeNode*>	child; // ï€ë∂Å@child node
//};
//enum direct { p_up,p_down,p_left,p_right,p_lup,p_ldown,p_rup,p_rdown};
//enum rundirect{ Zhiline,XieLine,Zhiline1};
//struct MyDirect
//{
//	MyPoint							Pos;
//	XMFLOAT3						dire;
//};
//
//class CAx
//{
//public:
//	CAx();
//	~CAx();
//	void Init(std::vector<SStaticMode*> meshes);
//	void Update();
//	void Draw();
//	void Uinit();
//private:
//	int initMap[Rows][Cows];
//	MyPoint		beginPos;
//	MyPoint		enPos;
//	pathNode	pathMap[Rows][Cows];
//	
//	treeNode*   pTemp = NULL; // dang qian shu jie idan 
//	std::vector<treeNode* > buffer;//// create Vecter for ï€ë∂Å@ï]âøÇ≥ÇÍÇΩPos
//	bool isfindEnd;
//public:
//	bool canwalk(MyPoint pos, pathNode pathmap[Rows][Cows]);
//	int GetH(MyPoint pos, MyPoint endpos);
//	void SetbeginPos(XMFLOAT2 bePos);
//	void SetTargetPos(XMFLOAT2 endPos);
//	bool* GetisfindEnd() { return& isfindEnd; }
//	MyPoint GetbeginPos() { return beginPos; }
//	MyPoint GetendPos() { return enPos; }
//	void SetfindEnd(bool xx) { isfindEnd = xx; }
//private:
//	bool Box(XMFLOAT2 cPoint, XMFLOAT2 p1, XMFLOAT2 p3);
//	bool PathPrinting(treeNode* pNode);
//	std::vector<XMFLOAT3> MesPos;
//	std::vector<MyDirect> directPos1;
//	bool endPrintpath;
//public:
//	std::vector<MyDirect>  GetdirectPos1();
//	bool GetenDprint() { return endPrintpath; }
//	//Set startNode
//	void SetStartNode();
//};
//
