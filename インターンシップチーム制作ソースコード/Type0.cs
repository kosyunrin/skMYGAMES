using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Type0 : MonoBehaviour {

	Mouse Cmouse;
	bool Me_colorSwich;
	Vector2 OldPos;
	Vector2 newPos;
	Vector2 Cha;
	// Use this for initialization
	void Start () {
		Cmouse = GameObject.Find ("Main Camera").GetComponent<Mouse> ();
		Me_colorSwich = false;
	}
	
	// Update is called once per frame
	void Update () 
	{
		if (Cmouse.drag2 && this.transform.GetChild (0).GetComponent<SpriteRenderer> ().color.a <= 0.9f&&PaturuControy.ColorUpadateCtr) 
		{
			newPos = this.transform.position;
			if (OldPos == Vector2.zero) {
			} else 
			{
				Vector2 cha
				 = newPos - OldPos;
				if(cha!=Vector2.zero)
					colorchecKDown ();
			}	
			OldPos = newPos;
		}
	}
    public void Destroy()
    {
        Destroy(this.gameObject);
    }
	void colorchecKDown()
	{
		Me_colorSwich = false;
		Collider2D[] hits;
		hits = Physics2D.OverlapCircleAll (this.transform.position, 0.45f);
		GameObject[] _hitsObj;
		_hitsObj = new GameObject[hits.Length];
		for (int i = 0; i < hits.Length; i++) 
		{
			_hitsObj [i] = hits [i].gameObject;	
		}
		for (int x = 0; x < _hitsObj.Length; x++)
		{
			if (_hitsObj [x] != this) 
			{
				if (_hitsObj [x].name == this.name) 
				{
					if (_hitsObj [x].transform.GetChild (0).GetComponent<SpriteRenderer> ().color.a > 0.8f)
					{
						this.transform.GetChild (0).GetComponent<SpriteRenderer> ().color = new Color32 (255, 255, 255, 255);
					}
				}
			}
		}

	}
}
