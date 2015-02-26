#ifndef _smi_h_
#define _smi_h_
#include <stdint.h>

// SMI Registers
#define BASIC_CONTROL_REG                  0
#define BASIC_STATUS_REG                   1
#define PHY_ID1_REG                        2
#define PHY_ID2_REG                        3
#define AUTONEG_ADVERT_REG                 4
#define AUTONEG_LINK_REG                   5
#define AUTONEG_EXP_REG                    6
#define GIGE_CONTROL_REG                   9

#define BASIC_CONTROL_LOOPBACK_BIT        14
#define BASIC_CONTROL_100_MBPS_BIT        13
#define BASIC_CONTROL_1000_MBPS_BIT        6
#define BASIC_CONTROL_AUTONEG_EN_BIT      12
#define BASIC_CONTROL_RESTART_AUTONEG_BIT  9
#define BASIC_CONTROL_FULL_DUPLEX_BIT      8

#define BASIC_STATUS_LINK_BIT              2

#define AUTONEG_ADVERT_1000BASE_T_FULL_DUPLEX             9
#define AUTONEG_ADVERT_100BASE_TX_FULL_DUPLEX             8
#define AUTONEG_ADVERT_10BASE_TX_FULL_DUPLEX              6

#ifdef __XC__

typedef interface smi_if {
  uint16_t read_reg(uint8_t regnum);
  void write_reg(uint8_t regnum, uint16_t val);
} smi_if;

[[distributable]]
void smi(server interface smi_if i,
         unsigned device_addr,
         port p_mdio, port p_mdc);

[[distributable]]
void smi_singleport(server interface smi_if i,
                    unsigned device_addr,
                    port p_smi,
                    unsigned mdio_bit, unsigned mdc_bit);


void smi_configure(client smi_if smi, int speed_mbps, int enable_auto_neg);

void smi_set_loopback_mode(client smi_if smi, int enable);

unsigned smi_get_id(client smi_if smi);

int smi_is_link_up(client smi_if smi);

#endif

#endif // _smi_h_
