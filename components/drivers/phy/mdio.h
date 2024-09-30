#ifndef __PHY_MDIO_H__
#define __PHY_MDIO_H__
#include <rtthread.h>
#include "phy.h"
struct mii_bus
{
   struct rt_list_node node;
	char name[RT_NAME_MAX];
	void *priv;
	int (*read)(struct mii_dev *bus, int addr, int devad, int reg);
	int (*write)(struct mii_dev *bus, int addr, int devad, int reg,
			rt_uint16_t val);
	int (*reset)(struct mii_dev *bus);
	struct rt_phy_device *phymap[RT_PHY_MAX];
	rt_uint32_t phy_mask;
	/** @reset_delay_us: Bus GPIO reset pulse width in microseconds */
	int reset_delay_us;
	/** @reset_post_delay_us: Bus GPIO reset deassert delay in microseconds */
	int reset_post_delay_us;
	/** @reset_gpiod: Bus Reset GPIO descriptor pointer */
	struct gpio_desc reset_gpiod;
}

#endif