using System.Linq;

using Unity.Mathematics;
using UnityEngine;

[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class GenerateQuad : MonoBehaviour
{
    private MeshFilter meshFilter;
    private new MeshRenderer renderer;
    
    private void Start()
    {
        meshFilter = GetComponent<MeshFilter>();
        renderer = GetComponent<MeshRenderer>();

        Vector3[] verts =
        {
            Vector3.up,
            Vector3.up + Vector3.right,
            Vector3.zero,
            Vector3.right
        };

        int[] tris =
        {
            0, 1, 3,
            0, 3, 2
        };

        Vector3[] normals =
        {
            Vector3.forward,
            Vector3.forward,
            Vector3.forward,
            Vector3.forward
        };

        Vector2[] uvs =
        {
            new(0, 0),
            new(1, 0),
            new(0, 1),
            new(1, 1),
        };

        Color[] colors =
        {
            Color.green,
            Color.red,
            Color.blue,
            Color.yellow
        };

        Mesh mesh = new()
        {
            vertices = verts.ToArray(),
            uv = uvs.ToArray(),
            normals = normals.ToArray(),
            triangles = tris,
            colors = colors
        };
        
        mesh.RecalculateBounds();
        mesh.RecalculateTangents();
        meshFilter.mesh = mesh;

        Texture2D texture = new(64, 64, TextureFormat.RGBA32, false)
        {
            filterMode = FilterMode.Point,
            alphaIsTransparency = true
        };

        bool isGrey = true;
        for(int x = 0; x < texture.width; x++)
        {
            for(int y = 0; y < texture.height; y++)
            {
                if((y * texture.width + x) % 4 == 0)
                    isGrey = !isGrey;

                Color color = isGrey ? Color.gray : Color.white;
                texture.SetPixel(x, y, color);
            }
        }

        texture.Apply();
        renderer.material.mainTexture = texture;
    }
}
