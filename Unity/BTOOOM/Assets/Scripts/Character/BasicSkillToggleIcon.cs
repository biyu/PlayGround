using UnityEngine;
using System.Collections;

public class BasicSkillToggleIcon : MonoBehaviour
{
	public Texture ActiveTexture;
	public Texture InactiveTexture;
	
	public void SetActive(bool active)
	{
		this.guiTexture.texture = active ? this.ActiveTexture : this.InactiveTexture;
	}
}
