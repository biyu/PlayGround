using UnityEngine;
using System.Collections;

public class HasHealth : MonoBehaviour
{
	public int MaxHealth = 100;
	public int CurrentHealth = 100;
	public bool ShowHealthBar = true;
	public bool HasHealthBar = true;
	
	public int HealthBarWidth = 100;
	public int HealthBarHeight = 20;
	public float HealthBarXOffset = -58;
	public float HealthBarYOffset = -145;
	
	private Destroy DestroyEffect = null;
	
	private void Start()
	{
		this.DestroyEffect = this.GetComponent<Destroy>();
	}
	
	public void AddHealth(int amount)
	{
		this.CurrentHealth = Mathf.Min(this.MaxHealth, this.CurrentHealth + amount);
	}
	
	public void DamageHealth(int amount)
	{
		this.CurrentHealth = Mathf.Max(0, this.CurrentHealth - amount);
	}
	
	void Update ()
	{
		Vector3 vpPoint = Camera.main.WorldToViewportPoint(this.gameObject.transform.position);
		if (vpPoint.x > 0.0f && vpPoint.x < 1.0f && vpPoint.z > 0.0f)
			this.ShowHealthBar = true;
		else 
			this.ShowHealthBar = false;
		if (CurrentHealth <= 0 && this.DestroyEffect != null && !this.DestroyEffect.Dying)
		{
			this.DestroyEffect.Die();
		}
	}
	
	private void OnGUI()
	{
		if (this.ShowHealthBar)
		{
			Vector3 onScreenPoint = Camera.main.WorldToScreenPoint(this.gameObject.transform.position);
			HasHealth health = this.gameObject.GetComponent<HasHealth>();
			GUI.Box(
				new Rect(onScreenPoint.x + HealthBarXOffset, Screen.height - onScreenPoint.y + HealthBarYOffset, this.HealthBarWidth, this.HealthBarHeight),
				health.CurrentHealth + " / " + health.MaxHealth
				);
		}
	}
}
