using UnityEngine;
using System.Collections;

public class BoxDestroy : Destroy
{
	public GameObject DestroyedBox;
	public float MinExplodeForce = 50.0f;
	public float MaxExplodeForce = 100.0f;
	public float ExplodeRange = 100.0f;
	
	protected override IEnumerator DoDestroy()
	{
		GameObject destroyedBoxPref = Instantiate(this.DestroyedBox, this.transform.position, Quaternion.identity) as GameObject;
		this.DoExplosionEffect(destroyedBoxPref);
		// destroy broken box after 5 seconds
		Destroy(destroyedBoxPref, 5.0f);
		// destroy original box immediately
		Destroy(this.gameObject);
		yield return null;
	}
	
	private void DoExplosionEffect(GameObject brokenObj)
	{
		Vector3 explodePos = brokenObj.transform.position;
		Rigidbody[] brokenPieces = brokenObj.GetComponentsInChildren<Rigidbody>();
		foreach(Rigidbody piece in brokenPieces)
		{
			float rndForce = Random.Range(this.MinExplodeForce, this.MaxExplodeForce);
//			Debug.Log(piece.gameObject.name + ": " + rndForce);
			piece.AddExplosionForce(rndForce, explodePos, this.ExplodeRange);
		}
	}
}
