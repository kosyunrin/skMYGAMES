#pragma once
enum FSM_SATE
{
	idle,
	walk,
	run,
	attack,
	die,
	move,
	unmove,
}; 
class FSM_AI
{
protected:
	FSM_SATE State;
	std::unique_ptr<AStarPathFinding> pAstar;
	ZOMBIEDATE sDate;
public:
	void FSM(float dt)
	{
		switch (State)
		{
		case move:
			FSMMove(dt);
			break;
		case unmove:
			UNMove(dt);
			break;
		}
	}
	virtual void FSMMove(float dt) {};
	virtual void UNMove(float dt) {};

public:
	void SetSate(FSM_SATE state) { State = state; }
	AStarPathFinding* GetPointForAstar() { return pAstar.get(); }
	ZOMBIEDATE* GetStrutForData() { return &sDate; }

};

