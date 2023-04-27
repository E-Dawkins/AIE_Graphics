using UnityEngine;
using System.Collections.Generic;

public class MaterialScaler : MonoBehaviour
{
    [SerializeField] private Vector2 scaleMulti = Vector2.one;
    [SerializeField] private List<Material> ignoredMaterials;

    private void Start()
    {
        var renderers = FindObjectsOfType<Renderer>();

        foreach (var rend in renderers)
        {
        
            var mat = rend.material;
            
            

            var trans = rend.gameObject.transform;
            
            mat.mainTextureScale = new Vector2(
                Mathf.Max(trans.localScale.x, trans.localScale.z) * scaleMulti.x, 
                trans.localScale.y * scaleMulti.y);
        }
    }
}