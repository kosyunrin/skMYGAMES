using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreCount : Father
{

	public struct ScoreCounts
	{
	public int normalPaturu;    // ノーマル
	public int RiKuPaturu;      // リンク
    public int CategoryNum;     // 種類
    public bool RolePaturu_Wind; // キャラ
    public bool RolePaturu_Fire; //キャラ
    public bool RolePaturu_Water;// キャラ
    }
    public struct Skill_Core
    {
        public int WaterSkillScore;
        public int FireSkillScore;
        public int WindSkillScore;
    }

    ScoreCounts _scorecounts;
    Vector3 _EachCategoryNum;   // x : 水, y : 風, z : 火
    public Skill_Core SkillCore;
    // Use this for initialization
    void Start () {
		ScoreCountZero ();
        SetAllSkillCoreCountZero();

    }

	// Update is called once per frame
	void Update () {
		//Debug.Log (_scorecounts.normalPaturu);
		//Debug.Log (_scorecounts.RiKuPaturu);
		if (Input.GetKeyDown("k"))
		{
			Debug.Log (GetPaturuCount ().normalPaturu);
			ScoreCountZero ();
		}
        _scorecounts.CategoryNum = 0;
        if (_EachCategoryNum.x > 1.0f) { _scorecounts.CategoryNum++; }
        if (_EachCategoryNum.y > 1.0f) { _scorecounts.CategoryNum++; }
        if (_EachCategoryNum.z > 1.0f) { _scorecounts.CategoryNum++; }


    }
    public void ScoreCountZero()
	{
		_scorecounts.normalPaturu = 0;
		_scorecounts.RiKuPaturu = 0;
		_scorecounts.RolePaturu_Water = false;
        _scorecounts.CategoryNum = 0;
        _scorecounts.RolePaturu_Wind = false;
        _scorecounts.RolePaturu_Fire = false;

        _EachCategoryNum = new Vector3(0.0f, 0.0f, 0.0f);
    }

    public ScoreCounts GetPaturuCount()
	{
        ScoreCounts score = _scorecounts;
        ScoreCountZero();

        return score;
	}
	public void PaturuMathCount(string _name)
	{
		switch (_name)
		{
		case"water(Clone)":
			_scorecounts.normalPaturu += 1;
            _EachCategoryNum.x += 1;
            SkillCore.WaterSkillScore += 1;
                Debug.Log(SkillCore.WaterSkillScore);
            break;
		case"wind(Clone)":
			_scorecounts.normalPaturu += 1;
                _EachCategoryNum.y += 1;
                SkillCore.WindSkillScore += 1;
                break;
		case"fire(Clone)":
			_scorecounts.normalPaturu += 1;
                _EachCategoryNum.z += 1;
                SkillCore.FireSkillScore += 1;
                break;
		case"link(Clone)":
			_scorecounts.RiKuPaturu += 1;
            break;
        case "waterRole(Clone)":
                _scorecounts.RolePaturu_Water =true;
                _scorecounts.normalPaturu += 1;
                break;
        case "windRole(Clone)":
                _scorecounts.RolePaturu_Wind =true;
                _scorecounts.normalPaturu += 1;
                break;
        case "fireRole(Clone)":
                _scorecounts.RolePaturu_Fire =true;
                _scorecounts.normalPaturu += 1;
                break;
        }
	}
    public void SetAllSkillCoreCountZero()
    {
        SkillCore.WaterSkillScore = 0;
        SkillCore.FireSkillScore = 0;
        SkillCore.WindSkillScore = 0;
    }
    public Skill_Core GetSkillCore()
    {
        return SkillCore;
    }

}
