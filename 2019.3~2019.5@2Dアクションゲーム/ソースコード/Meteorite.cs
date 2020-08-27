using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Destructible2D;

public class Meteorite : MonoBehaviour
{
    Rigidbody2D rb;
    //public float Speed;
    UI_Meteorite _met;
    Skill PickUp;
    public GameObject _dh;
    public GameObject _chongdong;
    public GameObject _star;
    FollowTarget follow;
    Rigidbody2D Player;
    public float upSpeed;
    bool KCtr;
   public bool tooltr;
    public float UpSpeed;
    // Start is called before the first frame update
    void Start()
    {
        //rb = GetComponent<Rigidbody2D>();
        //rb.angularVelocity = Random.Range(0,10)*Speed; 
        PickUp = GameObject.Find("Player").GetComponent<Skill>();
        follow = GameObject.Find("Player").GetComponent<FollowTarget>();
        KCtr = false;
        tooltr = false;
       


    }

    // Update is called once per frame
    void Update()
    {
        UsingButton();
        if (Input.GetKeyDown(KeyCode.F))
        {
            _met = GameObject.Find("Meteorite").GetComponentInChildren<UI_Meteorite>(true);
            // _met.GetTool = true;
            //collision.gameObject.GetComponent<Skill>().UsingMz = true;

           // Destroy(this.gameObject);
        }


    }
    private void OnCollisionStay2D(Collision2D collision)
    {
        if (Input.GetKeyDown(KeyCode.F)) 
        {
           // _met = GameObject.Find("Meteorite").GetComponentInChildren<UI_Meteorite>(true);
           // _met.GetTool = true;
            collision.gameObject.GetComponent<Skill>().UsingMz = true;

            Destroy(this.gameObject);
        }
        /*if (collision.gameObject.tag == "Player" && Input.GetKeyDown(KeyCode.J))
        {
            KCtr = true;
            follow = collision.gameObject.GetComponent<FollowTarget>();
            follow.enabled = true;
            follow.target = transform;
            Player = collision.gameObject.GetComponent<Rigidbody2D>();
            Player.gravityScale = 0;

        }*/
        if (collision.gameObject.tag == "Player" && Input.GetKeyDown(KeyCode.J))
        {
          
            follow.enabled = true;
            follow.target = transform;
            Player = collision.gameObject.GetComponent<Rigidbody2D>();
            Player.gravityScale = 0;
        }
        if (collision.gameObject.tag == "Player" && Input.GetKeyUp(KeyCode.J))
        {
            //collision.gameObject.GetComponent<Rigidbody2D>().velocity = Vector2.up * UpSpeed;
            follow.enabled = false;
            Player = collision.gameObject.GetComponent<Rigidbody2D>();
            Player.gravityScale = 3;
        }


    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.tag=="timemachine")
        {
            Instantiate(_dh, transform.position, Quaternion.identity, null);
            PickUp.SkillCheckUp();
            PickUp.TimemachineBool = false;
            Destroy(this.gameObject);
            
        }
        if(collision.gameObject.tag=="chongdong")
        {
            Instantiate(_chongdong, transform.position, Quaternion.identity, null);
            PickUp.ChongdongBool = true;
            PickUp.SkillCheckUp();
            GetComponent<CircleCollider2D>().enabled = false;
            GetComponent<MeshRenderer>().enabled = false;
        }
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {
     /*if(collision.gameObject.tag=="Player"&&Input.GetKeyDown(KeyCode.J))
        {
            KCtr = true;
            follow = collision.gameObject.GetComponent<FollowTarget>();
            follow.enabled = true;
            follow.target = transform;
            Player = collision.gameObject.GetComponent<Rigidbody2D>();
            Player.gravityScale = 0;
            
        }*/
     if(collision.gameObject.tag=="New tag"&&PickUp.yellowCtr)
        {
            Debug.Log("dadddd");
            Instantiate(_star, transform.position, Quaternion.identity, null);
            _star.gameObject.GetComponent<StarMove>().centerObj = this.gameObject.GetComponent<StarMove>().centerObj;
            Destroy(gameObject, 1*Time.deltaTime);
        }
       
    }
    
    void UsingButton()
    {
        /*if(Input.GetKeyDown(KeyCode.K)&&KCtr)
        {
            follow.enabled = false;
            KCtr = false;
            Player.gravityScale = 3;
            Player.velocity = Vector2.up * upSpeed;
        }*/
    }

}
