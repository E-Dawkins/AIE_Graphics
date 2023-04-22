using Unity.Mathematics;
using UnityEngine;

[CreateAssetMenu(fileName = "NewNoiseSettings", menuName = "Noise Settings", order = 0)]
public class NoiseSettings : ScriptableObject
{
	public int Seed => seed.GetHashCode();

	public string seed;

	public float scale = 1.5f;
	public int octaves = 8;

	public float persistance = 0.8f;
	public float lacunarity = 0.25f;

	public float2 offset;
}