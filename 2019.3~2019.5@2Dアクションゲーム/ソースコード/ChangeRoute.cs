using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeRoute : MonoBehaviour
{
    GameObject[] Stars;
    bool colorCtr;
    float timer;
    UI_Change Change;
    public bool C;
    Skill _skill;

    // Start is called before the first frame update
    void Start()
    {
        Stars = GameObject.FindGameObjectsWithTag("Star");
        colorCtr = false;
        timer = 0;
        C = false;
    }

    // Update is called once per frame
    void Update()
    {

    }
    private void OnTriggerStay2D(Collider2D collision)
    {
        if(Input.GetKeyDown(KeyCode.F))
        {
            Change = GameObject.Find("Change").GetComponentInChildren<UI_Change>(true);
            Change.GetTool = true;
            collision.gameObject.GetComponent<Skill>().UsingC = true;
            Destroy(gameObject);

        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
           
            colorCtr = true;
            Stars = GameObject.FindGameObjectsWithTag("Star");
            foreach (GameObject star in Stars)
            {
                
                // star.GetComponent<StarMove>().enabled = false;
                star.GetComponent<StarMove>().SwitchRotation();

            }

        }
        if(collision.gameObject.tag=="yunshi")
        {
            
            collision.gameObject.GetComponent<StarMove>().SwitchRotation();
            Destroy(gameObject);
        }
    }
    
    private void FixedUpdate()
    {
        if (colorCtr)
        {
            timer += Time.deltaTime;
            GetComponent<SpriteRenderer>().color = Color.red;
            if (timer > 0.5)
            {
                GetComponent<SpriteRenderer>().color = Color.white;
                timer = 0;
                colorCtr = false;
            }

        }
    }
}
