using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(ColorPicker))]
public class MaterialColorPicker : MonoBehaviour
{
    [SerializeField] private Material material;
    [SerializeField] private string colorReference;

    private ColorPicker picker;

    private void Awake()
    {
        picker = GetComponent<ColorPicker>();
    }

    private void Update()
    {
        material.SetColor(colorReference, picker.Color);
    }
}
