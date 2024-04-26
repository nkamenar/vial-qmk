#pragma once

#ifdef AUDIO_ENABLE

float qwerty_song[][2] = SONG(QWERTY_SOUND);
float colemak_song[][2] = SONG(COLEMAK_SOUND);
float fantasie_impromptu[][2] = SONG(FANTASIE_IMPROMPTU);
float ff_prelude[][2] = SONG(USER_FF_PRELUDE);
float imperial_march[][2] = SONG(USER_IMPERIAL_MARCH);
float coin_sound[][2] = SONG(USER_COIN_SOUND);
float one_up_sound[][2] = SONG(USER_ONE_UP_SOUND);
float zelda_puzzle[][2] = SONG(USER_ZELDA_PUZZLE);
float mario_mushroom[][2] = SONG(USER_MARIO_MUSHROOM);

layer_state_t layer_state_set_user(layer_state_t state) {
    static bool in_gaming_layer = false;
    uint8_t highest_layer = get_highest_layer(state);

    if (highest_layer == _GAMING) {
        if (!in_gaming_layer) {
            PLAY_SONG(zelda_puzzle);
            in_gaming_layer = true;
        }
    } else {
        if (in_gaming_layer) {
            uint8_t defaultLayer = biton32(default_layer_state);
            switch (defaultLayer) {
                case _QWERTY:
                    PLAY_SONG(qwerty_song);
                    break;
                case _COLEMAKDH:
                    PLAY_SONG(colemak_song);
                    break;
            }
            in_gaming_layer = false;
        }
    }

    return state;
}

#endif // AUDIO_ENABLE
