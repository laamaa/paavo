#include <string>
#include "inc/AudioEffect.h"
#include "dsp/effect_zitareverb_f32.h"
#include "inc/settings.h"

namespace Paavo
{
    namespace Audio
    {
        template <class T>
        Paavo::Audio::Effect<T>::Effect(String title)
        {
            _title = title;
            _fx = new T;
            this->init();
        }

        template <>
        void Paavo::Audio::Effect<AudioEffectZitaShimmerReverb_F32>::setQuicksetting(uint8_t setting, float val)
        {
            switch (setting)
            {
            //predelay
            case 0:
                constrain(val, 0.0f, 100.0f);
                _fx->getMydsp()->fVslider10 = val; //Predelay
                break;
            //decay
            case 1:
                constrain(val, 0.1f, 10.0f);
                _fx->getMydsp()->fVslider8 = val * (1.0 - _fx->getMydsp()->tone); //low freq rt60
                _fx->getMydsp()->fVslider6 = val;                                 //mid freq rt60
                break;
            //tone
            case 2:
                constrain(val, 0.0f, 1.0f);
                _fx->getMydsp()->tone = val;
                break;
            //shimmer
            case 3:
                constrain(val, -1.0f, 1.0f);
                _fx->getMydsp()->fVslider11 = val; //Shimmer
                break;
            //dry/wet
            case 4:
                constrain(val, -1.0f, 1.0f);
                _fx->getMydsp()->fVslider1 = val; //Output Dry/Wet Mix
                break;
            }
            _quickSettings[setting].setValue(val);
        }

        template <class T>
        Paavo::Audio::EffectQuickSetting *Audio::Effect<T>::getQuickSetting(uint8_t slot)
        {
            return &_quickSettings[slot];
        }

        template <>
        void Paavo::Audio::Effect<AudioEffectZitaShimmerReverb_F32>::init()
        {
            _quickSettings[0] = Paavo::Audio::EffectQuickSetting("Predelay", "ms", 0.0f, 100.0f, 1.0f, 60.0f);
            _quickSettings[1] = Paavo::Audio::EffectQuickSetting("Decay", "s", 0.1f, 16.0f, 0.2f, 8.0f);
            _quickSettings[2] = Paavo::Audio::EffectQuickSetting("Tone", "", 0.0f, 1.0f, 0.1f, 0.5f);
            _quickSettings[3] = Paavo::Audio::EffectQuickSetting("Shimmer", "", 0.0f, 1.0f, 0.1f, 0.5f);
            _quickSettings[4] = Paavo::Audio::EffectQuickSetting("Dry/Wet", "", 0.0f, 1.0f, 0.1f, 0.5f);
        }

        template <class T>
        void Paavo::Audio::Effect<T>::increaseQuicksettingValue(uint8_t setting)
        {
            float newValue = _quickSettings[setting].getValue() + _quickSettings[setting].getInc();
            if (newValue < _quickSettings[setting].getMin())
                newValue = _quickSettings[setting].getMin();
            else if (newValue > _quickSettings[setting].getMax())
                newValue = _quickSettings[setting].getMax();
#if SYNTH_DEBUG > 0
            Serial.printf(F("%s: %.1f %s\n"), _quickSettings[setting].getLabel().c_str(), newValue, _quickSettings[setting].getUnit().c_str());
#endif
            setQuicksetting(setting, newValue);
        }

        template <class T>
        void Paavo::Audio::Effect<T>::decreaseQuicksettingValue(uint8_t setting)
        {
            float newValue = _quickSettings[setting].getValue() - _quickSettings[setting].getInc();
            if (newValue < _quickSettings[setting].getMin())
                newValue = _quickSettings[setting].getMin();
            else if (newValue > _quickSettings[setting].getMax())
                newValue = _quickSettings[setting].getMax();
#if SYNTH_DEBUG > 0
            Serial.printf(F("%s: %.1f %s\n"), _quickSettings[setting].getLabel().c_str(), newValue, _quickSettings[setting].getUnit().c_str());
#endif
            setQuicksetting(setting, newValue);
        }

        template <class T>
        void Paavo::Audio::Effect<T>::addQuickSetting(uint8_t slot, EffectQuickSetting qs)
        {
            _quickSettings[slot] = qs;
        }

        template class Paavo::Audio::Effect<AudioEffectZitaShimmerReverb_F32>;

    } // namespace Audio
} // namespace Paavo