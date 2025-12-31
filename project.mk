# Add inputs and outputs from these tool invocations to the build variables
OUT_DIR += \
/$(SRC_PATH) \
/$(SRC_PATH)/zcl \
/$(SRC_PATH)/common
 
OBJS += \
$(OUT_PATH)/$(SRC_PATH)/common/main.o \
$(OUT_PATH)/$(SRC_PATH)/zcl/zcl_thermostat_ui_cfg.o \
$(OUT_PATH)/$(SRC_PATH)/zcl/zcl_app_thermostat.o \
$(OUT_PATH)/$(SRC_PATH)/zcl/zcl_app_fancontrol.o \
$(OUT_PATH)/$(SRC_PATH)/zcl/zcl_relative_humidity_measurement.o \
$(OUT_PATH)/$(SRC_PATH)/zcl/zcl_reporting.o \
$(OUT_PATH)/$(SRC_PATH)/app_tuya_datapoint.o \
$(OUT_PATH)/$(SRC_PATH)/app_uart_tuya.o \
$(OUT_PATH)/$(SRC_PATH)/app_uart.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model1.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model2.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model3.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model4.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model5.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model6.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model7.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model8.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model9.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model0a.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model0b.o \
$(OUT_PATH)/$(SRC_PATH)/app_thermostat_model0c.o \
$(OUT_PATH)/$(SRC_PATH)/app_endpoint_cfg.o \
$(OUT_PATH)/$(SRC_PATH)/app_utility.o \
$(OUT_PATH)/$(SRC_PATH)/app_time.o \
$(OUT_PATH)/$(SRC_PATH)/app_bootloader.o \
$(OUT_PATH)/$(SRC_PATH)/app_main.o \
$(OUT_PATH)/$(SRC_PATH)/zb_appCb.o \
$(OUT_PATH)/$(SRC_PATH)/zcl_appCb.o

#$(OUT_PATH)/$(SRC_PATH)/app_button.o \
#$(OUT_PATH)/$(SRC_PATH)/app_light.o \
#$(OUT_PATH)/$(SRC_PATH)/app_reporting.o \


# Each subdirectory must supply rules for building sources it contributes
$(OUT_PATH)/$(SRC_PATH)/%.o: $(SRC_PATH)/%.c 
	@echo 'Building file: $<'
	@$(CC) $(GCC_FLAGS) $(INCLUDE_PATHS) -c -o"$@" "$<"


