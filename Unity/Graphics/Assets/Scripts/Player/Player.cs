using Cinemachine;
using UnityEngine;
using UnityEngine.InputSystem;

[RequireComponent(typeof(Animator), typeof(PlayerInput), typeof(CharacterController))]
public class Player : MonoBehaviour
{
    // Set in inspector
    [SerializeField] private CinemachineVirtualCamera virtualCamera;
    [SerializeField] private float moveSpeed = 1;
    [SerializeField] private float sprintSpeed = 3;
    [SerializeField] private float rotateSpeed = 0.1f;
    [SerializeField] private Vector2 lookSpeeds = new(100, 200);

    // Set on awake
    private Animator m_animator;
    private CharacterController m_controller;

    // This will contain basic controls based on our key inputs
    private Vector2 m_direction;
    private bool m_isMoving;
    private bool m_isSprinting;
    private bool m_shouldLook;

    // Private fields
    private float m_speed;
    private CinemachinePOV m_pov;
    private CinemachineFramingTransposer m_transposer;
    private float m_lookMulti = 1;

    private void Awake()
    {
        // Store component references
        m_animator = GetComponent<Animator>();
        m_controller = GetComponent<CharacterController>();
        m_pov = virtualCamera.GetCinemachineComponent<CinemachinePOV>();
        m_transposer = virtualCamera.GetCinemachineComponent<CinemachineFramingTransposer>();
    }

    public void OnMove(InputAction.CallbackContext _value)
    {
        // Set move direction, and is moving bool
        m_direction = _value.ReadValue<Vector2>();
        m_isMoving = (m_direction != Vector2.zero);
    }

    public void OnSprint(InputAction.CallbackContext _value)
    {
        // Set sprint bool on/off based on the sprint key
        // being pressed down or let go of
        if (_value.started)
            m_isSprinting = true;
        
        else if (_value.canceled)
            m_isSprinting = false;
    }

    public void OnLook(InputAction.CallbackContext _value)
    {
        // This bool is solely so that you have to
        // hold RMB to look around, otherwise it is constant
        m_shouldLook = _value.ReadValueAsButton();
    }

    public void OnShoulderSwitch(InputAction.CallbackContext _value)
    {
        // Switch transposer's screen x pos, when key pressed
        m_transposer.m_ScreenX = 1 - m_transposer.m_ScreenX;
    }

    public void OnInteract(InputAction.CallbackContext _value)
    {
        // If interact button pressed, run the animation override
        if (_value.started)
            m_animator.SetTrigger("PointTrigger");
    }

    public void OnSensitivty(InputAction.CallbackContext _value)
    {
        // Read in the input value and store it
        var val = _value.ReadValue<float>();
        if (val == 0) return;
        
        // Apply the input to the look sensitivity multiplier
        m_lookMulti += Mathf.Sign(val) * 0.1f;
        
        // If look multiplier is negative or zero, set it to a really small value
        if (m_lookMulti <= 0) m_lookMulti = 0.1f;
    }

    private void FixedUpdate()
    {
        // Movement speed based on if sprinting and is moving
        m_speed = m_isSprinting ? sprintSpeed : (!m_isMoving ? 0 : moveSpeed);
        CasualMovement(Time.fixedDeltaTime);

        // Apply the move vector to the player controller
        Vector3 move = new Vector3(m_direction.x, 0, m_direction.y);
        move = move.x * virtualCamera.transform.right + move.z * virtualCamera.transform.forward;
        move.y = 0;
        m_controller.Move(move.normalized * Time.fixedDeltaTime * m_speed);

        // If movement is > zero...
        if (move != Vector3.zero)
        {
            // ...then set the player rotation to where we are looking
            Quaternion rotation = Quaternion.Euler(0, virtualCamera.transform.eulerAngles.y, 0);
            transform.rotation = Quaternion.Lerp(transform.rotation, rotation, Time.fixedDeltaTime * rotateSpeed);
        }

        // Update POV speeds to only work when we are pressing look button
        if (m_shouldLook)
        {
            m_pov.m_HorizontalAxis.m_MaxSpeed = lookSpeeds.x * m_lookMulti;
            m_pov.m_VerticalAxis.m_MaxSpeed = lookSpeeds.y * m_lookMulti;
        }
        else
        {
            m_pov.m_HorizontalAxis.m_MaxSpeed = 0;
            m_pov.m_VerticalAxis.m_MaxSpeed = 0;
        }
    }

    private void CasualMovement(float _dt)
    {
        // Speed is set based on isMoving bool
        float speed = m_isMoving ? m_speed : 0;
        
        // Movement direction normalized
        Vector2 direction = m_direction.normalized;
        
        // Set animator floats based off move direction / speed
        m_animator.SetFloat("Forward", direction.y * speed, 0.1f, _dt);
        m_animator.SetFloat("Right", direction.x * speed, 0.1f, _dt);
    }
}