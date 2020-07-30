using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class camare : MonoBehaviour
{
    public Transform player;
    Vector3 weizhicha;
    // Start is called before the first frame update
    void Start()
    {
        //renwu jian qu xiangji weizhi
        weizhicha = player.transform.position - transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        //gengxin xiaongji xiangji weizhi
        transform.position = player.transform.position - weizhicha;
    }
}
