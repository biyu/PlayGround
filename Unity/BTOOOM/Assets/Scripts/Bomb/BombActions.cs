using UnityEngine;
using System.Collections;

public class BombActions : MonoBehaviour
{
	public GameObject ExplosionPrefab = null;
	public float ExplosionFinishTime = 5.0f;
	public float ExplosionMaxDamage = 50.0f;
	public float ExplosionRadius = 15.0f;
	
	public bool IsActive = false;
	public GameObject User = null;
	
	// Use this for initialization
	void Start ()
	{
	
	}
	
	// Update is called once per frame
	void Update ()
	{
	
	}
	
	void OnCollisionEnter(Collision collision)
	{
		this.Explode(collision);
	}
	
	public void Active(GameObject user)
	{
		this.User = user;
		this.IsActive = true;
	}
	
	public virtual void OnActive()
	{
		
	}
	
	public void Explode(Collision collision)
	{
		this.DoExplodeEffect();
		this.DoExplodeDamage(collision);
	}
	
	public virtual void DoExplodeEffect()
	{
		if (this.ExplosionPrefab != null)
		{
			GameObject explosionEffectObj = (Instantiate(this.ExplosionPrefab, this.transform.position, this.transform.rotation)) as GameObject;
			Destroy(explosionEffectObj, this.ExplosionFinishTime);
			Destroy(this.gameObject);
		}
	}
	
	public virtual void DoExplodeDamage(Collision collision)
	{
		Vector3 explodeCenter = collision.contacts[0].point;
		Collider[] objInRange = Physics.OverlapSphere(explodeCenter, this.ExplosionRadius);
		foreach(Collider col in objInRange)
		{
			if (col.gameObject == this.gameObject)
				continue;
			HasHealth health = col.gameObject.GetComponent<HasHealth>();
			if (health == null)
				continue;
			int damage = this.CalculateDamage(explodeCenter, col.ClosestPointOnBounds(explodeCenter));
			health.DamageHealth(damage);
		}
	}
	
	private int CalculateDamage(Vector3 center, Vector3 other)
	{
		float distance = Vector3.Distance(center, other);
		float damage = this.ExplosionMaxDamage * (1 - Mathf.Clamp01(distance / this.ExplosionRadius));
		return Mathf.FloorToInt(damage);
	}
}
