/*------------------------------------------------------------------ VIA CUSTOM SETTINGS ------------------------------------------------------------------*/
/* I've unable to configure this and make it work with VIA, so in the mean time I'll comment this                                                          */
/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include "via.h"
#include "eeconfig.h"

// Single Indicator memory layout
typedef struct _indicator_config_t {
    uint8_t h;
    uint8_t s;
    uint8_t v;
    bool    enabled;
} indicator_config;

// Board memory layout
typedef struct pckey_config_t {
    indicator_config caps;
} pckey_config;

pckey_config pckey;

void eeconfig_init_user(void) {
    // Default values
    pckey.caps.h       = 0;
    pckey.caps.s       = 0;
    pckey.caps.v       = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    pckey.caps.enabled = true;

    // Write default value to EEPROM now
//    eeprom_update_block(&pckey);
    eeconfig_update_kb_datablock(&pckey);
}

enum pckey {
    id_caps_indicator_enabled    = 1,
    id_caps_indicator_brightness = 2,
    id_caps_indicator_color      = 3
};

//On Keyboard startup
void keyboard_post_init_user(void) {
    //Read our custom menu variables from memory
//    eeprom_read_block(&pckey);
//    eeconfig_read_kb_datablock(&pckey);
    eeprom_read_block(&pckey,
                      ( (void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR ),
                      sizeof(pckey) );
}


void pckey_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_indicator_enabled: {
            pckey.caps.enabled = value_data[0];
            break;
        }
        case id_caps_indicator_brightness: {
            pckey.caps.v = value_data[0];
            break;
        }
        case id_caps_indicator_color: {
            pckey.caps.h = value_data[0];
            pckey.caps.s = value_data[1];
            break;
        }
    }
}

void pckey_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_indicator_enabled: {
            value_data[0] = pckey.caps.enabled;
            break;
        }
        case id_caps_indicator_brightness: {
            value_data[0] = pckey.caps.v;
            break;
        }
        case id_caps_indicator_color: {
            //value_data[0] = pckey.caps.h;
            value_data[0] = 128;
            value_data[1] = pckey.caps.s;
            break;
        }
    }
}

void pckey_config_save(void) {
    //aeeconfig_update_kb_datablock(&pckey);
    eeprom_update_block(&pckey,
                        ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR),
                        sizeof(pckey) );
}

void via_custom_value_command_user(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                pckey_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                pckey_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                pckey_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    *command_id = id_unhandled;
}