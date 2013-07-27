using UnityEngine;
using System.Collections;

public class GameSettings : MonoBehaviour
{
	private void Awake()
	{
		// prevent being destroied when switching between scenes
		DontDestroyOnLoad(this);
	}
	
	public void SaveSettings(/*Savable*/)
	{
		// use PlayerPrefs
		// TODO: make Savable class
	}
}
