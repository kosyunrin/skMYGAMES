#pragma once
#include"main.h"
#include"FSM_AI.h" 
#include"CBlackBloard.h"

enum BET
{
	Runing,
	Success,
	Failed,
};

class CBET_Node
{
	
protected:
	int index = 0;
	
public:
	
	virtual BET Update(FSM_SATE& fsmstate, CBlackBloard* pBlackBloard) = 0;
	std::vector<CBET_Node* > m_child;
	void AddNode(CBET_Node* pNode)
	{
		m_child.push_back(pNode);
	}
};
class CSequence :public CBET_Node
{

public:
	BET Update(FSM_SATE& fsmstate, CBlackBloard* pBlackBloard) override
	{
		BET state;
		state = m_child[index]->Update(fsmstate, pBlackBloard);
		switch (state)
		{
		case Runing:
			index=0;
			return Runing;
			break;
		case Success:
			index++;
			return Success;
			break;
		case Failed:
			return Failed;
			break;
		}
	}
};
class CSeletor :public CBET_Node
{

public:
	BET Update(FSM_SATE& fsmstate, CBlackBloard* pBlackBloard) override
	{
		BET state;
		state = m_child[index]->Update(fsmstate, pBlackBloard);
		switch (state)
		{
		case Runing:
			index=0;
			return Runing;
			break;
		case Success:
			return Success;
			break;
		case Failed:
			index++;
			return Failed;
			break;
		}
	}
};
class CMove :public CBET_Node
{

public:
	BET Update(FSM_SATE& fsmstate, CBlackBloard* pBlackBloard) override
	{
		BET state;
		fsmstate = move;
		state = Runing;

		switch (state)
		{
		case Runing:
			return Runing;
			break;
		case Success:
			return Success;
			break;
		case Failed:
			index++;
			return Failed;
			break;
		}
	}
};

class CControlNode :public CBET_Node
{
private:
	int BlackBloaad_Index;

public:
	BET Update(FSM_SATE& fsmstate, CBlackBloard* pBlackBloard) override
	{
		BET state;
		if (pBlackBloard->isBool(BlackBloaad_Index))
			state = Success;
		else
			state = Failed;

		switch (state)
		{
		case Runing:
			return Runing;
			break;
		case Success:
			return Success;
			break;
		case Failed:
			return Failed;
			break;
		}
	}
	void SetBlackBloadIndex(int num)
	{
		BlackBloaad_Index = num;
	}
};
class UnMove :public CBET_Node
{
public:

	BET Update(FSM_SATE& fsmstate, CBlackBloard* pBlackBloard) override
	{
		BET state;
		fsmstate = unmove;
		state = Runing;

		switch (state)
		{
		case Runing:
			return Runing;
			break;
		case Success:
			return Success;
			break;
		case Failed:
			return Failed;
			break;
		}
	}
};