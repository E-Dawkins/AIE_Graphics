using UnityEngine;

public class CameraController : MonoBehaviour
{
    [Header("Main")]
    [SerializeField] private Transform target;
    [SerializeField] private float heightOffset = 1.5f;
    [SerializeField] private float lookSpeed = 180;
    [SerializeField] private float relaxSpeed = 0.1f;
    [SerializeField] private bool invertY = true;
    
    [Header("Zoom")]
    [SerializeField] private float zoomSpeed = 1;
    [SerializeField] private float minZoomDist = 2;
    [SerializeField] private float maxZoomDist = 10;
    [SerializeField, Range(0, 1)] private float defaultInRange;
    
    private float m_currentDistance;
    private float m_distanceBack;
    
    private void Start()
    {
        m_distanceBack = minZoomDist + (maxZoomDist - minZoomDist) * defaultInRange;
        m_currentDistance = m_distanceBack;
    }
    
    private void Update()
    {
        if(Input.GetMouseButton(1))
        {
            Vector3 angles = transform.eulerAngles;

            float dx = Input.GetAxis("Mouse Y") * (invertY ? -1 : 1);
            float dy = Input.GetAxis("Mouse X");
            
            // Look up and down by rotating around the X-axis
            angles.x = Mathf.Clamp(angles.x + dx * lookSpeed * Time.deltaTime, 0, 70);

            // Spin the camera sideways around target
            angles.y += dy * lookSpeed * Time.deltaTime;
            transform.eulerAngles = angles;
        }
        
        // Zoom in / out with scroll wheel
        m_distanceBack = Mathf.Clamp(m_distanceBack - Input.GetAxis("Mouse ScrollWheel") * zoomSpeed, minZoomDist, maxZoomDist);
        m_currentDistance = Mathf.Lerp(m_currentDistance, m_distanceBack, relaxSpeed);
        
        // Look at target point
        transform.position = GetTargetPosition() - m_currentDistance * transform.forward;
    }
    
    private Vector3 GetTargetPosition()
    {
        return target.position + heightOffset * Vector3.up;
    }
}
