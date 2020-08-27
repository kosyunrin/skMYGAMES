using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StarsMove : MonoBehaviour
{
    public float starsmove = 0.05f;

    public float starsmove2 = 0.3f;

    Vector3 Starlocation = new Vector3(105f, 12f, 0.0f);

    float Move;

    bool Switch = false;
    bool Switch2 = false;
    bool Switch3 = false;
    bool Switch4= false;
    bool Switch5 = false;
    bool TimeSwitch = false;

    float Time = 1.0f;
    float jikan = 0.0f;
    // Update is called once per frame



    void Update()
    {
        if (Switch == false)
        {
            Starlocation.y += starsmove;

            if (Starlocation.y > 15)
            {

                Switch = true;
                Switch2 = true;
            }
        }
        if (Switch2 == true)
        {
            Starlocation.y -= starsmove;


            if (Starlocation.y < 5)
            {
               Switch2 = false;
               TimeSwitch = true;
            }
        }
       if(TimeSwitch == true)
        {
            jikan += Time;
            if (jikan == 30)
            {
                Starlocation.y = 5;
                Switch3 = true;
                jikan = 0;
                TimeSwitch = false;
            }
        }


        if (Switch3 == true)
        {
            if (Starlocation.y > 4)
            {
                Starlocation.y += starsmove2;
                if (Starlocation.y > 10)
                {
                    Switch3 = false;
                    Switch4 = true;
                }
            }
           }
         if(Switch4 == true)
         {
        
             Starlocation.y += starsmove;
        
             if (Starlocation.y > 15)
             {
                 Starlocation.y = 14;
                 Switch4 = false;
                 Switch5 = true;
             } 
           }
         if(Switch5 == true)
        {
            if (Starlocation.y < 15)
            {
                Starlocation.y -= starsmove2;
                if (Starlocation.y < 7)
                {
                    Switch5 = false;
                    Switch2 = true;
                }

            }
        }





        transform.position = Starlocation;

    }



  
    
}
