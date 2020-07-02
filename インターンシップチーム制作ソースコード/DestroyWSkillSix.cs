using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyWSkillSix : MonoBehaviour {

	// Use this for initialization
	void Start () {
		PaturuControy.waterskill_six.WaterskillsixDestroy = false;
	}
	
	// Update is called once per frame
	void Update () {
		if (PaturuControy.waterskill_six.WaterskillsixDestroy)
			Destroy (this.gameObject);
	}
}
