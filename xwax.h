#ifndef xwax_h
#define xwax_h

#include "Arduino.h"
#include "WString.h"
extern "C" {
#include "timecoder.h"
}
class xwax
{
   public:
   xwax();
   ~xwax();
   // sampleRate is in Hz, bufferSize is in samples. format can be serato_2a,
   // serato_2b, serato_cd, traktor_a, traktor_b, mixvibes_v2, mixvibes_7inch
  void init(unsigned int sampleRate, unsigned int bufferSize, String format);
	
	// *input is an interlaced 2-channel audio stream, which means it points to
	// an array that contains (bufferSize * 2) elements.
  void update(float* input);

	// when the record is playing forward, the pitch is +1.0
  float getPitch() const;
	
	// velocity is the derivative of position, milliseconds since last update
  float getVelocity() const;
	
	// relative position does not change when you move the needle across the vinyl
  float getRelative() const;
	
	// absolute position knows where on the record you are, avoids sticker drift
  float getAbsolute() const;
	
	// absolute position can not always be read. check to see if it's valid
  bool isAbsoluteValid() const;
	
	// convert a time in milliseconds to an angle in degrees. this value is
	// unbounded, so it may be significantly higher than 360. to wrap it from
	// 0-360, use fmodf(ofxXwax::milliToDegrees(t), 360).
  static float millisToDegrees(float millis);
	
protected:
  struct timecoder timecoder;
  unsigned int sampleRate, bufferSize;
  short shortBuffer[];
  float pitch, velocity, relativePosition, absolutePosition;
  bool absoluteValid;
  String format;
};
#endif
