#ifndef DEMOCLICKABLEOBJECT_H
#define DEMOCLICKABLEOBJECT_H

class IDemoClickableObject
{
public:
	virtual ~IDemoClickableObject() {}
	virtual void onClicked() = 0;	// click event handler

};

#endif // !DEMOCLICKABLEOBJECT_H
