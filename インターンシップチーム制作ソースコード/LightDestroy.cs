using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightDestroy : MonoBehaviour {
    [SerializeField] float DestroyTime;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        Destroy(this.gameObject, DestroyTime);	
	}
}
