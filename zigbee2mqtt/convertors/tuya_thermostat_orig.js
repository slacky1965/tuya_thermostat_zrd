const {identify, reporting, ota} = require('zigbee-herdsman-converters/lib/modernExtend');

const definition = {
    fingerprint: [{modelID: 'TS0601', manufacturerName: '_TZE204_u9bfwha0'},
                  {modelID: 'TS0601', manufacturerName: '_TZE204_aoclfnxz'},
                  {modelID: 'TS0601', manufacturerName: '_TZE204_edl8pz1k'},
                  {modelID: 'TS0601', manufacturerName: '_TZE204_tagezcph'},
                  {modelID: 'TS0601', manufacturerName: '_TZE204_xyugziqv'},
                  {modelID: 'TS0601', manufacturerName: '_TZE204_5toc8efa'},
                  {modelID: 'TS0601', manufacturerName: '_TZE204_lzriup1j'}
                  
                  
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