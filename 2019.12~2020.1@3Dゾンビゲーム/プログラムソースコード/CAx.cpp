//#include"main.h"
//#include "CAx.h"
//
//CAx::CAx()
//{
//	beginPos = {23,21};
//	enPos = { 34,37 };
//	endPrintpath = false;
//}
//
//
//CAx::~CAx()
//{
//}
//
//void CAx::Init(std::vector<SStaticMode*> meshes)
//{
//	//
//	XMFLOAT3 m_Vertex[ab*ab];
//	for (int z = 0; z < ab; z++)
//	{
//		for (int x = 0; x < ab; x++)
//		{
//			XMMATRIX world;
//			world = XMMatrixScaling(3.0f, 3.0f, 3.0f);//拡大
//			m_Vertex[z * ab + x].x = x - ab / 2.0f;
//			m_Vertex[z * ab + x].z = -z + ab / 2.0f;
//			m_Vertex[z * ab + x].y = 0.0f/*sinf( x * 0.1f ) * sinf(z * 0.1f) * 2.0f*/;
//			XMVECTOR m_VerXM = XMVector3TransformCoord(XMLoadFloat3(&m_Vertex[z * ab + x]), world);
//			XMStoreFloat3(&m_Vertex[z * ab + x], m_VerXM);
//		}
//	}
//	//
//	unsigned short index[(ab - 1)*(ab - 1) * 6];
//	int count = 0;
//	for (int o = 0; o < (ab - 1); o++)
//	{
//		for (int i = 0; i < (ab - 1); i++)
//		{
//			index[count] = (o*((ab - 1) + 1)) + i;
//			//fang ru jin dian 
//			pathMap[o][i].jinD = m_Vertex[index[count]];
//			count++;
//			index[count] = (o*((ab - 1) + 1)) + (i + 1);
//			count++;
//			index[count] = ((o + 1)*((ab - 1) + 1)) + i;
//			count++;
//			index[count] = (o*((ab - 1) + 1)) + (i + 1);
//			count++;
//			index[count] = ((o + 1)*((ab - 1) + 1)) + i;
//			count++;
//			index[count] = ((o + 1)*((ab - 1) + 1)) + (i + 1);
//			//fang ru yuan dian 
//			pathMap[o][i].YuanD = m_Vertex[index[count]];
//			count++;
//			pathMap[o][i].iswark = false;
//			pathMap[o][i].val = 0;
//			float d = 1.5f;
//			pathMap[o][i].Center = { (pathMap[o][i].jinD.x + d),0,(pathMap[o][i].jinD.z>=0)? (pathMap[o][i].jinD.z + d):(pathMap[o][i].jinD.z - d) };
//
//		}
//	}
//
//
//
//
//	//pathMap[Rows][Cows] = { 0 };
//
//	/*for (int index = 0; index < meshes.size(); index++)
//	{
//		for (UINT g = 0; g < meshes[index]->vs.size(); g++)
//		{
//			XMMATRIX world;
//			world = XMMatrixRotationX(XMConvertToRadians(-90.0f));
//			world *= XMMatrixRotationY(XMConvertToRadians(90.0f));
//			world *= XMMatrixScaling(0.01f, 0.01f, 0.01f);
//			world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
//			XMVECTOR meshPos = XMVector3TransformCoord (XMLoadFloat3(& meshes[index]->vs[g].Position),
//				world);
//			XMFLOAT3 pos;
//			XMStoreFloat3(&pos, meshPos);
//			MesPos.push_back(pos);
//			XMFLOAT2 C = { pos.x,pos.z };
//			for (int i = 0; i < Rows; i++)
//			{
//				for (int j = 0; j < Cows; j++)
//				{
//					XMFLOAT2 jidian = { pathMap[i][j].jinD.x,pathMap[i][j].jinD.z };
//					XMFLOAT2 yuandian = { pathMap[i][j].YuanD.x,pathMap[i][j].YuanD.z };
//					if (C.x>=jidian.x&&C.y<=jidian.y&&C.x<=yuandian.x&&C.y>=yuandian.y)
//					{
//						if (pos.y >= 1.5f)
//							pathMap[i][j].val = 1;
//					}
//				}
//			}
//		}
//	}*/
//	
//	
//	for (int x = 26; x < 29; x++)
//	{
//		pathMap[x][23].val = 1;
//	}
//	for (int x = 26; x < 29; x++)
//	{
//		pathMap[x][22].val = 1;
//	}
//	pathMap[31][37].val = 1;
//	pathMap[32][36].val = 1;
//	pathMap[32][35].val = 1;
//	pathMap[33][35].val = 1;
//	pathMap[34][34].val = 1;
//	pathMap[34][35].val = 1;
//	//mapで起点を標記する過ぎてしました、
//	pathMap[beginPos.row][beginPos.cow].iswark = true;
//	// 起点を樹のRootを入れて
//	treeNode*	ptreeRoot;
//	ptreeRoot = new treeNode;
//	memset(ptreeRoot, 0, sizeof treeNode);//init 0
//	ptreeRoot->Pos = beginPos;
//	//経路探索
//	pTemp = ptreeRoot;
//	isfindEnd = false;
//	//1.0 检测当前点那些可以走，那些可以不走
//	//1.1 计算所有评估点的F值
//	//1.2 找出F值最小的点 走  并从Buffer中删除这个点
//	//1.3 判断是否找到终点，判断是否整个地图都找完还是没找到终点
//
//	
//}
//
//void CAx::Update()
//{
//	if (!isfindEnd)
//	{
//		//1.0f 检测周当前点周围那些点要纳入评估
//		for (int i = 0; i < 8; i++)
//		{
//			treeNode* pChild = new treeNode;
//			memset(pChild, 0, sizeof treeNode);//init 0
//			pChild->Pos = pTemp->Pos;
//			switch (i)
//			{
//			case p_up:
//				pChild->Pos.row--;
//				pChild->Pos.g += ZlineDaijia;
//				break;
//			case p_down:
//				pChild->Pos.row++;
//				pChild->Pos.g += ZlineDaijia;
//				break;
//			case p_left:
//				pChild->Pos.cow--;
//				pChild->Pos.g += ZlineDaijia;
//				break;
//			case p_right:
//				pChild->Pos.cow++;
//				pChild->Pos.g += ZlineDaijia;
//				break;
//			case p_lup:
//				pChild->Pos.row--;
//				pChild->Pos.cow--;
//				pChild->Pos.g += XlineDaijia;
//				break;
//			case p_ldown:
//				pChild->Pos.row++;
//				pChild->Pos.cow--;
//				pChild->Pos.g += XlineDaijia;
//				break;
//			case p_rup:
//				pChild->Pos.row--;
//				pChild->Pos.cow++;
//				pChild->Pos.g += XlineDaijia;
//				break;
//			case p_rdown:
//				pChild->Pos.row++;
//				pChild->Pos.cow++;
//				pChild->Pos.g += XlineDaijia;
//				break;
//			}
//			//判断这个点能不能走 要不要评估 
//			if (canwalk(pChild->Pos, pathMap))
//			{
//				//ji suan Fzhi 
//				pChild->Pos.h = GetH(pChild->Pos, enPos);
//				pChild->Pos.Setf();
//				//入树
//				pTemp->child.push_back(pChild);
//				pChild->pParent = pTemp;
//
//				buffer.push_back(pChild);
//			}
//		}
//		//找出F值最小的那个 并从buff中删除这个点
//		std::vector<treeNode*> ::iterator itMin;
//		std::vector<treeNode*> ::iterator it;
//		itMin = buffer.begin();
//		for (it = buffer.begin(); it != buffer.end(); it++)
//		{
//			if ((*itMin)->Pos.f > (*it)->Pos.f)
//				itMin = it;
//		}
//		
//		pathMap[pTemp->Pos.row][pTemp->Pos.cow].iswark = true;
//		pTemp = *itMin; //zou
//		buffer.erase(itMin);
//		//判断是否找到终点。 判断是否整个地图都找完还是没找到终点
//		if (pTemp->Pos.row == enPos.row&&pTemp->Pos.cow == enPos.cow)
//			isfindEnd = true;
//		if (buffer.empty()) isfindEnd = true;
//	}
//	else
//	{
//		//Dayin lujin
//		if (!PathPrinting(pTemp))
//		{
//			endPrintpath = true;
//		}
//		//pTemp = pTemp->pParent;
//		
//		
//	}
//}
//
//void CAx::Draw()
//{
//}
//
//void CAx::Uinit()
//{
//}
//
//bool CAx::canwalk(MyPoint pos, pathNode pathmap[Rows][Cows])
//{
//	if (pos.row < 0 || pos.row >= Rows || pos.cow < 0 || pos.cow >= Cows) return false;
//	if (pathMap[pos.row][pos.cow].val == 1) return false;
//	if (pathMap[pos.row][pos.cow].iswark == 1) return false;
//	return true;
//}
//
//int CAx::GetH(MyPoint pos, MyPoint endpos)
//{
//	int x = (pos.cow > enPos.cow) ? (pos.cow - endpos.cow) : (endpos.cow - pos.cow);
//	int y = (pos.row > enPos.row) ? (pos.row - endpos.row) : (endpos.row - pos.row);
//
//	return ZlineDaijia*(x+y);
//}
//
//void CAx::SetbeginPos(XMFLOAT2 bePos)
//{
//	for (int i = 0; i < Rows; i++)
//	{
//		for (int j = 0; j < Cows; j++)
//		{
//			XMFLOAT2 jidian = { pathMap[i][j].jinD.x,pathMap[i][j].jinD.z };
//			XMFLOAT2 yuandian = { pathMap[i][j].YuanD.x,pathMap[i][j].YuanD.z };
//			if (bePos.x >= jidian.x&&bePos.y <= jidian.y&&bePos.x <= yuandian.x&&bePos.y >= yuandian.y)
//			{
//				beginPos = { i,j };
//				//ptreeRoot = new treeNode;
//				//memset(ptreeRoot, 0, sizeof treeNode);//init 0
//				//ptreeRoot->Pos = beginPos;
//			
//
//				//pathMap[beginPos.row][beginPos.cow].iswark = true;
//			}
//		}
//		CRenderer::Debug_move_v2[0] = beginPos.row;
//		CRenderer::Debug_move_v2[1] = beginPos.cow;
//	}
//}
//
//void CAx::SetTargetPos(XMFLOAT2 endPos)
//{
//	MyPoint pos = { endPos.x,endPos.y };
//	enPos = pos;
//}
//
//bool CAx::Box(XMFLOAT2 cPoint, XMFLOAT2 p1, XMFLOAT2 p3)
//{
//		bool blResult = (cPoint.x >= p1.x && cPoint.x <= p3.x) && (cPoint.y >= p1.y && cPoint.y <= p3.y);
//		return blResult;
//}
//
//bool CAx::PathPrinting(treeNode * pNode)
//{
//	if (pNode == nullptr)
//		return false;
//	else if (pNode != nullptr)
//	{
//		MyDirect asd;
//		asd.Pos = pNode->Pos;
//		asd.dire = pathMap[asd.Pos.row][asd.Pos.cow].Center;
//		directPos1.push_back(asd);
//		pTemp = pTemp->pParent;
//		if (pTemp != nullptr)
//		{
//			PathPrinting(pTemp);
//		}
//	}
//	return  true;
//}
//
//std::vector<MyDirect> CAx::GetdirectPos1()
//{
//	return directPos1;
//}
//
//void CAx::SetStartNode()
//{
//	treeNode*	ptreeRoot;
//	ptreeRoot = new treeNode;
//	memset(ptreeRoot, 0, sizeof treeNode);//init 0
//	ptreeRoot->Pos = beginPos;
//	pTemp = ptreeRoot;
//	buffer.clear();
//	isfindEnd = false;
//}
//
