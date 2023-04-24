//------------------------------------------------------------------------------
// <auto-generated>
//     This code was auto-generated by com.unity.inputsystem:InputActionCodeGenerator
//     version 1.4.4
//     from Assets/_Data/Inputs.inputactions
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Utilities;

public partial class @Inputs : IInputActionCollection2, IDisposable
{
    public InputActionAsset asset { get; }
    public @Inputs()
    {
        asset = InputActionAsset.FromJson(@"{
    ""name"": ""Inputs"",
    ""maps"": [
        {
            ""name"": ""PlayerGameplay"",
            ""id"": ""0595d04f-c74c-4a1f-9b74-820f7f34e6b3"",
            ""actions"": [
                {
                    ""name"": ""Movement"",
                    ""type"": ""Value"",
                    ""id"": ""d4d21619-e49a-4408-b4bd-f0192c0121f4"",
                    ""expectedControlType"": ""Vector2"",
                    ""processors"": """",
                    ""interactions"": """",
                    ""initialStateCheck"": true
                },
                {
                    ""name"": ""Look"",
                    ""type"": ""Button"",
                    ""id"": ""ce68bcf2-d503-451b-9d4e-0580fb5ad6d8"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """",
                    ""initialStateCheck"": false
                },
                {
                    ""name"": ""Shoot"",
                    ""type"": ""Button"",
                    ""id"": ""db5b46a0-0f37-41f2-ba43-4561ba5d91dc"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """",
                    ""initialStateCheck"": false
                },
                {
                    ""name"": ""Interact"",
                    ""type"": ""Button"",
                    ""id"": ""51786afa-12dd-4598-933d-7756de5e6d07"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """",
                    ""initialStateCheck"": false
                },
                {
                    ""name"": ""Sprint"",
                    ""type"": ""Button"",
                    ""id"": ""5f0fcd31-68f1-4a40-b806-f22642db1819"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """",
                    ""initialStateCheck"": false
                },
                {
                    ""name"": ""Jump"",
                    ""type"": ""Button"",
                    ""id"": ""d9f3decb-92b1-487e-a790-3a8ebc2a6c0a"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """",
                    ""initialStateCheck"": false
                },
                {
                    ""name"": ""Grenade"",
                    ""type"": ""Button"",
                    ""id"": ""fd2d32d0-16ab-4f12-a8e1-cc513f7a8bc0"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """",
                    ""initialStateCheck"": false
                }
            ],
            ""bindings"": [
                {
                    ""name"": ""WASD"",
                    ""id"": ""479d63a8-0b69-4993-a4e2-8add67e561c1"",
                    ""path"": ""2DVector"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Movement"",
                    ""isComposite"": true,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": ""up"",
                    ""id"": ""fe5d846f-c868-4dfc-88db-0f7d8d04fe06"",
                    ""path"": ""<Keyboard>/w"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Movement"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": true
                },
                {
                    ""name"": ""down"",
                    ""id"": ""c5a4d680-ebbc-41d5-a7bc-bc022d7661a1"",
                    ""path"": ""<Keyboard>/s"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Movement"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": true
                },
                {
                    ""name"": ""left"",
                    ""id"": ""925e1a2c-7770-42ee-9e8e-d710e53e2423"",
                    ""path"": ""<Keyboard>/a"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Movement"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": true
                },
                {
                    ""name"": ""right"",
                    ""id"": ""eeafecbd-8e04-46a5-8217-52a73ec53f2a"",
                    ""path"": ""<Keyboard>/d"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Movement"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": true
                },
                {
                    ""name"": """",
                    ""id"": ""5c3201f8-dd64-4070-85f5-682b848d7a2d"",
                    ""path"": ""<Mouse>/rightButton"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Look"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""4bf261b6-7bbc-4fc8-857b-a610e00048e1"",
                    ""path"": ""<Mouse>/leftButton"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Shoot"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""5a04851f-2f6f-46f1-893b-b3e981391369"",
                    ""path"": ""<Keyboard>/e"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Interact"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""22d86158-53f5-449c-b4d4-888b0bb1e724"",
                    ""path"": ""<Keyboard>/leftShift"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Sprint"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""58cebeee-9c52-4143-9d41-4921de1839f5"",
                    ""path"": ""<Keyboard>/space"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Jump"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""f72e7ed9-7665-40e3-b18f-e1b6c1c5a95a"",
                    ""path"": ""<Keyboard>/g"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Grenade"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                }
            ]
        }
    ],
    ""controlSchemes"": []
}");
        // PlayerGameplay
        m_PlayerGameplay = asset.FindActionMap("PlayerGameplay", throwIfNotFound: true);
        m_PlayerGameplay_Movement = m_PlayerGameplay.FindAction("Movement", throwIfNotFound: true);
        m_PlayerGameplay_Look = m_PlayerGameplay.FindAction("Look", throwIfNotFound: true);
        m_PlayerGameplay_Shoot = m_PlayerGameplay.FindAction("Shoot", throwIfNotFound: true);
        m_PlayerGameplay_Interact = m_PlayerGameplay.FindAction("Interact", throwIfNotFound: true);
        m_PlayerGameplay_Sprint = m_PlayerGameplay.FindAction("Sprint", throwIfNotFound: true);
        m_PlayerGameplay_Jump = m_PlayerGameplay.FindAction("Jump", throwIfNotFound: true);
        m_PlayerGameplay_Grenade = m_PlayerGameplay.FindAction("Grenade", throwIfNotFound: true);
    }

    public void Dispose()
    {
        UnityEngine.Object.Destroy(asset);
    }

    public InputBinding? bindingMask
    {
        get => asset.bindingMask;
        set => asset.bindingMask = value;
    }

    public ReadOnlyArray<InputDevice>? devices
    {
        get => asset.devices;
        set => asset.devices = value;
    }

    public ReadOnlyArray<InputControlScheme> controlSchemes => asset.controlSchemes;

    public bool Contains(InputAction action)
    {
        return asset.Contains(action);
    }

    public IEnumerator<InputAction> GetEnumerator()
    {
        return asset.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    public void Enable()
    {
        asset.Enable();
    }

    public void Disable()
    {
        asset.Disable();
    }
    public IEnumerable<InputBinding> bindings => asset.bindings;

    public InputAction FindAction(string actionNameOrId, bool throwIfNotFound = false)
    {
        return asset.FindAction(actionNameOrId, throwIfNotFound);
    }
    public int FindBinding(InputBinding bindingMask, out InputAction action)
    {
        return asset.FindBinding(bindingMask, out action);
    }

    // PlayerGameplay
    private readonly InputActionMap m_PlayerGameplay;
    private IPlayerGameplayActions m_PlayerGameplayActionsCallbackInterface;
    private readonly InputAction m_PlayerGameplay_Movement;
    private readonly InputAction m_PlayerGameplay_Look;
    private readonly InputAction m_PlayerGameplay_Shoot;
    private readonly InputAction m_PlayerGameplay_Interact;
    private readonly InputAction m_PlayerGameplay_Sprint;
    private readonly InputAction m_PlayerGameplay_Jump;
    private readonly InputAction m_PlayerGameplay_Grenade;
    public struct PlayerGameplayActions
    {
        private @Inputs m_Wrapper;
        public PlayerGameplayActions(@Inputs wrapper) { m_Wrapper = wrapper; }
        public InputAction @Movement => m_Wrapper.m_PlayerGameplay_Movement;
        public InputAction @Look => m_Wrapper.m_PlayerGameplay_Look;
        public InputAction @Shoot => m_Wrapper.m_PlayerGameplay_Shoot;
        public InputAction @Interact => m_Wrapper.m_PlayerGameplay_Interact;
        public InputAction @Sprint => m_Wrapper.m_PlayerGameplay_Sprint;
        public InputAction @Jump => m_Wrapper.m_PlayerGameplay_Jump;
        public InputAction @Grenade => m_Wrapper.m_PlayerGameplay_Grenade;
        public InputActionMap Get() { return m_Wrapper.m_PlayerGameplay; }
        public void Enable() { Get().Enable(); }
        public void Disable() { Get().Disable(); }
        public bool enabled => Get().enabled;
        public static implicit operator InputActionMap(PlayerGameplayActions set) { return set.Get(); }
        public void SetCallbacks(IPlayerGameplayActions instance)
        {
            if (m_Wrapper.m_PlayerGameplayActionsCallbackInterface != null)
            {
                @Movement.started -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnMovement;
                @Movement.performed -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnMovement;
                @Movement.canceled -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnMovement;
                @Look.started -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnLook;
                @Look.performed -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnLook;
                @Look.canceled -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnLook;
                @Shoot.started -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnShoot;
                @Shoot.performed -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnShoot;
                @Shoot.canceled -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnShoot;
                @Interact.started -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnInteract;
                @Interact.performed -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnInteract;
                @Interact.canceled -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnInteract;
                @Sprint.started -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnSprint;
                @Sprint.performed -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnSprint;
                @Sprint.canceled -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnSprint;
                @Jump.started -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnJump;
                @Jump.performed -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnJump;
                @Jump.canceled -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnJump;
                @Grenade.started -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnGrenade;
                @Grenade.performed -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnGrenade;
                @Grenade.canceled -= m_Wrapper.m_PlayerGameplayActionsCallbackInterface.OnGrenade;
            }
            m_Wrapper.m_PlayerGameplayActionsCallbackInterface = instance;
            if (instance != null)
            {
                @Movement.started += instance.OnMovement;
                @Movement.performed += instance.OnMovement;
                @Movement.canceled += instance.OnMovement;
                @Look.started += instance.OnLook;
                @Look.performed += instance.OnLook;
                @Look.canceled += instance.OnLook;
                @Shoot.started += instance.OnShoot;
                @Shoot.performed += instance.OnShoot;
                @Shoot.canceled += instance.OnShoot;
                @Interact.started += instance.OnInteract;
                @Interact.performed += instance.OnInteract;
                @Interact.canceled += instance.OnInteract;
                @Sprint.started += instance.OnSprint;
                @Sprint.performed += instance.OnSprint;
                @Sprint.canceled += instance.OnSprint;
                @Jump.started += instance.OnJump;
                @Jump.performed += instance.OnJump;
                @Jump.canceled += instance.OnJump;
                @Grenade.started += instance.OnGrenade;
                @Grenade.performed += instance.OnGrenade;
                @Grenade.canceled += instance.OnGrenade;
            }
        }
    }
    public PlayerGameplayActions @PlayerGameplay => new PlayerGameplayActions(this);
    public interface IPlayerGameplayActions
    {
        void OnMovement(InputAction.CallbackContext context);
        void OnLook(InputAction.CallbackContext context);
        void OnShoot(InputAction.CallbackContext context);
        void OnInteract(InputAction.CallbackContext context);
        void OnSprint(InputAction.CallbackContext context);
        void OnJump(InputAction.CallbackContext context);
        void OnGrenade(InputAction.CallbackContext context);
    }
}
