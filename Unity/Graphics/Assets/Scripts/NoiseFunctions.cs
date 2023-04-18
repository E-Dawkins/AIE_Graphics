using Unity.Mathematics;

using Random = System.Random;

public static class NoiseFunctions
{
	public static float[,] GenerateNoiseMap(int _density, NoiseSettings _settings)
	{
		float[,] noiseMap = new float[_density, _density];

		Random prng = new(_settings.Seed);
		float2[] octaveOffsets = new float2[_settings.octaves];

		for(int i = 0; i < _settings.octaves; i++)
		{
			octaveOffsets[i] = new float2
			{
				x = prng.Next(-10000, 10000) + _settings.offset.x,
				y = prng.Next(-10000, 10000) + _settings.offset.y,
			};
		}

		float halfDensity = _density / 2;
		
		for(int x = 0; x < _density; x++)
		{
			for(int y = 0; y < _density; y++)
			{
				float amplitude = 1;
				float frequency = 1;

				float noiseHeight = 0;

				for(int i = 0; i < _settings.octaves; i++)
				{
					float sampleX = (x - halfDensity + octaveOffsets[i].x) / _settings.scale * frequency;
					float sampleY = (y - halfDensity + octaveOffsets[i].y) / _settings.scale * frequency;

					float perlin = Remap(noise.cnoise(new float2(sampleX, sampleY)), -1, 1, 0, 1);

					noiseHeight += perlin * amplitude;

					amplitude *= _settings.persistance;
					frequency *= _settings.lacunarity;
				}

				noiseMap[x, y] = noiseHeight;
			}
		}

		return noiseMap;
	}

	public static float Remap(float _val, float _oldMin, float _oldMax, float _newMin, float _newMax)
	{
		return (_val - _oldMin) / (_oldMax - _oldMin) * (_newMax - _newMin) + _newMin;
	}
}