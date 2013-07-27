using UnityEngine;
using System;
using System.Collections;

public class BasicCharacter : MonoBehaviour
{	
	public Attribute[] CharAttributes;
	public BasicCharacterState[] CharBasicStates;
	public BasicSkill[] CharBasicSkills;
	
	public string Name;
	
	// Use this for initialization
	void Start () {
		this.Name = String.Empty;
		// initialize character attributes
		this.CharAttributes = new Attribute[Enum.GetNames(typeof(AttributeName)).Length];
		this.CharBasicStates = new BasicCharacterState[Enum.GetNames(typeof(BasicCharacterStateName)).Length];
		this.CharBasicSkills = new BasicSkill[Enum.GetNames(typeof(BasicSkillName)).Length];
		
		this.InitCharAttributes();
		this.InitCharBasicStates();
		this.InitCharBasicSkills();
		
		this.SetupCharAttributes();
		this.SetupBasicStates();
		this.SetupBasicSkills();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	private void InitCharAttributes()
	{
		for(int i = 0; i < this.CharAttributes.Length; i++)
		{
			this.CharAttributes[i] = new Attribute(Enum.GetName(typeof(AttributeName), (AttributeName)i));
		}
	}
	
	private void InitCharBasicStates()
	{
		for(int i = 0; i < this.CharBasicStates.Length; i++)
		{
			this.CharBasicStates[i] = new BasicCharacterState(Enum.GetName(typeof(BasicCharacterStateName), (BasicCharacterStateName)i));
		}
	}
	
	private void InitCharBasicSkills()
	{
		for(int i = 0; i < this.CharBasicSkills.Length; i++)
		{
			this.CharBasicSkills[i] = new BasicSkill(Enum.GetName(typeof(BasicSkillName), (BasicSkillName)i));
		}
	}
	
	private void SetupCharAttributes()
	{
		// Str
		Attribute str = this.GetCharAttribute(AttributeName.Str);
		str.BasicValue = 10;
		
		// Vit
		Attribute vit = this.GetCharAttribute(AttributeName.Vit);
		vit.BasicValue = 10;
	}
	
	private void SetupBasicStates()
	{
		// health point
		AffectAttribute hpVitAffect = new AffectAttribute() { attr = this.GetCharAttribute(AttributeName.Vit), affectFactor = 10 };
		BasicCharacterState hp = this.GetCharBasicCharacterState(BasicCharacterStateName.MaxHealthPoint);
		hp.AddAffectAttribute(hpVitAffect);
		
		// throw power
		AffectAttribute tpStrAffect = new AffectAttribute() { attr = this.GetCharAttribute(AttributeName.Str), affectFactor = 1 };
		BasicCharacterState tp = this.GetCharBasicCharacterState(BasicCharacterStateName.ThrowPower);
		tp.AddAffectAttribute(tpStrAffect);
		
		// speed
		AffectAttribute spdStrAffect = new AffectAttribute() { attr = this.GetCharAttribute(AttributeName.Str), affectFactor = 2 };
		AffectAttribute spdVitAffect = new AffectAttribute() { attr = this.GetCharAttribute(AttributeName.Vit), affectFactor = -1 };
		BasicCharacterState spd = this.GetCharBasicCharacterState(BasicCharacterStateName.Speed);
		spd.AddAffectAttribute(spdStrAffect);
		spd.AddAffectAttribute(spdVitAffect);
		
		// stamina
		AffectAttribute stmVitAffect = new AffectAttribute() { attr = this.GetCharAttribute(AttributeName.Vit), affectFactor = 1 };
		BasicCharacterState stm = this.GetCharBasicCharacterState(BasicCharacterStateName.Stamina);
		stm.AddAffectAttribute(stmVitAffect);
	}
	
	// TODO: implement this function when needed
	private void SetupBasicSkills()
	{
		
	}
	
	#region Helper Funcs
	
	public Attribute GetCharAttribute(AttributeName name)
	{
		return this.CharAttributes[(int)name];
	}
	
	public BasicCharacterState GetCharBasicCharacterState(BasicCharacterStateName name)
	{
		return this.CharBasicStates[(int)name];
	}
	
	public BasicSkill GetCharBasicSkill(BasicSkillName name)
	{
		return this.CharBasicSkills[(int)name];
	}
	
	#endregion
}
