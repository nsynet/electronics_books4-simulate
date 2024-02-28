#define OPEN LOW
#define CLOSED HIGH
typedef char KeypadEvent;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef struct {
    byte rows;
    byte columns;
} KeypadSize;
#define LIST_MAX 10	
#define MAPSIZE 10
#define makeKeymap(x) ((char*)x)
//class Keypad : public Key, public HAL_obj {
class Keypad : public Key {
public:
	Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols);
	virtual void pin_mode(byte pinNum, byte mode) { pinMode(pinNum, mode); }
	virtual void pin_write(byte pinNum, boolean level) { digitalWrite(pinNum, level); }
	virtual int  pin_read(byte pinNum) { return digitalRead(pinNum); }
	uint bitMap[MAPSIZE];
	Key key[LIST_MAX];
	unsigned long holdTimer;
	char getKey();
	bool getKeys();
	KeyState getState();
	void begin(char *userKeymap);
	bool isPressed(char keyChar);
	void setDebounceTime(uint);
	void setHoldTime(uint);
	void addEventListener(void (*listener)(char));
	int findInList(char keyChar);
	int findInList(int keyCode);
	char waitForKey();
	bool keyStateChanged();
	byte numKeys();
private:
	unsigned long startTime;
	char *keymap;
    byte *rowPins;
    byte *columnPins;
	KeypadSize sizeKpd;
	uint debounceTime;
	uint holdTime;
	void scanKeys();
	bool updateList();
	void nextKeyState(byte n, boolean button);
	void transitionTo(byte n, KeyState nextState);
	void (*keypadEventListener)(char);
};
