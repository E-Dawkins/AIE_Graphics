using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

[RequireComponent(typeof(Button))]
public class ParticleButton : MonoBehaviour, IPointerDownHandler, IPointerUpHandler
{
    public ParticleSystem particlePrefab;
    [SerializeField] private Transform prefabParent;

    private ParticleSystem m_instance;

    public void OnPointerDown(PointerEventData eventData)
    {
        if (m_instance == null)
        {
            ParticleSystem instance = Instantiate(particlePrefab, prefabParent);
            m_instance = instance;
            m_instance.gameObject.SetActive(true);
        }
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        if (m_instance != null)
        {
            m_instance.Stop();
            m_instance = null;
        }
    }
}
