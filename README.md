
# <a id="Top">Tuya Thermostat for Floor Heating Zigbee with custom firmware</a>

### [Описание на русском](README_rus.md)

### Custom firmware for Tuya thermostat models

1. Model r01
	- "[_TZE204_u9bfwha0](doc/thermostats/tuya_thermostat_r01/README.md)"
	- "[_TZE204_aoclfnxz](doc/thermostats/tuya_thermostat_r01/README.md)"
2. Model r02
	- ["_TZE200_edl8pz1k"](doc/thermostats/tuya_thermostat_r02/README.md)
	- ["_TZE204_edl8pz1k"](doc/thermostats/tuya_thermostat_r02/README.md)
3. Model r03	
	- ["_TZE204_tagezcph"](doc/thermostats/tuya_thermostat_r03/README.md)
4. Model r04	
	- ["_TZE204_xyugziqv"](doc/thermostats/tuya_thermostat_r04/README.md)
5. Model r05
	- ["_TZE204_5toc8efa"](doc/thermostats/tuya_thermostat_r05/README.md)
6. Model r06
	- ["_TZE204_lzriup1j"](doc/thermostats/tuya_thermostat_r06/README.md)
	- ["_TZE204_oh8y8pv8"](doc/thermostats/tuya_thermostat_r06/README.md)
	- ["_TZE204_gops3slb"](doc/thermostats/tuya_thermostat_r06/README.md)
	- ["_TZE284_cvub6xbb"](doc/thermostats/tuya_thermostat_r06/README.md)
7. Model r07
	- ["_TZE204_mpbki2zm"](doc/thermostats/tuya_thermostat_r07/README.md)
8. Model r08
	- ["_TZE204_7rghpoxo"](doc/thermostats/tuya_thermostat_r08/README.md)
	- ["_TZE200_7rghpoxo"](doc/thermostats/tuya_thermostat_r08/README.md)
9. Model r09
	- ["_TZE204_6a4vxfnv"](doc/thermostats/tuya_thermostat_r09/README.md)
9. Model r0A
	- ["_TZE284_xalsoe3m"](doc/thermostats/tuya_thermostat_r0a/README.md)
10. Model r0B
	- ["_TZE204_8byfmxdv"](doc/thermostats/tuya_thermostat_r0b/README.md)
11. Model r0C
	- ["_TZE204_szbxmorb"](doc/thermostats/tuya_thermostat_r0c/README.md)

<img src="doc/images/model1.png"/>
<img src="doc/images/model1_2.png"/>
<img src="doc/images/model3_1.png"/>
<img src="doc/images/model3_2.png"/>
<img src="doc/images/model4.png"/>
<img src="doc/images/model5.png"/>
<img src="doc/images/model6.png"/>
<img src="doc/images/model7.png"/>
<img src="doc/images/model8.png"/>
<img src="doc/images/model9.png"/>
<img src="doc/images/model0b.png"/>

**The author assumes no responsibility if you turn your smart thermostat into a half-witted thermostat by using this project.**

Only the thermostats listed above were checked. If you have a different signature,  it is better not to flash without checking for a datapoint match.

**Theoretically, the firmware can be adapted for any thermostat with IEEE beginning with**

**`A4 C1 38`**

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/device_ieee.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/about_ieee.jpg"/>

**If the IEEE start is different from the specified one, then the thermostat has a different chip in the Zigbee module, you can't use this project.**

Only tested in `zigbee2mqtt`. As of April 2025 version of `zigbee2mqtt` no external converter is needed. Support is enabled globally.

## Why. 

To keep it from spamming the network. The first instance (see above) sent 25 packets every 8 seconds.

## Result. 

**About**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_about.jpg"/>

**Exposes**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_exposes.jpg"/>

**Reporting**
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_reporting.jpg"/>


## How to update.

First, add external [converter](https://github.com/slacky1965/tuya_thermostat_zrd/tree/main/zigbee2mqtt/convertors) `tuya_thermostat_orig.js` to z2m. He activates OTA in z2m for thermostat with Tuya firmware. Put the converter in the directory ` external_converters` , which should be created in the root of z2m.

Next, you need to add a local update repository. 

Create a directory` images` in the z2m directory and put the file [1141-d3a3-1111114b-tuya_thermostat_zrd.zigbee](https://github.com/slacky1965/tuya_thermostat_zrd/raw/refs/heads/main/bin/1141-d3a3-1111114b-tuya_thermostat_zrd.zigbee) there.

Copy the file [local_ota_index.json](https://github.com/slacky1965/tuya_thermostat_zrd/raw/refs/heads/main/zigbee2mqtt/local_ota_index.json) to the z2m directory.

And add local storage to the z2m config (configuration.yaml)

```
ota:
  zigbee_ota_override_index_location: local_ota_index.json
```

Then reboot z2m and see a new device (if the thermostat was already in the network and visible in z2m).

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_1.jpg"/>

Then go to the OTA section. And see your device there. Click check for updates.
<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_1.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_2.jpg"/>

Hit the red button. And update.

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_3.jpg"/>

If the result is not as described, it means you did something wrong (did not put the file where it should be, did not reboot z2m) or your thermostat signature is not in the list of supported devices.

> [!WARNING]
> Attention!!! If in the process you find a new updateon other Tuya devices that you may still have in your system, you do not need to update anything!!!! Otherwise you will flash into this device firmware from the thermostat and get a brick!!!! If the update process has already started by mistake, just turn off the device!!!!

Then wait for it to finish. After that we see our thermostat in OTA with the old name but with the new` Firmware build date` and` Firmware version .`

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_4.jpg"/>

This is what the log looks like on the first startup after upgrading from Tuya to custom firmware.

```
OTA mode enabled. MCU boot from address: 0x8000
Firmware version: v1.0.04
Tuya bootloader
Bootloader is overwritten. Reset
OTA mode enabled. MCU boot from address: 0x8000
Firmware version: v1.0.04
SDK bootloader
out_pkt <== 0x55AA0200010101000003
inp_pkt ==> 0x55AA02000101001C7B2270223A2265646C38707A316B222C2276223A22312E302E30227D8D
Tuya signature found: "edl8pz1k".
Use modelId: Tuya_Thermostat_r02
```

Next, go to the `Devices` section and click on our thermostat on the right side with the symbol "i" and confirm. In this way we force the device to go through the interview again.

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_int_1.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_int_1.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_int_2.jpg"/>

Then click the <img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_recfg.jpg"/> symbol again on the right side. This forces the device to go through the configuration again.

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_recfg_1.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_recfg_2.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/z2m_tuya_update_recfg_3.jpg"/>

That's it, the thermostat is ready to go.

> [!WARNING]
> Attention!!! If the thermostat remains with the old name after a successful update and all the above instructions have been followed, remove it from the network, reboot z2m and pair it again. If during the pairing process the thermostat blinks with the network icon but nothing happens, remove power from the thermostat (unplug it from electricity) and re-power it.

In Home Assistant, it looks like this

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/HA_3.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/HA_1.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/HA_2.jpg"/>

## How to write a new firmware version into an already updated thermostat.

All updates will be available via z2m as new releases are released, you don't need to do anything specifically for this.

That's it!

P.S. Not tested in real work, requires extensive testing.

A more detailed description for the very first thermostat [here](https://habr.com/ru/articles/864740)

---

You can contact me at **[Telegram](https://t.me/slacky1965)**.

### If you would like to thank the author, you can do so via [YouMoney](https://yoomoney.ru/to/4100118300223495).

---

Thanks :))))

- [@ruslikx3m](https://t.me/ruslikx3m) for the first provided thermostat `_TZE204_u9bfwha0` to tear apart.

- [@immortal_serg](https://t.me/immortal_serg) for providing the thermostat `_TZE204_edl8pz1k`.

- [@chernyshevruslan](https://t.me/chernyshevruslan) for providing the thermostats `_TZE204_tagezcph` in two different versions and `_TZE204_xyugziqv`.

- [@Alleol](https://t.me/Alleol) for providing the thermostat `_TZE204_lzriup1j`.

- [@terekhins](https://t.me/terekhins) for providing the `_TZE204_aoclfnxz` thermostat made by `MOES`.

- [@shadow_by](https://t.me/shadow_by) for providing the `_TZE204_aoclfnxz` thermostat made by `MOES`.

- [@dbunevich](https://t.me/dbunevich) for providing the thermostat `_TZE204_mpbki2zm`.

- [@liberatemei](https://t.me/liberatemei) for providing the thermostat `_TZE204_oh8y8pv8`.

- [@rheinx](https://t.me/rheinx) for providing the thermostat `_TZE204_6a4vxfnv`

- [@Nobodevi4](https://t.me/Nobodevi4) for providing the thermostat `_TZE284_cvub6xbb`

- [https://github.com/doctor64](https://github.com/doctor64) [@doctor_64](https://t.me/doctor_64) - for always wanting to help and point me in the right direction.

- [https://github.com/devbis](https://github.com/devbis) [@Belokobylskiy](https://t.me/Belokobylskiy) - for ideas and writing scripts in Python and for the z2m converter.

- [@goofyk](https://t.me/goofyk) - for patience and for knowing z2m well.

- [https://github.com/pvvx](https://github.com/pvvx) - for a wonderful programmer for Telink chips.

## Version History
- 1.0.01
	- Initial version.
- 1.0.02
	- Release. Removed due to an issue with the OTA update.
- 1.0.03
	- Fixed an issue with being able to set the heating temperature above the threshold set in maxHeatSetpoint. 
	- Corrected the converter for thermostat wiring in Home Assistant. 
	- Added callback functions of remote commands to DataPoints structure. 
	- Tested thermostat with signature `_TZE204_aoclfnxz`. Fixed problem with OTA update.
- 1.0.03a
	- PreRelease.
- 1.0.04
	- Added a thermostat with the signature `_TZE204_edl8pz1k`. 
	- Added callback functions of local commands to DataPoints structure.
	- Added `watchdog`.
	- The formation of zb_modelId has been changed. 
		> When upgrading to custom firmware, thermostats with different signatures, but which are essentially the same device, will now receive the same group name, regardless of signature.
	- Changed z2m covetors, now it's just two files. 
		> One for the thermostat with original firmware, one for the thermostat with custom firmware. There is no need to change anything in them.
- 1.0.05
	- Added thermostat with signature `_TZE204_tagezcph`
		> Checked two thermostats, one with the rotary knob down the middle, the other down the right side.
	- Edited the internal variable names associated with the model number.
		> It used to count from 0. Now it counts from 1. It's just for convenience, so that you don't get confused. For example, it used to be type0, now it is type1, etc.
	- Converters have been updated.
- 1.0.06
	- Added thermostat with signature `_TZE204_xyugziqv`
	- Increased uart buffer to 512 bytes. The last thermostat sends a lot of packets at one time.
	- Converters updated
- 1.0.07
	- Fixed a problem with the number of running timers. In z2m everything worked, but in ZHA it was overloading.
- 1.0.08
	- Updated SDK to version [V3.7.1.2](https://github.com/telink-semi/telink_zigbee_sdk/releases/tag/V3.7.1.2)
	- Updated `local_ota_index.js` - explicitly specifies devices to be updated.
	- The upgrade instructions have been changed - at the end you do not need to uninstall the device, just go through the interview and configuration procedures again.
- 1.0.09
	- Fixed a bug with saving settings and then restoring them when power is applied.
	- Added `watchdog` clearing to uart operation. This situation could happen - ZTU MCU was rebooted when MCU did not answer for a long time.
	- Converters for `zigbee2mqtt` 2.0.0 version have been updated
	- Updated instructions.
- 1.0.10
	- Added thermostat with signature `_TZE204_5toc8efa` from BSEED (GL86HTEZ1B).
	- The converters and the local update download file have been updated.
	- Updated instructions.
- 1.0.11
	- Added thermostat with signature `_TZE204_lzriup1j` manufactured by Avatto (ZWT10016A).
	- Added autodetection of `UART` speed. According to [Tuya Zigbee Serial protocol](https://developer.tuya.com/en/docs/mcu-standard-protocol/mcusdk-zigbee-uart-protocol?id=Kdg17v4544p37) standard, the speed can be `9600` or `115200`.
	- Added to the converter for z2m to display the schedule already available in the thermostat.
	- The converters and the local update download file have been updated.
	- Updated instructions.
- 1.0.12
	- A thermostat with signature `_TZE204_aoclfnxz` manufactured by `MOES` was physically tested. Based on the results, the code for processing incoming and outgoing packets in ` uart` was modified.
	- The `_TZE200_edl8pz1k` signature was added to the converters.
	- Added `System Mode` parameter to the data saved and restored at startup. When resetting the module, this parameter was set to 0, which was perceived by remote systems as if the thermostat was turned off.
- 1.0.13
	- Added thermostat with signature `_TZE204_mpbki2zm`.
- 1.0.14
	- Added a thermostat with the signature `_TZE204_7rghpoxo`.
	- Converters have been updated.
- 1.0.15
	- The outgoing packet queue has been changed. It is now an adapted ring buffer.
	- Enabled chip supply voltage check to eliminate errors when writing to flash memory when the voltage is less than 2.2 volts. Relevant in case of power failure.
	- Added timeouts for outgoing packets.
	- Reduced the number of outgoing identical responses for thermostats `_TZE204_edl8pz1k` and `_TZE204_aoclfnxz`, otherwise the program was often overloaded by watchdog.
	- The code for checking and overwriting `bootloader` has been removed from the main firmware - it was a potential threat of boot sector corruption under certain circumstances. This code is now only contained in the firmware that is loaded on the first update.
	- At the first update, the version number will always be `1.0.00` - done specially for the fastest update to the main firmware, where there is no code to check and overwrite `bootloader`.
	- Added a thermostat with the signature `_TZE200_7rghpoxo`. I have not checked it, added based on the words of a user who checked it.
	- Converters have been updated.
- 1.0.16
	- Added a thermostat with the signature `_TZE204_oh8y8pv8`.
- 1.0.17
	- Added thermostat with signature `_TZE204_gops3slb` (not tested, see [issue](https://github.com/slacky1965/tuya_thermostat_zrd/issues/124)).
	- Added thermostat with signature `_TZE204_6a4vxfnv`.
	- Fixed SDK bug with reporting.
- 1.0.18
	- Added thermostat with signature `_TZE284_cvub6xbb`.
- 1.0.19
	- Added thermostat with signature `_TZE284_xalsoe3m`.
	- Added thermostat with signature `_TZE204_8byfmxdv`.
	- Modified `Factory Reset` procedure.
	- Added the ability to change the thermostat's `ZigBee model` via the `mqtt` topic.
- 1.0.20
	- Added thermostat with signature `_TZE204_szbxmorb`.
	- Fixed a bug with the schedule divider.
- 1.0.21
	- Fixed error of enabling programming mode for Model r07 `_TZE204_mpbki2zm`.
	
[Top](#Top)



