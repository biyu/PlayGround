using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

public enum AttributeName
{
	Str,
	Vit
	//	add more here
}

public class Attribute 
{
	private string _name;
	private int _basicValue;
	
	public int AdjustedValue
	{
		get { return this._basicValue; }
	}
	
	public int BasicValue
	{
		get { return this._basicValue; }
		set { this._basicValue = Mathf.Max(0, value); }
	}
	
	public string Name
	{
		get { return this._name; }
		private set { this._name = value; }
	}
	
	public Attribute(string name)
	{
		this.Name = name;
		this._basicValue = 0;
	}
}
