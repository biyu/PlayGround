#ifndef DEMOCLICKABLEOBJECT_H
#define DEMOCLICKABLEOBJECT_H

// clickable interface
class IDemoClickableObject
{
public:
	virtual ~IDemoClickableObject() {}
	virtual void onPressed() = 0;	// click event handler
	virtual void onReleased() = 0;	
	virtual void onHover() = 0;
};

#endif // !DEMOCLICKABLEOBJECT_H
