using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerSTM : MonoBehaviour {
    [SerializeField] GameObject[] Menu;
    int count;


    [SerializeField] GameObject[] Menu2;
    [SerializeField] double colorcount;
    CanvasGroup[] Images;
    bool bl;
    // Use this for initialization
    void Start () {
        for (int i = 0; i < Menu.Length; i++)
        {
            Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
        }
        count = 0;



        colorcount = 1;
        Images = Menu2[0].GetComponentsInChildren<CanvasGroup>();
        Menu2[0].SetActive(true);
        Menu2[1].SetActive(false);
        Menu2[2].GetComponent<Scrollbar>().value = 1;
    }
	
	// Update is called once per frame
	void Update () {

        if (Input.GetMouseButton(0))
        {
            Menu2[1].SetActive(true);
        }
        if (bl == true)
        {
            StartCoroutine(ColorChangeOne());

        }

    }
    public void Button0()
    {
        Menu[0].GetComponent<RectTransform>().anchoredPosition = new Vector2(0, 0);
        Menu[4].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, -75);
        //Menu[5].GetComponent<RectTransform>().anchoredPosition = new Vector2(-75, -76);
        Menu[6].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, 86);
        count += 1;
    }
    public void Button1()
    {
        NextButton(count);
    }
    public void Button2()
    {
        KieroButton(count);
    }
    public void Button3()
    {
        for (int i = 0; i < Menu.Length; i++)
        {
            Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
        }
        count = 0;
    }


    void NextButton(int number)
    {
        switch (number)
        {
            case 1:
                for (int i = 0; i < Menu.Length; i++)
                {
                    Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
                }
                Menu[1].GetComponent<RectTransform>().anchoredPosition = new Vector2(0, 0);
                Menu[4].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, -75);
                Menu[5].GetComponent<RectTransform>().anchoredPosition = new Vector2(-75, -76);
                Menu[6].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, 86);
                count += 1;

                break;
            case 2:
                for (int i = 0; i < Menu.Length; i++)
                {
                    Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
                }
                Menu[2].GetComponent<RectTransform>().anchoredPosition = new Vector2(0, 0);
                Menu[4].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, -75);
                Menu[5].GetComponent<RectTransform>().anchoredPosition = new Vector2(-75, -76);
                Menu[6].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, 86);
                count += 1;

                break;
            case 3:
                for (int i = 0; i < Menu.Length; i++)
                {
                    Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
                }
                Menu[3].GetComponent<RectTransform>().anchoredPosition = new Vector2(0, 0);
                //Menu[4].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, -75);
                Menu[5].GetComponent<RectTransform>().anchoredPosition = new Vector2(-75, -76);
                Menu[6].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, 86);
                count += 1;
                break;
        }
    }
    void KieroButton(int number)
    {
        switch (number)
        {
            //case 1:
            //    for (int i = 0; i < Menu.Length; i++)
            //    {
            //        Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
            //    }
            //    count = 0;

            //    break;
            case 2:
                for (int i = 0; i < Menu.Length; i++)
                {
                    Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
                }
                Menu[0].GetComponent<RectTransform>().anchoredPosition = new Vector2(0, 0);
                Menu[4].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, -75);
                //Menu[5].GetComponent<RectTransform>().anchoredPosition = new Vector2(-75, -76);
                Menu[6].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, 86);
                count = 1;

                break;
            case 3:
                for (int i = 0; i < Menu.Length; i++)
                {
                    Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
                }
                Menu[1].GetComponent<RectTransform>().anchoredPosition = new Vector2(0, 0);
                Menu[4].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, -75);
                Menu[5].GetComponent<RectTransform>().anchoredPosition = new Vector2(-75, -76);
                Menu[6].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, 86);
                count = 2;
                break;
            case 4:
                for (int i = 0; i < Menu.Length; i++)
                {
                    Menu[i].GetComponent<RectTransform>().anchoredPosition = new Vector2(250, 0);
                }
                Menu[2].GetComponent<RectTransform>().anchoredPosition = new Vector2(0, 0);
                Menu[4].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, -75);
                Menu[5].GetComponent<RectTransform>().anchoredPosition = new Vector2(-75, -76);
                Menu[6].GetComponent<RectTransform>().anchoredPosition = new Vector2(75, 86);
                count = 3;

                break;
        }
    }




    public void Closed()
    {
        Menu2[1].SetActive(false);
        bl = true;
    }
    public void PointerEnter()
    {
        if (Camera.main.ScreenToWorldPoint(Input.mousePosition).x < 0)
        {
            Menu2[1].GetComponent<Image>().color = new Vector4(255, 255, 255, 130);
            Menu2[3].GetComponent<Image>().color = new Vector4(255, 255, 255, 0);
        }
        else
        {
            Menu2[3].GetComponent<Image>().color = new Vector4(255, 255, 255, 130);
            Menu2[1].GetComponent<Image>().color = new Vector4(255, 255, 255, 0);
        }
    }
    public void PointerExit()
    {
        if (Camera.main.ScreenToWorldPoint(Input.mousePosition).x < 0)
            Menu2[1].GetComponent<Image>().color = new Vector4(255, 255, 255, 0);
        else
            Menu2[3].GetComponent<Image>().color = new Vector4(255, 255, 255, 0);
    }
    public IEnumerator ColorChangeOne()
    {
        Images = Menu2[0].GetComponentsInChildren<CanvasGroup>();
        for (int i = 0; i < Images.Length; i++)
        {
            while (colorcount > 0)
            {
                colorcount -= 0.0001;
                Images[i].alpha = (float)colorcount;
                yield return null;
            }
        }


    }
}
