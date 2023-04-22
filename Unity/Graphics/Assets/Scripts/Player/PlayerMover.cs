using System;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerMover : MonoBehaviour
{
    [SerializeField] private float moveSpeed = 10;
    [SerializeField] private float rotateSpeed = 0.1f;
    [SerializeField] private Camera playerCam;
    
    private CharacterController m_controller;
    private Animator m_animator;
    
    private Vector2 m_moveInput;
    private Vector3 m_velocity;

    private bool m_isGrounded;

    private void Awake()
    {
        m_controller = GetComponent<CharacterController>();
        m_animator = GetComponentInChildren<Animator>();
    }

    private void Update()
    {
        m_moveInput.x = Input.GetAxis("Horizontal");
        m_moveInput.y = Input.GetAxis("Vertical");
        
        if (m_animator)
            m_animator.SetFloat("Forwards", m_moveInput.magnitude);
    }

    private void FixedUpdate()
    {
        Vector3 camForward = Vector3.ProjectOnPlane(playerCam.transform.forward, Vector3.up);
        camForward.Normalize();

        Vector3 camRight = playerCam.transform.right;

        Vector3 delta = (m_moveInput.x * camRight + m_moveInput.y * camForward) * moveSpeed;
        
        if (delta != Vector3.zero)
            transform.forward = Vector3.Lerp(transform.forward, delta, rotateSpeed);
        
        if(m_isGrounded || m_moveInput.x != 0 || m_moveInput.y != 0)
        {
            m_velocity.x = delta.x;
            m_velocity.z = delta.z;
        }
        
        if(m_isGrounded && m_velocity.y < 0)
            m_velocity.y = 0;
        
        m_velocity += Physics.gravity * Time.fixedDeltaTime;
        
        m_controller.Move(m_velocity * Time.deltaTime);
        m_isGrounded = m_controller.isGrounded;
    }
}
