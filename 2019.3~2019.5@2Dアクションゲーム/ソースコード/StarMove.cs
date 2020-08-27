
using UnityEngine;
using System.Collections;

public class StarMove : MonoBehaviour
{

    /// <summary>
    /// 中心箭头
    /// </summary>
    [SerializeField] public GameObject centerObj;
    /// <summary>
    /// 消息图片对象
    /// </summary>
    [SerializeField] GameObject roateObj;
    /// <summary>
    /// 四元数
    /// </summary>
    [SerializeField] float angleSpeed;

    [SerializeField] bool AntiRotate;
    Quaternion qua;


    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

        if (centerObj != null)
        {
            if (AntiRotate)
            {
                //roateObj围绕centerObj旋转，x,y不旋转
                roateObj.transform.RotateAround(centerObj.transform.position,
                        new Vector3(0, 0, 1), angleSpeed * Time.deltaTime);
                //这里处理不然roateObj图片的显示位置发生变化
                qua = roateObj.transform.rotation;
                qua.z = 0;
                roateObj.transform.rotation = qua;
            }
            else
            {
                //roateObj围绕centerObj旋转，x,y不旋转
                roateObj.transform.RotateAround(centerObj.transform.position,
                        new Vector3(0, 0, 1), -angleSpeed * Time.deltaTime);
                //这里处理不然roateObj图片的显示位置发生变化
                qua = roateObj.transform.rotation;
                qua.z = 0;
                roateObj.transform.rotation = qua;
            }
        }

    }

    public void SwitchRotation()
    {
        AntiRotate = !AntiRotate;
    }



}
