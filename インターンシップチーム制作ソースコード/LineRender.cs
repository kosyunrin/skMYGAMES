using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LineRender : MonoBehaviour {

    LineRenderer line;
    public Material Material;
    [SerializeField] GameObject Node;
    GameObject[] nodes;
   public List<GameObject> Nodes_list;
	// Use this for initialization
	void Start () {
        line = GetComponent<LineRenderer>();
        Nodes_list = new List<GameObject>();
    }

	// Update is called once per frame
	void Update () {
        //line.positionCount++;
	}
    public void CLineRender(GameObject hitobj,int linecount,int linesize)
    {
        GameObject _node;
        _node = Instantiate(Node, hitobj.transform.position, Quaternion.Euler(0, 0, 0), null);
        Nodes_list.Add(_node);
        line.enabled = true;
        line.positionCount = linesize;
        Vector3 linePos = new Vector3(hitobj.transform.position.x, hitobj.transform.position.y, -1);
        line.SetPosition(linecount, linePos);

        // line.materials = Material;
    }
    public void LineSwitch()
    {
        line.enabled = false;
    }
    public void destroyallNode()
    {
        nodes = GameObject.FindGameObjectsWithTag("node");
        foreach (GameObject _node in nodes)
        {
            if (nodes != null)
                Destroy(_node);
        }
    }
    public void SetlineSize(int linesize)
    {
        line.positionCount = linesize;
    }
}
