using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class Mian : MonoBehaviour
{
    ScoreCount SkillScore;
    GameObject[] Paturu_typeCount;
    GameObject[] Paturu_rinku;
    GameObject[] Role_type;
    GameObject[] Role_typeCount;
    GameObject[] ActingObj;
    List<GameObject> AllPaturu;
    List<GameObject> obj2;
    // type0=fire, type1=water,type2=wind
    public GameObject Paturu_type0;
    public GameObject Paturu_type1;
    public GameObject Paturu_type2;
    public GameObject rinku_0bj;
    public GameObject Role_type0;
    public GameObject Role_type1;
    public GameObject Role_type2;
    public int CurrentRoleCount;
    public int CurrentRinKuCount;
    public int RoleSize;
    public int RinKuSize;
    public int RoletypeCount;
    //public int count;
    [SerializeField] int BeginSize;
    [SerializeField] int LinkDenominator;




    void Start()
    {
        obj2 = new List<GameObject>();
        AllPaturu = new List<GameObject>();
        NumberInitalize();
        ObjInitalize();
        PaturuInitalize();
        PaturuDown(BeginSize);
        SkillScore = this.GetComponent<ScoreCount>();
    }


    void Update()
    {
    }









    void PaturuInitalize()
    {

    }
    void NumberInitalize()
    {
    }
    public void ObjInitalize()
    {
        Paturu_typeCount = new GameObject[3];
        Paturu_typeCount[0] = Paturu_type0;
        Paturu_typeCount[1] = Paturu_type1;
        Paturu_typeCount[2] = Paturu_type2;
        Role_typeCount = new GameObject[RoletypeCount];
        Role_typeCount[0] = Role_type0;
        Role_typeCount[1] = Role_type1;
        Role_typeCount[2] = Role_type2;
        //Paturu_rinku = new GameObject[CurrentRinKuCount];
        //for (int Length = 0; Length < Paturu_rinku.Length; Length++)
        //{
        //    Paturu_rinku[Length] = rinku_0bj;
        //    AllPaturu.Add(Paturu_rinku[Length]);
        //}
        Role_type = new GameObject[RoleSize];
        ActingObj = new GameObject[100];
    }
    public void PaturuDown(int count)
    {
        //キャラ
        for (int Length = 0; Length < CurrentRoleCount; Length++)
        {

            Role_type[Length] = Paturu_typeCount[Random.Range(0, Paturu_typeCount.Length)];
            AllPaturu.Add(Role_type[Length]);
        }
        for (int Length = CurrentRoleCount; Length < RoleSize; Length++)
        {
            Role_type[Length] = Paturu_typeCount[Random.Range(0, Paturu_typeCount.Length)];
            AllPaturu.Add(Role_type[Length]);
            //float asd = CurrentRoleCount;
        }
        //リンク
        for (int Length = CurrentRinKuCount; Length < RinKuSize; Length++)
        {
            Role_type[Length] = Paturu_typeCount[Random.Range(0, Paturu_typeCount.Length)];
            AllPaturu.Add(Role_type[Length]);
        }
        for (int i = 0; i < count; i++)
        {
            GameObject obj;
            obj = Instantiate(AllPaturu[Random.Range(0, AllPaturu.Count)], new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 8.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(-2.48f, 2.44f)), null);

        }
        AllPaturu.Clear();
        //Debug.Log(AllPaturu.Count);
    }
    public void PaturuDowns(int count, int AllSize)
    {
        List<GameObject> obj = new List<GameObject>();
        //ActingObj[0] = Role_typeCount[Random.Range(0, Role_typeCount.Length)];
        //ActingObj[1] = Role_typeCount[Random.Range(0, Role_typeCount.Length)];
        //ActingObj[2] = Role_typeCount[Random.Range(0, Role_typeCount.Length)];
        //ActingObj[3] = Role_typeCount[Random.Range(0, Role_typeCount.Length)];
        //obj.Add(ActingObj[0]);
        //obj.Add(ActingObj[1]);
        //obj.Add(ActingObj[2]);
        //obj.Add(ActingObj[3]);
        for (int Length = 0; Length < AllSize; Length++)
        {

            ActingObj[Length] = Paturu_typeCount[Random.Range(0, Paturu_typeCount.Length)];
            obj.Add(ActingObj[Length]);
        }
        for(int i=0;i< LinkDenominator; i++)
        {
            obj2.Add(obj[Random.Range(0, obj.Count)]);
            obj2[0] = rinku_0bj;
        }
        for (int i = 0; i < count; i++)
        {
            GameObject _obj;
            _obj = Instantiate(obj[Random.Range(0, AllSize)], new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
        }

    }
    public void RinKuDown()
    {
        GameObject _obj;
        _obj = Instantiate(obj2[Random.Range(0, LinkDenominator)], new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
        obj2.Clear();
    }
    public void RoleDown(int Count)
    {
        //int WaterNumber=0;
        switch(SkillCostManager.Role_Number.WaterNumber)
        {
            case 7:
                if(SkillScore.SkillCore.WaterSkillScore>=SkillCostManager.RoleCost.WaterSkill7_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type0, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)),null);
                    SkillScore.SkillCore.WaterSkillScore = 0;
                    Count -= 1;
                }
                break;
            case 2:
                if (SkillScore.SkillCore.WaterSkillScore >= SkillCostManager.RoleCost.WaterSkill2_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type0, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.WaterSkillScore = 0;
                    Count -= 1;
               }
                break;
            case 10:
                if (SkillScore.SkillCore.WaterSkillScore >= SkillCostManager.RoleCost.WaterSkill10_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type0, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.WaterSkillScore = 0;
                    Count -= 1;
                }
                break;
            case 6:
                if (SkillScore.SkillCore.WaterSkillScore >= SkillCostManager.RoleCost.WaterSkill6_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type0, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.WaterSkillScore = 0;
                    Count -= 1;
                }
                break;
        }
        //int FireNumber = 0;
        switch (SkillCostManager.Role_Number.FireNumber)
        {
            case 3:
                if (SkillScore.SkillCore.FireSkillScore >= SkillCostManager.RoleCost.FireSkill3_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type2, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.FireSkillScore = 0;
                    Count -= 1;
                }
                break;
            case 8:
                if (SkillScore.SkillCore.FireSkillScore >= SkillCostManager.RoleCost.FireSkill8_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type2, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.FireSkillScore = 0;
                    Count -= 1;
                }
                break;
            case 11:
                if (SkillScore.SkillCore.FireSkillScore >= SkillCostManager.RoleCost.FireSkill11_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type2, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.FireSkillScore = 0;
                    Count -= 1;
                }
                break;
            case 5:
                if (SkillScore.SkillCore.FireSkillScore >= SkillCostManager.RoleCost.FireSkill5_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type2, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.FireSkillScore = 0;
                    Count -= 1;
                }
                break;
        }
        //int WindNumber = 9;
        switch (SkillCostManager.Role_Number.WindNumber)
        {
            case 9:
                if (SkillScore.SkillCore.WindSkillScore >= SkillCostManager.RoleCost.WindSkill9_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type1, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.WindSkillScore = 0;
                    Count -= 1;
                }
                break;
            case 1:
                if (SkillScore.SkillCore.WindSkillScore >= SkillCostManager.RoleCost.WindSkill1_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type1, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.WindSkillScore = 0;
                    Count -= 1;
                }
                break;
            case 12:
                if (SkillScore.SkillCore.WindSkillScore >= SkillCostManager.RoleCost.WindSkill12_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type1, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.WindSkillScore = 0;
                    Count -= 1;
                }
                break;
            case 4:
                if (SkillScore.SkillCore.WindSkillScore >= SkillCostManager.RoleCost.WindSkill4_Cost)
                {
                    GameObject _obj;
                    _obj = Instantiate(Role_type1, new Vector3(Random.Range(-1.4f, 1.4f), Random.Range(3.0f, 6.0f), 0.0f), Quaternion.Euler(0, 0, Random.Range(0.0f, 300.0f)), null);
                    SkillScore.SkillCore.WindSkillScore = 0;
                    Count -= 1;
                }
                break;
        }
    }


}
