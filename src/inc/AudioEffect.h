#ifndef AUDIOEFFECT_H_
#define AUDIOEFFECT_H_

#include <string>
#include "AudioStream_F32.h"

namespace Paavo
{
    namespace Audio
    {

        class EffectQuickSetting
        {
        public:
            EffectQuickSetting(String label = "", String unit = "", float min = 0, float max = 0, float inc = 1.0f, float value = 0.0f)
            {
                _label = label;
                _unit = unit;
                _min = min;
                _max = max;
                _inc = 1.0f;
                _value = value;
            }

            inline String getLabel() { return _label; }
            inline String getUnit() { return _unit; }
            inline float getValue() { return _value; }

        private:
            String _label = "";
            String _unit = "";
            float _min = 0;
            float _max = 0;
            float _inc = 1.0f;
            float _value = 0;
        };

        class EffectMeta
        {
        public:
            EffectMeta(AudioStream_F32 *fx, String title)
            {
                _fx = fx;
                _title = title;
            }
            ~EffectMeta()
            {
                delete this;
            }

            String getTitle() { return _title; }

            void addQuickSetting(uint8_t slot, EffectQuickSetting qs)
            {
                _quickSettings[slot] = qs;
            }

            EffectQuickSetting getQuickSetting(uint8_t slot) { return _quickSettings[slot]; }

            ::AudioStream_F32 &getAudioStreamObject() { return *_fx; }

        private:
            AudioStream_F32 *_fx;
            AudioConnection_F32 *patch[2];
            String _title;
            bool _enabled;
            EffectQuickSetting _quickSettings[5];
        };
    } // namespace Audio
} // namespace Paavo

#endif