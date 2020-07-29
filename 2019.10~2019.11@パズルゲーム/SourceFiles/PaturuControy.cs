using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public static class PaturuControy
{
    public struct WaterSKill_six
    {
        public bool UpdaterCountDown;
		public int  StartCountDown;
		public bool WaterskillsixDestroy;
    }
	public struct NameClass
    {
        public string FireTag;
        public string WaterTag;
        public string LinkTag;
        public string WindTag;
        public string FireName;
        public string WaterName;
        public string LinkName;
        public string WindName;
        public string FinishTagName;
        public string WaterRoleName;
        public string FireRoleName;
        public string WindRoleName;
    }
    public static  NameClass PazuruTagAndName;
    //public static SKillControl Skill;
    static GameObject[] Paturus;
    static List<GameObject> objlist;
    static List<GameObject> Now_ColorChangeObj;
    static List<GameObject> test1;
    static List<GameObject> test2;
    static List<GameObject> test3;
    static List<GameObject> test4;
    static List<GameObject> test5;
    static List<GameObject> test6;
    static List<GameObject> test7;
    static List<GameObject> test8;
    static List<GameObject> test9;
    static GameObject S_hitObj;
    // Use this for initialization
	public static WaterSKill_six waterskill_six;
	//static public List<GameObject> ColorCtrALLObjlist;
	static public bool ColorUpadateCtr;
    public static void ImagesControy(GameObject hitobj,string FristTagname)
    {
        S_hitObj = null;
        if (S_hitObj == null)
        {
            S_hitObj = hitobj;
        }
        objlist = new List<GameObject>();
        Now_ColorChangeObj=new List<GameObject>();
        test1 = new List<GameObject>();
        test2  = new List<GameObject>();
        test3  = new List<GameObject>();
        test4   = new List<GameObject>();
        test5 = new List<GameObject>();
        test6 = new List<GameObject>();
        test7 = new List<GameObject>();
        test8 = new List<GameObject>();
        test9 = new List<GameObject>();
        if(hitobj.tag==FristTagname)
        Paturus = GameObject.FindGameObjectsWithTag(hitobj.tag);
        else if(hitobj.tag!=FristTagname)
        Paturus = GameObject.FindGameObjectsWithTag(FristTagname);
        foreach (GameObject type0 in Paturus)
        {
            if (Paturus != null)
            {
                //Debug.Log("asdasd");
                // type0.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 100);
                objlist.Add(type0);
            }
        }
        if (objlist!=null)
        {
            //Debug.Log(objlist.Count);
            objlist.Remove(S_hitObj);
            for (int i = 0; i < objlist.Count; i++)
            {
                //if (S_hitObj != objlist[i])
                //{
                var dist = Vector2.Distance(S_hitObj.transform.position, objlist[i].transform.position);
                if (dist <= 0.9/* && S_hitObj != objlist[i]*/)
                {

                    objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                    Now_ColorChangeObj.Add(objlist[i]);
                    //Debug.Log(Now_ColorChangeObj.Count);
                    //loopColorChangeObj(objlist[i]);
                    //loop(objlist[i], S_hitObj);
                    // }
                }
            }
            if (Now_ColorChangeObj != null)
            {
                for (int i = 0; i < Now_ColorChangeObj.Count; i++)
                {
                    objlist.Remove(Now_ColorChangeObj[i]);
                }
                for (int i = 0; i < Now_ColorChangeObj.Count; i++)
                {
                    loopColorChangeObj(Now_ColorChangeObj[i]);
                }
            }
        }
        //GameObject[] _paturus = new GameObject[Paturus.Length];
        //_paturus[0].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 100);
    }
    static void loopColorChangeObj(GameObject changeObj)
    {
        for(int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                test1.Add(objlist[i]);
            }
        }
        if(test1!=null)
        {
            for (int i = 0; i < test1.Count; i++)
            {
                objlist.Remove(test1[i]);
            }
            for (int i = 0; i < test1.Count; i++)
            {
                loopColorChangeObj2(test1[i]);
            }
        }
    }
    static void loopColorChangeObj2(GameObject changeObj)
    {
        //objlist.Remove(changeObj);
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                //Now_ColorChangeObj.Add(objlist[i]);
                test2.Add(objlist[i]);
            }
        }
        if (test2 != null)
        {
            for (int i = 0; i < test2.Count; i++)
            {
                objlist.Remove(test2[i]);
            }
            for (int i = 0; i < test2.Count; i++)
            {
                loopColorChangeObj3(test2[i]);
            }
        }
    }
    static void loopColorChangeObj3(GameObject changeObj)
    {
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                test3.Add(objlist[i]);
            }
        }
        if (test3 != null)
        {
            for (int i = 0; i < test3.Count; i++)
            {
                objlist.Remove(test3[i]);
            }
            for (int i = 0; i < test3.Count; i++)
            {
                loopColorChangeObj4(test3[i]);
            }
        }
    }
    static void loopColorChangeObj4(GameObject changeObj)
    {
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                test4.Add(objlist[i]);
            }
        }
        if (test4 != null)
        {
            for (int i = 0; i < test4.Count; i++)
            {
                objlist.Remove(test4[i]);
            }
            for (int i = 0; i < test4.Count; i++)
            {
                loopColorChangeObj5(test4[i]);
            }
        }
    }
    static void loopColorChangeObj5(GameObject changeObj)
    {
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                test5.Add(objlist[i]);
            }
        }
        if (test5 != null)
        {
            for (int i = 0; i < test5.Count; i++)
            {
                objlist.Remove(test5[i]);
            }
            for (int i = 0; i < test5.Count; i++)
            {
                loopColorChangeObj6(test5[i]);
            }
        }
    }
    static void loopColorChangeObj6(GameObject changeObj)
    {
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                test6.Add(objlist[i]);
            }
        }
        if (test6 != null)
        {
            for (int i = 0; i < test6.Count; i++)
            {
                objlist.Remove(test6[i]);
            }
            for (int i = 0; i < test6.Count; i++)
            {
                loopColorChangeObj7(test6[i]);
            }
        }
    }
    static void loopColorChangeObj7(GameObject changeObj)
    {
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                test7.Add(objlist[i]);
            }
        }
        if (test7 != null)
        {
            for (int i = 0; i < test7.Count; i++)
            {
                objlist.Remove(test7[i]);
            }
            for (int i = 0; i < test7.Count; i++)
            {
                loopColorChangeObj8(test7[i]);
            }
        }
    }
    static void loopColorChangeObj8(GameObject changeObj)
    {
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                test8.Add(objlist[i]);
            }
        }
        if (test8 != null)
        {
            for (int i = 0; i < test8.Count; i++)
            {
                objlist.Remove(test8[i]);
            }
            for (int i = 0; i < test8.Count; i++)
            {
                loopColorChangeObj9(test8[i]);
            }
        }
    }
    static void loopColorChangeObj9(GameObject changeObj)
    {
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                test9.Add(objlist[i]);
            }
        }
        if (test9 != null)
        {
            for (int i = 0; i < test9.Count; i++)
            {
                objlist.Remove(test9[i]);
            }
            for (int i = 0; i < test9.Count; i++)
            {
                loopColorChangeObj10(test9[i]);
            }
        }
    }
    static void loopColorChangeObj10(GameObject changeObj)
    {
        for (int i = 0; i < objlist.Count; i++)
        {
            var dist = Vector2.Distance(changeObj.transform.position, objlist[i].transform.position);
            if (dist <= 0.9)
            {
                objlist[i].GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                //test9.Add(objlist[i]);
            }
        }
        //if (test9 != null)
        //{
        //    for (int i = 0; i < test9.Count; i++)
        //    {
        //        objlist.Remove(test9[i]);
        //    }
        //    for (int i = 0; i < test9.Count; i++)
        //    {
        //        loopColorChangeObj10(test9[i]);
        //    }
        //}
    }
    public static void sethitobjCancel(string objname)
    {
        Paturus = GameObject.FindGameObjectsWithTag(objname);
        foreach (GameObject type0 in Paturus)
        {
            if (Paturus != null)
            {
                
                type0.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 100);
            }
        }
    }
    public static void SetColorAllLight(string N1,string N2, string N3)
    {
        string[] Normalpaturu;
        Normalpaturu = new string[3];
        Normalpaturu[0] = N1;
        Normalpaturu[1] = N2;
        Normalpaturu[2] = N3;
        for (int i = 0; i < 3; i++)
        {
            Paturus = GameObject.FindGameObjectsWithTag(Normalpaturu[i]);
            foreach (GameObject type0 in Paturus)
            {
                if (Paturus != null)
                {
                    type0.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                }
            }
        }
    }
     public static void SetColorAllBlack(string N1,string N2, string N3)
    {
        string[] Normalpaturu;
        Normalpaturu = new string[3];
        Normalpaturu[0] = N1;
        Normalpaturu[1] = N2;
        Normalpaturu[2] = N3;
        for (int i = 0; i < 3; i++)
        {
            Paturus = GameObject.FindGameObjectsWithTag(Normalpaturu[i]);
            foreach (GameObject type0 in Paturus)
            {
                if (Paturus != null)
                {

                    type0.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 100);
                }
            }
        }
    }
    static public void  NameSet()
    {
        PazuruTagAndName.FireTag = "type2";
        PazuruTagAndName.WaterTag = "ListType0";
        PazuruTagAndName.WindTag = "type1";
        PazuruTagAndName.LinkTag = "RK";
        PazuruTagAndName.FinishTagName = "Untagged";
        PazuruTagAndName.WaterRoleName = "waterRole(Clone)";
        PazuruTagAndName.FireRoleName = "fireRole(Clone)";
        PazuruTagAndName.WindRoleName = "windRole(Clone)";

        PazuruTagAndName.FireName = "fire(Clone)";
        PazuruTagAndName.WaterName = "water(Clone)";
        PazuruTagAndName.WindName = "wind(Clone)";
        PazuruTagAndName.LinkName = "link(Clone)";
    }
}
