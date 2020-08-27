using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallBreak : MonoBehaviour
{
    Rigidbody2D SimulatedBool;//与其他碰撞体发生仿真交互；关掉之后能解决追踪星星时的抖动；
    FollowTarget FollowBool;
    ColliderPlayer ColliderPlayer;
    // Start is called before the first frame update
    void Start()
    {
        SimulatedBool = GameObject.Find("Player").GetComponent<Rigidbody2D>();
        FollowBool = GameObject.Find("Player").GetComponent<FollowTarget>();
        ColliderPlayer = GameObject.Find("Player").GetComponentInChildren<ColliderPlayer>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag=="Star")
        {
            Destroy(gameObject, 1);
            Destroy(collision.gameObject);
            SimulatedBool.simulated = true;
            FollowBool.enabled = false;
            ColliderPlayer.boolFlingOff = false;
        }
    }
}
