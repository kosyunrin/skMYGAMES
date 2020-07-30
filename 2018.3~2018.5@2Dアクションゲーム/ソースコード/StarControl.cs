using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Destructible2D;

public class StarControl : MonoBehaviour
{
    public int radius;//爆炸效果的半径，！sence没有添加爆炸墙壁；
    BoxCollider2D Star;
    float timer;
    bool TimeBool;//控制颜色，星星的实体化，融化能力开启时间。。。；
    Rigidbody2D SimulatedBool;
    FollowTarget boolFollow;//控制是否跟随；
    ColliderPlayer ColliderPlayer;//取得人物的子物体的代码；
    public bool RealStar;//为了让角色一定时间可以使星星实体化；
    public GameObject Yunshi;



    // Start is called before the first frame update
    void Start()
    {
        TimeBool = false;
        Star = GetComponent<BoxCollider2D>();
        boolFollow = GameObject.Find("Player").GetComponent<FollowTarget>();
        SimulatedBool = GameObject.Find("Player").GetComponent<Rigidbody2D>();
        GetComponent<D2dRepeatStamp>().enabled = false;
        ColliderPlayer = GameObject.Find("Player").GetComponentInChildren<ColliderPlayer>();
        RealStar = false;



    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Sand")
        {


            collision.gameObject.GetComponent<DestructibleSprite>().ApplyDamage(collision.contacts[0].point, radius);
            SimulatedBool.simulated = true;
            boolFollow.enabled = false;
            ColliderPlayer.boolFlingOff = false;



        }
        if (collision.gameObject.tag == "yunshi")
        {
            collision.gameObject.GetComponent<FollowTarget>().enabled = true;
            collision.gameObject.GetComponent<FollowTarget>().target = transform;
            GetComponent<SpriteRenderer>().enabled = false;

        }
        if (collision.gameObject.tag == "Coin")
        {
            Destroy(collision.gameObject);
        }
        if(collision.gameObject.tag=="Player")
        {
            Destroy(gameObject);
        }
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player"&& RealStar)
        {
            TimeBool = true;

        }
    }

    // Update is called once per frame
    void Update()
    {
    }
    private void FixedUpdate()
    {
        
        if (TimeBool)
        {
            timer += Time.deltaTime;
            ColliderPlayer.Dissolve = true;
            GetComponent<SpriteRenderer>().color = Color.blue;
            if (timer > 0.5)
            {
                GameObject Yunshi1= Instantiate(Yunshi, transform.position, Quaternion.identity, null);
                ColliderPlayer.Dissolve = false;
                Star.isTrigger = false;
                timer = 0;
                TimeBool = false;
            }
        }
    }
}
