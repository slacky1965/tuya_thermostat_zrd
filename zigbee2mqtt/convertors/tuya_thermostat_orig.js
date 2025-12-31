const {identify, reporting, ota} = require('zigbee-herdsman-converters/lib/modernExtend');

const definition = {
    fingerprint: [{manufacturerName: '_TZE204_u9bfwha0'},
                  {manufacturerName: '_TZE204_aoclfnxz'},
                  {manufacturerName: '_TZE200_edl8pz1k'},
                  {manufacturerName: '_TZE204_edl8pz1k'},
                  {manufacturerName: '_TZE204_tagezcph'},
                  {manufacturerName: '_TZE204_xyugziqv'},
                  {manufacturerName: '_TZE204_5toc8efa'},
                  {manufacturerName: '_TZE204_lzriup1j'},
                  {manufacturerName: '_TZE204_oh8y8pv8'},
                  {manufacturerName: '_TZE204_gops3slb'},
                  {manufacturerName: '_TZE284_cvub6xbb'},
                  {manufacturerName: '_TZE204_mpbki2zm'},
                  {manufacturerName: '_TZE200_7rghpoxo'},
                  {manufacturerName: '_TZE204_7rghpoxo'},
                  {manufacturerName: '_TZE204_6a4vxfnv'},
                  {manufacturerName: '_TZE204_szbxmorb'}
                 ],
    zigbeeModel: ['TS0601'],
    model: 'Original Tuya thermostat ready for update',
    vendor: 'Slacky-DIY',
    description: 'Original Tuya thermostat ready for custom Firmware update',
    extend: [
      identify(),
    ],
    meta: {},
    ota: true,
};

module.exports = definition;
