#ifndef DEMOCLICKABLEOBJECT_H
#define DEMOCLICKABLEOBJECT_H

// clickable interface
class IDemoClickableObject
{
public:
	virtual ~IDemoClickableObject() {}
	virtual void onMousePressed() { this->_isMousePressed = true; }	// click event handler
	virtual void onMouseReleased() { this->_isMousePressed = false; }	
	virtual void onMouseOver() { this->_isMouseOver = true; }
	virtual void onMouseLeft() { this->_isMouseOver = false; }

	bool getMousePressed() const { return this->_isMousePressed; }
	
protected:
	IDemoClickableObject() : _isMouseOver(false), _isMousePressed(false) {}

protected:
	bool _isMousePressed;
	bool _isMouseOver;
};

#endif // !DEMOCLICKABLEOBJECT_H
