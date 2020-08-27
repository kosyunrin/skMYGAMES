using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_Change : MonoBehaviour
{
    public bool GetTool;
    Image Change;
    float Now;
    float Max=120;
    // Start is called before the first frame update
    void Start()
    {
        Now = 0;
        Change = GetComponent<Image>();
    }

    // Update is called once per frame
    void Update()
    {
        Change.fillAmount = Now / Max;
        if (GetTool)
        {
            Now += 1;
            if(Now>=Max)
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
