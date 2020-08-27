using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_Meteorite : MonoBehaviour
{
    public bool GetTool;
    public bool toolbool;
    Image Met;
    float Now;
    float Max = 120;
    GameObject[] yunshis;
    // Start is called before the first frame update
    void Start()
    {
        toolbool = false;
        GetTool = false;
        Now = 0;
        Met = GetComponent<Image>();
    }

    // Update is called once per frame
    void Update()
    {
        Met.fillAmount = Now / Max;
        if (GetTool)
        {
            yunshis = GameObject.FindGameObjectsWithTag("yunshi");
            foreach (GameObject yunshi in yunshis)
            {

                // star.GetComponent<StarMove>().enabled = false;
                yunshi.GetComponent<Meteorite>().tooltr = true;

            }
            Now += 1;
            if (Now >= Max)
            {
                Now = Max;
            }
        }
        else
        {
            Now = 0;
        }
    }
}
