using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Father : MonoBehaviour
{
    protected struct TagName
    {
        public string TagName0;
        public string TagName1;
        public string TagName2;
        public string FinishTagName;
        public string RinkuName;
        //public string Changename;
    }
    protected struct Name
    {
        public string Name0;
        public string Name1;
        public string Name2;
        public string NameRoleWater;
        public string NameRoleFire;
        public string NameRoleWind;
        public string RinkuName;
        // public string Changename;
    }

    protected Name NPaturu;
    protected TagName Paturu;
    void Start()
    {

    }
    protected void TName()
    {
        Paturu.TagName0 = "ListType0";
        Paturu.TagName1 = "type1";
        Paturu.TagName2 = "type2";
        Paturu.FinishTagName = "Untagged";


        Paturu.RinkuName = "RK";
        NPaturu.Name0 = "water(Clone)";
        NPaturu.Name1 = "wind(Clone)";
        NPaturu.Name2 = "fire(Clone)";
        NPaturu.NameRoleFire = "fireRole(Clone)";
        NPaturu.NameRoleWater = "waterRole(Clone)";
        NPaturu.NameRoleWind = "windRole(Clone)";
        NPaturu.RinkuName = "link(Clone)";

    }


}
