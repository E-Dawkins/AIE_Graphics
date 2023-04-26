using UnityEngine;

[RequireComponent(typeof(ColorPicker))]
public class MaterialColorPicker : MonoBehaviour
{
    [SerializeField] private Material material;
    [SerializeField] private string colorReference;

    private ColorPicker m_picker;

    private void Awake()
    {
        m_picker = GetComponent<ColorPicker>();
    }

    private void Update()
    {
        material.SetColor(colorReference, m_picker.Color);
    }
}
