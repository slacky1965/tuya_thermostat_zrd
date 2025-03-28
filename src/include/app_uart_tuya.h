#ifndef SRC_INCLUDE_APP_UART_TUYA_H_
#define SRC_INCLUDE_APP_UART_TUYA_H_

#define FLAG_START1         0x55
#define FLAG_START2         0xAA
#define SP_VERSION          0x02
#define DATA_MAX_LEN        64          /* do not change!   */


#define RING_CMD_QUEUE_CELL_SIZE    16                          /* size ring buffer  */
#define RING_CMD_QUEUE_CELL_MASK    RING_CMD_QUEUE_CELL_SIZE-1  /* mask ring buffer  */


//#define CMD_QUEUE_CELL_MAX  32

typedef enum {
    COMMAND00   =   0x00,
    COMMAND01,                      /* Query product information    */
    COMMAND02,                      /* Sync module’s network status */
    COMMAND03,
    COMMAND04,
    COMMAND05,
    COMMAND06,
    COMMAND20   =   0x20,           /* Query module’s network status*/
    COMMAND24   =   0x24,           /* Sync time                    */
    COMMAND28   =   0x28,           /* Query DP data                */
    COMMANDXX   =   0xFF,           /* For test                     */
} command_t;


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

typedef struct {
    uint8_t    used;
    uint8_t    confirm_need;
    uint8_t    confirm_rec;
    pkt_tuya_t pkt;
} cmd_queue_cell_t;

extern bool first_start;
extern char8_t signature[9];

uint8_t checksum(uint8_t *data, uint16_t length);
void uart_cmd_handler();
void set_status_net(status_net_t new_status);
uint16_t get_seq_num();
void set_seq_num(uint16_t f_seq_num);
void set_header_pkt(uint8_t *f_pkt_buff, uint8_t len, uint16_t f_seq_num, uint8_t command);
//uint8_t get_queue_cnt();
bool add_to_ring_cmd(pkt_tuya_t *pkt, uint8_t confirm_need);


#endif /* SRC_INCLUDE_APP_UART_TUYA_H_ */
