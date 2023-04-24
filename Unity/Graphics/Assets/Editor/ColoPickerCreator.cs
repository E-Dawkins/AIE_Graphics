using UnityEngine;
using UnityEditor;

public class ColoPickerCreator : MonoBehaviour
{
    [MenuItem("GameObject/UI/Color Picker")]
    private static void CreateColorPicker()
    {
        bool canView = Selection.activeGameObject && Selection.activeGameObject.GetComponentInParent<Canvas>();

        if (!canView)
            return;

        var item = Resources.Load("UI/Color Picker");
        var instance = PrefabUtility.InstantiatePrefab(item, Selection.activeTransform);

        Undo.RegisterCreatedObjectUndo(instance, $"Create {instance.name}");
        Selection.activeObject = instance;
    }
}
