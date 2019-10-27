// мини-класс для работы с энкодером, версия 1.0
#ifndef Encoder_h
#define Encoder_h

class Encoder
{
  public:
    Encoder(uint8_t clk, uint8_t dt, uint8_t sw, boolean dir, boolean type);
    void tick();
    boolean isClick();
    boolean isTurn();
    boolean isRight();
    boolean isLeft();
    boolean isRightH();
    boolean isLeftH();

  //private:
    byte _clk, _dt, _sw;
    boolean _type = false;
    boolean _state, 
			_lastState, 
			_turnFlag, 
			_swState, 
			_swFlag, 
			_turnState;
    byte _encState;
    uint32_t _debTimer;
    // 0 - ничего, 1 - лево, 2 - право, 3 - правоНажат, 4 - левоНажат
};
#endif

Encoder::Encoder (uint8_t clk, uint8_t dt, uint8_t sw, boolean dir, boolean type) {
  if (dir) {
    _clk = clk;
    _dt = dt;
  } else {
    _clk = dt;
    _dt = clk;
  }
  _sw = sw;
  _type = type;
  pinMode (_clk, INPUT);
  pinMode (_dt, INPUT);
  pinMode (_sw, INPUT_PULLUP);
  _lastState = bitRead(PIND, _clk);
}

void Encoder::tick() {
  _encState = 0;
  _state = bitRead(PIND, _clk);
  _swState = bitRead(PIND, _sw);

  if (_state != _lastState) {
    _turnState = true;
    _turnFlag = !_turnFlag;
    if (_turnFlag || !_type) {
      if (bitRead(PIND, _dt) != _lastState) {
        if (_swState) _encState = 1;
        else _encState = 3;
      } else {
        if (_swState) _encState = 2;
        else _encState = 4;
      }
    }
    _lastState = _state;
  }

  if (!_swState && !_swFlag && millis() - _debTimer > 80) {
    _debTimer = millis();
    _swFlag = true;
    _turnState = false;
  }
  if (_swState && _swFlag && millis() - _debTimer > 80) {
    _debTimer = millis();
    _swFlag = false;
    if (!_turnState) _encState = 5;
  }
}
boolean Encoder::isTurn() {
  if (_encState > 0 && _encState < 5) {
    return true;
  } else return false;
}
boolean Encoder::isRight() {
  if (_encState == 1) {
    _encState = 0;
    return true;
  } else return false;
}
boolean Encoder::isLeft() {
  if (_encState == 2) {
    _encState = 0;
    return true;
  } else return false;
}
boolean Encoder::isRightH() {
  if (_encState == 3) {
    _encState = 0;
    return true;
  } else return false;
}
boolean Encoder::isLeftH() {
  if (_encState == 4) {
    _encState = 0;
    return true;
  } else return false;
}
boolean Encoder::isClick() {
  if (_encState == 5) {
    _encState = 0;
    return true;
  } else return false;
}
