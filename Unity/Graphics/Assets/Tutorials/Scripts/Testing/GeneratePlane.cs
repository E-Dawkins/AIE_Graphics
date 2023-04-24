using Unity.Mathematics;

using UnityEngine;

[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class GeneratePlane : MonoBehaviour
{
    [SerializeField] private int density = 64;
    [SerializeField] private float spacing = .25f;

    private MeshFilter filter;
    private new MeshRenderer renderer;

    private void Start()
    {
        filter = GetComponent<MeshFilter>();
        renderer = GetComponent<MeshRenderer>();

        filter.mesh = CreateMesh();
        renderer.material = CreateMaterial();
    }

    private Material CreateMaterial()
    {
        Material material = new Material(Shader.Find("Unlit/Texture"));
        
        material.SetTexture("_MainTex", CreateTexture());
        
        return material;
    }

    private Texture2D CreateTexture()
    {
        Texture2D texture = new(density, density, TextureFormat.RGBA64, false)
        {
            filterMode = FilterMode.Point,
            wrapMode = TextureWrapMode.Clamp
        };

        for(int x = 0; x < density; x++)
        {
            for(int y = 0; y < density; y++)
            {
                float n = noise.cnoise(new float2(x, y) * spacing);
                
                texture.SetPixel(x, y, Color.Lerp(Color.black, Color.white, NoiseFunctions.Remap(n, -1, 1, 0, 1)));
            }
        }

        texture.Apply();
        return texture;
    }

    private Mesh CreateMesh()
    {
        Vector3[] verts = new Vector3[density * density];
        Vector2[] uvs = new Vector2[verts.Length];
        Vector3[] normals = new Vector3[verts.Length];
        int[] triangles = new int[(density - 1) * (density - 1) * 6];

        int triangleIndex = 0;

        for(int x = 0; x < density; x++)
        {
            for(int z = 0; z < density; z++)
            {
                int index = x * density + z;

                verts[index] = new Vector3
                {
                    x = x * spacing,
                    y = 0,
                    z = z * spacing
                };

                uvs[index] = new Vector2
                {
                    x = x / (float)density,
                    y = z / (float)density,
                };

                normals[index] = Vector3.up;
                
                if(x < density - 1 && z < density - 1)
                {
                    triangles[triangleIndex++] = index + 0;
                    triangles[triangleIndex++] = index + density + 1;
                    triangles[triangleIndex++] = index + density;
                    triangles[triangleIndex++] = index + 0;
                    triangles[triangleIndex++] = index + 1;
                    triangles[triangleIndex++] = index + density + 1;
                }
            }
        }

        Mesh mesh = new()
        {
            vertices = verts,
            normals = normals,
            uv = uvs,
            triangles = triangles
        };
        
        mesh.RecalculateBounds();
        mesh.RecalculateTangents();
        
        return mesh;
    }
}
