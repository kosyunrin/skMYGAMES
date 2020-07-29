using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class EdgeDetectNormalsAndDepth : PostEffectsBase {

    public Shader edgeDetectShader;
    private Material edgeDetectMaterial = null;
    public Material material {
        get {
            edgeDetectMaterial = CheckShaderAndCreateMaterial(edgeDetectShader, edgeDetectMaterial);
            return edgeDetectMaterial;
        }
    }

    [Range(0.0f, 1.0f)]
    public float edgesOnly = 0.0f;

    public Color edgeColor = Color.black;

    public Color backgroundColor = Color.white;

    public float sampleDistance = 1.0f;

    public float sensitivityDepth = 1.0f;

    public float sensitivityNormals = 1.0f;

    public Color DetectiveColor = Color.white;
    [Range(0.0f, 1000.0f)]
    public float DetectiveRange = 100.0f;
    [Range(0.0f, 50.0f)]
    public float DetectiveRangeWidth = 10.0f;
    [Range(0.0f, 200.0f)]
    public float DetectiveRangeLimit = 0.0f;
    [Range(-20.0f, 20.0f)]
    public float DetectiveSpeed = 0.3f;

    private Camera myCamera;
    public Camera camera
    {
        get
        {
            if (myCamera == null)
            {
                myCamera = GetComponent<Camera>();
            }
            return myCamera;
        }
    }
    public string myDetectiveTexturePath;
    public string myDetectiveTextureName;
    public int myDetectiveTextureWidth;
    public int myDetectiveTextureLength;
    private Texture2D myDetectiveTexture;
    private byte[] ReadPNG(string _path)
    {
        FileStream fileStream = new FileStream(_path, FileMode.Open, System.IO.FileAccess.Read);
        fileStream.Seek(0, SeekOrigin.Begin);
        byte[] binary = new byte[fileStream.Length];
        fileStream.Read(binary, 0, (int)fileStream.Length);
        fileStream.Close();
        fileStream.Dispose();
        fileStream = null;
        return binary;
    }
    private void LoadFromFile(string _path, string _name)
    {
        myDetectiveTexture = new Texture2D(myDetectiveTextureWidth, myDetectiveTextureLength);
        myDetectiveTexture.LoadImage(ReadPNG(_path + _name));
    }
    void OnEnable() {
        camera.depthTextureMode |= DepthTextureMode.Depth;
        camera.depthTextureMode |= DepthTextureMode.DepthNormals;
        CurrentRange = DetectiveRangeLimit;
        LoadFromFile(myDetectiveTexturePath, myDetectiveTextureName);
    }

    private float CurrentRange = 0.0f;
    public GameObject Player;
    private Matrix4x4 CurrentViewProjectionInverseMatrix;
    void FixedUpdate()
    {
        CurrentRange += DetectiveSpeed;
        if (DetectiveSpeed > 0)
        {
            if (CurrentRange >= DetectiveRange)
                CurrentRange = DetectiveRange;
        }
        else
        {
            if (CurrentRange <= DetectiveRangeLimit)
            {
                CurrentRange = DetectiveRangeLimit;
                this.enabled = false;
            }
        }
    }
  public void EdgeEnd()
    {
        DetectiveSpeed *= -1.0f;
    }
    public void EdgeStart()
    {
        DetectiveSpeed = Math.Abs(DetectiveSpeed);
    }
   

	[ImageEffectOpaque]
	void OnRenderImage (RenderTexture src, RenderTexture dest) {
		if (material != null) {
			material.SetFloat("_EdgeOnly", edgesOnly);
			material.SetColor("_EdgeColor", edgeColor);
			material.SetColor("_BackgroundColor", backgroundColor);
			material.SetFloat("_SampleDistance", sampleDistance);
			material.SetVector("_Sensitivity", new Vector4(sensitivityNormals, sensitivityDepth, 0.0f, 0.0f));
            material.SetColor("_DetectiveColor", DetectiveColor);
            material.SetFloat("_DetectiveRange", CurrentRange);
            material.SetFloat("_DetectiveRangeWidth", DetectiveRangeWidth);
            material.SetFloat("_DetectiveRangeLimit", DetectiveRangeLimit);
            material.SetVector("_PlayerPosition", new Vector4(Player.transform.position.x, Player.transform.position.y, Player.transform.position.z, 1.0f));
            CurrentViewProjectionInverseMatrix = camera.projectionMatrix * camera.worldToCameraMatrix;
            CurrentViewProjectionInverseMatrix = CurrentViewProjectionInverseMatrix.inverse;
            material.SetMatrix("_CurrentViewProjectionInverseMatrix", CurrentViewProjectionInverseMatrix);
            material.SetMatrix("_CurrentCameraToWorldMatrix", camera.cameraToWorldMatrix);
            material.SetTexture("_DetectiveTexture", myDetectiveTexture);
            material.SetFloat("_DetectiveTextureWidth", (float)myDetectiveTextureWidth);
            material.SetFloat("_DetectiveTextureLength", (float)myDetectiveTextureLength);

            Graphics.Blit(src, dest, material);
		} else {
			Graphics.Blit(src, dest);
		}
	}
}