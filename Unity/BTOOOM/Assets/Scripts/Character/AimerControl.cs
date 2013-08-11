using UnityEngine;
using System.Collections;

public class AimerControl : MonoBehaviour
{
	public GameObject AimDot;
	public bool Enabled = false;
	public int MaxNumOfDots = 10;
	
	private Vector3[] PathDotsPos;
	private GameObject[] PathDots;
	private Vector3 TargetPosition;
	private Vector3 Velocity;
	
	private void Start ()
	{
		this.PathDotsPos = new Vector3[this.MaxNumOfDots];
		this.PathDots = new GameObject[this.MaxNumOfDots];
	}
	
	private void Update ()
	{
		if (this.Enabled)
		{
			this.UpdatePathDots();
		}
	}
	
	public void SetEnable (bool enable)
	{
		this.Enabled = enable;
	}
	
	public void Aiming(Vector3 Velocity, Vector3 TargetPosition)
	{
		this.Velocity = Velocity;
		this.TargetPosition = TargetPosition;
		this.CalculatePathDots();
	}
	
	private void UpdatePathDots()
	{
		for (int i=0; i<this.MaxNumOfDots; i++)
		{
			if (this.PathDots[i] == null)
			{
				this.PathDots[i] = Instantiate(this.AimDot) as GameObject;
			}
			this.PathDots[i].transform.position = this.PathDotsPos[i];
		}
	}
	
	private void CalculatePathDots()
	{
		float xv = this.Velocity.x;
		float yv = this.Velocity.y;
		float zv = this.Velocity.z;
		// s = v0*t - 0.5*g*t*t
		float dropTime = 2.0f * yv / Mathf.Abs(Physics.gravity.y);
		float intervalTime = dropTime / this.MaxNumOfDots;
		for (int i=0; i<this.MaxNumOfDots; i++)
		{
			float deltaT = intervalTime*(i+1);
			Vector3 predictPoint = this.TargetPosition + new Vector3(xv*deltaT, yv*deltaT-Mathf.Abs(Physics.gravity.y)*deltaT*deltaT/2.0f, zv*deltaT);
			this.PathDotsPos[i] = predictPoint;
		}
	}
	
	public void DestroyPathDots()
	{
		foreach (GameObject obj in this.PathDots)
		{
			Destroy(obj);
		}
	}
}
