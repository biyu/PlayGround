using UnityEngine;
using System.Collections;

public enum BasicSkillName
{
	Scan	// scan enemies in limited range
}

public class BasicSkill : AttributeAffectStat
{
	private bool _known;
	
	public bool Known
	{
		get { return this._known; }
		set { this._known = value; }
	}
	
	public BasicSkill(string name = "")
	{
		this.Known = false;	// by default, character knows nothing	
	}
}
