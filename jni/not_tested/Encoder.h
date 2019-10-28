// мини-класс для работы с энкодером, версия 1.0
#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder
{
  public:
    Encoder(int, int, int, bool, bool);
    void tick();
    bool isClick();
    bool isTurn();
    bool isRight();
    bool isLeft();
    bool isRightH();
    bool isLeftH();

  //private:
    int _clk, _dt, _sw;
    bool _type = false;
    bool _state, 
			_lastState, 
			_turnFlag, 
			_swState, 
			_swFlag, 
			_turnState;
    int _encState;
    int _debTimer;
    // 0 - ничего, 1 - лево, 2 - право, 3 - правоНажат, 4 - левоНажат
};
#endif

Encoder::Encoder (int clk, int dt, int sw, bool dir, bool type) {
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
bool Encoder::isTurn() {
  if (_encState > 0 && _encState < 5) {
    return true;
  } else return false;
}
bool Encoder::isRight() {
  if (_encState == 1) {
    _encState = 0;
    return true;
  } else return false;
}
bool Encoder::isLeft() {
  if (_encState == 2) {
    _encState = 0;
    return true;
  } else return false;
}
bool Encoder::isRightH() {
  if (_encState == 3) {
    _encState = 0;
    return true;
  } else return false;
}
bool Encoder::isLeftH() {
  if (_encState == 4) {
    _encState = 0;
    return true;
  } else return false;
}
bool Encoder::isClick() {
  if (_encState == 5) {
    _encState = 0;
    return true;
  } else return false;
}
