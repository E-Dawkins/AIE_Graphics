using UnityEngine;
using UnityEngine.UI;

[RequireComponent(typeof(Slider))]
public class MaterialSlider : MonoBehaviour
{
    [SerializeField] private Material material;
    [SerializeField] private string floatReference;
    
    private Slider m_slider;

    private void Awake()
    {
        // Store the slider reference
        m_slider = GetComponent<Slider>();
        
        // Add our OnSliderValueChanged function to slider event
        m_slider.onValueChanged.AddListener(OnSliderValueChanged);
        
        // Invoke the function with the default slider value, 
        // this means the slider value HAS to be pre-set :(
        m_slider.onValueChanged.Invoke(m_slider.value);
    }

    // Function to set a float with floatName, to _val of slider
    private void OnSliderValueChanged(float _val)
    {
        material.SetFloat(floatReference, _val);
    }
}