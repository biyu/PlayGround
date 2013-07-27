using UnityEngine;
using System;
using System.Collections;

public class CharacterEditor : MonoBehaviour
{
	public bool Shown = false;
	public string EditorTitle = "Character Editor";
	public int EditorWindowWidth = 300;
	public int EditorWindowHeight = 200;
	public Rect EditorWindowRect;
	
	private int EditorWindowId = 0;	
	private BasicCharacter BasicCharacterInfo;
	
	private void Start()
	{
		this.BasicCharacterInfo = this.GetComponent<BasicCharacter>();
	}
	
	private void OnGUI()
	{
		if (this.Shown)
		{
			this.EditorWindowRect = GUI.Window(this.EditorWindowId, new Rect(20, 20, this.EditorWindowWidth, this.EditorWindowHeight), this.DrawEditorWindow, this.EditorTitle);
		}
	}
				
	private void DrawEditorWindow(int windowId)
	{
		GUILayout.BeginVertical();
		for (int i = 0; i < Enum.GetNames(typeof(AttributeName)).Length; i++)
		{
			this.DrawAttributeEditorControl((AttributeName)i, true);
		}
		for (int i = 0; i < Enum.GetNames(typeof(BasicCharacterStateName)).Length; i++)
		{
			this.DrawCharacterStateEditorControl((BasicCharacterStateName)i);
		}
		GUILayout.EndVertical();
	}
	
	private void DrawAttributeEditorControl(AttributeName attr, bool changalbe)
	{
		Attribute targetAttr = this.BasicCharacterInfo.GetCharAttribute(attr);
		GUILayout.BeginHorizontal();
		GUILayout.Label(Enum.GetName(typeof(AttributeName), attr));
		GUILayout.Space(80);
		GUILayout.Box(targetAttr.AdjustedValue.ToString());
		GUILayout.Space(30);
		if (changalbe)
		{
			if (GUILayout.Button("+", GUILayout.Width(20)))
			{
				targetAttr.BasicValue++;
			}
			if (GUILayout.Button("-", GUILayout.Width(20)))
			{
				targetAttr.BasicValue = Math.Max(--targetAttr.BasicValue, 0);
			}
		}
		GUILayout.Space(30);
		GUILayout.EndHorizontal();
	}
	
	private void DrawCharacterStateEditorControl(BasicCharacterStateName state)
	{
		BasicCharacterState targetAttr = this.BasicCharacterInfo.GetCharBasicCharacterState(state);
		GUILayout.BeginHorizontal();
		GUILayout.Label(Enum.GetName(typeof(BasicCharacterStateName), state), GUILayout.Width(100));
		GUILayout.FlexibleSpace();
		GUILayout.Box(targetAttr.AdjustedValue.ToString(), GUILayout.Width(80));
		GUILayout.FlexibleSpace();
		GUILayout.EndHorizontal();
	}
}
