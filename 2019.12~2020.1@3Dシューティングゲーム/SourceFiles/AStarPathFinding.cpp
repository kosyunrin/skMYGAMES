#include"main.h"
#include "AStarPathFinding.h"

AStarPathFinding::AStarPathFinding()
{
	//beginPos = { 23,21 };
	//enPos = { 34,37 };
	//endPrintpath = false;
}


AStarPathFinding::~AStarPathFinding()
{
}

void AStarPathFinding::Init()
{
	//enPos = { 34,37 };
	//made  a map
	XMFLOAT3 m_Vertex[ab*ab];
	for (int z = 0; z < ab; z++)
	{
		for (int x = 0; x < ab; x++)
		{
			XMMATRIX world;
			world = XMMatrixScaling(12.0f, 12.0f, 12.0f);//拡大
			m_Vertex[z * ab + x].x = x - ab / 2.0f;
			m_Vertex[z * ab + x].z = -z + ab / 2.0f;
			m_Vertex[z * ab + x].y = 0.0f/*sinf( x * 0.1f ) * sinf(z * 0.1f) * 2.0f*/;
			XMVECTOR m_VerXM = XMVector3TransformCoord(XMLoadFloat3(&m_Vertex[z * ab + x]), world);
			XMStoreFloat3(&m_Vertex[z * ab + x], m_VerXM);
		}
	}
	//
	unsigned short index[(ab - 1)*(ab - 1) * 6];
	int count = 0;
	for (int o = 0; o < (ab - 1); o++)
	{
		for (int i = 0; i < (ab - 1); i++)
		{
			index[count] = (o*((ab - 1) + 1)) + i;
			//fang ru jin dian 
			pathMap[o][i].jinD = m_Vertex[index[count]];
			count++;
			index[count] = (o*((ab - 1) + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + i;
			count++;
			index[count] = (o*((ab - 1) + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + i;
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + (i + 1);
			//fang ru yuan dian 
			pathMap[o][i].YuanD = m_Vertex[index[count]];
			count++;
			pathMap[o][i].iswark = false;
			pathMap[o][i].val = 1;
			float d = 6.0f;
			pathMap[o][i].Center = { (pathMap[o][i].jinD.x + d),0,(pathMap[o][i].jinD.z >= 0) ? (pathMap[o][i].jinD.z + d) : (pathMap[o][i].jinD.z - d) };
		}
	}







}

void AStarPathFinding::Init(SBOX sbox)
{
	isfindEnd = true;
	XMFLOAT3 m_Vertex[ab*ab];
	for (int z = 0; z < ab; z++)
	{
		for (int x = 0; x < ab; x++)
		{
			XMMATRIX world;
			world = XMMatrixScaling(12.0f, 12.0f, 12.0f);//拡大
			m_Vertex[z * ab + x].x = x - ab / 2.0f;
			m_Vertex[z * ab + x].z = -z + ab / 2.0f;
			m_Vertex[z * ab + x].y = 0.0f/*sinf( x * 0.1f ) * sinf(z * 0.1f) * 2.0f*/;
			XMVECTOR m_VerXM = XMVector3TransformCoord(XMLoadFloat3(&m_Vertex[z * ab + x]), world);
			XMStoreFloat3(&m_Vertex[z * ab + x], m_VerXM);
		}
	}
	//
	unsigned short index[(ab - 1)*(ab - 1) * 6];
	int count = 0;
	for (int o = 0; o < (ab - 1); o++)
	{
		for (int i = 0; i < (ab - 1); i++)
		{
			index[count] = (o*((ab - 1) + 1)) + i;
			//fang ru jin dian 
			pathMap[o][i].jinD = m_Vertex[index[count]];
			count++;
			index[count] = (o*((ab - 1) + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + i;
			count++;
			index[count] = (o*((ab - 1) + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + i;
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + (i + 1);
			//fang ru yuan dian 
			pathMap[o][i].YuanD = m_Vertex[index[count]];
			count++;
			pathMap[o][i].iswark = false;
			pathMap[o][i].val = 1;
			float d = 6.0f;
			pathMap[o][i].Center = { (pathMap[o][i].jinD.x + d),0,(pathMap[o][i].jinD.z >= 0) ? (pathMap[o][i].jinD.z + d) : (pathMap[o][i].jinD.z - d) };
			if (pathMap[o][i].Center.z <= 0.0f)
			{

				BoundingSphere _s;
				_s.Center = pathMap[o][i].Center;
				_s.Radius = 1.5f;

				for (int ii = 0; ii < sbox.ABOX.size(); ii++)
				{
					BoundingBox _box = sbox.ABOX[ii];
					if (_box.Contains(XMLoadFloat3(&pathMap[o][i].Center)))
						pathMap[o][i].val = 0;
				}
				for (int oo = 0; oo < sbox.OBOX.size(); oo++)
				{
				
					BoundingOrientedBox _box = sbox.OBOX[oo];
					if (_box.Contains(_s))
						pathMap[o][i].val = 1;
				}
				for (int oo = 0; oo < sbox.BlockABOX.size(); oo++)
				{

					BoundingBox _box = sbox.BlockABOX[oo];
					if (_box.Contains(_s))
						pathMap[o][i].val = 1;
				}
				
			}
			else
			{
				XMFLOAT3 pos = { pathMap[o][i].Center.x,0.0f,pathMap[o][i].Center.z - 10.0f };
				BoundingSphere _s;
				_s.Center = pos;
				_s.Radius = 1.5f;

				for (int ii = 0; ii < sbox.ABOX.size(); ii++)
				{
					BoundingBox _box = sbox.ABOX[ii];
					if (_box.Contains(XMLoadFloat3(&pos)))
						pathMap[o][i].val = 0;
				}


				for (int oo = 0; oo < sbox.OBOX.size(); oo++)
				{

					BoundingOrientedBox _box = sbox.OBOX[oo];
					if (_box.Contains(_s))
						pathMap[o][i].val = 1;
				}
				for (int oo = 0; oo < sbox.BlockABOX.size(); oo++)
				{

					BoundingBox _box = sbox.BlockABOX[oo];
					if (_box.Contains(_s))
						pathMap[o][i].val = 1;
				}
				
			}

		}
	}
	//
	for (int i = 48; i < 52; i++)
	{
		pathMap[56][i].val = 0.0f;
	}
}

void AStarPathFinding::Init(pathNode pathmap[Rows][Cows])
{
	isfindEnd = true;
	for (int o = 0; o < (ab - 1); o++)
	{
		for (int i = 0; i < (ab - 1); i++)
		{
			pathMap[o][i].iswark = pathmap[o][i].iswark;
			pathMap[o][i].val = pathmap[o][i].val;
			pathMap[o][i].jinD = pathmap[o][i].jinD;
			pathMap[o][i].YuanD = pathmap[o][i].YuanD;
			pathMap[o][i].Center = pathmap[o][i].Center;
		}
	}
}

void AStarPathFinding::Update()
{
	std::vector<treeNode*> buffer2;

	if (!isfindEnd)
	{
		//1.0f 检测周当前点周围那些点要纳入评估
		for (int i = 0; i < 8; i++)
		{
			treeNode* pChild = new treeNode;
			memset(pChild, 0, sizeof treeNode);//init 0
			pChild->Pos = pTemp->Pos;
			switch (i)
			{
			case p_up:
				pChild->Pos.row--;
				pChild->Pos.g += ZlineDaijia;
				break;
			case p_down:
				pChild->Pos.row++;
				pChild->Pos.g += ZlineDaijia;
				break;
			case p_left:
				pChild->Pos.cow--;
				pChild->Pos.g += ZlineDaijia;
				break;
			case p_right:
				pChild->Pos.cow++;
				pChild->Pos.g += ZlineDaijia;
				break;
			case p_lup:
				pChild->Pos.row--;
				pChild->Pos.cow--;
				pChild->Pos.g += XlineDaijia;
				break;
			case p_ldown:
				pChild->Pos.row++;
				pChild->Pos.cow--;
				pChild->Pos.g += XlineDaijia;
				break;
			case p_rup:
				pChild->Pos.row--;
				pChild->Pos.cow++;
				pChild->Pos.g += XlineDaijia;
				break;
			case p_rdown:
				pChild->Pos.row++;
				pChild->Pos.cow++;
				pChild->Pos.g += XlineDaijia;
				break;
			}
			//判断这个点能不能走 要不要评估 
			if (canwalk(pChild->Pos, pathMap))
			{
				//ji suan Fzhi 
				pChild->Pos.h = GetH(pChild->Pos, enPos);
				pChild->Pos.Setf();
				//入树
				pTemp->child.push_back(pChild);
				pChild->pParent = pTemp;

				buffer.push_back(pChild);
			}
		}
		//找出F值最小的那个 并从buff中删除这个点
		std::vector<treeNode*> ::iterator itMin;
		std::vector<treeNode*> ::iterator it;
		itMin = buffer.begin();
		for (it = buffer.begin(); it != buffer.end(); it++)
		{
			if ((*itMin)->Pos.f > (*it)->Pos.f)
				itMin = it;
		}

		pathMap[pTemp->Pos.row][pTemp->Pos.cow].iswark = true;
		pTemp = *itMin; //zou
		buffer.erase(itMin);
		if (pTemp->Pos.row == enPos.row&&pTemp->Pos.cow == enPos.cow)
			isfindEnd = true;
		if (buffer.empty()) isfindEnd = true;
	}
	else
	{
		buffer.clear();
		if (!PathPrinting(pTemp))
		{
			VPath = VPath2;
		}
	}
	CRenderer::Debug_show_int[0] = buffer.size();
}

void AStarPathFinding::FindPath(XMFLOAT3 StartPos, XMFLOAT3 EndPos)
{
	std::vector<treeNode*> buffer2;
	
	if (!isfindEnd)
	{
		VPath2.clear();
		//VPath.clear();
		//1.0f 检测周当前点周围那些点要纳入评估
		for (int i = 0; i < 8; i++)
		{
			treeNode* pChild = new treeNode;
			memset(pChild, 0, sizeof treeNode);//init 0
			pChild->Pos = pTemp->Pos;
			switch (i)
			{
			case p_up:
				pChild->Pos.row--;
				pChild->Pos.g += ZlineDaijia;
				break;
			case p_down:
				pChild->Pos.row++;
				pChild->Pos.g += ZlineDaijia;
				break;
			case p_left:
				pChild->Pos.cow--;
				pChild->Pos.g += ZlineDaijia;
				break;
			case p_right:
				pChild->Pos.cow++;
				pChild->Pos.g += ZlineDaijia;
				break;
			case p_lup:
				pChild->Pos.row--;
				pChild->Pos.cow--;
				pChild->Pos.g += XlineDaijia;
				break;
			case p_ldown:
				pChild->Pos.row++;
				pChild->Pos.cow--;
				pChild->Pos.g += XlineDaijia;
				break;
			case p_rup:
				pChild->Pos.row--;
				pChild->Pos.cow++;
				pChild->Pos.g += XlineDaijia;
				break;
			case p_rdown:
				pChild->Pos.row++;
				pChild->Pos.cow++;
				pChild->Pos.g += XlineDaijia;
				break;
			}
			//判断这个点能不能走 要不要评估 
			if (canwalk(pChild->Pos, pathMap))
			{
				//ji suan Fzhi 
				pChild->Pos.h = GetH(pChild->Pos, enPos);
				pChild->Pos.Setf();
				//入树
				pTemp->child.push_back(pChild);
				pChild->pParent = pTemp;

				buffer.push_back(pChild);
			}
		}
		//找出F值最小的那个 并从buff中删除这个点
		std::vector<treeNode*> ::iterator itMin;
		std::vector<treeNode*> ::iterator it;
		itMin = buffer.begin();
		for (it = buffer.begin(); it != buffer.end(); it++)
		{
			if ((*itMin)->Pos.f > (*it)->Pos.f)
				itMin = it;
		}

		pathMap[pTemp->Pos.row][pTemp->Pos.cow].iswark = true;
		pTemp = *itMin; //zou
		buffer.erase(itMin);
		if (pTemp->Pos.row == enPos.row&&pTemp->Pos.cow == enPos.cow)
			isfindEnd = true;
		if (buffer.empty()) isfindEnd = true;
	}
	else
	{
		SetbeginPos({ StartPos.x,StartPos.z });
		SetTargetPos({ EndPos.x,EndPos.z });
		
		if (!PathPrinting(pTemp))
		{
			VPath.clear();

			buffer.clear();
			VPath = VPath2;
			SetStartNode();
		}
	}
	CRenderer::Debug_show_int[0] = VPath.size();
}

void AStarPathFinding::Move(XMFLOAT3 & Pos, float dt)
{
	int count = 1;
	int Allsize = VPath.size();
	XMFLOAT3 P0Pos = Pos;
	/*if (beginPos.row != enPos.row ||
		beginPos.cow != enPos.cow)*/
	for (int i = 0; i < Allsize; i++)
	{
		if (VPath[i].dire.z > 0.0f) VPath[i].dire.z -= 10.0f;
	}
	if(Allsize>=1)
	{
		for (int i = Allsize - 1; i >= 0; i--)
		{
			//move
			if (i == Allsize - count)
			{
				XMFLOAT3 BeginPos = VPath[i].dire;
				XMFLOAT3 EndPos = VPath[i - 1].dire;
				BeginPos.y = 0.0f;
				EndPos.y = 0.0f;
				XMVECTOR dir = XMVector3Normalize(XMLoadFloat3(&EndPos) - XMLoadFloat3(&BeginPos));
				float P0_TO_B = Tool::Distance_float(P0Pos, BeginPos);//変化
				float END_TO_B = Tool::Distance_float(EndPos, BeginPos);
				if (P0_TO_B < END_TO_B)
				{
					XMVECTOR Ppos = XMLoadFloat3(&P0Pos);
					Ppos += dir * dt*20.0f;
					XMFLOAT3 Pposf;
					XMStoreFloat3(&Pposf, Ppos);
					Pos = Pposf;
				}
				else
				{
					if (count <= Allsize)
						count++;
				}
			}
			XMFLOAT3 finalPos =  VPath[0].dire ;
			float dis = Tool::Distance_float(P0Pos, finalPos);
			if (dis <= 7.0f)
			{
				VPath2.clear();
				//PathReset();
			}
		}
	}
}

void AStarPathFinding::Move(XMFLOAT3 & Pos, float dt, XMVECTOR & Dir,float& outblendtimer, float& outDeg,float speed, bool& pathoff,XMVECTOR nowfacedir)
{
	//bool isyizhi = false;
	int count = 1;
	int Allsize = VPath.size();
	XMFLOAT3 P0Pos = Pos;
	/*if (beginPos.row != enPos.row ||
		beginPos.cow != enPos.cow)*/
	for (int i = 0; i < Allsize; i++)
	{
		if (VPath[i].dire.z > 0.0f) VPath[i].dire.z -= 10.0f;
	}
	outblendtimer = 0.0f;

	if (Allsize >= 1)
	{
		for (int i = Allsize - 1; i >= 0; i--)
		{

			
			//move
			if (i == Allsize - count)
			{
				XMFLOAT3 Bpos;
				XMFLOAT3 Endpos;
				//outblendtimer <= 1.0f ? outblendtimer += 20.0f*dt : outblendtimer = 1.0f;

				XMFLOAT3 BeginPos = VPath[i].dire;
				int countsize = i - 1;
				countsize < 0.0f ? countsize = 0 : countsize = countsize;
				XMFLOAT3 EndPos = VPath[countsize].dire;
				BeginPos.y = 0.0f;
				EndPos.y = 0.0f;
				XMVECTOR dir = XMVector3Normalize(XMLoadFloat3(&EndPos) - XMLoadFloat3(&BeginPos));
				if (i < Allsize-1)
				{
					Bpos = VPath[i +1].dire;
					Endpos = VPath[i ].dire;
					XMVECTOR dir2 = XMVector3Normalize(XMLoadFloat3(&Endpos) - XMLoadFloat3(&Bpos));
					outDeg = XMVectorGetY(XMVector3AngleBetweenVectors(dir, dir2));
					Tool::GET_ANGLE(dir, dir2)>0.0f ? outDeg = -outDeg : outDeg = outDeg;
					if (Tool::GET_ANGLE(dir2,dir)!=0)
					{
						outblendtimer < 1.0f ? outblendtimer += 5.0f*dt : outblendtimer = 1.0f;
					}
					else
					{

						outblendtimer = 0.0f;
					}
				}
				 if (i == Allsize-1)
				{
						Tool::GET_ANGLE(dir, nowfacedir) > 0.0f ? outDeg = -outDeg : outDeg = outDeg;
						outblendtimer < 1.0f ? outblendtimer += 5.0f*dt : outblendtimer = 1.0f;
				}
				 Dir = dir;
				float P0_TO_B = Tool::Distance_float(P0Pos, BeginPos);//変化
				float END_TO_B = Tool::Distance_float(EndPos, BeginPos);
				if (P0_TO_B < END_TO_B)
				{
					XMVECTOR Ppos = XMLoadFloat3(&P0Pos);
					Ppos += dir * dt*speed;
					XMFLOAT3 Pposf;
					XMStoreFloat3(&Pposf, Ppos);
					Pos = Pposf;
				}
				else
				{
					if (count <= Allsize)
						count++;
				}
			}
			XMFLOAT3 finalPos = VPath[0].dire;
			float dis = Tool::Distance_float(P0Pos, finalPos);
			if (dis <= 7.0f)
			{
				VPath2.clear();
				//PathReset();
				pathoff = false;
			}
		}
	}
}


void AStarPathFinding::Draw()
{
}

void AStarPathFinding::Uinit()
{
	if (pTemp) delete pTemp;
	buffer.clear();
}

bool AStarPathFinding::canwalk(MyPoint pos, pathNode pathmap[Rows][Cows])
{
	if (pos.row < 0 || pos.row >= Rows || pos.cow < 0 || pos.cow >= Cows) return false;
	if (pathMap[pos.row][pos.cow].val == 1) return false;
	if (pathMap[pos.row][pos.cow].iswark == 1) return false;
	return true;
}

int AStarPathFinding::GetH(MyPoint pos, MyPoint endpos)
{
	int x = (pos.cow > enPos.cow) ? (pos.cow - endpos.cow) : (endpos.cow - pos.cow);
	int y = (pos.row > enPos.row) ? (pos.row - endpos.row) : (endpos.row - pos.row);

	return ZlineDaijia * (x + y);
}

void AStarPathFinding::NowPosInMap(XMFLOAT2 bePos)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cows; j++)
		{
			XMFLOAT2 jidian = { pathMap[i][j].jinD.x,pathMap[i][j].jinD.z };
			XMFLOAT2 yuandian = { pathMap[i][j].YuanD.x,pathMap[i][j].YuanD.z };
			if (bePos.x >= jidian.x&&bePos.y <= jidian.y&&bePos.x <= yuandian.x&&bePos.y >= yuandian.y)
			{
				UpdateMap = { i,j };
			}
		}
	}
}

void AStarPathFinding::SetbeginPos(XMFLOAT2 bePos)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cows; j++)
		{
			XMFLOAT2 jidian = { pathMap[i][j].jinD.x,pathMap[i][j].jinD.z };
			XMFLOAT2 yuandian = { pathMap[i][j].YuanD.x,pathMap[i][j].YuanD.z };
			if (bePos.x >= jidian.x&&bePos.y <= jidian.y&&bePos.x <= yuandian.x&&bePos.y >= yuandian.y)
			{
				beginPos = { i,j };
			}
		}
		//CRenderer::Debug_move_v2[0] = beginPos.row;
		//CRenderer::Debug_move_v2[1] = beginPos.cow;
	}

}

void AStarPathFinding::SetTargetPos(XMFLOAT2 endPos)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cows; j++)
		{
			XMFLOAT2 jidian = { pathMap[i][j].jinD.x,pathMap[i][j].jinD.z };
			XMFLOAT2 yuandian = { pathMap[i][j].YuanD.x,pathMap[i][j].YuanD.z };
			if (endPos.x >= jidian.x&&endPos.y <= jidian.y&&endPos.x <= yuandian.x&&endPos.y >= yuandian.y)
			{
				enPos = { i,j };
			}
		}
	}
}

void AStarPathFinding::RestMapForWalls(pathNode pathmap[Rows][Cows], std::vector<MyPoint> UpMap)
{
	for (int o = 0; o < (ab - 1); o++)
	{
		for (int i = 0; i < (ab - 1); i++)
		{
			pathMap[o][i].val = pathmap[o][i].val;
		}
	}
	for (int i = 0; i < UpMap.size(); i++)
	{
		int R = UpMap[i].row;
		int C = UpMap[i].cow;
		pathMap[R][C].val = 1;
	}
}

void AStarPathFinding::RestMapForwall()
{
	pathMap[beginPos.row][beginPos.cow].val = 0.0f;
}

bool AStarPathFinding::Box(XMFLOAT2 cPoint, XMFLOAT2 p1, XMFLOAT2 p3)
{
	bool blResult = (cPoint.x >= p1.x && cPoint.x <= p3.x) && (cPoint.y >= p1.y && cPoint.y <= p3.y);
	return blResult;
}

bool AStarPathFinding::PathPrinting(treeNode * pNode)
{
	if (pNode == nullptr)
		return false;
	else if (pNode != nullptr)
	{
		MyDirect asd;
		asd.Pos = pNode->Pos;
		asd.dire = pathMap[asd.Pos.row][asd.Pos.cow].Center;
		VPath2.push_back(asd);
		pTemp = pTemp->pParent;
		if (pTemp != nullptr)
		{
			PathPrinting(pTemp);
		}
	}
	return  true;
}

std::vector<MyDirect> AStarPathFinding::GetVPath()
{
	return VPath;
}

void AStarPathFinding::SetStartNode()
{
	//beginPos={22,25};
	VPath2.clear();
	//buffer.clear();
	pathMap[beginPos.row][beginPos.cow].iswark = true;
	treeNode*	ptreeRoot;
	ptreeRoot = new treeNode;
	memset(ptreeRoot, 0, sizeof treeNode);//init 0
	ptreeRoot->Pos = beginPos;
	if(pTemp!=NULL)
	memset(pTemp, 0, sizeof treeNode);
	pTemp = ptreeRoot;
	isfindEnd = false;
}

void AStarPathFinding::PathReset()
{
	//VPath.clear(); 
	for (int o = 0; o < (ab - 1); o++)
	{
		for (int i = 0; i < (ab - 1); i++)
		{
			pathMap[o][i].iswark = false;
		}
	}
}
