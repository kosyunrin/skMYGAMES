using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Skill : MonoBehaviour
{
    public GameObject xx;
    public GameObject jiantou;
    public Skills SkillChoose;
    public bool UsingChange;
    public float Angle;
    public GameObject GateAngle;
    public GameObject Gate;
    bool UsingShoot;
    public float ShootNow;
    public float ShootMax=15000000000000;
    public Image Amount;
    public GameObject MiaozhunAngle;
    public GameObject Miaozhun;
    public GameObject YunShi;
    public GameObject Yunshiz;

    public GameObject MzAngle;
    public GameObject Mz;
    public GameObject MzAnglez;
    public GameObject Mzz;
    public bool UsingMz;
    public bool SkillButtonMz;
    public bool SkillButtonMzz;
    public float ShootSpeed;
    public bool tiaochu;

    public bool UsingChange2;
    public GameObject FuChiAngle;
    public GameObject FuChi;
   
    public bool TimemachineBool;
    public bool ChongdongBool;
    public bool yellowCtr;
    float timer;
    bool timerbool;
    public GameObject text;

    float yunshitztimer;
    bool yunshitingzhibool;
    GameObject _fashe;
    GameObject _fashez;
    GameObject[] yunshis;
    GameObject[] yunshisz;
    FollowTarget Player;
    float redtimer;
    bool redtimerbool;
    bool tagbool;
    GameObject newtag;
    public bool UsingC;



    // Start is called before the first frame update
    void Start()
    {
        xx.SetActive(false);
        SkillButtonMzz = false;
        UsingC = false;
        tagbool = false;
        redtimerbool = false;
        yunshitingzhibool = false;
        text.SetActive(false);
        timerbool = false;
        yellowCtr = false;
        ChongdongBool = false;
        TimemachineBool = false;
        UsingChange = false;
        Gate.SetActive(false);
        Miaozhun.SetActive(false);
        UsingMz = true;
        Mz.SetActive(true);
        SkillChoose = Skills.none;
        SkillButtonMz = true;
        UsingChange2 = false;
        FuChi.SetActive(false);
        Player = GetComponent<FollowTarget>();
        newtag = GameObject.FindGameObjectWithTag("Player");
    }

    // Update is called once per frame
    void Update()
    {
        SKillButton();
        if (Input.GetMouseButtonDown(0))
        {
            SkillCheckDown();
        }
        if(Input.GetMouseButtonUp(0))
        {
            SkillCheckUp();
        }
        if(UsingChange&&!TimemachineBool)
        {
            Vector2 mousPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);//获取相机里的鼠标位置
            Angle=Mathf.Atan2(mousPos.y-this.transform.position.y,mousPos.x-this.transform.position.x)*Mathf.Rad2Deg;
            GateAngle.transform.rotation = Quaternion.Euler(0, 0,Angle);
            Gate.transform.position = mousPos;
            Gate.SetActive(true);
        }
        if (UsingChange2&&!ChongdongBool)
        {
            Vector2 mousPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);//获取相机里的鼠标位置
            Angle = Mathf.Atan2(mousPos.y - this.transform.position.y, mousPos.x - this.transform.position.x) * Mathf.Rad2Deg;
            FuChiAngle.transform.rotation = Quaternion.Euler(0, 0, Angle);
            FuChi.transform.position = mousPos;
        }
        if (UsingMz&&SkillButtonMz)
        {
            Vector2 mousPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);//获取相机里的鼠标位置
            Angle = Mathf.Atan2(mousPos.y - this.transform.position.y, mousPos.x - this.transform.position.x) * Mathf.Rad2Deg;
            MzAngle.transform.rotation = Quaternion.Euler(0, 0, Angle);
            Mz.SetActive(true);
            SkillChoose = Skills.fasheyunshi;
        }
        if (UsingC && SkillButtonMzz)
        {
            Vector2 mousPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);//获取相机里的鼠标位置
            Angle = Mathf.Atan2(mousPos.y - this.transform.position.y, mousPos.x - this.transform.position.x) * Mathf.Rad2Deg;
            MzAnglez.transform.rotation = Quaternion.Euler(0, 0, Angle);
            Mzz.SetActive(true);
            SkillChoose = Skills.zhiliangzhuanyi;
        }
        if (!SkillButtonMz)
        {
            Mz.SetActive(true);
            //jiantou.SetActive(false)
            
        }
        if (!SkillButtonMzz)
        {
            Mzz.SetActive(false);

        }
        if (UsingShoot)
        {
            Miaozhun.SetActive(true);
            ShootNow += 50 * Time.deltaTime;
            MiaozhunAngle.transform.rotation = Quaternion.Euler(0, 0, Angle);
            
            if(ShootNow>=ShootMax)
            {
                ShootNow = ShootMax;
            }
            Amount.fillAmount = ShootNow / ShootMax;
        }
        if(tagbool)
        {
            
            
            newtag.tag = "Player";
            tagbool = false;
        }
        

        
    }
    private void SkillCheckDown()
    {
        switch (SkillChoose)
        {
            case Skills.fasheyunshi:
                UsingShoot = true;
                ShootNow = 0;
                Amount.fillAmount = 0;
                //Mz.SetActive(false);
                UsingMz = true;
                break;
            case Skills.jiasushijie:
                UsingChange = true;
                //Gate.SetActive(true);
                break;
            case Skills.jiansushijie:
                UsingChange2 = true;
                FuChi.SetActive(true);
                break;
            case Skills.zhiliangzhuanyi:
                UsingShoot = true;
                ShootNow = 0;
                Amount.fillAmount = 0;
                Mzz.SetActive(false);
                UsingC = false;
                break;
            case Skills.none:
                break;
            default:
                
                break;
        }
    }
    public void SkillCheckUp()
    {
        switch (SkillChoose)
        {
            case Skills.fasheyunshi:
                jiantou.SetActive(false);
                UsingShoot = false;
                Miaozhun.SetActive(false);
                Vector2 mousPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);//获取相机里的鼠标位置
                Vector2 dir = (mousPos - new Vector2(transform.position.x, transform.position.y)).normalized;
                _fashe = Instantiate(YunShi, Mz.transform.position, Quaternion.Euler(0, 0, -85), null);

                var rt = _fashe.GetComponent<Transform>();

                rt.localScale = new Vector2((float)1.5, (float)1.5);
                _fashe.GetComponent<Rigidbody2D>().AddForce(dir * ShootNow * ShootSpeed*5);
                _fashe.GetComponent<StarMove>().enabled = false;
                UI_Meteorite _met = GameObject.Find("Meteorite").GetComponentInChildren<UI_Meteorite>(true);
                _met.GetTool = false;
                _met.toolbool = false;
                yunshis = GameObject.FindGameObjectsWithTag("yunshi");
                foreach (GameObject yunshi in yunshis)
                {

                    // star.GetComponent<StarMove>().enabled = false;
                    yunshi.GetComponent<Meteorite>().tooltr = false;
               

                }
                SkillChoose = Skills.none;
                SkillButtonMz = false;
                jiantou.SetActive(false);
                yunshitingzhibool = true;


                break;
            case Skills.jiasushijie:
                //Instantiate(magic, transform.position, Quaternion.identity, null);
                UsingChange = false;
                Gate.SetActive(false);
                SkillChoose = Skills.none;
                break;
            case Skills.jiansushijie:
                UsingChange2 = false;
                FuChi.SetActive(false);
                break;
            case Skills.zhiliangzhuanyi:
                UsingShoot = false;
                Miaozhun.SetActive(false);
                Vector2 mousPosz = Camera.main.ScreenToWorldPoint(Input.mousePosition);//获取相机里的鼠标位置
                Vector2 dirz = (mousPosz - new Vector2(transform.position.x, transform.position.y)).normalized;
                _fashez = Instantiate(Yunshiz, Mzz.transform.position, Quaternion.identity, null);
                
                _fashez.GetComponent<Rigidbody2D>().AddForce(dirz * ShootNow * ShootSpeed * 5);

                UI_Change _metzs = GameObject.Find("Change").GetComponentInChildren<UI_Change>(true);
                _metzs.GetTool = false;
                SkillChoose = Skills.none;
                SkillButtonMzz = false;
                /* yunshisz = GameObject.FindGameObjectsWithTag("Change");
                 foreach (GameObject yunshiz in yunshisz)
                 {

                     // star.GetComponent<StarMove>().enabled = false;
                     yunshiz.GetComponent<ChangeRoute>().C = false;


                 }*/
               
                break;
            case Skills.none:
                break;
            default:
                break;
        }
    }
   
    public void SKillButton()
    {
        if(Input.GetKeyDown(KeyCode.T))
        {
            xx.SetActive(true);
        }
        if(Input.GetKeyUp(KeyCode.T))
        {
            xx.SetActive(false);
        }
        if (Input.GetKeyDown(KeyCode.Alpha1)) 
        {
            //SkillButtonMz = !SkillButtonMz;
            SkillButtonMz = true;
            jiantou.SetActive(true);
            //SkillChoose = Skills.none;
        }
        if (Input.GetKeyDown(KeyCode.Alpha3) && UsingC)
        {
            SkillButtonMzz = !SkillButtonMzz;
            
            //SkillChoose = Skills.none;
        }
        if (Input.GetKeyDown(KeyCode.O)&&!Player.enabled && !timerbool)
        {
            
            newtag.tag = "New tag";
            GetComponent<SpriteRenderer>().color = Color.red;
            yellowCtr = true;
            timerbool = true;
        }
        if(Input.GetKeyDown(KeyCode.O)&&Player.enabled&&!redtimerbool)
            {
            GetComponent<SpriteRenderer>().color = Color.red;
            yunshis = GameObject.FindGameObjectsWithTag("yunshi");
            foreach (GameObject yunshi in yunshis)
            {

                // star.GetComponent<StarMove>().enabled = false;
                yunshi.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Static;
                GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Static;
                redtimerbool = true;
                
            }
        }
        
        if(Input.GetKeyDown(KeyCode.Alpha2))
        {
            SkillChoose = Skills.jiasushijie;
       
            text.SetActive(true);
        }
        if(Input.GetKeyUp(KeyCode.Alpha2))
            {
           
            text.SetActive(false);
            SkillCheckUp();
            SkillChoose = Skills.none;
            
        }
    }
    private void FixedUpdate()
    {
        if(timerbool)
        {
            timer += Time.deltaTime;
            
            if (timer > 1)
            {
                
                if (timer > 2)
                {
                    tagbool = true;
                    

                    GetComponent<SpriteRenderer>().color = Color.white;
                    GetComponent<BoxCollider2D>().isTrigger = false;
                    yellowCtr = false;
                   
                    if(timer>3)
                    {
                        timerbool = false;
                        timer = 0;
                    }
                }
            }
        }
        if(yunshitingzhibool)
        {
            yunshitztimer += Time.deltaTime;
            {
                if(yunshitztimer>2)
                {
                    
                    _fashe.GetComponent<Rigidbody2D>().gravityScale = 0;
                    _fashe.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Static;
                    

                        if (yunshitztimer > 2.2)
                        {
                          
                            yunshitingzhibool = false;
                            yunshitztimer = 0;
                        }
                    
                }

            }
        }
        if(redtimerbool)
        {
            redtimer += Time.deltaTime;
            if (redtimer > 1)
            {
                
                    GetComponent<SpriteRenderer>().color = Color.white;
                    yunshis = GameObject.FindGameObjectsWithTag("yunshi");
                    foreach (GameObject yunshi in yunshis)
                    {

                        // star.GetComponent<StarMove>().enabled = false;
                        yunshi.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Dynamic;
                        GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Dynamic;
                        
                    }
                    redtimer = 0;
                    redtimerbool = false;
                
            }
        }
    }
}
public enum Skills
{
    fasheyunshi,
    jiasushijie,
    jiansushijie,
    zhiliangzhuanyi,
    none
    

}

