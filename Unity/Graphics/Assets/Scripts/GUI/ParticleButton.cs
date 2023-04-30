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
        // If current particle system has been set...
        if (m_instance == null)
        {
            // ...then instantiate the instance
            ParticleSystem instance = Instantiate(particlePrefab, prefabParent);
            m_instance = instance;
            m_instance.gameObject.SetActive(true);
        }
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        // If current particle system has been set...
        if (m_instance != null)
        {
            // ...then stop the simulation and clear the reference
            m_instance.Stop();
            m_instance = null;
        }
    }
}
