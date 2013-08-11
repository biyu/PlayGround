using UnityEngine;
using System.Collections;

public class Item
{
	private string _name;
	
	public string Name {
		get { return this._name; }
		set { this._name = value; }
	}
	
	public Item(string name = "")
	{
		this.Name = name;
	}
}
