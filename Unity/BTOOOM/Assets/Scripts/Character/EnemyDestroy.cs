using UnityEngine;
using System.Collections;

public class EnemyDestroy : Destroy
{
	public ParticleSystem VanishEffect;
	public float DelayToDisappear = 2.0f;
	
	protected override IEnumerator DoDestroy()
	{
		this.DoEffect();
		yield return new WaitForSeconds(DelayToDisappear);
		this.DoDisappear();
	}
	
	private void DoEffect()
	{
		ParticleSystem effect = Instantiate(this.VanishEffect, this.transform.position, Quaternion.identity) as ParticleSystem;
		effect.Play();
		Destroy(effect.gameObject, effect.duration + effect.startLifetime + 4.0f);
	}
	
	private void DoDisappear()
	{
		Destroy(this.gameObject);
	}
}
