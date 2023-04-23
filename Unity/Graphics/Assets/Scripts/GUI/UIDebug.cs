using UnityEngine;

public class UIDebug : MonoBehaviour
{
    public void DebugVal(float _val) => Debug.Log($"{_val}");
}
