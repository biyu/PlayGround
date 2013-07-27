using UnityEngine;
using System.Collections;

public class BasicSkillPanelManager : MonoBehaviour {
	
	public BasicSkillToggleIcon[] SkillIcons;
	
	// Use this for initialization
	private void Awake ()
	{
		this.SkillIcons = this.gameObject.GetComponentsInChildren<BasicSkillToggleIcon>();
	}
	
	public void SetActiveSkill(int index)
	{
		InActiveAllSkill();
		this.SkillIcons[index].SetActive(true);
	}
	
	private void InActiveAllSkill()
	{
		foreach (BasicSkillToggleIcon icon in this.SkillIcons)
		{
			icon.SetActive(false);
		}
	}
}
