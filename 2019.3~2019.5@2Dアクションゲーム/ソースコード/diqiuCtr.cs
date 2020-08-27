using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class diqiuCtr : MonoBehaviour
{
    float angle;
    // Start is called before the first frame update
    void Start()
    {
        
        angle = 0;
    }

    // Update is called once per frame
    void Update()
    {
        this.transform.rotation = (Quaternion.Euler(0, 0, angle));
        angle+=2*Time.deltaTime;
    }
    private void OnTriggerStay2D(Collider2D collision)
    {
       

        
    }
}
