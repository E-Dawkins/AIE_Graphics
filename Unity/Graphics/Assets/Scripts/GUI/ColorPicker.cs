using UnityEngine;
using UnityEngine.UI;

public class ColorPicker : MonoBehaviour
{
    [SerializeField] private Slider redSlider;
    [SerializeField] private Slider greenSlider;
    [SerializeField] private Slider blueSlider;
    [SerializeField] private Slider alphaSlider;
    [SerializeField] private bool useAlpha = true;

    [SerializeField] private Image preview;

    private Image[] handles = new Image[4];

    public Color Color => color;
    private Color color = Color.black;

    private void Awake()
    {
        handles[0] = redSlider.handleRect.GetComponent<Image>();
        handles[1] = greenSlider.handleRect.GetComponent<Image>();
        handles[2] = blueSlider.handleRect.GetComponent<Image>();
        handles[3] = alphaSlider.handleRect.GetComponent<Image>();
    }

    private void Update()
    {
        handles[0].color = new Color(redSlider.value, 0, 0, 1);
        handles[1].color = new Color(0, greenSlider.value, 0, 1);
        handles[2].color = new Color(0, 0, blueSlider.value, 1);
        handles[3].color = new Color(alphaSlider.value, alphaSlider.value, alphaSlider.value, 1);

        color = new Color(redSlider.value, greenSlider.value, blueSlider.value, 
                                useAlpha ? alphaSlider.value : 1);
        preview.color = color;
    }
}
