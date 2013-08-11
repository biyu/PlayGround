using UnityEngine;
using System.Collections;

public class BasicCharacterControl : MonoBehaviour {
	
	public float MoveSpeed = 10.0f;
	public float RotateSpeedH = 5.0f;
	public float RotateSpeedV = 3.0f;
	public float RotateThresholdUpV = -25.0f;
	public float RotateThresholdDownV = 0.0f;
	public bool UseGravity = true;
	public float Gravity = -9.8f;
	public float JumpSpeed = 5.0f;
	public float CollisionForce = 0.5f;
	public float ThrowForce = 15.0f;
	
	public GameObject BombInUse = null;
	public GameObject RightHand = null;
	public Camera ThirdPersonCamera = null;
	// TODO: create inventory
	public GameObject[] AvailableBombs;
	public GameObject Scanner = null;
	
	private CharacterController ccontroller = null;
	private float VerticalVelocity = 0.0f;
	private Animator anim = null;
	private Vector3 MoveVec;
	private float UpDownAngle = 0;
	private BasicSkillPanelManager SkillPanelManager = null;
	private CharacterEditor ceditor = null;
	private AimerControl aimer = null;
	
	// Use this for initialization
	void Start ()
	{
		Screen.lockCursor = false;
		this.ccontroller = this.GetComponent<CharacterController>();
		this.ceditor = this.GetComponent<CharacterEditor>();
		this.anim = this.GetComponent<Animator>();
		this.SkillPanelManager = GameObject.Find("BasicSkillPanel").GetComponent<BasicSkillPanelManager>();
		this.SwitchBomb(0);
		this.aimer = this.GetComponent<AimerControl>();
	}
	
	// Update is called once per frame
	void Update ()
	{
		// pending the player if editor shown
		this.HandleManagementInput();
		if (this.ceditor.Shown) return;
		this.HandleMoveMentInput();
		this.HandleMouse();
		this.UpdateMovement(this.MoveVec);
		this.ApplyGravityForce();
		this.HandleBombSelection();
		this.ActiveScan();
		this.HandleActiveBombAction();
	}
	
	void OnControllerColliderHit(ControllerColliderHit hit)
	{
		if (hit.gameObject.tag == "Interactable"
			&& hit.rigidbody != null)
		{
			Rigidbody target = hit.rigidbody;
			target.AddForce(hit.moveDirection * CollisionForce, ForceMode.Impulse);
		}
		
		if (hit.gameObject.tag == "Bomb")
		{
			BombActions bombAction = hit.gameObject.GetComponent<BombActions>();
			if (bombAction.User != this.gameObject)
			{
				bombAction.Explode(null);
			}
		}
	}
	
	#region Handlers
	
	private void HandleMoveMentInput()
	{
		// move action
		float h = Input.GetAxis("Horizontal");
		float v = Input.GetAxis("Vertical");
		if (h != 0 || v != 0)
		{
			Move(h, v);
			this.anim.SetBool("Run", (v < 0 && h == 0) ? false : true);
			this.anim.SetFloat("Direction", h);
		}
		else 
		{
			this.anim.SetFloat("Direction", 0);
			this.anim.SetBool("Run", false);
		}
		
		// jump action
		if (Input.GetButtonDown("Jump"))
		{
			this.Jump();
		}
	}
	
	private void HandleManagementInput()
	{
		if (Input.GetKeyDown(KeyCode.F1))
		{
			// toggle editor window
			this.ceditor.Shown = !this.ceditor.Shown;
		}
	}
	
	private void HandleBombSelection()
	{
		if (Input.GetKeyDown(KeyCode.Alpha1))
		{
			this.SwitchBomb(0);
		}
		
		if (Input.GetKeyDown(KeyCode.Alpha2))
		{
			this.SwitchBomb(1);
		}
	}
	
	private void HandleActiveBombAction()
	{
		if (Input.GetButtonDown("Fire1"))
		{
			this.anim.SetBool("Targetting", true);
			if (BombInUse.GetComponent<BombActions>() is ImpulsiveBombActions)
			{
				this.aimer.SetEnable(true);
			}
		}
		
		if (Input.GetButton("Fire1"))
		{
			if (BombInUse.GetComponent<BombActions>() is ImpulsiveBombActions)
			{
				Vector3 velocity = this.transform.forward * (this.ThrowForce + Vector3.Dot(this.transform.forward, this.ccontroller.velocity)) + (this.transform.up * -this.UpDownAngle / 2.0f);
				this.aimer.Aiming(velocity, this.RightHand.transform.position);
			}
		}
		
		if (Input.GetButtonUp("Fire1"))
		{
			
			if (BombInUse.GetComponent<BombActions>() is ImpulsiveBombActions)
			{
				ThrowBomb();
				this.aimer.SetEnable(false);
				this.aimer.DestroyPathDots();
			}
			else 
				ActiveBomb();
			anim.SetBool("Targetting", false);
		}
	}
	
	private void HandleMouse()
	{
		float mx = Input.GetAxis("Mouse X");
		float my = Input.GetAxis("Mouse Y");
		
		if (mx != 0) RotateHorizontal(mx * RotateSpeedH);
		if (my != 0) RotateVertical(my * RotateSpeedV);
	}
	
	private void ActiveScan()
	{
		if (Input.GetMouseButtonDown(1))
		{
			this.Scan();
		}
	}
	
	private void ApplyGravityForce()
	{
		this.VerticalVelocity += this.Gravity * Time.deltaTime;
	}
	
	private void UpdateMovement (Vector3 moveVec)
	{
		if (this.ccontroller != null)
		{
			this.ccontroller.Move((moveVec * this.MoveSpeed + Vector3.up * this.VerticalVelocity) * Time.deltaTime);
		}
	}
	
	#endregion
	
	#region Helper Funcs
	
	private Vector3 MousePos2GuiPos(Vector3 mousePos)
	{
		Vector3 guiPos = new Vector3(mousePos.x, Screen.height - mousePos.y, mousePos.z);
		return guiPos;
	}
	
	#endregion
	
	#region Actions

	private void Move(float h, float v)
	{
		this.MoveVec = this.transform.forward * v + this.transform.right * h;
	}
	
	private void RotateHorizontal(float angle)
	{
		this.transform.Rotate(Vector3.up * angle);
	}
	
	private void RotateVertical(float angle)
	{
		this.UpDownAngle -= angle;
		this.UpDownAngle = Mathf.Clamp(this.UpDownAngle, this.RotateThresholdUpV, this.RotateThresholdDownV);
		this.ThirdPersonCamera.transform.localRotation = Quaternion.Euler(Vector3.right * this.UpDownAngle);
	}
	
	private void Jump ()
	{
		// FIXME: isGrounded doesn't work properly
		if (this.ccontroller.isGrounded)
		{
			this.VerticalVelocity = this.JumpSpeed;
		}
	}
	
	private void ThrowBomb()
	{
		GameObject testBomb = ActiveBomb();
//		testBomb.rigidbody.AddForce(
//			this.transform.forward * (this.ThrowForce + Vector3.Dot(this.transform.forward, this.ccontroller.velocity)) + (this.transform.up * -this.UpDownAngle / 2.0f),
//			ForceMode.Impulse);
		testBomb.rigidbody.velocity = this.transform.forward * (this.ThrowForce + Vector3.Dot(this.transform.forward, this.ccontroller.velocity)) + (this.transform.up * -this.UpDownAngle / 2.0f);
	}
	
	private GameObject ActiveBomb()
	{
		GameObject testBomb = Instantiate(this.BombInUse, this.RightHand.transform.position, Quaternion.identity) as GameObject;
		BombActions testBombActions = testBomb.GetComponent<BombActions>();
		testBombActions.Active(this.gameObject);
		return testBomb;
	}
	
	private void SwitchBomb(int index)
	{
		this.SkillPanelManager.SetActiveSkill(index);
		this.BombInUse = this.AvailableBombs[index];
	}
	
	private void Scan()
	{
		GameObject scanner = Instantiate(this.Scanner, this.RightHand.transform.position, Quaternion.identity) as GameObject;
		ScanControl scanCtrl = scanner.GetComponent<ScanControl>();
		scanCtrl.Scan();
	}
	
	#endregion
}
