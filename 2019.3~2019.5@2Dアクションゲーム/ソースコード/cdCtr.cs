using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cdCtr : MonoBehaviour
{
    float timer;
    Skill _skill;
    public GameObject star;
    // Start is called before the first frame update
    void Start()
    {
        _skill = GameObject.Find("Player").GetComponent<Skill>();


    }

    // Update is called once per frame
    void Update()
    {

    }
    private void FixedUpdate()
    {
        timer += Time.deltaTime;
        if (timer > 3)
        {
            Instantiate(star, transform.position, Quaternion.identity, null);
            timer = 0;
            Destroy(gameObject);
        }
    }
}
