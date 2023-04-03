using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(MeshRenderer))]
public class ShaderEditor : MonoBehaviour
{
    public List<string> colorNames;
    public List<Color> colorValues;
    
    [Space]
    
    public List<string> floatNames;
    public List<float> floatValues;

    private MeshRenderer meshRenderer;

    private void Awake()
    {
        meshRenderer = GetComponent<MeshRenderer>();
    }

    // Update is called once per frame
    private void Update()
    {
        for(int i = 0; i < colorNames.Count; i++)
        {
            meshRenderer.material.SetColor(colorNames[i], colorValues[i]);
        }
        
        for(int i = 0; i < floatNames.Count; i++)
        {
            meshRenderer.material.SetFloat(floatNames[i], floatValues[i]);
        }
    }
}
