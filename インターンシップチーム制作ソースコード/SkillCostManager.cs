using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class SkillCostManager
{
    public struct RoleSkill_Cost
    {
        public int WindSkill9_Cost;
        public int WindSkill1_Cost;
        public int WindSkill12_Cost;
        public int WindSkill4_Cost;
        public int WaterSkill7_Cost;
        public int WaterSkill2_Cost;
        public int WaterSkill10_Cost;
        public int WaterSkill6_Cost;
        public int FireSkill3_Cost;
        public int FireSkill8_Cost;
        public int FireSkill11_Cost;
        public int FireSkill5_Cost;
    }
    public struct RoleNumber
    {
        public int WaterNumber;
        public int FireNumber;
        public int WindNumber;
    }
    public  struct SKillControl
    {
        public bool Water6Swich;
    }

    static WaterSkill6 Skill6Code;
    public static RoleSkill_Cost RoleCost;
    public static RoleNumber Role_Number;
    public static SKillControl Skill_Control;
    // Use this for initialization
    public static WaterSkill6 GetSkill6Code()
	{       
		GameObject aa = GameObject.Find("WaterSkill6Control(Clone)");
		if (aa != null) {
			Skill6Code = aa.GetComponentInChildren<WaterSkill6> ();
			return Skill6Code;
		} else
			return null;
    }
    public static void SetRoleCost()
    {
        //Water
        RoleCost.WaterSkill10_Cost = 18;
        RoleCost.WaterSkill2_Cost = 12;
        RoleCost.WaterSkill6_Cost = 20;
        RoleCost.WaterSkill7_Cost = 10;
        //fire
        RoleCost.FireSkill11_Cost = 18;
        RoleCost.FireSkill3_Cost = 15;
        RoleCost.FireSkill5_Cost = 20;
        RoleCost.FireSkill8_Cost = 16;
        //wind
        RoleCost.WindSkill12_Cost = 16;
        RoleCost.WindSkill1_Cost = 14;
        RoleCost.WindSkill9_Cost = 7;
        RoleCost.WindSkill4_Cost = 20;
    }
}
