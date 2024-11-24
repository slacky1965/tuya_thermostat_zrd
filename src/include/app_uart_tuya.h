#ifndef SRC_INCLUDE_APP_UART_TUYA_H_
#define SRC_INCLUDE_APP_UART_TUYA_H_

#define FLAG_START1     0x55
#define FLAG_START2     0xAA
#define SP_VERSION      0x02
#define DATA_MAX_LEN    64          /* do not change!   */

typedef enum {
    MANUF_NAME_0 = 0,
    MANUF_NAME_1,
    MANUF_NAME_MAX
} manuf_name_t;

typedef enum {
    COMMAND00   =   0x00,
    COMMAND01,                      /* Query product information    */
    COMMAND02,                      /* Sync module’s network status */
    COMMAND03,
    COMMAND04,
    COMMAND05,
    COMMAND06,
    COMMAND24   =   0x24,           /* Sync time                    */
} command_t;

typedef enum {
    DP_ID_01    = 0x01,     // on off
    DP_ID_02    = 0x02,     // manual / programming
    DP_ID_03    = 0x03,     // unknown
    DP_ID_10    = 0x10,     // heat setpoint
    DP_ID_13    = 0x13,     // max heat
    DP_ID_18    = 0x18,     // local temperature
    DP_ID_1A    = 0x1A,     // min heat
    DP_ID_1B    = 0x1B,     // calibration
    DP_ID_24    = 0x24,     // unknown
    DP_ID_28    = 0x28,     // lock / unlock keys
    DP_ID_2B    = 0x2B,     // Sensor IN/AL/OU
    DP_ID_65    = 0x65,     // schedule
} dp_id_t;

/* Data Point
 *  Type    Data type   Data length     Description
    0x00    Raw         Custom          Raw data type in hex format, with customizable bytes.
    0x01    Boolean     1               Boolean data type. Valid values include 0x00 and 0x01.
    0x02    Value       4               Value data type, for example, 1, 23, and 104.
    0x03    String      Custom          Custom string.
    0x04    Enum        1               Enum data type, ranging from 0 to 255.
    0x05    Bitmap      1/2/4           Bitmap data type, used to report error codes.
 */

typedef enum {
    DP_RAW = 0,
    DP_BOOL,
    DP_VAL,
    DP_STR,
    DP_ENUM,
    DP_BITMAP
} dp_type_t;

typedef enum {
    STATUS_NET_FREE = 0,
    STATUS_NET_CONNECTED,
    STATUS_NET_ERROR,
    STATUS_NET_IN_PROGRESS,
    STATUS_NET_UNKNOWN
} status_net_t;

typedef enum {
    SENSOR_IN   = 0x00,
    SENSOR_AL   = 0x01,
    SENSOR_OU   = 0x02
} sensor_type_t;

typedef struct __attribute__((packed)) {
    uint8_t  f_start1;
    uint8_t  f_start2;
    uint8_t  pkt_vesion;
    uint16_t seq_num;
    uint8_t  command;
    uint16_t len;
    uint8_t  data[DATA_MAX_LEN];
    uint16_t pkt_len;
} pkt_tuya_t;

typedef struct __attribute__((packed)) {
    uint8_t  dp_id;
    uint8_t  dp_type;
    uint16_t dp_len;
    uint8_t  data[DATA_MAX_LEN-8];
    uint16_t len;
} data_point_t;


typedef struct {
    uint8_t    confirm_need;
    uint8_t    confirm_rec;
    pkt_tuya_t pkt;
} cmd_queue_cell_t;

typedef struct {
    uint8_t cmd_num;
    cmd_queue_cell_t cmd_queue[5];
} cmd_queue_t;

uint8_t checksum(uint8_t *data, uint16_t length);
void uart_cmd_handler();
void set_status_net(status_net_t new_status);
uint16_t get_seq_num();
void set_seq_num(uint16_t f_seq_num);
void set_header_pkt(uint8_t *f_pkt_buff, uint8_t len, uint16_t f_seq_num, uint8_t command);
//uint8_t get_queue_cnt();
void add_cmd_queue(pkt_tuya_t *pkt, uint8_t confirm_need);


#endif /* SRC_INCLUDE_APP_UART_TUYA_H_ */
