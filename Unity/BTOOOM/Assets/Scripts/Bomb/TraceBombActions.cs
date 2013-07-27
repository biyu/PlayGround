using UnityEngine;
using System.Collections;

public class TraceBombActions : BombActions
{
	public enum ActiveState 
	{
		Init,
		Trace,
		Attack
	}
	
	public float InitRaiseDistance = 3.0f;
	public float InitRaiseSpeed = 1.0f;
	public float AttackSpeed = 4.0f;
	public float TraceRadius = 20.0f;
	public float TraceMoveSpeed = 1.0f;
	public ActiveState CurrentState = ActiveState.Init;
	
//	private CapsuleCollider DetectCollider = null;
	private Vector3 InitialPos;
	private GameObject FoundTarget = null;
	private Vector3 NextTracePoint;
	
	// Use this for initialization
	void Start () {
		this.InitialPos = this.transform.position + Vector3.up * this.InitRaiseDistance;
//		this.DetectCollider = this.GetComponent<CapsuleCollider>();
		this.NextTracePoint = this.InitialPos;
	}
	
	// Update is called once per frame
	void Update () {
		if (this.IsActive)
			this.OnActive();
//		Debug.Log("Current State: " + this.CurrentState.ToString());
	}
	
	void OnTriggerStay(Collider other) 
	{
		if (this.CurrentState == ActiveState.Trace
			&& other.gameObject != this.User
			&& other.gameObject != GameObject.Find("Ground")
			&& other.gameObject.tag != "Bomb")
		{
			this.FoundTarget = other.gameObject;
			this.CurrentState = ActiveState.Attack;	
		}
	}
	
//	use Physics.OverlapSphere
	
	void OnTriggerExit(Collider other)
	{
		this.InitialPos.Set(this.transform.position.x, this.InitialPos.y, this.transform.position.z);
		this.CurrentState = ActiveState.Init;	
	}
	
	public override void OnActive ()
	{
		if (this.CurrentState == ActiveState.Init)
		{
			this.OnInit();
		}
		if (this.CurrentState == ActiveState.Trace)
		{
			this.OnTrace();
		}
		if (this.CurrentState == ActiveState.Attack)
		{
			this.OnAttack();
		}
	}
	
	private void OnInit()
	{
		if (Vector3.Distance(this.transform.position, this.InitialPos) > 0.3f)
		{
			this.transform.position = Vector3.Lerp(this.transform.position, this.InitialPos, Time.deltaTime * this.InitRaiseSpeed);
			return;
		}
		this.CurrentState = ActiveState.Trace;
	}
	
	private void OnTrace()
	{
		if (Vector3.Distance(this.transform.position, this.NextTracePoint) > 0.3f)
		{
			Vector3 targetDirection = this.NextTracePoint - this.transform.position;
			Quaternion targetRotation = Quaternion.LookRotation(targetDirection, Vector3.up);
			Quaternion newRotation = Quaternion.Lerp(this.rigidbody.rotation, targetRotation, this.TraceMoveSpeed * Time.deltaTime);
			this.rigidbody.MoveRotation(newRotation);
			this.rigidbody.MovePosition(this.rigidbody.position + this.transform.forward * this.TraceMoveSpeed * Time.deltaTime);
			return;
		}
		this.NextTracePoint = this.GenerateNextTracePoint();
	}
	
	private Vector3 GenerateNextTracePoint()
	{
		Vector3 nextPoint = this.transform.position 
			+ new Vector3(Random.Range(-this.TraceRadius, this.TraceRadius), 0, Random.Range(-this.TraceRadius, this.TraceRadius));
//		Debug.Log("nextpoint: " + nextPoint);
		return nextPoint;
	}
	
	private void OnAttack()
	{
		if (this.FoundTarget != null)
		{
			this.transform.position = Vector3.Lerp(this.transform.position, this.FoundTarget.transform.position, Time.deltaTime * this.AttackSpeed);
		}
	}
}
