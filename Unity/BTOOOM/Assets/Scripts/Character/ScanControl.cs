using UnityEngine;
using System.Collections;

public class ScanControl : MonoBehaviour
{
	public float ScanSpeed = 3.0f;
	public float ColorFadeoutSpeed = 1.0f;
	public Vector3 MaxSize = new Vector3(50.0f, 50.0f, 50.0f);
	
	public bool Scanning = false;
	
	// Use this for initialization
	void Start ()
	{
		
	}
	
	// Update is called once per frame
	void Update ()
	{
		this.DoScan();
	}
	
	public void Scan()
	{
		this.Scanning = true;
	}
	
	public void DoScan()
	{
		if (this.Scanning)
		{
			this.transform.localScale = Vector3.Lerp(this.transform.localScale, this.MaxSize, this.ScanSpeed * Time.deltaTime);
			if (Vector3.Distance(this.transform.localScale, this.MaxSize) > 0.3f)
				return;
			if (this.DoFadeOut())
			{
				this.Scanning = false;
				Destroy(this.gameObject, 1.0f);
			}
		}
	}
	
	private bool DoFadeOut()
	{
		this.renderer.material.color = Color.Lerp(this.renderer.material.color, Color.clear, this.ColorFadeoutSpeed * Time.deltaTime);
		if (this.renderer.material.color.a - Color.clear.a < 0.1f)
		{
			return true;
		}
		return false;
	}
	
	private void OnTriggerEnter(Collider other)
	{
		if (other.tag == "Enemy")
		{
			this.StartCoroutine("HighlightFound", other.gameObject);
		}
		
		if (other.tag == "Interactable")
		{
			this.StartCoroutine("TransparentForSeconds", other.gameObject);
		}
	}
	
	private IEnumerator HighlightFound(GameObject found)
	{
		Color colorCache = found.renderer.material.color;
		found.renderer.material.SetColor("_Color", Color.yellow);
		yield return new WaitForSeconds(2);
		found.renderer.material.SetColor("_Color", colorCache);
	}
	
	private IEnumerator TransparentForSeconds(GameObject obj)
	{
		Shader shaderCash = obj.renderer.material.shader;
		obj.renderer.material.shader = Shader.Find("Particles/Additive");
		obj.renderer.material.SetColor("_TintColor", new Color(0.0f, 1.0f, 0.0f, 0.5f));
		yield return new WaitForSeconds(2);
		obj.renderer.material.shader = shaderCash;
	}
}
