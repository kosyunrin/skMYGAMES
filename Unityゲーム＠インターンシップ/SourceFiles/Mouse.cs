using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class Mouse : Father
{
    public bool sg;
    GameObject First_Paturu;
    GameObject Last_Paturu;
     List<GameObject> DeleteList;
    string currentTga;
    public float distance;
    Mian _min;
    GameObject[] type0s;
    //string nameku;
    bool SwichType;
    int DestoySize;
    int DestoyCount;
    float timer;
    [SerializeField] float Keeptimer;
    GameObject[] DestoyObjs;
    public bool Drag;
    [SerializeField] int KakuRiTuControl;
    ScoreCount CScorecount;
    LineRender CLine;
    int lineSize;
    int linePosCount;
    [SerializeField] GameObject Light;
    [SerializeField] int RinkControy;
    string Tag_ColorControlName;
    string Tag_ColorControlName2;
    bool Back;
    public bool drag2;
    bool TagnameCty;
    private GameSoundManager m_SoundManager;
    private const float startTime = 0.15f;
    int Destroy_Size;
    GameObject HitObj_;
    Vector3 hitObjV3Pos;
    string FirstNameTag;
    // Start is called before the first frame update
    void Start()
    {
        PaturuControy.NameSet();
        sg = false;
        TName();
        Drag = true;
        drag2 = true;
        DestoyCount = 0;
        timer = Keeptimer;
        DestoySize = -1;
        SwichType = false;
        DeleteList = new List<GameObject>();
        _min = GetComponent<Mian>();
        CScorecount = GetComponent<ScoreCount>();
        CLine = GetComponent<LineRender>();
        lineSize = 0;
        linePosCount = 0;
        Tag_ColorControlName = null;
        Back = false;
        m_SoundManager = GameObject.Find("GameSoundManager").GetComponent<GameSoundManager>();
        //PaturuControy.Skill.Water6Swich = false;
		PaturuControy.waterskill_six.UpdaterCountDown = false;
		PaturuControy.ColorUpadateCtr = false;
		SkillCostManager.Skill_Control.Water6Swich=false;
    }

    // Update is called once per frame
    void Update()
    {
        if (Drag&&drag2)
        {
            if (Input.GetMouseButton(0) && First_Paturu == null)
            {
                OnDragStart();
            }
            else if (Input.GetMouseButtonUp(0))
            {
                OnDragEnd();
            }
            else if (First_Paturu != null)
            {
                OnDragging();
            }
        }
        timerDesty();
		UpdateSkill6 ();
    }

    void OnDragStart()
    {
		PaturuControy.ColorUpadateCtr = true;
        lineSize = 1;
        linePosCount = 0;
        Tag_ColorControlName2 = null;
        CLine.Nodes_list.Clear();
        var Ball = GetCurrentHitCollider();
        if (Ball != null)
        {
            var ball = Ball.gameObject;
            var hitTga = Ball.tag;
            currentTga = Ball.tag;
            FirstNameTag = Ball.tag;
            Tag_ColorControlName = Ball.tag;
            if (hitTga == Paturu.TagName0)
            {
				Skill6(ball, ball, FirstNameTag);
                PaturuControy.SetColorAllBlack(Paturu.TagName0, Paturu.TagName1, Paturu.TagName2);
                ball.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                PaturuControy.ImagesControy(ball, Tag_ColorControlName);
                First_Paturu = ball;
                ball.tag = Paturu.FinishTagName;
                AddDeleteObj(ball);
                CLine.CLineRender(ball, linePosCount, lineSize);
                Bigger(ball);
                //Skill6(ball, First_Paturu, FirstNameTag);
            }
            else if (hitTga == Paturu.TagName1)
            {
				Skill6(ball, ball, FirstNameTag);
                PaturuControy.SetColorAllBlack(Paturu.TagName0, Paturu.TagName1, Paturu.TagName2);
                ball.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                PaturuControy.ImagesControy(ball, Tag_ColorControlName);
                First_Paturu = ball;
                //ball.tag = "typeX";
                ball.tag = Paturu.FinishTagName;
                AddDeleteObj(ball);
                CLine.CLineRender(ball, linePosCount, lineSize);
                Bigger(ball);
            }
            else if (hitTga == Paturu.TagName2)
            {
				Skill6(ball, ball, FirstNameTag);
                PaturuControy.SetColorAllBlack(Paturu.TagName0, Paturu.TagName1, Paturu.TagName2);
                ball.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                PaturuControy.ImagesControy(ball, Tag_ColorControlName);
                First_Paturu = ball;
                ball.tag = Paturu.FinishTagName;
                AddDeleteObj(ball);
                CLine.CLineRender(ball, linePosCount, lineSize);
                Bigger(ball);
            }
            else if (hitTga == Paturu.RinkuName)
            {
                First_Paturu = ball;
                ball.tag = Paturu.FinishTagName;
                AddDeleteObj(ball);
                CLine.CLineRender(ball, linePosCount, lineSize);
                Bigger(ball);
                SwichType = true;
            }
        }
    }


    public void OnDragEnd()
    {
        if (First_Paturu != null)
        {
            var length = DeleteList.Count;
            //DestoySize = length;
            if (length >= 3)
            {
                DestoyObjs = new GameObject[length];
                debug(length);
                DestoySize = length;
                for (var i = 0; i < length; i++)
                {
                    CScorecount.PaturuMathCount(DeleteList[i].name);
                    DestoyObjs[i] = DeleteList[i];
                    if (DeleteList[i].name == PaturuControy.PazuruTagAndName.FireName)
                        hitObjV3Pos = DeleteList[i].transform.position;
                    //Destroy(asdasd);
                }
				if (SkillCostManager.Skill_Control.Water6Swich && SkillCostManager.GetSkill6Code () != null)
					SkillCostManager.GetSkill6Code ().BackByMouseKeyUp (DestoyObjs);
                Drag = false;
                drag2 = false;
            }
            else
            {
                for (int i = 0; i < DeleteList.Count; i++)
                {
                    Smaller(DeleteList[i]);
                    TagModori(DeleteList[i]);
                }
                SwichType = false;//2019,10.6
                DeleteList.Clear();
                drag2 = true;
				if(SkillCostManager.GetSkill6Code()!=null)
					SkillCostManager.GetSkill6Code ().BackAllChange2 ();
            }
			PaturuControy.ColorUpadateCtr = false;
			//PaturuControy.Skill.Water6Swich = false;
            PaturuControy.SetColorAllLight(Paturu.TagName0, Paturu.TagName1, Paturu.TagName2);
            //CScorecount.SetAllSkillCoreCountZero();
            //if (Tag_ColorControlName2!=null)
            //PaturuControy.sethitobjCancel(Tag_ColorControlName2);
            //Debug.Log(Tag_ColorControlName2);
            First_Paturu = null;
            Last_Paturu = null;
            CLine.LineSwitch();
            CLine.destroyallNode();
            Back = false;
            //drag2 = true;
			//Debug.Log(PaturuControy.Skill.Water6Swich);
        }
    }

    void OnDragging()
    {
        var hitcol = GetCurrentHitCollider();
        if (hitcol != null)
        {
            var hitObj = hitcol.gameObject;
            HitObj_ = hitcol.gameObject;
            string nameRk = null;
            nameRk = hitObj.tag;
            //if (Last_Paturu != hitObj&&hitObj!=First_Paturu)
            //WaterSkill6(hitObj);
            if (nameRk == Paturu.RinkuName && !SwichType)
            {
                var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                if (dist <= distance)
                    currentTga = Paturu.RinkuName;
            }
            if (!SwichType&&!Back)
                switch (currentTga)
                {
                    case "ListType0":
                        if (Last_Paturu != hitObj && hitObj.name == NPaturu.Name0 && hitObj.tag != Paturu.FinishTagName || Last_Paturu != hitObj && hitObj.name == NPaturu.NameRoleWater && hitObj.tag != Paturu.FinishTagName)
                        {
                            var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                            if (dist <= distance)
                            {
								if(SkillCostManager.Skill_Control.Water6Swich&&SkillCostManager.GetSkill6Code()!=null
							&& PaturuControy.waterskill_six.StartCountDown>0)
                                SkillCostManager.GetSkill6Code().CountDownControl(hitObj);
						if (PaturuControy.waterskill_six.StartCountDown > 0) 
							{
								DraggingSKill6 (hitObj, First_Paturu, FirstNameTag);
							}
							//Debug.Log ("asdadsadasdsssssssssssssssssssssssssssss");
                              //  SkillCostManager.GetSkill6Code().CountBackControl(DeleteList);
                                hitObj.tag = Paturu.FinishTagName;
                                AddDeleteObj(hitObj);
                                linePosCount += 1;
                                lineSize += 1;
                                CLine.CLineRender(hitObj, linePosCount, lineSize);
                                Bigger(hitObj);
                                m_SoundManager.PlaySE((int)GameSoundManager.SoundInfo.se_puzzle_link, 1.0f, startTime);
                            }
                        }
                        break;
                    case "type1":
                        if (Last_Paturu != hitObj && hitObj.name == NPaturu.Name1 && hitObj.tag != Paturu.FinishTagName || Last_Paturu != hitObj && hitObj.name == NPaturu.NameRoleWind && hitObj.tag != Paturu.FinishTagName)
                        {
                            var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                            if (dist <= distance)
                            {
						if(SkillCostManager.Skill_Control.Water6Swich&&SkillCostManager.GetSkill6Code()!=null
							&& PaturuControy.waterskill_six.StartCountDown>0)
							SkillCostManager.GetSkill6Code().CountDownControl(hitObj);
						if (PaturuControy.waterskill_six.StartCountDown > 0) 
						{
							DraggingSKill6 (hitObj, First_Paturu, FirstNameTag);
						}
                                hitObj.tag = Paturu.FinishTagName;
                                AddDeleteObj(hitObj);
                                //test(hitObj);
                                linePosCount += 1;
                                lineSize += 1;
                                CLine.CLineRender(hitObj, linePosCount, lineSize);
                                Bigger(hitObj);
                                m_SoundManager.PlaySE((int)GameSoundManager.SoundInfo.se_puzzle_link, 1.0f, startTime);
                            }
                        }

                        break;
                    case "type2":
                        if (Last_Paturu != hitObj && hitObj.name == NPaturu.Name2 && hitObj.tag != Paturu.FinishTagName || Last_Paturu != hitObj && hitObj.name == NPaturu.NameRoleFire && hitObj.tag != Paturu.FinishTagName)
                        {
                            var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                            if (dist <= distance)
                            {
						if(SkillCostManager.Skill_Control.Water6Swich&&SkillCostManager.GetSkill6Code()!=null
							&& PaturuControy.waterskill_six.StartCountDown>0)
							SkillCostManager.GetSkill6Code().CountDownControl(hitObj);
						if (PaturuControy.waterskill_six.StartCountDown > 0) 
						{
							DraggingSKill6 (hitObj, First_Paturu, FirstNameTag);
						}
                                hitObj.tag = Paturu.FinishTagName;
                                AddDeleteObj(hitObj);
                                linePosCount += 1;
                                lineSize += 1;
                                CLine.CLineRender(hitObj, linePosCount, lineSize);
                                Bigger(hitObj);
                                m_SoundManager.PlaySE((int)GameSoundManager.SoundInfo.se_puzzle_link, 1.0f, startTime);
                            }
                        }
                        break;
                    case "RK":
                        if (Last_Paturu != hitObj && hitObj.tag != Paturu.FinishTagName)
                        {
                            var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                            if (dist <= distance)
                            {
                                hitObj.tag = Paturu.FinishTagName;
                                AddDeleteObj(hitObj);
                                linePosCount += 1;
                                lineSize += 1;
                                CLine.CLineRender(hitObj, linePosCount, lineSize);
                                Bigger(hitObj);
                                SwichType = true;
                                m_SoundManager.PlaySE((int)GameSoundManager.SoundInfo.se_puzzle_link, 1.0f, startTime);
                            }
                        }
                        break;
                }
            if (SwichType&&!Back)
                switch (nameRk)
                {
                    case "ListType0":
                        if (Last_Paturu != hitObj && hitObj.name == NPaturu.Name0 && hitObj.tag != Paturu.FinishTagName || Last_Paturu != hitObj && hitObj.name == NPaturu.NameRoleWater && hitObj.tag != Paturu.FinishTagName)
                        {
                            var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                            if (dist <= distance)
                            {
                                hitObj.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                                Tag_ColorControlName2 = hitObj.tag;
                                PaturuControy.ImagesControy(hitObj, hitObj.tag);
                                //if(Tag_ColorControlName!=hitObj.tag)
                                //PaturuControy.sethitobjCancel(Tag_ColorControlName);
                                hitObj.tag = Paturu.FinishTagName;
                                AddDeleteObj(hitObj);
                                linePosCount += 1;
                                lineSize += 1;
                                CLine.CLineRender(hitObj, linePosCount, lineSize);
                                Bigger(hitObj);
                                currentTga = Paturu.TagName0;
                                SwichType = false;
                                Debug.Log("sb");
                                m_SoundManager.PlaySE((int)GameSoundManager.SoundInfo.se_puzzle_link, 1.0f, startTime);
                            }
                        }
                        break;
                    case "type1":
                        if (Last_Paturu != hitObj && hitObj.name == NPaturu.Name1 && hitObj.tag != Paturu.FinishTagName || Last_Paturu != hitObj && hitObj.name == NPaturu.NameRoleWind && hitObj.tag != Paturu.FinishTagName)
                        {
                            var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                            if (dist <= distance)
                            {
                                hitObj.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                                Tag_ColorControlName2 = hitObj.tag;
                                PaturuControy.ImagesControy(hitObj, hitObj.tag);
                                //if (Tag_ColorControlName != hitObj.tag)
                                //PaturuControy.sethitobjCancel(Tag_ColorControlName);
                                hitObj.tag = Paturu.FinishTagName;
                                AddDeleteObj(hitObj);
                                linePosCount += 1;
                                lineSize += 1;
                                CLine.CLineRender(hitObj, linePosCount, lineSize);
                                Bigger(hitObj);
                                currentTga = Paturu.TagName1;
                                SwichType = false;
                                m_SoundManager.PlaySE((int)GameSoundManager.SoundInfo.se_puzzle_link, 1.0f, startTime);
                            }
                        }
                        //Debug.Log(currentTga);
                        break;
                    case "type2":
                        if (Last_Paturu != hitObj && hitObj.name == NPaturu.Name2 && hitObj.tag != Paturu.FinishTagName || Last_Paturu != hitObj && hitObj.name == NPaturu.NameRoleFire && hitObj.tag != Paturu.FinishTagName)
                        {
                            var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                            if (dist <= distance)
                            {
                                hitObj.GetComponentInChildren<SpriteRenderer>().color = new Color32(255, 255, 255, 255);
                                Tag_ColorControlName2 = hitObj.tag;
                                PaturuControy.ImagesControy(hitObj, hitObj.tag);
                                //if (Tag_ColorControlName != hitObj.tag)
                                //PaturuControy.sethitobjCancel(Tag_ColorControlName);
                                hitObj.tag = Paturu.FinishTagName;
                                AddDeleteObj(hitObj);
                                linePosCount += 1;
                                lineSize += 1;
                                CLine.CLineRender(hitObj, linePosCount, lineSize);
                                Bigger(hitObj);
                                currentTga = Paturu.TagName2;
                                SwichType = false;
                                m_SoundManager.PlaySE((int)GameSoundManager.SoundInfo.se_puzzle_link, 1.0f, startTime);
                            }
                        }


                        break;
                }
            //var dist2 = Vector2.Distance(mousePos(), DeleteList[DeleteList.Count - 2].transform.position);
            if (hitObj.tag==Paturu.FinishTagName&&hitObj!=Last_Paturu)
            {
               // Last_Paturu = hitObj;
                if (DeleteList.Count > 1)
                {
                    var dist = Vector2.Distance(Last_Paturu.transform.position, hitObj.transform.position);
                    var dist2 = Vector2.Distance(mousePos(), DeleteList[DeleteList.Count - 2].transform.position);
                    if (dist <= distance && dist2 <= 0.3)
                    {
						if(SkillCostManager.Skill_Control.Water6Swich&&SkillCostManager.GetSkill6Code()!=null
							&&PaturuControy.waterskill_six.StartCountDown>=0)
						SkillCostManager.GetSkill6Code().CountBackControl(DeleteList[DeleteList.Count - 1]);
						if(PaturuControy.waterskill_six.StartCountDown>=0)
						DraggingSKill6 (hitObj,First_Paturu,FirstNameTag);
                        Last_Paturu = hitObj;
                        GameObject node;
                        Back = true;
                        Smaller(DeleteList[DeleteList.Count - 1]);
                        TagModori(DeleteList[DeleteList.Count - 1]);
                        if(DeleteList[DeleteList.Count - 1].tag==Paturu.RinkuName)
                            currentTga = Tag_ColorControlName;
                        SwichType = false;
                        // DeleteList[DeleteList.Count - 1].tag = "Finish";
                        //Debug.Log(DeleteList[DeleteList.Count - 1].tag);
                        node = CLine.Nodes_list[CLine.Nodes_list.Count - 1];
                        CLine.Nodes_list.Remove(CLine.Nodes_list[CLine.Nodes_list.Count - 1]);
                        Destroy(node);
                        lineSize -= 1;
                        linePosCount -= 1;
                        CLine.SetlineSize(lineSize);
                        DeleteList.Remove(DeleteList[DeleteList.Count - 1]);
                       // PaturuControy.Skill.Water6Swich = true;

                    }
                }
                else if (DeleteList.Count == 1)
                {
                    Last_Paturu = hitObj;
                    SwichType = false;
                    //currentTga = hitObj.tag;
                }
                if (hitObj.name == NPaturu.RinkuName)
                {
                    currentTga = Paturu.RinkuName;
                    
                    PaturuControy.sethitobjCancel(Tag_ColorControlName2);
                    PaturuControy.ImagesControy(First_Paturu, Tag_ColorControlName);
                    SwichType = true;
                }
                
            }
            if(Back)
            {

                    {
                    if (hitObj.tag == Paturu.TagName0 || hitObj.tag == Paturu.TagName1 ||
                        hitObj.tag == Paturu.TagName2||hitObj.tag==Paturu.RinkuName)
                    {
                        Back = false;
                    }
                }
            }
        }
    }
    public Collider2D GetCurrentHitCollider()
    {
        RaycastHit2D hit
             = Physics2D.Raycast(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);
        return hit.collider;
    }
    void test(GameObject obj)
    {
        List<GameObject> asd;
        asd = new List<GameObject>();
        asd.Add(obj);
    }
    void AddDeleteObj(GameObject paturu)
    {
        Last_Paturu = paturu;
        //MoDoRi_PaTuru = paturu;
        DeleteList.Add(paturu);
    }
    void debug(int sss)
    {
        Debug.Log(sss);
    }
    public void DestroyButton()
    {
        DestroyAll(Paturu.TagName0);
        DestroyAll(Paturu.TagName1);
        DestroyAll(Paturu.TagName2);
        DestroyAll(Paturu.RinkuName);
        DestroyAll("キャラ00");

        DestroyAll("キャラ2");
    }
    public void DestroyAll(string Tag)
    {
        type0s = GameObject.FindGameObjectsWithTag(Tag);
        foreach (GameObject type0 in type0s)
        {
            if (type0s != null)
            {
                AddDeleteObj(type0);
            }                
        }

        var length = DeleteList.Count;

        DestoyObjs = new GameObject[length];
        debug(length);
        DestoySize = length;
        for (var i = 0; i < length; i++)
        {
            CScorecount.PaturuMathCount(DeleteList[i].name);
            DestoyObjs[i] = DeleteList[i];
        }
    }
    //コンフリクトごめんな
    public void DestroyObject(GameObject[] _gameobject)
    {
        type0s = _gameobject;
        foreach (GameObject type0 in type0s)
        {
            if (type0s != null)
            {
                AddDeleteObj(type0);
            }
        }

        var length = DeleteList.Count;

        DestoyObjs = new GameObject[length];
        debug(length);
        DestoySize = length;
        for (var i = 0; i < length; i++)
        {
            CScorecount.PaturuMathCount(DeleteList[i].name);
            DestoyObjs[i] = DeleteList[i];
        }
    }

    void Instantiate()
    {
        _min.PaturuDowns(DestoySize, KakuRiTuControl);
    }
    void Bigger(GameObject hitobj)
    {
        string Names;
        Names = hitobj.name;
        switch (Names)
        {
            case "water(Clone)":
                Transform name1 = hitobj.transform.Find("water1");
                name1.transform.localScale = new Vector2(1.5f, 1.5f);
                break;
            case "waterRole(Clone)":
                Transform name11 = hitobj.transform.Find("waterRole1");
                name11.transform.localScale = new Vector2(1.5f, 1.5f);
                break;
            case "wind(Clone)":
                Transform name2 = hitobj.transform.Find("wind1");
                name2.transform.localScale = new Vector2(1.5f, 1.5f);
                break;
            case "windRole(Clone)":
                Transform name22 = hitobj.transform.Find("windRole1");
                name22.transform.localScale = new Vector2(1.5f, 1.5f);
                break;
            case "fire(Clone)":
                Transform name3 = hitobj.transform.Find("fire1");
                name3.transform.localScale = new Vector2(1.5f, 1.5f);
                break;
            case "fireRole(Clone)":
                Transform name33 = hitobj.transform.Find("fireRole1");
                name33.transform.localScale = new Vector2(1.5f, 1.5f);
                break;
            case "link(Clone)":
                Transform name4 = hitobj.transform.Find("link1");
                name4.transform.localScale = new Vector2(1.5f, 1.5f);
                break;
        }

    }
    void Smaller(GameObject hitobj)
    {
        string Names;
        Names = hitobj.name;
        switch (Names)
        {
            case "water(Clone)":
                Transform name1 = hitobj.transform.Find("water1");
                name1.transform.localScale = new Vector2(1.0f, 1.0f);
                break;
            case "waterRole(Clone)":
                Transform name11 = hitobj.transform.Find("waterRole1");
                name11.transform.localScale = new Vector2(1.0f, 1.0f);
                break;
            case "wind(Clone)":
                Transform name2 = hitobj.transform.Find("wind1");
                name2.transform.localScale = new Vector2(1.0f, 1.0f);
                break;
            case "windRole(Clone)":
                Transform name22 = hitobj.transform.Find("windRole1");
                name22.transform.localScale = new Vector2(1.0f, 1.0f);
                break;
            case "fire(Clone)":
                Transform name3 = hitobj.transform.Find("fire1");
                name3.transform.localScale = new Vector2(1.0f, 1.0f);
                break;
            case "fireRole(Clone)":
                Transform name33 = hitobj.transform.Find("fireRole1");
                name33.transform.localScale = new Vector2(1.0f, 1.0f);
                break;
            case "link(Clone)":
                Transform name4 = hitobj.transform.Find("link1");
                name4.transform.localScale = new Vector2(1.0f, 1.0f);
                break;
        }
    }
    void TagModori(GameObject hitoobj)
    {
        string name;
        name = hitoobj.name;
        switch (name)
        {
            case "water(Clone)":
                hitoobj.tag = Paturu.TagName0;
                break;
            case "waterRole(Clone)":
                hitoobj.tag = Paturu.TagName0;
                break;
            case "wind(Clone)":
                hitoobj.tag = Paturu.TagName1;
                break;
            case "windRole(Clone)":
                hitoobj.tag = Paturu.TagName1;
                break;
            case "fire(Clone)":
                hitoobj.tag = Paturu.TagName2;
                break;
            case "fireRole(Clone)":
                hitoobj.tag = Paturu.TagName2;
                break;
            case "link(Clone)":
                hitoobj.tag = Paturu.RinkuName;
                break;
        }
    }
    void timerDesty()
    {
        if (DestoySize > 0)
        {
            timer -= Time.deltaTime;
        }
        if (timer <= 0)
        {
            DestoyCount += 1;
            GameObject _light;
            _light = Instantiate(Light, DestoyObjs[DestoyCount - 1].transform.position, Quaternion.Euler(0, 0, 0), null);
            Destroy(DestoyObjs[DestoyCount - 1]);
            debug(DestoyCount);
            DestoySize -= 1;
            timer = Keeptimer;
            m_SoundManager.PlaySE((int)GameSoundManager.SoundInfo.se_puzzle_delete, 1.0f, 0.0f);
        }
        if (DestoySize == 0)
        {
            int _count = DeleteList.Count;
            _min.RoleDown(_count);
           _min.PaturuDowns(_count - 1, KakuRiTuControl);
           _min.RinKuDown();
            DeleteList.Clear();
            DestoySize = -1;
            timer = Keeptimer;
            DestoyCount = 0;
            sg = true;
            //PaturuControy.sethitobjCancel(Tag_ColorControlName);
            //if (Tag_ColorControlName2 != null)
            //PaturuControy.sethitobjCancel(Tag_ColorControlName2);
			if(SkillCostManager.GetSkill6Code()!=null)
			SkillCostManager.GetSkill6Code ().BackAllChange ();
            Drag = true;
            drag2 = true;
        }

    }
    Vector2 mousePos()
    {
        return Camera.main.ScreenToWorldPoint(Input.mousePosition);
    }
    public GameObject GetFirstBall()
    {
        return First_Paturu;
    }
    public GameObject GetLastBall()
    {
        return Last_Paturu;
    }
    public string GetFirstTagName()
    {
        return  Tag_ColorControlName;
    }
    public GameObject GetHitObj()
    {
        return HitObj_;
    }
    void Skill6(GameObject hitObj,GameObject firstBall,string firstnameTag)
    {
		if (SkillCostManager.Skill_Control.Water6Swich&&SkillCostManager.GetSkill6Code()!=null)
        {
            SkillCostManager.GetSkill6Code().SetPazuruName(firstBall.name);
            SkillCostManager.GetSkill6Code().FindOtherChangeName(firstBall, hitObj,firstnameTag);
           //SkillCostManager.GetSkill6Code().FindOtherBackName(hitObj);
        }
    }
	void DraggingSKill6(GameObject hitObj,GameObject firstBall,string firstnameTag)
	{
		if (SkillCostManager.Skill_Control.Water6Swich && SkillCostManager.GetSkill6Code () != null) 
		{
			SkillCostManager.GetSkill6Code ().CheckOutOldObjsToBack (hitObj);
			SkillCostManager.GetSkill6Code ().DraggingAddOldObjs (firstBall, hitObj, firstnameTag);
		}
	}
    public Vector3 GetFireRolePos()
    {
        if (hitObjV3Pos != null)
        {
            return hitObjV3Pos;
        }
        else
            return hitObjV3Pos;
        
    }
	 void UpdateSkill6()
	{
		if (SkillCostManager.GetSkill6Code () != null) {
			if (PaturuControy.waterskill_six.StartCountDown == 0) {
				//PaturuControy.waterskill_six.UpdaterCountDown = true;
				SkillCostManager.GetSkill6Code ().DraggingByCountDown ();
			}
		}
	}
}
