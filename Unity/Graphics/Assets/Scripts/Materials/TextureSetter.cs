using UnityEngine;
using System.Collections.Generic;

[RequireComponent(typeof(Renderer))]
public class TextureSetter : MonoBehaviour
{
    [SerializeField] private List<string> references;
    [SerializeField] private List<Texture> textures;
    [SerializeField] private int materialIndex;
    
    private MeshRenderer m_renderer;

    private void Awake()
    {
        m_renderer = GetComponent<MeshRenderer>();

        Material mat = GetComponent<Renderer>().materials[materialIndex];

        for (int i = 0; i < references.Count; i++)
        {
            mat.SetTexture(references[i], textures[i]);
        }
    }
}
