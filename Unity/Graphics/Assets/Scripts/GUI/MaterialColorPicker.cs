using UnityEngine;

[RequireComponent(typeof(ColorPicker))]
public class MaterialColorPicker : MonoBehaviour
{
    [SerializeField] private Material material;
    [SerializeField] private string colorReference;

    private ColorPicker m_picker;

    private void Awake()
    {
        // Store color picker component
        m_picker = GetComponent<ColorPicker>();
    }

    private void Update()
    {
        // Set material color with 'colorReference' to picker's color
        material.SetColor(colorReference, m_picker.Color);
    }
}
