using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Destructible2D;

public class ColliderPlayer : MonoBehaviour
{
    FollowTarget boolFollow;//控制是否跟随星星；
    Rigidbody2D boolSimulated;//与其他碰撞体发生仿真交互；关掉之后能解决追踪星星时的抖动；
    public bool boolFlingOff;//控制是否离开星星
    public float upSpeed;//离开星星时跳起的速度；
    BoxCollider2D Star;
    float timer;//计时为了解决抛开星星时人物对星星的影响；
    float timer2;//在一定时间呢人物可以把触碰到的星星变实体化；
    bool Timebool;//开启计时
    bool TimeBool2;
    SpriteRenderer _Star;//获取星星的颜色；
    SpriteRenderer PlayerColor;
    GameObject[] _RealStars;//
    D2dRepeatStamp DissolvedBool;//取得融化的组件；
    public bool Dissolve;//判断是否开启星星融化的能力；
     bool Catch;//为了控制再一定时间里面才能抓取星星且人物为蓝色形态时；







    // Start is called before the first frame update
    void Start()
    {
        Dissolve = false;
        Catch = false;
        //aa = GameObject.Find("CharacterRobotBoy").GetComponent<xiangji2>();
        boolFollow = GameObject.Find("Player").GetComponent<FollowTarget>();
        boolFollow.enabled = false;
        boolSimulated = GameObject.Find("Player").GetComponent<Rigidbody2D>();
        PlayerColor = GameObject.Find("Player").GetComponent<SpriteRenderer>();
        _RealStars = GameObject.FindGameObjectsWithTag("Star");
        boolSimulated.simulated = true;
        boolFlingOff = false;
        Timebool = false;
        TimeBool2 = false;


    }

    // Update is called once per frame
    void Update()
    {
        UseInput();

    }

    void UseInput()
    {
        if (boolFlingOff)
        {

            /*if (Input.GetKeyDown(KeyCode.K))//按下K离开星星；
            {
                boolFollow.enabled = false;
                boolSimulated.simulated = true;
                boolSimulated.velocity = Vector2.up * upSpeed;
                Star.enabled = false;
                boolFlingOff = false;
                _Star.color = Color.white;
                Timebool = true;
                DissolvedBool.enabled = false;
            }*/
        }
        if (Input.GetKeyDown(KeyCode.I))
        {
            Catch = true;
            PlayerColor.color = Color.blue;
            TimeBool2 = true;
            _RealStars = GameObject.FindGameObjectsWithTag("Star");
            foreach (GameObject star in _RealStars)
            {

                // star.GetComponent<StarMove>().enabled = false;
                star.GetComponent<StarControl>().RealStar = true;

            }


        }
    }
    private void OnTriggerStay2D(Collider2D collision)
    {
        /*if (collision.gameObject.tag == "Star" && Input.GetKeyDown(KeyCode.J)&&Catch)
        {
            boolFlingOff = true;
            boolFollow.enabled = true;
            boolSimulated.simulated = false;
            boolFollow.target = collision.gameObject.GetComponent<Transform>();
            Star = collision.gameObject.GetComponent<BoxCollider2D>();
            _Star = collision.gameObject.GetComponent<SpriteRenderer>();
        }*/
        if(collision.gameObject.tag=="Star")
        {
           DissolvedBool=collision.gameObject.GetComponent<D2dRepeatStamp>();
            if (Dissolve)
            {
                DissolvedBool.enabled = true;
            }
        }
    }
    private void FixedUpdate()
    {

        if (Timebool)
        {
            timer += Time.deltaTime;
            {
                if (timer > 0.3)
                {
                    Star.enabled = true;
                    Star.isTrigger = true;
                    Timebool = false;
                    timer = 0;
                }
            }
        }
        if (TimeBool2)
        {
            timer2 += Time.deltaTime;
            if (timer2 > 1.5)
            {
                Catch = false;
                PlayerColor.color = Color.white;
                _RealStars = GameObject.FindGameObjectsWithTag("Star");
                foreach (GameObject star in _RealStars)
                {

                    // star.GetComponent<StarMove>().enabled = false;
                    star.GetComponent<StarControl>().RealStar = false;

                }
                timer2 = 0;
                TimeBool2 = false;
            }
        }
    }
}
