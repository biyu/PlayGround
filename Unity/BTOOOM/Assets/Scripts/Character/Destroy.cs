using UnityEngine;
using System.Collections;

public class Destroy : MonoBehaviour
{
	public bool Dying = false;
	
	public void Die()
	{
		Dying = true;
		this.StartCoroutine(this.DoDestroy());
	}
	
	protected virtual IEnumerator DoDestroy()
	{
		yield return null;
	}
}
