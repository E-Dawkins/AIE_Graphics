using System;

using UnityEngine;

[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class TerrainGenerator : MonoBehaviour
{
	[SerializeField] private int density = 128;
	[SerializeField] private float spacing = 0.5f;
	[SerializeField] private NoiseSettings noiseSettings;
	[SerializeField] private bool alwaysRegenerate;

	private MeshFilter filter;
	private new MeshRenderer renderer;

	private void Start()
	{
		filter = GetComponent<MeshFilter>();
		renderer = GetComponent<MeshRenderer>();
		
		GenerateMap();
	}

	private void Update()
	{
		if (alwaysRegenerate)
			GenerateMap();
	}

	private void GenerateMap()
	{
		float[,] noiseMap = NoiseFunctions.GenerateNoiseMap(density, noiseSettings);

		filter.mesh = MeshGenerator.Generate(density, noiseMap, spacing);
	}
}