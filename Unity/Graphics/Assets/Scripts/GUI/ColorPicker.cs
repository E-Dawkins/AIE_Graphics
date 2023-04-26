using UnityEngine;
using UnityEngine.UI;

public class ColorPicker : MonoBehaviour
{
    [Header("Components")]
    [SerializeField] private Slider rSlider;
    [SerializeField] private Slider gSlider;
    [SerializeField] private Slider bSlider;
    [SerializeField] private Slider aSlider;
    [SerializeField] private Image preview;
    
    [Header("Color")]
    [SerializeField] private Color defaultColor;
    [SerializeField] private bool useAlpha;

    private readonly Image[] m_handles = new Image[4];

    public Color Color { get; private set; } = Color.black;

    private void Awake()
    {
        // Store references to the slider handle images
        m_handles[0] = rSlider.handleRect.GetComponent<Image>();
        m_handles[1] = gSlider.handleRect.GetComponent<Image>();
        m_handles[2] = bSlider.handleRect.GetComponent<Image>();
        m_handles[3] = aSlider.handleRect.GetComponent<Image>();
        
        // Set slider active state and value, based on useAlpha
        aSlider.gameObject.SetActive(useAlpha);
        aSlider.value = useAlpha ? aSlider.value : aSlider.maxValue;
        
        // Set sliders to default color
        rSlider.value = defaultColor.r * rSlider.maxValue;
        gSlider.value = defaultColor.g * gSlider.maxValue;
        bSlider.value = defaultColor.b * bSlider.maxValue;
        aSlider.value = defaultColor.a * aSlider.maxValue;

        // Invoke slider value changed event
        rSlider.onValueChanged.Invoke(rSlider.value);
        gSlider.onValueChanged.Invoke(gSlider.value);
        bSlider.onValueChanged.Invoke(bSlider.value);
        aSlider.onValueChanged.Invoke(aSlider.value);
    }

    private void Update()
    {
        // Store normalized slider values
        float r = rSlider.normalizedValue;
        float g = gSlider.normalizedValue;
        float b = bSlider.normalizedValue;
        float a = aSlider.normalizedValue;
        
        // Set slider colors, based on above values
        m_handles[0].color = new Color(r, 0, 0, 1);
        m_handles[1].color = new Color(0, g, 0, 1);
        m_handles[2].color = new Color(0, 0, b, 1);
        m_handles[3].color = new Color(a, a, a, 1);

        // Set Color to rgba, then preview to Color
        Color = new Color(r, g, b, a);
        preview.color = Color;
    }
}
