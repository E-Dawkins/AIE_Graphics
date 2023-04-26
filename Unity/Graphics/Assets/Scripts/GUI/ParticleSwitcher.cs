using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class ParticleSwitcher : MonoBehaviour
{
    [SerializeField] private Button incrementButton;
    [SerializeField] private Button decrementButton;
    [SerializeField] private List<ParticleSystem> particleSystems;
    [SerializeField] private int defaultIndex;
    [SerializeField] private ParticleButton particleButton;
    [SerializeField] private TextMeshProUGUI text;

    private int m_curIndex;

    private void Awake()
    {
        // Add increment function as a listener, with appropriate _val
        incrementButton.onClick.AddListener(() => Increment(1));
        decrementButton.onClick.AddListener(() => Increment(-1));

        // Set current index to default index
        m_curIndex = defaultIndex;
    }

    private void Increment(int _val)
    {
        // Update current index
        m_curIndex += _val;

        // Restrict current index : 0 -> max guiObjects index
        if (m_curIndex < 0) m_curIndex = particleSystems.Count - 1;
        else if (m_curIndex >= particleSystems.Count) m_curIndex = 0;
    }

    private void LateUpdate()
    {
        particleButton.particlePrefab = particleSystems[m_curIndex];
        text.text = particleButton.particlePrefab.name;
    }
}
