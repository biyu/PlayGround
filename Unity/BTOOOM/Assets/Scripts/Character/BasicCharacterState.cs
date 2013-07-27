using UnityEngine;
using System.Collections;

public enum BasicCharacterStateName 
{
	MaxHealthPoint,
	ThrowPower,
	Speed, // rush speed
	Stamina	// for character rush
}

public class BasicCharacterState : AttributeAffectStat
{
	private int _currentValue;
	
	public int CurrentValue
	{
		get
		{
			if (this._currentValue > this.AdjustedValue)
			{
				this._currentValue = this.AdjustedValue;
			}
			return this._currentValue;
		}
		set { this._currentValue = value; }
	}
	
	public BasicCharacterState(string name = "")
		: base(name)
	{
		// by default, the current value for basic character state equals to AdjustedValue
		// e.g. by default, current HP value equals to Max HP value
		this.CurrentValue = this.AdjustedValue;
	}
}
