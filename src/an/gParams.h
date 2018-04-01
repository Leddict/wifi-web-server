#ifndef __AN__G_PARAMS_H__
#define __AN__G_PARAMS_H__

#include "jsonCommon.h"
#include <FastLED.h>

class AnimationsGlobalParams : public ObjectFromJsonIfc {

public:

  AnimationsGlobalParams(uint16_t maxPixels)
    :
    m_maxPixels(maxPixels), m_numOfPixels(maxPixels), m_leadingColor(0, 0, 255)
  {

  }

  const uint16_t m_maxPixels;
  uint16_t m_numOfPixels;

  CHSV m_leadingColor;

public:

  bool setFromJson(const JsonObject &root) {
    if(validateJson(root) == false) {
      return false;
    }

    colorConvertor.parseColorFromJson(root["leadingColor"], &this->m_leadingColor);
    Serial.println(String("leadingColor = "));

    m_numOfPixels = root["numOfPixels"].as<uint16_t>();
    Serial.println(String("numOfPixels = ") + m_numOfPixels);

    return true;
  }

  bool validateJson(const JsonObject &root) {

    const JsonVariant leadingColor = root["leadingColor"];
    bool leadingColorSuccess = colorConvertor.parseColorFromJson(leadingColor, NULL);
    if(!leadingColorSuccess) {
      Serial.println("leadingColor is not a valid format");
      return false;
    }

    const JsonVariant numOfPixels = root["numOfPixels"];
    if(!numOfPixels.is<uint16_t>()) {
      Serial.println("GlobalParams::validateJson: numOfPixels is not uint16_t");
      return false;
    }
    double nop = numOfPixels.as<uint16_t>();
    if(nop > m_maxPixels) {
      Serial.println(String("GlobalParams::validateJson: numOfPixels is larger than max allowed pixels [") + m_maxPixels + "]");
      return false;
    }

    return true;
  }


};

#endif // __AN__G_PARAMS_H__
