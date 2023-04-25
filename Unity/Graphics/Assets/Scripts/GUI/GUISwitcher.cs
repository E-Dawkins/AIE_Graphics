using UnityEngine;
using System.Collections.Generic;
using UnityEngine.UI;

public class GUISwitcher : MonoBehaviour
{
    [SerializeField] private Button incrementButton;
    [SerializeField] private Button decrementButton;
    [SerializeField] private List<GameObject> guiObjects;
    [SerializeField] private int defaultIndex;

    private int m_curIndex;
    private bool m_firstFrame = true;

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
        if (m_curIndex < 0) m_curIndex = guiObjects.Count - 1;
        else if (m_curIndex >= guiObjects.Count) m_curIndex = 0;
    }

    private void Update()
    {
        // Skip update for first frame, allows other UI
        // scripts 1 frame to 'catch-up' (mainly sliders)
        if (m_firstFrame)
        {
            m_firstFrame = false;
            return;
        }
        
        // Set non-current objects to false, and vice versa
        for (int i = 0; i < guiObjects.Count; i++) 
            guiObjects[i].SetActive(i == m_curIndex);
    }
}