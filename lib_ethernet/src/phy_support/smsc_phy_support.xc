#include "ethernet.h"
#include "smi.h"
#include "timer.h"

#define ETHERNET_PHY_RESET_DELAY_US 1
// Check link state every second
#define ETHERNET_LINK_POLL_PERIOD_MS 1000

[[combinable]]
static void smsc_LAN8710_driver_aux(client smi_if smi,
                                    port ?p_reset,
                                    client ethernet_config_if i_config)
{
  // Initialize the phy
  if (!isnull(p_reset)) {
    p_reset <: 0;
    delay_microseconds(ETHERNET_PHY_RESET_DELAY_US);
    p_reset <: 1;
  }
  smi.configure_phy(1, 1);
  i_config.set_link_state(0, ETHERNET_LINK_UP);

  // Periodically check the link state
  ethernet_link_state_t link_state = ETHERNET_LINK_UP;
  timer tmr;
  int t;
  tmr :> t;
  while (1) {
    select {
    case tmr when timerafter(t) :> t:
      ethernet_link_state_t new_state = smi.get_link_state();
      if (new_state != link_state) {
        link_state = new_state;
        i_config.set_link_state(0, ETHERNET_LINK_DOWN);
      }
      t += ETHERNET_LINK_POLL_PERIOD_MS * XS1_TIMER_MHZ * 1000;
      break;
    }
  }
}

[[combinable]]
void smsc_LAN8710_driver(client ethernet_config_if i_config,
                         client output_gpio_if mdc, client inout_gpio_if p_mdio,
                         client output_gpio_if ?p_reset,
                         unsigned phy_address)
{
  // TODO
  while (1) select {}
}

#if 0
[[combinable]]
void smsc_LAN8710_driver_old(client ethernet_config_if i_config,
                             port p_mdio, port p_mdc, port ?p_reset,
                                 unsigned phy_address)
{
  smi_if i_smi;
  [[combine]]
  par {
    smi(i_smi, phy_address, p_mdio, p_mdc);
    smsc_LAN8710_driver_aux(i_smi, p_reset, i_config);
  }
}
#endif