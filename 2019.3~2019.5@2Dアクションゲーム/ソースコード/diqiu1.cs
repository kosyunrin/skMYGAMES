using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class diqiu1 : MonoBehaviour
{
    
    // Start is called before the first frame update
    void Start()
    {
       
    }

    // Update is called once per frame
    void Update()
    {
    }
    private void OnTriggerStay2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "yunshi")
        {
            Debug.Log("sdada");
            Rigidbody2D yunshi = collision.gameObject.GetComponent<Rigidbody2D>();
            yunshi.gravityScale = 0;
            StarMove yunshi1 = collision.gameObject.GetComponent<StarMove>();
            yunshi1.centerObj = gameObject;
            yunshi1.enabled = true;
            CircleCollider2D yunshi2 = collision.gameObject.GetComponent<CircleCollider2D>();

        }
        if (collision.gameObject.tag == "Player")
        {
            GetComponent<CircleCollider2D>().radius = 1;
        }
    }
    
}
