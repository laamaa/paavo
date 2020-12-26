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
                _inc = inc;
                _value = value;
            }

            inline String getLabel() { return _label; }
            inline String getUnit() { return _unit; }
            inline float getValue() { return _value; }
            inline float getInc() { return _inc; }
            inline float getMin() { return _min; }
            inline float getMax() { return _max; }
            inline void setValue(float value)
            {
                constrain(value, _min, _max);
                _value = value;
            }

        private:
            String _label = "";
            String _unit = "";
            float _min = 0;
            float _max = 0;
            float _inc = 1.0f;
            float _value = 0;
        };

        class EffectBase
        {
        public:
            virtual AudioStream_F32 *getFx();
            virtual String getTitle();
            virtual Paavo::Audio::EffectQuickSetting *getQuickSetting(uint8_t slot);
            virtual void init();
            virtual void increaseQuicksettingValue(uint8_t setting);
            virtual void decreaseQuicksettingValue(uint8_t setting);
        };

        template <class T>
        class Effect : public EffectBase
        {
        public:
            Effect(String title);
            ~Effect();
            void addQuickSetting(uint8_t slot, EffectQuickSetting qs);
            void setQuicksetting(uint8_t setting, float val);
            Paavo::Audio::EffectQuickSetting *getQuickSetting(uint8_t slot);
            void increaseQuicksettingValue(uint8_t setting);
            void decreaseQuicksettingValue(uint8_t setting);
            String getTitle() { return _title; }
            void init();
            ::AudioStream_F32 *getFx() { return _fx; }

        private:
            EffectQuickSetting _quickSettings[5];
            String _title;
            T *_fx;
        };

    } // namespace Audio
} // namespace Paavo

#endif