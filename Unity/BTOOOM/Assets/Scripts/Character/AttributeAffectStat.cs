using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.Linq;	// for Where clause

public class AffectAttribute
{
	public Attribute attr;
	public int affectFactor;
	
	// TODO: add constructor if needed
}

public class AttributeAffectStat
{
	private List<AffectAttribute> AffectAttributes;
	private int _basicValue;
	private string _name;
	
	public int AdjustedValue 
	{
		get 
		{
			return Mathf.Max(0, this.BasicValue + this.CalculateAttributesEffect());
		}
	}
	
	public int BasicValue
	{
		get { return this._basicValue; }
		set { this._basicValue = Mathf.Max(0, value); }
	}
	
	public string Name
	{
		get { return this._name; }
		set { this._name = value; }
	}
	
	public AttributeAffectStat(string name = "")
	{
		this.AffectAttributes = new List<AffectAttribute>();
		this.BasicValue = 0;
		this.Name = name;
	}
	
	public void AddAffectAttribute(AffectAttribute attr)
	{
		this.AffectAttributes.Add(attr);
	}
	
	private int CalculateAttributesEffect()
	{
		int effectValue = 0;
		foreach (AffectAttribute aa in this.AffectAttributes)
		{
			effectValue += aa.attr.AdjustedValue * aa.affectFactor;
		}
		return effectValue;
	}
}
